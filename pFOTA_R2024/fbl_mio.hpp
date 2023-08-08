

#ifndef FBL_MIO_H
#define FBL_MIO_H

#define FBLMIO_VERSION              0x0301u
#define FBLMIO_RELEASE_VERSION      0x01u

#define kMioDeviceIdle              0xFFu

#define MemDriver_InitBegin(a)              { \
                                              memDrvDeviceActive   = (vuint8)(a);        \
                                              memDrvFunctionActive = kMioFunctionInit;   \
                                            }
#define MemDriver_InitEnd(a)                { \
                                              memDrvDeviceActive   = kMioDeviceIdle;     \
                                              memDrvFunctionActive = kMioFunctionNone;   \
                                            }
#define MemDriver_REraseBegin(a)            { \
                                              memDrvDeviceActive   = (vuint8)(a);        \
                                              memDrvFunctionActive = kMioFunctionErase;  \
                                            }
#define MemDriver_REraseEnd(a)              { \
                                              memDrvDeviceActive   = kMioDeviceIdle;     \
                                              memDrvFunctionActive = kMioFunctionNone;   \
                                            }
#define MemDriver_RWriteBegin(a)            { \
                                              memDrvDeviceActive   = (vuint8)(a);        \
                                              memDrvFunctionActive = kMioFunctionWrite;  \
                                            }
#define MemDriver_RWriteEnd(a)              { \
                                              memDrvDeviceActive   = kMioDeviceIdle;     \
                                              memDrvFunctionActive = kMioFunctionNone;   \
                                            }
#define MemDriver_VerifyBegin(a)            { \
                                              memDrvDeviceActive   = (vuint8)(a);        \
                                              memDrvFunctionActive = kMioFunctionVerify; \
                                            }
#define MemDriver_VerifyEnd(a)              { \
                                              memDrvDeviceActive   = kMioDeviceIdle;     \
                                              memDrvFunctionActive = kMioFunctionNone;   \
                                            }
#define MemDriver_DeinitBegin(a)            { \
                                             memDrvDeviceActive   = (vuint8)(a);        \
                                             memDrvFunctionActive = kMioFunctionDeinit;  \
                                            }
#define MemDriver_DeinitEnd(a)              { \
                                             memDrvDeviceActive   = kMioDeviceIdle;      \
                                             memDrvFunctionActive = kMioFunctionNone;    \
                                            }

#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES )

# define MemDriver_RReadSync                       (*memDrvLst[FlashBlock[memSegment].device].read)
# define MemDriver_SegmentSize                     (memDrvLst[FlashBlock[memSegment].device].segmentSize)
# if defined( FBL_MEMDRV_SEGMENT_SIZE )
#  if( FLASH_SEGMENT_SIZE > FBL_MEMDRV_SEGMENT_SIZE )
#   define FBL_MAX_SEGMENT_SIZE_MIO FLASH_SEGMENT_SIZE
#  else
#   define FBL_MAX_SEGMENT_SIZE_MIO FBL_MEMDRV_SEGMENT_SIZE
#  endif
# else
#  define FBL_MAX_SEGMENT_SIZE_MIO FLASH_SEGMENT_SIZE
# endif

#else

# define kMioDeviceInternalFlash     0u

# define MemDriver_RReadSync(a, b, c)              FlashDriver_RReadSync((a), (b), (c))
# define MemDriver_SegmentSize                     FLASH_SEGMENT_SIZE
# define FBL_MAX_SEGMENT_SIZE_MIO                  FLASH_SEGMENT_SIZE

#endif

#if defined( FBL_MAX_SEGMENT_SIZE )
# if( FBL_MAX_SEGMENT_SIZE_MIO > FBL_MAX_SEGMENT_SIZE )
#  error "Define FBL_MAX_SEGMENT_SIZE from external only with values larger than determined through FblMio."
# endif
#else
# define FBL_MAX_SEGMENT_SIZE FBL_MAX_SEGMENT_SIZE_MIO
#endif

#define kMioFunctionNone            0u
#define kMioFunctionInit            1u
#define kMioFunctionDeinit          2u
#define kMioFunctionWrite           3u
#define kMioFunctionErase           4u
#define kMioFunctionVerify          5u

#define FBLMIO_START_SEC_CODE
#include "MemMap.hpp"

void MemDriver_InitPowerOn( void );

vsint16 FblMemSegmentNrGet( tFblAddress address );
tFblResult FblMemGetDeviceByAddr(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * device);
tFblResult FblMemGetDeviceByRange(tFblAddress address, tFblLength length, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * device);
tFblLength FblReadProm(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * buffer, tFblLength length);
IO_ErrorType FblReadPromExt(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * buffer, tFblLength length,
   V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * actualReadCount);

IO_ErrorType V_API_NEAR MemDriver_InitSync( void * address );
IO_ErrorType V_API_NEAR MemDriver_DeinitSync( void * address );
IO_ErrorType V_API_NEAR MemDriver_RWriteSync( IO_MemPtrType buf, IO_SizeType len, IO_PositionType addr );
IO_ErrorType V_API_NEAR MemDriver_REraseSync( IO_SizeType len, IO_PositionType addr );

#define FBLMIO_STOP_SEC_CODE
#include "MemMap.hpp"

#define FBLMIO_START_SEC_VAR
#include "MemMap.hpp"

V_MEMRAM0 extern V_MEMRAM1      vuint8              V_MEMRAM2      memDrvDeviceActive;
V_MEMRAM0 extern V_MEMRAM1      vuint8              V_MEMRAM2      memDrvFunctionActive;

V_MEMRAM0 extern V_MEMRAM1      vsint16             V_MEMRAM2      memSegment;

#define FBLMIO_STOP_SEC_VAR
#include "MemMap.hpp"

#endif

