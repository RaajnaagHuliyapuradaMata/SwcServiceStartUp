

#include "fbl_inc.hpp"

#if( FBLWRAPPERFLASH_RH850RV40HIS_VERSION != 0x0111u ) || \
    ( FBLWRAPPERFLASH_RH850RV40HIS_RELEASE_VERSION != 0x00u )
# error "Error in fbl_flio.c: Source and header file are inconsistent!"
#endif

#if( FBLWRAPPERFLASH_RH850RV40HIS_VERSION != _FBLWRAPPERFLASH_HW_VERSION ) || \
    ( FBLWRAPPERFLASH_RH850RV40HIS_RELEASE_VERSION != _FBLWRAPPERFLASH_HW_RELEASE_VERSION )
# error "Error in fbl_flio.c: Source and v_ver.h are inconsistent!"
#endif

#if defined( FLASH_ENABLE_MACHINE_CHECK_ECC_DETECTION )
#define FBL_FLASH_ENABLE_ECC_SAFE_READ
#endif

#ifndef FLASH_AUTH_ID_0
#define FLASH_AUTH_ID_0 0xFFFFFFFFul
#endif
#ifndef FLASH_AUTH_ID_1
#define FLASH_AUTH_ID_1 0xFFFFFFFFul
#endif
#ifndef FLASH_AUTH_ID_2
#define FLASH_AUTH_ID_2 0xFFFFFFFFul
#endif
#ifndef FLASH_AUTH_ID_3
#define FLASH_AUTH_ID_3 0xFFFFFFFFul
#endif

#define FLASHCODE_START_SEC_VAR
#include "MemMap.hpp"
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 flashCode[FLASH_SIZE];
#define FLASHCODE_STOP_SEC_VAR
#include "MemMap.hpp"

static tFlashParam flashParam;

IO_ErrorType FlashDriver_InitSync ( void * address ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)address;
#endif

   if( (FLASH_DRIVER_MCUTYPE(flashCode)   != FLASH_DRIVER_VERSION_MCUTYPE)  ||
        (FLASH_DRIVER_MASKTYPE(flashCode)  != FLASH_DRIVER_VERSION_MASKTYPE) ||
        (FLASH_DRIVER_INTERFACE(flashCode) != FLASH_DRIVER_VERSION_INTERFACE)
      ){
      return kFlashInitInvalidVersion;
   }

   flashParam.wdTriggerFct = (IO_U8(*)(void)) FblLookForWatchdog;
   flashParam.reserved1    = (IO_U8)   0x00u;
   flashParam.reserved2    = (IO_U8)   0x00u;
   flashParam.errorCode    = kFlashOk;

   flashParam.majorVersion = (IO_U8)   FLASH_DRIVER_VERSION_MAJOR;
   flashParam.minorVersion = (IO_U8)   FLASH_DRIVER_VERSION_MINOR;
   flashParam.patchLevel   = (IO_U8)   FLASH_DRIVER_VERSION_PATCH;

   flashParam.authID[0u] = FLASH_AUTH_ID_0;
   flashParam.authID[1u] = FLASH_AUTH_ID_1;
   flashParam.authID[2u] = FLASH_AUTH_ID_2;
   flashParam.authID[3u] = FLASH_AUTH_ID_3;

   flashParam.frequencyMHz = FBL_SYSTEM_FREQUENCY;

   FLASH_DRIVER_INIT(flashCode, &flashParam);

   return (flashParam.errorCode);
}

IO_ErrorType FlashDriver_DeinitSync ( void * address ){
   vuint32 i;
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)address;
#endif

   FLASH_DRIVER_DEINIT(flashCode, &flashParam);

   for(i = 0; i < FLASH_SIZE; i++){
      flashCode[i] = 0x00u;

      if((i & 0xFFul) == 0x00ul)
      {
         (void)FblLookForWatchdog();
      }
   }

   return flashParam.errorCode;
}

IO_ErrorType FlashDriver_RWriteSync ( IO_MemPtrType writeBuffer, IO_SizeType writeLength, IO_PositionType writeAddress ){
   IO_ErrorType retVal;

   if((writeAddress & (FLASH_SEGMENT_SIZE - 1)) != 0x00u){
      retVal = kFlashWriteInvalidAddr;
   }
   else if((writeLength & (FLASH_SEGMENT_SIZE - 1)) != 0x00u){
      retVal = kFlashWriteInvalidSize;
   }
   else{
      retVal = kFlashOk;
   }

   if( (retVal == kFlashOk) && (writeLength > 0) ){
      flashParam.address = (tFlashAddress)writeAddress;
      flashParam.length = (tFlashLength)writeLength;
      flashParam.data = (tFlashData*)writeBuffer;

      FLASH_DRIVER_WRITE(flashCode, &flashParam);
      retVal = flashParam.errorCode;

   }

   return retVal;

}

IO_ErrorType FlashDriver_REraseSync ( IO_SizeType eraseLength, IO_PositionType eraseAddress ){
   IO_ErrorType retValue;

   flashParam.address = eraseAddress;
   flashParam.length  = eraseLength;

   FLASH_DRIVER_ERASE(flashCode, &flashParam);

   retValue   = flashParam.errorCode;

   return retValue;

}

#if defined ( FBL_ENABLE_USR_RREAD_SYNC )
#else

IO_ErrorType FlashDriver_RReadSync ( IO_MemPtrType readBuffer, IO_SizeType readLength, IO_PositionType readAddress ){
   IO_ErrorType retValue      = IO_E_OK;

#if defined( FBL_FLASH_ENABLE_ECC_SAFE_READ )
   const vuint8* tempPtr      = readBuffer;

   vuint16 tempSEGCONT        = FBL_SEG_CONT;

   tFblEccCtl tempCFECCCTL    = FBL_CODE_FLASH_ECC_CTL;
   tFblEccErrInt tempCFERRINT = FBL_CODE_FLASH_ECC_ERRINT;

   FBL_SEG_CONT               = tempSEGCONT & FblInvert16Bit(kSegContRome);

   FBL_CODE_FLASH_ECC_CTL     = kEccProtWrite;

   FBL_CODE_FLASH_ECC_ERRINT  = kEccNotificationDisable;

   FBL_CODE_FLASH_ECC_ERROR_CLEAR();

   (void)MEMCPY(readBuffer, readAddress, readLength);

   if( (FBL_CODE_FLASH_ECC_FSTERSTR & kEccUncorrectableError) == kEccUncorrectableError ){
      FBL_CODE_FLASH_ECC_CTL  = ( kEccProtWrite | kEccCorrectionDisable );

      (void)MEMCPY(readBuffer, readAddress, readLength);

      while((retValue == IO_E_OK) && (readLength > 0u))
      {
         if(*tempPtr != FBL_FLASH_DELETED)
         {
            retValue = IO_E_NOT_OK;
         }
         tempPtr++;
         readLength--;
      }

      if(retValue == IO_E_OK)
      {
         retValue = IO_E_ERASED;
      }

      FBL_CODE_FLASH_ECC_ERROR_CLEAR();
   }

   FBL_SEG_FLAG &= FblInvert16Bit(kSegFlagRomf);
   FBL_SEG_CONT = tempSEGCONT;
   FBL_CODE_FLASH_ECC_CTL = (kEccProtWrite | tempCFECCCTL);
   FBL_CODE_FLASH_ECC_ERRINT = tempCFERRINT;
#else

   (void)MEMCPY(readBuffer, readAddress, readLength);
#endif
   return retValue;

}
#endif

IO_U32 FlashDriver_GetVersionOfDriver(void){
   if( (FLASH_DRIVER_MCUTYPE(flashCode)   != FLASH_DRIVER_VERSION_MCUTYPE)  ||
        (FLASH_DRIVER_MASKTYPE(flashCode)  != FLASH_DRIVER_VERSION_MASKTYPE) ||
        (FLASH_DRIVER_INTERFACE(flashCode) != FLASH_DRIVER_VERSION_INTERFACE)
      ){
      return (IO_U32)(((IO_U32)FLASH_DRIVER_VERSION_MAJOR << 16) | \
                      ((IO_U32)FLASH_DRIVER_VERSION_MINOR <<  8) | \
                      ((IO_U32)FLASH_DRIVER_VERSION_PATCH));
   }
   else{
      return (IO_U32)(((IO_U32)flashParam.majorVersion << 16) | \
                      ((IO_U32)flashParam.minorVersion <<  8) | \
                      ((IO_U32)flashParam.patchLevel));
   }
}

#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )

IO_ErrorType FlashDriver_SetResetVector ( IO_PositionType vectorAddress, IO_SizeType coreIndex ){
   flashParam.address    = vectorAddress;
   flashParam.length     = coreIndex;

   FLASH_DRIVER_SET_RESET_VECTOR(flashCode, &flashParam);

   return (flashParam.errorCode);

}
#endif

#if defined( FLASH_ENABLE_OPTIONBYTE_API )

IO_ErrorType FlashDriver_GetOptionByte ( IO_U32 * readBuffer, IO_SizeType readLength ){
   flashParam.data = &readBuffer[0u];
   flashParam.length = readLength;

   FLASH_DRIVER_GET_OPTIONBYTE(flashCode, &flashParam);

   return (flashParam.errorCode);
}

IO_ErrorType FlashDriver_SetOptionByte ( IO_U32 * writeBuffer, IO_SizeType writeLength ){
   flashParam.data = &writeBuffer[0u];
   flashParam.length = writeLength;

   FLASH_DRIVER_SET_OPTIONBYTE(flashCode, &flashParam);

   return (flashParam.errorCode);
}
#endif

