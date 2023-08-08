#ifndef FBL_DIAG_H
#define FBL_DIAG_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "fbl_diag_oem.hpp"
#include "version.hpp"

#define FBLDIAG_14229_CORE_VERSION           0x0402u
#define FBLDIAG_14229_CORE_RELEASE_VERSION   0x00u

#if !defined( kDiagCallCycle )
# define kDiagCallCycle    1u
#endif

#define FBL_DIAG_SEGMENT_SIZE                   FBL_MAX_SEGMENT_SIZE

#define GET_ID_HIGH(id)                         ((vuint8)(((id) >> 8u) & 0xFFu))
#define GET_ID_LOW(id)                          ((vuint8)((id) & 0xFFu))

#if defined( FBL_CW_ENABLE_DECLINED_REQUESTS )
# if !defined( FBL_DIAG_DECLINE_BUFFER_LENGTH )
#  define FBL_DIAG_DECLINE_BUFFER_LENGTH     8u
# endif
#endif

#define kFblDiagStateSessionDefault             0u
#define kFblDiagStateSessionExtended            1u
#define kFblDiagStateSessionProgramming         2u
#define kFblDiagStateFunctionalRequest          3u
#define kFblDiagStateDiagBufferLocked           4u
#define kFblDiagStateExecutePostHandler         5u
#define kFblDiagStateServiceInProgress          6u
#define kFblDiagStateRcrRpAllowed               7u
#define kFblDiagStateRcrRpInProgress            8u
#define kFblDiagStateSuppressPosRspMsg          9u
#define kFblDiagStateServiceHasSubfunction      10u
#define kFblDiagStateResponseProcessing         11u
#define kFblDiagStateTransferTypeFlash          12u

#define kFblDiagStateWaitEcuReset               13u
#define kFblDiagStateEcuResetFctFinished        14u
#define kFblDiagStateResetMsgConfirmed          15u

#define kFblDiagStatePreconditionsChecked       16u
#define kFblDiagStateMemDriverInitialized       17u

#define kFblDiagLastCoreStateIdx                kFblDiagStateMemDriverInitialized

#define kFblDiagNumberOfStates                  ( kFblDiagLastOemStateIdx + 1u )
#define kFblDiagNumberOfDispatchStates          kFblDiagNumberOfStates

#define FblDiagGetDefaultSession()              GetFblDiagState( kFblDiagStateSessionDefault )
#define FblDiagGetProgrammingSession()          GetFblDiagState( kFblDiagStateSessionProgramming )
#define FblDiagGetExtendedSession()             GetFblDiagState( kFblDiagStateSessionExtended )
#define FblDiagGetBufferLocked()                GetFblDiagState( kFblDiagStateDiagBufferLocked )
#define FblDiagGetExecutePostHandler()          GetFblDiagState( kFblDiagStateExecutePostHandler )
#define FblDiagGetRcrRpAllowed()                GetFblDiagState( kFblDiagStateRcrRpAllowed )
#define FblDiagGetRcrRpInProgress()             GetFblDiagState( kFblDiagStateRcrRpInProgress )
#define FblDiagGetResponseProcessing()          GetFblDiagState( kFblDiagStateResponseProcessing )
#define FblDiagGetSuppressPosRspMsg()           GetFblDiagState( kFblDiagStateSuppressPosRspMsg )
#define FblDiagGetServiceHasSubfunction()       GetFblDiagState( kFblDiagStateServiceHasSubfunction )
#define FblDiagGetServiceInProgress()           GetFblDiagState( kFblDiagStateServiceInProgress )
#define FblDiagGetFunctionalRequest()           GetFblDiagState( kFblDiagStateFunctionalRequest )
#define FblDiagGetTransferTypeFlash()           GetFblDiagState( kFblDiagStateTransferTypeFlash )

#define FblDiagGetWaitEcuReset()                GetFblDiagState( kFblDiagStateWaitEcuReset )
#define FblDiagGetEcuResetFctFinished()         GetFblDiagState( kFblDiagStateEcuResetFctFinished )
#define FblDiagGetResetMsgConfirmed()           GetFblDiagState( kFblDiagStateResetMsgConfirmed )

#define FblDiagGetPreconditionsChecked()        GetFblDiagState( kFblDiagStatePreconditionsChecked )
#define FblDiagGetMemDriverInitialized()        GetFblDiagState( kFblDiagStateMemDriverInitialized )

#define GetDiagDefaultSession()                 FblDiagGetDefaultSession()
#define GetDiagProgrammingSession()             FblDiagGetProgrammingSession()
#define GetDiagExtendedSession()                FblDiagGetExtendedSession()
#define GetDiagBufferLocked()                   FblDiagGetBufferLocked()
#define GetRcrRpInProgress()                    FblDiagGetRcrRpInProgress()
#define GetMemDriverInitialized()               FblDiagGetMemDriverInitialized()

#define FBL_DIAG_STATECHECK_ARRAYSIZE        (((kFblDiagNumberOfDispatchStates - 1u) / FBL_STATE_BITS) + 1u)

#define GetFblDiagState(state)               FBL_STATE_TEST(fblDiagStates, (state))

#define FBL_DIAG_STATE_CHECK_COUNT  0u
#define FBL_DIAG_STATE_ADDCLR_COUNT 0u
#define FBL_DIAG_STATE_COUNT        (FBL_DIAG_STATE_CHECK_COUNT + FBL_DIAG_STATE_ADDCLR_COUNT)

#define FBL_DIAG_STATE_ARRAYENTRY(mask, idx)    ((tFblStateBitmap)(((mask) >> ((idx) * FBL_STATE_BITS)) & kFblDiagStateMaskAll))
#if(FBL_DIAG_STATECHECK_ARRAYSIZE == 1u)
# define FBL_STATE_BUILDARRAYENTRIES(mask)      FBL_STATE_ARRAYENTRY(mask, 0u)
#endif
#if(FBL_DIAG_STATECHECK_ARRAYSIZE == 2u)
# define FBL_STATE_BUILDARRAYENTRIES(mask)      FBL_STATE_ARRAYENTRY(mask, 0u), FBL_STATE_ARRAYENTRY(mask, 1u)
#endif
#if(FBL_DIAG_STATECHECK_ARRAYSIZE == 3u)
# define FBL_STATE_BUILDARRAYENTRIES(mask)      FBL_STATE_ARRAYENTRY(mask, 0u), FBL_STATE_ARRAYENTRY(mask, 1u), FBL_STATE_ARRAYENTRY(mask, 2u)
#endif
#if(FBL_DIAG_STATECHECK_ARRAYSIZE == 4u)
# define STATE_BUILDARRAYENTRIES(mask)          FBL_STATE_ARRAYENTRY(mask, 0u), FBL_STATE_ARRAYENTRY(mask, 1u), FBL_STATE_ARRAYENTRY(mask, 2u), FBL_STATE_ARRAYENTRY(mask, 3u)
#endif
#if(FBL_DIAG_STATECHECK_ARRAYSIZE > 4u)
# error "Invalid array size for state check!"
#endif

#define DIAG_STATE_BUILDARRAY(mask)             { DIAG_STATE_BUILDARRAYENTRIES(mask) }

#define kFblDiagStateMaskAllLong                FBL_STATE_MULTIMASKLONG(0u, ((FBL_DIAG_STATECHECK_ARRAYSIZE * FBL_STATE_BITS) - 1u))

#define kFblDiagStateMask(state)                FBL_STATE_MASKLONG(state)

#define SetFblDiagState(state)                  FBL_STATE_SET(fblDiagStates, state)
#define ClrFblDiagState(state)                  FBL_STATE_CLR(fblDiagStates, state)

#define kDiagSidDiagnosticSessionControl                 0x10u
#define kDiagSidEcuReset                                 0x11u
#define kDiagSidClearDiagInfo                            0x14u
#define kDiagSidReadDTCInformation                       0x19u
#define kDiagSidReadDataByIdentifier                     0x22u
#define kDiagSidSecurityAccess                           0x27u
#define kDiagSidCommunicationControl                     0x28u
#define kDiagSidWriteDataByIdentifier                    0x2Eu
#define kDiagSidRoutineControl                           0x31u
#define kDiagSidRequestDownload                          0x34u
#define kDiagSidTransferData                             0x36u
#define kDiagSidRequestTransferExit                      0x37u
#define kDiagSidTesterPresent                            0x3Eu
#define kDiagSidControlDTCSetting                        0x85u
#define kDiagSidLinkControl                              0x87u

#define kDiagRidNegativeResponse                         0x7Fu

#define kDiagSuppressPosRspMsgIndicationBit              0x80u

#define kDiagSubDefaultSession                           0x01u
#define kDiagSubProgrammingSession                       0x02u
#define kDiagSubExtendedDiagSession                      0x03u

#ifdef SMART_TESTER_JUMP_IN
#define kDiagSubSUPPLIER1DiagSession                        0x60u
#endif

#define kDiagSubTesterPresent                            0x00u

#define kDiagSubHardReset                                0x01u
#define kDiagSubKeyOffOnReset                            0x02u
#define kDiagSubSoftReset                                0x03u
#define kDiagOemSpecBlJump                               0x4Cu

#define kDiagSubReportDTCByStatusMask                    0x02u

#define kDiagSubEnableRxAndTx                            0x00u
#define kDiagSubEnableRxAndDisableTx                     0x01u
#define kDiagSubDisableRxAndTx                           0x03u
#define kDiagSubNormalCommunication                      0x01u
#define kDiagSubNmCommunication                          0x02u
#define kDiagSubNmAndNormalCommunication                 0x03u

#define kDiagSubStartRoutine                             0x01u
#define kDiagSubStopRoutine                              0x02u
#define kDiagSubRequestRoutineResults                    0x03u

#define kDiagErrorNone                                   0x00u
#define kDiagNrcGeneralReject                            0x10u
#define kDiagNrcServiceNotSupported                      0x11u
#define kDiagNrcSubFunctionNotSupported                  0x12u
#define kDiagNrcIncorrectMessageLengthOrInvalidFormat    0x13u
#define kDiagNrcResponseTooLong                          0x14u
#define kDiagNrcBusyRepeatRequest                        0x21u
#define kDiagNrcConditionsNotCorrect                     0x22u
#define kDiagNrcRequestSequenceError                     0x24u
#define kDiagNrcRequestOutOfRange                        0x31u
#define kDiagNrcSecurityAccessDenied                     0x33u
#define kDiagNrcInvalidKey                               0x35u
#define kDiagNrcExceedNumberOfAttempts                   0x36u
#define kDiagNrcRequiredTimeDelayNotExpired              0x37u
#define kDiagNrcUploadDownloadNotAccepted                0x70u
#define kDiagNrcTransferDataSuspended                    0x71u
#define kDiagNrcGeneralProgrammingFailure                0x72u
#define kDiagNrcWrongBlockSequenceCounter                0x73u
#define kDiagNrcIllegalByteCountInBlockTransfer          0x75u
#define kDiagNrcRcrResponsePending                       0x78u
#define kDiagNrcSubfunctionNotSupportedInActiveSession   0x7Eu
#define kDiagNrcServiceNotSupportedInActiveSession       0x7Fu
#define kDiagNrcVoltageTooHigh                           0x92u
#define kDiagNrcVoltageTooLow                            0x93u

#define DiagNRCGeneralReject()                           FblDiagSetError(kDiagNrcGeneralReject)
#define DiagNRCServiceNotSupported()                     FblDiagSetError(kDiagNrcServiceNotSupported)
#define DiagNRCSubFunctionNotSupported()                 FblDiagSetError(kDiagNrcSubFunctionNotSupported)
#define DiagNRCIncorrectMessageLengthOrInvalidFormat()   FblDiagSetError(kDiagNrcIncorrectMessageLengthOrInvalidFormat)
#define DiagNRCResponseTooLong()                         FblDiagSetError(kDiagNrcResponseTooLong)
#define DiagNRCBusyRepeatRequest()                       FblDiagSetError(kDiagNrcBusyRepeatRequest)
#define DiagNRCConditionsNotCorrect()                    FblDiagSetError(kDiagNrcConditionsNotCorrect)
#define DiagNRCRequestSequenceError()                    FblDiagSetError(kDiagNrcRequestSequenceError)
#define DiagNRCRequestOutOfRange()                       FblDiagSetError(kDiagNrcRequestOutOfRange)
#define DiagNRCSecurityAccessDenied()                    FblDiagSetError(kDiagNrcSecurityAccessDenied)
#define DiagNRCInvalidKey()                              FblDiagSetError(kDiagNrcInvalidKey)
#define DiagNRCExceedNumberOfAttempts()                  FblDiagSetError(kDiagNrcExceedNumberOfAttempts)
#define DiagNRCRequiredTimeDelayNotExpired()             FblDiagSetError(kDiagNrcRequiredTimeDelayNotExpired)
#define DiagNRCUploadDownloadNotAccepted()               FblDiagSetError(kDiagNrcUploadDownloadNotAccepted)
#define DiagNRCTransferDataSuspended()                   FblDiagSetError(kDiagNrcTransferDataSuspended)
#define DiagNRCGeneralProgrammingFailure()               FblDiagSetError(kDiagNrcGeneralProgrammingFailure)
#define DiagNRCWrongBlockSequenceCounter()               FblDiagSetError(kDiagNrcWrongBlockSequenceCounter)
#define DiagNRCIllegalByteCountInBlockTransfer()         FblDiagSetError(kDiagNrcIllegalByteCountInBlockTransfer)
#define DiagNRCRcrResponsePending()                      FblDiagSetError(kDiagNrcRcrResponsePending)
#define DiagNRCSubfunctionNotSupportedInActiveSession()  FblDiagSetError(kDiagNrcSubfunctionNotSupportedInActiveSession)
#define DiagNRCServiceNotSupportedInActiveSession()      FblDiagSetError(kDiagNrcServiceNotSupportedInActiveSession)
#define DiagNRCVoltageTooHigh()                          FblDiagSetError(kDiagNrcVoltageTooHigh)
#define DiagNRCVoltageTooLow()                           FblDiagSetError(kDiagNrcVoltageTooLow)

#define DiagPutResponseSId(a)    (DiagBuffer[0] = (a))
#define DiagGetRequestSId()      (DiagBuffer[0])

#define kDiagSubNoEncryption              0x00u
#define kDiagSubNoCompression             0x00u
#define kDiagSubNoDataProcessing          ((kDiagSubNoCompression << 4u) | kDiagSubNoEncryption)

#define kDiagFmtEncryptionMask            0x0Fu
#define kDiagFmtCompressionMask           0xF0u

#define FblDiagGetCompressionMode(m)      (((m) & kDiagFmtCompressionMask) >> 4u)
#define FblDiagGetEncryptionMode(m)       ((m) & kDiagFmtEncryptionMask)

#define kDiagResetPutResponse                0x00u
#define kDiagResetNoResponse                 0x01u

#define kNotForceSendResponsePending         0x00u
#define kForceSendResponsePending            0x01u
#define kForceSendRpIfNotInProgress          0x02u

#if !defined( kDiagInitDataRetries )
# define kDiagInitDataRetries                0x03u
#endif

#define FblReadRam                           FblReadBlock

#if !defined( TESTER_PRESENT_TIMEOUT )

# define TESTER_PRESENT_TIMEOUT                 5000u
#endif

#define TimeoutTesterValue()                    testerPresentTimeout
#define DecTimeoutTesterValue()                 ( testerPresentTimeout-- )
#define ResetTesterTimeout()                    ( testerPresentTimeout = (vuint16)( TESTER_PRESENT_TIMEOUT / kDiagCallCycle ))
#define StopTesterTimeout()                     ( testerPresentTimeout = 0u )

#if defined( FBL_ENABLE_SLEEPMODE )

# define kFblSleepDelayTime                     ((vuint32)( FBL_SLEEP_TIME / FBL_REPEAT_CALL_CYCLE ))
# define FblSleepCounterClear()                 ( sleepCounter = 0x00u )
# define FblSleepCounterReload()                ( sleepCounter = kFblSleepDelayTime )
# define FblDecSleepCounter()                   ( sleepCounter-- )
# define FblGetSleepCounter()                   ((vuint32) sleepCounter )
#endif

typedef tFblResult (*tFblDiagLengthCheck )( vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen );
typedef tFblResult (*tFblDiagPreHandler )( vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen );
typedef tFblResult (*tFblDiagMainHandler)( vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen );
typedef tFblResult (*tFblDiagNrcHandler)( vuint32 serviceErrorMask );
typedef void       (*tFblDiagPostHandler)( vuint8 postParam );

typedef tFblAddress  tFblDiagAddr;
typedef vuint8       tFblDiagNrc;

void        FblDiagInitPowerOn( void );
void        FblDiagInit( void );
void        FblDiagPostInit( void );

void        FblDiagSetError( vuint8 errorCode );
void        DiagProcessingDone( tCwDataLengthType dataLength );

vuint8      FblRealTimeSupport( void );
void        DiagExRCRResponsePending( vuint8 forceSend );

void        FblDiagTimerTask( void );
void        FblDiagStateTask( void );

void        FblDiagInitStartFromAppl( void );
#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )
void        FblDiagInitStartFromReset( vuint8 resetRequestType );
#endif

V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * FblDiagMemGetActiveBuffer(void);

tFblResult  FblDiagMemPreWrite( void );
tFblResult  FblDiagMemPostWrite( void );

#define FBLDIAG_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"

#if defined( FBL_ENABLE_STAY_IN_BOOT )
vuint8      FblDiagCheckStartMsg( const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *pData, vuintx length);
#endif
void        FblDiagRxStartIndication( void );
void        FblDiagRxIndication( vuint8* pbDiagBuffer, tCwDataLengthType rxDataLength );
vuint8*     FblDiagRxGetPhysBuffer( tCwDataLengthType rxDataLength );
vuint8*     FblDiagRxGetFuncBuffer( tCwDataLengthType rxDataLength );
void        FblDiagTxConfirmation( vuint8 cwMsgType );
void        FblDiagTxErrorIndication( vuint8 cwMsgType );
void        FblDiagRxErrorIndication( void );

#if defined( FBL_CW_ENABLE_DECLINED_REQUESTS )
void        FblDiagRxDeclineIndication(vuint8* pbDiagBuffer, tCwDataLengthType rxDataLength, vuint8 connectionIndex);
vuint8*     FblDiagRxGetDeclineBuffer(tCwDataLengthType rxDataLength, vuint8 connectionIndex);
void        FblDiagDeclineErrorIndication(vuint8 connectionIndex);
void        FblDiagDeclineTxConfirmation(vuint8 connectionIndex);
#endif

#define FBLDIAG_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

V_MEMRAM0 extern V_MEMRAM1       vuint8            V_MEMRAM2 V_MEMRAM3 * V_MEMRAM1 V_MEMRAM2 DiagBuffer;
V_MEMRAM0 extern V_MEMRAM1_NEAR  tCwDataLengthType V_MEMRAM2_NEAR DiagDataLength;
V_MEMRAM0 extern V_MEMRAM1_NEAR  vuint16           V_MEMRAM2_NEAR testerPresentTimeout;
V_MEMRAM0 extern V_MEMRAM1_NEAR  vuint8            V_MEMRAM2_NEAR diagServiceCurrent;
V_MEMRAM0 extern V_MEMRAM1_NEAR  tFblStateBitmap   V_MEMRAM2_NEAR fblDiagStates[FBL_STATE_INDEX(kFblDiagNumberOfStates - 1u) + 1u];

#if defined( FBL_ENABLE_SLEEPMODE )
V_MEMRAM0 extern V_MEMRAM1       vuint32           V_MEMRAM2      sleepCounter;
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )

V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 fblDiagStayInBootMsg[];
V_MEMROM0 extern V_MEMROM1 vuintx V_MEMROM2 kSizeOfStayInBootMsg;
#endif

#if !(defined(FBL_ENABLE_SYSTEM_CHECK) || defined(FBL_DISABLE_SYSTEM_CHECK))
# error "Error in fbl_cfg.h: Usage of system check not defined"
#endif

#if !(defined(FBL_ENABLE_DEBUG_STATUS) || defined(FBL_DISABLE_DEBUG_STATUS))
# error "Error in fbl_cfg.h: Usage of debug support not defined"
#endif

#if !(defined(FBL_ENABLE_APPL_TASK) || defined(FBL_DISABLE_APPL_TASK))
# error "Error in fbl_cfg.h: Usage of application task function not defined"
#endif

#if !(defined(FBL_ENABLE_USERSUBFUNCTION) || defined(FBL_DISABLE_USERSUBFUNCTION))
# error "Error in fbl_cfg.h: Usage of diag user-subfunction call not defined"
#endif

#if !(defined(FBL_ENABLE_DATA_PROCESSING) || defined(FBL_DISABLE_DATA_PROCESSING))
# error "Error in fbl_cfg.h: Usage of data processing interface not defined"
#endif

#if !(defined(FBL_WATCHDOG_ON) || defined(FBL_WATCHDOG_OFF))
# error "Error in fbl_cfg.h: Usage of watchdog support not defined"
#endif

#if defined( FBL_WATCHDOG_ON) && !defined(FBL_WATCHDOG_TIME )
# error "Error in fbl_cfg.h: Watchdog trigger period not defined"
#endif

#if !(defined(FBL_ENABLE_FBL_START) || defined(FBL_DISABLE_FBL_START))
# error "Error in fbl_cfg.h: Usage of FblStart function not defined"
#endif

#if defined ( FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING )
# if !defined(SWM_DATA_MAX_NOAR)
#  error "Error in fbl_cfg.h: Number of supported download segments (SWM_DATA_MAX_NOAR) not defined"
# endif
#endif

#if !defined(FBL_HEADER_ADDRESS)
# error "Error in fbl_cfg.h: Start address of bootblock header not defined"
#endif

#if !defined(FBL_DIAG_BUFFER_LENGTH)
# error "Error in fbl_cfg.h: FBL_DIAG_BUFFER_LENGTH not defined"
#endif

#if( FBL_DIAG_BUFFER_LENGTH < (FBL_MAX_SEGMENT_SIZE+2) )
# error "Error in fbl_cfg.: DiagBuffer size too small - modify FBL_DIAG_BUFFER_LENGTH"
#endif

#if defined( SEC_SECURITY_CLASS )
# if( SEC_SECURITY_CLASS == SEC_CLASS_C ) || ( SEC_SECURITY_CLASS == SEC_CLASS_CCC )
#  if( FBL_DIAG_BUFFER_LENGTH < (kSecSigLength+4) )
#   error "Error in fbl_cfg.h: DiagBuffer size too small - modify FBL_DIAG_BUFFER_LENGTH"
#  endif
# endif
#endif

#if !defined( FBL_DIAG_ENABLE_CORE_READ_SECACCESSDELAY_FLAG ) && \
    !defined( FBL_DIAG_DISABLE_CORE_READ_SECACCESSDELAY_FLAG )
# error "OEM diagnostic module has to configure this setting"
#endif
#if !defined( FBL_DIAG_ENABLE_CORE_WRITE_SECACCESSDELAY_FLAG ) && \
    !defined( FBL_DIAG_DISABLE_CORE_WRITE_SECACCESSDELAY_FLAG )
# error "OEM diagnostic module has to configure this setting"
#endif

#if !defined(FBL_DIAG_TIME_P3MAX)
# error "Error in fbl_cfg.h: P2Star time not defined"
#endif

#if !defined(FLASH_SIZE)
# error "Error in fbl_cfg.h: Size of flash code buffer not defined"
#endif

#ifdef __cplusplus
}
#endif
#endif
