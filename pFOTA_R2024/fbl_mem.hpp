

#ifndef __FBL_MEM_H__
#define __FBL_MEM_H__

#define FBLLIB_MEM_VERSION            0x0405u
#define FBLLIB_MEM_RELEASE_VERSION    0x02u

#define FBL_MEM_API_VERSION_MAJOR     0x04u

#define FBL_MEM_API_VERSION_MINOR     0x05u

#define FBL_MEM_API_VERSION_RELEASE   0x00u

#include "fbl_mem_oem.hpp"

#define FblMemTaskIsPending()    (fblMemProgState >= kFblMemProgState_Suspended)

#define FblMemTaskIsActive()     (fblMemProgState >= kFblMemProgState_SuspendPending)

#define FBL_MEM_SOURCE_HANDLE_DEFAULT  0u

#if defined( FBL_MEM_SOURCE_COUNT )
# if(FBL_MEM_SOURCE_COUNT > 1u)
#  if defined( FBL_MEM_ENABLE_MULTI_SOURCE )
#  else

#   define FBL_MEM_ENABLE_MULTI_SOURCE
#  endif
# endif
#endif

# define FblMemRemapStatus(status)   ((FBL_MEM_STATUS_TYPE)(status))

#if defined( FBL_MEM_PROC_SEGMENTATION )
#else

# define FBL_MEM_PROC_SEGMENTATION     FBL_MEM_PROC_BUFFER_SIZE
#endif

#if defined( FBL_ENABLE_GAP_FILL )
# if defined( FBL_MEM_ENABLE_GAP_FILL) || \
     defined( FBL_MEM_DISABLE_GAP_FILL )

# else
#  define FBL_MEM_ENABLE_GAP_FILL
# endif
#endif

#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT ) || \
    defined( FBL_MEM_ENABLE_GAP_FILL )
# if defined( FBL_MEM_ENABLE_SEGMENT_HANDLING ) || \
     defined( FBL_MEM_DISABLE_SEGMENT_HANDLING )

# else

#  define FBL_MEM_ENABLE_SEGMENT_HANDLING
# endif
#endif

#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )     || \
    defined( FBL_MEM_ENABLE_SEGMENT_HANDLING )  || \
    defined( FBL_ENABLE_PROCESSED_DATA_LENGTH ) || \
    defined( FBL_MEM_ENABLE_STREAM_OUTPUT )     || \
    defined( FBL_MEM_ENABLE_GAP_FILL )          || \
    defined( FBL_MEM_ENABLE_PROGRESS_INFO )

# define FBL_MEM_ENABLE_GLOBAL_BLOCK_INFO
#endif

#if defined( FBL_MEM_VERIFY_OK_OVERWRITE )
#define FBL_MEM_VERIFY_OK                       (FBL_MEM_VERIFY_OK_OVERWRITE)
#else
#define FBL_MEM_VERIFY_OK                       (tFblMemVerifyStatus)(SECM_OK)
#endif
#if defined( FBL_MEM_VERIFY_STATE_INIT_OVERWRITE )
#define FBL_MEM_VERIFY_STATE_INIT               (FBL_MEM_VERIFY_STATE_INIT_OVERWRITE)
#else
#define FBL_MEM_VERIFY_STATE_INIT               kHashInit
#endif
#if defined( FBL_MEM_VERIFY_STATE_COMPUTE_OVERWRITE )
#define FBL_MEM_VERIFY_STATE_COMPUTE            (FBL_MEM_VERIFY_STATE_COMPUTE_OVERWRITE)
#else
#define FBL_MEM_VERIFY_STATE_COMPUTE            kHashCompute
#endif
#if defined( FBL_MEM_VERIFY_STATE_FINALIZE_OVERWRITE )
#define FBL_MEM_VERIFY_STATE_FINALIZE           (FBL_MEM_VERIFY_STATE_FINALIZE_OVERWRITE)
#else
#define FBL_MEM_VERIFY_STATE_FINALIZE           kHashFinalize
#endif
#if defined( FBL_MEM_VERIFY_STATE_VERIFY_OVERWRITE )
#define FBL_MEM_VERIFY_STATE_VERIFY             (FBL_MEM_VERIFY_STATE_VERIFY_OVERWRITE)
#else
#define FBL_MEM_VERIFY_STATE_VERIFY             kSigVerify
#endif

#define FBL_MEM_STATUS_NAME(name)         kFblMemStatus_ ## name
#define FBL_MEM_STATUS_DEFINE(name)       FBL_MEM_STATUS_ ## name

#if defined( FBL_MEM_ENABLE_STATUS_OVERWRITE )

# define FBL_MEM_STATUS_DEFINITION(name)  FBL_MEM_STATUS_NAME(name) = FBL_MEM_STATUS_DEFINE(name)
#else

# define FBL_MEM_STATUS_DEFINITION(name)  FBL_MEM_STATUS_NAME(name)
#endif

#if defined( FBL_MEM_ENABLE_STATUS_OVERWRITE )

#  if defined( FBL_MEM_STATUS_ProgramOverflow )
#  else

#   define FBL_MEM_STATUS_ProgramOverflow             FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_VerifyCompute )
#  else

#   define FBL_MEM_STATUS_VerifyCompute               FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_VerifyFinalize )
#  else

#   define FBL_MEM_STATUS_VerifyFinalize              FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_SegmentStartVerifyInit )
#  else

#   define FBL_MEM_STATUS_SegmentStartVerifyInit      FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_BlockEndVerifyFinalize )
#  else

#   define FBL_MEM_STATUS_BlockEndVerifyFinalize      FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_BlockVerifyInputVerify )
#  else

#   define FBL_MEM_STATUS_BlockVerifyInputVerify      FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_BlockVerifyPipeVerify )
#  else

#   define FBL_MEM_STATUS_BlockVerifyPipeVerify       FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_BlockVerifyOutputVerify )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_BlockVerifyOutputVerify
#  endif

#  if defined( FBL_MEM_STATUS_BlockStartParam )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_BlockStartParam
#  endif

#  if defined( FBL_MEM_STATUS_SegmentStartVerifyCompute )
#  else

#   define FBL_MEM_STATUS_SegmentStartVerifyCompute   FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_DataProc )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_DataProc
#  endif

#  if defined( FBL_MEM_STATUS_DataProcConsume )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_DataProcConsume
#  endif

#  if defined( FBL_MEM_STATUS_DataProcDeinit )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_DataProcDeinit
#  endif

#  if defined( FBL_MEM_STATUS_SegmentStartStreamOutInit )
#  else

#   define FBL_MEM_STATUS_SegmentStartStreamOutInit   FBL_MEM_STATUS_SegmentStartDataProcInit
#  endif

#  if defined( FBL_MEM_STATUS_StreamOutput )
#  else

#   define FBL_MEM_STATUS_StreamOutput                FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_StreamOutputConsume )
#  else

#   define FBL_MEM_STATUS_StreamOutputConsume         FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_StreamOutputOverflow )
#  else

#   define FBL_MEM_STATUS_StreamOutputOverflow        FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_StreamOutputDeinit )
#  else

#   define FBL_MEM_STATUS_StreamOutputDeinit          FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_DriverResumeWrite )
#  else

#   define FBL_MEM_STATUS_DriverResumeWrite           FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_DriverRemainder )
#  else

#   define FBL_MEM_STATUS_DriverRemainder             FBL_MEM_STATUS_Failed
#  endif

#  if defined( FBL_MEM_STATUS_BlockEraseSequence )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_BlockEraseSequence
#  endif

#  if defined( FBL_MEM_STATUS_EraseOutsideFbt )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_EraseOutsideFbt
#  endif

#  if defined( FBL_MEM_STATUS_EraseDriverNotReady )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_EraseDriverNotReady
#  endif

# if defined( __ApplFblMemPreErase )
#  if defined( FBL_MEM_STATUS_ErasePreErase )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_ErasePreErase
#  endif
# else
#  if defined( FBL_MEM_STATUS_ErasePreErase )
#  else

#   define FBL_MEM_STATUS_ErasePreErase               FBL_MEM_STATUS_Failed
#  endif
# endif

# if defined( __ApplFblMemPostErase )
#  if defined( FBL_MEM_STATUS_ErasePostErase )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_ErasePostErase
#  endif
# else
#  if defined( FBL_MEM_STATUS_ErasePostErase )
#  else

#   define FBL_MEM_STATUS_ErasePostErase              FBL_MEM_STATUS_Failed
#  endif
# endif

# if defined( __ApplFblMemDriverReady )
#  if defined( FBL_MEM_STATUS_EraseDriverNotReady )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_EraseDriverNotReady
#  endif
# else
#  if defined( FBL_MEM_STATUS_EraseDriverNotReady )
#  else

#   define FBL_MEM_STATUS_EraseDriverNotReady         FBL_MEM_STATUS_Failed
#  endif
# endif

#  if defined( FBL_MEM_STATUS_SegmentStartSegmentCount )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_SegmentStartSegmentCount
#  endif

# if defined( __ApplFblMemPostSegmentEnd )
#  if defined( FBL_MEM_STATUS_SegmentEndPost )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_SegmentEndPost
#  endif
# else
#  if defined( FBL_MEM_STATUS_SegmentEndPost )
#  else

#   define FBL_MEM_STATUS_SegmentEndPost              FBL_MEM_STATUS_Failed
#  endif
# endif

# if defined( __ApplFblMemDriverReady )
#  if defined( FBL_MEM_STATUS_ProgramDriverNotReady )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_ProgramDriverNotReady
#  endif
# else
#  if defined( FBL_MEM_STATUS_ProgramDriverNotReady )
#  else

#   define FBL_MEM_STATUS_ProgramDriverNotReady       FBL_MEM_STATUS_Failed
#  endif
# endif

# if defined( __ApplFblMemPreWrite )
#  if defined( FBL_MEM_STATUS_ProgramPreWrite )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_ProgramPreWrite
#  endif
# else
#  if defined( FBL_MEM_STATUS_ProgramPreWrite )
#  else

#   define FBL_MEM_STATUS_ProgramPreWrite             FBL_MEM_STATUS_Failed
#  endif
# endif

# if defined( __ApplFblMemPostWrite )
#  if defined( FBL_MEM_STATUS_ProgramPostWrite )
#  else
#   error Status overwrite value missing: FBL_MEM_STATUS_ProgramPostWrite
#  endif
# else
#  if defined( FBL_MEM_STATUS_ProgramPostWrite )
#  else

#   define FBL_MEM_STATUS_ProgramPostWrite            FBL_MEM_STATUS_Failed
#  endif
# endif

#endif

#if defined( FBL_MEM_VERIFY_STATUS_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_STATUS_TYPE_OVERWRITE             tFblMemVerifyStatus;
#else
typedef SecM_StatusType                                  tFblMemVerifyStatus;
#endif
#if defined( FBL_MEM_VERIFY_PARAM_TYPE_INPUT_OVERWRITE )
typedef FBL_MEM_VERIFY_PARAM_TYPE_INPUT_OVERWRITE        tFblMemVerifyParamInput;
#else
typedef SecM_SignatureParamType                          tFblMemVerifyParamInput;
#endif
#if defined( FBL_MEM_VERIFY_PARAM_TYPE_OUTPUT_OVERWRITE )
typedef FBL_MEM_VERIFY_PARAM_TYPE_OUTPUT_OVERWRITE       tFblMemVerifyParamOutput;
#else
typedef SecM_VerifyParamType                             tFblMemVerifyParamOutput;
#endif
#if defined( FBL_MEM_VERIFY_LENGTH_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_LENGTH_TYPE_OVERWRITE             tFblMemVerifyLength;
#else
typedef SecM_LengthType                                  tFblMemVerifyLength;
#endif
#if defined( FBL_MEM_VERIFY_SIZE_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_SIZE_TYPE_OVERWRITE               tFblMemVerifySize;
#else
typedef SecM_SizeType                                    tFblMemVerifySize;
#endif
#if defined( FBL_MEM_VERIFY_ADDRESS_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_ADDRESS_TYPE_OVERWRITE            tFblMemVerifyAddr;
#else
typedef SecM_AddrType                                    tFblMemVerifyAddr;
#endif
#if defined( FBL_MEM_VERIFY_DATA_PTR_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_DATA_PTR_TYPE_OVERWRITE           tFblMemVerifyDataPtr;
#else
typedef V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *           tFblMemVerifyDataPtr;
#endif
#if defined( FBL_MEM_VERIFY_WD_FCT_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_WD_FCT_TYPE_OVERWRITE             tFblMemVerifyWdFct;
#else
typedef FL_WDTriggerFctType                              tFblMemVerifyWdFct;
#endif
#if defined( FBL_MEM_VERIFY_READ_FCT_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_READ_FCT_TYPE_OVERWRITE           tFblMemVerifyReadFct;
#else
typedef FL_ReadMemoryFctType                             tFblMemVerifyReadFct;
#endif
#if defined( FBL_MEM_VERIFY_FCT_INPUT_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_FCT_INPUT_TYPE_OVERWRITE(tFblMemVerifyFctInput);
#else
typedef FBL_CALL_TYPE tFblMemVerifyStatus (*tFblMemVerifyFctInput) (V_MEMRAM1 tFblMemVerifyParamInput V_MEMRAM2 V_MEMRAM3 *);
#endif
#if defined( FBL_MEM_VERIFY_FCT_OUTPUT_TYPE_OVERWRITE )
typedef FBL_MEM_VERIFY_FCT_OUTPUT_TYPE_OVERWRITE(tFblMemVerifyFctOutput);
#else
typedef FBL_CALL_TYPE tFblMemVerifyStatus (*tFblMemVerifyFctOutput) (V_MEMRAM1 tFblMemVerifyParamOutput V_MEMRAM2 V_MEMRAM3 *);
#endif

#if defined( FBL_MEM_SEGMENT_LIST_TYPE_OVERWRITE )
typedef FBL_MEM_SEGMENT_LIST_TYPE_OVERWRITE              tFblMemSegmentList;
#else
typedef FL_SegmentListType                               tFblMemSegmentList;
#endif
#if defined( FBL_MEM_SEGMENT_LIST_ENTRY_TYPE_OVERWRITE )
typedef FBL_MEM_SEGMENT_LIST_ENTRY_TYPE_OVERWRITE        tFblMemSegmentListEntry;
#else
typedef FL_SegmentInfoType                               tFblMemSegmentListEntry;
#endif

typedef enum{
   FBL_MEM_STATUS_DEFINITION(Ok)
   ,FBL_MEM_STATUS_DEFINITION(Failed)

   ,FBL_MEM_STATUS_DEFINITION(BlockEraseSequence)

   ,FBL_MEM_STATUS_DEFINITION(BlockStartSequence)
   ,FBL_MEM_STATUS_DEFINITION(BlockStartParam)

   ,FBL_MEM_STATUS_DEFINITION(BlockEndSequence)
   ,FBL_MEM_STATUS_DEFINITION(BlockEndVerifyFinalize)

   ,FBL_MEM_STATUS_DEFINITION(BlockVerifySequence)
   ,FBL_MEM_STATUS_DEFINITION(BlockVerifyInputVerify)
   ,FBL_MEM_STATUS_DEFINITION(BlockVerifyProcessedVerify)
   ,FBL_MEM_STATUS_DEFINITION(BlockVerifyPipeVerify)
   ,FBL_MEM_STATUS_DEFINITION(BlockVerifyOutputVerify)

   ,FBL_MEM_STATUS_DEFINITION(SegmentStartSequence)
   ,FBL_MEM_STATUS_DEFINITION(SegmentStartDataProcInit)
   ,FBL_MEM_STATUS_DEFINITION(SegmentStartStreamOutInit)
   ,FBL_MEM_STATUS_DEFINITION(SegmentStartVerifyInit)
   ,FBL_MEM_STATUS_DEFINITION(SegmentStartVerifyCompute)
   ,FBL_MEM_STATUS_DEFINITION(SegmentStartSegmentCount)

   ,FBL_MEM_STATUS_DEFINITION(SegmentEndSequence)
   ,FBL_MEM_STATUS_DEFINITION(SegmentEndInsufficientData)
   ,FBL_MEM_STATUS_DEFINITION(SegmentEndPost)

   ,FBL_MEM_STATUS_DEFINITION(DataIndSequence)
   ,FBL_MEM_STATUS_DEFINITION(DataIndParam)
   ,FBL_MEM_STATUS_DEFINITION(DataIndOverflow)

   ,FBL_MEM_STATUS_DEFINITION(DataProc)
   ,FBL_MEM_STATUS_DEFINITION(DataProcConsume)
   ,FBL_MEM_STATUS_DEFINITION(DataProcDeinit)

   ,FBL_MEM_STATUS_DEFINITION(StreamOutput)
   ,FBL_MEM_STATUS_DEFINITION(StreamOutputConsume)
   ,FBL_MEM_STATUS_DEFINITION(StreamOutputOverflow)
   ,FBL_MEM_STATUS_DEFINITION(StreamOutputDeinit)

   ,FBL_MEM_STATUS_DEFINITION(DriverResumeWrite)
   ,FBL_MEM_STATUS_DEFINITION(DriverWrite)
   ,FBL_MEM_STATUS_DEFINITION(DriverErase)
   ,FBL_MEM_STATUS_DEFINITION(DriverRemainder)
   ,FBL_MEM_STATUS_DEFINITION(DriverSuspendWrite)

   ,FBL_MEM_STATUS_DEFINITION(ProgramOverflow)
   ,FBL_MEM_STATUS_DEFINITION(ProgramOutsideFbt)
   ,FBL_MEM_STATUS_DEFINITION(ProgramUnalignedAddress)
   ,FBL_MEM_STATUS_DEFINITION(ProgramDriverNotReady)
   ,FBL_MEM_STATUS_DEFINITION(ProgramPreWrite)
   ,FBL_MEM_STATUS_DEFINITION(ProgramPostWrite)

   ,FBL_MEM_STATUS_DEFINITION(EraseOutsideFbt)
   ,FBL_MEM_STATUS_DEFINITION(EraseDriverNotReady)
   ,FBL_MEM_STATUS_DEFINITION(ErasePreErase)
   ,FBL_MEM_STATUS_DEFINITION(ErasePostErase)

   ,FBL_MEM_STATUS_DEFINITION(VerifyCompute)
   ,FBL_MEM_STATUS_DEFINITION(VerifyFinalize)

   ,FBL_MEM_STATUS_DEFINITION(PassThroughLocal)
   ,FBL_MEM_STATUS_DEFINITION(PassThroughRemote)
#if defined( FBL_MEM_STATUS_ConditionCheck0 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck0)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck1 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck1)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck2 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck2)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck3 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck3)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck4 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck4)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck5 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck5)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck6 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck6)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck7 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck7)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck8 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck8)
#endif
#if defined( FBL_MEM_STATUS_ConditionCheck9 )
   ,FBL_MEM_STATUS_DEFINITION(ConditionCheck9)
#endif
}tFblMemStatus;

typedef enum{
   kFblMemType_RAM = 0u,
   kFblMemType_ROM
}tFblMemType;

typedef enum{
   kFblMemProgState_Idle = 0u,
   kFblMemProgState_Error,
   kFblMemProgState_Suspended,
   kFblMemProgState_SuspendPending,
   kFblMemProgState_Checkpoint,
   kFblMemProgState_Pending
}tFblMemProgState;

typedef V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *        tFblMemRamData;

typedef const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *  tFblMemConstRamData;

typedef vuint8 tFblMemDfi;

typedef struct{
   tFblMemVerifyFctInput      function;
   V_MEMRAM1 tFblMemVerifyParamInput   V_MEMRAM2 V_MEMRAM3 * param;
}tFblMemVerifyRoutineInput;

typedef struct{
   tFblMemVerifyFctOutput     function;
   V_MEMRAM1 tFblMemVerifyParamOutput  V_MEMRAM2 V_MEMRAM3 * param;
}tFblMemVerifyRoutineOutput;

typedef struct{
   tFblAddress                targetAddress;
   tFblLength                 targetLength;

   tFblAddress                logicalAddress;
   tFblLength                 logicalLength;
   tFblMemVerifyRoutineInput  verifyRoutineInput;
   tFblMemVerifyRoutineInput  verifyRoutineProcessed;
   tFblMemVerifyRoutineInput  verifyRoutinePipe;
   tFblMemVerifyRoutineOutput verifyRoutineOutput;
   tFblMemVerifyReadFct       readFct;
   V_MEMRAM1 tFblMemSegmentList V_MEMRAM2 V_MEMRAM3 * segmentList;
   vuint8                     maxSegments;
}tFblMemBlockInfo;

typedef struct{
   tFblMemRamData data;
   tFblLength     length;
}tFblMemVerifyData;

typedef struct{
   tFblMemVerifyData    verifyDataInput;
   tFblMemVerifyData    verifyDataProcessed;
   tFblMemVerifyData    verifyDataPipe;
   tFblMemVerifyData    verifyDataOutput;
}tFblMemBlockVerifyData;

typedef struct{
   tFblAddress    targetAddress;
   tFblLength     targetLength;

   tFblAddress    logicalAddress;
   tFblLength     logicalLength;

   tFblMemType    type;
   tFblMemDfi     dataFormat;
}tFblMemSegmentInfo;

#if defined( FBL_MEM_TRIGGER_STATUS_OVERWRITE )
typedef FBL_MEM_TRIGGER_STATUS_OVERWRITE  tFblMemTriggerStatus;
#else
typedef vuint8                            tFblMemTriggerStatus;
#endif

typedef vuintx tFblMemInputSource;

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

typedef enum{
   kFblMemProgressType_Erase,
   kFblMemProgressType_Program,
   kFblMemProgressType_GapFill,
   kFblMemProgressType_Verify,
   kFblMemProgressType_Undefined
}tFblMemProgressType;

typedef struct{
   tFblMemProgressType  type;
   tFblAddress          logicalAddress;
   vuint32              segmentCount;
   vuint8               totalProgress;
   vuint8               partialProgress;
}tFblMemProgressInfo;
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
typedef struct{
   tFblAddress                baseAddress;
   tFblLength                 baseLength;
   tFblAddress                address;
   tFblLength                 length;
   tFblMemConstRamData        inputData;
   tFblMemRamData             outputData;
   void (* watchdog)(void);
   tFblLength                 inputLength;
   tFblLength                 outputSize;
   tFblLength                 consumedLength;
   tFblLength                 producedLength;
   vuint8                     mode;
}tFblMemStreamProcessing;
#endif

#if defined( __cplusplus )
extern "C" {
#endif

tFblMemRamData FblMemInitPowerOn( void );
tFblMemRamData FblMemInitPowerOnExt( tFblLength preambleLen, tFblMemInputSource sourceHandle );
tFblMemRamData FblMemInit( void );
void FblMemDeinit( void );
tFblMemRamData FblMemGetActiveBuffer( void );
tFblMemStatus FblMemBlockEraseIndication( const V_MEMRAM1 tFblMemBlockInfo V_MEMRAM2 V_MEMRAM3 * block );
tFblMemStatus FblMemBlockStartIndication( V_MEMRAM1 tFblMemBlockInfo V_MEMRAM2 V_MEMRAM3 * block );
tFblMemStatus FblMemBlockEndIndication( void );
tFblMemStatus FblMemBlockVerify( const V_MEMRAM1 tFblMemBlockVerifyData V_MEMRAM2 V_MEMRAM3 * verifyData,
   V_MEMRAM1 tFblMemVerifyStatus V_MEMRAM2 V_MEMRAM3 * verifyResult );
tFblMemStatus FblMemSegmentStartIndication( const V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * segment );
tFblMemStatus FblMemSegmentEndIndication( V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * writeLength );
tFblMemStatus FblMemDataIndication( tFblMemConstRamData buffer, tFblLength offset, tFblLength length );
void FblMemTask( void );
void FblMemFlushInputData( void );

tFblMemStatus FblMemEraseRegion( tFblAddress eraseAddress, tFblLength eraseLength );
tFblMemStatus FblMemProgramBuffer( tFblAddress programAddress,V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength,
   tFblMemRamData programData );

void FblMemSetInteger( vuintx count, vuint32 input, tFblMemRamData buffer );
vuint32 FblMemGetInteger( vuintx count, tFblMemConstRamData buffer );

#if defined( FBL_MEM_ENABLE_MULTI_SOURCE )
void FblMemLockInputSource( tFblMemInputSource sourceHandle );
#endif

# define FBLLIB_MEM_RAMCODE_START_SEC_CODE_EXPORT
# include "MemMap.hpp"

void FblMemResumeIndication( void );

# define FBLLIB_MEM_RAMCODE_STOP_SEC_CODE_EXPORT
# include "MemMap.hpp"

#if defined( __cplusplus )
}
#endif

# define FBLLIB_MEM_START_SEC_VAR_EXPORT
# include "MemMap.hpp"

V_MEMRAM0 extern V_MEMRAM1 tFblMemProgState V_MEMRAM2 fblMemProgState;

# define FBLLIB_MEM_STOP_SEC_VAR_EXPORT
# include "MemMap.hpp"

#if defined( FBL_ENABLE_ADAPTIVE_DATA_TRANSFER_RCRRP )
# if defined( FBL_MEM_WRITE_SEGMENTATION )
# else
#  error Write segmentation not defined
# endif
# if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )
# else
#  if( (FBL_MEM_WRITE_SEGMENTATION & (FBL_MAX_SEGMENT_SIZE - 1u)) != 0u )
#   error Write segmentation has to be multiple of segment size
#  endif
# endif
#endif

#if defined( FBL_ENABLE_DATA_PROCESSING )
# if defined( FBL_MEM_PROC_BUFFER_SIZE )
# else
#  error Data processing buffer size not defined
# endif
# if( FBL_MEM_PROC_SEGMENTATION > 0xFFFFu )
#  error Data processing segmentation exceeds interface constraints
# endif
# if( FBL_MEM_PROC_SEGMENTATION > FBL_MEM_PROC_BUFFER_SIZE )
#  error Data processing segmentation exceeds buffer size
# endif
# if( FBL_MEM_PROC_SEGMENTATION == FBL_MEM_PROC_BUFFER_SIZE )
# else
# endif
#endif

#if defined( FBL_MEM_BUFFER_SIZE )
#else
# error Input buffer size not defined
#endif

#if defined( FBL_MEM_DEFAULT_PREAMBLE_LENGTH )
#else
# error Default preamble length not defined
#endif

#if defined( FBL_MEM_MAX_PREAMBLE_LENGTH )
#else
# error Maximum preamble length not defined
#endif

#if defined( FBL_MEM_WD_TRIGGER_DEFAULT )
#else
# error Default watchdog trigger return code not defined
#endif

#if defined( FBL_MEM_ENABLE_STATUS_OVERWRITE )
# if defined( FBL_MEM_STATUS_Ok ) && \
     defined( FBL_MEM_STATUS_Failed )
# else
#  error Status overwrite or remapping enabled, but actual values missing
# endif
#endif

#if defined( FBL_MEM_STATUS_Ok ) || \
    defined( FBL_MEM_STATUS_Failed )
# if defined( FBL_MEM_ENABLE_STATUS_OVERWRITE )
# else
#  error Status values defined, but neither status overwrite nor remapping enabled
# endif
#endif

#if defined( FBL_MEM_ENABLE_EXT_STATUS )
# if defined( FBL_MEM_EXT_STATUS_Ok ) && \
     defined( FBL_MEM_EXT_STATUS_Failed )
# else
#  error Extended status enabled, but actual macros missing
# endif
#endif

#if defined( FBL_MEM_EXT_STATUS_Ok ) || \
    defined( FBL_MEM_EXT_STATUS_Failed )
# if defined( FBL_MEM_ENABLE_EXT_STATUS )
# else
#  error Extended status macros defined, but feature not enabled
# endif
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
# if defined( __ApplFblMemIsStreamOutputRequired )
# else
#  error Stream output enabled, but data format check not specified
# endif
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )
# if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH)
#  error Combination of progress information with processed data length not supported
# endif
# if defined( __ApplFblMemReportProgress )
# else
#  error Progress information enabled, but report callout not specified
# endif
#endif

#endif

