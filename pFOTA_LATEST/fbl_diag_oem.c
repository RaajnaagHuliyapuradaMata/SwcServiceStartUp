#include "fbl_inc.hpp"
#include "fbl_diag_core.hpp"
#include "version.hpp"
#include "ProductionFlashInterfaceX.hpp"
#include "SUPPLIER1_CustomFunctions.hpp"
#include "EcuabFee_FblBlockInterface.hpp"
#include "LibAutosar_Crc.hpp"
#include "hmac_sha2.hpp"
#include "infSwcServicePduRCddCom.hpp"

#if((FBLDIAG_14229_UDS2_VERSION != 0x0801u) || \
     (FBLDIAG_14229_UDS2_RELEASE_VERSION != 0x00u))
# error "Error in fbl_diag_oem.c: Source and header file are inconsistent!"
#endif
#if(( FBLDIAG_14229_UDS2_VERSION != _FBLDIAG_OEM_VERSION ) || \
    ( FBLDIAG_14229_UDS2_RELEASE_VERSION != _FBLDIAG_OEM_RELEASE_VERSION ))
# error "Error in fbl_diag_oem.c: Source and v_ver.h are inconsistent!"
#endif

#if defined( FBL_DIAG_ENABLE_FLASHDRV_ROM )

typedef struct tagFlashDriverInitData
{
   V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3 * sourceBuffer;
   V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * destBuffer;
   vuint32 copySize;
   vuint8 decryptValue;
}tFlashDriverInitData;
#endif

#if defined( FBL_DIAG_FLASH_CODE_BASE_ADDR )

#else
#define FBL_DIAG_FLASH_CODE_BASE_ADDR    ((tFblAddress)flashCode)
#endif

#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )

#define FBL_DIAG_RESPONSE_BUFFER_SIZE FBL_DIAG_BUFFER_LENGTH
#else

#define FBL_DIAG_RESPONSE_BUFFER_SIZE ((((FBL_DIAG_SEGMENT_SIZE - 1u) ^ 0xFFFFFFFFu) & (FBL_DIAG_BUFFER_LENGTH - 2u)) + 2u)
#endif

#if( FBL_DIAG_RESPONSE_BUFFER_SIZE >= 0x1000000u )
#define FBL_DIAG_RESPONSE_BUFFER_LFI 4u
#elif( FBL_DIAG_RESPONSE_BUFFER_SIZE >= 0x10000u )
#define FBL_DIAG_RESPONSE_BUFFER_LFI 3u
#else
#define FBL_DIAG_RESPONSE_BUFFER_LFI 2u
#endif

#define FblDiagSetSecurityKeyAllowed()    SetFblDiagState( kFblDiagStateSecurityKeyAllowed )
#define FblDiagClrSecurityKeyAllowed()    ClrFblDiagState( kFblDiagStateSecurityKeyAllowed )
#define FblDiagSetSecurityUnlock()        SetFblDiagState( kFblDiagStateSecurityUnlock )
#define FblDiagClrSecurityUnlock()        ClrFblDiagState( kFblDiagStateSecurityUnlock )
#define FblDiagSetFingerprintValid()      SetFblDiagState( kFblDiagStateFingerprintValid )
#define FblDiagClrFingerprintValid()      ClrFblDiagState( kFblDiagStateFingerprintValid )
#define FblDiagSetEraseSucceeded()        SetFblDiagState( kFblDiagStateEraseSucceeded )
#define FblDiagClrEraseSucceeded()        ClrFblDiagState( kFblDiagStateEraseSucceeded )
#define FblDiagSetTransferDataAllowed()   SetFblDiagState( kFblDiagStateTransferDataAllowed )
#define FblDiagClrTransferDataAllowed()   ClrFblDiagState( kFblDiagStateTransferDataAllowed )
#define FblDiagSetTransferDataSucceeded() SetFblDiagState( kFblDiagStateTransferDataSucceeded )
#define FblDiagClrTransferDataSucceeded() ClrFblDiagState( kFblDiagStateTransferDataSucceeded )
#define FblDiagSetChecksumAllowed()       SetFblDiagState( kFblDiagStateChecksumAllowed )
#define FblDiagClrChecksumAllowed()       ClrFblDiagState( kFblDiagStateChecksumAllowed )
#define FblDiagSetFlashDriverPresent()    SetFblDiagState( kFblDiagStateFlashDriverPresent )
#define FblDiagClrFlashDriverPresent()    ClrFblDiagState( kFblDiagStateFlashDriverPresent )
#define FblDiagSetDownloadRunning()       SetFblDiagState( kFblDiagStateDownloadRunning )
#define FblDiagClrDownloadRunning()       ClrFblDiagState( kFblDiagStateDownloadRunning )

#define kDiagInitSequenceNum     ((vuint8) 0x01u)

#if defined( FBL_DIAG_ENABLE_FLASHDRV_ROM )
#if !defined( FLASH_DRIVER_INIT_DATA )

#define FLASH_DRIVER_INIT_DATA {{flashDrvBlk0, flashCode, FLASHDRV_BLOCK0_LENGTH, FLASHDRV_DECRYPTVALUE}}
#endif
#endif

static void FblDiagSessionControlParamInit(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);

vuint8 FblDiagDownloadCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);

static tFblResult FblDiagEraseBlock( V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 *pBlockDescriptor );

static tFblResult FblDiagCheckErasePreconditionsCustom( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pbDiagData
   ,                                                       V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 ucDynamicLength
   ,                                                       V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * pEraseAddress
   ,                                                       V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * pEraseLength);

static tFblResult FblDiagCheckProgAttemptCounter(V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 *pBlockDescriptor);
static tFblResult FblDiagPrepareFlashDriver(void);

static tFblResult FblDiagCheckRequestDownloadPreconditions(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pbDiagData
   ,                                                          V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo);
#if defined( FBL_DIAG_ENABLE_FLASHDRV_DOWNLOAD )
static tFblResult FblDiagCheckForFlashDriverDownload(V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo);
static tFblResult FblDiagCheckFlashDriverDownload(V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo);
#endif
static tFblResult FblDiagCheckFlashMemoryDownload(V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo);
static tFblResult FblDiagPrepareFirstDownloadSegment(V_MEMRAM1 tFblMemBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo
   ,                                                    V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo
   ,                                                    vuint8 tempBlockNr);
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
static tFblResult FblDiagInitDeltaDownload(V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo);
#endif

static tFblResult FblDiagProcessSubfunctionNrc(vuint32 serviceErrorMask);
static tFblResult FblDiagProcessServiceNrc(vuint32 serviceErrorMask);
static tFblResult FblDiagProcessRoutineNrc(vuint32 serviceErrorMask);
static tFblResult FblDiagDefaultSessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagExtendedSessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagProgrammingSessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
#ifdef SMART_TESTER_JUMP_IN
  static tFblResult FblDiagSUPPLIER1SessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
#endif
static tFblResult FblDiagTesterPresentMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagEcuResetMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagDataByIdLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagReadDataByIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWriteDataByIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiModuleToProgramMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiFingerprintAppMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiManufSupportMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiVinMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiEcuSerialnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiBoardSerialnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiEcuPartnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiBoardPartnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiAuxIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagWdbiModeIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagSecAccessSeedMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagSecAccessKeyMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagCommCtrlMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagControlDTCMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);

#if defined( FBL_DIAG_ENABLE_CHECK_PROGRAMMING_PRECONDITIONS )
static tFblResult FblDiagRCStartCheckProgPreCondMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
#endif

static tFblResult FblDiagRCStartEraseLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRCStartEraseMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRCStartApplicationHwidCheckMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRCStartCompareAndStoreSignatureMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRCStartLoadSecurityKeyMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRCStartInitGenealogyBlockMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRCStartCheckValidModuleMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRCStartSecretServiceMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRequestDownloadLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagRequestDownloadMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagTransferDataLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagTransferDataMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagReqTransferExitMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
static tFblResult FblDiagDefaultPreHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);

#if defined( FBL_DIAG_ENABLE_FLASHDRV_ROM )
V_MEMROM0 static V_MEMROM1 tFlashDriverInitData V_MEMROM2 kFlashDriverInitData[] = FLASH_DRIVER_INIT_DATA;
#endif

V_MEMRAM0 static V_MEMRAM1 vuint8               V_MEMRAM2      currentSequenceCnt;
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
V_MEMRAM0 static V_MEMRAM1 vuint8               V_MEMRAM2      secSendKeyInvalid;
#endif

V_MEMRAM0 static V_MEMRAM1 SecM_VerifyParamType       V_MEMRAM2 verifyParam;

V_MEMRAM0 static V_MEMRAM1 FL_SegmentInfoType         V_MEMRAM2 downloadSegments[SWM_DATA_MAX_NOAR];
#if defined( FBL_MEM_ENABLE_VERIFY_PIPELINED )
V_MEMRAM0 static V_MEMRAM1 SecM_SignatureParamType    V_MEMRAM2 pipeSigParam;
V_MEMRAM0 static V_MEMRAM1 vuint32                    V_MEMRAM2 pipeSigDataLength;
#endif

V_MEMRAM0 static V_MEMRAM1 tBlockDescriptor     V_MEMRAM2      downloadBlockDescriptor;
V_MEMRAM0 static V_MEMRAM1 tFblLength           V_MEMRAM2      transferRemainder;
V_MEMRAM0 static V_MEMRAM1 vuint8               V_MEMRAM2      expectedSequenceCnt;

static uint32 ulMemEraseStartAddress;
static uint32 ulMemEraseLength;

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableDsc_DefaultSession[] = { kDiagSubDefaultSession };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableDsc_ProgSession[] = { kDiagSubProgrammingSession };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableDsc_ExtendedSession[] = { kDiagSubExtendedDiagSession };

#ifdef SMART_TESTER_JUMP_IN
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableDsc_SUPPLIER1Session[] = { kDiagSubSUPPLIER1DiagSession };
#endif

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableSessionControl[] =
{
   {
      kFblDiagSubtableDsc_DefaultSession
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlDiagnosticSessionControl
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagDefaultSessionMainHandler
   },

   {
      kFblDiagSubtableDsc_ProgSession
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlDiagnosticSessionControl
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagProgrammingSessionMainHandler
   },

   {
      kFblDiagSubtableDsc_ExtendedSession
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlDiagnosticSessionControl
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagExtendedSessionMainHandler
   }

#ifdef SMART_TESTER_JUMP_IN
   
   ,  {
      kFblDiagSubtableDsc_SUPPLIER1Session
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlDiagnosticSessionControl
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagSUPPLIER1SessionMainHandler
   }
#endif
};

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableEcuReset_HardReset[] = { kDiagSubHardReset };

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableEcuReset[] =
{
   {
      kFblDiagSubtableEcuReset_HardReset
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlEcuReset
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagEcuResetMainHandler
   }
};

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableSecAccess_Seed[] = { kFblDiagSubRequestSeed };

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableSecAccess_Key[] = { kFblDiagSubSendKey };

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableSecAccess[] =
{
   {
      kFblDiagSubtableSecAccess_Seed
   ,     (kFblDiagOptionSessionProgramming)
   ,     kDiagRqlSecurityAccessSeed
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagSecAccessSeedMainHandler
   },

   {
      kFblDiagSubtableSecAccess_Key
   ,     (kFblDiagOptionSessionProgramming)
   ,     kDiagRqlSecurityAccessKey
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagSecAccessKeyMainHandler
   }
};

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableCommControl_EnRxEnTx[] = { kDiagSubEnableRxAndTx };

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableCommControl_Disable[] = { FBL_DIAG_COMMUNICATION_CONTROL_TYPE };

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableCommControl[] =
{
   {
      kFblDiagSubtableCommControl_EnRxEnTx
   ,     (kFblDiagOptionSessionExtended | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlCommunicationControl
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagCommCtrlMainHandler
   },

   {
      kFblDiagSubtableCommControl_Disable
   ,     (kFblDiagOptionSessionExtended | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlCommunicationControl
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagCommCtrlMainHandler
   }
};

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableRC_StartErase[] = { kDiagSubStartRoutine, kDiagRoutineIdEraseMemoryHigh, kDiagRoutineIdEraseMemoryLow };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableRC_ApplicationHwidCheck[] = { kDiagSubStartRoutine, kDiagRoutineIdAppHwidCheckHigh, kDiagRoutineIdAppHwidCheckLow };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableRC_CompareAndStoreSignature[] = { kDiagSubStartRoutine, kDiagRoutineIdCompAndStoreSignatureHigh, kDiagRoutineIdCompAndStoreSignatureLow };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableRC_CheckValidModule[] = { kDiagSubStartRoutine, kDiagRoutineIdCheckValidModuleHigh, kDiagRoutineIdCheckValidModuleLow };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableRC_InitGenealogyBlock[] = { kDiagSubStartRoutine, kDiagRoutineIdInitGenealogyBlockHigh, kDiagRoutineIdInitGenealogyBlockLow };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableRC_LoadSecurityKey[] = { kDiagSubStartRoutine, kDiagRoutineIdLoadSecurityKeyHigh, kDiagRoutineIdLoadSecurityKeyLow };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableRC_SecretService[] = { kDiagSubStartRoutine, kDiagRoutineIdSecretServiceHigh, kDiagRoutineIdSecretServiceLow };

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableRoutine[] =
{
#if defined( FBL_DIAG_ENABLE_CHECK_PROGRAMMING_PRECONDITIONS )
  {
      kFblDiagSubtableRC_StartProgPreCond
   ,     (kFblDiagOptionSessionExtended | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlRoutineControlProgPreCond
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagRCStartCheckProgPreCondMainHandler
   },
#endif
   {
      kFblDiagSubtableRC_StartErase
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRoutineControlEraseRoutine
   ,     FblDiagRCStartEraseLengthCheck
   ,     FblDiagRCStartEraseMainHandler
   }
   ,  {
      kFblDiagSubtableRC_ApplicationHwidCheck
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRoutineControlAppHwidCheck
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagRCStartApplicationHwidCheckMainHandler
   }
   ,  {
      kFblDiagSubtableRC_CompareAndStoreSignature
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRoutineControlCompAndStoreSig
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagRCStartCompareAndStoreSignatureMainHandler
   }
   ,  {
      kFblDiagSubtableRC_CheckValidModule
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRoutineControlCheckValidModule
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagRCStartCheckValidModuleMainHandler
   }
   ,  {
      kFblDiagSubtableRC_InitGenealogyBlock
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRoutineControlInitGenealogyBlock
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagRCStartInitGenealogyBlockMainHandler
   }
   ,  {
      kFblDiagSubtableRC_LoadSecurityKey
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRoutineControlLoadSecurityKey
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagRCStartLoadSecurityKeyMainHandler
   }
   ,  {
      kFblDiagSubtableRC_SecretService
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming)
   ,     kDiagRqlRoutineControlSecretService
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagRCStartSecretServiceMainHandler
   }
};

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableTesterPresent_ZeroSubfunction[] = { kDiagSubTesterPresent };

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableTesterPresent[] =
{
   {
      kFblDiagSubtableTesterPresent_ZeroSubfunction
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlTesterPresent
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagTesterPresentMainHandler
   }
};

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableControlDtc_OnSubfunction[] = { kDiagSubDtcOn };
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableControlDtc_OffSubfunction[] = { kDiagSubDtcOff };

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableControlDtc[] =
{
   {
      kFblDiagSubtableControlDtc_OnSubfunction
   ,     (kFblDiagOptionSessionExtended | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlControlDTCSetting
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagControlDTCMainHandler
   }
   ,  {
      kFblDiagSubtableControlDtc_OffSubfunction
   ,     (kFblDiagOptionSessionExtended | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlControlDTCSetting
   ,     (tFblDiagLengthCheck)0u
   ,     FblDiagControlDTCMainHandler
   }
};

V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_ModuleToProgram  [] = {GET_ID_HIGH(cCustSubFuncModuleToProgram),   GET_ID_LOW(cCustSubFuncModuleToProgram)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_BoardPartnumber  [] = {GET_ID_HIGH(cCustSubFuncBoardPartnumber),   GET_ID_LOW(cCustSubFuncBoardPartnumber)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_BoardSerialnumber[] = {GET_ID_HIGH(cCustSubFuncBoardSerialnumber), GET_ID_LOW(cCustSubFuncBoardSerialnumber)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_EcuPartnumber    [] = {GET_ID_HIGH(cCustSubFuncEcuPartnumber),     GET_ID_LOW(cCustSubFuncEcuPartnumber)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_EcuSerialnumber  [] = {GET_ID_HIGH(cCustSubFuncEcuSerialnumber),   GET_ID_LOW(cCustSubFuncEcuSerialnumber)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_ManufSupport     [] = {GET_ID_HIGH(cCustSubFuncManufSupport),      GET_ID_LOW(cCustSubFuncManufSupport)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_Vin              [] = {GET_ID_HIGH(cCustSubFuncVin),               GET_ID_LOW(cCustSubFuncVin)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_FingerprintApp   [] = {GET_ID_HIGH(cCustSubFuncFingerprintApp),    GET_ID_LOW(cCustSubFuncFingerprintApp)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_ModeId           [] = {GET_ID_HIGH(cCustSubFuncModeId),            GET_ID_LOW(cCustSubFuncModeId)};
V_MEMROM0 static V_MEMROM1 vuint8 V_MEMROM2 kFblDiagSubtableWdbi_AuxId            [] = {GET_ID_HIGH(cCustSubFuncAuxId),             GET_ID_LOW(cCustSubFuncAuxId)};

V_MEMROM0 static V_MEMROM1 tFblDiagServiceSubTable V_MEMROM2 kFblDiagSubtableWdbi[] =
{
  {
    kFblDiagSubtableWdbi_ModuleToProgram
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenModuleToProgram)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiModuleToProgramMainHandler
  },

  {
    kFblDiagSubtableWdbi_BoardPartnumber
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenBoardPartnumber)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiBoardPartnumberMainHandler
  },

  {
    kFblDiagSubtableWdbi_BoardSerialnumber
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenBoardSerialnumber)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiBoardSerialnumberMainHandler
  },

  {
    kFblDiagSubtableWdbi_EcuPartnumber
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenEcuPartnumber)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiEcuPartnumberMainHandler
  },

  {
    kFblDiagSubtableWdbi_EcuSerialnumber
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenEcuSerialnumber)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiEcuSerialnumberMainHandler
  },

  {
    kFblDiagSubtableWdbi_ManufSupport
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenManufSupport)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiManufSupportMainHandler
  },

  {
    kFblDiagSubtableWdbi_Vin
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenVin)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiVinMainHandler
  },

  {
    kFblDiagSubtableWdbi_FingerprintApp
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenFingerprintApp)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiFingerprintAppMainHandler
  },

  {
    kFblDiagSubtableWdbi_ModeId
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenModeId)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiModeIdMainHandler
  },

  {
    kFblDiagSubtableWdbi_AuxId
   ,   (kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,   (2 + cDiagDataLenAuxId)
   ,   (tFblDiagLengthCheck)0u
   ,   FblDiagWdbiAuxIdMainHandler
  }
};

V_MEMROM0 V_MEMROM1 tFblDiagServiceTable V_MEMROM2 kFblDiagServiceTable[] =
{
   {
      kDiagSidDiagnosticSessionControl
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionServiceIsSubfunction | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlDiagnosticSessionControl
   ,     (tFblDiagLengthCheck)0u
   ,     ARRAY_SIZE(kFblDiagSubtableSessionControl)
   ,     ARRAY_SIZE(kFblDiagSubtableDsc_DefaultSession)
   ,     kFblDiagSubtableSessionControl
   ,     FblDiagDefaultPreHandler
   ,     (tFblDiagMainHandler)0u
   ,     FblDiagProcessSubfunctionNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidEcuReset
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionServiceIsSubfunction | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlEcuReset
   ,     (tFblDiagLengthCheck)0u
   ,     ARRAY_SIZE(kFblDiagSubtableEcuReset)
   ,     ARRAY_SIZE(kFblDiagSubtableEcuReset_HardReset)
   ,     kFblDiagSubtableEcuReset
   ,     FblDiagDefaultPreHandler
   ,     (tFblDiagMainHandler)0u
   ,     FblDiagProcessSubfunctionNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidReadDataByIdentifier
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlReadDataByIdentifier
   ,     FblDiagDataByIdLengthCheck
   ,     0u
   ,     0u
   ,     (tFblDiagServiceSubTable*)V_NULL
   ,     FblDiagDefaultPreHandler
   ,     FblDiagReadDataByIdMainHandler
   ,     FblDiagProcessServiceNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidSecurityAccess
   ,     (kFblDiagSecurityAccessSessionMask | kFblDiagOptionServiceIsSubfunction)
   ,     kDiagRqlServiceWithSubfunction
   ,     (tFblDiagLengthCheck)0u
   ,     ARRAY_SIZE(kFblDiagSubtableSecAccess)
   ,     ARRAY_SIZE(kFblDiagSubtableSecAccess_Seed)
   ,     kFblDiagSubtableSecAccess
   ,     FblDiagDefaultPreHandler
   ,     (tFblDiagMainHandler)0u
   ,     FblDiagProcessSubfunctionNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidCommunicationControl
   ,     (kFblDiagOptionSessionExtended | kFblDiagOptionServiceIsSubfunction | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlServiceWithSubfunction
   ,     (tFblDiagLengthCheck)0u
   ,     ARRAY_SIZE(kFblDiagSubtableCommControl)
   ,     ARRAY_SIZE(kFblDiagSubtableCommControl_EnRxEnTx)
   ,     kFblDiagSubtableCommControl
   ,     FblDiagDefaultPreHandler
   ,     (tFblDiagMainHandler)0u
   ,     FblDiagProcessSubfunctionNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidWriteDataByIdentifier
   ,     (kFblDiagOptionSessionProgramming | kFblDiagSecurityAccessSessionMask)
   ,     kDiagRqlWriteDataByIdentifier
   ,     FblDiagDataByIdLengthCheck
   ,     ARRAY_SIZE(kFblDiagSubtableWdbi)
   ,     ARRAY_SIZE(kFblDiagSubtableWdbi_ModuleToProgram)
   ,     kFblDiagSubtableWdbi
   ,     FblDiagDefaultPreHandler
   ,     FblDiagWriteDataByIdMainHandler
   ,     FblDiagProcessServiceNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidRoutineControl
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionServiceIsSubfunction | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlRoutineControl
   ,     (tFblDiagLengthCheck)0u
   ,     ARRAY_SIZE(kFblDiagSubtableRoutine)
   ,     ARRAY_SIZE(kFblDiagSubtableRC_StartErase)
   ,     kFblDiagSubtableRoutine
   ,     FblDiagDefaultPreHandler
   ,     (tFblDiagMainHandler)0u
   ,     FblDiagProcessRoutineNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidRequestDownload
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRequestDownload
   ,     FblDiagRequestDownloadLengthCheck
   ,     0u
   ,     0u
   ,     (tFblDiagServiceSubTable*)V_NULL
   ,     FblDiagDefaultPreHandler
   ,     FblDiagRequestDownloadMainHandler
   ,     FblDiagProcessServiceNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidTransferData
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlTransferData
   ,     FblDiagTransferDataLengthCheck
   ,     0u
   ,     0u
   ,     (tFblDiagServiceSubTable*)V_NULL
   ,     FblDiagDefaultPreHandler
   ,     FblDiagTransferDataMainHandler
   ,     FblDiagProcessServiceNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidRequestTransferExit
   ,     (kFblDiagOptionSessionProgramming | kFblDiagOptionSecuredService)
   ,     kDiagRqlRequestTransferExit
   ,     (tFblDiagLengthCheck)0u
   ,     0u
   ,     0u
   ,     (tFblDiagServiceSubTable*)V_NULL
   ,     FblDiagDefaultPreHandler
   ,     FblDiagReqTransferExitMainHandler
   ,     FblDiagProcessServiceNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidTesterPresent
   ,     (kFblDiagOptionSessionDefault | kFblDiagOptionSessionExtended | kFblDiagOptionSessionProgramming | kFblDiagOptionServiceIsSubfunction | kFblDiagOptionFunctionalRequest)
   ,     kDiagRqlTesterPresent
   ,     (tFblDiagLengthCheck)0u
   ,     ARRAY_SIZE(kFblDiagSubtableTesterPresent)
   ,     ARRAY_SIZE(kFblDiagSubtableTesterPresent_ZeroSubfunction)
   ,     kFblDiagSubtableTesterPresent
   ,     FblDiagDefaultPreHandler
   ,     (tFblDiagMainHandler)0u
   ,     FblDiagProcessSubfunctionNrc
   ,     FblDiagDefaultPostHandler
   }
   ,  {
      kDiagSidControlDTCSetting
   ,     (kFblDiagOptionSessionExtended | kFblDiagOptionFunctionalRequest | kFblDiagOptionServiceIsSubfunction)
   ,     kDiagRqlServiceWithSubfunction
   ,     (tFblDiagLengthCheck)0u
   ,     ARRAY_SIZE(kFblDiagSubtableControlDtc)
   ,     ARRAY_SIZE(kFblDiagSubtableControlDtc_OnSubfunction)
   ,     kFblDiagSubtableControlDtc
   ,     FblDiagDefaultPreHandler
   ,     (tFblDiagMainHandler)0u
   ,     FblDiagProcessSubfunctionNrc
   ,     FblDiagDefaultPostHandler
   }
};

V_MEMROM0 V_MEMROM1 vuintx V_MEMROM2 kSizeOfServiceTable = ARRAY_SIZE(kFblDiagServiceTable);

vuint8 FblDiagDownloadCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblMemBlockVerifyData verifyData;
   SecM_StatusType verifyErrorCode;
   vuint8 result;

#if defined( FBL_MEM_ENABLE_VERIFY_PIPELINED )
   verifyData.verifyDataPipe.length = diagReqDataLen - 3u;
   verifyData.verifyDataPipe.data = (V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *)&pbDiagData[kDiagLocFmtRoutineStatus];
#endif

#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
   verifyData.verifyDataOutput.length = diagReqDataLen - 3u;
   verifyData.verifyDataOutput.data = (V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *)&pbDiagData[kDiagLocFmtRoutineStatus];
#endif

   if(FblMemRemapStatus(FblMemBlockVerify(&verifyData, &verifyErrorCode)) != kFblMemStatus_Ok){
      result = kDiagCheckVerificationFailed;
   }
   else{
      result = kDiagCheckVerificationOk;
   }

   if(result == kDiagCheckVerificationOk){
      if(FblDiagGetTransferTypeFlash())
      {
         (void)FblRealTimeSupport();
#if defined( SEC_ENABLE_CRC_TOTAL )
         (void)ApplFblWriteCRCTotal(&downloadBlockDescriptor
   ,                                   (vuint32)verifyParam.blockStartAddress
   ,                                   (vuint32)verifyParam.blockLength
   ,                                   (vuint32)verifyParam.crcTotal
                                   );
#endif

         if(ApplFblValidateBlock(downloadBlockDescriptor) != kFblOk)
         {
            result = kDiagCheckVerificationFailed;
         }
         else
         {
            (void)ApplFblIncProgCounts(downloadBlockDescriptor);
         }
      }
#if defined( FBL_DIAG_ENABLE_FLASHDRV_DOWNLOAD )
      else
      {
         DiagExRCRResponsePending(kForceSendRpIfNotInProgress);

         FblDiagSetFlashDriverPresent();

         if(FblDiagPrepareFlashDriver() == kFblOk)
         {
            FblDiagSetTransferTypeFlash();
         }
         else
         {
            result = kDiagCheckVerificationFailed;
         }
      }
#endif
   }

   return result;
}

static tFblResult FblDiagEraseBlock( V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 *pBlockDescriptor ){
   tFblResult result;
   tFblMemBlockInfo blockInfo;

   result = FblLbtGetBlockDescriptorByNr(pBlockDescriptor->blockNr, pBlockDescriptor);

   if(result == kFblOk){
      blockInfo.targetAddress = pBlockDescriptor->blockStartAddress;
      blockInfo.targetLength = pBlockDescriptor->blockLength;
      blockInfo.logicalAddress = pBlockDescriptor->blockStartAddress;
      blockInfo.logicalLength = pBlockDescriptor->blockLength;

      if(FblMemRemapStatus(FblMemBlockEraseIndication(&blockInfo)) == kFblMemStatus_Ok)
      {
         FblDiagSetEraseSucceeded();

         (void)ApplFblAdjustLbtBlockData(&downloadBlockDescriptor);

         FblDiagSegmentInit();
      }
      else
      {
         result = kFblFailed;
      }
   }

   if(result != kFblOk){
      FblDiagClrEraseSucceeded();
   }

   return result;
}

static tFblResult FblDiagCheckErasePreconditionsCustom( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pbDiagData
   ,                                                       V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 ucDynamicLength
   ,                                                       V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * pEraseAddress
   ,                                                       V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * pEraseLength){
   tFblResult result;

   *pEraseAddress = 0u;
   *pEraseLength = 0u;

   if(FblDiagPrepareFlashDriver() != kFblOk){
      DiagNRCConditionsNotCorrect();
      result = kFblFailed;
   }
   else{
      if(ucDynamicLength == kDiagRqlRoutineControlEraseRoutine)
      {
        if(ulMemEraseLength == 0)
        {
          DiagNRCRequestSequenceError();
          result = kFblFailed;
        }

        else
        {
          *pEraseAddress = ulMemEraseStartAddress;
          *pEraseLength = ulMemEraseLength;
          ulMemEraseLength = 0;
          result = kFblOk;
        }
      }
      else
      {
         DiagNRCRequestOutOfRange();
         result = kFblFailed;
      }
   }

   return result;
}

static tFblResult FblDiagPrepareFlashDriver(void){
   tFblResult result;
   tFlashErrorCode flashErrorCode;
#if defined( FBL_DIAG_ENABLE_FLASHDRV_ROM )
   vuintx flashDriverIndex;
   vuint32 byteIndex;
   V_MEMROM1 tFlashDriverInitData V_MEMROM2 V_MEMROM3 * flashDriverInitData;
#endif

   result = kFblFailed;

   if(!FblDiagGetMemDriverInitialized()){
#if defined( FBL_DIAG_ENABLE_FLASHDRV_ROM )

      if(!FblDiagGetFlashDriverPresent())
      {
         for(flashDriverIndex = 0u; flashDriverIndex < ARRAY_SIZE(kFlashDriverInitData); flashDriverIndex++)
         {
            flashDriverInitData = &kFlashDriverInitData[flashDriverIndex];

            if(flashDriverInitData->copySize > FLASH_SIZE)
            {
               FblErrStatSetError(FBL_ERR_FLASHCODE_EXCEEDS_MEMORY);
               break;
            }

            for(byteIndex = 0u; byteIndex < flashDriverInitData->copySize; byteIndex++)
            {
               flashDriverInitData->destBuffer[byteIndex] = (flashDriverInitData->decryptValue ^ flashDriverInitData->sourceBuffer[byteIndex]);
               if((byteIndex & 0xFFu) == 0x00u)
               {
                  FblLookForWatchdogVoid();
               }
            }
         }

         if(flashDriverIndex == ARRAY_SIZE(kFlashDriverInitData))
         {
            FblDiagSetFlashDriverPresent();
         }
      }
#endif

      if(FblDiagGetFlashDriverPresent())
      {
         FblErrStatSetFlashDrvVersion();

         ApplFblSetVfp();

         FblCwSetOfflineMode();

         flashErrorCode = MemDriver_InitSync(V_NULL);
         FblCwSetOnlineMode();

         if(flashErrorCode == IO_E_OK)
         {
            FblDiagSetMemDriverInitialized();
            result = kFblOk;
         }
         else
         {
            FblErrStatSetError(FBL_ERR_FLASHCODE_INIT_FAILED);
            FblErrStatSetFlashDrvError(flashErrorCode);
         }
      }
   }
   else{
      result = kFblOk;
   }

   return result;
}

static tFblResult FblDiagCheckProgAttemptCounter(V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 *pBlockDescriptor){
   tFblResult result;
   vuint16 progAttempts;

   result = kFblOk;

   if(ApplFblGetProgAttempts(*pBlockDescriptor, &progAttempts) != kFblOk){
      progAttempts = 0u;
   }

   if(ApplFblGetPromMaxProgAttempts(pBlockDescriptor->blockNr) != 0u){
      if(progAttempts >= ApplFblGetPromMaxProgAttempts(pBlockDescriptor->blockNr))
      {
         FblErrStatSetError(FBL_ERR_FLASH_PROG_CONDITIONS);
         DiagNRCConditionsNotCorrect();
         result = kFblFailed;
      }
   }

   return result;
}

static tFblResult FblDiagCheckRequestDownloadPreconditions(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pbDiagData
   ,                                                          V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo){
   tFblResult result;

   vuint8  lengthFormat;
   vuint8  addrFormat;

   pSegmentInfo->logicalAddress = 0u;
   pSegmentInfo->logicalLength = 0u;
   pSegmentInfo->targetAddress = 0u;
   pSegmentInfo->targetLength = 0u;

   lengthFormat = (vuint8)((pbDiagData[kDiagLocFmtFormatOffset] & 0xF0u) >> 4u);
   addrFormat = (vuint8) (pbDiagData[kDiagLocFmtFormatOffset] & 0x0Fu);

   pSegmentInfo->dataFormat = (tFblMemDfi)pbDiagData[kDiagLocFmtSubparam];

   if((addrFormat == 0u) || (lengthFormat == 0u) || (addrFormat > 4u) || (lengthFormat > 4u)){
      DiagNRCRequestOutOfRange();
      result = kFblFailed;
   }
   else if((FblDiagGetTransferDataAllowed())){
      DiagNRCConditionsNotCorrect();
      result = kFblFailed;
   }
#if defined( FBL_ENABLE_DATA_PROCESSING )
#if defined( FBL_ENABLE_ENCRYPTION_MODE )
#else

   else if(FblDiagGetEncryptionMode(pSegmentInfo->dataFormat) != kDiagSubNoEncryption){
      DiagNRCRequestOutOfRange();
      result = kFblFailed;
   }
#endif
#if defined( FBL_ENABLE_COMPRESSION_MODE )
#else

   else if((FblDiagGetCompressionMode(pSegmentInfo->dataFormat) != kDiagSubNoCompression)
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
      && (!GetOemStreamModeSupported(pSegmentInfo->dataFormat))
#endif
      ){
      DiagNRCRequestOutOfRange();
      result = kFblFailed;
   }
#endif
#else
   else if((pSegmentInfo->dataFormat != kDiagSubNoDataProcessing)
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
      && (!GetOemStreamModeSupported(pSegmentInfo->dataFormat))
#endif
      ){
      DiagNRCRequestOutOfRange();
      result = kFblFailed;
   }
#endif
   else{
      pSegmentInfo->logicalAddress = FblMemGetInteger(addrFormat, &(pbDiagData[kDiagLocFmtAddrOffset]));

      pSegmentInfo->logicalLength = FblMemGetInteger(lengthFormat, &(pbDiagData[kDiagLocFmtAddrOffset + addrFormat]));

      result = kFblOk;
   }

   return result;
}

#if defined( FBL_DIAG_ENABLE_FLASHDRV_DOWNLOAD )

static tFblResult FblDiagCheckForFlashDriverDownload(V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo){
   tFblResult result;

   result = kFblOk;

#if defined( FLASHCODE_RELOCATABLE ) || \
     defined( FLASH_DRIVER_RELOCATABLE )

   if((pSegmentInfo->logicalAddress == 0u) && (!FblDiagGetEraseSucceeded()))
#else
   if(pSegmentInfo->logicalAddress == FBL_DIAG_FLASH_CODE_BASE_ADDR)
#endif
   {
      FblDiagClrFlashDriverPresent();

      if(FblDiagGetMemDriverInitialized())
      {
         DiagExRCRResponsePending(kForceSendRpIfNotInProgress);
         FblDiagClrMemDriverInitialized();
         (void)MemDriver_DeinitSync(V_NULL);
      }

      FblDiagClrTransferTypeFlash();
      pSegmentInfo->type = kFblMemType_RAM;

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
      if(GetOemStreamModeSupported(pSegmentInfo->dataFormat))
      {
         DiagNRCRequestOutOfRange();
         result = kFblFailed;
      }
#endif
   }
   else{
      FblDiagSetTransferTypeFlash();

      pSegmentInfo->type = kFblMemType_ROM;
   }

   return result;
}

static tFblResult FblDiagCheckFlashDriverDownload( V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo){
   tFblResult result;

#if defined( FLASHCODE_RELOCATABLE ) || \
    defined( FLASH_DRIVER_RELOCATABLE )
   pSegmentInfo->targetAddress = FBL_DIAG_FLASH_CODE_BASE_ADDR;
#else
   pSegmentInfo->targetAddress = pSegmentInfo->logicalAddress;
#endif

   pSegmentInfo->targetLength = pSegmentInfo->logicalLength;

   if(FblLbtCheckRangeContained(pSegmentInfo->targetAddress, pSegmentInfo->targetLength, FBL_DIAG_FLASH_CODE_BASE_ADDR, FLASH_SIZE) == kFblOk){
      FblDiagSegmentInit();

      (void)FblDiagSegmentNext();

      result = kFblOk;
   }
   else{
      FblErrStatSetError(FBL_ERR_FLASHCODE_EXCEEDS_MEMORY);
      DiagNRCRequestOutOfRange();

      result = kFblFailed;
   }

   downloadBlockDescriptor.blockNr = 0u;

   return result;
}
#endif

static tFblResult FblDiagCheckFlashMemoryDownload( V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo){
   FL_SegmentInfoType * segment;

   tFblResult result;

   result = kFblOk;

   if(!FblDiagGetMemDriverInitialized()){
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
      if(GetOemStreamModeSupported(pSegmentInfo->dataFormat))
      {
         if(FblDiagPrepareFlashDriver() != kFblOk)
         {
            DiagNRCConditionsNotCorrect();
            result = kFblFailed;
         }
      }
      else
#endif
      {
         DiagNRCUploadDownloadNotAccepted();
         result = kFblFailed;
      }
   }

   if(result == kFblOk){
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
      if(GetOemStreamModeSupported(pSegmentInfo->dataFormat))
      {
         result = FblDiagInitDeltaDownload(pSegmentInfo);
      }
      else
#endif
      {
         if((segmentCount == 0u) && (!FblDiagGetEraseSucceeded()))
         {
            DiagNRCUploadDownloadNotAccepted();
            result = kFblFailed;
         }

         else
         {
            if(  (FblLbtCheckRangeContained(pSegmentInfo->logicalAddress
   ,                                            pSegmentInfo->logicalLength
   ,                                            downloadBlockDescriptor.blockStartAddress
   ,                                            downloadBlockDescriptor.blockLength) != kFblOk)
               || (transferRemainder == 0u)
               )
            {
               FblErrStatSetError(FBL_ERR_LBT_ADDR_MISMATCH);
               DiagNRCRequestOutOfRange();
               result = kFblFailed;
            }
         }
      }
   }

   if(result == kFblOk){
      if(FblDiagSegmentNext() == kSwmOutOfRange)
      {
         FblErrStatSetError(FBL_ERR_TOO_MANY_SEGMENTS_IN_MODULE);
         DiagNRCRequestOutOfRange();
         result = kFblFailed;
      }
      else
      {
         pSegmentInfo->targetAddress = pSegmentInfo->logicalAddress;
         pSegmentInfo->targetLength = pSegmentInfo->logicalLength;

         if(segmentCount > 1u)
         {
            segment = &verifyParam.segmentList.segmentInfo[segmentCount - 2u];

            if(   (pSegmentInfo->targetAddress <= segment->transferredAddress)
                || ((pSegmentInfo->targetAddress - segment->transferredAddress) < segment->length)
               )
            {
               DiagNRCRequestOutOfRange();
               result = kFblFailed;
            }
         }
      }
   }

   return result;
}

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

static tFblResult FblDiagInitDeltaDownload(V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo){
   tFblResult result;

   result = kFblOk;

   if(FblLbtGetBlockDescriptorByAddressLength(pSegmentInfo->logicalAddress, pSegmentInfo->logicalLength, &downloadBlockDescriptor) != kFblOk){
      DiagNRCRequestOutOfRange();
      result = kFblFailed;
   }
   else{
      (void)ApplFblAdjustLbtBlockData(&downloadBlockDescriptor);

      if(ApplFblInvalidateBlock(downloadBlockDescriptor) != kFblOk)
      {
         DiagNRCConditionsNotCorrect();
         result = kFblFailed;
      }
      else
      {
         if(ApplFblErasePatternArea(&downloadBlockDescriptor) != kFblOk)
         {
            assertFblUser(DiagGetError() != kDiagErrorNone, kFblOemAssertNoNrcSet);
            result = kFblFailed;
         }
         else
         {
            FblDiagSegmentInit();
         }
      }
   }

   return result;

}
#endif

static tFblResult FblDiagPrepareFirstDownloadSegment(V_MEMRAM1 tFblMemBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo
   ,                                                    V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * pSegmentInfo
   ,                                                    vuint8 tempBlockNr){
   tFblResult result;
   tFblDiagNrc libMemResult;
   tExportFct exportFct;

   result = kFblOk;

#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
   if(result == kFblOk){
      result = FblLbtGetBlockVerifyOutputFuncByNr(tempBlockNr, &exportFct);
   }
   if(result == kFblOk){
      pBlockInfo->verifyRoutineOutput.function = (tFblMemVerifyFctOutput)exportFct;
      pBlockInfo->verifyRoutineOutput.param = (V_MEMRAM1 tFblMemVerifyParamOutput V_MEMRAM2 V_MEMRAM3 *)&verifyParam;
   }
#endif

#if defined( FBL_MEM_ENABLE_VERIFY_PIPELINED )
   if(result == kFblOk){
      result = FblLbtGetBlockVerifyPipelinedFuncByNr(tempBlockNr, &exportFct);
   }
   if(result == kFblOk){
      pBlockInfo->verifyRoutinePipe.function = (tFblMemVerifyFctInput)exportFct;
      pBlockInfo->verifyRoutinePipe.param = (V_MEMRAM1 tFblMemVerifyParamInput V_MEMRAM2 V_MEMRAM3 *)&pipeSigParam;

      pipeSigParam.currentHash.sigResultBuffer = (SecM_ResultBufferType)V_NULL;
      pipeSigParam.currentHash.length = 0u;
      pipeSigParam.currentDataLength = &pipeSigDataLength;
   }
#endif

   if(result == kFblOk){
      pBlockInfo->segmentList = &verifyParam.segmentList;
      pBlockInfo->maxSegments = SWM_DATA_MAX_NOAR;
      verifyParam.segmentList.segmentInfo = downloadSegments;

      if( FblDiagGetTransferTypeFlash())
      {
         pBlockInfo->targetAddress = downloadBlockDescriptor.blockStartAddress;
         pBlockInfo->targetLength = downloadBlockDescriptor.blockLength;
         pBlockInfo->logicalAddress = downloadBlockDescriptor.blockStartAddress;
         pBlockInfo->logicalLength = downloadBlockDescriptor.blockLength;

         pBlockInfo->readFct = (tFblMemVerifyReadFct)FblReadProm;
      }
#if defined( FBL_DIAG_ENABLE_FLASHDRV_DOWNLOAD )
      else
      {
         pBlockInfo->targetAddress = pSegmentInfo->targetAddress;
         pBlockInfo->targetLength = pSegmentInfo->targetLength;
         pBlockInfo->logicalAddress = pSegmentInfo->logicalAddress;
         pBlockInfo->logicalLength = pSegmentInfo->logicalLength;

         pBlockInfo->readFct = (tFblMemVerifyReadFct)FblReadRam;
      }
#endif

      libMemResult = FblMemRemapStatus(FblMemBlockStartIndication(pBlockInfo));

      if(libMemResult != kDiagErrorNone)
      {
         FblDiagSetError(libMemResult);
         result = kFblFailed;
      }
   }

   return result;
}

static void FblDiagSessionControlParamInit(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)diagReqDataLen;
#endif

   FblDiagClrPreconditionsChecked();
   FblDiagClrSecurityKeyAllowed();
   FblDiagClrSecurityUnlock();
   FblDiagClrFingerprintValid();
   FblDiagClrEraseSucceeded();
   FblDiagClrTransferDataAllowed();
   FblDiagClrTransferDataSucceeded();
   FblDiagClrChecksumAllowed();

   transferRemainder = 0u;

   FblDiagClrTransferTypeFlash();
   FblDiagSegmentInit();
   (void)ApplFblSecurityInit();

   pbDiagData[kDiagLocFmtSubparam + 1u] = (vuint8)((kDiagSessionTimingP2 >> 8u) & 0xFFu);
   pbDiagData[kDiagLocFmtSubparam + 2u] = (vuint8)(kDiagSessionTimingP2 & 0xFFu);
   pbDiagData[kDiagLocFmtSubparam + 3u] = (vuint8)((kDiagSessionTimingP2Star >> 8u) & 0xFFu);
   pbDiagData[kDiagLocFmtSubparam + 4u] = (vuint8)(kDiagSessionTimingP2Star & 0xFFu);
}

void FblDiagOemInitPowerOn(void){
   expectedSequenceCnt = 0;
}

static tFblResult FblDiagProcessServiceNrc(vuint32 serviceErrorMask){
   tFblResult result;

   result = kFblOk;

   if((serviceErrorMask & kFblDiagServiceNoFuncSupport) != 0u){
      DiagSetNoResponse();
   }
   else{
      if((serviceErrorMask & kFblDiagServiceSessionFailure) == kFblDiagServiceSessionFailure)
      {
         DiagNRCServiceNotSupportedInActiveSession();
      }

      else if((serviceErrorMask & kFblDiagServiceMinLenFailure) == kFblDiagServiceMinLenFailure)
      {
         DiagNRCIncorrectMessageLengthOrInvalidFormat();
      }

      else if((serviceErrorMask & kFblDiagServiceSecAccessFailure) == kFblDiagServiceSecAccessFailure)
      {
         DiagNRCSecurityAccessDenied();
      }

      else if((serviceErrorMask & kFblDiagServiceLenFailure) == kFblDiagServiceLenFailure)
      {
         DiagNRCIncorrectMessageLengthOrInvalidFormat();
      }
      else if((serviceErrorMask & kFblDiagServicePrehandlerFailure) == kFblDiagServicePrehandlerFailure)
      {
         if(DiagGetError() == kDiagErrorNone)
         {
            DiagNRCConditionsNotCorrect();
         }
      }

      else
      {
         DiagNRCGeneralReject();
      }
   }

   return result;
}

static tFblResult FblDiagProcessSubfunctionNrc(vuint32 serviceErrorMask){
   tFblResult result;

   result = kFblOk;

   if((serviceErrorMask & (kFblDiagServiceNoFuncSupport | kFblDiagSubNoFuncSupport)) != 0u){
      DiagSetNoResponse();
   }
   else{
      if((serviceErrorMask & kFblDiagServiceSessionFailure) == kFblDiagServiceSessionFailure)
      {
         DiagNRCServiceNotSupportedInActiveSession();
      }

      else if((serviceErrorMask & kFblDiagServiceMinLenFailure) == kFblDiagServiceMinLenFailure)
      {
         DiagNRCIncorrectMessageLengthOrInvalidFormat();
      }

      else if((serviceErrorMask & kFblDiagSubfunctionNotFound) == kFblDiagSubfunctionNotFound)
      {
#if defined( FBL_ENABLE_USERSUBFUNCTION )

         FblDiagSetRcrRpAllowed();
         ApplDiagUserSubFunction(&DiagBuffer[kDiagFmtSubparam], DiagDataLength);
#else
         DiagNRCSubFunctionNotSupported();
#endif
      }

      else if((serviceErrorMask & kFblDiagSubparamNotFound) == kFblDiagSubparamNotFound)
      {
         DiagNRCRequestOutOfRange();
      }

      else if((serviceErrorMask & (kFblDiagServiceSecAccessFailure | kFblDiagSubfuncSecAccessFailure | kFblDiagSubparamSecAccessFailure)) != 0u)
      {
         DiagNRCSecurityAccessDenied();
      }

      else if((serviceErrorMask & (kFblDiagServiceLenFailure | kFblDiagSubMinLenFailure | kFblDiagSubLenFailure)) != 0u)
      {
         DiagNRCIncorrectMessageLengthOrInvalidFormat();
      }

      else if((serviceErrorMask & (kFblDiagSubfuncSessionFailure | kFblDiagSubparamSessionFailure)) != 0u)
      {
         DiagNRCSubfunctionNotSupportedInActiveSession();
      }
      else if((serviceErrorMask & kFblDiagServicePrehandlerFailure) == kFblDiagServicePrehandlerFailure)
      {
         if(DiagGetError() == kDiagErrorNone)
         {
            DiagNRCConditionsNotCorrect();
         }
      }

      else
      {
         DiagNRCGeneralReject();
      }
   }

   return result;
}

static tFblResult FblDiagProcessRoutineNrc(vuint32 serviceErrorMask){
   tFblResult result;

   result = kFblOk;

   if((serviceErrorMask & (kFblDiagServiceNoFuncSupport | kFblDiagSubNoFuncSupport)) != 0u){
      DiagSetNoResponse();
   }
   else{
      if((serviceErrorMask & kFblDiagServiceSessionFailure) == kFblDiagServiceSessionFailure)
      {
         DiagNRCServiceNotSupportedInActiveSession();
      }

      else if((serviceErrorMask & kFblDiagServiceMinLenFailure) == kFblDiagServiceMinLenFailure)
      {
         DiagNRCIncorrectMessageLengthOrInvalidFormat();
      }

      else if((serviceErrorMask & kFblDiagSubparamNotFound) == kFblDiagSubparamNotFound)
      {
#if defined( FBL_ENABLE_USERROUTINE )

         FblDiagSetRcrRpAllowed();
         ApplDiagUserRoutine(&DiagBuffer[kDiagFmtSubparam], DiagDataLength);
#else
         DiagNRCRequestOutOfRange();
#endif
      }

      else if((serviceErrorMask & kFblDiagSubfunctionNotFound) == kFblDiagSubfunctionNotFound)
      {
#if defined( FBL_ENABLE_USERSUBFUNCTION )

         FblDiagSetRcrRpAllowed();
         ApplDiagUserSubFunction(&DiagBuffer[kDiagFmtSubparam], DiagDataLength);
#else
         DiagNRCSubFunctionNotSupported();
#endif
      }

      else if((serviceErrorMask & (kFblDiagServiceSecAccessFailure | kFblDiagSubfuncSecAccessFailure | kFblDiagSubparamSecAccessFailure)) != 0u)
      {
         DiagNRCSecurityAccessDenied();
      }

      else if((serviceErrorMask & (kFblDiagServiceLenFailure | kFblDiagSubMinLenFailure | kFblDiagSubLenFailure)) != 0u)
      {
         DiagNRCIncorrectMessageLengthOrInvalidFormat();
      }

      else if((serviceErrorMask & (kFblDiagSubfuncSessionFailure | kFblDiagSubparamSessionFailure)) != 0u)
      {
         DiagNRCSubfunctionNotSupportedInActiveSession();
      }
      else if((serviceErrorMask & kFblDiagServicePrehandlerFailure) == kFblDiagServicePrehandlerFailure)
      {
         if(DiagGetError() == kDiagErrorNone)
         {
            DiagNRCConditionsNotCorrect();
         }
      }

      else
      {
         DiagNRCGeneralReject();
      }
   }

   return result;
}

static tFblResult FblDiagDefaultSessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )
   vuint8 responseFlag;
#endif

   if(FblDiagGetProgrammingSession()){
      FblDiagSetWaitEcuReset();

#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )

      DiagExRCRResponsePending(kForceSendResponsePending);

      responseFlag = RESET_RESPONSE_SDS_REQUIRED;
      (void)ApplFblWriteResetResponseFlag(&responseFlag);

      if(FblCwSaveResponseAddress() != kFblOk)
      {
      }
#else

      FblDiagSessionControlParamInit(pbDiagData, diagReqDataLen);

      DiagProcessingDone(kDiagRslDiagnosticSessionControl);
#endif
      FblDiagSetEcuResetFctFinished();
   }
   else{
      FblDiagSetDefaultSession();

      FblDiagSessionControlParamInit(pbDiagData, diagReqDataLen);

      DiagProcessingDone(kDiagRslDiagnosticSessionControl);
   }

   return kFblOk;
}

static tFblResult FblDiagExtendedSessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   FblDiagSetExtendedSession();

   FblDiagSessionControlParamInit(pbDiagData, diagReqDataLen);

   DiagProcessingDone(kDiagRslDiagnosticSessionControl);

   return kFblOk;
}

#ifdef SMART_TESTER_JUMP_IN
static tFblResult FblDiagSUPPLIER1SessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  void(*pSmartTesterStart)(void) = (void(*)(void))(0x78000u);

  DiagExRCRResponsePending(kForceSendResponsePending);

  FblRealTimeSupport();
  (*pSmartTesterStart)();
  return 0;
}
#endif

static tFblResult FblDiagProgrammingSessionMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

#if defined( FBL_DIAG_ENABLE_CHECK_PROGRAMMING_PRECONDITIONS )
   if((!FblDiagGetPreconditionsChecked()) && (!FblMainGetStartFromAppl()))
#else
   if(ApplFblCheckProgConditions() != kFblOk)
#endif
   {
      FblErrStatSetError(FBL_ERR_FLASH_PROG_CONDITIONS);
      DiagNRCConditionsNotCorrect();
      result = kFblFailed;
   }
   else{
      result = kFblOk;

      FblDiagSetProgrammingSession();

      FblDiagSessionControlParamInit(pbDiagData, diagReqDataLen);

      DiagProcessingDone(kDiagRslDiagnosticSessionControl);
   }

   return result;
}

static tFblResult FblDiagEcuResetMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )
   vuint8 responseFlag;
#endif

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)diagReqDataLen;
   (void)pbDiagData;
#endif

   FblDiagSetWaitEcuReset();

#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )

   DiagExRCRResponsePending(kForceSendResponsePending);

   responseFlag = RESET_RESPONSE_ECURESET_REQUIRED;
   (void)ApplFblWriteResetResponseFlag(&responseFlag);

   if(FblCwSaveResponseAddress() != kFblOk){
   }
#else

   DiagProcessingDone(kDiagRslEcuReset);
#endif
   FblDiagSetEcuResetFctFinished();

   return kFblOk;
}

static tFblResult FblDiagSecAccessSeedMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)diagReqDataLen;
#endif

   result = kFblOk;

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

   if(GetSecurityAccessDelay() > 0u){
      DiagNRCRequiredTimeDelayNotExpired();
      result = kFblFailed;
   }
#endif

   if(result == kFblOk){
      if(FblDiagGetSecurityUnlock())
      {
         vuintx i;

         for(i = 0; i < kSecSeedLength; i++)
         {
            pbDiagData[kDiagLocFmtSeedKeyStart + i] = 0x00u;
         }
      }
      else
      {
         if(ApplFblSecuritySeed() == kFblOk)
         {
            FblDiagSetSecurityKeyAllowed();
         }
         else
         {
            FblErrStatSetError(FBL_ERR_SEED_GENERATION_FAILED);
            DiagNRCConditionsNotCorrect();
            result = kFblFailed;
         }
      }
   }

   if(result == kFblOk){
      DiagProcessingDone(kDiagRslSecurityAccessSeed);
   }

   return result;
}

static tFblResult FblDiagSecAccessKeyMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)diagReqDataLen;
   (void)pbDiagData;
#endif

   if(    (!FblDiagGetSecurityKeyAllowed())
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
        || (GetSecurityAccessDelay() > 0u)
#endif
      ){
      DiagNRCRequestSequenceError();
      result = kFblFailed;
   }
   else{
      DiagExRCRResponsePending(kForceSendResponsePending);

      FblDiagClrSecurityKeyAllowed();

      if(ApplFblSecurityKey() == kFblOk)
      {
         FblDiagSetSecurityUnlock();
         result = kFblOk;
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

         secSendKeyInvalid = 0u;

         (void)ApplFblClrSecAccessDelayFlag();
         (void)ApplFblWriteSecAccessInvalidCount(&secSendKeyInvalid);
#endif
      }
      else
      {
         result = kFblFailed;
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

         if(ApplFblReadSecAccessInvalidCount(&secSendKeyInvalid) != kFblOk)
         {
            secSendKeyInvalid = (kSecMaxInvalidKeys - 1u);
         }

         secSendKeyInvalid++;

         if(secSendKeyInvalid >= kSecMaxInvalidKeys)
         {
            SetSecurityAccessDelay();
            (void)ApplFblSetSecAccessDelayFlag();

            DiagNRCExceedNumberOfAttempts();
         }
         else
         {
            (void)ApplFblWriteSecAccessInvalidCount(&secSendKeyInvalid);

            DiagNRCInvalidKey();
         }
#else
         DiagNRCInvalidKey();
#endif
      }
   }

   if(result == kFblOk){
      DiagProcessingDone(kDiagRslSecurityAccessKey);
   }

   return result;
}

static tFblResult FblDiagCommCtrlMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)diagReqDataLen;
#endif

   if(pbDiagData[kDiagLocFmtSubparam + 0x01u] != kDiagSubNormalCommunication){
      DiagNRCRequestOutOfRange();
      result = kFblFailed;
   }
   else{
      DiagProcessingDone(kDiagRslCommunicationControl);
      result = kFblOk;
   }

   return result;
}

static tFblResult FblDiagDataByIdLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pbDiagData;
   (void)diagReqDataLen;
#endif

   return kFblOk;
}

static tFblResult FblDiagWriteDataByIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

   DiagNRCRequestOutOfRange();
   result = kFblFailed;

   return result;
}

static tFblResult FblDiagRCStartEraseLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

   result = kFblOk;

   return result;
}

static tFblResult FblDiagRCStartEraseMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblAddress memoryAddress;
   tFblLength memorySize;

   tFblResult result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)diagReqDataLen;
#endif

   result = FblDiagCheckErasePreconditionsCustom(pbDiagData, diagReqDataLen, &memoryAddress, &memorySize);

   if(result == kFblOk){
      if(FblLbtGetBlockNrByAddressLength(memoryAddress, memorySize, &downloadBlockDescriptor.blockNr) != kFblOk)
      {
         FblErrStatSetError(FBL_ERR_LBT_BLOCK_INDEX_EXCEEDED);
         DiagNRCRequestOutOfRange();
         result = kFblFailed;
      }
      else
      {
         FblErrStatSetBlockNr(downloadBlockDescriptor.blockNr);
      }
   }

   if(result == kFblOk){
      DiagExRCRResponsePending(kForceSendResponsePending);

      result = FblDiagCheckProgAttemptCounter(&downloadBlockDescriptor);
   }

   if(result == kFblOk){
      (void)FblRealTimeSupport();

      if(ApplFblInvalidateBlock(downloadBlockDescriptor) != kFblOk)
      {
         DiagNRCConditionsNotCorrect();
         result = kFblFailed;
      }
   }

   if(result == kFblOk){
      if(ApplFblIncProgAttempts(downloadBlockDescriptor) != kFblOk)
      {
         DiagNRCConditionsNotCorrect();
         result = kFblFailed;
      }
   }

   if(result == kFblOk){
      result = FblDiagEraseBlock(&downloadBlockDescriptor);
      if(result == kFblOk)
      {
         pbDiagData[kDiagLocFmtRoutineStatus] = kDiagEraseMemoryOk;
      }
      else
      {
         pbDiagData[kDiagLocFmtRoutineStatus] = kDiagEraseMemoryFailed;
      }
   }

   if(DiagGetError() == kDiagErrorNone){
      DiagProcessingDone(kDiagRslRoutineControlEraseRoutine);
   }

   return result;
}

#if defined( FBL_DIAG_ENABLE_CHECK_PROGRAMMING_PRECONDITIONS )

static tFblResult FblDiagRCStartCheckProgPreCondMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pbDiagData;
   (void)diagReqDataLen;
#endif

   FblDiagClrFingerprintValid();

   if(ApplFblCheckProgConditions() == kFblOk){
      FblDiagSetPreconditionsChecked();
   }
   else{
      FblDiagClrPreconditionsChecked();
   }

   return kFblOk;
}
#endif

static tFblResult FblDiagRCStartApplicationHwidCheckMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  if(SUPPLIER1_HwidCheck() == FALSE){
    pbDiagData[kDiagLocFmtRoutineStatus] = 0x01;
  }

  else{
    pbDiagData[kDiagLocFmtRoutineStatus] = 0x00;
  }

  DiagProcessingDone(kDiagRslRoutineControlAppHwidCheck);
  return kFblOk;
}

static tFblResult FblDiagRCStartCompareAndStoreSignatureMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  FblRealTimeSupport();
  ApplFblValidateBlock(downloadBlockDescriptor);

  if(SUPPLIER1_ApplicationSignatureCheck(pbDiagData, diagReqDataLen) == TRUE){
    pbDiagData[kDiagLocFmtRoutineStatus] = 0x00;
  }
  else{
    pbDiagData[kDiagLocFmtRoutineStatus] = 0x01;
  }

  SUPPLIER1_ClearWakeupFactorRramCopy();
  DiagProcessingDone(kDiagRslRoutineControlCheckRoutine);

  return kFblOk;
}

static tFblResult FblDiagRCStartLoadSecurityKeyMainHandler(
      vuint8*           pbDiagData
   ,  tCwDataLengthType diagReqDataLen
){
  tFblResult result = kFblOk;
#if(SEED_KEY_ALGORITHM==SEED_KEY_USE_HMAC_SHA256)
  switch(pbDiagData[3]){
    case 0x01: result = FEEFBL_PutUdsBootKey(&pbDiagData[4]);                             break;
    case 0x02: result = FEEFBL_PutUdsAppKey(&pbDiagData[4]);                              break;
    case 0x03: result = FEEFBL_PutUdsMsgKey(&pbDiagData[4]);                              break;
    default:   result = kFblFailed;                           DiagNRCRequestOutOfRange(); break;
  }
#endif
  if(result == kFblOk){
    pbDiagData[4] = 0x00;
  }
  else{
    pbDiagData[4] = 0x01;
  }

  if(DiagGetError() == kDiagErrorNone){
    DiagProcessingDone(kDiagRslRoutineControlLoadSecurityKey);
  }

  return result;
}

static tFblResult FblDiagRCStartSecretServiceMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 ucPassword[10] = {'M','S','P','P','D','P','2','0','2','0'};
  uint8 i;
  uint8 clearMem[20];
  tFblResult result = kFblOk;

  for(i=0; i<10; i++){
    if(pbDiagData[3+i] != ucPassword[i]){
       result = kFblFailed;
    }
  }

  if(result == kFblOk){
    for(i=0; i<20; i++){
      clearMem[i] = 0xff;
    }
#if(SEED_KEY_ALGORITHM==SEED_KEY_USE_HMAC_SHA256)
	FEEFBL_PutUdsBootKey(clearMem);
    FEEFBL_PutUdsMsgKey(clearMem);
    FEEFBL_PutUdsAppKey(clearMem);
#endif
    PRODFLASH_PutVin(clearMem);

    clearMem[0] = 0;
    PRODFLASH_PutManufacturingSupportMode(clearMem);
    DiagProcessingDone(kDiagRslRoutineControlSecretService);
  }
  else{
    DiagNRCRequestOutOfRange();
  }
  return result;
}

static tFblResult FblDiagRCStartInitGenealogyBlockMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 aucTempBuffer[40];
  uint8 i;
  uint32 ulGenealogyCrc32;

  for(i=0; i<40; i++){
    aucTempBuffer[i] = 0xff;
  }
  PRODFLASH_PutAuxId(aucTempBuffer);
  PRODFLASH_PutModeId(aucTempBuffer);
  PRODFLASH_PutRivianBoardPartnumber(aucTempBuffer);
  PRODFLASH_PutRivianBoardSerialnumber(aucTempBuffer);
  PRODFLASH_PutRivianEcuPartnumber(aucTempBuffer);
  PRODFLASH_PutRivianEcuSerialnumber(aucTempBuffer);

  (void)VERSION_GetGenealogyVersion(aucTempBuffer, cSTRING_SIZ_SCHEMA_VERS, cFBL);
  PRODFLASH_PutGenealogyVersion(aucTempBuffer);
  (void)VERSION_GetComponentId(aucTempBuffer, cSTRING_SIZ_COMP_ID, cFBL);
  PRODFLASH_PutComponentId(aucTempBuffer);
  (void)VERSION_GetPcbaId(aucTempBuffer, cSTRING_SIZ_PCBA_ID, cFBL);
  PRODFLASH_PutPcbaId(aucTempBuffer);

  ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
  PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);

  DiagProcessingDone(kDiagRslRoutineControlInitGenealogyBlock);
  return kFblOk;
}

static tFblResult FblDiagRCStartCheckValidModuleMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
	tFblResult  result = kFblOk;
#if(SEED_KEY_ALGORITHM==SEED_KEY_USE_HMAC_SHA256)
  uint32      pStartOfApplication;
  uint32      pEndOfApplication;
  uint32      ulLength;
  uint8       aucKey[16];
  uint8       aucHashCalc[16];
  uint8       aucHashNvm[16];
  uint8       i;

  ApplFblValidateBlock(downloadBlockDescriptor);

  (void)FblRealTimeSupport();

  pStartOfApplication = cAPPLICATION_START_ADDRESS;
  pEndOfApplication = cAPPLICATION_END_ADDRESS;
  ulLength = pEndOfApplication - pStartOfApplication + 1;
  hmac_sha256(aucKey, kEepSizeSecKey_UDSMSGKEY, (const unsigned char*)pStartOfApplication, ulLength, aucHashCalc, cSTRING_SIZ_HASH);

  PRODFLASH_GetApplicationSignature(aucHashNvm);
  pbDiagData[kDiagLocFmtRoutineStatus] = 0x00;

  for(i=0; i<cSTRING_SIZ_HASH; i++){
    if(aucHashCalc[i] != aucHashNvm[i]){
      pbDiagData[kDiagLocFmtRoutineStatus] = 0x01;
    }
  }

#endif
  DiagProcessingDone(kDiagRslRoutineControlCheckValidModule);
  return result;
}

static tFblResult FblDiagRequestDownloadLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

   vuint8 addrFormat;
   vuint8 lengthFormat;

   lengthFormat = (vuint8)((pbDiagData[kDiagLocFmtFormatOffset] & 0xF0u) >> 4u);
   addrFormat   = (vuint8)(pbDiagData[kDiagLocFmtFormatOffset] & 0x0Fu);

   if(diagReqDataLen != (kDiagRqlRequestDownload + lengthFormat + addrFormat)){
      result = kFblFailed;
   }
   else{
      result = kFblOk;
   }

   return result;
}

static tFblResult FblDiagRequestDownloadMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblMemBlockInfo blockInfo;
   tFblMemSegmentInfo segmentInfoLocal;
   tFblResult result;
   tFblDiagNrc libMemResult;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)diagReqDataLen;
#endif

   segmentInfoLocal.logicalAddress = 0u;
   segmentInfoLocal.logicalLength = 0u;

   result = FblDiagCheckRequestDownloadPreconditions(pbDiagData, &segmentInfoLocal);

#if defined( FBL_DIAG_ENABLE_FLASHDRV_DOWNLOAD )

   if(result == kFblOk){
      result = FblDiagCheckForFlashDriverDownload(&segmentInfoLocal);
   }
#else
   FblDiagSetTransferTypeFlash();
   segmentInfoLocal.type = kFblMemType_ROM;
#endif

   if(result == kFblOk){
      transferRemainder = segmentInfoLocal.logicalLength;

      FblErrStatSetAddress(segmentInfoLocal.logicalAddress);

      expectedSequenceCnt = kDiagInitSequenceNum;

      currentSequenceCnt = kDiagInitSequenceNum;

      if(FblDiagGetTransferTypeFlash())
      {
         result = FblDiagCheckFlashMemoryDownload(&segmentInfoLocal);
      }
#if defined( FBL_DIAG_ENABLE_FLASHDRV_DOWNLOAD )
      else
      {
         result = FblDiagCheckFlashDriverDownload(&segmentInfoLocal);
      }
#endif
   }

   if((result == kFblOk) && (segmentCount <= 1u)){
      result = FblDiagPrepareFirstDownloadSegment(&blockInfo, &segmentInfoLocal, downloadBlockDescriptor.blockNr);
      pbDiagData = FblDiagMemGetActiveBuffer();
   }

   if(result == kFblOk){
      libMemResult = FblMemRemapStatus(FblMemSegmentStartIndication(&segmentInfoLocal));
      pbDiagData = FblDiagMemGetActiveBuffer();
      if(libMemResult == kDiagErrorNone)
      {
         expectedSequenceCnt = kDiagInitSequenceNum;

         currentSequenceCnt = kDiagInitSequenceNum;

         FblDiagSetTransferDataAllowed();
         FblDiagClrTransferDataSucceeded();
         FblDiagClrChecksumAllowed();

         pbDiagData[kDiagLocFmtSubparam] = (FBL_DIAG_RESPONSE_BUFFER_LFI << 4u);
         FblMemSetInteger(FBL_DIAG_RESPONSE_BUFFER_LFI, FBL_DIAG_RESPONSE_BUFFER_SIZE, &pbDiagData[kDiagLocFmtSubparam + 1u]);

         DiagProcessingDone(kDiagRslRequestDownload + FBL_DIAG_RESPONSE_BUFFER_LFI);
      }
      else
      {
         FblDiagSetError(libMemResult);
         result = kFblFailed;
      }
   }

   return result;
}

static tFblResult FblDiagTransferDataLengthCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pbDiagData;
#endif

   if((diagReqDataLen <= (kDiagRqlTransferData)) || (diagReqDataLen > (tTpDataType)(FBL_DIAG_RESPONSE_BUFFER_SIZE - 1u))){
      FblDiagClrTransferDataAllowed();
      result = kFblFailed;
   }
   else{
      result = kFblOk;
   }

   return result;
}

static tFblResult FblDiagTransferDataMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;
   tFblDiagNrc libMemResult;
   tFblLength transferDataLength;

   if(!FblDiagGetTransferDataAllowed()){
      DiagNRCRequestSequenceError();
      result = kFblFailed;
   }

   else if(pbDiagData[kDiagLocFmtSubparam] != expectedSequenceCnt){
      if(pbDiagData[kDiagLocFmtSubparam] == currentSequenceCnt)
      {
         DiagProcessingDone(kDiagRslTransferData);
         result = kFblOk;
      }
      else
      {
         DiagNRCWrongBlockSequenceCounter();
         result = kFblFailed;
      }
   }
   else{
      transferDataLength = diagReqDataLen - 1u;

      FblDiagClrEraseSucceeded();
      libMemResult = FblMemRemapStatus(FblMemDataIndication(DiagBuffer, kDiagFmtDataOffset, transferDataLength));

      pbDiagData = FblDiagMemGetActiveBuffer();
      if(libMemResult == kDiagErrorNone)
      {
         currentSequenceCnt = expectedSequenceCnt;

         expectedSequenceCnt = ((expectedSequenceCnt + 1u) & 0xFFu);

         DiagProcessingDone(kDiagRslTransferData);
         result = kFblOk;
      }
      else
      {
         FblDiagSetError(libMemResult);
         FblDiagClrTransferDataAllowed();
         result = kFblFailed;
      }
   }

   return result;
}

static tFblResult FblDiagReqTransferExitMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;
   tFblDiagNrc libMemResult;
   tFblLength  totalProgramLength;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pbDiagData;
   (void)diagReqDataLen;
#endif

   if(!FblDiagGetTransferDataAllowed()){
      DiagNRCRequestSequenceError();
      result = kFblFailed;
   }
   else{
      FblDiagClrTransferDataAllowed();

      libMemResult = FblMemRemapStatus((FblMemSegmentEndIndication(&totalProgramLength)));
      pbDiagData = FblDiagMemGetActiveBuffer();

      if(libMemResult == kDiagErrorNone)
      {
         FblDiagSetTransferDataSucceeded();
         FblDiagSetChecksumAllowed();
         DiagProcessingDone(kDiagRslRequestTransferExit);
         result =  kFblOk;
      }
      else
      {
         FblDiagSetError(libMemResult);
         result = kFblFailed;
      }
   }

   return result;
}

static tFblResult FblDiagTesterPresentMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pbDiagData;
   (void)diagReqDataLen;
#endif

   DiagProcessingDone(kDiagRslTesterPresent);

   return kFblOk;
}

static tFblResult FblDiagControlDTCMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   tFblResult result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if !defined( FBL_DIAG_ENABLE_CONTROLDTC_OPTIONRECORD )
   (void)pbDiagData;
#endif
   (void)diagReqDataLen;
#endif

#if defined( FBL_DIAG_ENABLE_CONTROLDTC_OPTIONRECORD )

   if(   ( pbDiagData[kDiagLocFmtRoutineIdHigh] != 0xFFu) \
       || ( pbDiagData[kDiagLocFmtRoutineIdLow]  != 0xFFu) \
       || ( pbDiagData[kDiagLocFmtRoutineStatus] != 0xFFu)
      ){
      DiagNRCRequestOutOfRange();
      result = kFblFailed;
   }
   else
#endif
   {
      DiagProcessingDone(kDiagRslControlDTCSetting);

      result = kFblOk;
   }

   return result;
}

static tFblResult FblDiagReadDataByIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   ApplFblReadDataByIdentifier(pbDiagData, diagReqDataLen);

   return kFblOk;
}

static tFblResult FblDiagWdbiModuleToProgramMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result = kFblOk;

  if(diagReqDataLen != (cDiagDataLenManufSupport + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }

  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    if(pbDiagData[kDiagFmtDataIdSize] == cPROG_TYPE_APP){
      ulMemEraseStartAddress = FblLogicalBlockTable.logicalBlock[FBL_LBT_RIVIANAPPL_BLOCK_NUMBER].blockStartAddress;
      ulMemEraseLength = FblLogicalBlockTable.logicalBlock[FBL_LBT_RIVIANAPPL_BLOCK_NUMBER].blockLength;
    }

    else{
      result = kFblFailed;
      DiagNRCRequestOutOfRange();
    }
  }

  if(result == kFblOk){
    FblDiagSetDownloadRunning();
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }

  return result;
}

static tFblResult FblDiagWdbiBoardPartnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result = kFblOk;
  uint32 ulGenealogyCrc32;
  uint8 ucBuffer[40];
  uint8 ucLength;

  ucLength = PRODFLASH_GetRivianBoardPartNumber(ucBuffer);
  if(SUPPLIER1_IsMemoryInitialized(ucBuffer, ucLength) == FALSE){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteBoardPartnumber(pbDiagData, &diagReqDataLen);
    ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
    PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);
  }

  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagWdbiEcuPartnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result = kFblOk;
  uint32 ulGenealogyCrc32;
  uint8 ucBuffer[40];
  uint8 ucLength;

  ucLength = PRODFLASH_GetRivianEcuPartNumber(ucBuffer);
  if(SUPPLIER1_IsMemoryInitialized(ucBuffer, ucLength) == FALSE){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteEcuPartnumber(pbDiagData, &diagReqDataLen);

    ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
    PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);
  }

  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagWdbiBoardSerialnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result = kFblOk;
  uint32 ulGenealogyCrc32;
  uint8 ucBuffer[40];
  uint8 ucLength;

  ucLength = PRODFLASH_GetRivianBoardSerialNumber(ucBuffer);
  if(SUPPLIER1_IsMemoryInitialized(ucBuffer, ucLength) == FALSE){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteBoardSerialnumber(pbDiagData, &diagReqDataLen);

    ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
    PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);
  }
  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagWdbiEcuSerialnumberMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result = kFblOk;
  uint32 ulGenealogyCrc32;
  uint8 ucBuffer[40];
  uint8 ucLength;

  ucLength = PRODFLASH_GetRivianEcuSerialNumber(ucBuffer);
  if(SUPPLIER1_IsMemoryInitialized(ucBuffer, ucLength) == FALSE){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteEcuSerialnumber(pbDiagData, &diagReqDataLen);

    ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
    PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);
  }

  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagWdbiVinMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result = kFblOk;
    uint8 ucBuffer[40];
  uint8 ucLength;

  ucLength = PRODFLASH_GetVin(ucBuffer);
  if(SUPPLIER1_IsMemoryInitialized(ucBuffer, ucLength) == FALSE){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteVin(pbDiagData, &diagReqDataLen);
  }

  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagWdbiManufSupportMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result = kFblOk;
  uint8 ucBuffer[40];

  (void)PRODFLASH_GetManufacturingSupportMode(ucBuffer);
  if(ucBuffer[0] == 0x01){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteManufSupport(pbDiagData, &diagReqDataLen);
  }

  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagWdbiFingerprintAppMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result;

  result = SUPPLIER1_CustomDid_WriteFingerprint(pbDiagData, &diagReqDataLen);
  if(result == kFblOk){
    FblDiagSetFingerprintValid();
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }

  return result;
}

static tFblResult FblDiagWdbiAuxIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result;
  uint32 ulGenealogyCrc32;
  uint8 ucBuffer[40];
  uint8 ucLength;

  ucLength = PRODFLASH_GetAuxId(ucBuffer);
  if(SUPPLIER1_IsMemoryInitialized(ucBuffer, ucLength) == FALSE){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteAuxId(pbDiagData, &diagReqDataLen);

    ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
    PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);
  }

  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagWdbiModeIdMainHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
  uint8 result;
  uint32 ulGenealogyCrc32;
  uint8 ucBuffer[40];
  uint8 ucLength;

  ucLength = PRODFLASH_GetModeId(ucBuffer);
  if(SUPPLIER1_IsMemoryInitialized(ucBuffer, ucLength) == FALSE){
    result = kFblFailed;
    DiagNRCConditionsNotCorrect();
  }

  if(result == kFblOk){
    result = SUPPLIER1_CustomDid_WriteModeId(pbDiagData, &diagReqDataLen);

    ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
    PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);
  }

  if(result == kFblOk){
    DiagProcessingDone(kDiagRslWriteDataByIdentifier);
  }
  return result;
}

static tFblResult FblDiagDefaultPreHandler(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
   return ApplFblCheckConditions(pbDiagData, diagReqDataLen);
}

#define FBLDIAG_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"

void FblDiagDefaultPostHandler( vuint8 postParam ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)postParam;
#endif
   if(FblDiagGetDefaultSession()){
      FblCwResetResponseAddress();
   }
}

#define FBLDIAG_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

void FblDiagOemTimerTask(void){
  static vuint16 ush500msTimer = 1;
  PduInfoType pdu;
  BootIdType tMessageContent;
  uint8 ucCompId[2];
  uint8 ucFaultFlag;

  if(!FblDiagGetDownloadRunning()){
    if(--ush500msTimer == 0){
      ush500msTimer = 500;

      ucFaultFlag = SUPPLIER1_GetFaultFlag();
      tMessageContent.ucFaultFlag = (ucFaultFlag & 0xf);
      tMessageContent.ucVersion = 0x1;
      PRODFLASH_GetComponentId(ucCompId);
      tMessageContent.ucLsbCompId = ucCompId[1];
      PRODFLASH_GetPcbaId(&tMessageContent.ucPcbaId);
      PRODFLASH_GetAuxId(&tMessageContent.ucAuxId);
      PRODFLASH_GetModeId((uint8*)&tMessageContent.ucModeId);
      ApplFblNvReadValidityFlags(&tMessageContent.ucUnused);
      tMessageContent.ucCurrentSw = 0x02;

#ifndef LORDSTOWN_STARTER_APP
      pdu.SduDataPtr = (uint8*)&tMessageContent;
      pdu.SduLength = 8;
      PduR_MyCom_Bl_Status_MsgTransmit(0, &pdu);
#endif
    }
  }
}

vuint8 FblDiagCheckStartMsg(const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *pData, vuintx length){
   vuint8 result;

   if(FblDiagGetFunctionalRequest()){
     result = kFblFailed;
   }
   else{
     result = kFblOk;
   }

   return result;
}

uint16 FblDiagGetLengthOfDataForWdbi(uint16 ushDid){
  uint16 ushNoOfElements = (uint16)((uint16)sizeof(kFblDiagSubtableWdbi) / (uint16)sizeof(tFblDiagServiceSubTable));
  uint8 i = 0;
  uint16 ushDidInTable;
  uint16 ushLength = 0;

  while(i < ushNoOfElements){
    ushDidInTable = (uint16)(kFblDiagSubtableWdbi[i].subTableParamTable[0] << 8) + (uint16)kFblDiagSubtableWdbi[i].subTableParamTable[1];
    if(ushDidInTable == ushDid){
      ushLength = kFblDiagSubtableWdbi[i].serviceLength;
      i = ushNoOfElements;
    }
    else{
      i++;
    }
  }

  return ushLength;
}

uint16 FblDiagGetLengthOfDataForRoutineControl(uint16 ushRid){
  uint16 ushNoOfElements = (uint16)((uint16)sizeof(kFblDiagSubtableRoutine) / (uint16)sizeof(tFblDiagServiceSubTable));
  uint8 i = 0;
  uint16 ushRidInTable;
  uint16 ushLength = 0;

  while(i < ushNoOfElements){
    ushRidInTable = (uint16)(kFblDiagSubtableRoutine[i].subTableParamTable[1] << 8) + (uint16)kFblDiagSubtableRoutine[i].subTableParamTable[2];
    if(ushRidInTable == ushRid){
      ushLength = kFblDiagSubtableRoutine[i].serviceLength;
      i = ushNoOfElements;
    }
    else{
      i++;
    }
  }

  return ushLength;
}

void FblDiagOemPrepareRrResponse(V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * pDiagBuffer, V_MEMRAM1 tCwDataLengthType V_MEMRAM2 V_MEMRAM3 *pDiagDataLength){
  pDiagBuffer[kDiagFmtSubparam] = kDiagOemSpecBlJump;
  *pDiagDataLength = kDiagRqlEcuReset;
}

