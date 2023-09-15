

#ifndef __FBL_CW_H__
#define __FBL_CW_H__

#define FBLWRAPPERCOM_PDUR_VERSION           0x0506u
#define FBLWRAPPERCOM_PDUR_RELEASE_VERSION   0x01u

#include "Types_SwcServiceCom.hpp"
#include "SwcApplDcm.hpp"
#include "FblCw_Cfg.hpp"
#include "FblCw_Lcfg.hpp"

#define FBLCW_VENDOR_ID              30U
#define FBLCW_MODULE_ID              255U

#define FBLCW_AR_RELEASE_MAJOR_VERSION       4U
#define FBLCW_AR_RELEASE_MINOR_VERSION       0U
#define FBLCW_AR_RELEASE_REVISION_VERSION    3U

#define FBLCW_E_NO_ERROR                    0U
#define FBLCW_E_PARAM                       1U
#define FBLCW_E_UNINIT                      2U
#define FBLCW_E_PARAM_POINTER               3U
#define FBLCW_E_INIT_FAILED                 4U

#define FBLCW_APIID_INIT                      0U
#define FBLCW_APIID_STARTOFRECEPTION          1U
#define FBLCW_APIID_COPYRXDATA                2U
#define FBLCW_APIID_COPYTXDATA                3U
#define FBLCW_APIID_TPRXINDICATION            4U
#define FBLCW_APIID_TPTXCONFIRMATION          5U

#define FBL_CW_API_REFERENCE_VERSION_MAJOR      0x02u

#define FBL_CW_API_REFERENCE_VERSION_MINOR      0x00u

#define FBL_CW_API_REFERENCE_VERSION_RELEASE    0x00u

#if defined( kFblCwTxPendingTimeout )
#else

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
#define kFblCwTxPendingTimeout           (5000u / FBL_REPEAT_CALL_CYCLE)
#else
#define kFblCwTxPendingTimeout           (100u / FBL_REPEAT_CALL_CYCLE)
#endif
#endif
#if defined( kFblCwMaxWaitTime )
#else

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
#define kFblCwMaxWaitTime                (1000u / FBL_REPEAT_CALL_CYCLE)
#else
#define kFblCwMaxWaitTime                (10u / FBL_REPEAT_CALL_CYCLE)
#endif
#endif

#if defined( kFblCwTxModeSwitchTimeout )
#else

#define kFblCwTxModeSwitchTimeout        (100u / FBL_REPEAT_CALL_CYCLE)
#endif

#if defined (kFblCwShutdownWaitTime)
#else
#define kFblCwShutdownWaitTime           (4500u / FBL_REPEAT_CALL_CYCLE)
#endif

#define FblCwIsTimerTaskAllowed()        0x01u
#define FblCwIsStateTaskAllowed()        0x01u

#define FBL_CW_LOCKS_TASKS

#define FBLCW_LOCKS_TASKS

#define kFblCwResetEcuRegularCase         0x00u

#define kFblCwResetEcuTesterTimeout       0x01u

#define FblCwSetOfflineMode()
#define FblCwSetOnlineMode()

#define FblCwTransmit(data, length, type) FblCwPduTransmit((data), (length))

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

#define FblCwShutdownRequest(a)           FblCwPduShutdownRequest()
#else

#define FblCwShutdownRequest(a)          FblSetShutdownRequest()
#endif

#define kFblCwTxCallPosResponse           0x00u
#define kFblCwTxCallNegResponse           0x01u
#define kFblCwTxCallFailedResponse        0x02u
#define kFblCwTxCallRcrRp                 0x03u
#define kFblCwTxCallNoResponse            0x04u

#define kFblCwMsgTypeNormal               0x00u
#define kFblCwMsgTypeRcrRp                0x03u

#define kFblCwRcrRpMsgLength              0x03u

#if defined( FBL_ENABLE_STAY_IN_BOOT )

#define kFblCwCheckForStartMsg           FBL_BIT0

#define kFblCwStartMsgReceived           FBL_BIT1

#define FblCwGetCheckForStartMsg()       ((fblCwStateStartMsg & kFblCwCheckForStartMsg) == kFblCwCheckForStartMsg)

#define FblCwSetCheckForStartMsg()       (fblCwStateStartMsg |= kFblCwCheckForStartMsg)

#define FblCwClrCheckForStartMsg()       (fblCwStateStartMsg &= FblInvert8Bit(kFblCwCheckForStartMsg))

#define FblCwGetStartMsgReceived()       ((fblCwStateStartMsg & kFblCwStartMsgReceived) == kFblCwStartMsgReceived)

#define FblCwSetStartMsgReceived()       (fblCwStateStartMsg |= kFblCwStartMsgReceived)

#define FblCwClrStartMsgReceived()       (fblCwStateStartMsg &= FblInvert8Bit(kFblCwStartMsgReceived))
#endif

#define FblCwDiscardReception()
#define FblCwSetTxInit()
#define FblCwSetRxBlock()

#if( FBLCW_MODULE_FRSM == STD_ON )

#define FblCwGetWakeUpEvent()           (0x01u == cwWakeUpFlag)
#define FblCwSetWakeUpEvent()           (cwWakeUpFlag = 0x01u)
#define FblCwClrWakeUpEvent()           (cwWakeUpFlag = 0x00u)
#endif

#if( FBLCW_MODULE_COMM == STD_OFF )

#define Dcm_ComM_FullComModeEntered(a)
#define Dcm_ComM_SilentComModeEntered(a)
#define Dcm_ComM_NoComModeEntered(a)
#endif

#if(FBLCW_CHANGE_PARAMETER == STD_OFF)
#define FblCw_ResetParameter() kFblOk
#endif

#if(FblCw_GetSizeOfDcmDslConnectionInfo() > 1u)

#define FBL_CW_ENABLE_MULTIPLE_CONNECTIONS
#endif

#if(FBLCW_DECLINED_REQUESTS == STD_ON)
#define kFblCwNumberOfRequests (kFblCwMaxNumDeclinedRequests + 1u)
#define FBL_CW_ENABLE_DECLINED_REQUESTS
#else
#define kFblCwNumberOfRequests 1u
#endif
#define FBL_CW_MAIN_REQUEST_INDEX 0u

#if( FBLCW_KEY_SLOT_MODE == STD_ON )

#define FBL_CW_KEY_SLOT_MODE       0u
#define FBL_CW_ALL_SLOT_MODE       1u

#define FBL_CW_NW_STATUS_NORMAL    0x0001u
#define FBL_CW_NW_STATUS_BOOT      0x1000u
#define FBL_CW_NW_STATUS_UNDEFINED 0x2000u
#endif

#if( FBLCW_KEY_SLOT_MODE == STD_ON )
#if( FBLCW_USE_INIT_POINTER == STD_ON)
#error "FBLCW_KEY_SLOT_MODE is not supported if FBLCW_USE_INIT_POINTER is used!"
#endif
#if !defined (FBLCW_NW_STATUS_PDU)
#error "Define the FBLCW_NW_STATUS_PDU in the user config file! At this point the handle ID of the FrIfLPdu of the first slot shall be configured."
#endif
#endif

#if defined ( FRNM_NUMBER_OF_FRNM_CHANNELS )
#if( FRNM_NUMBER_OF_FRNM_CHANNELS > 1u )
#error "Multiple FrNm channels are currently not supported"
#endif
#endif

typedef uint16 FblCw_RxTesterSourceAddressOfDcmDslConnectionInfo16BitType;

typedef PduLengthType tCwDataLengthType;
typedef tCwDataLengthType tTpDataType;

#if( FBLCW_EXISTS_FR_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
#if( FBLCW_KEY_SLOT_MODE == STD_ON)
typedef vuint16 tCwNwStatus;
#endif
#endif

#define FBLCW_START_SEC_CODE
#include "MemMap.hpp"

FUNC(void, FBLCW_CODE) FblCw_InitMemory(void);

FUNC(void, FBLCW_CODE) FblCw_Init(P2CONST(FblCw_ConfigType, AUTOMATIC, FBLCW_INIT_DATA) config);

FUNC(void, FBLCW_CODE) FblCw_Deinit(void);

void FblCwIdleTask(void);

void FblCwTimerTask(void);

void FblCwStateTask(void);

void FblCwPduTransmit(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * data, tCwDataLengthType length);

#if(FBLCW_DECLINED_REQUESTS == STD_ON)

void FblCwPduTransmitDeclinedRequest(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * data, tCwDataLengthType length, vuint8 connectionIndex);
#endif

void FblCwTransmitRP(const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * data);

void FblCwRetransmitRP(void);

#if defined( FBL_ENABLE_STAY_IN_BOOT )

tFblResult FblCwCheckStartMessage(void);
#endif

void FblCwTxSetTargetAddress(FblCw_DcmDslConnectionInfoIterType targetAddress);

FblCw_DcmDslConnectionInfoIterType FblCwGetResponseAddress(void);

void FblCwResetResponseAddress(void);

tFblResult FblCwPrepareResponseAddress(void);

tFblResult FblCwSaveResponseAddress(void);

#if( FBLCW_BAUDRATE_SWITCH == STD_ON )

tFblResult FblCwCheckBaudrate(vuint32 baudrate);

tFblResult FblCwSwitchBaudrate(vuint32 baudrate);
#endif

void FblCwResetRxBlock(void);

tCwDataLengthType FblCwGetPayloadLimit(void);

#if(FBLCW_CHANGE_PARAMETER == STD_ON)

FUNC(tFblResult, FBLCW_CODE) FblCw_ChangeParameter(TPParameterType parameter, uint16 value);

FUNC(tFblResult, FBLCW_CODE) FblCw_ResetParameter(void);

FUNC(tFblResult, FBLCW_CODE) FblCw_ReadParameter(TPParameterType parameter, uint16 * value);
#endif

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

void FblCwPduShutdownRequest(void);
#endif

#if( FBLCW_MODULE_COMM == STD_ON )

FUNC(void, FBLCW_CODE) Dcm_ComM_NoComModeEntered(NetworkHandleType channel);

FUNC(void, FBLCW_CODE) Dcm_ComM_SilentComModeEntered(NetworkHandleType channel);

FUNC(void, FBLCW_CODE) Dcm_ComM_FullComModeEntered(NetworkHandleType channel);
#endif

#define FBLCW_STOP_SEC_CODE
#include "MemMap.hpp"

#if(FBLCW_USE_INIT_POINTER == STD_ON)
#define FBLCW_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.hpp"

extern P2CONST(FblCw_ConfigType, FBLCW_VAR_ZERO_INIT, FBLCW_PBCFG) FblCw_ConfigDataPtr;

#define FBLCW_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.hpp"
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 fblCwStateStartMsg;
#endif

#endif

