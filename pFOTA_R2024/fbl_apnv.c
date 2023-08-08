#include "fbl_inc.hpp"

#include "BrsHw.hpp"
# include "SwcServiceDet.hpp"
# if(DET_ENABLED == STD_ON)
#   include "McalCan.hpp"
#   include "SwcServiceCanTp.hpp"
# endif

#include "ProductionFlashInterfaceX.hpp"

#if( FBLKBAPI_FRAMENV_UDS1_VERSION != 0x0601u ) || \
    ( FBLKBAPI_FRAMENV_UDS1_RELEASE_VERSION != 0x00u )
# error "Error in fbl_apnv.c Source and header file are inconsistent!"
#endif

#if( (FBLKBAPI_FRAMENV_UDS1_VERSION != _FBLKBAPI_FRAMENV_OEM_VERSION ) || \
      (FBLKBAPI_FRAMENV_UDS1_RELEASE_VERSION != _FBLKBAPI_FRAMENV_OEM_RELEASE_VERSION) )
# error "Error in fbl_apxx.c: Source and v_ver.h are inconsistent!"
#endif

# if( kEepSizeValidityFlags != kNrOfValidationBytes )
#  error "Size of block validity data is not correct. Check GENy configuration of size."
# endif

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 blockFingerprint[kEepSizeFingerprint];

#if defined( FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK )
#else
# if defined( FBL_ENABLE_PRESENCE_PATTERN )
V_MEMRAM0 static V_MEMRAM1 tBlockDescriptor V_MEMRAM2 currentValidatedBlock;
# endif
#endif

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
#else
static tFblResult ApplFblChgBlockValid( vuint8 mode, tBlockDescriptor descriptor );
#endif

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
#else

static tFblResult ApplFblChgBlockValid( vuint8 mode, tBlockDescriptor descriptor ){
   vuint8         validityMask;
   tFblResult     result;

   vuint8         byteIdx;
   vuint8         validityFlags[kEepSizeValidityFlags];
   vuint8         validityCheck[kEepSizeValidityFlags];

   byteIdx = (vuint8)(descriptor.blockNr >> 0x03u);
   validityMask = (vuint8)(0x01u << (descriptor.blockNr & 0x07u));

   result = kFblFailed;

   if(((ApplFblNvReadValidityFlags(validityFlags))) == kFblOk){
      if(mode == kEepValidateBlock)
      {
         validityFlags[byteIdx] &= FblInvert8Bit(validityMask);
      }
      else
      {
         validityFlags[byteIdx] |= validityMask;
      }

      if(ApplFblNvWriteValidityFlags(validityFlags) == kFblOk)
      {
         if(ApplFblNvReadValidityFlags(validityCheck) == kFblOk)
         {
            if(validityCheck[byteIdx] == validityFlags[byteIdx])
            {
               result = kFblOk;
            }
         }
      }
   }
   return result;
}
#endif

tFblResult ApplFblAdjustLbtBlockData( tBlockDescriptor * blockDescriptor ){
   tFblResult        result;
#if defined( FBL_ENABLE_PRESENCE_PATTERN )
   IO_PositionType   presPtnAddress;
   IO_SizeType       presPtnLen;
#endif

   result = kFblOk;

#if defined( FBL_ENABLE_PRESENCE_PATTERN )

   if(result == kFblOk){
      memSegment = FblNvPatternGetBaseAddr(blockDescriptor->blockNr, (tFblNvPatternId)(kFblNvPatternId_Last - 1u), &presPtnAddress, &presPtnLen);

      if(memSegment >= 0)
      {
         blockDescriptor->blockLength -= ((presPtnLen * 2u) * (kFblNvPatternId_Last - 1u));
      }
      else
      {
         result = kFblFailed;
      }
   }
#endif

   return result;
}

tFblProgStatus ApplFblExtProgRequest( void ){
   tFblProgStatus progStatus;
#if defined( FBL_ENABLE_FBL_START )
#else
   vuint8 progReqFlag;
#endif

   progStatus = kNoProgRequest;

# if defined( FBL_ENABLE_FBL_START )

   if(FblBmChkFblStartMagicFlag()){
      FblBmClrMagicFlag();

      progStatus = kProgRequest;
   }
# else

   if(ApplFblNvReadProgReqFlag(&progReqFlag) == kFblOk){
      if(progReqFlag == kEepFblReprogram)
      {
         progReqFlag = 0u;
         (void)ApplFblNvWriteProgReqFlag(&progReqFlag);

         progStatus = kProgRequest;
      }
   }
# endif
# if defined( FBL_ENABLE_STAY_IN_BOOT )
   if(FblBmChkStayInBootMagicFlag()){
      FblBmClrMagicFlag();

      progStatus = kCheckStayInBootRequest;
   }
# endif
   return progStatus;
}

tFblResult ApplFblValidateBlock( tBlockDescriptor blockDescriptor ){
   tFblResult result;

   result = kFblOk;

   {
#if defined( FBL_ENABLE_PRESENCE_PATTERN )

      currentValidatedBlock = blockDescriptor;

      if(FblNvPatternSet(&blockDescriptor, kFblNvPatternId_BlockValidity) != kFblOk)
      {
         result = kFblFailed;
      }
#else

      if(ApplFblChgBlockValid(kEepValidateBlock, blockDescriptor) != kFblOk)
      {
         result = kFblFailed;
      }
#endif
   }

   return result;
}

tFblResult ApplFblInvalidateBlock( tBlockDescriptor blockDescriptor ){
   tFblResult result;

      {
         result = ApplFblInvalidateApp();
      }

   {
      if(result == kFblOk)
      {
#if defined( FBL_ENABLE_PRESENCE_PATTERN )

         result = FblNvPatternClr(&blockDescriptor, kFblNvPatternId_BlockValidity);
#else
         result = ApplFblChgBlockValid(kEepInvalidateBlock, blockDescriptor);
#endif
      }

      if(result == kFblOk)
      {
		result = (tFblResult)ApplFblNvWriteTesterSerialNumber(&blockFingerprint[0]);
		if(result == kFblOk)
        {
			result = (tFblResult)ApplFblNvWriteProgrammingDate(&blockFingerprint[20]);
		}
      }
   }

   return result;
}

tApplStatus ApplFblIsValidApp( void ){
   tApplStatus applicationStatus;
# if defined( FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK )
# else
#  if defined( FBL_ENABLE_PRESENCE_PATTERN )
   tBlockDescriptor iterBlock;
   tFblLbtBlockFilter blockFilter;
   vuint8 device;
#  else
   vuint8 applValidity;
#  endif
# endif

   applicationStatus = kApplInvalid;

# if defined( FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK )

   if(ApplFblCheckProgDependencies() == 0x00u){
      applicationStatus = kApplValid;
   }
# else
#  if defined( FBL_ENABLE_PRESENCE_PATTERN )

   FblLbtBlockFilterInit(&blockFilter);
   iterBlock = FblLbtBlockFirst(&blockFilter);
   while ((FblLbtBlockDone() == FALSE) && (applicationStatus == kApplInvalid)){
      if(kFblOk == FblMemGetDeviceByRange(iterBlock.blockStartAddress, iterBlock.blockLength, &device))
      {
#   if defined( kMioDeviceRam )

         if(device != kMioDeviceRam)
#   endif
         {
            if(FblNvPatternGet(&iterBlock, kFblNvPatternId_ApplValidity) == kFblOk)
            {
               applicationStatus = kApplValid;
            }
         }
      }

      iterBlock = FblLbtBlockNext();
   }
#  else

   if(ApplFblNvReadApplValidity(&applValidity) == kFblOk){
      if(applValidity == kEepApplConsistent)
      {
         applicationStatus = kApplValid;
      }
   }
#  endif
# endif

# if( FBL_PROJECT_STATE >= FBL_INTEGRATION )
   if((applicationStatus == kApplValid) && (FblCheckBootVectTableIsValid())){
      applicationStatus = kApplInvalid;
   }
# endif

   return applicationStatus;
}

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

vuint8 ApplFblRWSecurityAccessDelayFlag( vuint8 mode, vuint8 value ){
   tFblResult readResult;
   vuint8 buffer;
   vuint8 result;

   readResult = (tFblResult)ApplFblNvReadSecAccessDelayFlag(&buffer);

   if(mode == kEepWriteData){
      if((readResult == kFblOk) && (buffer == value))
      {
         result = kFblOk;
      }
      else
      {
         buffer = value;
         result = ((tFblResult)ApplFblNvWriteSecAccessDelayFlag(&buffer));
      }
   }
   else{
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

      (void)value;
#endif

      result = kEepSecAccessDelayActive;

      if(readResult == kFblOk)
      {
         result = buffer;
      }
   }

   return result;
}
#endif

tFblResult ApplFblStoreFingerprint( vuint8 * buffer ){
   (void)MEMCPY(blockFingerprint, buffer, kEepSizeFingerprint);

   return kFblOk;
}

void ApplFblErrorNotification( tFblErrorType errorType, tFblErrorCode errorCode ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)errorType;
   (void)errorCode;
#endif
}

tFblResult ApplFblIncProgCounts( tBlockDescriptor blockDescriptor ){
   vuint16 progCounts;
   vuint8 nvBuffer[sizeof(vuint16)];
   tFblResult status;

   status = (tFblResult)ApplFblNvReadProgCounter(blockDescriptor.blockNr, nvBuffer);
   progCounts = (vuint16)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);

   if(status == kFblOk){
      progCounts = FblInvert16Bit(progCounts);
      progCounts++;
      progCounts = FblInvert16Bit(progCounts);

      FblMemSetInteger(sizeof(nvBuffer), progCounts, nvBuffer);
      status = (tFblResult)ApplFblNvWriteProgCounter(blockDescriptor.blockNr, nvBuffer);
   }

   return status;
}

tFblResult ApplFblGetProgCounts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progCounts){
   tFblResult status;
   vuint8 nvBuffer[sizeof(vuint16)];
   vuint16 tempCount;

   status = (tFblResult)ApplFblNvReadProgCounter(blockDescriptor.blockNr, nvBuffer);
   tempCount = (vuint16)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);
   *progCounts = FblInvert16Bit(tempCount);

   return status;
}

tFblResult ApplFblIncProgAttempts( tBlockDescriptor blockDescriptor ){
   vuint16 progAttempts;
   vuint8 nvBuffer[sizeof(vuint16)];
   tFblResult status;

   status = (tFblResult)ApplFblNvReadProgAttempts(blockDescriptor.blockNr, nvBuffer);
   progAttempts = (vuint16)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);

   if(status == kFblOk){
      progAttempts = FblInvert16Bit(progAttempts);
      progAttempts++;
      progAttempts = FblInvert16Bit(progAttempts);

      FblMemSetInteger(sizeof(nvBuffer), progAttempts, nvBuffer);
      status = (tFblResult)ApplFblNvWriteProgAttempts(blockDescriptor.blockNr, nvBuffer);
   }

   return status;
}

tFblResult ApplFblGetProgAttempts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progAttempts ){
   tFblResult status;
   vuint8 nvBuffer[sizeof(vuint16)];
   vuint16 tempCount;

   status = (tFblResult)ApplFblNvReadProgAttempts(blockDescriptor.blockNr, nvBuffer);
   tempCount = (vuint16)FblMemGetInteger(sizeof(nvBuffer), nvBuffer);
   *progAttempts = FblInvert16Bit(tempCount);

   return status;
}

tFblLbtMaxProgAttempts ApplFblGetPromMaxProgAttempts(tFblLbtBlockNr blockNr){
   tFblLbtMaxProgAttempts maxProgAttempt;

   if(FblLbtGetBlockMaxProgAttemptsByNr(blockNr, &maxProgAttempt) != kFblOk){
      maxProgAttempt = 0u;
   }

   return maxProgAttempt;
}

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

tFblResult ApplFblWriteSecAccessInvalidCount( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * invalidCount ){
   vuint8 buffer;

   buffer = FblInvert8Bit(*invalidCount);

   return (tFblResult)ApplFblNvWriteSecAccessInvalidCount(&buffer);
}

tFblResult ApplFblReadSecAccessInvalidCount( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * invalidCount ){
   tFblResult status;

   status = (tFblResult)ApplFblNvReadSecAccessInvalidCount(invalidCount);

   if(status == kFblOk){
      *invalidCount = FblInvert8Bit(*invalidCount);
   }
   else{
      *invalidCount = 0u;
   }

   return status;
}
#endif

#if defined( SEC_DISABLE_CRC_TOTAL )
#else

tFblResult ApplFblWriteCRCTotal( V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, vuint32 crcStart, vuint32 crcLength, vuint32 crcValue ){
   tFblResult status;
   vuint8 strConversionBuffer[4u];

   status = kFblOk;

# if( kEepSizeCRCStart  != 4u ) || \
     ( kEepSizeCRCLength != 4u ) || \
     ( kEepSizeCRCValue  != 4u )
#  error "Error in FBL_APNV.C: Configuration error (kEepSizeCRC... != 4)"
# endif

   FblMemSetInteger(kEepSizeCRCStart, crcStart, strConversionBuffer);
   status |= (tFblResult)ApplFblNvWriteCRCStart(blockDescriptor->blockNr, strConversionBuffer);

   FblMemSetInteger(kEepSizeCRCLength, crcLength, strConversionBuffer);
   status |= (tFblResult)ApplFblNvWriteCRCLength(blockDescriptor->blockNr, strConversionBuffer);

   FblMemSetInteger(kEepSizeCRCValue, crcValue, strConversionBuffer);
   status |= (tFblResult)ApplFblNvWriteCRCValue(blockDescriptor->blockNr, strConversionBuffer);

   return status;
}
#endif

#if defined( FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK )
#else

tFblResult ApplFblValidateApp( void ){
   tFblResult result;
# if defined( FBL_ENABLE_PRESENCE_PATTERN )
# else
   vuint8 applValidity;
# endif

# if defined( FBL_ENABLE_PRESENCE_PATTERN )
   {
      result = FblNvPatternSet(&currentValidatedBlock, kFblNvPatternId_ApplValidity);
   }
# else
   applValidity = kEepApplConsistent;
   result = (tFblResult)ApplFblNvWriteApplValidity(&applValidity);
# endif

   return result;
}

tFblResult ApplFblInvalidateApp( void ){
   tFblResult result;
# if defined( FBL_ENABLE_PRESENCE_PATTERN )
   tBlockDescriptor iterBlock;
   tFblLbtBlockFilter blockFilter;
# else
   vuint8 applValidity;
# endif

   result = kFblOk;

# if defined( FBL_ENABLE_PRESENCE_PATTERN )

   FblLbtBlockFilterInit(&blockFilter);
   iterBlock = FblLbtBlockFirst(&blockFilter);
   while ((FblLbtBlockDone() == FALSE) && (result == kFblOk)){
      {
         result = FblNvPatternClr(&iterBlock, kFblNvPatternId_ApplValidity);
      }

      iterBlock = FblLbtBlockNext();
   }
# else
   applValidity = kEepApplInconsistent;
   result = (tFblResult)ApplFblNvWriteApplValidity(&applValidity);
# endif

   return result;
}
#endif

# if defined( FBL_CW_ENABLE_MULTIPLE_CONNECTIONS )

tFblResult ApplFblWriteDcmDslRxTesterSourceAddr(vuint8* buffer){
   return ApplFblNvWriteDcmDslRxTesterSourceAddr(buffer);
}

tFblResult ApplFblReadDcmDslRxTesterSourceAddr(vuint8* buffer){
   return ApplFblNvReadDcmDslRxTesterSourceAddr(buffer);
}
# endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

tFblResult ApplFblErasePatternArea(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * logicalBlockDescriptor){
   tFblResult     result;

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
   tFblAddress    patternAddress;
#endif

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
   tFblLength     patternLength;
   tFblLength     macStructLength;
   tFblLength     dataLength;

   dataLength = 0u;
   patternLength = 0u;
   macStructLength = 0u;
#endif

   result = kFblOk;

#if defined( FBL_ENABLE_PRESENCE_PATTERN )

   memSegment = FblNvPatternGetBaseAddr(logicalBlockDescriptor->blockNr, (tFblNvPatternId)(kFblNvPatternId_Last - 1u), &patternAddress, &patternLength);

   if(memSegment >= 0){
      if(FlashBlock[memSegment].end >= patternAddress)
      {
         patternLength = FlashBlock[memSegment].end - patternAddress;
      }
      else
      {
         result = kFblFailed;
      }
   }
   else{
      result = kFblFailed;
   }
#endif

#if defined( FBL_ENABLE_PRESENCE_PATTERN )

   if(result == kFblOk){
      DiagExRCRResponsePending(kForceSendRpIfNotInProgress);

      dataLength = ((FlashBlock[memSegment].end + 1u) - FlashBlock[memSegment].begin) - (patternLength + macStructLength);
# if defined( FBL_BSPATCH_ENABLE_RAM_BUFFER )

      FblReadProm(FlashBlock[memSegment].begin, fblBspatchNewImageBuffer, dataLength);

      FblMemEraseRegion(FlashBlock[memSegment].begin, FlashBlock[memSegment].end - FlashBlock[memSegment].begin + 1u);

      FblMemProgramBuffer(FlashBlock[memSegment].begin, &dataLength, fblBspatchNewImageBuffer);
# else
#  error "This default implementation requires the Bspatch module with temporary RAM buffer, please adapt this example using an own buffer"
# endif
      result = kFblOk;
   }
#endif
   return result;
}
#endif

