#include "fbl_inc.hpp"
#include "fbl_diag_core.hpp"
#include "SwcServiceDcm.hpp"
#include "Version.hpp"

#if((FBLDIAG_14229_COREINT_VERSION != 0x0402u) || \
     (FBLDIAG_14229_COREINT_RELEASE_VERSION != 0x00u))
# error "Error in fbl_diag_core.c: Source and header file are inconsistent!"
#endif
#if(( FBLDIAG_14229_COREINT_VERSION != FBLDIAG_14229_CORE_VERSION ) || \
     ( FBLDIAG_14229_COREINT_RELEASE_VERSION != FBLDIAG_14229_CORE_RELEASE_VERSION ))
# error "Error in fbl_diag_core.h: Header versions are inconsistent."
#endif
#if((FBLDIAG_14229_CORE_VERSION != _FBLDIAG_14229_CORE_VERSION) || \
     (FBLDIAG_14229_CORE_RELEASE_VERSION != _FBLDIAG_14229_CORE_RELEASE_VERSION))
# error "Error in fbl_diag_core.c: Source and v_ver.h file are inconsistent!"
#endif

#if defined( FBL_DIAGCORE_API_REFERENCE_VERSION_MAJOR ) && \
    defined( FBL_DIAGCORE_API_REFERENCE_VERSION_MINOR )
#else
#  error "Error in fbl_diag_core.c: Interface version requirements not defined!"
#endif

#if( FBL_DIAGCORE_API_REFERENCE_VERSION_MAJOR != FBL_DIAGCORE_API_VERSION_MAJOR) || \
    ( FBL_DIAGCORE_API_REFERENCE_VERSION_MINOR > FBL_DIAGCORE_API_VERSION_MINOR)
# error "Error in fbl_diag_core.c: Interface version compatibility check failed!"
#endif

#if( kFblDiagStateSessionDefault != 0u )  || \
   ( kFblDiagStateSessionExtended != 1u ) || \
   ( kFblDiagStateSessionProgramming != 2u )
# error "Session states must not be changed to different values."
#endif

#define kDiagResponseActive               ( kDiagPutNoResponse  | kDiagPutPosResponse | kDiagPutNegResponse )

#if defined( FBL_DIAG_ENABLE_OEM_SESSIONCHECK_NRC )
#else
# define DiagNRCServiceCheckNotSucceeded() DiagNRCServiceNotSupportedInActiveSession()
#endif

#if !defined( FBL_DIAG_ENABLE_SPS_EXTENDED_SESSION ) && \
    !defined( FBL_DIAG_DISABLE_SPS_EXTENDED_SESSION )
# define FBL_DIAG_ENABLE_SPS_EXTENDED_SESSION
#endif
#if !defined( kDiagRqlSpsFromAppl )
# define kDiagRqlSpsFromAppl kDiagRqlDiagnosticSessionControl
#endif

#if !defined( kDiagEraseSucceeded )
# define kDiagEraseSucceeded                                0x00u
#endif
#if !defined( kDiagEraseFailed )
# define kDiagEraseFailed                                   0x01u
#endif

#if !defined(kSecSigSize)
# define kSecSigSize 0
#endif

#if( FBL_MAX_SEGMENT_SIZE > 64u )
# define FILL_BUFFER_SIZE FBL_MAX_SEGMENT_SIZE
#else
# define FILL_BUFFER_SIZE 64u
#endif

#if defined( FBL_DIAG_ENABLE_TASK_LOCKS )

# define kFblDiagStateTaskRunning      FBL_BIT0
# define kFblDiagTimerTaskRunning      FBL_BIT1

# define SetDiagStateTaskRunning()     (diagTaskState |= kFblDiagStateTaskRunning)
# define ClrFblDiagStateTaskRunning()  (diagTaskState &= FblInvert8Bit(kFblDiagStateTaskRunning))
# define GetDiagStateTaskRunning()     ((diagTaskState & kFblDiagStateTaskRunning) == kFblDiagStateTaskRunning)

# define SetDiagTimerTaskRunning()     (diagTaskState |= kFblDiagTimerTaskRunning)
# define ClrDiagTimerTaskRunning()     (diagTaskState &= FblInvert8Bit(kFblDiagTimerTaskRunning))
# define GetDiagTimerTaskRunning()     ((diagTaskState & kFblDiagTimerTaskRunning) == kFblDiagTimerTaskRunning)
#endif

V_MEMRAM0 V_MEMRAM1      vuint8              V_MEMRAM2 V_MEMRAM3 * V_MEMRAM1 V_MEMRAM2 DiagBuffer;

V_MEMRAM0 V_MEMRAM1_NEAR tCwDataLengthType   V_MEMRAM2_NEAR DiagDataLength;

V_MEMRAM0 V_MEMRAM1_NEAR vuint16             V_MEMRAM2_NEAR testerPresentTimeout;

V_MEMRAM0 V_MEMRAM1_NEAR vuint8              V_MEMRAM2_NEAR diagServiceCurrent;

V_MEMRAM0 V_MEMRAM1_NEAR tFblStateBitmap     V_MEMRAM2_NEAR fblDiagStates[FBL_STATE_INDEX(kFblDiagNumberOfStates - 1u) + 1u];

#if defined( FBL_ENABLE_DEBUG_STATUS )

V_MEMRAM0 V_MEMRAM1      vuint16          V_MEMRAM2      errStatErrorCode;
V_MEMRAM0 V_MEMRAM1      vuint16          V_MEMRAM2      errStatFblStates;
V_MEMRAM0 V_MEMRAM1      vuint8           V_MEMRAM2      errStatLastServiceId;
V_MEMRAM0 V_MEMRAM1      vuint8           V_MEMRAM2      errStatFlashDrvVersion[3];
V_MEMRAM0 V_MEMRAM1      vuint16          V_MEMRAM2      errStatFlashDrvErrorCode;
V_MEMRAM0 V_MEMRAM1      tBlockDescriptor V_MEMRAM2      errStatDescriptor;
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )
# if defined( FBL_DIAG_ENABLE_CORE_STAYINBOOT )

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 fblDiagStayInBootMsg[] = FBL_DIAG_STAY_IN_BOOT_ARRAY;

V_MEMROM0 V_MEMROM1 vuintx V_MEMROM2 kSizeOfStayInBootMsg = ARRAY_SIZE(fblDiagStayInBootMsg);
# endif
#endif

#if defined( FBL_CW_ENABLE_DECLINED_REQUESTS )

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 additionalDiagnosticBuffer[kFblCwMaxNumDeclinedRequests][FBL_DIAG_DECLINE_BUFFER_LENGTH];
V_MEMRAM0 static V_MEMRAM1 tFblResult V_MEMRAM2 additionalDiagBufferUsed[kFblCwMaxNumDeclinedRequests];
#endif

V_MEMRAM0 static V_MEMRAM1 vuint8               V_MEMRAM2      diagPostParam;

V_MEMRAM0 static V_MEMRAM1 vuint8               V_MEMRAM2      rcrrpBuffer[3];

V_MEMRAM0 static V_MEMRAM1 tCwDataLengthType    V_MEMRAM2      diagResLen;

#if defined( FBL_DIAG_ENABLE_TASK_LOCKS )
V_MEMRAM0 static V_MEMRAM1 vuint8               V_MEMRAM2      diagTaskState;
#endif

V_MEMRAM0 static V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3 * V_MEMRAM1 V_MEMRAM2 serviceInfo;

V_MEMRAM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3 * V_MEMRAM1 V_MEMRAM2 subServiceInfo;

#if defined( FBL_DIAG_ENABLE_SERVICE_PREHANDLER )

V_MEMRAM0 static V_MEMRAM1 tFblDiagPreHandler V_MEMRAM2 fblDiagServicePreHandler;
#endif

V_MEMRAM0 static V_MEMRAM1 tFblDiagMainHandler V_MEMRAM2 fblDiagServiceMainHandler;

V_MEMRAM0 static V_MEMRAM1 tFblDiagNrcHandler V_MEMRAM2 fblDiagServiceNrcHandler;
#if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )

V_MEMRAM0 static V_MEMRAM1 tFblDiagPostHandler V_MEMRAM2 fblDiagServicePostHandler;
#endif

V_MEMRAM0 V_MEMRAM1_NEAR vuint8          V_MEMRAM2_NEAR diagResponseFlag;

V_MEMRAM0 V_MEMRAM1 vuint8               V_MEMRAM2      diagErrorCode;

#if defined( FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING )

V_MEMRAM0 V_MEMRAM1 vuint8               V_MEMRAM2      segmentCount;
#endif

V_MEMRAM0 V_MEMRAM1 vuint16              V_MEMRAM2      ecuResetTimeout;

#if defined( FBL_ENABLE_SLEEPMODE )

V_MEMRAM0 V_MEMRAM1        vuint32              V_MEMRAM2      sleepCounter;
#endif
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

V_MEMRAM0 V_MEMRAM1 vuint32              V_MEMRAM2      secSecurityAccessDelay;
#endif

static void       ChkSuppressPosRspMsgIndication(vuint8 *subparam);
static void       FblDiagDiscardReception(void);
static void       FblDiagResponseProcessor(void);

static V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3 * FblDiagGetServiceInfo(vuint8 receivedServiceId);

static vuint32 FblDiagCheckServiceTableEntry(V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3* pServiceInfo,
                                             vuint8 *pbDiagData,
                                             tCwDataLengthType diagReqDataLen);
static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3* FblDiagFindSubTableEntry(V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3* pServiceInfo,
                                        V_MEMRAM1 vuint32 V_MEMRAM2 V_MEMRAM3* pServiceErrorMask,
                                        vuint8 *pbDiagData,
                                        tCwDataLengthType diagReqDataLen);
static vuint32 FblDiagCheckSubTableEntry(V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3* pSubtableInfo,
                                         vuint8 *pbDiagData,
                                         tCwDataLengthType diagReqDataLen);

static tFblResult FblDiagServiceProcessingTask(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);

static tFblResult FblDiagDefaultNrcHandler(vuint32 serviceErrorMask);

static void FblDiagDeinit(void);

#define FBLDIAG_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"
static void FblDiagResetServiceFlags(void);
static void FblDiagConfirmation(void);

#define FBLDIAG_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

void FblDiagEcuReset(void){
   StopTesterTimeout();

   DiagSetNoResponse();
   FblDiagDeinit();
}

void FblDiagSetError( vuint8 errorCode ){
   diagErrorCode = errorCode;

   if(    (FblDiagGetFunctionalRequest())
        && (!FblDiagGetRcrRpInProgress())
        && (   (errorCode == kDiagNrcServiceNotSupported )
            || (errorCode == kDiagNrcSubFunctionNotSupported )
            || (errorCode == kDiagNrcRequestOutOfRange )
#if defined( FBL_DIAG_ENABLE_14229_2013 )
            || (errorCode == kDiagNrcSubfunctionNotSupportedInActiveSession)
            || (errorCode == kDiagNrcServiceNotSupportedInActiveSession)
#endif
           )
      ){
     DiagSetNoResponse();
   }
   else{
      diagResponseFlag |= kDiagPutNegResponse;
   }
}

vuint8 FblRealTimeSupport( void ){
   vuint8 returnCode;

   returnCode = (vuint8)FblLookForWatchdog();
   DiagExRCRResponsePending(kNotForceSendResponsePending);
   return returnCode;
}

void DiagExRCRResponsePending( vuint8 forceSend ){
   if(FblDiagGetRcrRpAllowed()){
      if((forceSend == kForceSendResponsePending)
            || ((forceSend == kForceSendRpIfNotInProgress) && (!FblDiagGetRcrRpInProgress()))
            || (GetP2Timer() < (FblDiagGetRcrRpInProgress() ? kFblDiagP2StarMinThreshold : kFblDiagP2MinThreshold)) )
      {
         diagPostParam = kDiagPostRcrRp;

         rcrrpBuffer[0] = kDiagRidNegativeResponse;
         rcrrpBuffer[1] = diagServiceCurrent;
         rcrrpBuffer[2] = kDiagNrcRcrResponsePending;
         FblCwTransmitRP(rcrrpBuffer);

         SetP2Timer(kFblDiagTimeP2Star);

         diagResponseFlag &= FblInvert8Bit(kDiagPutNoResponse);

         FblDiagSetRcrRpInProgress();
      }
   }
}

V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * FblDiagMemGetActiveBuffer(void){
   DiagBuffer = FblMemGetActiveBuffer();
   return &DiagBuffer[kDiagFmtpbDiagData];
}

void DiagProcessingDone( tCwDataLengthType dataLength ){
   diagResponseFlag |= kDiagPutPosResponse;
   diagResLen        = dataLength;
}

static void FblDiagDiscardReception( void ){
   FblDiagSetResponseProcessing();

   FblCwDiscardReception();
   FblDiagClrResponseProcessing();
}

#define FBLDIAG_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"

static void FblDiagResetServiceFlags( void ){
   DiagClrError();

   FblDiagClrServiceInProgress();
   FblDiagClrRcrRpInProgress();

   FblDiagClrFunctionalRequest();
   FblDiagClrExecutePostHandler();

   FblDiagClrSuppressPosRspMsg();

   diagResponseFlag = kDiagResponseIdle;
}

static void FblDiagConfirmation( void ){
   FblDiagClrBufferLocked();

   ClrP2Timer();

#if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )

   if( FblDiagGetExecutePostHandler() && ( fblDiagServicePostHandler != (tFblDiagPostHandler)0u )){
      (*fblDiagServicePostHandler)( diagPostParam );
   }
#endif

   FblDiagResetServiceFlags();

#if defined( FBL_ENABLE_STAY_IN_BOOT )
   if(FblDiagGetProgrammingSession() || FblDiagGetExtendedSession() || FblMainGetStartMessageReceived())
#else
   if(FblDiagGetProgrammingSession() || FblDiagGetExtendedSession())
#endif
   {
      ResetTesterTimeout();
   }
}

#define FBLDIAG_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

static void FblDiagResponseProcessor( void ){
   if(( diagResponseFlag & kDiagResponseActive ) != 0u ){
      FblDiagClrRcrRpAllowed();
      ClrP2Timer();
      FblDiagClrRcrRpInProgress();

      FblDiagDiscardReception();
      FblErrStatSetSId( diagServiceCurrent );

      if(( diagResponseFlag & kDiagPutNoFuncResponse ) != 0u )
      {
         diagPostParam = kDiagPostNoResponse;

         FblDiagConfirmation();

         if(FblDiagGetWaitEcuReset())
         {
            FblDiagSetResetMsgConfirmed();
         }

         FblCwResetRxBlock();
      }
      else if(( diagResponseFlag & kDiagPutNegResponse) != 0u )
      {
         diagPostParam = kDiagPostNegResponse;

         DiagBuffer[kDiagFmtSubparam]     = diagServiceCurrent;
         DiagBuffer[kDiagFmtServiceId]    = kDiagRidNegativeResponse;
         DiagBuffer[kDiagFmtNegResponse]  = DiagGetError();

         assertFblUser(DiagGetError() != kDiagErrorNone, kFblSysAssertParameterOutOfRange);
         FblCwTransmit(DiagBuffer, 3u, kFblCwTxCallNegResponse);

         diagResponseFlag = kDiagResponseIdle;
      }
      else if(( diagResponseFlag & kDiagPutNoResponse ) != 0u )
      {
         diagPostParam = kDiagPostNoResponse;

         FblDiagConfirmation();

         if(FblDiagGetWaitEcuReset())
         {
            FblDiagSetResetMsgConfirmed();
         }

         FblCwResetRxBlock();
      }
      else if((diagResponseFlag & kDiagPutPosResponse) != 0u)
      {
         diagPostParam = kDiagPostPosResponse;

         DiagBuffer[kDiagFmtServiceId] = (vuint8)(diagServiceCurrent + 0x40u);
         FblCwTransmit(DiagBuffer, (tCwDataLengthType)( diagResLen + 1u ), kFblCwTxCallPosResponse );

         diagResponseFlag = kDiagResponseIdle;
      }
      else
      {
         assertFblInternal(0u, kFblSysAssertParameterOutOfRange);

         diagPostParam = kDiagResponseIdle;
      }

      if( diagPostParam == kDiagPostRcrRp )
      {
        diagResponseFlag = kDiagResponseIdle;
      }
   }
}

static void ChkSuppressPosRspMsgIndication( vuint8 *subparam ){
   if(((*(subparam)) & (kDiagSuppressPosRspMsgIndicationBit)) != 0u){
      DiagSetNoResponse();
      FblDiagSetSuppressPosRspMsg();

      (*(subparam)) &= FblInvert8Bit( kDiagSuppressPosRspMsgIndicationBit );
   }
}
#if defined( FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING )

vuint8 FblDiagSegmentNext( void ){
   vuint8 result;

   if(segmentCount >= SWM_DATA_MAX_NOAR){
      result =  kSwmOutOfRange;
   }
   else{
      segmentCount++;

      result = segmentCount;
   }

   return result;
}
#endif

#if defined( FBL_DIAG_ENABLE_CORE_GETBLOCKFROMID )

tFblResult FblGetNrFromBlockTable(V_MEMROM1 tBlockDescriptor V_MEMROM2 V_MEMROM3 * pBlockTable, vuint8 noOfBlocks,
   tFblLbtBlockIndex blockIndex, vuint8 * pLogicalBlockNr){
   tFblResult result;
   vuint8 tempCount;

   result = kFblFailed;
   *pLogicalBlockNr = 0xFFu;

   (void)FblLookForWatchdog();
   tempCount = 0u;

   while ((result == kFblFailed) && (tempCount < noOfBlocks)){
      if(blockIndex == pBlockTable[tempCount].blockIndex)
      {
         result = kFblOk;
         *pLogicalBlockNr = tempCount;
      }

      tempCount++;
   }

   return result;
}
#endif

void FblDiagInitPowerOn(void){
   vuintx i;

   for (i = 0u; i < (FBL_STATE_INDEX(kFblDiagNumberOfStates - 1u) + 1u); i++){
      fblDiagStates[i] = (tFblStateBitmap)0x00u;
   }

   diagResponseFlag = kDiagResponseIdle;

   DiagClrError();

#if defined( FBL_DIAG_ENABLE_SERVICE_PREHANDLER )
   fblDiagServicePreHandler = (tFblDiagPreHandler)0u;
#endif
   fblDiagServiceMainHandler = (tFblDiagMainHandler)0u;
   fblDiagServiceNrcHandler = (tFblDiagNrcHandler)0u;
#if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )
   fblDiagServicePostHandler = (tFblDiagPostHandler)0u;
#endif

   FblDiagSetDefaultSession();

   StopTesterTimeout();

   ClrP2Timer();

   ApplFblResetVfp();

   StopEcuResetTimeout();

#if defined( FBL_ENABLE_SLEEPMODE )

   FblSleepCounterClear();
#endif

#if defined( FBL_DIAG_ENABLE_TASK_LOCKS )
   diagTaskState = 0u;
#endif

#if defined( FBL_CW_ENABLE_DECLINED_REQUESTS )
   for (i = 0u; i < kFblCwMaxNumDeclinedRequests; i++){
     additionalDiagBufferUsed[i] = kFblFailed;
   }
#endif

#if defined( FBL_DIAG_ENABLE_OEM_INITPOWERON )

   FblDiagOemInitPowerOn();
#endif
}

void FblDiagInit(void){
   DiagBuffer = FblMemInitPowerOn();

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
# if defined( FBL_DIAG_ENABLE_CORE_READ_SECACCESSDELAY_FLAG )

   SetSecurityAccessDelay();
# endif
#endif

#if defined( FBL_ENABLE_DEBUG_STATUS )

   ApplFblInitErrStatus();
#endif

#if defined ( FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING )

   FblDiagSegmentInit();
#endif

   (void)ApplFblSecurityInit();

   FblCwSetTxInit();

#if defined( FBL_DIAG_ENABLE_OEM_INIT )

   FblDiagOemInit();
#endif
}

void FblDiagPostInit(void){
#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )
vuint8 resetCauseRead;
vuint8 resetCauseWrite;
#endif

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
# if defined( FBL_DIAG_ENABLE_CORE_READ_SECACCESSDELAY_FLAG )

   if(!ApplFblGetSecAccessDelayFlag()){
      ClrSecurityAccessDelay();
   }
# endif
#endif

#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )

         if(   (kFblOk == ApplFblReadResetResponseFlag(&resetCauseRead))
             && (resetCauseRead != RESET_RESPONSE_NOT_REQUIRED))
         {
            resetCauseWrite = RESET_RESPONSE_NOT_REQUIRED;

            (void)ApplFblWriteResetResponseFlag(&resetCauseWrite);

            if(FblMainGetStartFromAppl())
            {
               assertFblInternal(0u, kFblOemAssertInvalidError);

              FblDiagInitStartFromReset(resetCauseRead);
              FblDiagSetProgrammingSession();
              ResetTesterTimeout();
              FblDiagSetPreconditionsChecked();
              ClrFblMainState( kFblMainStateStartFromAppl );

            }
            else
            {
               FblDiagInitStartFromReset(resetCauseRead);
            }
         }
#endif

         if(FblMainGetStartFromAppl())
         {
            FblDiagInitStartFromAppl();
         }

#if defined( FBL_ENABLE_SLEEPMODE )

         FblSleepCounterReload();
#endif

#if defined( FBL_DIAG_ENABLE_OEM_POSTINIT )

   FblDiagOemPostInit();
#endif
}

static void FblDiagDeinit(void){
   FblMemDeinit();

#if defined( FBL_DIAG_ENABLE_OEM_DEINIT )

   FblDiagOemDeinit();
#endif

   if(FblDiagGetProgrammingSession()){
      FblDiagClrProgrammingSession();
      if(FblDiagGetMemDriverInitialized())
      {
         FblCwSetOfflineMode();

         (void)MemDriver_DeinitSync((void*)V_NULL);

         FblCwSetOnlineMode();

         FblDiagClrMemDriverInitialized();
      }

      ApplFblResetVfp();
   }

   FblDiagClrWaitEcuReset();

   FblDiagResetServiceFlags();

   FblCwShutdownRequest(kFblCwResetEcuRegularCase);
}

static tFblResult FblDiagServiceProcessingTask(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;
   vuint32 serviceProcessingErrors;
   uint8 ucMsgAuthResult;

    serviceProcessingErrors = kFblDiagServiceOk;

    if(diagResponseFlag == kDiagResponseRequested){
      (void)ApplFblSecuritySeedInit();

      diagResponseFlag = kDiagRepeatResponse;

      serviceInfo = FblDiagGetServiceInfo(diagServiceCurrent);

      if(serviceInfo == (V_MEMROM1 tFblDiagServiceTable  V_MEMROM2 V_MEMROM3 *) V_NULL)
      {
          serviceProcessingErrors = kFblDiagServiceNotFound;
          fblDiagServiceNrcHandler = FblDiagDefaultNrcHandler;
      }
      else
      {
          serviceProcessingErrors = FblDiagCheckServiceTableEntry(serviceInfo, pbDiagData, diagReqDataLen);
    #if defined( FBL_DIAG_ENABLE_SERVICE_PREHANDLER )
          fblDiagServicePreHandler = serviceInfo->servicePreHandler;
    #endif
          fblDiagServiceMainHandler = serviceInfo->serviceMainHandler;
    #if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )
          fblDiagServicePostHandler = serviceInfo->servicePostHandler;
    #endif
          fblDiagServiceNrcHandler = serviceInfo->serviceNrcHandler;

          ucMsgAuthResult = DcmCheckMessageAuthentication(DiagBuffer[kDiagFmtServiceId], &DiagBuffer[kDiagFmtSubparam], DiagDataLength);
          if(ucMsgAuthResult == MSG_REJECTED)
          {
            serviceProcessingErrors = kFblDiagServiceSecAccessFailure;
          }
          else if(ucMsgAuthResult == MSG_AUTH_SUCCESSFUL)
          {
            if(DiagDataLength > 16)
            {
              DiagDataLength -= 16;
              diagReqDataLen -= 16;
            }
          }
          else
          {
          }

          if(serviceProcessingErrors != kFblDiagServiceSecAccessFailure)
          {
            if((serviceProcessingErrors & kFblDiagSubTableNotFound) == 0u)
            {
              subServiceInfo = FblDiagFindSubTableEntry(serviceInfo, &serviceProcessingErrors, pbDiagData, diagReqDataLen);

              if((serviceProcessingErrors & kFblDiagSubTableNotFound) == kFblDiagSubTableNotFound)
              {
                  if((serviceProcessingErrors & kFblDiagServiceLevelErrors) == 0u)
                  {
                    if(fblDiagServiceMainHandler != (tFblDiagMainHandler)0u)
                    {
                        serviceProcessingErrors &= kFblDiagServiceLevelErrors;
                    }
                  }
              }
              else
              {
                  serviceProcessingErrors |= FblDiagCheckSubTableEntry(subServiceInfo, pbDiagData, diagReqDataLen);
                  fblDiagServiceMainHandler = subServiceInfo->serviceMainHandler;
              }
            }
            else
            {
              serviceProcessingErrors &= kFblDiagServiceLevelErrors;
            }

      #if defined( FBL_DIAG_ENABLE_SERVICE_PREHANDLER )

            if(((serviceProcessingErrors & kFblDiagServiceErrorMask) == 0u) && (fblDiagServicePreHandler != (tFblDiagPreHandler)V_NULL))
            {
              if((*fblDiagServicePreHandler)(pbDiagData, diagReqDataLen) == kFblFailed)
              {
                  serviceProcessingErrors |= kFblDiagServicePrehandlerFailure;
              }
            }
      #endif

          }

      }
    }

   if(serviceProcessingErrors == kFblDiagServiceOk){
      FblDiagSetRcrRpAllowed();

      result = (*fblDiagServiceMainHandler)(pbDiagData, diagReqDataLen);
   }
   else{
      result = (*fblDiagServiceNrcHandler)(serviceProcessingErrors);
   }

#if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )

   FblDiagSetExecutePostHandler();
#endif

   FblDiagResponseProcessor();

   return result;
}

void FblDiagStateTask( void ){
#if defined( FBL_DIAG_ENABLE_TASK_LOCKS )
   if(!GetDiagStateTaskRunning()){
      SetDiagStateTaskRunning();
#endif

      if((!FblDiagGetWaitEcuReset()) && (diagResponseFlag != kDiagResponseIdle))
      {
         (void)FblDiagServiceProcessingTask(&DiagBuffer[kDiagFmtSubparam], (tCwDataLengthType)(DiagDataLength));
      }

#if defined( FBL_MEM_ENABLE_PIPELINING )

      FblMemResumeIndication();
#endif

      if((FblDiagGetWaitEcuReset()) && (FblDiagGetResetMsgConfirmed()) && (FblDiagGetEcuResetFctFinished()))
      {
         FblDiagDeinit();
      }

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

      if(GetSecurityAccessDelay() == 1u)
      {
# if defined( FBL_DIAG_ENABLE_CORE_SECACCESSCOUNTER_RESET )

         vuint8 securityAccessDelayCounterReset;
         securityAccessDelayCounterReset = kDiagSecAccessResetValue;
         (void)ApplFblWriteSecAccessInvalidCount(&securityAccessDelayCounterReset);
# endif
# if defined( FBL_DIAG_ENABLE_CORE_WRITE_SECACCESSDELAY_FLAG )

         (void)ApplFblClrSecAccessDelayFlag();
# endif

         ClrSecurityAccessDelay();
      }
#endif

#if defined( FBL_DIAG_ENABLE_OEM_STATETASK )
      FblDiagOemStateTask();
#endif

#if defined( FBL_DIAG_ENABLE_TASK_LOCKS )

      ClrFblDiagStateTaskRunning();
   }
#endif
}

void FblDiagTimerTask(void){
#if defined( FBL_DIAG_ENABLE_TASK_LOCKS )
   if(!GetDiagTimerTaskRunning()){
      SetDiagTimerTaskRunning();
#endif

      if(TimeoutTesterValue() != 0u)
      {
         DecTimeoutTesterValue();
         if(TimeoutTesterValue() == 0u)
         {
#if defined( FBL_DIAG_ENABLE_OEM_SESSION_TIMEOUT )
            FblDiagSessionTimeout();
#else

            FblDiagEcuReset();
#endif
         }
      }

      if(TimeoutEcuResetValue() != 0u)
      {
         DecTimeoutEcuResetValue();
         if(TimeoutEcuResetValue() == 0u)
         {
            FblDiagEcuReset();
         }
      }

#if defined( FBL_ENABLE_SLEEPMODE )

            if(FblGetSleepCounter() != 0u)
            {
               FblDecSleepCounter();
               if(FblGetSleepCounter() == 0u)
               {
                  ApplFblBusSleep();
                  FblSleepCounterReload();
               }
            }
#endif

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

      if(GetSecurityAccessDelay() > 1u)
      {
         DecSecurityAccessDelay();
      }
#endif

#if defined( FBL_DIAG_ENABLE_OEM_TIMERTASK )
      FblDiagOemTimerTask();
#endif

#if defined( FBL_DIAG_ENABLE_TASK_LOCKS )

      ClrDiagTimerTaskRunning();
   }
#endif
}

static tFblResult FblDiagDefaultNrcHandler(vuint32 serviceErrorMask){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)serviceErrorMask;
#endif

#if defined( FBL_ENABLE_USERSERVICE )
   FblDiagSetRcrRpAllowed();
   ApplDiagUserService(&DiagBuffer[kDiagFmtSubparam], (tCwDataLengthType)(DiagDataLength));
#else
   DiagNRCServiceNotSupported();
#endif

   return kFblOk;
}

static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3* FblDiagFindSubTableEntry(V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3* pServiceInfo,
                                        V_MEMRAM1 vuint32 V_MEMRAM2 V_MEMRAM3* pServiceErrorMask,
                                        vuint8 *pbDiagData,
                                        tCwDataLengthType diagReqDataLen){
   V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3* subTableEntry;
   vuint32 tempServiceErrorMask;

   vuintx subFunctionLength;
   vuintx subParamLength;

   vuintx subTableIndex;
   vuintx subTableIdIndex;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)diagReqDataLen;
#endif

   subTableIndex = 0u;
   subTableEntry = (V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3*)V_NULL;

   *pServiceErrorMask |= (kFblDiagSubTableNotFound | kFblDiagSubfunctionNotFound | kFblDiagSubparamNotFound);

   if((pServiceInfo->serviceOptions & kFblDiagOptionServiceIsSubfunction) == kFblDiagOptionServiceIsSubfunction){
      subFunctionLength = 1u;

      ChkSuppressPosRspMsgIndication(pbDiagData);
   }
   else{
      subFunctionLength = 0u;
   }
   subParamLength = pServiceInfo->subTableIdLength - subFunctionLength;

   while (((*pServiceErrorMask & kFblDiagSubTableNotFound) == kFblDiagSubTableNotFound) && (subTableIndex < pServiceInfo->subTableLength)){
      tempServiceErrorMask = kFblDiagServiceOk;
      subTableEntry = &pServiceInfo->serviceSubTable[subTableIndex];

      for (subTableIdIndex = 0u; subTableIdIndex < (subFunctionLength + subParamLength); subTableIdIndex++)
      {
         if(subTableEntry->subTableParamTable[subTableIdIndex] != pbDiagData[kDiagLocFmtSubfunction + subTableIdIndex])
         {
            if(subTableIdIndex < subFunctionLength)
            {
               tempServiceErrorMask |= kFblDiagSubfunctionNotFound;
            }
            else
            {
               tempServiceErrorMask |= kFblDiagSubparamNotFound;
            }
         }
      }

      if((tempServiceErrorMask & kFblDiagSubfunctionNotFound) != kFblDiagSubfunctionNotFound)
      {
         *pServiceErrorMask &= FblInvert32Bit(kFblDiagSubfunctionNotFound);

         if((subTableEntry->serviceOptions & GetCurrentSession()) == 0u)
         {
            *pServiceErrorMask |= kFblDiagSubfuncSessionFailure;
            tempServiceErrorMask |= kFblDiagSubfuncSessionFailure;
         }

         if(((subTableEntry->serviceOptions & kFblDiagOptionSecuredService) == kFblDiagOptionSecuredService) && (!FblDiagGetSecurityUnlock()))
         {
            *pServiceErrorMask |= kFblDiagSubfuncSecAccessFailure;
            tempServiceErrorMask |= kFblDiagSubfuncSecAccessFailure;
         }
      }

      if((tempServiceErrorMask & kFblDiagSubparamNotFound) != kFblDiagSubparamNotFound)
      {
         *pServiceErrorMask &= FblInvert32Bit(kFblDiagSubparamNotFound);

         if((subTableEntry->serviceOptions & GetCurrentSession()) == 0u)
         {
            *pServiceErrorMask |= kFblDiagSubparamSessionFailure;
            tempServiceErrorMask |= kFblDiagSubparamSessionFailure;
         }

         if(((subTableEntry->serviceOptions & kFblDiagOptionSecuredService) == kFblDiagOptionSecuredService) && (!FblDiagGetSecurityUnlock()))
         {
            *pServiceErrorMask |= kFblDiagSubparamSecAccessFailure;
            tempServiceErrorMask |= kFblDiagSubparamSecAccessFailure;
         }
      }

      subTableIndex++;

      if((tempServiceErrorMask & (kFblDiagSubfunctionNotFound | kFblDiagSubparamNotFound)) == 0u)
      {
         *pServiceErrorMask &= kFblDiagServiceLevelErrors;

         *pServiceErrorMask |= tempServiceErrorMask;
      }
   }

   return subTableEntry;
}

static vuint32 FblDiagCheckSubTableEntry(V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3* pSubtableInfo,
                                         vuint8 *pbDiagData,
                                         tCwDataLengthType diagReqDataLen){
   vuint32 result;

   result = kFblDiagServiceOk;

   if(FblDiagGetFunctionalRequest() && ((pSubtableInfo->serviceOptions & kFblDiagOptionFunctionalRequest) == 0u)){
      result |= kFblDiagSubNoFuncSupport;
   }

   if(diagReqDataLen < pSubtableInfo->serviceLength){
      result |= kFblDiagSubMinLenFailure;
   }

   if(pSubtableInfo->serviceLengthCheck != (tFblDiagLengthCheck)0u){
      if(pSubtableInfo->serviceLengthCheck(pbDiagData, diagReqDataLen) == kFblFailed)
      {
         result |= kFblDiagSubLenFailure;
      }
   }
   else{
      if(pSubtableInfo->serviceLength != diagReqDataLen)
      {
         result |= kFblDiagSubLenFailure;
      }
   }

   return result;
}

static vuint32 FblDiagCheckServiceTableEntry(V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3* pServiceInfo,
                                             vuint8 *pbDiagData,
                                             tCwDataLengthType diagReqDataLen){
   vuint32 result;

   result = kFblDiagServiceOk;

   if(pServiceInfo->subTableLength == 0u){
      result |= kFblDiagSubTableNotFound;
   }

   if(diagReqDataLen < pServiceInfo->subTableIdLength){
      result |= kFblDiagSubTableNotFound;
   }

   if(FblDiagGetFunctionalRequest() && ((pServiceInfo->serviceOptions & kFblDiagOptionFunctionalRequest) == 0u)){
      result |= kFblDiagServiceNoFuncSupport;
   }

   if((pServiceInfo->serviceOptions & GetCurrentSession()) == 0u){
      result |= kFblDiagServiceSessionFailure;
   }

   if(diagReqDataLen < pServiceInfo->serviceLength){
      result |= kFblDiagServiceMinLenFailure;
   }

   if(((pServiceInfo->serviceOptions & kFblDiagOptionSecuredService) != 0u) && (!FblDiagGetSecurityUnlock())){
      result |= kFblDiagServiceSecAccessFailure;
   }

   if(pServiceInfo->serviceLengthCheck != (tFblDiagLengthCheck)0u){
      if(pServiceInfo->serviceLengthCheck(pbDiagData, diagReqDataLen) == kFblFailed)
      {
         result |= kFblDiagServiceLenFailure;
      }
   }
   else{
      if((pServiceInfo->subTableLength == 0u) && (pServiceInfo->serviceLength != diagReqDataLen))
      {
         result |= kFblDiagServiceLenFailure;
      }
   }

   return result;
}

static V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3 * FblDiagGetServiceInfo(vuint8 receivedServiceId){
   V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3 * serviceTableEntry;
   vuintx serviceIndex;

   serviceTableEntry = (V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3 *)V_NULL;

   for (serviceIndex = 0u; serviceIndex < kSizeOfServiceTable; serviceIndex++){
      if(kFblDiagServiceTable[serviceIndex].serviceId == receivedServiceId)
      {
         serviceTableEntry = &kFblDiagServiceTable[serviceIndex];
         break;
      }
   }

   return serviceTableEntry;
}

void FblDiagInitStartFromAppl(void){
   FblCwSetRxBlock();

   if(FblDiagRxGetPhysBuffer(kDiagRqlSpsFromAppl + 1u) == DiagBuffer){
      DiagBuffer[kDiagFmtServiceId] = kDiagSidDiagnosticSessionControl;

#if defined( FBL_DIAG_ENABLE_OEM_SPS_REQUEST )

      FblDiagOemPrepareSpsRequest(DiagBuffer, &DiagDataLength);
#else

      DiagBuffer[kDiagFmtSubparam] = kDiagSubProgrammingSession;
      DiagDataLength = kDiagRqlDiagnosticSessionControl;
#endif

#if defined( FBL_DIAG_ENABLE_SPS_EXTENDED_SESSION )

      FblDiagSetExtendedSession();
#endif

      ResetTesterTimeout();

      if(FblCwPrepareResponseAddress() == kFblOk)
      {
         FblDiagRxStartIndication();
         FblDiagRxIndication(DiagBuffer, DiagDataLength + 1u);

         FblDiagSetPreconditionsChecked();

         FblDiagStateTask();
      }
      else
      {
         FblDiagConfirmation();
         FblCwResetRxBlock();
      }
   }
   else{
      FblCwResetRxBlock();
   }
}

#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )

void FblDiagInitStartFromReset(vuint8 resetRequestType){
   FblCwSetRxBlock();

   if(FblDiagRxGetPhysBuffer(kDiagRqlDiagnosticSessionControl + 1u) == DiagBuffer){
      FblDiagSetDefaultSession();

      switch(resetRequestType)
      {
         case RESET_RESPONSE_SDS_REQUIRED:
         {
            diagServiceCurrent = kDiagSidDiagnosticSessionControl;
# if defined( FBL_DIAG_ENABLE_OEM_SDS_RESPONSE )

            FblDiagOemPrepareSdsResponse(DiagBuffer, &DiagDataLength);
# else

            DiagBuffer[kDiagFmtSubparam] = kDiagSubDefaultSession;
            DiagDataLength = kDiagRqlDiagnosticSessionControl;

            DiagBuffer[kDiagFmtSubparam + 1u] = (vuint8)(kDiagSessionTimingP2 >> 8u);
            DiagBuffer[kDiagFmtSubparam + 2u] = (vuint8)(kDiagSessionTimingP2);
            DiagBuffer[kDiagFmtSubparam + 3u] = (vuint8)(kDiagSessionTimingP2Star >> 8u);
            DiagBuffer[kDiagFmtSubparam + 4u] = (vuint8)(kDiagSessionTimingP2Star);
# endif

            if(FblCwPrepareResponseAddress() == kFblOk)
            {
# if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )

               FblDiagSetExecutePostHandler();
               fblDiagServicePostHandler = kFblDiagResponseSdsPostHandler;
# endif
               DiagProcessingDone(kDiagRslDiagnosticSessionControl);
               FblDiagResponseProcessor();
            }
            else
            {
               FblDiagConfirmation();
               FblCwResetRxBlock();
            }

            break;
         }
         case RESET_RESPONSE_ECURESET_REQUIRED:
         {
            diagServiceCurrent = kDiagSidEcuReset;
# if defined( FBL_DIAG_ENABLE_OEM_RR_RESPONSE )

            FblDiagOemPrepareRrResponse(DiagBuffer, &DiagDataLength);
# else

            DiagBuffer[kDiagFmtSubparam] = kFblDiagSubReset;
            DiagDataLength = kDiagRqlEcuReset;
# endif

            if(FblCwPrepareResponseAddress() == kFblOk)
            {
# if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )

               FblDiagSetExecutePostHandler();
               fblDiagServicePostHandler = kFblDiagResponseResetPostHandler;
# endif
               DiagProcessingDone(kDiagRslEcuReset);
               FblDiagResponseProcessor();
            }
            else
            {
               FblDiagConfirmation();
               FblCwResetRxBlock();
            }

            break;
         }
         default:
         {
            FblDiagConfirmation();
            FblCwResetRxBlock();
            break;
         }
      }
   }
}
#endif

#define FBLDIAG_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"

#if defined( FBL_ENABLE_STAY_IN_BOOT )
# if defined( FBL_DIAG_ENABLE_CORE_STAYINBOOT )

vuint8 FblDiagCheckStartMsg(const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *pData, vuintx length){
   vuint8 result;
   vuintx index;

   if(length < (kSizeOfStayInBootMsg + 1u)){
      result = kFblFailed;
   }
   else{
      if(kSizeOfStayInBootMsg == pData[0u])
      {
         result = kFblOk;

         for (index = 0u; index < kSizeOfStayInBootMsg; index++)
         {
            if(fblDiagStayInBootMsg[index] != pData[index + 1u])
            {
               result = kFblFailed;
               break;
            }
         }
      }
      else
      {
         result = kFblFailed;
      }
   }

   return result;
}
# endif
#endif

void FblDiagRxStartIndication(void){
   StopTesterTimeout();

   FblDiagSetServiceInProgress();

   DiagClrError();

#if defined( FBL_DIAG_ENABLE_SERVICE_PREHANDLER )
   fblDiagServicePreHandler = (tFblDiagPreHandler)0u;
#endif
   fblDiagServiceMainHandler = (tFblDiagMainHandler)0u;
   fblDiagServiceNrcHandler = (tFblDiagNrcHandler)0u;
#if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )
   fblDiagServicePostHandler = FblDiagDefaultPostHandler;
#endif
   serviceInfo = (V_MEMROM1 tFblDiagServiceTable V_MEMROM2 V_MEMROM3 *) V_NULL;
   subServiceInfo = (V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3 *) V_NULL;
}

void FblDiagRxIndication(vuint8* pbDiagBuffer, tCwDataLengthType rxDataLength){
   DiagBuffer = pbDiagBuffer;
   DiagDataLength = rxDataLength - 1u;

#if defined( FBL_DIAG_ENABLE_DYNAMIC_P2_HANDLING )
   SetP2Timer(fblDiagTimeP2Max);
#else
   SetP2Timer(kFblDiagTimeP2);
#endif

   if(    (kDiagSidTesterPresent == DiagBuffer[kDiagFmtServiceId])
        && (kDiagSuppressPosRspMsgIndicationBit == DiagBuffer[kDiagFmtSubparam])
        && (kDiagRqlTesterPresent == DiagDataLength)
        && FblDiagGetFunctionalRequest()
      ){
      FblDiagConfirmation();
      FblCwResetRxBlock();
   }
   else{
      diagResponseFlag = kDiagResponseRequested;
      diagServiceCurrent = DiagBuffer[kDiagFmtServiceId];

#if defined( FBL_MEM_ENABLE_PIPELINING )
      if(FblMemTaskIsPending())
      {
         FblMemRxNotification();
      }
#endif
   }

#if defined( FBL_ENABLE_SLEEPMODE )

   FblSleepCounterReload();
#endif
}

vuint8* FblDiagRxGetPhysBuffer(tCwDataLengthType rxDataLength){
   vuint8* result;

   result = (vuint8*)V_NULL;

   if((rxDataLength > 0u )
        && (FBL_DIAG_BUFFER_LENGTH >= rxDataLength)
        && (!FblDiagGetBufferLocked())
      ){
      FblDiagClrFunctionalRequest();

      FblDiagSetBufferLocked();

      result = DiagBuffer;
   }

   return result;
}

vuint8* FblDiagRxGetFuncBuffer(tCwDataLengthType rxDataLength){
   vuint8* funcBuffer = FblDiagRxGetPhysBuffer(rxDataLength);

   if((void*)V_NULL != funcBuffer){
      FblDiagSetFunctionalRequest();
   }

   return funcBuffer;
}

void FblDiagRxErrorIndication(void){
   FblDiagConfirmation();
}

void FblDiagTxErrorIndication(vuint8 cwMsgType){
   if(cwMsgType != kFblCwMsgTypeRcrRp){
      FblDiagConfirmation();
   }
}

void FblDiagTxConfirmation(vuint8 cwMsgType){
   if(cwMsgType != kFblCwMsgTypeRcrRp){
      FblDiagConfirmation();
   }

   if(FblDiagGetWaitEcuReset()){
      FblDiagSetResetMsgConfirmed();
   }
}

#if defined( FBL_CW_ENABLE_DECLINED_REQUESTS )

void FblDiagRxDeclineIndication(vuint8* pbDiagBuffer, tCwDataLengthType rxDataLength, vuint8 connectionIndex){
   tCwDataLengthType messageLength;

   messageLength = rxDataLength;
   FblDiagOem_ProcessDeclineRequest((V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *)pbDiagBuffer, (V_MEMRAM1 tCwDataLengthType V_MEMRAM2 V_MEMRAM3 *)&messageLength);
   FblCwPduTransmitDeclinedRequest(pbDiagBuffer, messageLength, connectionIndex);
}

vuint8* FblDiagRxGetDeclineBuffer(tCwDataLengthType rxDataLength, vuint8 connectionIndex){
   vuint8* result;

   result = (vuint8*)V_NULL;

   if((connectionIndex > 0u) &&
       (rxDataLength > 0u) &&
       (rxDataLength <= FBL_DIAG_DECLINE_BUFFER_LENGTH) &&
       (additionalDiagBufferUsed[connectionIndex - 1u] == kFblFailed)
      ){
      result = &additionalDiagnosticBuffer[connectionIndex - 1u][0u];
      additionalDiagBufferUsed[connectionIndex - 1u] = kFblOk;
   }

   return result;
}

void FblDiagDeclineErrorIndication(vuint8 connectionIndex){
   additionalDiagBufferUsed[connectionIndex - 1u] = kFblFailed;
}

void FblDiagDeclineTxConfirmation(vuint8 connectionIndex){
   additionalDiagBufferUsed[connectionIndex - 1u] = kFblFailed;
}

#endif

# define FBLDIAG_RAMCODE_STOP_SEC_CODE
# include "MemMap.hpp"

#if defined( FBL_DIAG_ENABLE_CORE_PREWRITE )

tFblResult FblDiagMemPreWrite(void){
   FblCwSetOfflineMode();

   return kFblOk;
}
#endif

#if defined( FBL_DIAG_ENABLE_CORE_POSTWRITE )

tFblResult FblDiagMemPostWrite(void){
   FblCwSetOnlineMode();

   return kFblOk;
}
#endif

