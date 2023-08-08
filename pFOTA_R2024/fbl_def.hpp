

#ifndef __FBL_DEF_H__
#define __FBL_DEF_H__

#include "v_cfg.hpp"

#if defined( VGEN_GENY ) && !defined( VGEN_ENABLE_CANFBL )

# if defined( MAGIC_NUMBER )
#  undef MAGIC_NUMBER
# endif
#endif

#if defined( V_GEN_GENERATOR_MSR )
# include "Fbl_Cfg.hpp"
#else
# include "fbl_cfg.hpp"
#endif
#if defined( VGEN_GENY ) && !defined( VGEN_ENABLE_CANFBL )

# if defined( MAGIC_NUMBER )
#  undef MAGIC_NUMBER
# endif
#endif

#include "v_def.hpp"

#if defined( FBL_ENABLE_SECMOD_VECTOR )
# include "CfgSwcServiceSecM.hpp"
#endif

# include "fbl_assert.hpp"

#define FBLDEF_VERSION          0x0405u
#define FBLDEF_RELEASE_VERSION  0x00u

#define FBL_DEF_ENABLE_NON_KB_MAIN

#ifndef NULL
# define NULL ((void *)0)
#endif

# if !defined( FBL_ENABLE_WRAPPER_NV ) && \
     !defined( FBL_DISABLE_WRAPPER_NV )
#  define FBL_ENABLE_WRAPPER_NV
# endif

# if !defined( FBL_ENABLE_SECMOD_VECTOR ) && \
     !defined( FBL_DISABLE_SECMOD_VECTOR )
#  define FBL_ENABLE_SECMOD_VECTOR
# endif

#define kFblOk                0x00u
#define kFblFailed            0x01u

#define kFblVoltageTooLow     0x01u
#define kFblVoltageTooHigh    0x02u

#define kProgRequest             0x00u
#define kProgRequestXcp          0x01u
#define kNoProgRequest           0xFFu

#define kCheckStayInBootRequest  0x10u
#define kInitKeysRequest         0x11u
#define kInitMacsRequest         0x12u

# define kApplValid            1
# define kApplInvalid          0

# define kFlashErased          1
# define kFlashNotErased       0

#if !defined( FBL_REPEAT_CALL_CYCLE )

# define FBL_REPEAT_CALL_CYCLE 1
#endif

#if defined( FBL_ENABLE_BANKING )
#else
# define FBL_CALL_TYPE
#endif

#ifndef V_CALLBACK_NEAR
# define V_CALLBACK_NEAR
#endif
#ifndef V_API_NEAR
# define V_API_NEAR
#endif

# if defined( C_CPUTYPE_BIGENDIAN )
#  if defined( C_CPUTYPE_32BIT )
#   define FblBytesToShort(hi,lo)            (((vuint16)(hi) << 8) | ((vuint16)(lo) ))
#  else
#   define FblBytesToShort(hi,lo)            (vuint16)*(V_MEMRAM1_FAR vuint16 V_MEMRAM2_FAR *)(&(hi))
#  endif
# endif
# if defined( C_CPUTYPE_LITTLEENDIAN )
#  define FblBytesToShort(hi,lo)              (((vuint16)(hi) << 8) | ((vuint16)(lo) ))
# endif

# if defined( C_CPUTYPE_BIGENDIAN )
#  if defined( C_CPUTYPE_32BIT )
#   define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt,loWrd_loByt)  \
                                         (((vuint32)(hiWrd_hiByt) << 24) |  \
                                          ((vuint32)(hiWrd_loByt) << 16) |  \
                                          ((vuint32)(loWrd_hiByt) <<  8) |  \
                                          ((vuint32)(loWrd_loByt)      )  )
#  else
#   define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt, loWrd_loByt)  \
            (vuint32)*(V_MEMRAM1_FAR vuint32 V_MEMRAM2_FAR *)(&(hiWrd_hiByt))
#  endif
# endif
# if defined( C_CPUTYPE_LITTLEENDIAN )
#  define FblBytesToLong(hiWrd_hiByt,hiWrd_loByt,loWrd_hiByt,loWrd_loByt)  \
                                        (((vuint32)(hiWrd_hiByt) << 24) |  \
                                         ((vuint32)(hiWrd_loByt) << 16) |  \
                                         ((vuint32)(loWrd_hiByt) <<  8) |  \
                                         ((vuint32)(loWrd_loByt)      )  )
# endif

#define FBL_BIT0   0x01u
#define FBL_BIT1   0x02u
#define FBL_BIT2   0x04u
#define FBL_BIT3   0x08u
#define FBL_BIT4   0x10u
#define FBL_BIT5   0x20u
#define FBL_BIT6   0x40u
#define FBL_BIT7   0x80u

#define RESET_RESPONSE_NOT_REQUIRED             0x00u
#define RESET_RESPONSE_SDS_REQUIRED             0x01u
#define RESET_RESPONSE_ECURESET_REQUIRED        0x02u
#define RESET_RESPONSE_KEYOFFON_REQUIRED        0x03u

#define FblInvertBits(x,type)    ((type)~((type)(x)))
#define FblInvert8Bit(x)         ((vuint8) ((x) ^ ((vuint8)0xFFu)))
#define FblInvert16Bit(x)        ((vuint16)((x) ^ ((vuint16)0xFFFFu)))
#define FblInvert32Bit(x)        ((vuint32)((x) ^ ((vuint32)0xFFFFFFFFul)))

# define kFblDiagTimeP2             FBL_DIAG_TIME_P2MAX
# define kFblDiagTimeP2Star         FBL_DIAG_TIME_P3MAX

#define kEepFblReprogram       0xB5u

#define kEepWriteData           1u
#define kEepReadData            2u

#define kFblErrTypeAppl         0x10u
#define kFblErrTypeFlash        0x20u
#define kFblErrTypeEeprom       0x30u
#define kFblErrTypeSec          0x40u
#define kFblErrTypeVectorTPMC   0x50u

#if defined( C_CPUTYPE_8BIT )
typedef vuint8 tFblStateBitmap;
# define FBL_STATE_BITS             8
# define kFblStateMaskNone          0x00u
# define kFblStateMaskAll           0xFFu
# define FblInvertStates(x)         FblInvert8Bit(x)
#elif defined( C_CPUTYPE_16BIT )
typedef vuint16 tFblStateBitmap;
# define FBL_STATE_BITS             16u
# define kFblStateMaskNone          0x0000u
# define kFblStateMaskAll           0xFFFFu
# define FblInvertStates(x)         FblInvert16Bit(x)
#elif defined( C_CPUTYPE_32BIT )
typedef vuint32 tFblStateBitmap;
# define FBL_STATE_BITS             32u
# define kFblStateMaskNone          0x00000000ul
# define kFblStateMaskAll           0xFFFFFFFFul
# define FblInvertStates(x)         FblInvert32Bit(x)
#else
# error "Bit count of CPU not supported."
#endif

#define FBL_STATE_MASK(bit)               ((tFblStateBitmap)(1ul << ((bit) % FBL_STATE_BITS)))
#define FBL_STATE_MULTIMASK(min, max)     ((((kFblStateMaskAll) >> ((min) % FBL_STATE_BITS)) << ((min) % FBL_STATE_BITS)) ^ (((kFblStateMaskAll) >> (((max) + 1) % FBL_STATE_BITS)) << (((max) + 1) % FBL_STATE_BITS)))
#define FBL_STATE_MASKLONG(bit)           (1ul << (bit))
#define FBL_STATE_MULTIMASKLONG(min, max) ((((~0ul) >> (min)) << (min)) ^ (((max) < (STATE_BITS - 1u)) ? (((~0ul) >> ((max) + 1)) << ((max) + 1)) : 0ul))
#define FBL_STATE_INDEX(bit)              ((bit) / FBL_STATE_BITS)
#define FBL_STATE_SET(arr, bit)           ((arr)[FBL_STATE_INDEX(bit)] |= FBL_STATE_MASK(bit))
#define FBL_STATE_CLR(arr, bit)           ((arr)[FBL_STATE_INDEX(bit)] &= FblInvertStates(FBL_STATE_MASK(bit)))
#define FBL_STATE_MULTICLR(arr, min, max) ((arr)[FBL_STATE_INDEX(min)] &= FblInvertStates(FBL_STATE_MULTIMASK((min), (max))))
#define FBL_STATE_TEST(arr, bit)          (((arr)[FBL_STATE_INDEX(bit)] & FBL_STATE_MASK(bit)) == FBL_STATE_MASK(bit))

typedef vuint8  tFblErrorType;
typedef vuint16 tFblErrorCode;

typedef vuint8 tFblResult;
typedef vuint8 tFblProgStatus;
typedef vuint8 tApplStatus;
typedef vuint8 tMagicFlag;
typedef vuint8 tFlashStatus;

#if defined( C_CPUTYPE_8BIT ) && !defined( FBL_PROCESSOR_BANKED )
typedef vuint16 FBL_ADDR_TYPE;
typedef vuint16 FBL_MEMSIZE_TYPE;
# define MEMSIZE_OK
#else
typedef vuint32 FBL_ADDR_TYPE;
typedef vuint32 FBL_MEMSIZE_TYPE;
# define MEMSIZE_OK
#endif
#if defined( MEMSIZE_OK )
#else
# error "Error in FBL_DEF.H: C_CPUTYPE_ not defined."
#endif

typedef vuint8 FBL_MEMID_TYPE;

typedef FBL_ADDR_TYPE       tFblAddress;
typedef FBL_MEMSIZE_TYPE    tFblLength;

typedef FBL_ADDR_TYPE       tMtabAddress;
typedef FBL_MEMSIZE_TYPE    tMtabLength;
typedef FBL_MEMID_TYPE      tMtabMemId;

typedef vuint16 tChecksum;

#if defined( FBL_ENABLE_BANKING )
typedef FBL_CALL_TYPE void (*FBL_CALL_TYPE tExportFct)(void);
#else
typedef MEMORY_FAR void (*tExportFct)(void);
#endif

typedef FBL_CALL_TYPE vuint8 (* tFblRealtimeFct)(void);

typedef FBL_CALL_TYPE tFblLength (* tReadMemoryFct)(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * buffer, tFblLength length);

#if defined( FBL_ENABLE_DATA_PROCESSING )
typedef struct tagProcParam
{
   V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * dataBuffer;
   vuint16        dataLength;
   V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * dataOutBuffer;
   vuint16        dataOutLength;
   vuint16        dataOutMaxLength;
   vuint8         (* wdTriggerFct)(void);
   vuint8         mode;
}tProcParam;
#endif

#endif

