#define FBLCW_SOURCE

#include "FblCw_Cfg.hpp"
#include "FblCw_Lcfg.hpp"
#include "FblCw_PBcfg.hpp"
#include "Types_SwcServiceCom.hpp"
#include "fbl_inc.hpp"

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON)

#include "infEcuabCanIfEcuabCanTrcv.hpp"
#include FBLCW_CANDRV_HEADER_NAME
#include "EcuabCanIf.hpp"
#include "SwcServiceCanTp.hpp"

#include FBLCW_CANSCHM_HEADER_NAME
#include "SchM_CanIf.hpp"
#include "SchM_CanTp.hpp"

#include "CfgEcuabCanIf.hpp"
#include "CanIf_Cdd.hpp"
#endif

#if( FBLCW_MODULE_COMM == STD_ON )
#include "SwcServiceComM.hpp"
#include "ComM_EcuMBswM.hpp"
#endif

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
#if( FBLCW_MODULE_ETHSM == STD_ON )
#include "EthIf.hpp"
#include "EthSM.hpp"
#include "TcpIp.hpp"
#endif
#include "IpBase.hpp"
#include "SoAd.hpp"
#include "DoIP.hpp"
#include "DoIP_Cbk.hpp"
#include "SchM_SoAd.hpp"
#include "SchM_DoIP.hpp"
#include "SchM_TcpIp.hpp"
#endif

#if( FBLCW_MODULE_CANSM == STD_ON )
#include "CanSM_Cbk.hpp"
#include "SchM_CanSM.hpp"
#endif

#if( FBLCW_MODULE_CANNM == STD_ON )
#include "SchM_CanNm.hpp"
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
#include "Fr.hpp"
#include "FrIf.hpp"
#include "FrIf_Priv.hpp"
#include "FrIf_Ext.hpp"
#include "FrSM.hpp"
#include "SchM_FrSM.hpp"
#include "SchM_FrTp.hpp"

#include "BswM_FrSM.hpp"
#endif

#if( FBLCW_MODULE_FRNM == STD_ON )
#include "Nm.hpp"
#include "FrNm.hpp"
#include "SchM_FrNm.hpp"
#endif

#if( FBLCW_MODULE_XCP == STD_ON )
#include "SchM_Xcp.hpp"
#endif

#include "SwcServicePduR.hpp"
#include "infSwcServicePduRSwcServiceDcm.hpp"
#include "SwcApplDcm.hpp"
#include "SwcServiceDet.hpp"
#include "SwcServiceDcm.hpp"

#if( FBLWRAPPERCOM_PDUR_VERSION != 0x0506u ) || ( FBLWRAPPERCOM_PDUR_RELEASE_VERSION != 0x01u )
# error "Error in fbl_cw.c: Source and header file are inconsistent!"
#endif

#if( FBLWRAPPERCOM_PDUR_VERSION != _FBLWRAPPERCOM_PDUR_VERSION ) || ( FBLWRAPPERCOM_PDUR_RELEASE_VERSION != _FBLWRAPPERCOM_PDUR_RELEASE_VERSION )
# error "Error in fbl_cw.c: Source and v_ver.h are inconsistent!"
#endif

#define kFblCwTxStateIdle                    0x00u
#define kFblCwTxStateRpInProgress            0x01u
#define kFblCwTxStateTxInProgress            0x02u
#define kFblCwTxStateRpPending               0x03u
#define kFblCwTxStateTxPending               0x04u
#define kFblCwTxStateTxPendingWaitForConf    0x05u

#define kFblCwTaskRunning              FBL_BIT0
#define kFblCwStateTaskRunning         (kFblCwTaskRunning | FBL_BIT1)
#define kFblCwTimerTaskRunning         (kFblCwTaskRunning | FBL_BIT2)

#define kFblCwNoShutdownRequest        0x00u
#define kFblCwShutdownRequested        0x01u
#define kFblCwShutdownFinished         0x02u

#define SetCwTaskRunning()             (cwTaskState |= kFblCwTaskRunning)
#define ClrCwTaskRunning()             (cwTaskState &= FblInvert8Bit(kFblCwTaskRunning))
#define GetCwTaskRunning()             ((cwTaskState & kFblCwTaskRunning) == kFblCwTaskRunning)
#define IsCwTaskAllowed()              ((cwTaskState & kFblCwTaskRunning) != kFblCwTaskRunning)
#define GetCwTaskState()               (cwTaskState)
#define RestoreCwTaskState(state)      (cwTaskState = (state))

#define SetCwStateTaskRunning()        (cwTaskState |= kFblCwStateTaskRunning)
#define ClrCwStateTaskRunning()        (cwTaskState &= FblInvert8Bit(kFblCwStateTaskRunning))
#define GetCwStateTaskRunning()        ((cwTaskState & kFblCwStateTaskRunning) == kFblCwStateTaskRunning)
#define IsCwStateTaskAllowed()         IsCwTaskAllowed()

#define SetCwTimerTaskRunning()        (cwTaskState |= kFblCwTimerTaskRunning)
#define ClrCwTimerTaskRunning()        (cwTaskState &= FblInvert8Bit(kFblCwTimerTaskRunning))
#define GetCwTimerTaskRunning()        ((cwTaskState & kFblCwTimerTaskRunning) == kFblCwTimerTaskRunning)
#define IsCwTimerTaskAllowed()         IsCwTaskAllowed()

#if( FBLCW_QUEUED_REQUEST == STD_ON )
#define kFblCwMsgInProcess         FBL_BIT0
#define kFblCwMsgQueued            FBL_BIT1
#define kFblCwRxIndPending         FBL_BIT2
#define SetCwMsgInProcess()        (cwQueuedRequestFlags |= kFblCwMsgInProcess)
#define GetCwMsgInProcess()        ((cwQueuedRequestFlags & kFblCwMsgInProcess) == kFblCwMsgInProcess)
#define ClrCwMsgInProcess()        cwQueuedRequestFlags &= FblInvert8Bit(kFblCwMsgInProcess)
#define SetCwMsgQueued()           (cwQueuedRequestFlags |= kFblCwMsgQueued)
#define GetCwMsgQueued()           ((cwQueuedRequestFlags & kFblCwMsgQueued) == kFblCwMsgQueued)
#define ClrCwMsgQueued()           cwQueuedRequestFlags &= FblInvert8Bit(kFblCwMsgQueued)
#define SetCwRxIndPending()        (cwQueuedRequestFlags |= kFblCwRxIndPending)
#define GetCwRxIndPending()        ((cwQueuedRequestFlags & kFblCwRxIndPending) == kFblCwRxIndPending)
#define ClrCwRxIndPending()        cwQueuedRequestFlags &= FblInvert8Bit(kFblCwRxIndPending)

#if defined( FBL_CW_MAX_FPL_START_FRAME )
#else
#if( FBLCW_MODULE_FRSM == STD_ON )
#define FBL_CW_MAX_FPL_START_FRAME       246
#  elif( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
#define FBL_CW_MAX_FPL_START_FRAME       6
#else
#   error "Error in fbl_cw.c: Maximum payload length has to be defined for configured bus type"
#endif
#endif
#endif

#if( FBLCW_KEY_SLOT_MODE == STD_ON )

#define FBL_CW_KEY_SLOT_MODE       0u
#define FBL_CW_ALL_SLOT_MODE       1u

#ifndef FBL_CW_NW_STATUS_NORMAL
#define FBL_CW_NW_STATUS_NORMAL    0x0001u
#endif
#ifndef FBL_CW_NW_STATUS_BOOT
#define FBL_CW_NW_STATUS_BOOT      0x1000u
#endif

#ifndef FBL_CW_NW_STATUS_TIMEOUT
#define FBL_CW_NW_STATUS_TIMEOUT   50u
#endif
#endif

#define FBLCW_CONNECTION_UNASSIGNED   0xFFu

#if(FBLCW_DEV_ERROR_REPORT == STD_ON)

#define FblCw_Det_ReportError(ApiId, ErrorCode)    (void)Det_ReportError(FBLCW_MODULE_ID, 0, (ApiId), (ErrorCode))
#endif

#if( FBLCW_MODULE_COMM == STD_ON )

#if( COMM_ACTIVE_CHANNEL == 1u)

#if !defined( FBLCW_COMM_CHANNEL )
#define FBLCW_COMM_CHANNEL 0u
#endif
#else
#if !defined( FBL_CW_DCM_COMM_MAPPING )
#   error "Please defined Dcm/ComM channel mapping."
#endif
#endif
#endif

#if !defined( FblCw_CheckRxPduAllowedInActiveConnection )

#define FblCw_CheckRxPduAllowedInActiveConnection(pduId, connection)     ((connection) == FblCw_GetDcmDslConnectionInfoIdxOfDcmDslProtocolRxInfo((pduId)))
#endif

#if( FBLCW_DCMDSLCONNECTIONGROUPINFO == STD_OFF ) && \
    ( FBLCW_DCMDSLBROADCASTGROUPINFO == STD_OFF )

#define FblCw_CheckRxPduAllowedInConnection(pduId, connectionIdx)        FblCw_CheckRxPduAllowedInActiveConnection((pduId), activeConnection[(connectionIdx)])
#else

#define FblCw_CheckRxPduAllowedInConnection(pduId, connectionIdx)        (FblCwInternalCheckRxPduAllowedInConnection((pduId), (connectionIdx)) == TRUE)
#endif

#if !defined( FblCw_CheckTxPduAllowedInActiveConnection )

#define FblCw_CheckTxPduAllowedInActiveConnection(pduId, connection)     ((connection) == FblCw_GetDcmDslConnectionInfoIdxOfDcmDslProtocolTxInfo((pduId)))
#endif

#if(FBLCW_USE_INIT_POINTER == STD_ON)
#define FBLCW_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.hpp"

P2CONST(FblCw_ConfigType, FBLCW_VAR_ZERO_INIT, FBLCW_PBCFG) FblCw_ConfigDataPtr = NULL_PTR;

#define FBLCW_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.hpp"
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 fblCwStateStartMsg;
#endif

#if( FBLCW_TASK_CYCLE > 1u )
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cycleCounter;
#endif
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cwTxState;
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 cwTxTimer;
V_MEMRAM0 static V_MEMRAM1 tCwDataLengthType V_MEMRAM2 cwTxPendingLength;
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cwTaskState;

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
V_MEMRAM0 static V_MEMRAM1 vuintx V_MEMRAM2 cwCanHardwareLoopTimer;
#endif

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 cwShutdownTimer;
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cwShutdownState;
#endif

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *V_MEMRAM1 V_MEMRAM2 cwTxPendingBuffer;

V_MEMRAM0 static V_MEMRAM1 PduInfoType V_MEMRAM2 rxPduPhys[kFblCwNumberOfRequests];
V_MEMRAM0 static V_MEMRAM1 PduInfoType V_MEMRAM2 rxPduFunc;

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 * rxBuffer[kFblCwNumberOfRequests];
V_MEMRAM0 static V_MEMRAM1 PduInfoType V_MEMRAM2 txPdu[kFblCwNumberOfRequests];
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 txBuffer[kFblCwRcrRpMsgLength];
V_MEMRAM0 static V_MEMRAM1 tCwDataLengthType V_MEMRAM2 rxDataLength[kFblCwNumberOfRequests];

V_MEMRAM0 static V_MEMRAM1 PduLengthType V_MEMRAM2 rxRemainingBufferSize[kFblCwNumberOfRequests];

V_MEMRAM0 static V_MEMRAM1 FblCw_DcmDslConnectionInfoIterType V_MEMRAM2 activeConnection[kFblCwNumberOfRequests];

#if( FBLCW_QUEUED_REQUEST == STD_ON )
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cwQueuedRequestBuffer[FBL_CW_MAX_FPL_START_FRAME];
V_MEMRAM0 static V_MEMRAM1 PduLengthType V_MEMRAM2 cwQueuedRequestLength;
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cwQueuedRequestFlags;
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
V_MEMRAM0 static V_MEMRAM1 vuintx V_MEMRAM2 cwWakeUpFlag;

#if( FRIF_CUSTOM_JLE_SCHEDULING == STD_ON )
V_MEMRAM0 static V_MEMRAM1 vuint8            V_MEMRAM2 JLETimerCycle[FrIf_CommonMaxNumberOfClusters];
V_MEMRAM0 static V_MEMRAM1 vuint16           V_MEMRAM2 JLETimerOffset[FrIf_CommonMaxNumberOfClusters];
V_MEMRAM0 static V_MEMRAM1 boolean           V_MEMRAM2 JLETimerEnabled[FrIf_CommonMaxNumberOfClusters];
#endif

#if( FBLCW_KEY_SLOT_MODE == STD_ON )

V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2 cwAllSlots;
V_MEMRAM0 static V_MEMRAM1 vuint8  V_MEMRAM2 cwNwStatusTimeoutCtr;
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 cwNwStatusTimeout;
#endif

#endif

#if( FBLCW_MODULE_COMM == STD_ON )

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cwComMChannelIsOnline[COMM_ACTIVE_CHANNEL];

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cwDcmComMChannelMapping[FblCw_GetSizeOfDcmDslConnectionInfo()];
#endif

#define FBLCW_START_SEC_CODE
#include "MemMap.hpp"

static void FblCwInternalTransmitRP(void);

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
#if( FBLCW_MODULE_COMM == STD_OFF ) || \
     ( FBLCW_BAUDRATE_SWITCH == STD_ON )

static void FblCwCanIfSetMode(uint8 controllerId, CanIf_ControllerModeType mode);
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )

static void FblCheckOwnStartMsg(SduDataPtrType data, PduLengthType length);
#endif
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
#if( FRIF_CUSTOM_JLE_SCHEDULING == STD_ON )

static void FrIf_CustomJLEHandling(void);
#endif
#endif

#if( FBLCW_KEY_SLOT_MODE == STD_ON )

static void FblCwCheckNwStatus(void);
#endif

static void FblCwInternalMainFunctionTimerTask(void);

#if( FBLCW_QUEUED_REQUEST == STD_ON )

static void FblCwInternalQueuedRequestTask(void);
#endif

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

static void FblCwInternalEthShutdown(void);
#endif

static void FblCwInternalPendingTask(void);

#if(FBLCW_DECLINED_REQUESTS == STD_ON)

static BufReq_ReturnType Dcm_StartOfReception_Decline(PduIdType id, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, FBLCW_APPL_DATA) bufferSizePtr);
#endif

#if( FBLCW_DCMDSLCONNECTIONGROUPINFO == STD_ON )

static boolean FblCwInternalCheckForConnectionGroup(FblCw_DcmDslConnectionInfoIterType requestedConnection, FblCw_DcmDslConnectionInfoIterType currentConnection);
#endif

#if( FBLCW_DCMDSLBROADCASTGROUPINFO == STD_ON )

static boolean FblCwInternalCheckForBroadcastGroup(FblCw_DcmDslConnectionInfoIterType requestedConnection, FblCw_DcmDslConnectionInfoIterType currentConnection);
#endif

#if( FBLCW_DCMDSLCONNECTIONGROUPINFO == STD_ON ) || \
    ( FBLCW_DCMDSLBROADCASTGROUPINFO == STD_ON )

static boolean FblCwInternalCheckRxPduAllowedInConnection(PduIdType requestedPduId, uint8_least connectionIdx);
#endif

static void FblCwInternalTransmitRP(void){
  if(activeConnection[FBL_CW_MAIN_REQUEST_INDEX] != FBLCW_CONNECTION_UNASSIGNED){
    if(cwTxState == kFblCwTxStateIdle){
      txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduLength = kFblCwRcrRpMsgLength;
      txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = txBuffer;

      cwTxState = kFblCwTxStateRpInProgress;

#if( FBLCW_MODULE_COMM == STD_ON )
      if(FALSE == cwComMChannelIsOnline[cwDcmComMChannelMapping[activeConnection[FBL_CW_MAIN_REQUEST_INDEX]]])
      {
        cwTxTimer = kFblCwTxPendingTimeout;
        cwTxState = kFblCwTxStateRpPending;

        cwTxPendingLength = (tCwDataLengthType) kFblCwRcrRpMsgLength;
        cwTxPendingBuffer = txBuffer;
      }
      else
#endif
      {
        if(PduR_DcmTransmit(FblCw_GetTxRemotePduIdOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]), &txPdu[FBL_CW_MAIN_REQUEST_INDEX]) != E_OK)
        {
          cwTxTimer = kFblCwTxPendingTimeout;
          cwTxState = kFblCwTxStateRpPending;

          cwTxPendingLength = (tCwDataLengthType) kFblCwRcrRpMsgLength;
          cwTxPendingBuffer = txBuffer;
        }
      }
    }
  }
}

static void FblCwInternalMainFunctionTimerTask(void){
#if( FBLCW_MODULE_COMM == STD_ON )
  vuintx i;
#endif

#if( FBLCW_TASK_CYCLE > 1u )

  cycleCounter++;

  if(cycleCounter >= FBLCW_TASK_CYCLE){
    cycleCounter = 0u;
#else
  {
#endif
#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

    SwcServiceCanTp_MainFunction();
#endif
#if( FBLCW_MODULE_CANNM == STD_ON )

    CanNm_MainFunction();
#endif
#if( FBLCW_MODULE_CANSM == STD_ON )

    CanSM_MainFunction();
#endif

#if( FBLCW_MODULE_ETHSM == STD_ON )

    EthIf_MainFunctionState();
    EthSM_MainFunction();
#if defined(FBLCW_ETHSWT_MAINFUNCTION)
    FBLCW_ETHSWT_MAINFUNCTION();
#endif
#if defined(FBLCW_ETHTRCV_MAINFUNCTION)
    FBLCW_ETHTRCV_MAINFUNCTION();
#endif
#if defined(FBLCW_ETHTRCV_MAINFUNCTION_LINKHANDLING)
    FBLCW_ETHTRCV_MAINFUNCTION_LINKHANDLING();
#endif
#endif
#if( FBLCW_MODULE_FRSM == STD_ON )

    for(i = 0; i < FrIf_CommonMaxNumberOfClusters; i++){
       FrSM_MainFunction((FrSM_SizeOfVarStructType)i);
    }

#if( FBLCW_KEY_SLOT_MODE == STD_ON )

    if(FBL_CW_KEY_SLOT_MODE == cwAllSlots){
      cwNwStatusTimeoutCtr++;
    }
#endif
#endif

#if( FBLCW_MODULE_COMM == STD_ON )

    for(i = 0u; i < COMM_ACTIVE_CHANNEL; i++){
       ComM_MainFunction((NetworkHandleType)i);
    }
#endif
  }

#if( FBLCW_MODULE_SOAD == STD_ON )
  SoAd_MainFunction();
#endif
#if( FBLCW_MODULE_DOIP == STD_ON )
  DoIP_MainFunction();
#endif
#if( FBLCW_MODULE_TCPIP == STD_ON )
  TcpIp_MainFunction();
#endif

#if( FBLCW_EXISTS_CDD_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

  FBL_CW_CDD_TIMER_TASK();
#endif
}

#if( FBLCW_QUEUED_REQUEST == STD_ON )

static void FblCwInternalQueuedRequestTask(void){
  FblDiagRxStartIndication();

  rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = FblDiagRxGetPhysBuffer((tCwDataLengthType) rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduLength);

  assertFbl((rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr != NULL_PTR), kFblSysAssertNoBufferAvailable);

  if(rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr != NULL_PTR){
    if(GetCwRxIndPending()){
      assertFbl((rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduLength == cwQueuedRequestLength), kFblSysAssertParameterOutOfRange);

      ClrCwRxIndPending();

      (void) MEMCPY(rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr, cwQueuedRequestBuffer, cwQueuedRequestLength);

      rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = &rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr[cwQueuedRequestLength];

      SetCwMsgInProcess();

      FblDiagRxIndication(DiagBuffer, rxDataLength[FBL_CW_MAIN_REQUEST_INDEX]);
    }
    else{
      (void) MEMCPY(rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr, cwQueuedRequestBuffer, cwQueuedRequestLength);

      rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = &rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr[cwQueuedRequestLength];

      rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX] = (PduLengthType) FBL_DIAG_BUFFER_LENGTH - cwQueuedRequestLength;
    }

    ClrCwMsgQueued();
  }
  else{
  }
}
#endif

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

static void FblCwInternalEthShutdown(void){
  if((0u != cwShutdownTimer) && (kFblCwShutdownRequested == cwShutdownState)){
    switch(DoIP_Shutdown()){
      case E_OK:
      {
        cwShutdownState = kFblCwShutdownFinished;
        break;
      }
      case SOAD_E_INPROGRESS:
      {
        break;
      }
      default:
      {
        cwShutdownState = kFblCwShutdownFinished;
        break;
      }
    }

    cwShutdownTimer--;

    if(0u == cwShutdownTimer){
      cwShutdownState = kFblCwShutdownFinished;
    }

    if(kFblCwShutdownFinished == cwShutdownState){
      FblSetShutdownRequest();

      cwShutdownState = kFblCwNoShutdownRequest;
      cwShutdownTimer = 0u;
    }
  }
}
#endif

static void FblCwInternalPendingTask(void){
  vuint8 msgType;
  vuint8 newTxState;

  if(kFblCwTxStateRpPending == cwTxState){
    msgType = kFblCwMsgTypeRcrRp;
    newTxState = kFblCwTxStateRpInProgress;
  }
  else{
    msgType = kFblCwMsgTypeNormal;
    newTxState = kFblCwTxStateTxInProgress;
  }

  if(cwTxTimer == 0u){
    cwTxState = kFblCwTxStateIdle;

    FblDiagTxErrorIndication(msgType);
  }
  else{
    vuint8 prevTxState = cwTxState;

    cwTxState = newTxState;

    txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduLength = (PduLengthType) cwTxPendingLength;
    txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = cwTxPendingBuffer;

#if( FBLCW_MODULE_COMM == STD_ON )
    if(TRUE == cwComMChannelIsOnline[cwDcmComMChannelMapping[activeConnection[FBL_CW_MAIN_REQUEST_INDEX]]])
#endif
    {
      if(PduR_DcmTransmit(FblCw_GetTxRemotePduIdOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]), &txPdu[FBL_CW_MAIN_REQUEST_INDEX]) != E_OK)
      {
        cwTxState = prevTxState;
      }
      else
      {
        cwTxTimer = 0u;
      }
#if( FBLCW_TX_PROCESSING == FBLCW_POLLING )

      FBLCW_CAN_MAINFUNCTION_WRITE();
#endif
    }
#if( FBLCW_MODULE_COMM == STD_ON )
    else{
      cwTxState = prevTxState;
    }
#endif
  }
}

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
#if( FBLCW_MODULE_COMM == STD_OFF ) || \
     ( FBLCW_BAUDRATE_SWITCH == STD_ON )

static void FblCwCanIfSetMode(uint8 controllerId, CanIf_ControllerModeType mode){
  Std_ReturnType result;
  CanIf_ControllerModeType currentMode;

  result = CanIf_GetControllerMode(controllerId, &currentMode);
  assertFblInternal((E_OK == result), kFblSysAssertParameterOutOfRange);

  if((E_OK == result) && (mode != currentMode)){
    vuint16 maxWaitTime = kFblCwMaxWaitTime;

    result = CanIf_SetControllerMode(controllerId, mode);
    assertFblInternal((E_OK == result), kFblSysAssertParameterOutOfRange);

    while((E_OK == result) && (mode != currentMode) && (maxWaitTime > 0u)){
      if(FBL_NO_TRIGGER != FblLookForWatchdog())
      {
        maxWaitTime--;
      }

      FBLCW_CAN_MAINFUNCTION_MODE();

      result = CanIf_GetControllerMode(controllerId, &currentMode);
      assertFblInternal((E_OK == result), kFblSysAssertParameterOutOfRange);
    }
  }
}
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )

static void FblCheckOwnStartMsg(SduDataPtrType data, PduLengthType length){
  if(length < 8){
    vuint8 messageBuffer[8u];

    messageBuffer[0u] = (vuint8) (length & 0xFFu);
    {
      vuintx i;
      for(i = 1u; i < 8u; i++)
      {
        messageBuffer[i] = data[i - 1u];
      }
    }

    if(kFblOk == FblDiagCheckStartMsg(messageBuffer, 8u)){
      FblCwSetStartMsgReceived();
    }
  }
}
#endif
#endif

#if(FBLCW_DECLINED_REQUESTS == STD_ON)
static BufReq_ReturnType Dcm_StartOfReception_Decline(PduIdType id, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, FBLCW_APPL_DATA) bufferSizePtr){
  BufReq_ReturnType result = BUFREQ_E_NOT_OK;
  uint8_least connectionIndex;

  for(connectionIndex = 1u; connectionIndex < kFblCwNumberOfRequests; connectionIndex++){
    if(FBLCW_CONNECTION_UNASSIGNED == activeConnection[connectionIndex]){
      activeConnection[connectionIndex] = FblCw_GetDcmDslConnectionInfoIdxOfDcmDslProtocolRxInfo(id);
    }

    if(FblCw_CheckRxPduAllowedInConnection(id, connectionIndex)){
      if(TpSduLength <= FBL_DIAG_DECLINE_BUFFER_LENGTH)
      {
        rxPduPhys[connectionIndex].SduDataPtr = FblDiagRxGetDeclineBuffer((tCwDataLengthType) TpSduLength, connectionIndex);
        rxBuffer[connectionIndex] = rxPduPhys[connectionIndex].SduDataPtr;
        rxRemainingBufferSize[connectionIndex] = (PduLengthType) FBL_DIAG_DECLINE_BUFFER_LENGTH;

        activeConnection[connectionIndex] = FblCw_GetDcmDslConnectionInfoIdxOfDcmDslProtocolRxInfo(id);

        if(NULL_PTR != rxPduPhys[connectionIndex].SduDataPtr)
        {
          rxPduPhys[connectionIndex].SduLength = TpSduLength;
          *bufferSizePtr = rxRemainingBufferSize[connectionIndex];

          rxDataLength[connectionIndex] = TpSduLength;
          result = BUFREQ_OK;
        }
        else
        {
        }
      }
      else
      {
        result = BUFREQ_E_OVFL;
      }
      break;
    }
  }

  return result;
}
#endif

#if( FBLCW_DCMDSLCONNECTIONGROUPINFO == STD_ON )

static boolean FblCwInternalCheckForConnectionGroup(FblCw_DcmDslConnectionInfoIterType requestedConnection, FblCw_DcmDslConnectionInfoIterType currentConnection){
  boolean result = FALSE;

  if(FblCw_IsDcmDslConnectionGroupInfoIndUsedOfDcmDslConnectionInfo(currentConnection)){
    FblCw_DcmDslConnectionGroupInfoIndIterType  currentIdx;
    FblCw_DcmDslConnectionGroupInfoIndIterType  requestedIdx;
    FblCw_DcmDslConnectionGroupInfoIndType      currentGroup;

    for( currentIdx = FblCw_GetDcmDslConnectionGroupInfoIndStartIdxOfDcmDslConnectionInfo(currentConnection);
          currentIdx < FblCw_GetDcmDslConnectionGroupInfoIndEndIdxOfDcmDslConnectionInfo(currentConnection);
          currentIdx++){
      currentGroup = FblCw_GetDcmDslConnectionGroupInfoInd(currentIdx);

      for( requestedIdx = FblCw_GetDcmDslConnectionGroupInfoIndStartIdxOfDcmDslConnectionInfo(requestedConnection);
            requestedIdx < FblCw_GetDcmDslConnectionGroupInfoIndEndIdxOfDcmDslConnectionInfo(requestedConnection);
            requestedIdx++)
      {
        if(currentGroup == FblCw_GetDcmDslConnectionGroupInfoInd(requestedIdx))
        {
          result = TRUE;

          break;
        }
      }

      if(result == TRUE)
      {
        break;
      }
    }
  }

  return result;
}
#endif

#if( FBLCW_DCMDSLBROADCASTGROUPINFO == STD_ON )

static boolean FblCwInternalCheckForBroadcastGroup(FblCw_DcmDslConnectionInfoIterType requestedConnection, FblCw_DcmDslConnectionInfoIterType currentConnection){
  boolean result = FALSE;

  if( FblCw_IsDcmDslBroadcastGroupInfoUsedOfDcmDslConnectionInfo(requestedConnection)
    && FblCw_IsDcmDslBroadcastGroupInfoIndUsedOfDcmDslConnectionInfo(currentConnection) ){
    FblCw_DcmDslBroadcastGroupInfoIndIterType currentIdx;
    FblCw_DcmDslBroadcastGroupInfoIdxOfDcmDslConnectionInfoType broadcastGroup;

    broadcastGroup = FblCw_GetDcmDslBroadcastGroupInfoIdxOfDcmDslConnectionInfo(requestedConnection);

    for( currentIdx = FblCw_GetDcmDslBroadcastGroupInfoIndStartIdxOfDcmDslConnectionInfo(currentConnection);
          currentIdx < FblCw_GetDcmDslBroadcastGroupInfoIndEndIdxOfDcmDslConnectionInfo(currentConnection);
          currentIdx++){
      if(broadcastGroup == FblCw_GetDcmDslBroadcastGroupInfoInd(currentIdx))
      {
        result = TRUE;

        break;
      }
    }
  }

  return result;
}
#endif

#if( FBLCW_DCMDSLCONNECTIONGROUPINFO == STD_ON ) || \
    ( FBLCW_DCMDSLBROADCASTGROUPINFO == STD_ON )

static boolean FblCwInternalCheckRxPduAllowedInConnection(PduIdType requestedPduId, uint8_least connectionIdx){
  boolean result = FALSE;
  FblCw_DcmDslConnectionInfoIterType currentConnection;
  FblCw_DcmDslConnectionInfoIterType requestedConnection;

  currentConnection   = activeConnection[connectionIdx];

  if(FblCw_CheckRxPduAllowedInActiveConnection(requestedPduId, currentConnection)){
    result = TRUE;
  }
  else{
    requestedConnection = FblCw_GetDcmDslConnectionInfoIdxOfDcmDslProtocolRxInfo(requestedPduId);

#if( FBLCW_DCMDSLCONNECTIONGROUPINFO == STD_ON )

    result = FblCwInternalCheckForConnectionGroup(requestedConnection, currentConnection);

    if(result == TRUE){
      activeConnection[connectionIdx] = requestedConnection;
    }

    else
#endif
    {
#if( FBLCW_DCMDSLBROADCASTGROUPINFO == STD_ON )

      result = FblCwInternalCheckForBroadcastGroup(requestedConnection, currentConnection);
#endif
    }
  }

  return result;
}
#endif

void FblCwTransmitRP(const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * data){
  if(cwTxState == kFblCwTxStateIdle){
    vuintx i;

    for(i = 0u; i < kFblCwRcrRpMsgLength; i++){
      txBuffer[i] = data[i];
    }

    FblCwInternalTransmitRP();
  }
}

void FblCwRetransmitRP(void){
  FblCwInternalTransmitRP();
}

void FblCwTimerTask(void){
  if(FblCw_IsInitialized()){
    if(IsCwTimerTaskAllowed()){
      SetCwTimerTaskRunning();

      FblCwInternalMainFunctionTimerTask();

      if(cwTxTimer != 0u)
      {
        cwTxTimer--;

        switch(cwTxState)
        {
          case kFblCwTxStateIdle:
          case kFblCwTxStateRpInProgress:
          case kFblCwTxStateTxInProgress:
          {
            cwTxTimer = 0u;
            break;
          }
          case kFblCwTxStateTxPendingWaitForConf:
          {
            if(cwTxTimer == 0u)
            {
              cwTxState = kFblCwTxStateIdle;

              FblDiagTxErrorIndication(kFblCwMsgTypeNormal);
            }
            break;
          }
          case kFblCwTxStateRpPending:
          case kFblCwTxStateTxPending:
          {
            FblCwInternalPendingTask();
            break;
          }
          default:
          {
            cwTxState = kFblCwTxStateIdle;
            cwTxTimer = 0u;
            break;
          }
        }
      }

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
      FblCwInternalEthShutdown();
#endif

      ClrCwTimerTaskRunning();
    }
  }
}

void FblCwStateTask(void){
#if( FBLCW_MODULE_FRSM == STD_ON )
  vuintx i;
#endif

  if(FblCw_IsInitialized()){
    if(IsCwStateTaskAllowed()){
      SetCwStateTaskRunning();

#if( FBLCW_QUEUED_REQUEST == STD_ON )

      if(GetCwMsgQueued() && (!GetCwMsgInProcess()))
      {
        FblCwInternalQueuedRequestTask();
      }
#endif

#if( FBLCW_TX_PROCESSING == FBLCW_POLLING)

      FBLCW_CAN_MAINFUNCTION_WRITE();
#endif

#if( FBLCW_RX_PROCESSING == FBLCW_POLLING)

      FBLCW_CAN_MAINFUNCTION_READ();
#endif

#if( FBLCW_MODULE_ETHSM == STD_ON )

      EthIf_MainFunctionTx();
      EthIf_MainFunctionRx();
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
      for(i = 0; i < FrIf_CommonMaxNumberOfClusters; i++)
      {
#if( FRIF_CTRL_ENABLE_API_OPTIMIZATION == STD_ON )
         FrIf_MainFunction();
#else
         FrIf_MainFunction(i);
#endif
      }

#if( FRIF_CUSTOM_JLE_SCHEDULING == STD_ON )

      FrIf_CustomJLEHandling();
#endif
#endif

#if( FBLCW_EXISTS_CDD_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
      FBL_CW_CDD_STATE_TASK();
#endif

      ClrCwStateTaskRunning();
    }
  }
}

void FblCwIdleTask(void){
#if( FBLCW_BUSOFF_PROCESSING == FBLCW_POLLING )

   FBLCW_CAN_MAINFUNCTION_BUSOFF();
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
  if(FblCwGetWakeUpEvent()){
    if(kFblOk == ApplFblCwWakeUp()){
      (void) FrSM_RequestComMode(FrSM_ClusterConfig[0].NetworkHandleOfClusterConfig, COMM_FULL_COMMUNICATION);

      ApplTrcvrNormalMode();

      FblCwClrWakeUpEvent();
    }
  }

#if( FBLCW_KEY_SLOT_MODE == STD_ON )

  if(activeConnection[FBL_CW_MAIN_REQUEST_INDEX] != FBLCW_CONNECTION_UNASSIGNED){
    FblCwCheckNwStatus();
  }
#endif
#endif

#if( FBLCW_MODULE_XCP == STD_ON )
  if(GetXcpEnabled()){
#if( FBLCW_MODULE_CANXCP == STD_ON )
    (void) Xcp_MainFunction();
#endif
#if( FBLCW_MODULE_TCPIPXCP == STD_ON )
    TcpIpXcp_MainFunction();
#endif
  }
#endif
}

FUNC(void, FBLCW_CODE) FblCw_InitMemory(void){
  FblCw_SetInitialized(FALSE);
#if(FBLCW_USE_INIT_POINTER == STD_ON)
  FblCw_ConfigDataPtr = NULL_PTR;
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )
  fblCwStateStartMsg = 0u;
#endif
}

FUNC(void, FBLCW_CODE) FblCw_Init(P2CONST(FblCw_ConfigType, AUTOMATIC, FBLCW_INIT_DATA) config){
  uint8_least initializationIndex;

#if( FBLCW_MODULE_COMM == STD_ON )
#if( COMM_ACTIVE_CHANNEL > 1u)
  static V_MEMROM1 vuint8 V_MEMROM2 dcmComMMappingTable[FblCw_GetSizeOfDcmDslConnectionInfo()] = FBL_CW_DCM_COMM_MAPPING;
#endif
#endif

#if(FBLCW_USE_INIT_POINTER == STD_ON)
  FblCw_ConfigDataPtr = config;
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
#if( FBLCW_KEY_SLOT_MODE == STD_ON )

  if(FblMainGetStartFromAppl()){
    cwAllSlots = FBL_CW_ALL_SLOT_MODE;
    cwNwStatusTimeout = TESTER_PRESENT_TIMEOUT / FBL_CW_TASK_CYCLE;
  }
  else{
    cwAllSlots = FBL_CW_KEY_SLOT_MODE;
    cwNwStatusTimeout = FBL_CW_NW_STATUS_TIMEOUT / FBL_CW_TASK_CYCLE;
  }
  cwNwStatusTimeoutCtr = 0u;
#endif
  FblCwClrWakeUpEvent();
#endif

#if( FBLCW_TASK_CYCLE > 1u )
  cycleCounter = 0u;
#endif
  cwTxTimer = 0u;
  cwTxState = kFblCwTxStateIdle;
  cwTaskState = 0u;

#if( FBLCW_QUEUED_REQUEST == STD_ON )
  cwQueuedRequestFlags = 0;
#endif

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
  cwCanHardwareLoopTimer = 0u;
#endif

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )
  cwShutdownState = kFblCwNoShutdownRequest;
  cwShutdownTimer = 0u;
#endif

  for(initializationIndex = 0u; initializationIndex < kFblCwNumberOfRequests; initializationIndex++){
    activeConnection[initializationIndex] = FBLCW_CONNECTION_UNASSIGNED;
  }

#if defined( FBL_DEF_ENABLE_NON_KB_MAIN )

   ApplTrcvrNormalMode();
#endif

  FblCw_EcuMInit();

#if( FBLCW_MODULE_COMM == STD_ON )
  for(initializationIndex = 0u; initializationIndex < FblCw_GetSizeOfDcmDslConnectionInfo(); initializationIndex++){
#if( COMM_ACTIVE_CHANNEL == 1u)

     cwDcmComMChannelMapping[initializationIndex] = FBLCW_COMM_CHANNEL;
#else
     cwDcmComMChannelMapping[initializationIndex] = dcmComMMappingTable[initializationIndex];
#endif
  }

  for(initializationIndex = 0u; initializationIndex < COMM_ACTIVE_CHANNEL; initializationIndex++){
    cwComMChannelIsOnline[initializationIndex] = FALSE;
    (void) ComM_CommunicationAllowed((NetworkHandleType)initializationIndex, TRUE);
    (void) ComM_EcuM_WakeUpIndication((NetworkHandleType)initializationIndex);
  }
#else
#if( FBLCW_CANIFCTRLINFO == STD_ON )

  {
    FblCw_CanIfCtrlInfoIterType canIfCtrlIdx;

    for(canIfCtrlIdx = 0u; canIfCtrlIdx < FblCw_GetSizeOfCanIfCtrlInfo(); canIfCtrlIdx++){
      uint8 currentChannel;
      currentChannel = FblCw_GetCanIfCtrlInfo(canIfCtrlIdx);

      FblCwCanIfSetMode(currentChannel, CANIF_CS_STARTED);

      {
        (void) CanIf_SetPduMode(currentChannel, CANIF_SET_ONLINE);
      }
    }
  }
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )

  FrIf_Status[0].State = FRIF_STATE_OFFLINE;
#endif

#if( FBLCW_COMMETHCHANNELINFO == STD_ON )

  {
    FblCw_ComMEthChannelInfoIterType comMChannelIdx;
    for(comMChannelIdx = 0u; comMChannelIdx < FblCw_GetSizeOfComMEthChannelInfo(); comMChannelIdx++){
      (void) EthSM_RequestComMode(FblCw_GetComMEthChannelInfo(comMChannelIdx), COMM_FULL_COMMUNICATION);
    }
  }
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
#if( FBLCW_COMMFRNMCHANNELINFO == STD_ON ){
    FblCw_ComMFrNmChannelInfoIterType comMChannelIdx;
    for(comMChannelIdx = 0u; comMChannelIdx < FblCw_GetSizeOfComMFrNmChannelInfo(); comMChannelIdx++){
      (void) Nm_PassiveStartUp(FblCw_GetComMFrNmChannelInfo(comMChannelIdx));
    }
  }
#endif

#if( FRIF_CUSTOM_JLE_SCHEDULING == STD_ON )

  FrIf_Enable_JLE_Timer(0);
#endif
#if( FBLCW_COMMFRCHANNELINFO == STD_ON )
#if( FblCw_GetSizeOfComMFrChannelInfo() > 1 )
#    error "Multiple FR Channels are not supported!"
#endif
  (void) FrSM_RequestComMode(FblCw_GetComMFrChannelInfo(0), COMM_FULL_COMMUNICATION);
#else
  {
    FblCwSetWakeUpEvent();

    ApplTrcvrSleepMode();
  }
#endif
#endif
#endif

#if(FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON)
#if(CANTP_ENABLE_READ_PARAM == STD_ON)
  {
    FblCw_DcmDslConnectionInfoIterType dcmDslConnectionInfoIdx;
    for(dcmDslConnectionInfoIdx = 0u; dcmDslConnectionInfoIdx < FblCw_GetSizeOfDcmDslConnectionInfo(); dcmDslConnectionInfoIdx++){
      if(FblCw_IsParameterInfoUsedOfDcmDslConnectionInfo(dcmDslConnectionInfoIdx))
      {
        FblCw_ParameterInfoIterType parameterInfoIdx;
        parameterInfoIdx = FblCw_GetParameterInfoIdxOfDcmDslConnectionInfo(dcmDslConnectionInfoIdx);

        (void) CanTp_ReadParameter(FblCw_GetCanTpIdOfParameterInfo(parameterInfoIdx), TP_BS, FblCw_GetAddrInitialBS(parameterInfoIdx));

        (void) CanTp_ReadParameter(FblCw_GetCanTpIdOfParameterInfo(parameterInfoIdx), TP_STMIN, FblCw_GetAddrInitialSTmin(parameterInfoIdx));

      }
    }
  }
#endif
#endif

  FblCw_SetInitialized(TRUE);
  FBLCW_DUMMY_STATEMENT(config);
}

FUNC(void, FBLCW_CODE) FblCw_Deinit(void){
#if( FBLCW_MODULE_FRSM == STD_ON )
  vuintx i;

  (void) FrSM_RequestComMode(FrSM_ClusterConfig[0].NetworkHandleOfClusterConfig, COMM_NO_COMMUNICATION);
  for(i = 0; i < FrIf_CommonMaxNumberOfClusters; i++){
     FrSM_MainFunction((FrSM_SizeOfVarStructType)i);
  }
#endif
  FblCw_SetInitialized(FALSE);
}

void FblCwPduTransmit(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * data, tCwDataLengthType length){
  vuint16 maxWaitTime = kFblCwMaxWaitTime;

  while((maxWaitTime > 0u) && (cwTxState != kFblCwTxStateIdle)){
    if(FBL_NO_TRIGGER != FblLookForWatchdog()){
      maxWaitTime--;
    }
  }

  if((activeConnection[FBL_CW_MAIN_REQUEST_INDEX] != FBLCW_CONNECTION_UNASSIGNED) && (GetDiagBufferLocked())){
    cwTxTimer = kFblCwTxPendingTimeout;

    length += DcmAppendMessageAuthentication(data[0], &data[1], (length-1));

    cwTxPendingLength = length;
    cwTxPendingBuffer = data;

    switch(cwTxState){
      case kFblCwTxStateRpInProgress:
      case kFblCwTxStateTxInProgress:
      {
        cwTxState = kFblCwTxStateTxPendingWaitForConf;
        break;
      }

      default:
      {
        txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduLength = (PduLengthType) length;
        txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = data;

#if( FBLCW_MODULE_COMM == STD_ON )
        if(TRUE == cwComMChannelIsOnline[cwDcmComMChannelMapping[activeConnection[FBL_CW_MAIN_REQUEST_INDEX]]])
#endif
        {
          cwTxState = kFblCwTxStateTxInProgress;

          if(PduR_DcmTransmit(FblCw_GetTxRemotePduIdOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]), &txPdu[FBL_CW_MAIN_REQUEST_INDEX]) != E_OK)
          {
            cwTxState = kFblCwTxStateTxPending;
          }
        }
#if( FBLCW_MODULE_COMM == STD_ON )
        else
        {
          cwTxState = kFblCwTxStateTxPending;
        }
#endif
      }
    }
  }
#if( FBLCW_TX_PROCESSING == FBLCW_POLLING )
  FBLCW_CAN_MAINFUNCTION_WRITE();
#endif
}

#if defined( FBL_ENABLE_STAY_IN_BOOT )

tFblResult FblCwCheckStartMessage(void){
  tFblResult result = kFblFailed;

  if(FblCwGetStartMsgReceived()){
    result = kFblOk;
  }
  return result;
}
#endif

#if(FBLCW_DECLINED_REQUESTS == STD_ON)

void FblCwPduTransmitDeclinedRequest(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * data, tCwDataLengthType length, vuint8 connectionIndex){
  if(activeConnection[connectionIndex] != FBLCW_CONNECTION_UNASSIGNED){
    txPdu[connectionIndex].SduLength = (PduLengthType) length;
    txPdu[connectionIndex].SduDataPtr = data;
    if(PduR_DcmTransmit(FblCw_GetTxRemotePduIdOfDcmDslConnectionInfo(activeConnection[connectionIndex]), &txPdu[connectionIndex]) != E_OK){
      FblDiagDeclineErrorIndication(connectionIndex);
      activeConnection[connectionIndex] = FBLCW_CONNECTION_UNASSIGNED;
    }
  }
}
#endif

void FblCwTxSetTargetAddress(FblCw_DcmDslConnectionInfoIterType targetAddress){
  if(targetAddress < FblCw_GetSizeOfDcmDslConnectionInfo()){
    activeConnection[FBL_CW_MAIN_REQUEST_INDEX] = targetAddress;
  }
  else{
    activeConnection[FBL_CW_MAIN_REQUEST_INDEX] = FBLCW_CONNECTION_UNASSIGNED;
  }
}

FblCw_DcmDslConnectionInfoIterType FblCwGetResponseAddress(void){
  return activeConnection[FBL_CW_MAIN_REQUEST_INDEX];
}

void FblCwResetResponseAddress(void){
  activeConnection[FBL_CW_MAIN_REQUEST_INDEX] = FBLCW_CONNECTION_UNASSIGNED;
}

tFblResult FblCwPrepareResponseAddress(void){
  tFblResult result;
  FblCw_DcmDslConnectionInfoIterType connectionIndex;

#if defined( FBL_CW_ENABLE_MULTIPLE_CONNECTIONS )
  vuint8 addressBuffer[sizeof(FblCw_RxTesterSourceAddressOfDcmDslConnectionInfo16BitType)];
  FblCw_RxTesterSourceAddressOfDcmDslConnectionInfoType address;

  result = ApplFblReadDcmDslRxTesterSourceAddr(addressBuffer);

  if(kFblOk == result){
    address = (FblCw_RxTesterSourceAddressOfDcmDslConnectionInfoType) FblMemGetInteger(sizeof(FblCw_RxTesterSourceAddressOfDcmDslConnectionInfo16BitType), (tFblMemConstRamData) addressBuffer);

    for(connectionIndex = 0u; connectionIndex < FblCw_GetSizeOfDcmDslConnectionInfo(); connectionIndex++){
      if(FblCw_GetRxTesterSourceAddressOfDcmDslConnectionInfo(connectionIndex) == address)
      {
        break;
      }
    }
  }
  else{
    connectionIndex = FBLCW_CONNECTION_UNASSIGNED;
  }
#else

  connectionIndex = 0u;

  result = kFblOk;
#endif

  FblCwTxSetTargetAddress(connectionIndex);

  return result;
}

tFblResult FblCwSaveResponseAddress(void){
  tFblResult result;

#if defined( FBL_CW_ENABLE_MULTIPLE_CONNECTIONS )
  vuint8 addressBuffer[sizeof(FblCw_RxTesterSourceAddressOfDcmDslConnectionInfo16BitType)];

  FblMemSetInteger(sizeof(FblCw_RxTesterSourceAddressOfDcmDslConnectionInfo16BitType)
   ,                  FblCw_GetRxTesterSourceAddressOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX])
   ,                  addressBuffer);

  result = ApplFblWriteDcmDslRxTesterSourceAddr(addressBuffer);
#else
  result = kFblOk;
#endif

  return result;
}

#if( FBLCW_BAUDRATE_SWITCH == STD_ON )

tFblResult FblCwCheckBaudrate(vuint32 baudrate){
  tFblResult result = kFblFailed;

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

  if((activeConnection[FBL_CW_MAIN_REQUEST_INDEX] != FBLCW_CONNECTION_UNASSIGNED)
     && (FBLCW_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == FblCw_GetBusTypeOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]))){
    if(baudrate < 0x10000u){
      if(E_OK == CanIf_CheckBaudrate((uint8) (FblCw_GetControllerOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]) & 0xFFu), (uint16) (baudrate & 0xFFFFu)))
      {
        result = kFblOk;
      }
    }
  }
#endif

  return result;
}

tFblResult FblCwSwitchBaudrate(vuint32 baudrate){
  tFblResult result = kFblFailed;

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

  if((activeConnection[FBL_CW_MAIN_REQUEST_INDEX] != FBLCW_CONNECTION_UNASSIGNED)
     && (FBLCW_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == FblCw_GetBusTypeOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]))){
    FblCwCanIfSetMode((uint8) (FblCw_GetControllerOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]) & 0xFFu), CANIF_CS_STOPPED);

    if(baudrate < 0x10000u){
      if(E_OK == CanIf_ChangeBaudrate((uint8) (FblCw_GetControllerOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]) & 0xFFu), (uint16) (baudrate & 0xFFFFu)))
      {
        result = kFblOk;
      }
    }

    FblCwCanIfSetMode((uint8) (FblCw_GetControllerOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]) & 0xFFu), CANIF_CS_STARTED);
  }
#endif

  return result;
}
#endif

void FblCwResetRxBlock(void){
#if( FBLCW_QUEUED_REQUEST == STD_ON )

  ClrCwMsgInProcess();
#endif
}

tCwDataLengthType FblCwGetPayloadLimit(void){
  tCwDataLengthType payloadLimit;

  if(activeConnection[FBL_CW_MAIN_REQUEST_INDEX] == FBLCW_CONNECTION_UNASSIGNED){
    payloadLimit = 0u;
  }
  else{
    payloadLimit = (tCwDataLengthType) FblCw_GetPayloadLimitOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]);
  }

  return payloadLimit;
}

FUNC(BufReq_ReturnType, FBLCW_CODE) Dcm_StartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, FBLCW_APPL_DATA) info, PduLengthType TpSduLength
   ,                                                        P2VAR(PduLengthType, AUTOMATIC, FBLCW_APPL_DATA) bufferSizePtr){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId = FBLCW_E_NO_ERROR;
#endif
  BufReq_ReturnType result = BUFREQ_E_NOT_OK;

  if(!FblCw_IsInitialized()){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
    errorId = FBLCW_E_UNINIT;
#endif
  }
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  else if(id >= FblCw_GetSizeOfDcmDslProtocolRxInfo()){
    errorId = FBLCW_E_PARAM;
  }
#if(FBLCW_INVALIDHNDOFDCMDSLPROTOCOLRXINFO == STD_ON)
  else if(FblCw_IsInvalidHndOfDcmDslProtocolRxInfo(id)){
    errorId = FBLCW_E_PARAM;
  }
#endif
#if( FBLCW_QUEUED_REQUEST == STD_ON )

  else if(GetCwMsgQueued()){
  }
#endif
  else
#endif
  {
    if(FBLCW_CONNECTION_UNASSIGNED == activeConnection[FBL_CW_MAIN_REQUEST_INDEX]){
      activeConnection[FBL_CW_MAIN_REQUEST_INDEX] = FblCw_GetDcmDslConnectionInfoIdxOfDcmDslProtocolRxInfo(id);
    }

    if(FblCw_CheckRxPduAllowedInConnection(id, FBL_CW_MAIN_REQUEST_INDEX)){
      switch(FblCw_GetAddrTypeOfDcmDslProtocolRxInfo(id))
      {
#if(FBLCW_EXISTS_PHYSICAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO == STD_ON)
        case FBLCW_PHYSICAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO:
        {
          if(TpSduLength <= FBL_DIAG_BUFFER_LENGTH)
          {
#if( FBLCW_QUEUED_REQUEST == STD_ON )

            if(GetCwMsgInProcess())
            {
              rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = cwQueuedRequestBuffer;
              rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX] = FBL_CW_MAX_FPL_START_FRAME;
            }
            else
#endif
            {
              rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = FblDiagRxGetPhysBuffer((tCwDataLengthType) TpSduLength);
              rxBuffer[FBL_CW_MAIN_REQUEST_INDEX] = rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr;
              rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX] = (PduLengthType) FBL_DIAG_BUFFER_LENGTH;
            }

            if(NULL_PTR != rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr)
            {
              rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduLength = TpSduLength;
              *bufferSizePtr = rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX];

              rxDataLength[FBL_CW_MAIN_REQUEST_INDEX] = TpSduLength;
#if( FBLCW_QUEUED_REQUEST == STD_ON )
              if(GetCwMsgInProcess())
              {
              }
              else
#endif
              {
                FblDiagRxStartIndication();
              }
              result = BUFREQ_OK;
            }
            else
            {
            }
          }
          else
          {
            result = BUFREQ_E_OVFL;
          }
          break;
        }
#endif
#if(FBLCW_EXISTS_FUNCTIONAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO == STD_ON)
        case FBLCW_FUNCTIONAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO:
        {
          if(TpSduLength <= FBL_DIAG_BUFFER_LENGTH)
          {
            rxPduFunc.SduDataPtr = FblDiagRxGetFuncBuffer((tCwDataLengthType) TpSduLength);
            rxBuffer[FBL_CW_MAIN_REQUEST_INDEX] = rxPduFunc.SduDataPtr;
            rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX] = (PduLengthType) FBL_DIAG_BUFFER_LENGTH;

            *bufferSizePtr = rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX];

            result = BUFREQ_OK;
            if(NULL_PTR != rxPduFunc.SduDataPtr)
            {
              rxPduFunc.SduLength = TpSduLength;

              rxDataLength[FBL_CW_MAIN_REQUEST_INDEX] = TpSduLength;

              FblDiagRxStartIndication();
            }
            else
            {
            }
          }
          else
          {
            result = BUFREQ_E_OVFL;
          }
          break;
        }
#endif
        default:
        {
          break;
        }
      }
    }
#if(FBLCW_DECLINED_REQUESTS == STD_ON)

    else{
      result = Dcm_StartOfReception_Decline(id, TpSduLength, bufferSizePtr);
    }
#endif
  }

#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  if(errorId != FBLCW_E_NO_ERROR){
    FblCw_Det_ReportError(FBLCW_APIID_STARTOFRECEPTION, (errorId));
  }
#endif

  FBLCW_DUMMY_STATEMENT(info);
  return result;
}

FUNC(BufReq_ReturnType, FBLCW_CODE) Dcm_CopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, FBLCW_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, FBLCW_APPL_DATA) bufferSizePtr){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId = FBLCW_E_NO_ERROR;
#endif
  BufReq_ReturnType result = BUFREQ_E_NOT_OK;
  vuint8 state = GetCwTaskState();
  SetCwTaskRunning();

  if(!FblCw_IsInitialized()){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
    errorId = FBLCW_E_UNINIT;
#endif
  }
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  else if(id >= FblCw_GetSizeOfDcmDslProtocolRxInfo()){
    errorId = FBLCW_E_PARAM;
  }
#if(FBLCW_INVALIDHNDOFDCMDSLPROTOCOLRXINFO == STD_ON)
  else if(FblCw_IsInvalidHndOfDcmDslProtocolRxInfo(id)){
    errorId = FBLCW_E_PARAM;
  }
#endif
#endif
  else{
#if defined( FBL_ENABLE_STAY_IN_BOOT )
    if(FblCwGetCheckForStartMsg()){
      FblCheckOwnStartMsg(info->SduDataPtr, info->SduLength);

      if(!FblCwGetStartMsgReceived())
      {
        result = BUFREQ_OK;
      }
    }
    else
#endif
    {
      if(FblCw_CheckRxPduAllowedInConnection(id, FBL_CW_MAIN_REQUEST_INDEX))
      {
        switch(FblCw_GetAddrTypeOfDcmDslProtocolRxInfo(id))
        {
#if(FBLCW_EXISTS_PHYSICAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO == STD_ON)
          case FBLCW_PHYSICAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO:
          {
#if( FBLCW_QUEUED_REQUEST == STD_ON )

            if(GetCwMsgInProcess())
            {
              if(GetCwMsgQueued())
              {
                *bufferSizePtr = 0u;
                result = BUFREQ_OK;
              }
              else
              {
                assertFblInternal((info->SduLength <= rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX]), kFblSysAssertParameterOutOfRange);

                (void) MEMCPY(rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr, info->SduDataPtr, info->SduLength);
                rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = &rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr[info->SduLength];
                rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX] -= info->SduLength;
                *bufferSizePtr = rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX];

                cwQueuedRequestLength = info->SduLength;

                SetCwMsgQueued();
                result = BUFREQ_OK;
              }
            }
            else
#endif
            {
              if(NULL_PTR != rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr)
              {
                if(info->SduLength <= rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX])
                {
                  (void) MEMCPY(rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr, info->SduDataPtr, info->SduLength);
                  rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = &rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr[info->SduLength];
                  rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX] -= info->SduLength;
                  *bufferSizePtr = rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX];

                  result = BUFREQ_OK;
                }
              }
              else
              {
              }
            }
            break;
          }
#endif

#if(FBLCW_EXISTS_FUNCTIONAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO == STD_ON)
          case FBLCW_FUNCTIONAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO:
          {
            if(NULL_PTR != rxPduFunc.SduDataPtr)
            {
              if(info->SduLength <= rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX])
              {
                (void) MEMCPY(rxPduFunc.SduDataPtr, info->SduDataPtr, info->SduLength);
                rxPduFunc.SduDataPtr = &rxPduFunc.SduDataPtr[info->SduLength];
                rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX] -= info->SduLength;
                *bufferSizePtr = rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX];

                result = BUFREQ_OK;
              }
            }
            else
            {
              *bufferSizePtr = rxRemainingBufferSize[FBL_CW_MAIN_REQUEST_INDEX];
              result = BUFREQ_OK;
            }
            break;
          }
#endif
          default:
          {
          }
        }
      }
#if(FBLCW_DECLINED_REQUESTS == STD_ON)
      else
      {
        uint8_least connectionIndex;

        for(connectionIndex = 1u; connectionIndex < kFblCwNumberOfRequests; connectionIndex++)
        {
          if(FblCw_CheckRxPduAllowedInConnection(id, connectionIndex))
          {
            if(NULL_PTR != rxPduPhys[connectionIndex].SduDataPtr)
            {
              if(info->SduLength <= rxRemainingBufferSize[connectionIndex])
              {
                (void) MEMCPY(rxPduPhys[connectionIndex].SduDataPtr, info->SduDataPtr, info->SduLength);
                rxPduPhys[connectionIndex].SduDataPtr = &rxPduPhys[connectionIndex].SduDataPtr[info->SduLength];
                rxRemainingBufferSize[connectionIndex] -= info->SduLength;
                *bufferSizePtr = rxRemainingBufferSize[connectionIndex];

                result = BUFREQ_OK;
              }
            }
            else
            {
            }
            break;
          }
        }
      }
#endif
    }
  }

  RestoreCwTaskState(state);

#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  if(errorId != FBLCW_E_NO_ERROR){
    FblCw_Det_ReportError(FBLCW_APIID_COPYRXDATA, (errorId));
  }
#endif

  return result;
}

FUNC(BufReq_ReturnType, FBLCW_CODE) Dcm_CopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry
   ,                                                  P2VAR(PduLengthType, AUTOMATIC, FBLCW_APPL_DATA) availableDataPtr){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId = FBLCW_E_NO_ERROR;
#endif
  BufReq_ReturnType result = BUFREQ_E_NOT_OK;
  vuint8 state = GetCwTaskState();

  SetCwTaskRunning();
  if(!FblCw_IsInitialized()){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
    errorId = FBLCW_E_UNINIT;
#endif
  }
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  else if(id >= FblCw_GetSizeOfDcmDslProtocolTxInfo()){
    errorId = FBLCW_E_PARAM;
  }
#if(FBLCW_INVALIDHNDOFDCMDSLPROTOCOLTXINFO == STD_ON)
  else if(FblCw_IsInvalidHndOfDcmDslProtocolTxInfo(id)){
    errorId = FBLCW_E_PARAM;
  }
#endif
  else
#endif
  {
    if(retry != NULL_PTR){
      assertFblInternal((retry->TpDataState == TP_DATACONF), kFblSysAssertParameterOutOfRange);
    }

    if(FblCw_CheckTxPduAllowedInActiveConnection(id, activeConnection[FBL_CW_MAIN_REQUEST_INDEX])){
      result = BUFREQ_OK;
      if(info->SduLength == 0)
      {
        *availableDataPtr = txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduLength;
      }
      else
      {
        if(info->SduLength <= txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduLength)
        {
          (void) MEMCPY(info->SduDataPtr, txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr, info->SduLength);
          txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr = &txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr[info->SduLength];
          txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduLength -= info->SduLength;
          *availableDataPtr = txPdu[FBL_CW_MAIN_REQUEST_INDEX].SduLength;
        }
        else
        {
          result = BUFREQ_E_NOT_OK;
        }
      }
    }
#if(FBLCW_DECLINED_REQUESTS == STD_ON)
    else{
      uint8_least connectionIndex;

      for(connectionIndex = 1u; connectionIndex < kFblCwNumberOfRequests; connectionIndex++)
      {
        if(FblCw_CheckTxPduAllowedInActiveConnection(id, activeConnection[connectionIndex]))
        {
          result = BUFREQ_OK;
          if(info->SduLength == 0)
          {
            *availableDataPtr = txPdu[connectionIndex].SduLength;
          }
          else
          {
            if(info->SduLength <= txPdu[connectionIndex].SduLength)
            {
              (void) MEMCPY(info->SduDataPtr, txPdu[connectionIndex].SduDataPtr, info->SduLength);
              txPdu[connectionIndex].SduDataPtr = &txPdu[connectionIndex].SduDataPtr[info->SduLength];
              txPdu[connectionIndex].SduLength -= info->SduLength;
              *availableDataPtr = txPdu[connectionIndex].SduLength;
            }
            else
            {
              result = BUFREQ_E_NOT_OK;
            }
          }
          break;
        }
      }
    }
#endif
  }

  RestoreCwTaskState(state);

#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  if(errorId != FBLCW_E_NO_ERROR){
    FblCw_Det_ReportError(FBLCW_APIID_COPYTXDATA, (errorId));
  }
#endif

  FBLCW_DUMMY_STATEMENT(id);

  return result;
}

FUNC(void, FBLCW_CODE) Dcm_TpRxIndication(PduIdType id, NotifResultType result){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId = FBLCW_E_NO_ERROR;
#endif

  if(!FblCw_IsInitialized()){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
    errorId = FBLCW_E_UNINIT;
#endif
  }
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  else if(id >= FblCw_GetSizeOfDcmDslProtocolRxInfo()){
    errorId = FBLCW_E_PARAM;
  }
#if(FBLCW_INVALIDHNDOFDCMDSLPROTOCOLRXINFO == STD_ON)
  else if(FblCw_IsInvalidHndOfDcmDslProtocolRxInfo(id)){
    errorId = FBLCW_E_PARAM;
  }
#endif
  else
#endif
  {
    if(FblCw_CheckRxPduAllowedInConnection(id, FBL_CW_MAIN_REQUEST_INDEX)){
      if(((FblCw_GetAddrTypeOfDcmDslProtocolRxInfo(id) == FBLCW_PHYSICAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO) && (NULL_PTR != rxPduPhys[FBL_CW_MAIN_REQUEST_INDEX].SduDataPtr))
#if(FBLCW_EXISTS_FUNCTIONAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO == STD_ON)
         || ((FblCw_GetAddrTypeOfDcmDslProtocolRxInfo(id) == FBLCW_FUNCTIONAL_ADDRTYPEOFDCMDSLPROTOCOLRXINFO) && (NULL_PTR != rxPduFunc.SduDataPtr))
#endif
        )
      {
        switch(result)
        {
          case NTFRSLT_OK:
          {
#if( FBLCW_QUEUED_REQUEST == STD_ON )

            if(GetCwMsgInProcess())
            {
              SetCwRxIndPending();
            }
            else
#endif
            {
#if( FBLCW_QUEUED_REQUEST == STD_ON )

              SetCwMsgInProcess();
#endif

              FblDiagRxIndication(DiagBuffer, rxDataLength[FBL_CW_MAIN_REQUEST_INDEX]);
            }
            break;
          }
          case NTFRSLT_E_NOT_OK:
          case NTFRSLT_E_TIMEOUT_A:
          case NTFRSLT_E_TIMEOUT_BS:
          case NTFRSLT_E_TIMEOUT_CR:
          case NTFRSLT_E_WRONG_SN:
          case NTFRSLT_E_INVALID_FS:
          case NTFRSLT_E_UNEXP_PDU:
          case NTFRSLT_E_WFT_OVRN:
          {
            FblDiagRxErrorIndication();
            break;
          }
          default:
          {
            break;
          }
        }
      }
    }
#if(FBLCW_DECLINED_REQUESTS == STD_ON)
    else{
      vuintx connectionIndex;

      for(connectionIndex = 1u; connectionIndex < kFblCwNumberOfRequests; connectionIndex++)
      {
        if(FblCw_CheckRxPduAllowedInConnection(id, connectionIndex))
        {
          switch(result)
          {
            case NTFRSLT_OK:
            {
              FblDiagRxDeclineIndication(rxBuffer[connectionIndex], rxDataLength[connectionIndex], connectionIndex);
              break;
            }
            case NTFRSLT_E_NOT_OK:
            case NTFRSLT_E_TIMEOUT_A:
            case NTFRSLT_E_TIMEOUT_BS:
            case NTFRSLT_E_TIMEOUT_CR:
            case NTFRSLT_E_WRONG_SN:
            case NTFRSLT_E_INVALID_FS:
            case NTFRSLT_E_UNEXP_PDU:
            case NTFRSLT_E_WFT_OVRN:
            {
              FblDiagDeclineErrorIndication(connectionIndex);
              activeConnection[connectionIndex] = FBLCW_CONNECTION_UNASSIGNED;
              break;
            }
            default:
            {
              break;
            }
          }
          break;
        }
      }
    }
#endif
  }

#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  if(errorId != FBLCW_E_NO_ERROR){
    FblCw_Det_ReportError(FBLCW_APIID_TPRXINDICATION, (errorId));
  }
#endif

  FBLCW_DUMMY_STATEMENT(id);
}

FUNC(void, FBLCW_CODE) Dcm_TpTxConfirmation(PduIdType id, NotifResultType result){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  uint8 errorId = FBLCW_E_NO_ERROR;
#endif

  if(!FblCw_IsInitialized()){
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
    errorId = FBLCW_E_UNINIT;
#endif
  }
#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  else if(id >= FblCw_GetSizeOfDcmDslProtocolTxInfo()){
    errorId = FBLCW_E_PARAM;
  }
#if(FBLCW_INVALIDHNDOFDCMDSLPROTOCOLTXINFO == STD_ON)
  else if(FblCw_IsInvalidHndOfDcmDslProtocolTxInfo(id)){
    errorId = FBLCW_E_PARAM;
  }
#endif
  else
#endif
  {
    if(FblCw_CheckTxPduAllowedInActiveConnection(id, activeConnection[FBL_CW_MAIN_REQUEST_INDEX])){
      if(result == NTFRSLT_OK)
      {
        switch(cwTxState)
        {
          case kFblCwTxStateIdle:
          {
            break;
          }
          case kFblCwTxStateRpInProgress:
          {
            FblDiagTxConfirmation(kFblCwMsgTypeRcrRp);
            break;
          }
          case kFblCwTxStateTxInProgress:
          {
            FblDiagTxConfirmation(kFblCwMsgTypeNormal);
#if( FBLCW_QUEUED_REQUEST == STD_ON )

            ClrCwMsgInProcess();
#endif
            break;
          }
          case kFblCwTxStateTxPendingWaitForConf:
          {
            cwTxState = kFblCwTxStateTxPending;
            break;
          }
          default:
          {
            assertFblInternal(0u, kFblSysAssertParameterOutOfRange);
            break;
          }
        }

        if(kFblCwTxStateTxPending != cwTxState)
        {
          cwTxState = kFblCwTxStateIdle;
          cwTxTimer = 0;
        }
      }
      else
      {
        switch(cwTxState)
        {
          case kFblCwTxStateRpInProgress:
          case kFblCwTxStateRpPending:
          {
            FblDiagTxErrorIndication(kFblCwMsgTypeRcrRp);
            break;
          }
          case kFblCwTxStateTxPendingWaitForConf:
          {
            cwTxState = kFblCwTxStateTxPending;
            break;
          }
          default:
          {
            FblDiagTxErrorIndication(kFblCwMsgTypeNormal);

            cwTxState = kFblCwTxStateIdle;
            cwTxTimer = 0;
#if( FBLCW_QUEUED_REQUEST == STD_ON )

            ClrCwMsgInProcess();
#endif
          }
        }
      }
    }
#if(FBLCW_DECLINED_REQUESTS == STD_ON)
    else{
      uint8_least connectionIndex;

      for(connectionIndex = 1u; connectionIndex < kFblCwNumberOfRequests; connectionIndex++)
      {
        if(FblCw_CheckTxPduAllowedInActiveConnection(id, activeConnection[connectionIndex]))
        {
          FblDiagDeclineTxConfirmation(connectionIndex);
          activeConnection[connectionIndex] = FBLCW_CONNECTION_UNASSIGNED;
          break;
        }
      }
    }
#endif
  }

#if(FBLCW_DEV_ERROR_DETECT == STD_ON)
  if(errorId != FBLCW_E_NO_ERROR){
    FblCw_Det_ReportError(FBLCW_APIID_TPTXCONFIRMATION, (errorId));
  }
#endif

  FBLCW_DUMMY_STATEMENT(id);
}

#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

FUNC(void, FBLCW_CODE) FBLCW_APPLCANTIMERSTART(FBLCW_CAN_CHANNEL_CANTYPE_FIRST uint8 source){
  cwCanHardwareLoopTimer = FBLCW_CAN_HARDWARE_LOOP_TIMEOUT;

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  FBLCW_DUMMY_STATEMENT(Controller);
#endif
  FBLCW_DUMMY_STATEMENT(source);
}

FUNC(Can_ReturnType, FBLCW_CODE) FBLCW_APPLCANTIMERLOOP(FBLCW_CAN_CHANNEL_CANTYPE_FIRST uint8 source){
  Can_ReturnType result = CAN_OK;

  if(0u != cwCanHardwareLoopTimer){
    if(FBL_NO_TRIGGER != FblLookForWatchdog()){
      cwCanHardwareLoopTimer--;
    }
  }

  if(0u == cwCanHardwareLoopTimer){
    result = CAN_NOT_OK;
  }
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  FBLCW_DUMMY_STATEMENT(Controller);
#endif
  FBLCW_DUMMY_STATEMENT(source);
  return result;
}

FUNC(void, FBLCW_CODE) FBLCW_APPLCANTIMEREND(FBLCW_CAN_CHANNEL_CANTYPE_FIRST uint8 source){
  cwCanHardwareLoopTimer = 0u;
#if defined( C_MULTIPLE_RECEIVE_CHANNEL )
  FBLCW_DUMMY_STATEMENT(Controller);
#endif
  FBLCW_DUMMY_STATEMENT(source);
}

FUNC(void, FBLCW_CODE) FblCw_ControllerBusOff(uint8 controllerId){
  ApplFblCanBusOff();
  FBLCW_DUMMY_STATEMENT(controllerId);
}

FUNC(void, FBLCW_CODE) FblCw_ControllerModeIndication(uint8 controllerId, CanIf_ControllerModeType controllerMode){
#if( FBLCW_MODULE_CANSM == STD_ON )
  CanSM_ControllerModeIndication(controllerId, controllerMode);
#else
  FBLCW_DUMMY_STATEMENT(controllerId);
  FBLCW_DUMMY_STATEMENT(controllerMode);

#endif
}

FUNC(void, FBLCW_CODE) FblCw_CheckTransceiverWakeFlagIndication(uint8 transceiverId){
  FBLCW_DUMMY_STATEMENT(transceiverId);

}

FUNC(void, FBLCW_CODE) FblCw_ClearTrcvWufFlagIndication(uint8 transceiverId){
  FBLCW_DUMMY_STATEMENT(transceiverId);

}

FUNC(void, FBLCW_CODE) FblCw_ConfirmPnAvailability(uint8 transceiverId){
  FBLCW_DUMMY_STATEMENT(transceiverId);

}

FUNC(void, FBLCW_CODE) FblCw_TransceiverModeIndication(uint8 transceiverId, CanTrcv_TrcvModeType transceiverMode){
  FBLCW_DUMMY_STATEMENT(transceiverId);
  FBLCW_DUMMY_STATEMENT(transceiverMode);

}
#endif

#if(FBLCW_CHANGE_PARAMETER == STD_ON)
#if( FBLCW_EXISTS_CAN_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_OFF )
#error "Error in CanTp_cfg.h: Feature is supported for CAN only"
#endif
#if(CANTP_ENABLE_READ_PARAM == STD_OFF)
#error "Error in CanTp_cfg.h: Read parameter API must be enabled"
#endif
#endif

#if(FBLCW_CHANGE_PARAMETER == STD_ON)

FUNC(tFblResult, FBLCW_CODE) FblCw_ChangeParameter(TPParameterType parameter, uint16 value){
  FblCw_ParameterInfoIterType parameterInfoIdx;
  Std_ReturnType result;

  result = kFblFailed;

  parameterInfoIdx = FblCw_GetParameterInfoIdxOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]);
  if(PduR_DcmChangeParameter(FblCw_GetPduRIdOfParameterInfo(parameterInfoIdx), parameter, value) == E_OK){
    result = kFblOk;
  }

  return result;
}

FUNC(tFblResult, FBLCW_CODE) FblCw_ResetParameter(void){
  FblCw_DcmDslConnectionInfoIterType dcmDslConnectionInfoIdx;
  for(dcmDslConnectionInfoIdx = 0u; dcmDslConnectionInfoIdx < FblCw_GetSizeOfDcmDslConnectionInfo(); dcmDslConnectionInfoIdx++){
    if(FblCw_IsParameterInfoUsedOfDcmDslConnectionInfo(dcmDslConnectionInfoIdx)){
      FblCw_ParameterInfoIterType parameterInfoIdx;
      parameterInfoIdx = FblCw_GetParameterInfoIdxOfDcmDslConnectionInfo(dcmDslConnectionInfoIdx);

      (void) CanTp_ChangeParameter(FblCw_GetCanTpIdOfParameterInfo(parameterInfoIdx), TP_BS, FblCw_GetInitialBS(parameterInfoIdx));
      (void) CanTp_ChangeParameter(FblCw_GetCanTpIdOfParameterInfo(parameterInfoIdx), TP_STMIN, FblCw_GetInitialSTmin(parameterInfoIdx));
    }
  }
  return kFblOk;
}

FUNC(tFblResult, FBLCW_CODE) FblCw_ReadParameter(TPParameterType parameter, uint16 * value){
  tFblResult result;
  FblCw_ParameterInfoIterType parameterInfoIdx;

  result = kFblFailed;
  parameterInfoIdx = FblCw_GetParameterInfoIdxOfDcmDslConnectionInfo(activeConnection[FBL_CW_MAIN_REQUEST_INDEX]);

  if(CanTp_ReadParameter(FblCw_GetCanTpIdOfParameterInfo(parameterInfoIdx), parameter, value) == E_OK){
    result = kFblOk;
  }

  return result;
}
#endif

#if( FBLCW_MODULE_FRSM == STD_ON )
#if( FRIF_CUSTOM_JLE_SCHEDULING == STD_ON )

static void FrIf_CustomJLEHandling(void){
  uint8 ClusterIdx;
  boolean isLastFrIfRxTaskForTp[FrIf_CommonMaxNumberOfClusters];

  for(ClusterIdx = 0u; ClusterIdx < FrIf_CommonMaxNumberOfClusters; ClusterIdx++){
      isLastFrIfRxTaskForTp[ClusterIdx] = FALSE;
  }

  for(ClusterIdx = 0u; ClusterIdx < FrIf_CommonMaxNumberOfClusters; ClusterIdx++){
    if(TRUE == JLETimerEnabled[ClusterIdx]){
      uint8 cycle;
      uint16 macroTicks;
      if(E_OK == FrIf_GetGlobalTime(ClusterIdx, &cycle, &macroTicks))
      {
        sint8_least diffCycle = (sint8_least) ((vuint8) ((JLETimerCycle[ClusterIdx] + 64) - cycle) & 63);
        if(32 < diffCycle)
        {
          diffCycle -= 64;
        }
        if(((0 == diffCycle) && (JLETimerOffset[ClusterIdx] <= macroTicks)) || (0 > diffCycle))
        {
#if( FBLCW_MODULE_FRNM == STD_ON )
          boolean isLastFrIfRxTaskForNm = FrIf_IsLastFrIfRxTaskForNm(ClusterIdx);
#endif
          isLastFrIfRxTaskForTp[ClusterIdx] = FrIf_IsLastFrIfRxTaskForTp(ClusterIdx);

#if( FRIF_CTRL_ENABLE_API_OPTIMIZATION == STD_ON )
          FrIf_JobListExec();
#else
          FrIf_JobListExec(ClusterIdx);
#endif

#if( FBLCW_MODULE_FRNM == STD_ON )
          if(TRUE == isLastFrIfRxTaskForNm)
          {
            FrNm_MainFunction_0();
          }
#endif

        }
      }
    }
  }

  if(TRUE == isLastFrIfRxTaskForTp[0u]){
    FrTp_MainFunction();
  }
}

FUNC(void, FRIF_CODE) FrIf_Enable_JLE_Timer(vuint8 ClusterIdx){
  JLETimerEnabled[ClusterIdx] = TRUE;
}

FUNC(void, FRIF_CODE) FrIf_Disable_JLE_Timer(vuint8 ClusterIdx){
  JLETimerEnabled[ClusterIdx] = FALSE;
}

FUNC(Std_ReturnType, FRIF_CODE) FrIf_Set_JLE_Timer(vuint8 ClusterIdx, vuint8 Cycle, vuint16 MacrotickOffset, vuint8 RepeatJLE){
  JLETimerCycle[ClusterIdx] = Cycle;
  JLETimerOffset[ClusterIdx] = MacrotickOffset;
  FBLCW_DUMMY_STATEMENT(RepeatJLE);
  return E_OK;
}
#endif

FUNC(void, BSWM_CODE) BswM_FrSM_CurrentState(NetworkHandleType Network, FrSM_BswM_StateType CurrentState){
#if( FBLCW_KEY_SLOT_MODE == STD_ON )
  vuintx i;
  const FrSM_ClusterConfigType * FrSM_ClusterConfigPtr = FrSM_GetClusterConfigOfPCConfig();

  for(i = 0; i < FrSM_GetSizeOfClusterConfigOfPCConfig(); i++){
    if(FrSM_ClusterConfigPtr[i].NetworkHandleOfClusterConfig == Network){
      break;
    }
  }
  if((FrSM_GetFrIfClusterIndexOfClusterConfig(i) == FBLCW_FRIF_MAIN_NETWORK) && (FRSM_BSWM_ONLINE != CurrentState)){
    cwAllSlots = FBL_CW_KEY_SLOT_MODE;
  }
#endif

  FBLCW_DUMMY_STATEMENT(Network);
  FBLCW_DUMMY_STATEMENT(CurrentState);
}

#if( FBLCW_KEY_SLOT_MODE == STD_ON )

static void FblCwCheckNwStatus(void){
  vuint8 localRxBuffer[FBLCW_NW_STATUS_RX_BUFFER_SIZE];
  vuint8 rxLen;
  Fr_RxLPduStatusType rxStatus;
  tCwNwStatus nwStatus;
  Std_ReturnType ret;
  Fr_POCStatusType pocStatus;

  rxLen = sizeof(localRxBuffer);
  rxStatus = FR_NOT_RECEIVED;
  pocStatus.State = FR_POCSTATE_CONFIG;

  ret = FrIf_GetPOCStatus(FBLCW_FR_CONTROLLER_IDX_MAIN_NETWORK, &pocStatus);

  if((E_OK == ret) && (FR_POCSTATE_NORMAL_ACTIVE == pocStatus.State)){
    ret = Fr_ReceiveRxLPdu(FBLCW_FR_CONTROLLER_IDX_MAIN_NETWORK, FBLCW_NW_STATUS_PDU, localRxBuffer, &rxStatus, &rxLen);
  }

  if((E_OK == ret) && (FR_RECEIVED == rxStatus)){
    nwStatus = ((vuint16) localRxBuffer[0u] << 8u) | (vuint16) localRxBuffer[1u];

    if(FBL_CW_ALL_SLOT_MODE == cwAllSlots){
      if(FBL_CW_NW_STATUS_BOOT == nwStatus)
      {
        ResetTesterTimeout();
      }

      else if(FBL_CW_NW_STATUS_NORMAL == nwStatus)
      {
        if(kApplValid == ApplFblIsValidApp())
        {
          FblBmSetApplStartMagicFlag();
          FblCwShutdownRequest(kFblCwResetEcuRegularCase);
        }
      }
      else
      {
        FblCwShutdownRequest(kFblCwResetEcuRegularCase);
      }
    }
    else{
      if(FBL_CW_NW_STATUS_BOOT == nwStatus)
      {
        if(E_OK == FrIf_AllSlots(FBLCW_FRIF_MAIN_NETWORK))
        {
          cwAllSlots = FBL_CW_ALL_SLOT_MODE;
        }
      }
      else
      {
        if(kApplValid == ApplFblIsValidApp())
        {
          FblBmSetApplStartMagicFlag();
          FblCwShutdownRequest(kFblCwResetEcuRegularCase);
        }
      }
    }
  }
  else{
    if(FBL_CW_KEY_SLOT_MODE == cwAllSlots){
      if(cwNwStatusTimeoutCtr > cwNwStatusTimeout)
      {
        if(kApplValid == ApplFblIsValidApp())
        {
          FblBmSetApplStartMagicFlag();
          FblCwShutdownRequest(kFblCwResetEcuRegularCase);
        }
        else
        {
          cwNwStatusTimeoutCtr = 0u;
        }
      }
    }
  }
}
#endif
#endif

#if( FBLCW_EXISTS_ETH_BUSTYPEOFDCMDSLCONNECTIONINFO == STD_ON )

void FblCwPduShutdownRequest(void){
  cwShutdownState = kFblCwShutdownRequested;
  cwShutdownTimer = kFblCwShutdownWaitTime;
}
#endif

#if( FBLCW_MODULE_COMM == STD_ON )

FUNC(void, FBLCW_CODE) Dcm_ComM_NoComModeEntered(NetworkHandleType channel){
  cwComMChannelIsOnline[channel] = FALSE;
  ApplFbl_ComM_NoComModeEntered(channel);
}

FUNC(void, FBLCW_CODE) Dcm_ComM_SilentComModeEntered(NetworkHandleType channel){
  cwComMChannelIsOnline[channel] = FALSE;
  ApplFbl_ComM_SilentComModeEntered(channel);
}

FUNC(void, FBLCW_CODE) Dcm_ComM_FullComModeEntered(NetworkHandleType channel){
  cwComMChannelIsOnline[channel] = TRUE;
  ApplFbl_ComM_FullComModeEntered(channel);
}
#endif

#define FBLCW_STOP_SEC_CODE
#include "MemMap.hpp"

