

#ifndef FBL_DIAG_CORE_H
#define FBL_DIAG_CORE_H

#define FBLDIAG_14229_COREINT_VERSION           0x0402u
#define FBLDIAG_14229_COREINT_RELEASE_VERSION   0x00u

#define FBL_DIAGCORE_API_VERSION_MAJOR    0x04u

#define FBL_DIAGCORE_API_VERSION_MINOR    0x01u

#define FBL_DIAGCORE_API_VERSION_RELEASE  0x00u

#define kFblDiagOptionSessionDefault         0x01u
#define kFblDiagOptionSessionExtended        0x02u
#define kFblDiagOptionSessionProgramming     0x04u
#define kFblDiagOptionSecuredService         0x08u
#define kFblDiagOptionServiceIsSubfunction   0x10u
#define kFblDiagOptionFunctionalRequest      0x20u

#define kDiagStateNone                       0x00u

#define FblDiagClrDiagSession()              FBL_STATE_MULTICLR(fblDiagStates, kFblDiagStateSessionDefault, kFblDiagStateSessionProgramming)

#define kFblDiagStateMaskSessionDefault      kFblDiagStateMask(kFblDiagStateSessionDefault)
#define FblDiagSetDefaultSession()                 \
{                                                  \
   FblDiagClrDiagSession();                        \
   SetFblDiagState(kFblDiagStateSessionDefault);   \
}

#define kFblDiagStateMaskSessionExtended     kFblDiagStateMask(kFblDiagStateSessionExtended)

#define FblDiagSetExtendedSession()                   \
{                                                  \
   FblDiagClrDiagSession();                        \
   SetFblDiagState(kFblDiagStateSessionExtended);  \
}

#define kFblDiagStateMaskSessionProgramming  kFblDiagStateMask(kFblDiagStateSessionProgramming)
#define FblDiagSetProgrammingSession()                   \
{                                                     \
   FblDiagClrDiagSession();                           \
   SetFblDiagState(kFblDiagStateSessionProgramming);  \
}

#define kFblDiagStateMaskSession          (kFblDiagStateMaskSessionDefault|kFblDiagStateMaskSessionExtended|kFblDiagStateMaskSessionProgramming)
#define GetCurrentSession()               (vuint8)(fblDiagStates[0] & kFblDiagStateMaskSession)

#define ARRAY_SIZE(arr)                   (sizeof(arr) / sizeof((arr)[0]))

#define FblDiagClrDefaultSession()        ClrFblDiagState( kFblDiagStateSessionDefault )
#define FblDiagClrProgrammingSession()    ClrFblDiagState( kFblDiagStateSessionProgramming )
#define FblDiagClrExtendedSession()       ClrFblDiagState( kFblDiagStateSessionExtended )
#define FblDiagSetBufferLocked()          SetFblDiagState( kFblDiagStateDiagBufferLocked )
#define FblDiagClrBufferLocked()          ClrFblDiagState( kFblDiagStateDiagBufferLocked )
#define FblDiagSetExecutePostHandler()    SetFblDiagState( kFblDiagStateExecutePostHandler )
#define FblDiagClrExecutePostHandler()    ClrFblDiagState( kFblDiagStateExecutePostHandler )
#define FblDiagSetRcrRpAllowed()          SetFblDiagState( kFblDiagStateRcrRpAllowed )
#define FblDiagClrRcrRpAllowed()          ClrFblDiagState( kFblDiagStateRcrRpAllowed )
#define FblDiagSetRcrRpInProgress()       SetFblDiagState( kFblDiagStateRcrRpInProgress )
#define FblDiagClrRcrRpInProgress()       ClrFblDiagState( kFblDiagStateRcrRpInProgress )
#define FblDiagSetResponseProcessing()    SetFblDiagState( kFblDiagStateResponseProcessing )
#define FblDiagClrResponseProcessing()    ClrFblDiagState( kFblDiagStateResponseProcessing )
#define FblDiagSetSuppressPosRspMsg()     SetFblDiagState( kFblDiagStateSuppressPosRspMsg )
#define FblDiagClrSuppressPosRspMsg()     ClrFblDiagState( kFblDiagStateSuppressPosRspMsg )
#define FblDiagSetServiceHasSubfunction() SetFblDiagState( kFblDiagStateServiceHasSubfunction )
#define FblDiagClrServiceHasSubfunction() ClrFblDiagState( kFblDiagStateServiceHasSubfunction )
#define FblDiagSetServiceInProgress()     SetFblDiagState( kFblDiagStateServiceInProgress )
#define FblDiagClrServiceInProgress()     ClrFblDiagState( kFblDiagStateServiceInProgress )
#define FblDiagSetFunctionalRequest()     SetFblDiagState( kFblDiagStateFunctionalRequest )
#define FblDiagClrFunctionalRequest()     ClrFblDiagState( kFblDiagStateFunctionalRequest )
#define FblDiagSetTransferTypeFlash()     SetFblDiagState( kFblDiagStateTransferTypeFlash )
#define FblDiagClrTransferTypeFlash()     ClrFblDiagState( kFblDiagStateTransferTypeFlash )

#define FblDiagSetWaitEcuReset()                   \
{                                                  \
   SetFblDiagState( kFblDiagStateWaitEcuReset );   \
   ResetEcuResetTimeout();                         \
}
#define FblDiagClrWaitEcuReset()                   \
{                                                  \
   ClrFblDiagState( kFblDiagStateWaitEcuReset );   \
   StopEcuResetTimeout();                          \
}
#define FblDiagSetEcuResetFctFinished()   SetFblDiagState( kFblDiagStateEcuResetFctFinished )
#define FblDiagClrEcuResetFctFinished()   ClrFblDiagState( kFblDiagStateEcuResetFctFinished )
#define FblDiagSetResetMsgConfirmed()     SetFblDiagState( kFblDiagStateResetMsgConfirmed )
#define FblDiagClrResetMsgConfirmed()     ClrFblDiagState( kFblDiagStateResetMsgConfirmed )

#define FblDiagSetPreconditionsChecked()  SetFblDiagState( kFblDiagStatePreconditionsChecked )
#define FblDiagClrPreconditionsChecked()  ClrFblDiagState( kFblDiagStatePreconditionsChecked )
#define FblDiagSetMemDriverInitialized()  SetFblDiagState( kFblDiagStateMemDriverInitialized )
#define FblDiagClrMemDriverInitialized()  ClrFblDiagState( kFblDiagStateMemDriverInitialized )

#define kDiagSessionTimingP2                 ( kFblDiagTimeP2 * FBL_REPEAT_CALL_CYCLE )
#define kDiagSessionTimingP2StarRaw          ( kFblDiagTimeP2Star * FBL_REPEAT_CALL_CYCLE )
#define kDiagSessionTimingP2Star             ( kDiagSessionTimingP2StarRaw / 10u )

#if !defined( kFblDiagP2MinThreshold )
# define kFblDiagP2MinThreshold              ( kDiagSessionTimingP2 / 2u )
#endif

#if !defined( kFblDiagP2StarMinThreshold )
# define kFblDiagP2StarMinThreshold          ( kDiagSessionTimingP2StarRaw / 2u )
#endif

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
# if !defined(kSecMaxInvalidKeys)
#  define kSecMaxInvalidKeys           0x03u
# endif
# define kSecSecurityAccessDelay       ((vuint32) FBL_SEC_ACCESS_DELAY_TIME )
#endif

#if defined( kCwMaxWaitTimeEcuResetRequest )
# define kFblDiagMaxWaitTimeEcuResetRequest     (kCwMaxWaitTimeEcuResetRequest / FBL_REPEAT_CALL_CYCLE)
#else
# define kFblDiagMaxWaitTimeEcuResetRequest     kFblDiagTimeP2Star
#endif

#if !defined( kFblDiagSubReset )
# define kFblDiagSubReset                       kDiagSubHardReset
#endif

#define TimeoutEcuResetValue()                  ecuResetTimeout
#define DecTimeoutEcuResetValue()              (ecuResetTimeout--)
#define ResetEcuResetTimeout()                 (ecuResetTimeout = (vuint16)(kFblDiagMaxWaitTimeEcuResetRequest/kDiagCallCycle))
#define StopEcuResetTimeout()                  (ecuResetTimeout = 0u)

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

# define SetSecurityAccessDelay()      (secSecurityAccessDelay = (vuint32)(kSecSecurityAccessDelay / kDiagCallCycle))
# define GetSecurityAccessDelay()      (secSecurityAccessDelay)
# define DecSecurityAccessDelay()      (secSecurityAccessDelay--)
# define ClrSecurityAccessDelay()      (secSecurityAccessDelay = 0u)
#endif

#define DiagClrError()                    ( diagErrorCode = kDiagErrorNone )
#define DiagGetError()                    ( diagErrorCode )

#if defined ( FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING )

#define kSwmOutOfRange           0xFFu
#define FblDiagSegmentInit()     (segmentCount = 0u)
#endif

#define DiagSetNoResponse()               ( diagResponseFlag |= kDiagPutNoResponse )
#define DiagGetNoResponse()               ( diagResponseFlag & kDiagPutNoResponse )

#define kDiagResponseIdle                 0x00u
#define kDiagResponseRequested            FBL_BIT0
#define kDiagPutNoResponse                FBL_BIT1
#define kDiagPutNoFuncResponse            FBL_BIT2
#define kDiagPutPosResponse               FBL_BIT3
#define kDiagPutNegResponse               FBL_BIT4
#define kDiagRepeatResponse               FBL_BIT7

#define kDiagPostPosResponse              0x00u
#define kDiagPostNegResponse              0x01u
#define kDiagPostFailedResponse           0x02u
#define kDiagPostRcrRp                    0x03u
#define kDiagPostNoResponse               0x04u

#define kFblDiagServiceOk                 0x00000000u
#define kFblDiagServiceErrorMask          0xFFFFFFFEu
#define kFblDiagServiceLevelErrors        0x0000FFFEu
#define kFblDiagSubTableNotFound          0x00000001u
#define kFblDiagGeneralFailure            0x00000002u
#define kFblDiagServiceNotFound           0x00000100u
#define kFblDiagServiceNoFuncSupport      0x00000200u
#define kFblDiagServiceSessionFailure     0x00000400u
#define kFblDiagServiceMinLenFailure      0x00000800u
#define kFblDiagServiceSecAccessFailure   0x00001000u
#define kFblDiagServiceLenFailure         0x00002000u

#define kFblDiagSubfunctionNotFound       0x00010000u
#define kFblDiagSubparamNotFound          0x00020000u
#define kFblDiagSubNoFuncSupport          0x00040000u
#define kFblDiagSubfuncSessionFailure     0x00080000u
#define kFblDiagSubparamSessionFailure    0x00100000u
#define kFblDiagSubMinLenFailure          0x00200000u
#define kFblDiagSubfuncSecAccessFailure   0x00400000u
#define kFblDiagSubparamSecAccessFailure  0x00800000u
#define kFblDiagSubLenFailure             0x01000000u

#define kFblDiagServicePrehandlerFailure  0x10000000u

typedef struct tagSubFctInfoTable
{
   V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3  *subFctParamIdTable;

   vuint8                     sessionSupport;

   tCwDataLengthType          serviceLen;

   vsintx                     mainInstanceHandlerIdx;
}tSubFctInfoTable;

typedef struct tagFblDiagServiceSubTable
{
   V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3  *subTableParamTable;

   vuint32              serviceOptions;

   tCwDataLengthType    serviceLength;

   tFblDiagLengthCheck  serviceLengthCheck;

   tFblDiagMainHandler  serviceMainHandler;
}tFblDiagServiceSubTable;

typedef struct tagFblDiagServiceTable
{
   vuint8               serviceId;

   vuint32              serviceOptions;

   tCwDataLengthType    serviceLength;

   tFblDiagLengthCheck  serviceLengthCheck;

   vuintx               subTableLength;

   vuintx               subTableIdLength;

   V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 V_MEMROM3 * serviceSubTable;
#if defined( FBL_DIAG_ENABLE_SERVICE_PREHANDLER )

   tFblDiagPreHandler   servicePreHandler;
#endif

   tFblDiagMainHandler  serviceMainHandler;

   tFblDiagNrcHandler   serviceNrcHandler;
#if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )
   tFblDiagPostHandler  servicePostHandler;
#endif
}tFblDiagServiceTable;

V_MEMRAM0 extern V_MEMRAM1_NEAR vuint8          V_MEMRAM2_NEAR diagResponseFlag;
V_MEMRAM0 extern V_MEMRAM1 vuint16              V_MEMRAM2      ecuResetTimeout;
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
V_MEMRAM0 extern V_MEMRAM1 vuint32              V_MEMRAM2      secSecurityAccessDelay;
#endif
V_MEMRAM0 extern V_MEMRAM1 vuint8               V_MEMRAM2      diagErrorCode;
#if defined( FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING )
V_MEMRAM0 extern V_MEMRAM1 vuint8               V_MEMRAM2      segmentCount;
#endif

V_MEMROM0 extern V_MEMROM1 tFblDiagServiceTable V_MEMROM2      kFblDiagServiceTable[];
V_MEMROM0 extern V_MEMROM1 vuintx V_MEMROM2 kSizeOfServiceTable;
V_MEMROM0 extern V_MEMROM1 vuintx V_MEMROM2 kSizeOfMainHandlerTable;

#if defined( FBL_DIAG_ENABLE_DYNAMIC_P2_HANDLING )
V_MEMRAM0 extern V_MEMRAM1 vuint16 V_MEMRAM2 fblDiagTimeP2Max;
#endif

#if defined( FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING )
vuint8 FblDiagSegmentNext(void);
#endif

#if defined( FBL_DIAG_ENABLE_CORE_GETBLOCKFROMADDR )

# define FblGetBlockNrFromAddress(blockAddress, blockLength, pLogicalBlock)   \
   FblLbtGetBlockDescriptorByAddressLength(blockAddress, blockLength, pLogicalBlock)
#endif
#if defined( FBL_DIAG_ENABLE_CORE_GETBLOCKFROMID )
# define FblGetBlockNrFromIndex(blockIndex, pLogicalBlockNr)   \
   FblLbtGetBlockNrByIndex(blockIndex, pLogicalBlockNr)
tFblResult FblGetNrFromBlockTable(V_MEMROM1 tBlockDescriptor V_MEMROM2 V_MEMROM3 * pBlockTable, vuint8 noOfBlocks,
   tFblLbtBlockIndex blockIndex, vuint8 * pLogicalBlockNr);
#endif

void FblDiagEcuReset( void );
#if defined( FBL_DIAG_ENABLE_OEM_INITPOWERON )
void FblDiagOemInitPowerOn(void);
#endif
#if defined( FBL_DIAG_ENABLE_OEM_INIT )
void FblDiagOemInit(void);
#endif
#if defined( FBL_DIAG_ENABLE_OEM_POSTINIT )
void FblDiagOemPostInit(void);
#endif
#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )
# if defined( FBL_DIAG_ENABLE_OEM_SDS_RESPONSE )
void FblDiagOemPrepareSdsResponse(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pDiagBuffer, V_MEMRAM1 tCwDataLengthType V_MEMRAM2 V_MEMRAM3 *pDiagDataLength);
# endif
# if defined( FBL_DIAG_ENABLE_OEM_RR_RESPONSE )
void FblDiagOemPrepareRrResponse(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pDiagBuffer, V_MEMRAM1 tCwDataLengthType V_MEMRAM2 V_MEMRAM3 *pDiagDataLength);
# endif
#endif
#if defined( FBL_DIAG_ENABLE_OEM_SPS_REQUEST )
void FblDiagOemPrepareSpsRequest(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pDiagBuffer, V_MEMRAM1 tCwDataLengthType V_MEMRAM2 V_MEMRAM3 *pDiagDataLength);
#endif
#if defined( FBL_DIAG_ENABLE_OEM_DEINIT )
void FblDiagOemDeinit(void);
#endif
#if defined( FBL_DIAG_ENABLE_OEM_STATETASK )
void FblDiagOemStateTask(void);
#endif
#if defined( FBL_DIAG_ENABLE_OEM_TIMERTASK )
void FblDiagOemTimerTask(void);
#endif

#if defined( FBL_DIAG_ENABLE_OEM_SESSION_TIMEOUT )
void FblDiagSessionTimeout(void);
#endif

#if defined( FBL_DIAG_ENABLE_SERVICE_POSTHANDLER )

# define FBLDIAG_RAMCODE_START_SEC_CODE
# include "MemMap.hpp"
extern void FblDiagDefaultPostHandler( vuint8 postParam );

#if defined( FBL_CW_ENABLE_DECLINED_REQUESTS )
extern void FblDiagOem_ProcessDeclineRequest(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pDiagBuffer, V_MEMRAM1 tCwDataLengthType V_MEMRAM2 V_MEMRAM3 *pDiagDataLength);
#endif

# define FBLDIAG_RAMCODE_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

#endif

