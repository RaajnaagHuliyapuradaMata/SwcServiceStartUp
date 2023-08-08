#define BM_AP_C

#include "bm_ap.hpp"
#include "bm_main.hpp"
#include "fbl_inc.hpp"
#include "fbl_main_types.hpp"

#if defined( FBLBM_ENABLE_STANDALONE_MODE )
# include "SwcServiceDet.hpp"
#endif
#if defined( FBLBM_ENABLE_SECURE_BOOT )
# include "SwcServiceCsm.hpp"
# include "fbl_secboot.hpp"
#endif

# include "BrsHw.hpp"
# include "version.hpp"
# include "SUPPLIER1_CustomFunctions.hpp"
# include "dr7f701013.dvf.hpp"

#if( FBLBM_AP_VERSION != 0x0301u ) || \
    ( FBLBM_AP_RELEASE_VERSION != 0x01u )
# error "Error in bm_ap.c: Source and Header file are inconsistent!"
#endif

#if !defined( FBL_MTAB_LBT_BLOCK_NUMBER )
# define FBL_MTAB_LBT_BLOCK_NUMBER                       FBL_MTAB_BOOTLOADER_BLOCK_NUMBER
#endif

#if defined( FBLBMAP_ARRAY_SIZE )
#else
# define FBLBMAP_ARRAY_SIZE(arr)                         (sizeof(arr) / sizeof((arr)[0]))
#endif

#define FBLBMAP_START_SEC_VAR
#include "MemMap.hpp"

#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
V_MEMRAM0 static V_MEMRAM1 vuintx V_MEMRAM2 g_ApplFblBmSearchUpdaterHeaderIndex;
#endif

#define FBLBMAP_STOP_SEC_VAR
#include "MemMap.hpp"

#define FBLBMAP_START_SEC_CODE
#include "MemMap.hpp"

void ApplFblBmPowerOnPre( void ){
	   if(SUPPLIER1_GetWakeupFactorRramCopy() == 0)
     {
       SUPPLIER1_SetWakeupFactorRramCopy(WUF0);
     }

}

void ApplFblBmPowerOnPost( void ){
}

void ApplFblBmInitPre( void ){
   BrsHwWatchdogInitPowerOn();

   BrsHwPllInitPowerOn();

# if defined( FBL_ENABLE_PRE_TIMERINIT )

   FblTimerInit();
# endif

}

void ApplFblBmInitPost( void ){
#if defined( FBLBM_ENABLE_SECURE_BOOT )
#endif

#if !defined( FBL_ENABLE_PRESENCE_PATTERN ) || \
    !defined( FBL_ENABLE_FBL_START )

#if defined( WRAPNV_USECASE_FEE )
   WrapNv_Init();
#else
   (void)EepromDriver_InitSync(V_NULL);
#endif
#endif

  #if defined (FBL_SUPPLIER1_NVM)

    ApplFblNvInit();
  #endif

  #ifdef LORDSTOWN_STARTER_APP
    JSR_APPL();
  #else
    if((WUF0 & 0x78000) != 0)
	  {
			JSR_APPL();
	  }
  #endif

}

#if defined( FBLBM_AP_CALLOUT_RESET )

void ApplFblBmReset(void){
   BrsHwSoftwareResetECU();
}
#endif

#if defined( FBLBM_AP_CALLOUT_CHECK_TARGET_VALIDITY )

tFblResult ApplFblBmCheckTargetValidity(tFblBmHdrTargetHandle targetHandle){
   tFblResult result;
# if defined( FBL_ENABLE_PRESENCE_PATTERN )
   vuint8 blockNo;
   tBlockDescriptor blockDescriptor;
   vuint8 device;
# else
   vuint8 applValidity;
# endif

   if(targetHandle == FBLBMHDR_TARGET_APPL){
      result = kFblFailed;

# if defined( FBL_ENABLE_PRESENCE_PATTERN )

      blockNo = 0u;

      while ((blockNo < FblLbtGetBlockCount()) && (result != kFblOk))
      {
         if(kFblOk == FblLbtGetBlockDescriptorByNr(blockNo, &blockDescriptor))
         {
            if(kFblOk == FblMemGetDeviceByRange(blockDescriptor.blockStartAddress, blockDescriptor.blockLength, &device))
            {
#  if defined( kMioDeviceRam )

               if(device != kMioDeviceRam)
#  endif
               {
                  result = FblNvPatternGet(&blockDescriptor, kFblNvPatternId_ApplValidity);
               }
            }
         }

         blockNo++;
      }
# else

      #ifndef SMART_TESTER_JUMP_IN
      if(SUPPLIER1_CustomerSpecificValidityChecks() == TRUE)
      {
        applValidity = applValidity;
        result = kFblOk;
      }
      #endif

# endif
   }
   else{
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBLBM_AP_CALLOUT_IS_VALIDBLOCK )

tFblResult ApplFblBmIsValidBlock(tFblBmHdrTargetHandle targetHandle,
   const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * pLogicalBlock){
   tFblResult result;
# if defined( FBL_ENABLE_PRESENCE_PATTERN )
   vuint8 device;
# else
   vuint8 validityFlags[kEepSizeValidityFlags];
   vuint8 validityMask;
   vuint8 byteIdx;
# endif

# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)targetHandle;
# endif

   result = kFblFailed;

# if defined( FBL_ENABLE_PRESENCE_PATTERN )

   if(kFblOk == FblMemGetDeviceByRange(pLogicalBlock->blockStartAddress, pLogicalBlock->blockLength, &device)){
#  if defined( kMioDeviceRam )

      if(device != kMioDeviceRam)
#  endif
      {
         result = FblNvPatternGetByBlockDescriptor(pLogicalBlock, kFblNvPatternId_BlockValidity );
      }
   }
# else

   byteIdx = (pLogicalBlock->blockNr >> 0x03u);
   validityMask = (vuint8)(0x01u << (pLogicalBlock->blockNr & 0x07u));

   if(ApplFblNvReadValidityFlags(validityFlags) == kFblOk){
      if((validityFlags[byteIdx] & validityMask) == 0u)
      {
         result = kFblOk;
      }
   }
# endif

   return result;
}
#endif

#if defined( FBLBM_AP_CALLOUT_START_SOFTWARE )

void ApplFblBmStartSoftware(const V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 V_MEMRAM3 * bmHeader){
   JSR(bmHeader->bmEntryAddress);

# if defined( FBL_ENABLE_SYSTEM_CHECK )

   while (1){
      ;
   }
# endif
}
#endif

#if defined( FBLBM_ENABLE_SECURE_BOOT )
# if defined( FBLBM_AP_CALLOUT_GET_KEYEMPTY )

tFblBmKeyEmptyResult ApplFblBmGetKeyEmpty( void ){
   tFblBmKeyEmptyResult result;
   vuint8 cmac[16u]= {0u};
   vuint8 data[16u] = {0u};
   uint32 length = 16u;
   uint32 macId;

   macId = FblBmHdr_GetFblSbMacId(FBLBMHDR_TARGET_FBL);

   if(kFblOk ==  FblSb_MacGenerate(macId, (uint32)data, sizeof(data), cmac, &length)){
      result = FBLBM_KEY_IS_AVAILABLE;
   }
   else{
      result = FBLBM_KEY_IS_NOT_AVAILABLE;
   }

   return result;
}
# endif

# if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
#  if defined( FBLBM_AP_CALLOUT_GET_FBL_CMACERASED )

tFblBmMacEmptyResult ApplFblBmGetFblCmacErased( const tFblBmBlockInfo * fblBlockInfo ){
   tFblBmMacEmptyResult result;
   tFblAddress macStructAddress;
   vuint8 buffer[0x100u];
   tFblLength macStructLength;
   tFblLength readCount;
   vuintx i;

   if(kFblOk != ApplFblSbGetBaseAddrByBlockDescriptor(&fblBlockInfo->logicalBlock, &macStructAddress, &macStructLength)){
      FBLBM_CALLOUT_FATAL_ERROR(FBLBM_ERROR_AP_CHECK_MAC_READ_FAIL);
   }

   if(sizeof(buffer) < macStructLength){
      FBLBM_CALLOUT_FATAL_ERROR(FBLBM_ERROR_AP_CHECK_MAC_BUF_LENGTH);
   }

   if(IO_E_ERASED == FblReadPromExt(macStructAddress, buffer, macStructLength, &readCount)){
      result = FBLBM_MAC_IS_NOT_AVAILABLE;
   }
   else{
      result = FBLBM_MAC_IS_NOT_AVAILABLE;
      for(i = 0; i < macStructLength; i++)
      {
         if(buffer[i] != FBL_FLASH_DELETED)
         {
            result = FBLBM_MAC_IS_AVAILABLE;
         }
      }
   }

   if(macStructLength != readCount){
      FBLBM_CALLOUT_FATAL_ERROR(FBLBM_ERROR_AP_CHECK_MAC_READ_FAIL_LENGTH);
   }

   return result;
}
#  endif
# endif
#endif

#if !defined( FBL_ENABLE_FBL_START )
# if defined( FBLBM_AP_CALLOUT_CHECKREPROGFLAG )

tFblResult ApplFblBmCheckReprogFlag( void ){
   tFblResult result;
   vuint8 progReqFlag;

   result = kFblFailed;
   progReqFlag = 0u;

   if(ApplFblNvReadProgReqFlag(&progReqFlag) == kFblOk){
      if(progReqFlag == kEepFblReprogram)
      {
         result = kFblOk;
      }
# if defined( FBL_ENABLE_XCP )
      else if(progReqFlag == kEepFblXcpProgram)
      {
         result = kFblOk;
      }
# endif
      else
      {
      }
   }

   return result;
}
# endif
#endif

#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
# if defined( FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_INIT )

tFblResult ApplFblBmSearchUpdaterHeaderInit(void){
   g_ApplFblBmSearchUpdaterHeaderIndex = 0u;
   return kFblOk;
}
# endif

# if defined( FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_HEADER_ADDRESS )

tFblResult ApplFblBmSearchUpdaterHeaderAddress(vuint32 * headerAddress){
   vuint32 offset = 0u;
   (* headerAddress) = FlashBlock[g_ApplFblBmSearchUpdaterHeaderIndex].begin + offset;
   return kFblOk;
}
# endif

# if defined( FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_NEXT )

tFblResult ApplFblBmSearchUpdaterHeaderNext(void){
   tFblResult result;

   g_ApplFblBmSearchUpdaterHeaderIndex ++;

   if(g_ApplFblBmSearchUpdaterHeaderIndex < kNrOfFlashBlock){
      result = kFblOk;
   }
   else{
      result = kFblFailed;
   }

   return result;
}
# endif
#endif

#if defined( FBLBM_AP_CALLOUT_FATAL_ERROR )

void ApplFblBmFatalError(tFblBmError error){
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)error;
# endif

# if defined( FBL_ENABLE_SYSTEM_CHECK )

   while (1){
      ;
   }
# endif
}
#endif

#if defined( FBLBM_ENABLE_STANDALONE_MODE )
# if defined( FBL_ENABLE_ASSERTION )

void ApplFblFatalError( FBL_DECL_ASSERT_EXTENDED_INFO(vuint8 errorCode) ){
   volatile vuint8 stayInWhile = 1u;

#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)errorCode;
#  endif

   while (0u != stayInWhile){
      FblLookForWatchdogVoid();
   }
}
# endif

# if(DET_ENABLED == STD_ON)

#  if((DET_AR_RELEASE_MAJOR_VERSION >= 4u) && (DET_AR_RELEASE_MINOR_VERSION >= 3u))
FUNC(Std_ReturnType, DET_CODE) ApplFbl_DetEntryHandler( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId )
#  else
FUNC(boolean, DET_APPL_CODE) ApplFbl_DetEntryHandler( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId )
#  endif
{
#  if((DET_AR_RELEASE_MAJOR_VERSION >= 4u) && (DET_AR_RELEASE_MINOR_VERSION >= 3u))
   Std_ReturnType result = E_OK;

#  else
   boolean result = FALSE;

#  endif

#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)ModuleId;
   (void)InstanceId;
   (void)ApiId;
   (void)ErrorId;
#  endif

   return result;
}
# endif
#endif

#define FBLBMAP_STOP_SEC_CODE
#include "MemMap.hpp"

