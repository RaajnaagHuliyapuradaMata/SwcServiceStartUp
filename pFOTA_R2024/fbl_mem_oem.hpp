

#ifndef FBL_MEM_OEM_H
#define FBL_MEM_OEM_H

#define FBLLIB_MEM_VECTOR_VERSION                0x0801u
#define FBLLIB_MEM_VECTOR_RELEASE_VERSION        0x00u

#define FBL_MEM_API_REFERENCE_VERSION_MAJOR     0x04u

#define FBL_MEM_API_REFERENCE_VERSION_MINOR     0x00u

#define FBL_MEM_API_REFERENCE_VERSION_RELEASE   0x00u

#define FBL_MEM_BUFFER_SIZE               FBL_DIAG_BUFFER_LENGTH

#define FBL_MEM_DEFAULT_PREAMBLE_LENGTH   2u

#define FBL_MEM_MAX_PREAMBLE_LENGTH       2u

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

# if defined( __ApplFblMemIsDataProcessingRequired )
# else

#  define __ApplFblMemIsDataProcessingRequired(dataFormat) \
   (tFblResult) (GetOemProcessingModeSupported(dataFormat) ? kFblOk : kFblFailed)
# endif

# if defined( __ApplFblMemIsStreamOutputRequired )
# else

#  define __ApplFblMemIsStreamOutputRequired(dataFormat) \
   ((tFblResult)(GetOemStreamModeSupported(dataFormat)) ? kFblOk : kFblFailed)
# endif
#else

# if defined( __ApplFblMemIsDataProcessingRequired )
# else

#  define __ApplFblMemIsDataProcessingRequired(dataFormat) \
   ((tFblResult)((kDiagSubNoDataProcessing == (dataFormat)) ? kFblFailed : kFblOk))
# endif
#endif

#if defined( FBL_MEM_ENABLE_VERIFY_PIPELINED )
# define FBL_MEM_ENABLE_SEGMENT_HANDLING
#endif

#if defined( SEC_ENABLE_VERIFICATION_ADDRESS_LENGTH )

# if(SEC_SECURITY_CLASS != SEC_CLASS_DDD )

#  define FBL_MEM_ENABLE_VERIFY_INPUT_ADDRESS_LENGTH

#  define FBL_MEM_ENABLE_VERIFY_PROCESSED_ADDRESS_LENGTH

#  define FBL_MEM_ENABLE_VERIFY_PIPELINED_ADDRESS_LENGTH
# endif
#endif

#define FBL_MEM_SIG_RESULT_BUFFER_SIZE                   kDiagSigBufLength

#define __ApplFblMemPreWrite()                     FblDiagMemPreWrite()
#define __ApplFblMemPostWrite()                    FblDiagMemPostWrite()

#define __ApplFblMemPreErase()                     FblDiagMemPreWrite()
#define __ApplFblMemPostErase()                    FblDiagMemPostWrite()

#define FBL_MEM_WD_TRIGGER_DEFAULT                 (FBL_NO_TRIGGER)

#define FBL_MEM_TRIGGER_STATUS_OVERWRITE           vuint8

#define __ApplFblMemWdTrigger()                    FblLookForWatchdog()

#define __ApplFblMemAdaptiveRcrRp()                FblRealTimeSupport()

#define __ApplFblMemIsRcrRpActive()                ((tFblResult)(FblDiagGetRcrRpInProgress() ? kFblOk : kFblFailed))

#define __ApplFblMemForcedRcrRp()                  DiagExRCRResponsePending(kForceSendResponsePending)

#define FBL_MEM_ENABLE_EXT_TRIGGER_DATA_PROC

#define FBL_MEM_ENABLE_EXT_TRIGGER_INPUT_VERIFY

#define FBL_MEM_ENABLE_EXT_TRIGGER_OUTPUT_VERIFY

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

# define __ApplFblMemReportProgress(progressInfo)
#endif

#define FBL_MEM_ENABLE_STATUS_OVERWRITE

#define FBL_MEM_DISABLE_STATUS_REMAPPING

#define FBL_MEM_STATUS_TYPE                           vuint8

#if defined( FBL_MEM_ENABLE_STATUS_OVERWRITE ) || \
    defined( FBL_MEM_ENABLE_STATUS_REMAPPING )

# define FBL_MEM_STATUS_Ok                            kDiagErrorNone
# define FBL_MEM_STATUS_Failed                        kDiagNrcConditionsNotCorrect

# define FBL_MEM_STATUS_BlockEraseSequence            kDiagNrcRequestSequenceError

# define FBL_MEM_STATUS_BlockStartSequence            kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_BlockStartParam               kDiagNrcConditionsNotCorrect

# define FBL_MEM_STATUS_BlockEndSequence              kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_BlockEndVerifyFinalize        kDiagNrcGeneralProgrammingFailure

# define FBL_MEM_STATUS_BlockVerifySequence           kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_BlockVerifyInputVerify        kDiagNrcGeneralReject
# define FBL_MEM_STATUS_BlockVerifyProcessedVerify    kDiagNrcGeneralReject
# define FBL_MEM_STATUS_BlockVerifyPipeVerify         kDiagNrcGeneralReject
# define FBL_MEM_STATUS_BlockVerifyOutputVerify       kDiagNrcGeneralReject

# define FBL_MEM_STATUS_SegmentStartSequence          kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_SegmentStartDataProcInit      kDiagNrcUploadDownloadNotAccepted
# define FBL_MEM_STATUS_SegmentStartStreamOutInit     kDiagNrcUploadDownloadNotAccepted
# define FBL_MEM_STATUS_SegmentStartVerifyInit        kDiagNrcConditionsNotCorrect
# define FBL_MEM_STATUS_SegmentStartVerifyCompute     kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_SegmentStartSegmentCount      kDiagNrcRequestOutOfRange

# define FBL_MEM_STATUS_SegmentEndSequence            kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_SegmentEndInsufficientData    kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_SegmentEndPost                kDiagNrcConditionsNotCorrect

# define FBL_MEM_STATUS_DataIndSequence               kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_DataIndParam                  kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_DataIndOverflow               kDiagNrcTransferDataSuspended

# define FBL_MEM_STATUS_DataProc                      kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_DataProcConsume               kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_DataProcDeinit                kDiagNrcConditionsNotCorrect

# define FBL_MEM_STATUS_StreamOutput                  kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_StreamOutputConsume           kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_StreamOutputOverflow          kDiagNrcTransferDataSuspended
# define FBL_MEM_STATUS_StreamOutputDeinit            kDiagNrcConditionsNotCorrect

# define FBL_MEM_STATUS_DriverResumeWrite             kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_DriverWrite                   kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_DriverErase                   kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_DriverRemainder               kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_DriverSuspendWrite            kDiagNrcGeneralProgrammingFailure

# define FBL_MEM_STATUS_ProgramOverflow               kDiagNrcTransferDataSuspended
# define FBL_MEM_STATUS_ProgramOutsideFbt             kDiagNrcTransferDataSuspended
# define FBL_MEM_STATUS_ProgramUnalignedAddress       kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_ProgramDriverNotReady         kDiagNrcRequestSequenceError
# define FBL_MEM_STATUS_ProgramPreWrite               kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_ProgramPostWrite              kDiagNrcGeneralProgrammingFailure

# define FBL_MEM_STATUS_EraseOutsideFbt               kDiagNrcRequestOutOfRange
# define FBL_MEM_STATUS_EraseDriverNotReady           kDiagNrcConditionsNotCorrect
# define FBL_MEM_STATUS_ErasePreErase                 kDiagNrcConditionsNotCorrect
# define FBL_MEM_STATUS_ErasePostErase                kDiagNrcConditionsNotCorrect

# define FBL_MEM_STATUS_VerifyCompute                 kDiagNrcGeneralProgrammingFailure
# define FBL_MEM_STATUS_VerifyFinalize                kDiagNrcGeneralProgrammingFailure

# define FBL_MEM_STATUS_PassThroughLocal              kDiagNrcConditionsNotCorrect
# define FBL_MEM_STATUS_PassThroughRemote             kDiagNrcConditionsNotCorrect
#endif

#if defined( FBL_ENABLE_DEBUG_STATUS )

# define FBL_MEM_ENABLE_EXT_STATUS

# define FBL_MEM_EXT_STATUS_Ok(status)
# define FBL_MEM_EXT_STATUS_Failed(status)

# define FBL_MEM_EXT_STATUS_BlockEraseSequence(status)

# define FBL_MEM_EXT_STATUS_BlockStartSequence(status)
# define FBL_MEM_EXT_STATUS_BlockStartParam(status)

# define FBL_MEM_EXT_STATUS_BlockEndSequence(status)
# define FBL_MEM_EXT_STATUS_BlockEndVerifyFinalize(status)

# define FBL_MEM_EXT_STATUS_BlockVerifySequence(status)
# define FBL_MEM_EXT_STATUS_BlockVerifySigVerify(status)
# define FBL_MEM_EXT_STATUS_BlockVerifyInputVerify(status)
# define FBL_MEM_EXT_STATUS_BlockVerifyProcessedVerify(status)
# define FBL_MEM_EXT_STATUS_BlockVerifyPipeVerify(status)
# define FBL_MEM_EXT_STATUS_BlockVerifyOutputVerify(status)

# define FBL_MEM_EXT_STATUS_SegmentStartSequence(status)
# define FBL_MEM_EXT_STATUS_SegmentStartDataProcInit(status)
# define FBL_MEM_EXT_STATUS_SegmentStartStreamOutInit(status)
# define FBL_MEM_EXT_STATUS_SegmentStartVerifyInit(status)
# define FBL_MEM_EXT_STATUS_SegmentStartVerifyCompute(status)
# define FBL_MEM_EXT_STATUS_SegmentStartSegmentCount(status)   FblErrStatSetError(FBL_ERR_TOO_MANY_SEGMENTS_IN_MODULE)

# define FBL_MEM_EXT_STATUS_SegmentEndSequence(status)
# define FBL_MEM_EXT_STATUS_SegmentEndInsufficientData(status)
# define FBL_MEM_EXT_STATUS_SegmentEndPost(status)

# define FBL_MEM_EXT_STATUS_DataIndSequence(status)
# define FBL_MEM_EXT_STATUS_DataIndParam(status)
# define FBL_MEM_EXT_STATUS_DataIndOverflow(status)            FblErrStatSetState(FBL_ERR_DATA_OVERFLOW)

# define FBL_MEM_EXT_STATUS_DataProc(status)
# define FBL_MEM_EXT_STATUS_DataProcConsume(status)
# define FBL_MEM_EXT_STATUS_DataProcDeinit(status)

# define FBL_MEM_EXT_STATUS_StreamOutput(status)
# define FBL_MEM_EXT_STATUS_StreamOutputConsume(status)
# define FBL_MEM_EXT_STATUS_StreamOutputOverflow(status)
# define FBL_MEM_EXT_STATUS_StreamOutputDeinit(status)

# define FBL_MEM_EXT_STATUS_DriverResumeWrite(status)

# define FBL_MEM_EXT_STATUS_DriverWrite(status)                { FblErrStatSetFlashDrvError(status); FblErrStatSetError(FBL_ERR_FLASH_PROG_ERROR); }
# define FBL_MEM_EXT_STATUS_DriverErase(status)                { FblErrStatSetFlashDrvError(status); FblErrStatSetError(FBL_ERR_FLASH_ERASE_ERROR); }
# define FBL_MEM_EXT_STATUS_DriverRemainder(status)
# define FBL_MEM_EXT_STATUS_DriverSuspendWrite(status)

# define FBL_MEM_EXT_STATUS_ProgramOverflow(status)            FblErrStatSetState(FBL_ERR_DATA_OVERFLOW)
# define FBL_MEM_EXT_STATUS_ProgramOutsideFbt(status)          FblErrStatSetError(FBL_ERR_NO_MEMORY_REGION_FOUND)
# define FBL_MEM_EXT_STATUS_ProgramUnalignedAddress(status)    FblErrStatSetError(FBL_ERR_FLASH_PROG_ERROR)
# define FBL_MEM_EXT_STATUS_ProgramDriverNotReady(status)      FblErrStatSetError(FBL_ERR_FLASHCODE_INIT_FAILED)
# define FBL_MEM_EXT_STATUS_ProgramPreWrite(status)
# define FBL_MEM_EXT_STATUS_ProgramPostWrite(status)

# define FBL_MEM_EXT_STATUS_EraseOutsideFbt(status)            FblErrStatSetError(FBL_ERR_NO_MEMORY_REGION_FOUND)
# define FBL_MEM_EXT_STATUS_EraseDriverNotReady(status)        FblErrStatSetError(FBL_ERR_FLASHCODE_INIT_FAILED)
# define FBL_MEM_EXT_STATUS_ErasePreErase(status)
# define FBL_MEM_EXT_STATUS_ErasePostErase(status)

# define FBL_MEM_EXT_STATUS_VerifyCompute(status)
# define FBL_MEM_EXT_STATUS_VerifyFinalize(status)

# define FBL_MEM_EXT_STATUS_PassThroughLocal(status)
# define FBL_MEM_EXT_STATUS_PassThroughRemote(status)

# define FBL_MEM_EXT_STATUS_ProgramAddress(status)             FblErrStatSetAddress(status)
# define FBL_MEM_EXT_STATUS_EraseAddress(status)               FblErrStatSetAddress(status)
#endif

#endif

