#ifndef FBL_DIAG_OEM_H
#define FBL_DIAG_OEM_H

#define FBLDIAG_14229_UDS2_VERSION           0x0801u
#define FBLDIAG_14229_UDS2_RELEASE_VERSION   0x00u

#define FBL_VERSION                          _VECTOR_SIP_VERSION
#define FBL_RELEASE_VERSION                  _VECTOR_SIP_RELEASE_VERSION

#define FBL_DIAGCORE_API_REFERENCE_VERSION_MAJOR     0x04u

#define FBL_DIAGCORE_API_REFERENCE_VERSION_MINOR     0x01u

#define FBL_DIAGCORE_API_REFERENCE_VERSION_RELEASE   0x00u

#define FBL_ENABLE_TRANSFER_VERIFICATION_CHECK
#define FBL_ENABLE_EXCEEDED_RETRIES_REJECT

#define FBL_DIAG_ENABLE_CORE_GETBLOCKFROMADDR
#define FBL_DIAG_ENABLE_OEM_INITPOWERON
#define FBL_DIAG_ENABLE_CORE_PREWRITE
#define FBL_DIAG_ENABLE_CORE_POSTWRITE
#define FBL_DIAG_ENABLE_CORE_READ_SECACCESSDELAY_FLAG
#define FBL_DIAG_ENABLE_CORE_SEGMENTHANDLING
#define FBL_DIAG_ENABLE_CORE_WRITE_SECACCESSDELAY_FLAG

#define FBL_DIAG_ENABLE_OEM_TIMERTASK
#define FBL_DIAG_ENABLE_OEM_RR_RESPONSE

# define TESTER_PRESENT_TIMEOUT                 2000u

#define FBL_DIAG_ENABLE_SERVICE_PREHANDLER
#define FBL_DIAG_ENABLE_SERVICE_POSTHANDLER

#if defined( FBL_ENABLE_STAY_IN_BOOT )
# if !defined( FBL_DIAG_STAY_IN_BOOT_ARRAY )

#  define FBL_DIAG_STAY_IN_BOOT_ARRAY {  kDiagSidRoutineControl, kDiagSubStartRoutine, kDiagRoutineIdStayInBootHigh, kDiagRoutineIdStayInBootLow }
# endif
#endif

#define kFblDiagStateSecurityKeyAllowed         ( kFblDiagLastCoreStateIdx + 1u )
#define kFblDiagStateSecurityUnlock             ( kFblDiagLastCoreStateIdx + 2u )
#define kFblDiagStateFingerprintValid           ( kFblDiagLastCoreStateIdx + 3u )
#define kFblDiagStateEraseSucceeded             ( kFblDiagLastCoreStateIdx + 4u )
#define kFblDiagStateTransferDataAllowed        ( kFblDiagLastCoreStateIdx + 5u )
#define kFblDiagStateTransferDataSucceeded      ( kFblDiagLastCoreStateIdx + 6u )
#define kFblDiagStateChecksumAllowed            ( kFblDiagLastCoreStateIdx + 7u )
#define kFblDiagStateFlashDriverPresent         ( kFblDiagLastCoreStateIdx + 8u )
#define kFblDiagStateDownloadRunning            ( kFblDiagLastCoreStateIdx + 9u )

#define kFblDiagLastOemStateIdx                 kFblDiagStateFlashDriverPresent

#define FblDiagGetSecurityKeyAllowed()          GetFblDiagState( kFblDiagStateSecurityKeyAllowed )
#define FblDiagGetSecurityUnlock()              GetFblDiagState( kFblDiagStateSecurityUnlock )
#define FblDiagGetFingerprintValid()            GetFblDiagState( kFblDiagStateFingerprintValid )
#define FblDiagGetEraseSucceeded()              GetFblDiagState( kFblDiagStateEraseSucceeded )
#define FblDiagGetTransferDataAllowed()         GetFblDiagState( kFblDiagStateTransferDataAllowed )
#define FblDiagGetTransferDataSucceeded()       GetFblDiagState( kFblDiagStateTransferDataSucceeded )
#define FblDiagGetChecksumAllowed()             GetFblDiagState( kFblDiagStateChecksumAllowed )
#define FblDiagGetFlashDriverPresent()          GetFblDiagState( kFblDiagStateFlashDriverPresent )
#define FblDiagGetDownloadRunning()             GetFblDiagState( kFblDiagStateDownloadRunning )

#define kFblDiagResponseResetPostHandler           FblDiagDefaultPostHandler
#define kFblDiagResponseSdsPostHandler             FblDiagDefaultPostHandler

#define kDiagSubDtcOn                                    0x01u
#define kDiagSubDtcOff                                   0x02u

#if !defined( kFblDiagSubRequestSeed )
# define kFblDiagSubRequestSeed                          0x11u
#endif
#if !defined( kFblDiagSubSendKey )
# define kFblDiagSubSendKey                              0x12u
#endif

#if !defined( kFblDiagSecurityAccessSessionMask )
# define kFblDiagSecurityAccessSessionMask kFblDiagOptionSessionProgramming
#endif

#define kSecSeedLength                                   SEC_SEED_LENGTH
#define kSecKeyLength                                    SEC_KEY_LENGTH

#define kDiagRoutineIdCheckProgPreCond                   0x0203u
#define kDiagRoutineIdCheckProgPreCondHigh               GET_ID_HIGH(kDiagRoutineIdCheckProgPreCond)
#define kDiagRoutineIdCheckProgPreCondLow                GET_ID_LOW(kDiagRoutineIdCheckProgPreCond)
#define kDiagRoutineIdEraseMemory                        0xFF00u
#define kDiagRoutineIdEraseMemoryHigh                    GET_ID_HIGH(kDiagRoutineIdEraseMemory)
#define kDiagRoutineIdEraseMemoryLow                     GET_ID_LOW(kDiagRoutineIdEraseMemory)
#define kDiagRoutineIdChecksum                           0x0202u
#define kDiagRoutineIdChecksumHigh                       GET_ID_HIGH(kDiagRoutineIdChecksum)
#define kDiagRoutineIdChecksumLow                        GET_ID_LOW(kDiagRoutineIdChecksum)
#define kDiagRoutineIdCheckProgDep                       0xFF01u
#define kDiagRoutineIdCheckProgDepHigh                   GET_ID_HIGH(kDiagRoutineIdCheckProgDep)
#define kDiagRoutineIdCheckProgDepLow                    GET_ID_LOW(kDiagRoutineIdCheckProgDep)
#if defined ( FBL_ENABLE_STAY_IN_BOOT )
# define kDiagRoutineIdStayInBoot                        0xF518u
# define kDiagRoutineIdStayInBootHigh                    GET_ID_HIGH(kDiagRoutineIdStayInBoot)
# define kDiagRoutineIdStayInBootLow                     GET_ID_LOW(kDiagRoutineIdStayInBoot)
#endif

#define kDiagRoutineIdSecretService                      0x1248u
#define kDiagRoutineIdSecretServiceHigh                  GET_ID_HIGH(kDiagRoutineIdSecretService)
#define kDiagRoutineIdSecretServiceLow                   GET_ID_LOW(kDiagRoutineIdSecretService)
#define kDiagRoutineIdLoadSecurityKey                    0x0207u
#define kDiagRoutineIdLoadSecurityKeyHigh                GET_ID_HIGH(kDiagRoutineIdLoadSecurityKey)
#define kDiagRoutineIdLoadSecurityKeyLow                 GET_ID_LOW(kDiagRoutineIdLoadSecurityKey)
#define kDiagRoutineIdAppHwidCheck                       0x0401u
#define kDiagRoutineIdAppHwidCheckHigh                   GET_ID_HIGH(kDiagRoutineIdAppHwidCheck)
#define kDiagRoutineIdAppHwidCheckLow                    GET_ID_LOW(kDiagRoutineIdAppHwidCheck)
#define kDiagRoutineIdCheckValidModule                   0x0402u
#define kDiagRoutineIdCheckValidModuleHigh               GET_ID_HIGH(kDiagRoutineIdCheckValidModule)
#define kDiagRoutineIdCheckValidModuleLow                GET_ID_LOW(kDiagRoutineIdCheckValidModule)
#define kDiagRoutineIdInitGenealogyBlock                 0x0404u
#define kDiagRoutineIdInitGenealogyBlockHigh             GET_ID_HIGH(kDiagRoutineIdInitGenealogyBlock)
#define kDiagRoutineIdInitGenealogyBlockLow              GET_ID_LOW(kDiagRoutineIdInitGenealogyBlock)
#define kDiagRoutineIdCompAndStoreSignature              0x0406u
#define kDiagRoutineIdCompAndStoreSignatureHigh          GET_ID_HIGH(kDiagRoutineIdCompAndStoreSignature)
#define kDiagRoutineIdCompAndStoreSignatureLow           GET_ID_LOW(kDiagRoutineIdCompAndStoreSignature)

#define kDiagCheckVerificationOk                         0x00u
#define kDiagCheckVerificationFailed                     0x01u
#define kDiagEraseMemoryOk                               0x00u
#define kDiagEraseMemoryFailed                           0x01u
#define kDiagCheckCompatibilityOk                        0x00u
#define kDiagCheckCompatibilityFailed                    0x01u
#define kDiagCheckCompatibilitySwHw                      0x02u
#define kDiagCheckCompatibilitySwSw                      0x03u
#define kDiagCheckCompatibilityBlockMissing              0x04u

#if(SEC_SECURITY_CLASS == SEC_CLASS_DDD)
# define kSecCRCLength                                   SEC_VERIFY_CLASS_DDD_VERIFY_SIZE
# define kSecSigLength                                   0x00u
#else
# if defined( kSecCRCLength)
# else
#  define kSecCRCLength                                  0x00u
# endif
# if(SEC_SECURITY_CLASS == SEC_CLASS_C )
#  define kSecSigLength                                  SEC_VERIFY_CLASS_C_VERIFY_SIZE
# endif
# if(SEC_SECURITY_CLASS == SEC_CLASS_CCC )
#  define kSecSigLength                                  SEC_VERIFY_CLASS_CCC_VERIFY_SIZE
# endif
#endif

#if !defined( kDiagWriteFingerprint )
# define kDiagWriteFingerprint                           0xF15Au
#endif
#define kDiagWriteFingerprintHigh                        GET_ID_HIGH(kDiagWriteFingerprint)
#define kDiagWriteFingerprintLow                         GET_ID_LOW(kDiagWriteFingerprint)

#define kDiagReturnValidationOk                          0x5Cu
#define kDiagReturnValidationFailed                      (kFblFailed)

#define kDiagRqlDiagnosticSessionControlParameter           0u
#define kDiagRqlSecurityAccessSeedParameter                 0u
#define kDiagRqlSecurityAccessKeyParameter                  kSecKeyLength
#if !defined( kDiagRqlWriteDataByIdentifierFingerPrintParameter )
# define kDiagRqlWriteDataByIdentifierFingerPrintParameter  9u
#endif
#define kDiagRqlRoutineControlCheckRoutineParameter         (kSecCRCLength + kSecSigLength)
#define kDiagRqlRoutineControlAddrAndLenFormatIdParameter   1u
#if defined( FBL_DIAG_ENABLE_CONTROLDTC_OPTIONRECORD )
# define kDiagRqlControlDTCSettingParameter                 3u
#else
# define kDiagRqlControlDTCSettingParameter                 0u
#endif

#define kDiagRqlRoutineControlAppHwidCheckParameter         0u
#define kDiagRqlRoutineControlCompAndStoreSigParameter      16u
#define kDiagRqlRoutineControlCheckValidModuleParameter     0u
#define kDiagRqlRoutineControlInitGenealogyBlockParameter   0u
#define kDiagRqlRoutineControlLoadSecurityKeyParameter      17u
#define kDiagRqlRoutineControlSecretServiceParameter        10u

#define kDiagRqlServiceWithSubfunction             1u
#define kDiagRqlDiagnosticSessionControl           (1u + kDiagRqlDiagnosticSessionControlParameter)
#define kDiagRqlEcuReset                           1u
#define kDiagRqlReadDataByIdentifier               2u
#define kDiagRqlSecurityAccessSeed                 (1u + kDiagRqlSecurityAccessSeedParameter)
#define kDiagRqlSecurityAccessKey                  (1u + kDiagRqlSecurityAccessKeyParameter)
#define kDiagRqlCommunicationControl               2u
#define kDiagRqlWriteDataByIdentifier              2u
#define kDiagRqlWriteDataByIdentifierFingerPrint   (kDiagRqlWriteDataByIdentifier + kDiagRqlWriteDataByIdentifierFingerPrintParameter)
#define kDiagRqlRoutineControl                     3u
#define kDiagRqlRoutineControlCheckRoutine         (kDiagRqlRoutineControl + kDiagRqlRoutineControlCheckRoutineParameter)
#define kDiagRqlRoutineControlEraseRoutine         kDiagRqlRoutineControl
#define kDiagRqlRoutineControlProgPreCond          kDiagRqlRoutineControl
#define kDiagRqlRoutineControlCheckProgDep         kDiagRqlRoutineControl
#define kDiagRqlRoutineControlForceBoot            kDiagRqlRoutineControl

#define kDiagRqlRoutineControlAppHwidCheck         (kDiagRqlRoutineControl + kDiagRqlRoutineControlAppHwidCheckParameter)
#define kDiagRqlRoutineControlCompAndStoreSig      (kDiagRqlRoutineControl + kDiagRqlRoutineControlCompAndStoreSigParameter)
#define kDiagRqlRoutineControlCheckValidModule     (kDiagRqlRoutineControl + kDiagRqlRoutineControlCheckValidModuleParameter)
#define kDiagRqlRoutineControlInitGenealogyBlock   (kDiagRqlRoutineControl + kDiagRqlRoutineControlInitGenealogyBlockParameter)
#define kDiagRqlRoutineControlLoadSecurityKey      (kDiagRqlRoutineControl + kDiagRqlRoutineControlLoadSecurityKeyParameter)
#define kDiagRqlRoutineControlSecretService        (kDiagRqlRoutineControl + kDiagRqlRoutineControlSecretServiceParameter)

#define kDiagRqlRequestDownload                    2u
#define kDiagRqlTransferData                       1u
#define kDiagRqlRequestTransferExit                0u
#define kDiagRqlTesterPresent                      1u
#define kDiagRqlControlDTCSetting                  (1u + kDiagRqlControlDTCSettingParameter)

#define kDiagRslEcuResetParameter                           0u
#define kDiagRslDiagnosticSessionControlParameter           4u
#define kDiagRslSecurityAccessSeedParameter                 kSecSeedLength
#define kDiagRslSecurityAccessKeyParameter                  0u
#define kDiagRslRoutineControlEraseRoutineParameter         1u
#define kDiagRslRoutineControlCheckRoutineParameter         1u
#define kDiagRslRoutineControlCheckPreCondParameter         3u

#define kDiagRslRoutineControlAppHwidCheckRoutineParameter  1u
#define kDiagRslRoutineControlCompAndStoreSigParameter      1u
#define kDiagRslRoutineControlCheckValidModuleParameter     1u
#define kDiagRslRoutineControlInitGenealogyBlockParameter   0u
#define kDiagRslRoutineControlLoadSecurityKeyParameter      2u
#define kDiagRslRoutineControlSecretServiceParameter        0u

#define kDiagRslTransferDataParameter                       0u
#define kDiagRslRequestTransferExitParameter                0u

#define kDiagRslDiagnosticSessionControl           (1u + kDiagRslDiagnosticSessionControlParameter)
#define kDiagRslEcuReset                           (1u + kDiagRslEcuResetParameter)
#define kDiagRslSecurityAccessSeed                 (1u + kDiagRslSecurityAccessSeedParameter)
#define kDiagRslSecurityAccessKey                  (1u + kDiagRslSecurityAccessKeyParameter)
#define kDiagRslCommunicationControl               1u
#define kDiagRslWriteDataByIdentifier              2u
#define kDiagRslRoutineControlEraseRoutine         (3u + kDiagRslRoutineControlEraseRoutineParameter)
#define kDiagRslRoutineControlCheckRoutine         (3u + kDiagRslRoutineControlCheckRoutineParameter)
#define kDiagRslRoutineControlCheckPreCond         (3u + kDiagRslRoutineControlCheckPreCondParameter)

#define kDiagRslRoutineControlAppHwidCheck         (3u + kDiagRslRoutineControlAppHwidCheckRoutineParameter)
#define kDiagRslRoutineControlCompAndStoreSig      (3u + kDiagRslRoutineControlCompAndStoreSigParameter)
#define kDiagRslRoutineControlCheckValidModule     (3u + kDiagRslRoutineControlCheckValidModuleParameter)
#define kDiagRslRoutineControlInitGenealogyBlock   (3u + kDiagRslRoutineControlInitGenealogyBlockParameter)
#define kDiagRslRoutineControlLoadSecurityKey      (3u + kDiagRslRoutineControlLoadSecurityKeyParameter)
#define kDiagRslRoutineControlSecretService        (3u + kDiagRslRoutineControlSecretServiceParameter)

#if defined ( FBL_ENABLE_STAY_IN_BOOT )
# define kDiagRslRoutineControlStayInBoot          3u
#endif
#define kDiagRslRequestDownload                    1u
#define kDiagRslTransferData                       (1u + kDiagRslTransferDataParameter)
#define kDiagRslRequestTransferExit                (0u + kDiagRslRequestTransferExitParameter)
#define kDiagRslTesterPresent                      1u
#define kDiagRslControlDTCSetting                  1u

#define kDiagFmtServiceId                    0u
#define kDiagFmtpbDiagData                   1u
#define kDiagFmtSubparam                     (kDiagFmtServiceId + 1u)
#define kDiagFmtDataIdSize                   2u
#define kDiagFmtDataIdHigh                   (kDiagFmtServiceId + 1u)
#define kDiagFmtDataIdLow                    (kDiagFmtDataIdHigh + 1u)
#define kDiagFmtSubFctDataIdHigh             (kDiagFmtSubparam + 1u)
#define kDiagFmtSubFctDataIdLow              (kDiagFmtSubFctDataIdHigh + 1u)
#define kDiagFmtDataRecord                   (kDiagFmtDataIdLow + 1u)
#define kDiagFmtSequenceCnt                  (kDiagFmtServiceId + 1u)
#define kDiagFmtDataOffset                   (kDiagFmtSequenceCnt + 1u)
#define kDiagFmtFormatOffset                 2u
#define kDiagFmtNegResponse                  (kDiagFmtSubparam + 1u)
#define kDiagFmtAddrOffset                   3u
#define kDiagFmtRoutineIdHigh                (kDiagFmtSubparam + 1u)
#define kDiagFmtRoutineIdLow                 (kDiagFmtRoutineIdHigh + 1u)
#define kDiagFmtRoutineStatus                (kDiagFmtRoutineIdLow + 1u)
#define kDiagFmtRoutineAlfi                  (kDiagFmtRoutineIdLow + 1u)
#define kDiagFmtStartAddress                 (kDiagFmtRoutineAlfi + 1u)
#define kDiagFmtStopAddress                  (kDiagFmtStartAddress + 4u)
#define kDiagFmtChecksumHigh                 (kDiagFmtStopAddress + 4u)
#define kDiagFmtChecksumLow                  (kDiagFmtChecksumHigh + 1u)
#define kDiagFmtSeedKeyStart                 (kDiagFmtSubparam + 1u)

#define kDiagLocFmtSubparam                              0u
#define kDiagLocFmtSubfunction                           0u
#define kDiagLocFmtDataIdHigh                            0u
#define kDiagLocFmtDataIdLow                             (kDiagLocFmtDataIdHigh + 1u)
#define kDiagLocFmtSubFctDataIdHigh                      (kDiagLocFmtSubfunction + 1u)
#define kDiagLocFmtSubFctDataIdLow                       (kDiagLocFmtSubFctDataIdHigh + 1u)
#define kDiagLocFmtDataRecord                            (kDiagLocFmtDataIdLow + 1u)
#define kDiagLocFmtSequenceCnt                           0u
#define kDiagLocFmtDataOffset                            (kDiagLocFmtSequenceCnt + 1u)
#define kDiagLocFmtFormatOffset                          1u
#define kDiagLocFmtNegResponse                           (kDiagLocFmtSubparam + 1u)
#define kDiagLocFmtAddrOffset                            2u
#define kDiagLocFmtRoutineIdHigh                         (kDiagLocFmtSubparam + 1u)
#define kDiagLocFmtRoutineIdLow                          (kDiagLocFmtRoutineIdHigh + 1u)
#define kDiagLocFmtRoutineStatus                         (kDiagLocFmtRoutineIdLow + 1u)
#define kDiagLocFmtRoutineAlfi                           (kDiagLocFmtRoutineIdLow + 1u)
#define kDiagLocFmtStartAddress                          (kDiagLocFmtRoutineAlfi + 1u)
#define kDiagLocFmtStopAddress                           (kDiagLocFmtStartAddress + 4u)
#define kDiagLocFmtChecksumHigh                          (kDiagLocFmtStopAddress + 4u)
#define kDiagLocFmtChecksumLow                           (kDiagLocFmtChecksumHigh + 1u)
#define kDiagLocFmtSeedKeyStart                          (kDiagLocFmtSubparam + 1u)

#if defined( FBL_ENABLE_DEBUG_STATUS )

# define FBL_ERR_NONE                        0x00u

# define FBL_ERR_FLASH_ERASE_ERROR           0x10u
# define FBL_ERR_FLASH_PROG_ERROR            0x11u
# define FBL_ERR_FLASH_PROG_CONDITIONS       0x12u

# define FBL_ERR_APPL_OVERLAPPING            0x20u
# define FBL_ERR_APPL_NOT_ALIGNED            0x21u
# define FBL_ERR_TOO_MANY_SEGMENTS_IN_MODULE 0x22u
# define FBL_ERR_NO_MEMORY_REGION_FOUND      0x23u
# define FBL_ERR_SEED_GENERATION_FAILED      0x24u
# define FBL_ERR_GAP_FILL                    0x25u
# define FBL_ERR_VERIFICATION                0x26u

# define FBL_ERR_FLASHCODE_INIT_FAILED       0x30u
# define FBL_ERR_FLASHCODE_EXCEEDS_MEMORY    0x31u
# define FBL_ERR_FLASHCODE_NOT_ACCEPTED      0x32u

# define FBL_ERR_LBT_MISSING_INVALID_FORMAT  0x40u
# define FBL_ERR_LBT_ADDR_MISMATCH           0x41u
# define FBL_ERR_LBT_BLOCK_INDEX_EXCEEDED    0x42u
# define FBL_ERR_LBT_NOT_REPROGRAMMABLE      0x43u
# define FBL_ERR_LBT_BLOCK_INDEX_ILLEGAL     0x44u

# define FBL_ERR_DATA_OVERFLOW               0x50u

# define FblErrStatSetSId(id)                (errStatLastServiceId = (id))
# define FblErrStatSetState(state)           (errStatFblStates = (state))
# define FblErrStatSetFlashDrvError(error)   (errStatFlashDrvErrorCode = (error))
# define FblErrStatSetFlashDrvVersion()      \
{                                            \
   errStatFlashDrvVersion[0] = flashCode[0]; \
   errStatFlashDrvVersion[1] = flashCode[1]; \
   errStatFlashDrvVersion[2] = flashCode[3]; \
}
# define FblErrStatSetError(error)           (errStatErrorCode = (error))
# define FblErrStatSetBlockNr(blockNumber)   (errStatDescriptor.blockNr = (blockNumber))
# define FblErrStatSetAddress(address)       (errStatDescriptor.blockStartAddress = (address))
#else
# define FblErrStatSetSId(id)
# define FblErrStatSetState(state)
# define FblErrStatSetFlashDrvError(error)
# define FblErrStatSetFlashDrvVersion()
# define FblErrStatSetError(error)
# define FblErrStatSetBlockNr(blockNr)
# define FblErrStatSetAddress(address)
#endif

#if !defined( kDiagSubDefaultEncryption )
# define kDiagSubDefaultEncryption        0x01u
#endif

#if !defined(kDiagSubDefaultCompression)
# define kDiagSubDefaultCompression       0x01u
#endif

#if !defined( kDiagSubDefaultDelta )
# define kDiagSubDefaultDelta             0x02u
#endif

#if defined( FBL_ENABLE_DEBUG_STATUS )

V_MEMRAM0 extern V_MEMRAM1      vuint16            V_MEMRAM2      errStatErrorCode;
V_MEMRAM0 extern V_MEMRAM1      vuint16            V_MEMRAM2      errStatFblStates;
V_MEMRAM0 extern V_MEMRAM1      vuint8             V_MEMRAM2      errStatLastServiceId;
V_MEMRAM0 extern V_MEMRAM1      vuint8             V_MEMRAM2      errStatFlashDrvVersion[3];
V_MEMRAM0 extern V_MEMRAM1      vuint16            V_MEMRAM2      errStatFlashDrvErrorCode;
V_MEMRAM0 extern V_MEMRAM1      tBlockDescriptor   V_MEMRAM2      errStatDescriptor;
#endif

#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT ) && \
    defined( FBL_MEM_ENABLE_VERIFY_PIPELINED )
# error "Output verification and pipelined verification mustn't be combined."
#endif
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT ) || \
    defined( FBL_MEM_ENABLE_VERIFY_PIPELINED )
#else
# error "At least one verification method must be activated."
#endif

#endif
