#include "fbl_inc.hpp"
#include "fbl_mem.hpp"

#if( FBLLIB_MEM_VERSION != 0x0405u ) || \
    ( FBLLIB_MEM_RELEASE_VERSION != 0x02u )
# error "Error in fbl_mem.c: Source and Header file are inconsistent!"
#endif

#if( FBLLIB_MEM_VERSION != _FBLLIB_MEM_VERSION ) || \
    ( FBLLIB_MEM_RELEASE_VERSION != _FBLLIB_MEM_RELEASE_VERSION )
# error "Error in fbl_mem.c: Source and v_ver.h are inconsistent!"
#endif

#if defined( FBL_MEM_API_REFERENCE_VERSION_MAJOR ) && \
    defined( FBL_MEM_API_REFERENCE_VERSION_MINOR )
#else
#error "Error in fbl_mem.c: Interface version requirements not defined!"
#endif

#if( FBL_MEM_API_REFERENCE_VERSION_MAJOR != FBL_MEM_API_VERSION_MAJOR) || \
    ( FBL_MEM_API_REFERENCE_VERSION_MINOR > FBL_MEM_API_VERSION_MINOR)
# error "Error in fbl_mem.c: Interface version compatibility check failed!"
#endif

#define FBL_MEM_SEGMENT_SIZE              FBL_MAX_SEGMENT_SIZE

#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )

#define FBL_MEM_ENABLE_PREAMBLE_HANDLING
#endif

#if defined( FBL_ENABLE_DATA_PROCESSING ) || \
    defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )

#if( FBL_MEM_SEGMENT_SIZE > 1u )

#define FBL_MEM_ENABLE_REMAINDER_HANDLING
#endif
#endif

#if defined( FBL_ENABLE_ADAPTIVE_DATA_TRANSFER_RCRRP )

#define FBL_MEM_ENABLE_SEGMENTATION
#endif

#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )

#define FBL_MEM_ENABLE_INPUT_LENGTH
#endif

#if defined( FBL_MEM_WRITE_SEGMENTATION )
#else

#define FBL_MEM_WRITE_SEGMENTATION    (FBL_MEM_BUFFER_SIZE + FBL_MEM_SEGMENT_SIZE)
#endif

#if defined( FBL_ENABLE_DATA_PROCESSING )
#if defined( FBL_MEM_ENABLE_SEGMENTATION )
#define FBL_MEM_INTERNAL_PROC_SEGMENTATION       FBL_MEM_PROC_SEGMENTATION
#if( FBL_MEM_INTERNAL_PROC_SEGMENTATION == FBL_MEM_PROC_BUFFER_SIZE)

#else

#define FBL_MEM_ENABLE_PROC_SEGMENTATION
#endif
#else

#define FBL_MEM_INTERNAL_PROC_SEGMENTATION       FBL_MEM_PROC_BUFFER_SIZE
#endif
#endif

#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )  || \
    defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )

#define FBL_MEM_ENABLE_VERIFICATION
#endif

#if defined( FBL_MEM_VERIFY_SEGMENTATION )
#if defined( FBL_MEM_VERIFY_INPUT_SEGMENTATION )
#else

#define FBL_MEM_VERIFY_INPUT_SEGMENTATION        FBL_MEM_VERIFY_SEGMENTATION
#endif
#if defined( FBL_MEM_VERIFY_PIPELINED_SEGMENTATION )
#else

#define FBL_MEM_VERIFY_PIPELINED_SEGMENTATION    FBL_MEM_VERIFY_SEGMENTATION
#endif
#endif

#if defined( FBL_MEM_VERIFY_INPUT_SEGMENTATION )
#else

#define FBL_MEM_VERIFY_INPUT_SEGMENTATION         64u
#endif

#if defined( FBL_MEM_VERIFY_PIPELINED_SEGMENTATION )
#else

#define FBL_MEM_VERIFY_PIPELINED_SEGMENTATION     64u
#endif

#define FBL_MEM_ENABLE_RESPONSE_PENDING

#define FBL_MEM_ENABLE_INPUT_DATA_FLUSH

#if defined( FBL_MEM_ENABLE_GAP_FILL )
#if defined( FBL_MEM_GAP_FILL_SEGMENTATION )
#else

#if defined( FBL_MEM_WRITE_SEGMENTATION )
#if(FBL_MEM_SEGMENT_SIZE > FBL_MEM_WRITE_SEGMENTATION)
#define FBL_MEM_GAP_FILL_SEGMENTATION          FBL_MEM_SEGMENT_SIZE
#   else
#define FBL_MEM_GAP_FILL_SEGMENTATION          FBL_MEM_WRITE_SEGMENTATION
#endif
#else
#define FBL_MEM_GAP_FILL_SEGMENTATION           FBL_MEM_SEGMENT_SIZE
#endif
#endif
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )
#if defined( FBL_MEM_PROGRESS_ERASE )
#else

#define FBL_MEM_PROGRESS_ERASE                   10u
#endif
#if defined( FBL_MEM_PROGRESS_VERIFY )
#else

#define FBL_MEM_PROGRESS_VERIFY                  10u
#endif
#if defined( FBL_MEM_PROGRESS_INITIAL )
#else

#define FBL_MEM_PROGRESS_INITIAL                 0u
#endif
#if defined( FBL_MEM_PROGRESS_COMPLETE )
#else

#define FBL_MEM_PROGRESS_COMPLETE                100u
#endif
#if defined( FBL_MEM_PROGRESS_PROGRAM )
#else

#define FBL_MEM_PROGRESS_PROGRAM     (FBL_MEM_PROGRESS_COMPLETE - FBL_MEM_PROGRESS_ERASE - FBL_MEM_PROGRESS_VERIFY)
#endif
#if defined( FBL_MEM_PROGRESS_THRESHOLD_BYTES )
#else

#define FBL_MEM_PROGRESS_THRESHOLD_BYTES         1024u
#endif
#if defined( FBL_MEM_PROGRESS_THRESHOLD_PERCENTAGE )
#else

#define FBL_MEM_PROGRESS_THRESHOLD_PERCENTAGE    5u
#endif
#endif

#define FBL_MEM_QUEUE_ENTRIES_INPUT               1u

#define FBL_MEM_BUFFER_COUNT_INPUT                 ((FBL_MEM_QUEUE_ENTRIES_INPUT + FBL_MEM_SOURCE_COUNT) - 1u)

#define FBL_MEM_QUEUE_ENTRIES_VERIFY_INPUT        0u

#define FBL_MEM_QUEUE_ENTRIES_VERIFY_PROCESSED    0u

#define FBL_MEM_QUEUE_ENTRIES_VERIFY_PIPE         0u

#if defined( FBL_ENABLE_DATA_PROCESSING )

#define FBL_MEM_QUEUE_ENTRIES_DATA_PROC           2u
#else
#define FBL_MEM_QUEUE_ENTRIES_DATA_PROC           0u
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

#define FBL_MEM_QUEUE_ENTRIES_STREAM_OUTPUT       2u
#else
#define FBL_MEM_QUEUE_ENTRIES_STREAM_OUTPUT       0u
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

#define FBL_MEM_QUEUE_ENTRIES_REMAINDER           1u
#else
#define FBL_MEM_QUEUE_ENTRIES_REMAINDER           0u
#endif

#define FBL_MEM_QUEUE_ENTRIES_CHECKPOINT          0u

#if defined( FBL_MEM_ENABLE_GAP_FILL )

#define FBL_MEM_QUEUE_ENTRIES_GAP_FILL            1u
#else
#define FBL_MEM_QUEUE_ENTRIES_GAP_FILL            0u
#endif

#define FBL_MEM_QUEUE_ENTRIES_PROCESSING  \
   ( FBL_MEM_QUEUE_ENTRIES_VERIFY_INPUT + FBL_MEM_QUEUE_ENTRIES_VERIFY_PROCESSED + FBL_MEM_QUEUE_ENTRIES_DATA_PROC   \
     + FBL_MEM_QUEUE_ENTRIES_STREAM_OUTPUT + FBL_MEM_QUEUE_ENTRIES_INPUT + FBL_MEM_QUEUE_ENTRIES_VERIFY_PIPE         \
     + FBL_MEM_QUEUE_ENTRIES_CHECKPOINT + FBL_MEM_QUEUE_ENTRIES_GAP_FILL )

#if( FBL_MEM_QUEUE_ENTRIES_PROCESSING > 1u )

#define FBL_MEM_ENABLE_PROC_QUEUE

#define FBL_MEM_QUEUE_ENTRIES_TOTAL               (FBL_MEM_QUEUE_ENTRIES_PROCESSING + FBL_MEM_QUEUE_ENTRIES_REMAINDER)
#else

#define FBL_MEM_DISABLE_PROC_QUEUE
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
#if defined( FBL_MEM_ENABLE_PROC_QUEUE )
#else

#define FBL_MEM_ENABLE_REMAINDER_HANDLING_SINGLE_JOB
#endif
#endif

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

#define FBL_MEM_RESERVED_QUEUE_ENTRIES         2u

#define FBL_MEM_QUEUE_HANDLE_HEAD_USED         0u
#define FBL_MEM_QUEUE_HANDLE_HEAD_FREE         1u

#define FBL_MEM_QUEUE_HANDLE_ENTRY_OFFSET      2u

#define FBL_MEM_QUEUE_SIZE_PROCESSING          (FBL_MEM_RESERVED_QUEUE_ENTRIES + FBL_MEM_QUEUE_ENTRIES_TOTAL)

#define FblMemQueueIsEmpty(queue)              (FBL_MEM_QUEUE_HANDLE_HEAD_USED == (queue)[FBL_MEM_QUEUE_HANDLE_HEAD_USED].next)
#define FblMemQueueIsFull(queue)               (FBL_MEM_QUEUE_HANDLE_HEAD_FREE == (queue)[FBL_MEM_QUEUE_HANDLE_HEAD_FREE].next)

#define FblMemQueueGetFirstUsedHandle(queue)   ((queue)[FBL_MEM_QUEUE_HANDLE_HEAD_USED].next)
#define FblMemQueueGetLastUsedHandle(queue)    ((queue)[FBL_MEM_QUEUE_HANDLE_HEAD_USED].prev)
#define FblMemQueueGetFirstFreeHandle(queue)   ((queue)[FBL_MEM_QUEUE_HANDLE_HEAD_FREE].next)

#define FblMemQueueGetEntry(queue, handle)     ((queue)[handle])

#define FblMemQueueGetFirstUsedEntry(queue)    (FblMemQueueGetEntry((queue), FblMemQueueGetFirstUsedHandle(queue)))
#define FblMemQueueGetLastUsedEntry(queue)     (FblMemQueueGetEntry((queue), FblMemQueueGetLastUsedHandle(queue)))
#define FblMemQueueGetFirstFreeEntry(queue)    (FblMemQueueGetEntry((queue), FblMemQueueGetFirstFreeHandle(queue)))
#endif

#define FBL_MEM_QUEUE_PRIO_LOWEST              0x00u
#define FBL_MEM_QUEUE_PRIO_HIGHEST             0xFFu

#define FBL_MEM_QUEUE_NULL                     ((V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 *)V_NULL)

#define FBL_MEM_JOB_NULL                       ((V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 *)V_NULL)

#define FblMemGetPendingInputJob()             (&FBL_MEM_INPUT_JOB[0])

#define FBL_MEM_VERIFY_STATUS_NULL              ((V_MEMRAM1 tFblMemVerifyStatus V_MEMRAM2 V_MEMRAM3 *)V_NULL)
#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )

#define FBL_MEM_VERIFY_FCT_INPUT_NULL          ((tFblMemVerifyFctInput)0)
#endif
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )

#define FBL_MEM_VERIFY_FCT_OUTPUT_NULL         ((tFblMemVerifyFctOutput)0)
#endif

#define FblMemGetRemainder(address, length, segSize)  ((tFblLength)(((address) + (tFblAddress)(length)) & ((tFblAddress)(segSize) - 1u)))

#define FblMemGetGlobalRemainder(address, length)     FblMemGetRemainder((address), (length), FBL_MEM_SEGMENT_SIZE)

#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES ) && \
     defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
#define FblMemGetWriteRemainder(address, length)    FblMemGetSpecificRemainder((address), (length))
#else

#define FblMemGetWriteRemainder(address, length)    FblMemGetGlobalRemainder((address), (length))
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

#define FBL_MEM_REMAINDER_PADDING        (FBL_MEM_SEGMENT_SIZE - 1u)

#define FBL_MEM_WRITE_PADDING            (FBL_MEM_SEGMENT_SIZE - 1u)
#else
#define FBL_MEM_REMAINDER_PADDING        0u
#define FBL_MEM_WRITE_PADDING            0u
#endif

#define FBL_MEM_TOTAL_PADDING             (FBL_MEM_REMAINDER_PADDING + FBL_MEM_WRITE_PADDING)

#if defined( FBL_ENABLE_SYSTEM_CHECK )

#define FBL_MEM_CANARY_VALUE       0x42697264ul
#endif

#if defined( C_CPUTYPE_32BIT ) || \
    defined( C_CPUTYPE_16BIT )
#define FBL_MEM_PLATFORM_ALIGN        4u
#define FBL_MEM_PLATFORM_ALIGN_MASK   0x03u
#else
#define FBL_MEM_PLATFORM_ALIGN        1u
#define FBL_MEM_PLATFORM_ALIGN_MASK   0x00u
#endif

#if defined( FBL_ENABLE_SYSTEM_CHECK )

#define FBL_MEM_ALIGNED_BUFFER_TYPE(size)                                 \
   struct                                                                  \
   {                                                                       \
        \
      vuint32  canaryFront;                                                \
          \
      vuint8   data[size];                                                 \
        \
      vuint32  canaryBack;                                                 \
   }
#else

#if defined( C_CPUTYPE_32BIT ) || \
     defined( C_CPUTYPE_16BIT )

#define FBL_MEM_ALIGNED_BUFFER_TYPE(size)                                \
   struct                                                                  \
   {                                                                       \
      vuint32  alignDummy;                                                 \
          \
      vuint8   data[size];                                                 \
   }
#else

#define FBL_MEM_ALIGNED_BUFFER_TYPE(size)                                \
   struct                                                                  \
   {                                                                       \
          \
      vuint8   data[size];                                                 \
   }
#endif
#endif

#define FBL_MEM_LENGTH_ALIGN(length, align)  (((((length) - 1u) / (align)) + 1u) * (align))

#define FBL_MEM_PREAMBLE_ALIGN(length)       FBL_MEM_LENGTH_ALIGN((length), FBL_MEM_PLATFORM_ALIGN)

#define FBL_MEM_PREAMBLE_OFFSET(length)      (FBL_MEM_PREAMBLE_ALIGN(length) - (length))

#define FBL_MEM_PADDED_BUFFER_SIZE           (FBL_MEM_BUFFER_SIZE + (FBL_MEM_PLATFORM_ALIGN - 1u) + FBL_MEM_TOTAL_PADDING)
#if defined( FBL_ENABLE_DATA_PROCESSING )

#define FBL_MEM_PADDED_PROC_BUFFER_SIZE     (FBL_MEM_PROC_BUFFER_SIZE + FBL_MEM_TOTAL_PADDING)
#endif

#if defined( FBL_MEM_ENABLE_MULTI_SOURCE )

#define FBL_MEM_ACTIVE_SOURCE               gActiveSource
#else

#define FBL_MEM_ACTIVE_SOURCE               0u
#if defined( FBL_MEM_SOURCE_COUNT )
#else

#define FBL_MEM_SOURCE_COUNT               1u
#endif
#endif

#if defined( FBL_MEM_ENABLE_DYNAMIC_PREAMBLE_LENGTH )

#define FBL_MEM_PREAMBLE_LENGTH             gPreambleLength[FBL_MEM_ACTIVE_SOURCE]
#else

#define FBL_MEM_PREAMBLE_LENGTH             FBL_MEM_DEFAULT_PREAMBLE_LENGTH
#endif

#define FBL_MEM_INPUT_JOB                    gInputJobs[FBL_MEM_ACTIVE_SOURCE]

#define FBL_MEM_ARRAY_SIZE(arr)              (sizeof(arr) / sizeof((arr)[0]))

#if defined( FBL_MEM_ENABLE_SEGMENTATION )
#if defined( FBL_ENABLE_ADAPTIVE_DATA_TRANSFER_RCRRP )

#define FBL_MEM_FINALIZE_UNLIMITED_MODE    kFblMemOperationMode_Unconditional
#else

#define FBL_MEM_FINALIZE_UNLIMITED_MODE    kFblMemOperationMode_Finalize
#endif
#else

#define FblMemLimitLength(inputLen, type, finalize)     (inputLen)
#endif

#if defined( __ApplFblMemCopyBuffer )
#else

#define __ApplFblMemCopyBuffer(address, data, length)   (void)MEMCPY((address), (data), (length))
#endif

#define FBL_MEM_BUFFER_NULL                 ((tFblMemRamData)V_NULL)

#define FBL_MEM_ALLOWED_NONE           0x00u
#define FBL_MEM_ALLOWED_BLOCK_START    0x01u
#define FBL_MEM_ALLOWED_SEGMENT_START  0x02u
#define FBL_MEM_ALLOWED_DATA_IND       0x04u
#define FBL_MEM_ALLOWED_SEGMENT_END    0x08u
#define FBL_MEM_ALLOWED_BLOCK_END      0x10u
#define FBL_MEM_ALLOWED_BLOCK_VERIFY   0x20u
#define FBL_MEM_ALLOWED_BLOCK_ERASE    0x40u

#define FblMemResetAllowed()           (FblMemSetAllowed(FBL_MEM_ALLOWED_NONE))

#define FblMemSetAllowed(mask)        (gAllowedInd = (tFblMemAllowedInd)(mask))

#define FblMemAddAllowed(mask)        (gAllowedInd |= (tFblMemAllowedInd)(mask))

#define FblMemClrAllowed(mask)         (gAllowedInd &= FblInvertBits(mask, tFblMemAllowedInd))

#define FblMemIsAllowed(mask)          ((gAllowedInd & (tFblMemAllowedInd)(mask)) == (tFblMemAllowedInd)(mask))

#define FblMemIsAnyAllowed(mask)       ((gAllowedInd & (tFblMemAllowedInd)(mask)) != (tFblMemAllowedInd)(FBL_MEM_ALLOWED_NONE))

#define FBL_MEM_EXT_STATUS_NONE        0x00u

#define FBL_MEM_SET_STATUS(status, var)            FBL_MEM_SET_EXT_STATUS(status, FBL_MEM_EXT_STATUS_NONE, var)

#if defined( FBL_MEM_ENABLE_EXT_STATUS )

#define FBL_MEM_SET_EXT_STATUS(status, ext, var)  {                                      \
                                                      FBL_MEM_EXT_STATUS_## status(ext); \
                                                      (var) = kFblMemStatus_## status;   \
                                                   }

#define FBL_MEM_SET_EXT_INFO(type, info)          FBL_MEM_EXT_STATUS_## type(info)
#else

#define FBL_MEM_SET_EXT_STATUS(status, ext, var)  (var) = kFblMemStatus_## status
#define FBL_MEM_SET_EXT_INFO(type, info)
#endif

#define kFblMemAssertParameterOutOfRange     0x01u
#define kFblMemAssertUserResultOutOfRange    0x02u

#if defined( __ApplFblMemEnterCriticalSection )
#else

#define __ApplFblMemEnterCriticalSection()
#endif

#if defined( __ApplFblMemLeaveCriticalSection )
#else

#define __ApplFblMemLeaveCriticalSection()
#endif

typedef vuintx tFblMemAllowedInd;

typedef enum{
   kFblMemJobType_InputWrite = 0u
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   , kFblMemJobType_WriteFinalize
#endif
#if defined( FBL_ENABLE_DATA_PROCESSING )
   , kFblMemJobType_ProcInput
   , kFblMemJobType_ProcWrite
   , kFblMemJobType_ProcFinalize
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   , kFblMemJobType_StreamInput
   , kFblMemJobType_StreamProc
   , kFblMemJobType_StreamFinalize
#endif
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   , kFblMemJobType_GapFill
#endif
   , kFblMemJobType_Max
}tFblMemJobType;

typedef enum{
   kFblMemOperationMode_Normal = 0u
   ,  kFblMemOperationMode_Finalize
   ,  kFblMemOperationMode_Unconditional
}tFblMemOperationMode;

typedef FBL_MEM_ALIGNED_BUFFER_TYPE(FBL_MEM_PADDED_BUFFER_SIZE)      tFblMemInputBuffer;
#if defined( FBL_ENABLE_DATA_PROCESSING )

typedef FBL_MEM_ALIGNED_BUFFER_TYPE(FBL_MEM_PADDED_PROC_BUFFER_SIZE) tFblMemProcBuffer;
#endif
#if defined( FBL_MEM_ENABLE_GAP_FILL )

typedef FBL_MEM_ALIGNED_BUFFER_TYPE(FBL_MEM_GAP_FILL_SEGMENTATION)   tFblMemGapFillBuffer;
#endif
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

typedef FBL_MEM_ALIGNED_BUFFER_TYPE(FBL_MEM_SEGMENT_SIZE)            tFblMemRemainderBuffer;
#endif

typedef struct{
   tFblMemRamData       buffer;
   tFblLength           totalSize;
   tFblLength           netSize;
   tFblLength           offset;
   tFblLength           position;
   tFblLength           used;
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   tFblAddress          baseAddress;
#endif
   tFblMemJobType       type;
   tFblMemOperationMode completion;
   vuintx               segmentIndex;
}tFblMemJob;

typedef struct{
   tFblMemSegmentInfo   input;

   tFblAddress          writeAddress;
   tFblLength           writeRemainder;
   tFblLength           writeLength;
#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )
   tFblLength           writtenLength;
#endif
#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )
   tFblLength           inputAddress;
#endif
#if defined( FBL_MEM_ENABLE_INPUT_LENGTH )
   tFblLength           inputLength;
#endif
#if defined( FBL_ENABLE_DATA_PROCESSING ) || \
    defined( FBL_MEM_ENABLE_STREAM_OUTPUT ) || \
    defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   tFblMemJobType       jobType;
#endif
   vuintx               ownIndex;
   vuintx               nextIndex;
}tFblMemSegmentInternal;

typedef vuint8 tFblMemQueuePrio;

typedef enum{
   kFblMemJobPrio_Lowest               = FBL_MEM_QUEUE_PRIO_LOWEST
   ,  kFblMemJobPrio_Write,
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   kFblMemJobPrio_GapFill,
#endif
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   kFblMemJobPrio_WriteFinalize,
#endif
#if defined( FBL_ENABLE_DATA_PROCESSING )
   kFblMemJobPrio_ProcFinalize,
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   kFblMemJobPrio_StreamFinalize,
#endif
   kFblMemJobPrio_Input
   ,  kFblMemJobPrio_InputWrite           = kFblMemJobPrio_Input,
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   kFblMemJobPrio_StreamInput          = kFblMemJobPrio_Input
   ,  kFblMemJobPrio_StreamProcLow        = kFblMemJobPrio_Input,
#endif
#if defined( FBL_ENABLE_DATA_PROCESSING )
   kFblMemJobPrio_ProcInput            = kFblMemJobPrio_Input
   ,  kFblMemJobPrio_ProcWriteLow         = kFblMemJobPrio_Input
   ,  kFblMemJobPrio_ProcWriteHigh,
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   kFblMemJobPrio_StreamProcHigh,
#endif
   kFblMemJobPrio_Highest              = FBL_MEM_QUEUE_PRIO_HIGHEST
}tFblMemJobPrio;

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

typedef vuintx tFblMemQueueHandle;

typedef struct{
   V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 *   job;
   tFblMemQueuePrio                             prio;
   tFblMemQueueHandle                           prev;
   tFblMemQueueHandle                           next;
}tFblMemQueueEntry;
#endif

#if defined( FBL_MEM_ENABLE_SEGMENTATION )

typedef struct{
   tFblLength           limit;
   tFblMemOperationMode unlimitedMode;
}tFblMemLengthLimit;
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

typedef enum{
   kFblMemProgressState_Disabled
   ,  kFblMemProgressState_Enabled
}tFblMemProgressState;

typedef struct{
   vuint32 target;
   vuint8  totalOffset;
   vuint8  totalPercentage;
}tFblMemProgressInfoInternal;
#endif

#define FBLLIB_MEM_START_SEC_VAR
#include "MemMap.hpp"

V_MEMRAM0        V_MEMRAM1 tFblMemProgState        V_MEMRAM2 fblMemProgState;

V_MEMRAM0 static V_MEMRAM1 tFblMemAllowedInd       V_MEMRAM2 gAllowedInd;

V_MEMRAM0 static V_MEMRAM1 tFblMemStatus           V_MEMRAM2 gErrorStatus;

#if defined( FBL_MEM_ENABLE_GLOBAL_BLOCK_INFO )

V_MEMRAM0 static V_MEMRAM1 tFblMemBlockInfo        V_MEMRAM2 gBlockInfo;
#endif

V_MEMRAM0 static V_MEMRAM1 tFblMemSegmentInternal  V_MEMRAM2 gSegInfo;

#if defined( FBL_MEM_ENABLE_MULTI_SOURCE )

V_MEMRAM0 static V_MEMRAM1 tFblMemInputSource      V_MEMRAM2 gActiveSource;
#endif

#if defined( FBL_MEM_ENABLE_DYNAMIC_PREAMBLE_LENGTH )

V_MEMRAM0 static V_MEMRAM1 tFblLength              V_MEMRAM2 gPreambleLength[FBL_MEM_SOURCE_COUNT];
#endif

#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

V_MEMRAM0 static V_MEMRAM1 vuint8                  V_MEMRAM2 gPreambleBuffer[FBL_MEM_MAX_PREAMBLE_LENGTH];
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

V_MEMRAM0 static V_MEMRAM1 tFblMemRemainderBuffer  V_MEMRAM2 gRemainderBuffer;
#endif
#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )

V_MEMRAM0 static V_MEMRAM1 vuint8                  V_MEMRAM2 gPaddingBuffer[FBL_MEM_SEGMENT_SIZE];
#endif

V_MEMRAM0 static V_MEMRAM1 tFblMemInputBuffer      V_MEMRAM2 gBasicInputBuffer[FBL_MEM_BUFFER_COUNT_INPUT];

V_MEMRAM0 static V_MEMRAM1 tFblMemJob              V_MEMRAM2 gInputJobs[FBL_MEM_SOURCE_COUNT][FBL_MEM_QUEUE_ENTRIES_INPUT];

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

V_MEMRAM0 static V_MEMRAM1 tFblMemJob              V_MEMRAM2 gWriteFinalizeJob;
#endif

#if defined( FBL_ENABLE_DATA_PROCESSING )

V_MEMRAM0 static V_MEMRAM1 tProcParam              V_MEMRAM2 gProcParam;

V_MEMRAM0 static V_MEMRAM1 tFblMemJob              V_MEMRAM2 gProcWriteJob;
V_MEMRAM0 static V_MEMRAM1 tFblMemJob              V_MEMRAM2 gProcFinalizeJob;

V_MEMRAM0 static V_MEMRAM1 tFblMemProcBuffer       V_MEMRAM2 gProcBuffer;

#if defined( FBL_MEM_ENABLE_PROC_SEGMENTATION )

V_MEMRAM0 static V_MEMRAM1 tFblMemQueueHandle      V_MEMRAM2 gProcHandle;
#endif
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

V_MEMRAM0 static V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 gStreamParam;

#if defined( FBL_ENABLE_DATA_PROCESSING )
V_MEMRAM0 static V_MEMRAM1 tFblMemJob              V_MEMRAM2 gStreamProcJob;
#endif
V_MEMRAM0 static V_MEMRAM1 tFblMemJob              V_MEMRAM2 gStreamFinalizeJob;
#endif

#if defined( FBL_MEM_ENABLE_GAP_FILL )
V_MEMRAM0 static V_MEMRAM1 tFblMemJob              V_MEMRAM2 gGapFillJob;
V_MEMRAM0 static V_MEMRAM1 tFblMemGapFillBuffer    V_MEMRAM2 gGapFillBuffer;
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

V_MEMRAM0 static V_MEMRAM1 tFblMemProgressInfo           V_MEMRAM2 gProgressInfo;

V_MEMRAM0 static V_MEMRAM1 tFblMemProgressInfo           V_MEMRAM2 gPrevProgressInfo;

V_MEMRAM0 static V_MEMRAM1 tFblMemProgressState          V_MEMRAM2 gProgressState;

V_MEMRAM0 static V_MEMRAM1 tFblMemProgressInfoInternal   V_MEMRAM2 gProgressInfoInternal;

V_MEMRAM0 static V_MEMRAM1 vuint32                       V_MEMRAM2 gProgressPrevRemainder;
#endif

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

V_MEMRAM0 static V_MEMRAM1 tFblMemQueueEntry       V_MEMRAM2 gProcessingQueue[FBL_MEM_QUEUE_SIZE_PROCESSING];
#endif

#define FBLLIB_MEM_STOP_SEC_VAR
#include "MemMap.hpp"

#define FBLLIB_MEM_START_SEC_CONST
#include "MemMap.hpp"

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

V_MEMROM0 static V_MEMROM1 tFblMemQueuePrio V_MEMROM2 gJobPrio[] =
{
   kFblMemJobPrio_InputWrite
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   , kFblMemJobPrio_WriteFinalize
#endif
#if defined( FBL_ENABLE_DATA_PROCESSING )
   , kFblMemJobPrio_ProcInput
#if defined( FBL_MEM_ENABLE_PROC_SEGMENTATION )
   , kFblMemJobPrio_ProcWriteLow

#else
   , kFblMemJobPrio_ProcWriteHigh

#endif
   , kFblMemJobPrio_ProcFinalize
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   , kFblMemJobPrio_StreamInput
#if defined( FBL_MEM_ENABLE_PROC_SEGMENTATION )
   , kFblMemJobPrio_StreamProcLow

#else
   , kFblMemJobPrio_StreamProcHigh

#endif
   , kFblMemJobPrio_StreamFinalize
#endif
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   ,kFblMemJobPrio_GapFill
#endif
   , kFblMemJobPrio_Lowest
};
#endif

#if defined( FBL_MEM_ENABLE_SEGMENTATION )

V_MEMROM0 static V_MEMROM1 tFblMemLengthLimit V_MEMROM2 gLengthLimits[] =
{
   { FBL_MEM_WRITE_SEGMENTATION, FBL_MEM_FINALIZE_UNLIMITED_MODE }
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   , { 0u, kFblMemOperationMode_Normal }
#endif
#if defined( FBL_ENABLE_DATA_PROCESSING )
   , { 0xFFFFu, kFblMemOperationMode_Unconditional }
   , { FBL_MEM_WRITE_SEGMENTATION, FBL_MEM_FINALIZE_UNLIMITED_MODE }
   , { 0u, kFblMemOperationMode_Normal }
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   , { FBL_MEM_WRITE_SEGMENTATION, FBL_MEM_FINALIZE_UNLIMITED_MODE }
   , { FBL_MEM_WRITE_SEGMENTATION, FBL_MEM_FINALIZE_UNLIMITED_MODE }
   , { 0u, kFblMemOperationMode_Normal }
#endif
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   , { 0u, kFblMemOperationMode_Normal }
#endif
   , { 0u, kFblMemOperationMode_Normal }
};
#endif

#define FBLLIB_MEM_STOP_SEC_CONST
#include "MemMap.hpp"

static tFblMemTriggerStatus FblMemTriggerWatchdogExt(void);
static void FblMemTriggerWatchdog(void);
#if defined( FBL_MEM_ENABLE_RESPONSE_PENDING )
static void FblMemResponsePending(void);
#endif

static void FblMemInitInputQueue(void);
static void FblMemInitStates(void);
static tFblMemRamData FblMemInitInternal(void);
static tFblMemStatus FblMemQueueBuffer( tFblMemConstRamData buffer, tFblLength offset, tFblLength length );
static void FblMemProcessQueue( tFblMemOperationMode mode );
static void FblMemFlushQueueByPrio( tFblMemQueuePrio prio );
#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )
static tFblMemStatus FblMemVerifyInput( V_MEMRAM1 tFblMemVerifyRoutineInput V_MEMRAM2 V_MEMRAM3 * routine
   ,  const V_MEMRAM1 tFblMemVerifyData V_MEMRAM2 V_MEMRAM3 * data, vuint8 state
   ,  V_MEMRAM1 tFblMemVerifyStatus V_MEMRAM2 V_MEMRAM3 * result );
static tFblMemStatus FblMemInitVerifyInput(void);
#endif
static tFblMemStatus FblMemProcessJob( V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob, tFblMemOperationMode mode );
static tFblMemStatus FblMemProgramStream( const V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * programJob
   ,  V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength, tFblMemOperationMode mode );
static tFblLength FblMemPadLength( tFblAddress address, tFblLength length );
static tFblLength FblMemPadBuffer( tFblAddress address, tFblLength length, tFblMemRamData data );
#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )
static void FblMemUnpadBuffer( tFblMemRamData data, tFblLength padLen );
#endif
static tFblMemStatus FblMemCopyBuffer( tFblAddress programAddress
   ,  const V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength, tFblMemConstRamData programData );
static tFblMemStatus FblMemEraseRegionInternal( tFblAddress eraseAddress, tFblLength eraseLength );
static tFblMemStatus FblMemProgramBufferInternal( tFblAddress programAddress
   ,  V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength, tFblMemRamData programData
   ,  tFblMemProgState checkPointState );
#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES ) && \
     defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
static tFblLength FblMemGetSpecificRemainder( tFblAddress address, tFblLength length );
#endif

#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )
static tFblMemStatus FblMemRelocateBufferOffset( V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob
   ,  tFblMemConstRamData buffer, tFblLength offset, tFblLength length );
#endif

#if defined( FBL_MEM_ENABLE_SEGMENTATION )
static tFblLength FblMemLimitLength( tFblLength inputLen, tFblMemJobType type, tFblMemOperationMode mode );
#endif

#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )
static void FblMemStorePreamble(void);
static void FblMemRestorePreamble(void);
#endif

static tFblResult FblMemCheckAllowed( tFblMemAllowedInd check, tFblMemAllowedInd clear );
static tFblMemRamData FblMemGetBuffer( const V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job );
#if defined( FBL_ENABLE_SYSTEM_CHECK )
static void FblMemInitBufferIntegrity(void);
static tFblMemStatus FblMemVerifyBufferIntegrity(void);
#endif

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )
static void FblMemQueueInit( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue, tFblMemQueueHandle length );

static tFblMemQueueHandle FblMemQueueMove( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueueHandle handle, tFblMemQueueHandle prevNew );

static tFblMemQueueHandle FblMemQueueRemove( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueueHandle handle );
static tFblMemQueueHandle FblMemQueuePrioUpdate( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueueHandle handle, tFblMemQueuePrio prio );
static tFblMemQueueHandle FblMemQueuePrioInsert( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueuePrio prio, V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job );
static tFblMemQueueHandle FblMemQueueDefaultPrioInsert( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job, vuintx segmentIndex );
#endif

static void FblMemInitJob( V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job, tFblMemRamData buffer
   ,  tFblLength size, tFblMemJobType type );

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )
static vuint8 FblMemCalculateProgress( vuint32 current, vuint32 total, vuint8 percentage );
static void FblMemInitProgress(void);
static void FblMemReportProgress(void);
static void FblMemSetupProgress( tFblMemProgressType type, tFblAddress logicalAddress, vuint32 segmentCount
   ,  vuint8 totalOffset, vuint8 totalPercentage, vuint32 target );
static void FblMemOffsetProgress( vuint32 totalDone, vuint32 totalTarget );
static void FblMemUpdateProgress( vuint32 remainder );
static void FblMemConcludeProgress(void);
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
#if defined( FBL_MEM_ENABLE_SWITCH_READMEMORY_PARAM )

static tFblMemVerifySize FblMemProgressRead( tFblMemVerifyAddr address, tFblMemVerifySize length, tFblMemVerifyDataPtr buffer );
#else

static tFblMemVerifySize FblMemProgressRead( tFblMemVerifyAddr address, tFblMemVerifyDataPtr buffer, tFblMemVerifySize length );
#endif
#endif
#endif

static tFblMemTriggerStatus FblMemTriggerWatchdogExt(void){
   tFblMemTriggerStatus result;

   {
#if defined( __ApplFblMemAdaptiveRcrRp )

      result = __ApplFblMemAdaptiveRcrRp();
#else

      result = FBL_MEM_WD_TRIGGER_DEFAULT;
#endif
   }

   return result;
}

static void FblMemTriggerWatchdog(void){
   (void)FblMemTriggerWatchdogExt();
}

#if defined( FBL_MEM_ENABLE_RESPONSE_PENDING )

static void FblMemResponsePending(void){
#if defined( __ApplFblMemForcedRcrRp )
   {
#if defined( __ApplFblMemIsRcrRpActive )

      if(kFblOk != __ApplFblMemIsRcrRpActive())
#endif
      {
         __ApplFblMemForcedRcrRp();
      }
   }
#endif
}
#endif

static tFblMemRamData FblMemGetBuffer( const V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job ){
   tFblMemRamData jobBuffer;

   jobBuffer = job->buffer;

   if(FBL_MEM_BUFFER_NULL != jobBuffer){
      assertFblInternal((job->offset <= (job->totalSize - job->netSize)), kFblMemAssertParameterOutOfRange);
      assertFblInternal((job->used <= (job->totalSize - job->offset)), kFblMemAssertParameterOutOfRange);

      jobBuffer = &jobBuffer[job->position];
   }

   return jobBuffer;
}

#if defined( FBL_ENABLE_SYSTEM_CHECK )

static void FblMemInitBufferIntegrity(void){
   vuintx idx;

   for(idx = 0u; idx < FBL_MEM_BUFFER_COUNT_INPUT; idx++){
      gBasicInputBuffer[idx].canaryFront = FBL_MEM_CANARY_VALUE;
      gBasicInputBuffer[idx].canaryBack  = FBL_MEM_CANARY_VALUE;
   }

#if defined( FBL_ENABLE_DATA_PROCESSING )

   gProcBuffer.canaryFront = FBL_MEM_CANARY_VALUE;
   gProcBuffer.canaryBack  = FBL_MEM_CANARY_VALUE;
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

   gRemainderBuffer.canaryFront = FBL_MEM_CANARY_VALUE;
   gRemainderBuffer.canaryBack  = FBL_MEM_CANARY_VALUE;
#endif

#if defined( FBL_MEM_ENABLE_GAP_FILL )

   gGapFillBuffer.canaryFront = FBL_MEM_CANARY_VALUE;
   gGapFillBuffer.canaryBack  = FBL_MEM_CANARY_VALUE;
#endif
}

static tFblMemStatus FblMemVerifyBufferIntegrity(void){
   tFblMemStatus  retVal;
   vuint32        aggregated;
   vuintx         idx;

   retVal      = kFblMemStatus_Ok;
   aggregated  = 0x00ul;

   for(idx = 0u; idx < FBL_MEM_BUFFER_COUNT_INPUT; idx++){
      aggregated |= (FBL_MEM_CANARY_VALUE ^ gBasicInputBuffer[idx].canaryFront);
      aggregated |= (FBL_MEM_CANARY_VALUE ^ gBasicInputBuffer[idx].canaryBack);
   }

#if defined( FBL_ENABLE_DATA_PROCESSING )

   aggregated |= (FBL_MEM_CANARY_VALUE ^ gProcBuffer.canaryFront);
   aggregated |= (FBL_MEM_CANARY_VALUE ^ gProcBuffer.canaryBack);
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

   aggregated |= (FBL_MEM_CANARY_VALUE ^ gRemainderBuffer.canaryFront);
   aggregated |= (FBL_MEM_CANARY_VALUE ^ gRemainderBuffer.canaryBack);
#endif

#if defined( FBL_MEM_ENABLE_GAP_FILL )

   aggregated |= (FBL_MEM_CANARY_VALUE ^ gGapFillBuffer.canaryFront);
   aggregated |= (FBL_MEM_CANARY_VALUE ^ gGapFillBuffer.canaryBack);
#endif

   if(0x00ul != aggregated){
      retVal = kFblMemStatus_Failed;
   }

   return retVal;
}
#endif

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

static void FblMemQueueInit( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue, tFblMemQueueHandle length ){
   tFblMemQueueHandle handle;
   tFblMemQueueHandle prevHandle;
   tFblMemQueueHandle nextHandle;

   queue[FBL_MEM_QUEUE_HANDLE_HEAD_USED].next   = FBL_MEM_QUEUE_HANDLE_HEAD_USED;
   queue[FBL_MEM_QUEUE_HANDLE_HEAD_USED].prev   = FBL_MEM_QUEUE_HANDLE_HEAD_USED;

   queue[FBL_MEM_QUEUE_HANDLE_HEAD_USED].job    = FBL_MEM_JOB_NULL;
   queue[FBL_MEM_QUEUE_HANDLE_HEAD_USED].prio   = FBL_MEM_QUEUE_PRIO_HIGHEST;

   prevHandle = length - 1u;
   nextHandle = FBL_MEM_QUEUE_HANDLE_HEAD_FREE;

   for(handle = FBL_MEM_QUEUE_HANDLE_HEAD_FREE; handle < length; handle++){
      nextHandle++;

      queue[handle].prev   = prevHandle;
      queue[handle].next   = nextHandle;

      queue[handle].job    = FBL_MEM_JOB_NULL;
      queue[handle].prio   = FBL_MEM_QUEUE_PRIO_LOWEST;

      prevHandle = handle;
   }

   queue[length - 1u].next = FBL_MEM_QUEUE_HANDLE_HEAD_FREE;
}

static tFblMemQueueHandle FblMemQueueMove( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueueHandle handle, tFblMemQueueHandle prevNew ){
   tFblMemQueueHandle prevOld;
   tFblMemQueueHandle nextOld;
   tFblMemQueueHandle nextNew;

   if(handle == prevNew){
   }
   else{
      prevOld              = queue[handle].prev;
      nextOld              = queue[handle].next;

      assertFblInternal((queue[prevOld].next != prevOld), kFblMemAssertParameterOutOfRange);

      queue[prevOld].next  = nextOld;
      queue[nextOld].prev  = prevOld;

      nextNew              = queue[prevNew].next;

      queue[handle].prev   = prevNew;
      queue[prevNew].next  = handle;
      queue[handle].next   = nextNew;
      queue[nextNew].prev  = handle;
   }

   return handle;
}

static tFblMemQueueHandle FblMemQueueRemove( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueueHandle handle ){
   return FblMemQueueMove(queue, handle, queue[FBL_MEM_QUEUE_HANDLE_HEAD_FREE].prev);
}

static tFblMemQueueHandle FblMemQueuePrioUpdate( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueueHandle handle, tFblMemQueuePrio prio ){
   tFblMemQueueHandle prevHandle;

   prevHandle = queue[FBL_MEM_QUEUE_HANDLE_HEAD_USED].prev;

   while(queue[prevHandle].prio < prio){
      prevHandle = queue[prevHandle].prev;
   }

   (void)FblMemQueueMove(queue, handle, prevHandle);

   queue[handle].prio = prio;

   return handle;
}

static tFblMemQueueHandle FblMemQueuePrioInsert( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  tFblMemQueuePrio prio, V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job ){
   tFblMemQueueHandle handle;

   assertFblInternal((!FblMemQueueIsFull(queue)), kFblMemAssertParameterOutOfRange);

   handle = FblMemQueuePrioUpdate(queue, queue[FBL_MEM_QUEUE_HANDLE_HEAD_FREE].next, prio);

   queue[handle].job = job;

   return handle;
}

static tFblMemQueueHandle FblMemQueueDefaultPrioInsert( V_MEMRAM1 tFblMemQueueEntry V_MEMRAM2 V_MEMRAM3 * queue
   ,  V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job, vuintx segmentIndex ){
   assertFblInternal((job->type < kFblMemJobType_Max), kFblMemAssertParameterOutOfRange);

   job->segmentIndex = segmentIndex;

   return FblMemQueuePrioInsert(queue, gJobPrio[job->type], job);
}
#endif

static void FblMemInitJob( V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * job, tFblMemRamData buffer, tFblLength size
   ,  tFblMemJobType type ){
   job->buffer          = buffer;
   job->totalSize       = size;
   job->netSize         = size;

   job->offset          = 0u;
   job->position        = 0u;
   job->used            = 0u;

   job->type            = type;

   job->completion      = kFblMemOperationMode_Normal;
}

static void FblMemInitInputQueue(void){
   vuintx idx;
   vuintx actualBasicIdx;

   actualBasicIdx = FBL_MEM_ACTIVE_SOURCE;

   idx = 0u;

   {
      FblMemInitJob( &FBL_MEM_INPUT_JOB[idx], gBasicInputBuffer[actualBasicIdx].data
   ,                    FBL_MEM_ARRAY_SIZE(gBasicInputBuffer[actualBasicIdx].data), kFblMemJobType_InputWrite );

      FBL_MEM_INPUT_JOB[idx].netSize   = FBL_MEM_BUFFER_SIZE;

      FBL_MEM_INPUT_JOB[idx].offset    = FBL_MEM_PREAMBLE_OFFSET(FBL_MEM_PREAMBLE_LENGTH);

   }
}

static void FblMemInitStates(void){
   fblMemProgState   = kFblMemProgState_Idle;
   gErrorStatus      = kFblMemStatus_Ok;

   FblMemResetAllowed();
}

static tFblMemRamData FblMemInitInternal(void){
   FblMemInitStates();

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

   FblMemQueueInit(gProcessingQueue, FBL_MEM_ARRAY_SIZE(gProcessingQueue));
#endif
   FblMemInitInputQueue();

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   FblMemInitJob(&gWriteFinalizeJob, gRemainderBuffer.data, FBL_MEM_SEGMENT_SIZE, kFblMemJobType_WriteFinalize);
#endif

#if defined( FBL_ENABLE_DATA_PROCESSING )

   gProcWriteJob.used = 0u;
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT ) && \
    defined( FBL_ENABLE_DATA_PROCESSING )

   gStreamProcJob.used = 0u;
#endif

#if defined( FBL_ENABLE_SYSTEM_CHECK )
   FblMemInitBufferIntegrity();
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )
   FblMemInitProgress();
#endif

   FblMemSetAllowed(FBL_MEM_ALLOWED_BLOCK_START | FBL_MEM_ALLOWED_BLOCK_ERASE);

   return FblMemGetActiveBuffer();
}

#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

static void FblMemStorePreamble(void){
#if defined( FBL_MEM_ENABLE_DYNAMIC_PREAMBLE_LENGTH )

   assertFblGen(FBL_MEM_PREAMBLE_LENGTH <= FBL_MEM_MAX_PREAMBLE_LENGTH, kFblMemAssertParameterOutOfRange);
#endif

   (void)MEMCPY(gPreambleBuffer, FblMemGetActiveBuffer(), FBL_MEM_PREAMBLE_LENGTH);
}

static void FblMemRestorePreamble(void){
   (void)MEMCPY(FblMemGetActiveBuffer(), gPreambleBuffer, FBL_MEM_PREAMBLE_LENGTH);
}
#endif

#if defined( FBL_MEM_ENABLE_SEGMENTATION )

static tFblLength FblMemLimitLength( tFblLength inputLen, tFblMemJobType type, tFblMemOperationMode mode ){
   tFblLength lengthLimit;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if defined( FBL_MEM_ENABLE_SEGMENTATION )
#else
   (void)mode;
#endif
#endif

   assertFblInternal((type < kFblMemJobType_Max), kFblMemAssertParameterOutOfRange);

   lengthLimit = gLengthLimits[type].limit;

   if(lengthLimit > 0){
#if defined( FBL_MEM_ENABLE_SEGMENTATION )

      if((gLengthLimits[type].unlimitedMode != mode) && (inputLen > lengthLimit))
#else

      if((gLengthLimits[type].unlimitedMode == kFblMemOperationMode_Unconditional) && (inputLen > lengthLimit))
#endif
      {
         inputLen = lengthLimit;
      }
   }

   return inputLen;
}
#endif

static tFblLength FblMemPadLength( tFblAddress address, tFblLength length ){
   tFblLength  localAddress;
   tFblLength  localLength;
   tFblLength  padLen;
   tFblAddress alignMask;
   vsint16     oldSegment;

   localLength = length;

   if(length > 0u){
      localLength--;
   }

   localAddress  = address + localLength;

   padLen      = 0u;

   oldSegment  = memSegment;

   memSegment  = FblMemSegmentNrGet(localAddress);

   if(memSegment >= 0){
      alignMask = (tFblAddress)(MemDriver_SegmentSize - 1u);

      padLen = localAddress ^ alignMask;

      if(0u == length)
      {
         padLen++;
      }

      padLen &= alignMask;
   }

   memSegment = oldSegment;

   return padLen;
}

static tFblLength FblMemPadBuffer( tFblAddress address, tFblLength length, tFblMemRamData data ){
   tFblMemRamData padBuffer;
   tFblLength padLen;
   tFblLength idx;

   padLen = FblMemPadLength(address, length);

   if(padLen > 0u){
      padBuffer = &data[1];

      for(idx = 0u; idx < padLen; idx++)
      {
#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )

         gPaddingBuffer[idx] = padBuffer[idx];
#endif

         padBuffer[idx] = kFillChar;
      }
   }

   return padLen;
}

#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )

static void FblMemUnpadBuffer( tFblMemRamData data, tFblLength padLen ){
   if(padLen > 0u){
      (void)MEMCPY(&data[1], gPaddingBuffer, padLen);
   }
}
#endif

static tFblMemStatus FblMemCopyBuffer( tFblAddress programAddress
   ,  const V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength, tFblMemConstRamData programData ){
   __ApplFblMemCopyBuffer(programAddress, programData, *programLength);

   return kFblMemStatus_Ok;
}

static tFblMemStatus FblMemEraseRegionInternal( tFblAddress eraseAddress, tFblLength eraseLength ){
   tFblMemStatus  retVal;
   IO_ErrorType   flashErrorCode;
   tFblLength     eraseRemainder;
   tFblLength     currentLength;
   tFblLength     distance;
   vsint16        nextMemSegment;
#if defined( __ApplFblMemConditionCheck )
   tFblMemStatus  customReturnCode;
#endif

   retVal         = kFblMemStatus_Ok;

   eraseRemainder = eraseLength;
   memSegment     = FblMemSegmentNrGet(eraseAddress);

   if(memSegment < 0){
      FBL_MEM_SET_EXT_INFO(EraseAddress, eraseAddress);
      FBL_MEM_SET_STATUS(EraseOutsideFbt, retVal);
   }
   else{
      nextMemSegment = memSegment;

      while(eraseRemainder > 0u)
      {
         FblMemTriggerWatchdog();

         FblMemResponsePending();

         FBL_MEM_SET_EXT_INFO(EraseAddress, eraseAddress);

#if defined( __ApplFblMemDriverReady )

         if(kFblOk != __ApplFblMemDriverReady(memSegment))
         {
            FBL_MEM_SET_STATUS(EraseDriverNotReady, retVal);
            return retVal;
         }
#endif

         currentLength = (FlashBlock[memSegment].end - eraseAddress) + 1u;
         if(eraseRemainder > currentLength)
         {
            nextMemSegment = memSegment + 1;

            if(nextMemSegment >= kNrOfFlashBlock)
            {
               FBL_MEM_SET_STATUS(EraseOutsideFbt, retVal);
               return retVal;
            }

            distance = FlashBlock[nextMemSegment].begin - eraseAddress;
            if(distance <= eraseRemainder)
            {
               eraseRemainder -= distance;
            }
            else
            {
               FBL_MEM_SET_STATUS(EraseOutsideFbt, retVal);
               return retVal;
            }
         }
         else
         {
            currentLength = eraseRemainder;
            eraseRemainder = 0u;
         }

#if defined( __ApplFblMemConditionCheck )

         customReturnCode = __ApplFblMemConditionCheck();

         if(kFblMemStatus_Ok != customReturnCode)
         {
            retVal = customReturnCode;
            return retVal;
         }
#endif
#if defined( __ApplFblMemPreErase )

         if(kFblOk != __ApplFblMemPreErase())
         {
            FBL_MEM_SET_STATUS(ErasePreErase, retVal);
            return retVal;
         }
#endif

         flashErrorCode = MemDriver_REraseSync(currentLength, eraseAddress);

#if defined( __ApplFblMemPostErase )

         if(kFblOk != __ApplFblMemPostErase())
         {
            FBL_MEM_SET_STATUS(ErasePostErase, retVal);
            return retVal;
         }
#endif
#if defined( __ApplFblMemConditionCheck )

         customReturnCode = __ApplFblMemConditionCheck();

         if(kFblMemStatus_Ok != customReturnCode)
         {
            retVal = customReturnCode;
            return retVal;
         }
#endif

         if(IO_E_OK != flashErrorCode)
         {
            FBL_MEM_SET_EXT_STATUS(DriverErase, flashErrorCode, retVal);
            return retVal;
         }

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

         if(kFblMemProgressState_Enabled == gProgressState)
         {
            FblMemUpdateProgress(eraseRemainder);
         }
#endif

         memSegment = nextMemSegment;
         eraseAddress = FlashBlock[memSegment].begin;
      }
   }

   return retVal;
}

static tFblMemStatus FblMemProgramBufferInternal( tFblAddress programAddress
   ,  V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength, tFblMemRamData programData, tFblMemProgState checkPointState ){
   tFblMemStatus     retVal;
   tFblLength        currentLength;
   tFblLength        localLength;
   tFblLength        segLength;
   tFblLength        padLength;
   tFblLength        bufferIndex;
   tFblLength        padOffset;
   IO_ErrorType      flashErrorCode;
#if defined( __ApplFblMemConditionCheck )
   tFblMemStatus     customReturnCode;
#endif

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)checkPointState;
#endif

   retVal      = kFblMemStatus_Ok;
   padLength   = 0u;
   padOffset   = 0u;

   localLength    = *programLength;

   bufferIndex    = 0u;

   while((localLength > 0u) && (kFblMemProgState_Pending == fblMemProgState)){
      FblMemTriggerWatchdog();
#if defined( FBL_ENABLE_ADAPTIVE_DATA_TRANSFER_RCRRP )

#else

      FblMemResponsePending();
#endif

      FBL_MEM_SET_EXT_INFO(ProgramAddress, programAddress);

      currentLength = localLength;

      memSegment    = FblMemSegmentNrGet(programAddress);

      if(memSegment < 0)
      {
         FBL_MEM_SET_STATUS(ProgramOutsideFbt, retVal);
         return retVal;
      }

#if defined( __ApplFblMemDriverReady )

      if(kFblOk != __ApplFblMemDriverReady(memSegment))
      {
         FBL_MEM_SET_STATUS(ProgramDriverNotReady, retVal);
         return retVal;
      }
#endif

      if(0u != (programAddress & ((tFblAddress)MemDriver_SegmentSize - 1u)))
      {
         FBL_MEM_SET_STATUS(ProgramUnalignedAddress, retVal);
         return retVal;
      }

      segLength = (FlashBlock[memSegment].end - programAddress) + 1u;

      if(segLength < currentLength)
      {
         currentLength = segLength;
      }
      else
      {
         padOffset   = bufferIndex + (currentLength - 1u);

         padLength = FblMemPadBuffer(programAddress, currentLength, &programData[padOffset]);
         currentLength += padLength;
      }

#if defined( __ApplFblMemConditionCheck )

      customReturnCode = __ApplFblMemConditionCheck();

      if(kFblMemStatus_Ok != customReturnCode)
      {
         retVal = customReturnCode;
         return retVal;
      }
#endif
#if defined( __ApplFblMemPreWrite )

      if(kFblOk != __ApplFblMemPreWrite())
      {
         FBL_MEM_SET_STATUS(ProgramPreWrite, retVal);
         return retVal;
      }
#endif

      flashErrorCode = MemDriver_RWriteSync(&programData[bufferIndex], currentLength, programAddress);

#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )

      FblMemUnpadBuffer(&programData[padOffset], padLength);
#endif

#if defined( __ApplFblMemPostWrite )

      if(kFblOk != __ApplFblMemPostWrite())
      {
         FBL_MEM_SET_STATUS(ProgramPostWrite, retVal);
         return retVal;
      }
#endif
#if defined( __ApplFblMemConditionCheck )

      customReturnCode = __ApplFblMemConditionCheck();

      if(kFblMemStatus_Ok != customReturnCode)
      {
         retVal = customReturnCode;
         return retVal;
      }
#endif

      if(IO_E_OK != flashErrorCode)
      {
         FBL_MEM_SET_EXT_STATUS(DriverWrite, flashErrorCode, retVal);
         return retVal;
      }

      programAddress += (tFblAddress)currentLength;

      if(localLength > currentLength)
      {
         bufferIndex += currentLength;
         localLength -= currentLength;
      }
      else
      {
         assertFblInternal(((currentLength - padLength) == localLength), kFblMemAssertParameterOutOfRange);

         localLength = 0u;
      }

   }

   *programLength -= localLength;

   return retVal;
}

#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES ) && \
     defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

static tFblLength FblMemGetSpecificRemainder( tFblAddress address, tFblLength length ){
   tFblLength  remainder;
   vsint16     tempSegment;

   remainder = 0u;

   tempSegment = memSegment;
   memSegment = FblMemSegmentNrGet(address);

   if(memSegment >= 0){
      remainder = FblMemGetRemainder(address, length, MemDriver_SegmentSize);
   }

   memSegment = tempSegment;

   return remainder;
}
#endif

#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )

static tFblMemStatus FblMemRelocateBufferOffset( V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob
   ,  tFblMemConstRamData buffer, tFblLength offset, tFblLength length ){
   tFblMemStatus  retVal;
   tFblMemRamData activeBuffer;
   tFblLength activeOffset;

   retVal         = kFblMemStatus_Failed;
   activeBuffer   = activeJob->buffer;

   if(buffer >= activeBuffer){
      activeOffset = (tFblLength)(buffer - activeBuffer);

      if( (length <= activeJob->netSize)
        && (offset <= (activeJob->netSize - length))
        && (activeOffset < activeJob->totalSize)
        && ((offset + length + FBL_MEM_REMAINDER_PADDING) <= (activeJob->totalSize - activeOffset)) )
      {
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

         if((activeOffset + offset) >= activeJob->offset)
#endif
         {
            activeJob->offset = activeOffset;
            retVal = kFblMemStatus_Ok;
         }
      }
   }

   return retVal;
}
#endif

static tFblMemStatus FblMemProgramStream( const V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * programJob
   ,  V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength, tFblMemOperationMode mode ){
   tFblMemStatus  retVal;
   tFblMemRamData programData;
   tFblLength     localLength;
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   tFblLength     requestLength;
   tFblLength     remainder;
#endif

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
#else
   (void)mode;
#endif
#endif

   FblMemTriggerWatchdog();

   localLength = *programLength;

   programData = FblMemGetBuffer(programJob);

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   remainder   = 0u;

   if(kFblMemType_RAM != gSegInfo.input.type){
      assertFblInternal(gSegInfo.writeRemainder <= programJob->position, kFblMemAssertParameterOutOfRange);

      programData = &programJob->buffer[programJob->position - gSegInfo.writeRemainder];

      (void)MEMCPY(programData, gRemainderBuffer.data, gSegInfo.writeRemainder);

      localLength += gSegInfo.writeRemainder;

      if( (kFblMemOperationMode_Finalize == mode)
#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )
#else

        || (localLength == gSegInfo.writeLength)
#endif
         )
      {
      }
      else
      {
         remainder = FblMemGetWriteRemainder(gSegInfo.writeAddress, localLength);

         if(remainder > localLength)
         {
            remainder = 0u;
         }

         localLength -= remainder;

      }
   }

   requestLength = localLength;
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
   if((localLength + remainder) > gSegInfo.writeLength)
#else
   if(localLength > gSegInfo.writeLength)
#endif
   {
      FBL_MEM_SET_STATUS(ProgramOverflow, retVal);
   }
   else{
      if(kFblMemType_RAM == gSegInfo.input.type)
      {
         retVal = FblMemCopyBuffer(gSegInfo.writeAddress, &localLength, programData);
      }
      else
      {
         retVal = FblMemProgramBufferInternal(gSegInfo.writeAddress, &localLength, programData, kFblMemProgState_Checkpoint);
      }
   }

   if(kFblMemStatus_Ok == retVal){
      assertFblInternal(localLength <= gSegInfo.writeLength, kFblMemAssertParameterOutOfRange);

      gSegInfo.writeAddress    += (tFblAddress)localLength;

      gSegInfo.writeLength     -= localLength;
#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )

      gSegInfo.writtenLength   += localLength;
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

      if(requestLength == localLength)
      {
         gSegInfo.writeRemainder = remainder;

         (void)MEMCPY(gRemainderBuffer.data, &programData[localLength], remainder);
      }

      else if(localLength > 0u)
      {
         *programLength = localLength - gSegInfo.writeRemainder;

         gSegInfo.writeRemainder = 0u;
      }
      else
      {
         *programLength = 0u;

      }
#else

      *programLength = localLength;
#endif
   }

   return retVal;
}

#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )

static tFblMemStatus FblMemVerifyInput( V_MEMRAM1 tFblMemVerifyRoutineInput V_MEMRAM2 V_MEMRAM3 * routine
   ,  const V_MEMRAM1 tFblMemVerifyData V_MEMRAM2 V_MEMRAM3 * data, vuint8 state
   ,  V_MEMRAM1 tFblMemVerifyStatus V_MEMRAM2 V_MEMRAM3 * result ){
   tFblMemStatus retVal;
   tFblMemVerifyStatus localResult;

   retVal      = kFblMemStatus_Ok;
   localResult = FBL_MEM_VERIFY_OK;

   if(FBL_MEM_VERIFY_FCT_INPUT_NULL != routine->function){
      routine->param->sigState          = state;
      routine->param->sigSourceBuffer   = data->data;
      routine->param->sigByteCount      = (tFblMemVerifyLength)data->length;
#if defined( FBL_MEM_ENABLE_EXT_TRIGGER_INPUT_VERIFY )
      routine->param->wdTriggerFct      = (tFblMemVerifyWdFct)FblMemTriggerWatchdogExt;
#else
      routine->param->wdTriggerFct      = (tFblMemVerifyWdFct)FblMemTriggerWatchdog;
#endif

      localResult = routine->function(routine->param);
      if(FBL_MEM_VERIFY_OK != localResult)
      {
         retVal = kFblMemStatus_Failed;
      }
   }

   if(FBL_MEM_VERIFY_STATUS_NULL != result){
      *result = localResult;
   }

   return retVal;
}

static tFblMemStatus FblMemInitVerifyInput(void){
   tFblMemStatus     retVal;
   tFblMemVerifyData verifyData;

   retVal = kFblMemStatus_Ok;

   verifyData.data   = FBL_MEM_BUFFER_NULL;
   verifyData.length = 0u;

   return retVal;
}
#endif

static tFblMemStatus FblMemProcessJob( V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob, tFblMemOperationMode mode ){
   tFblLength     actualLength;
#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )     || \
    defined( FBL_ENABLE_DATA_PROCESSING )       || \
    defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   tFblMemRamData activeBuffer;
#endif
#if defined( FBL_ENABLE_DATA_PROCESSING )
   V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * procOutJob;
#endif
#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )
   tFblMemVerifyData verifyData;
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
   tFblResult streamResult;
#endif
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   tFblAddress fillAddress;
   tFblLength  fillLength;
   tFblLength  tempLength;
#endif
   tFblMemOperationMode finalizeStream;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if defined( FBL_MEM_ENABLE_SEGMENTATION )
#else
   (void)mode;
#endif
#endif

   FblMemTriggerWatchdog();

#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )  || \
    defined( FBL_ENABLE_DATA_PROCESSING )    || \
    defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

   activeBuffer   = FblMemGetBuffer(activeJob);
#endif

   actualLength = FblMemLimitLength(activeJob->used, activeJob->type, mode);

   switch(activeJob->type){
#if defined( FBL_ENABLE_DATA_PROCESSING )

      case kFblMemJobType_ProcInput:
      case kFblMemJobType_ProcFinalize:
      {
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
         if(kFblOk == __ApplFblMemIsStreamOutputRequired(gSegInfo.input.dataFormat))
         {
            procOutJob  = &gStreamProcJob;
         }
         else
#endif
         {
            procOutJob  = &gProcWriteJob;
         }

         procOutJob->position = gSegInfo.writeRemainder;

         if(actualLength > 0xFFFFu)
         {
           actualLength = 0xFFFFu;
         }

         gProcParam.dataBuffer      = activeBuffer;
         gProcParam.dataLength      = (vuint16)actualLength;

         gProcParam.dataOutBuffer   = &((FblMemGetBuffer(procOutJob))[procOutJob->used]);
         gProcParam.dataOutLength   = 0u;

         if(kFblOk != ApplFblDataProcessing(&gProcParam))
         {
            FBL_MEM_SET_STATUS(DataProc, gErrorStatus);
         }
         else
         {
            if((gProcParam.dataOutLength | gProcParam.dataLength) == 0u)
            {
               if(kFblMemJobType_ProcFinalize == activeJob->type)
               {
                  if(kFblOk != ApplFblDeinitDataProcessing(&gProcParam))
                  {
                     FBL_MEM_SET_STATUS(DataProcDeinit, gErrorStatus);
                  }

                  activeJob->completion = kFblMemOperationMode_Unconditional;
               }
               else
               {
                  FBL_MEM_SET_STATUS(DataProcConsume, gErrorStatus);
               }
            }
         }

         if(kFblMemStatus_Ok == gErrorStatus)
         {
            actualLength = gProcParam.dataLength;

            if(gProcParam.dataOutLength > 0u)
            {
               assertFblUser((gProcParam.dataOutBuffer == &((FblMemGetBuffer(procOutJob))[procOutJob->used])), kFblMemAssertUserResultOutOfRange);

               assertFblUser((gProcParam.dataOutLength <= FBL_MEM_INTERNAL_PROC_SEGMENTATION), kFblMemAssertUserResultOutOfRange);

               procOutJob->used += gProcParam.dataOutLength;

               assertFblInternal((procOutJob->used <= (procOutJob->totalSize - procOutJob->offset)), kFblMemAssertParameterOutOfRange);

#if defined( FBL_MEM_ENABLE_PROC_SEGMENTATION )

               if(procOutJob->used == gProcParam.dataOutLength)
               {
                  gProcHandle = FblMemQueueDefaultPrioInsert(gProcessingQueue, procOutJob, activeJob->segmentIndex);
               }

               if((procOutJob->netSize - procOutJob->used) < FBL_MEM_INTERNAL_PROC_SEGMENTATION)
               {
                  (void)FblMemQueuePrioUpdate(gProcessingQueue, gProcHandle, kFblMemJobPrio_ProcWriteHigh);
               }
#else

               (void)FblMemQueueDefaultPrioInsert(gProcessingQueue, procOutJob, activeJob->segmentIndex);
#endif
            }

         }

         break;
      }
      case kFblMemJobType_ProcWrite:
#endif
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
      case kFblMemJobType_WriteFinalize:
#endif
      case kFblMemJobType_InputWrite:
      {
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
         if(kFblMemJobType_WriteFinalize == activeJob->type)
         {
            finalizeStream       = kFblMemOperationMode_Finalize;

            activeJob->position  = gSegInfo.writeRemainder;
         }
#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )
#else
         else if(kFblMemJobType_InputWrite == activeJob->type)
         {
            finalizeStream = kFblMemOperationMode_Finalize;
         }
#endif
         else
#endif
         {
            finalizeStream = kFblMemOperationMode_Normal;
         }

         gErrorStatus = FblMemProgramStream(activeJob, &actualLength, finalizeStream);

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

         if(kFblMemStatus_Ok == gErrorStatus)
         {
#if defined( FBL_MEM_ENABLE_GAP_FILL )
            FblMemUpdateProgress(gSegInfo.writeLength + gGapFillJob.used);
#else
            FblMemUpdateProgress(gSegInfo.writeLength);
#endif
         }
#endif

         break;
      }
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
      case kFblMemJobType_StreamInput:
      case kFblMemJobType_StreamProc:
      case kFblMemJobType_StreamFinalize:
      {
         gStreamParam.inputData        = activeBuffer;
         gStreamParam.inputLength      = actualLength;
         gStreamParam.consumedLength   = 0u;
         gStreamParam.producedLength   = 0u;
         gStreamParam.address          = gSegInfo.writeAddress;
         gStreamParam.length           = gSegInfo.writeLength;

         if(kFblMemJobType_StreamFinalize == activeJob->type)
         {
            streamResult = ApplFblFinalizeStreamOutput(&gStreamParam);
         }
         else
         {
            streamResult = ApplFblStreamOutput(&gStreamParam);
         }

         if(kFblOk != streamResult)
         {
            FBL_MEM_SET_STATUS(StreamOutput, gErrorStatus);
         }
         else
         {
            if((gStreamParam.consumedLength | gStreamParam.producedLength) == 0u)
            {
               if(kFblMemJobType_StreamFinalize == activeJob->type)
               {
                  if(kFblOk != ApplFblDeinitStreamOutput(&gStreamParam))
                  {
                     FBL_MEM_SET_STATUS(StreamOutputDeinit, gErrorStatus);
                  }

                  activeJob->completion = kFblMemOperationMode_Unconditional;
               }
               else
               {
                  FBL_MEM_SET_STATUS(StreamOutputConsume, gErrorStatus);
               }
            }
         }

         if(kFblMemStatus_Ok == gErrorStatus)
         {
            actualLength = gStreamParam.consumedLength;

            if(gStreamParam.producedLength > 0u)
            {
               if(gStreamParam.producedLength > gSegInfo.writeLength)
               {
                  FBL_MEM_SET_STATUS(StreamOutputConsume, gErrorStatus);
               }
               else
               {
                  gSegInfo.writeAddress   += gStreamParam.producedLength;

                  gSegInfo.writeLength    -= gStreamParam.producedLength;
#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )

                  gSegInfo.writtenLength  += gStreamParam.producedLength;
#endif
               }
            }

         }

         break;
      }
#endif
#if defined( FBL_MEM_ENABLE_GAP_FILL )
      case kFblMemJobType_GapFill:
      {
         fillAddress    = activeJob->baseAddress + activeJob->position;

         fillLength     = actualLength;

         actualLength   = 0u;

         memSegment = FblMemSegmentNrGet(fillAddress);

         if(memSegment < 0)
         {
            memSegment = FblMemSegmentNrGet(fillAddress - 1u) + 1;

            if((memSegment >= kNrOfFlashBlock) || (memSegment <= 0))
            {
               FBL_MEM_SET_STATUS(ProgramOutsideFbt, gErrorStatus);
            }
            else
            {
               if(FlashBlock[memSegment].begin > fillAddress)
               {
                  tempLength = FlashBlock[memSegment].begin - fillAddress;

                  if(tempLength < fillLength)
                  {
                     actualLength = tempLength;
                     fillLength  -= actualLength;
                     fillAddress  = FlashBlock[memSegment].begin;
                  }
                  else
                  {
                     actualLength   = fillLength;
                     fillLength     = 0u;
                  }
               }
               else
               {
                  actualLength   = fillLength;
                  fillLength     = 0u;
               }
            }
         }

         if(kFblMemStatus_Ok == gErrorStatus)
         {
            if(fillLength > FBL_MEM_GAP_FILL_SEGMENTATION)
            {
               fillLength = FBL_MEM_GAP_FILL_SEGMENTATION;
            }

            tempLength =(FlashBlock[memSegment].end - fillAddress) + 1u;

            if(fillLength > tempLength)
            {
               fillLength = tempLength;
            }

            if(fillLength > 0u)
            {
               gErrorStatus = FblMemProgramBufferInternal(fillAddress, &fillLength, gGapFillBuffer.data, kFblMemProgState_Pending);

               actualLength += fillLength;
            }
         }

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )
         if(kFblMemStatus_Ok == gErrorStatus)
         {
            FblMemUpdateProgress(gSegInfo.writeLength + (gGapFillJob.used - actualLength));
         }
#endif

         break;
      }
#endif
      case kFblMemJobType_Max:
      default:
      {
         FBL_MEM_SET_STATUS(Failed, gErrorStatus);

         break;
      }
   }

   activeJob->position  += actualLength;
   activeJob->used      -= actualLength;

#if defined( FBL_ENABLE_SYSTEM_CHECK )
   if(kFblMemStatus_Ok == gErrorStatus){
      if(kFblMemStatus_Ok != FblMemVerifyBufferIntegrity())
      {
         FBL_MEM_SET_STATUS(Failed, gErrorStatus);
      }
   }
#endif

   return gErrorStatus;
}

static void FblMemProcessQueue( tFblMemOperationMode mode ){
#if defined( FBL_MEM_ENABLE_PROC_QUEUE )
   tFblMemQueueHandle activeHandle;
#endif
   V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob;

   FblMemTriggerWatchdog();

   __ApplFblMemEnterCriticalSection();

   if(fblMemProgState < kFblMemProgState_Suspended){
   }
   else{
      fblMemProgState = kFblMemProgState_Pending;
   }

   __ApplFblMemLeaveCriticalSection();

   if(kFblMemProgState_Pending == fblMemProgState){
#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

      activeHandle      = FblMemQueueGetFirstUsedHandle(gProcessingQueue);
      activeJob         = gProcessingQueue[activeHandle].job;
#else

      activeJob         = &FBL_MEM_INPUT_JOB[0];
#endif

      if(kFblMemStatus_Ok == FblMemProcessJob(activeJob, mode))
      {
         if(  (kFblMemOperationMode_Unconditional == activeJob->completion)
            || ((kFblMemOperationMode_Normal == activeJob->completion) && (0u == activeJob->used)) )
         {
#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

            (void)FblMemQueueRemove(gProcessingQueue, activeHandle);

            if(FblMemQueueIsEmpty(gProcessingQueue))
#endif
            {
               fblMemProgState = kFblMemProgState_Idle;
            }

         }
      }
      else
      {
         fblMemProgState = kFblMemProgState_Error;

      }

   }
}

static void FblMemFlushQueueByPrio( tFblMemQueuePrio prio ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )
#else
   (void)prio;
#endif
#endif

   while( (FblMemTaskIsPending())
#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

        && (FblMemQueueGetFirstUsedEntry(gProcessingQueue).prio >= prio)
#endif
         ){
      FblMemProcessQueue(kFblMemOperationMode_Finalize);
   }
}

static tFblMemStatus FblMemQueueBuffer( tFblMemConstRamData buffer, tFblLength offset, tFblLength length ){
   tFblMemStatus  retVal;
   V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER ) || \
     defined( FBL_ENABLE_SYSTEM_CHECK )               || \
     defined( FBL_ENABLE_ASSERTION )
#else
   (void)buffer;
#endif
#endif

   activeJob = FblMemGetPendingInputJob();

#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER ) || \
    defined( FBL_ENABLE_SYSTEM_CHECK )
#if defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )
   if(kFblMemStatus_Ok != FblMemRelocateBufferOffset(activeJob, buffer, offset, length))
#else

   if( (buffer != FblMemGetBuffer(activeJob))
     || (offset >= activeJob->netSize)
     || (length > (activeJob->netSize - offset)) )
#endif
   {
      FBL_MEM_SET_STATUS(DataIndParam, retVal);
   }
   else
#else
   assertFblUser(buffer == FblMemGetBuffer(activeJob),      kFblMemAssertParameterOutOfRange);
   assertFblUser(offset <  activeJob->netSize,              kFblMemAssertParameterOutOfRange);
   assertFblUser(length <= (activeJob->netSize - offset),   kFblMemAssertParameterOutOfRange);
#endif
   {
      if(kFblMemProgState_Error != fblMemProgState)
      {
         activeJob->position  = activeJob->offset + offset;
         activeJob->used      = length;
#if defined( FBL_ENABLE_DATA_PROCESSING )    || \
    defined( FBL_MEM_ENABLE_STREAM_OUTPUT )  || \
    defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

         activeJob->type      = gSegInfo.jobType;
#endif

         {
         }

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )
         {
            (void)FblMemQueueDefaultPrioInsert(gProcessingQueue, activeJob, gSegInfo.ownIndex);

         }
#endif

         {
            fblMemProgState = kFblMemProgState_Pending;
         }
      }

      retVal = gErrorStatus;
   }

   return retVal;
}

static tFblResult FblMemCheckAllowed( tFblMemAllowedInd check, tFblMemAllowedInd clear ){
   tFblResult retVal;

   FblMemTriggerWatchdog();

   if(FblMemIsAllowed(check)){
      FblMemClrAllowed(clear);
      retVal = kFblOk;
   }
   else{
      FblMemResetAllowed();
      retVal = kFblFailed;
   }

   return retVal;
}

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

static vuint8 FblMemCalculateProgress( vuint32 current, vuint32 total, vuint8 percentage ){
   vuint8 progress;

   progress = percentage;

   if((0u != total) && (0u != percentage)){
      if(total < (((vuint32)-1) / (vuint32)percentage))
      {
         progress = (vuint8)(((current * percentage) / total) & 0xFFu);
      }
      else
      {
         progress = (vuint8)((current / (total / percentage)) & 0xFFu);
      }
   }

   if(progress > percentage){
      progress = percentage;
   }

   return progress;
}

static void FblMemInitProgress(void){
   gProgressInfo.type                  = kFblMemProgressType_Undefined;

   gPrevProgressInfo.type              = kFblMemProgressType_Undefined;
   gPrevProgressInfo.totalProgress     = FBL_MEM_PROGRESS_INITIAL;
   gPrevProgressInfo.partialProgress   = FBL_MEM_PROGRESS_INITIAL;
}

static void FblMemReportProgress(void){
   if(  (FBL_MEM_PROGRESS_COMPLETE       == gProgressInfo.partialProgress)
      || (gPrevProgressInfo.type          != gProgressInfo.type)
      || (gPrevProgressInfo.segmentCount  != gProgressInfo.segmentCount)
      || ((gProgressInfo.totalProgress - gPrevProgressInfo.totalProgress) >= (vuint8)FBL_MEM_PROGRESS_THRESHOLD_PERCENTAGE)
      || ((gProgressInfo.partialProgress - gPrevProgressInfo.partialProgress) >= (vuint8)FBL_MEM_PROGRESS_THRESHOLD_PERCENTAGE) ){
      if(FBL_MEM_PROGRESS_COMPLETE != gPrevProgressInfo.partialProgress)
      {
         __ApplFblMemReportProgress(&gProgressInfo);

         gPrevProgressInfo = gProgressInfo;
      }
   }
}

static void FblMemSetupProgress( tFblMemProgressType type, tFblAddress logicalAddress, vuint32 segmentCount
   ,  vuint8 totalOffset, vuint8 totalPercentage, vuint32 target ){
   gProgressInfo.type                     = type;
   gProgressInfo.logicalAddress           = logicalAddress;
   gProgressInfo.segmentCount             = segmentCount;

   gProgressInfoInternal.totalOffset      = totalOffset;
   gProgressInfoInternal.totalPercentage  = totalPercentage;

   gProgressInfoInternal.target           = target;

   gProgressPrevRemainder                 = 0u;
   gPrevProgressInfo.totalProgress        = FBL_MEM_PROGRESS_INITIAL;
   gPrevProgressInfo.partialProgress      = FBL_MEM_PROGRESS_INITIAL;
}

static void FblMemOffsetProgress( vuint32 totalDone, vuint32 totalTarget ){
   gProgressInfoInternal.totalOffset      +=
      FblMemCalculateProgress(totalDone, totalTarget, gProgressInfoInternal.totalPercentage);

   gProgressInfoInternal.totalPercentage   =
      FblMemCalculateProgress(gProgressInfoInternal.target, totalTarget, gProgressInfoInternal.totalPercentage);
}

static void FblMemUpdateProgress( vuint32 remainder ){
   vuint32 done;

   if(  (gProgressPrevRemainder < remainder)
      || ((gProgressPrevRemainder - remainder) >= FBL_MEM_PROGRESS_THRESHOLD_BYTES) ){
      done = gProgressInfoInternal.target - remainder;

      gProgressInfo.totalProgress   =
         gProgressInfoInternal.totalOffset
         + FblMemCalculateProgress(done, gProgressInfoInternal.target, gProgressInfoInternal.totalPercentage);
      gProgressInfo.partialProgress =
         FBL_MEM_PROGRESS_INITIAL + FblMemCalculateProgress(done, gProgressInfoInternal.target, FBL_MEM_PROGRESS_COMPLETE);

      FblMemReportProgress();

      gProgressPrevRemainder = remainder;
   }
}

static void FblMemConcludeProgress(void){
   gProgressInfo.totalProgress   = gProgressInfoInternal.totalOffset + gProgressInfoInternal.totalPercentage;
   gProgressInfo.partialProgress = FBL_MEM_PROGRESS_COMPLETE;

   FblMemReportProgress();
}

#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
#if defined( FBL_MEM_ENABLE_SWITCH_READMEMORY_PARAM )

static tFblMemVerifySize FblMemProgressRead( tFblMemVerifyAddr address, tFblMemVerifySize length, tFblMemVerifyDataPtr buffer )
#else

static tFblMemVerifySize FblMemProgressRead( tFblMemVerifyAddr address, tFblMemVerifyDataPtr buffer, tFblMemVerifySize length )
#endif
{
   vuint32 position;

   position = address - gBlockInfo.targetAddress;

   FblMemUpdateProgress(gBlockInfo.targetLength - position);

   return gBlockInfo.readFct(address, buffer, length);
}
#endif
#endif

tFblMemRamData FblMemInitPowerOnExt( tFblLength preambleLen, tFblMemInputSource sourceHandle ){
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   vuintx idx;
#endif

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if defined( FBL_MEM_ENABLE_DYNAMIC_PREAMBLE_LENGTH )
#else
   (void)preambleLen;
#endif
#if defined( FBL_MEM_ENABLE_MULTI_SOURCE )
#else
   (void)sourceHandle;
#endif
#endif

#if defined( FBL_MEM_ENABLE_MULTI_SOURCE )

   assertFblUser(sourceHandle < FBL_MEM_SOURCE_COUNT, kFblMemAssertParameterOutOfRange);
#endif

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

   assertFblInternal(kFblMemJobType_Max == (FBL_MEM_ARRAY_SIZE(gJobPrio) - 1), kFblMemAssertParameterOutOfRange);
#endif
#if defined( FBL_MEM_ENABLE_SEGMENTATION )

   assertFblInternal(kFblMemJobType_Max == (FBL_MEM_ARRAY_SIZE(gLengthLimits) - 1), kFblMemAssertParameterOutOfRange);
#endif

#if defined( FBL_ENABLE_DATA_PROCESSING )

   FblMemInitJob(&gProcWriteJob, gProcBuffer.data, FBL_MEM_ARRAY_SIZE(gProcBuffer.data), kFblMemJobType_ProcWrite);

   gProcWriteJob.netSize = FBL_MEM_PROC_BUFFER_SIZE;

   FblMemInitJob(&gProcFinalizeJob, FBL_MEM_BUFFER_NULL, 0, kFblMemJobType_ProcFinalize);

   gProcParam.dataOutMaxLength = (vuint16)FBL_MEM_INTERNAL_PROC_SEGMENTATION;
#if defined( FBL_MEM_ENABLE_EXT_TRIGGER_DATA_PROC )
   gProcParam.wdTriggerFct     = FblMemTriggerWatchdogExt;
#else
   gProcParam.wdTriggerFct     = FblMemTriggerWatchdog;
#endif
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

#if defined( FBL_ENABLE_DATA_PROCESSING )
   FblMemInitJob(&gStreamProcJob, gProcBuffer.data, FBL_MEM_ARRAY_SIZE(gProcBuffer.data), kFblMemJobType_StreamProc);

   gStreamProcJob.netSize = FBL_MEM_PROC_BUFFER_SIZE;
#endif

   FblMemInitJob(&gStreamFinalizeJob, FBL_MEM_BUFFER_NULL, 0, kFblMemJobType_StreamFinalize);

   gStreamParam.outputData = FBL_MEM_BUFFER_NULL;
   gStreamParam.outputSize = 0u;
   gStreamParam.watchdog   = FblMemTriggerWatchdog;
#endif

#if defined( FBL_MEM_ENABLE_GAP_FILL )

   FblMemInitJob(&gGapFillJob, FBL_MEM_BUFFER_NULL, FBL_MEM_ARRAY_SIZE(gGapFillBuffer.data), kFblMemJobType_GapFill);

   for(idx = 0u; idx < FBL_MEM_ARRAY_SIZE(gGapFillBuffer.data); idx++){
      gGapFillBuffer.data[idx] = kFillChar;
   }
#endif

#if defined( FBL_MEM_ENABLE_MULTI_SOURCE )
   gActiveSource = sourceHandle;
#endif

#if defined( FBL_MEM_ENABLE_DYNAMIC_PREAMBLE_LENGTH )
   gPreambleLength[FBL_MEM_ACTIVE_SOURCE] = preambleLen;
#endif

   return FblMemInitInternal();
}

tFblMemRamData FblMemInitPowerOn(void){
   return FblMemInitPowerOnExt(FBL_MEM_DEFAULT_PREAMBLE_LENGTH, FBL_MEM_SOURCE_HANDLE_DEFAULT);
}

tFblMemRamData FblMemInit(void){
   tFblMemRamData activeBuffer;

#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

   FblMemStorePreamble();
#endif

   activeBuffer = FblMemInitInternal();

#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

   FblMemRestorePreamble();
#endif

   return activeBuffer;
}

void FblMemDeinit(void){
   FblMemInitStates();
}

#if defined( FBL_MEM_ENABLE_MULTI_SOURCE )

void FblMemLockInputSource( tFblMemInputSource sourceHandle ){
   assertFblInternal(sourceHandle < FBL_MEM_SOURCE_COUNT, kFblMemAssertParameterOutOfRange);

   gActiveSource = sourceHandle;
}
#endif

tFblMemRamData FblMemGetActiveBuffer(void){
   V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * inputJob;

   inputJob = FblMemGetPendingInputJob();

   inputJob->position = inputJob->offset;

   return FblMemGetBuffer(inputJob);
}

tFblMemStatus FblMemBlockEraseIndication( const V_MEMRAM1 tFblMemBlockInfo V_MEMRAM2 V_MEMRAM3 * block ){
   tFblMemStatus  retVal;

   if(kFblOk != FblMemCheckAllowed(FBL_MEM_ALLOWED_BLOCK_ERASE, FBL_MEM_ALLOWED_NONE)){
      FBL_MEM_SET_STATUS(BlockEraseSequence, retVal);
   }
   else{
#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

      FblMemSetupProgress(kFblMemProgressType_Erase, block->logicalAddress, 0u
   ,        FBL_MEM_PROGRESS_INITIAL, FBL_MEM_PROGRESS_ERASE, block->targetLength);

      FblMemUpdateProgress(block->targetLength);

      gProgressState = kFblMemProgressState_Enabled;
#endif

      retVal = FblMemEraseRegionInternal(block->targetAddress, block->targetLength);

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

      FblMemConcludeProgress();
#endif
   }

   if(kFblMemStatus_Ok == retVal){
      FblMemSetAllowed(FBL_MEM_ALLOWED_BLOCK_START | FBL_MEM_ALLOWED_BLOCK_ERASE);
   }

   return retVal;
}

tFblMemStatus FblMemBlockStartIndication( V_MEMRAM1 tFblMemBlockInfo V_MEMRAM2 V_MEMRAM3 * block ){
   tFblMemStatus     retVal;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

#if defined( FBL_MEM_ENABLE_GLOBAL_BLOCK_INFO )
#else
   (void)block;
#endif
#endif

   retVal = kFblMemStatus_Ok;

   if(kFblOk != FblMemCheckAllowed(FBL_MEM_ALLOWED_BLOCK_START, FBL_MEM_ALLOWED_BLOCK_START)){
      FBL_MEM_SET_STATUS(BlockStartSequence, retVal);
   }
   else{
#if defined( FBL_ENABLE_SYSTEM_CHECK ) && \
    defined( FBL_MEM_ENABLE_VERIFICATION )

#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
      if(FBL_MEM_VERIFY_FCT_OUTPUT_NULL != block->verifyRoutineOutput.function)
      {
      }
      else
#endif
      {
         FBL_MEM_SET_STATUS(BlockStartParam, retVal);
      }
#endif
   }

   if(kFblMemStatus_Ok == retVal){
#if defined( FBL_MEM_ENABLE_GLOBAL_BLOCK_INFO )
      gBlockInfo = *block;
#endif
#if defined( FBL_MEM_ENABLE_SEGMENT_HANDLING )

      gBlockInfo.segmentList->nrOfSegments = 0u;
#endif

      gSegInfo.nextIndex = 0u;

      FblMemSetAllowed(FBL_MEM_ALLOWED_SEGMENT_START);
   }

   return retVal;
}

tFblMemStatus FblMemBlockEndIndication(void){
   tFblMemStatus retVal;
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   tFblAddress baseAddress;
   tFblLength  baseLength;
#endif

   retVal = kFblMemStatus_Ok;

   if(kFblOk != FblMemCheckAllowed(FBL_MEM_ALLOWED_BLOCK_END, FBL_MEM_ALLOWED_BLOCK_END)){
      FBL_MEM_SET_STATUS(BlockEndSequence, retVal);
   }
   else{
#if defined( FBL_MEM_ENABLE_GAP_FILL )

      if(kFblMemType_RAM != gSegInfo.input.type)
      {
         baseAddress = gBlockInfo.segmentList->segmentInfo[gSegInfo.ownIndex].targetAddress;
         baseLength  = gBlockInfo.segmentList->segmentInfo[gSegInfo.ownIndex].length;

         baseLength += FblMemPadLength(baseAddress, baseLength);

         gGapFillJob.used  = (gBlockInfo.targetLength - (baseAddress - gBlockInfo.targetAddress)) - baseLength;

         if(gGapFillJob.used > 0u)
         {
            gGapFillJob.position    = 0u;

            gGapFillJob.baseAddress = baseAddress + baseLength;

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

            FblMemSetupProgress(kFblMemProgressType_GapFill, gBlockInfo.logicalAddress, gSegInfo.nextIndex
   ,              FBL_MEM_PROGRESS_INITIAL + FBL_MEM_PROGRESS_ERASE, FBL_MEM_PROGRESS_PROGRAM, gGapFillJob.used);

            FblMemOffsetProgress((gGapFillJob.baseAddress - gBlockInfo.targetAddress), gBlockInfo.targetLength);

            FblMemUpdateProgress(gGapFillJob.used);
#endif

            (void)FblMemQueueDefaultPrioInsert(gProcessingQueue, &gGapFillJob, gSegInfo.ownIndex);

            fblMemProgState = kFblMemProgState_Pending;

            FblMemFlushQueueByPrio(kFblMemJobPrio_Write);
         }
      }
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

      FblMemConcludeProgress();
#endif

      {
      }
   }

   if(kFblMemStatus_Ok == retVal){
      FblMemSetAllowed(FBL_MEM_ALLOWED_BLOCK_VERIFY);
   }

   return retVal;
}

tFblMemStatus FblMemBlockVerify( const V_MEMRAM1 tFblMemBlockVerifyData V_MEMRAM2 V_MEMRAM3 * verifyData
   ,  V_MEMRAM1 tFblMemVerifyStatus V_MEMRAM2 V_MEMRAM3 * verifyResult ){
   tFblMemStatus retVal;
   tFblMemVerifyStatus localResult;
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT_FULL_BLOCK_LENGTH )
#else
   V_MEMRAM1 tFblMemSegmentListEntry V_MEMRAM2 V_MEMRAM3 * lastSegment;
#endif
#endif

#if defined( FBL_MEM_ENABLE_VERIFICATION )
#else
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)verifyData;
#endif
#endif

   retVal      = kFblMemStatus_Ok;
   localResult = FBL_MEM_VERIFY_OK;

   if(kFblOk != FblMemCheckAllowed(FBL_MEM_ALLOWED_BLOCK_VERIFY, FBL_MEM_ALLOWED_NONE)){
      FBL_MEM_SET_STATUS(BlockVerifySequence, retVal);
   }
   else{
      {
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
         {
            if(FBL_MEM_VERIFY_FCT_OUTPUT_NULL != gBlockInfo.verifyRoutineOutput.function)
            {
#if defined( FBL_MEM_ENABLE_EXT_TRIGGER_OUTPUT_VERIFY )
               gBlockInfo.verifyRoutineOutput.param->wdTriggerFct       = (tFblMemVerifyWdFct)FblMemTriggerWatchdogExt;
#else
               gBlockInfo.verifyRoutineOutput.param->wdTriggerFct       = (tFblMemVerifyWdFct)FblMemTriggerWatchdog;
#endif
#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

               FblMemSetupProgress(kFblMemProgressType_Verify, gBlockInfo.logicalAddress, 0u
   ,                 FBL_MEM_PROGRESS_INITIAL + FBL_MEM_PROGRESS_ERASE + FBL_MEM_PROGRESS_PROGRAM, FBL_MEM_PROGRESS_VERIFY
   ,                 gBlockInfo.targetLength);

               FblMemUpdateProgress(gBlockInfo.targetLength);

               gBlockInfo.verifyRoutineOutput.param->readMemory         = FblMemProgressRead;
#else
               gBlockInfo.verifyRoutineOutput.param->readMemory         = gBlockInfo.readFct;
#endif
               gBlockInfo.verifyRoutineOutput.param->verificationData   = verifyData->verifyDataOutput.data;

               gBlockInfo.verifyRoutineOutput.param->blockStartAddress  = gBlockInfo.targetAddress;
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT_FULL_BLOCK_LENGTH )
               gBlockInfo.verifyRoutineOutput.param->blockLength        = gBlockInfo.targetLength;
#else

               lastSegment = &(gBlockInfo.segmentList->segmentInfo[gBlockInfo.segmentList->nrOfSegments - 1u]);

               gBlockInfo.verifyRoutineOutput.param->blockLength = (lastSegment->targetAddress - gBlockInfo.targetAddress)
                                                                   + lastSegment->length;
#endif

               localResult = gBlockInfo.verifyRoutineOutput.function(gBlockInfo.verifyRoutineOutput.param);
               if(FBL_MEM_VERIFY_OK != localResult)
               {
                  FBL_MEM_SET_STATUS(BlockVerifyOutputVerify, retVal);
               }
            }
         }
#else
         {
         }
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

         FblMemConcludeProgress();
#endif
      }
   }

   if(kFblMemStatus_Ok == retVal){
      FblMemAddAllowed(FBL_MEM_ALLOWED_BLOCK_START | FBL_MEM_ALLOWED_BLOCK_ERASE);
   }

   if(FBL_MEM_VERIFY_STATUS_NULL != verifyResult){
      *verifyResult = localResult;
   }

   return retVal;
}

tFblMemStatus FblMemSegmentStartIndication( const V_MEMRAM1 tFblMemSegmentInfo V_MEMRAM2 V_MEMRAM3 * segment ){
   tFblMemStatus     retVal;
#if defined( FBL_MEM_ENABLE_GAP_FILL )
   tFblAddress baseAddress;
   tFblLength  baseLength;
#endif
#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )
   tFblAddress progressAddress;
   tFblLength  progressRemainder;
#endif

   retVal = kFblMemStatus_Ok;

#if defined( FBL_ENABLE_DATA_PROCESSING )    || \
    defined( FBL_MEM_ENABLE_STREAM_OUTPUT )  || \
    defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

   gSegInfo.jobType = kFblMemJobType_InputWrite;
#endif

   if(kFblOk != FblMemCheckAllowed(FBL_MEM_ALLOWED_SEGMENT_START, FBL_MEM_ALLOWED_SEGMENT_START)){
      FBL_MEM_SET_STATUS(SegmentStartSequence, retVal);
   }
#if defined( FBL_MEM_ENABLE_SEGMENT_HANDLING )
   else if(gBlockInfo.segmentList->nrOfSegments >= gBlockInfo.maxSegments){
      FBL_MEM_SET_STATUS(SegmentStartSegmentCount, retVal);
   }
#endif
   else{
#if defined( FBL_MEM_ENABLE_VERIFY_STREAM )

      if(0u == gSegInfo.nextIndex)
      {
         if(kFblMemStatus_Ok != FblMemInitVerifyInput())
         {
            FBL_MEM_SET_STATUS(SegmentStartVerifyInit, retVal);
         }
      }

      if(kFblMemStatus_Ok == retVal)
#endif
#if defined( FBL_MEM_ENABLE_VERIFY_ADDRESS_LENGTH )
      {
         {
         }
      }

      if(kFblMemStatus_Ok == retVal)
#endif
      {
         if(kFblOk == __ApplFblMemIsDataProcessingRequired(segment->dataFormat))
         {
#if defined( FBL_ENABLE_DATA_PROCESSING )

            gSegInfo.jobType = kFblMemJobType_ProcInput;

            gProcParam.mode = segment->dataFormat;

            if(kFblOk != ApplFblInitDataProcessing(&gProcParam))
            {
               FBL_MEM_SET_STATUS(SegmentStartDataProcInit, retVal);
            }
#else

            FBL_MEM_SET_STATUS(SegmentStartDataProcInit, retVal);
#endif
         }
      }

#if defined( __ApplFblMemIsStreamOutputRequired )
      if(kFblMemStatus_Ok == retVal)
      {
         if(kFblOk == __ApplFblMemIsStreamOutputRequired(segment->dataFormat))
         {
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
#if defined( FBL_ENABLE_DATA_PROCESSING )
            if(kFblOk == __ApplFblMemIsDataProcessingRequired(segment->dataFormat))
            {
            }
            else
#endif
            {
               gSegInfo.jobType = kFblMemJobType_StreamInput;
            }

            gStreamParam.mode          = segment->dataFormat;
            gStreamParam.baseAddress   = segment->targetAddress;
            gStreamParam.baseLength    = gBlockInfo.targetLength - (segment->targetAddress - gBlockInfo.targetAddress);

            if(kFblOk != ApplFblInitStreamOutput(&gStreamParam))
            {
               FBL_MEM_SET_STATUS(SegmentStartStreamOutInit, retVal);
            }
#else

            FBL_MEM_SET_STATUS(SegmentStartStreamOutInit, retVal);
#endif
         }
      }
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

      progressAddress   = segment->targetAddress;
      progressRemainder = segment->targetLength;
#endif

#if defined( FBL_MEM_ENABLE_GAP_FILL )
      if(kFblMemStatus_Ok == retVal)
      {
         if(kFblMemType_RAM != segment->type)
         {
            if(0u == gSegInfo.nextIndex)
            {
               baseAddress = gBlockInfo.targetAddress;
               baseLength  = 0u;
            }
            else
            {
               baseAddress = gBlockInfo.segmentList->segmentInfo[gSegInfo.ownIndex].targetAddress;
               baseLength  = gBlockInfo.segmentList->segmentInfo[gSegInfo.ownIndex].length;
            }

            baseLength += FblMemPadLength(baseAddress, baseLength);

            assertFblInternal((segment->targetAddress >= baseAddress), kFblMemAssertParameterOutOfRange);
            assertFblInternal(((segment->targetAddress - baseAddress) >= baseLength), kFblMemAssertParameterOutOfRange);

            gGapFillJob.used = (segment->targetAddress - baseAddress) - baseLength;

            if(gGapFillJob.used > 0u)
            {
               gGapFillJob.position    = 0u;

               gGapFillJob.baseAddress = baseAddress + baseLength;

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

               progressAddress    = gGapFillJob.baseAddress;
               progressRemainder += gGapFillJob.used;
#endif

               (void)FblMemQueueDefaultPrioInsert(gProcessingQueue, &gGapFillJob, gSegInfo.nextIndex);

            }
         }
      }
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

      FblMemSetupProgress(kFblMemProgressType_Program, gBlockInfo.logicalAddress, gSegInfo.nextIndex
   ,        FBL_MEM_PROGRESS_INITIAL + FBL_MEM_PROGRESS_ERASE, FBL_MEM_PROGRESS_PROGRAM, progressRemainder);

      FblMemOffsetProgress((progressAddress - gBlockInfo.targetAddress), gBlockInfo.targetLength);

      FblMemUpdateProgress(progressRemainder);
#endif
   }

   if(kFblMemStatus_Ok == retVal){
      gSegInfo.input          = *segment;

      gSegInfo.writeAddress   = segment->targetAddress;
      gSegInfo.writeRemainder = 0u;
#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )

      gSegInfo.writeLength    = gBlockInfo.targetLength - (segment->targetAddress - gBlockInfo.targetAddress);
      gSegInfo.writtenLength  = 0u;
#else
      gSegInfo.writeLength    = segment->targetLength;
#endif
#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )

      gSegInfo.inputAddress   = segment->targetAddress;
#endif
#if defined( FBL_MEM_ENABLE_INPUT_LENGTH )

      gSegInfo.inputLength    = segment->targetLength;
#endif

      gSegInfo.ownIndex       = gSegInfo.nextIndex;
      gSegInfo.nextIndex++;

      FblMemSetAllowed(FBL_MEM_ALLOWED_DATA_IND);
   }

   return retVal;
}

tFblMemStatus FblMemSegmentEndIndication( V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * writeLength ){
   tFblMemStatus retVal;
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING_SINGLE_JOB ) || \
    defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER ) || \
    defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )
   V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob;
#endif
#if defined( FBL_MEM_ENABLE_SEGMENT_HANDLING )
   V_MEMRAM1 tFblMemSegmentListEntry V_MEMRAM2 V_MEMRAM3 * activeSegment;
#endif

   retVal = kFblMemStatus_Ok;

   if(kFblOk != FblMemCheckAllowed(FBL_MEM_ALLOWED_SEGMENT_END, FBL_MEM_ALLOWED_DATA_IND | FBL_MEM_ALLOWED_SEGMENT_END)){
      FBL_MEM_SET_STATUS(SegmentEndSequence, retVal);
   }
   else{
#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

      FblMemStorePreamble();
#endif

#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING_SINGLE_JOB )

      activeJob = FblMemGetPendingInputJob();
#endif

      {
#if defined( FBL_ENABLE_DATA_PROCESSING )    || \
    defined( FBL_MEM_ENABLE_STREAM_OUTPUT )  || \
    defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
         if(kFblMemProgState_Error != fblMemProgState)
         {
#if defined( FBL_ENABLE_DATA_PROCESSING )

            if(kFblOk == __ApplFblMemIsDataProcessingRequired(gSegInfo.input.dataFormat))
            {
               gProcFinalizeJob.completion = kFblMemOperationMode_Finalize;

               (void)FblMemQueueDefaultPrioInsert(gProcessingQueue, &gProcFinalizeJob, gSegInfo.ownIndex);
            }
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

            if(kFblOk == __ApplFblMemIsStreamOutputRequired(gSegInfo.input.dataFormat))
            {
               gStreamFinalizeJob.completion = kFblMemOperationMode_Finalize;

               (void)FblMemQueueDefaultPrioInsert(gProcessingQueue, &gStreamFinalizeJob, gSegInfo.ownIndex);
            }

            else
#endif
            {
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )
#if defined( FBL_MEM_ENABLE_PROC_QUEUE )

               (void)FblMemQueueDefaultPrioInsert(gProcessingQueue, &gWriteFinalizeJob, gSegInfo.ownIndex);
#else

               activeJob->type = kFblMemJobType_WriteFinalize;
#endif
#endif
            }

#if defined( FBL_MEM_ENABLE_PROC_QUEUE )
            if(!FblMemQueueIsEmpty(gProcessingQueue))
#endif
            {
               fblMemProgState = kFblMemProgState_Pending;
            }
         }
#endif
      }

#if defined( FBL_MEM_ENABLE_PROC_QUEUE ) || \
    defined( FBL_MEM_ENABLE_REMAINDER_HANDLING )

      FblMemFlushQueueByPrio(kFblMemJobPrio_Write);

      if(kFblMemProgState_Error == fblMemProgState)
      {
         retVal = gErrorStatus;
      }
      else
#endif
      {
#if defined( FBL_MEM_ENABLE_REMAINDER_HANDLING_SINGLE_JOB )

         activeJob->type = kFblMemJobType_InputWrite;
#endif

#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )

         if(0u != gSegInfo.inputLength)
#else

         if(0u != gSegInfo.writeLength)
#endif
         {
            FBL_MEM_SET_STATUS(SegmentEndInsufficientData, retVal);
         }
#if defined( __ApplFblMemPostSegmentEnd )
         else
         {
            if(kFblOk != __ApplFblMemPostSegmentEnd())
            {
               FBL_MEM_SET_STATUS(SegmentEndPost, retVal);
            }
         }
#endif

#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )
         *writeLength = gSegInfo.writtenLength;
#else
         *writeLength = gSegInfo.input.targetLength - gSegInfo.writeLength;
#endif

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )
         FblMemConcludeProgress();
#endif
      }

#if defined( FBL_MEM_ENABLE_SEGMENT_HANDLING )

      if(kFblMemStatus_Ok == retVal)
      {
         activeSegment = &(gBlockInfo.segmentList->segmentInfo[gBlockInfo.segmentList->nrOfSegments]);
         activeSegment->targetAddress        = gSegInfo.input.targetAddress;
         activeSegment->transferredAddress   = gSegInfo.input.logicalAddress;
         activeSegment->length               = *writeLength;
         gBlockInfo.segmentList->nrOfSegments++;
      }
#endif

#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER ) || \
    defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )

      activeJob         = FblMemGetPendingInputJob();
      activeJob->offset = FBL_MEM_PREAMBLE_OFFSET(FBL_MEM_PREAMBLE_LENGTH);
#endif

#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

      FblMemRestorePreamble();
#endif
   }

   if(kFblMemStatus_Ok == retVal){
      FblMemSetAllowed(FBL_MEM_ALLOWED_SEGMENT_START | FBL_MEM_ALLOWED_BLOCK_END);
   }

   return retVal;
}

tFblMemStatus FblMemDataIndication( tFblMemConstRamData buffer, tFblLength offset, tFblLength length ){
   tFblMemStatus retVal;
#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER ) || \
    defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )
   V_MEMRAM1 tFblMemJob V_MEMRAM2 V_MEMRAM3 * activeJob;
#endif
#if defined( FBL_MEM_ENABLE_INPUT_LENGTH )
   tFblLength inputLength;

   inputLength = 0u;
#endif

   retVal = kFblMemStatus_Ok;

   if(kFblOk != FblMemCheckAllowed(FBL_MEM_ALLOWED_DATA_IND, FBL_MEM_ALLOWED_DATA_IND | FBL_MEM_ALLOWED_SEGMENT_END)){
      FBL_MEM_SET_STATUS(DataIndSequence, retVal);
   }
   else{
#if defined( FBL_ENABLE_SYSTEM_CHECK ) || \
    defined( FBL_MEM_ENABLE_INPUT_LENGTH )
#if defined( FBL_ENABLE_PROCESSED_DATA_LENGTH )

      {
#else
#if defined( FBL_ENABLE_DATA_PROCESSING ) || \
      defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
      {
#if defined( FBL_ENABLE_DATA_PROCESSING )
         if(kFblOk == __ApplFblMemIsDataProcessingRequired(gSegInfo.input.dataFormat))
         {
         }
         else
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
         if(kFblOk == __ApplFblMemIsStreamOutputRequired(gSegInfo.input.dataFormat))
         {
         }
         else
#endif
#else
      {
#endif
#endif
         {
#if defined( FBL_MEM_ENABLE_INPUT_LENGTH )

            inputLength = length;

            if(gSegInfo.inputLength < length)
#else
            if(gSegInfo.writeLength < length)
#endif
            {
               FBL_MEM_SET_STATUS(DataIndOverflow, retVal);
            }
         }
      }
#endif
   }

   if(kFblMemStatus_Ok == retVal){
#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

      FblMemStorePreamble();
#endif

      retVal = FblMemQueueBuffer(buffer, offset, length);
      if(kFblMemStatus_Ok == retVal)
      {
#if defined( FBL_MEM_ENABLE_INPUT_LENGTH )

         gSegInfo.inputLength -= inputLength;
#endif

#if defined( FBL_MEM_ENABLE_INPUT_DATA_FLUSH )
         {
            FblMemFlushQueueByPrio(kFblMemJobPrio_Write);
         }

         if(kFblMemProgState_Error == fblMemProgState)
         {
            retVal = gErrorStatus;
         }
         else
#endif
         {
#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER ) || \
    defined( FBL_MEM_ENABLE_SEGMENTED_INPUT_BUFFER )

            activeJob         = FblMemGetPendingInputJob();
            activeJob->offset = FBL_MEM_PREAMBLE_OFFSET(FBL_MEM_PREAMBLE_LENGTH);

#if defined( FBL_ENABLE_UNALIGNED_DATA_TRANSFER )

            if(kFblMemType_RAM == gSegInfo.input.type)
            {
            }
            else
#if defined( FBL_ENABLE_DATA_PROCESSING )
            if(kFblOk == __ApplFblMemIsDataProcessingRequired(gSegInfo.input.dataFormat))
            {
            }
            else
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
            if(kFblOk == __ApplFblMemIsStreamOutputRequired(gSegInfo.input.dataFormat))
            {
            }
            else
#endif
            {
               activeJob->offset += FblMemGetWriteRemainder(gSegInfo.inputAddress, length);

               gSegInfo.inputAddress += length;
            }
#endif
#endif
         }
      }

#if defined( FBL_MEM_ENABLE_PREAMBLE_HANDLING )

      FblMemRestorePreamble();
#endif
   }

   if(kFblMemStatus_Ok == retVal){
#if defined( FBL_MEM_ENABLE_INPUT_LENGTH )

      if(gSegInfo.inputLength == 0u)
      {
         FblMemSetAllowed(FBL_MEM_ALLOWED_SEGMENT_END);
      }
      else
#endif
      {
         FblMemSetAllowed(FBL_MEM_ALLOWED_DATA_IND | FBL_MEM_ALLOWED_SEGMENT_END);
      }
   }

   return retVal;
}

void FblMemTask(void){
}

void FblMemFlushInputData(void){
   FblMemFlushQueueByPrio(kFblMemJobPrio_Write);
}

#define FBLLIB_MEM_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"

void FblMemResumeIndication(void){
}

#define FBLLIB_MEM_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

tFblMemStatus FblMemEraseRegion( tFblAddress eraseAddress, tFblLength eraseLength ){
   tFblMemStatus  retVal;

#if defined( FBL_MEM_ENABLE_PROGRESS_INFO )

   gProgressState = kFblMemProgressState_Disabled;
#endif

   retVal = FblMemEraseRegionInternal(eraseAddress, eraseLength);

   return retVal;
}

tFblMemStatus FblMemProgramBuffer( tFblAddress programAddress
   ,  V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * programLength, tFblMemRamData programData ){
   tFblMemProgState activeProgState;
   tFblMemStatus retVal;

   {
      activeProgState = fblMemProgState;

      fblMemProgState   = kFblMemProgState_Pending;

      retVal = FblMemProgramBufferInternal(programAddress, programLength, programData, kFblMemProgState_Pending);

      fblMemProgState = activeProgState;
   }

   return retVal;
}

void FblMemSetInteger( vuintx count, vuint32 input, tFblMemRamData buffer ){
   while(count > 0u){
      count--;

      buffer[count] = (vuint8)(input & 0xFFu);

      input >>= 8u;
   }
}

vuint32 FblMemGetInteger( vuintx count, tFblMemConstRamData buffer ){
   vuint32 output;
   vuintx idx;

   output = 0u;
   idx    = 0u;

   while(count > 0u){
      output <<= 8u;

      output |= (vuint32)buffer[idx];

      idx++;
      count--;
   }

   return output;
}

