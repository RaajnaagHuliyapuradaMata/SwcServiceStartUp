

#ifndef BM_SHARED_H
#define BM_SHARED_H

#if !defined( FBLBM_MAIN_ENABLE_FBL_START ) && \
    !defined( FBLBM_MAIN_DISABLE_FBL_START )
#if defined( FBL_ENABLE_FBL_START )
#define FBLBM_MAIN_ENABLE_FBL_START
#endif
#endif

#if !defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT ) && \
    !defined( FBLBM_MAIN_DISABLE_STAY_IN_BOOT )
#if defined( FBL_ENABLE_STAY_IN_BOOT )
#define FBLBM_MAIN_ENABLE_STAY_IN_BOOT
#endif
#endif

#if !defined( FBLBM_MAIN_ENABLE_MAGICFLAG ) && \
    !defined( FBLBM_MAIN_DISABLE_MAGICFLAG )
#if defined( FBLBM_MAIN_ENABLE_FBL_START )        || \
     defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )     || \
     (defined( FBLBM_ENABLE_SECURE_BOOT )       && \
         (defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_KEY ) || \
          defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )) \
     )

#define FBLBM_MAIN_ENABLE_MAGICFLAG
#endif
#endif

#if defined( FBLBM_MAIN_ENABLE_MAGICFLAG )
#define kFblBmNoOfMagicBytes          8u
#define kFblBmClearMagicByte          0x00u
#define FblBmClrMagicFlag()                    \
{                                               \
   fblBmMagicFlag[0u] = kFblBmClearMagicByte;   \
   fblBmMagicFlag[1u] = kFblBmClearMagicByte;   \
   fblBmMagicFlag[2u] = kFblBmClearMagicByte;   \
   fblBmMagicFlag[3u] = kFblBmClearMagicByte;   \
   fblBmMagicFlag[4u] = kFblBmClearMagicByte;   \
   fblBmMagicFlag[5u] = kFblBmClearMagicByte;   \
   fblBmMagicFlag[6u] = kFblBmClearMagicByte;   \
   fblBmMagicFlag[7u] = kFblBmClearMagicByte;   \
}

#define FblBmSetMagicFlag(infix)                        \
{                                                        \
   fblBmMagicFlag[0u] = kFblBm## infix## MagicByte0;   \
   fblBmMagicFlag[1u] = kFblBm## infix## MagicByte1;   \
   fblBmMagicFlag[2u] = kFblBm## infix## MagicByte2;   \
   fblBmMagicFlag[3u] = kFblBm## infix## MagicByte3;   \
   fblBmMagicFlag[4u] = kFblBm## infix## MagicByte4;   \
   fblBmMagicFlag[5u] = kFblBm## infix## MagicByte5;   \
   fblBmMagicFlag[6u] = kFblBm## infix## MagicByte6;   \
   fblBmMagicFlag[7u] = kFblBm## infix## MagicByte7;   \
}

#define FblBmChkMagicFlag(infix)                              \
   ((    (fblBmMagicFlag[0u] == kFblBm## infix## MagicByte0) \
      && (fblBmMagicFlag[1u] == kFblBm## infix## MagicByte1) \
      && (fblBmMagicFlag[2u] == kFblBm## infix## MagicByte2) \
      && (fblBmMagicFlag[3u] == kFblBm## infix## MagicByte3) \
      && (fblBmMagicFlag[4u] == kFblBm## infix## MagicByte4) \
      && (fblBmMagicFlag[5u] == kFblBm## infix## MagicByte5) \
      && (fblBmMagicFlag[6u] == kFblBm## infix## MagicByte6) \
      && (fblBmMagicFlag[7u] == kFblBm## infix## MagicByte7)) ? 1u : 0u)

#if defined( FBLBM_MAIN_ENABLE_FBL_START )

#define kFblBmFblStartMagicByte0        0x50u
#define kFblBmFblStartMagicByte1        0x72u
#define kFblBmFblStartMagicByte2        0x6Fu
#define kFblBmFblStartMagicByte3        0x67u
#define kFblBmFblStartMagicByte4        0x53u
#define kFblBmFblStartMagicByte5        0x69u
#define kFblBmFblStartMagicByte6        0x67u
#define kFblBmFblStartMagicByte7        0x6Eu
#define FblBmSetFblStartMagicFlag()     FblBmSetMagicFlag(FblStart)
#define FblBmChkFblStartMagicFlag()     FblBmChkMagicFlag(FblStart)
#endif

#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )

#define kFblBmApplStartMagicByte0       0x41u
#define kFblBmApplStartMagicByte1       0x70u
#define kFblBmApplStartMagicByte2       0x70u
#define kFblBmApplStartMagicByte3       0x6Cu
#define kFblBmApplStartMagicByte4       0x53u
#define kFblBmApplStartMagicByte5       0x69u
#define kFblBmApplStartMagicByte6       0x67u
#define kFblBmApplStartMagicByte7       0x6Eu
#define FblBmSetApplStartMagicFlag()    FblBmSetMagicFlag(ApplStart)
#define FblBmChkApplStartMagicFlag()    FblBmChkMagicFlag(ApplStart)

#define kFblBmStayInBootMagicByte0      0x53u
#define kFblBmStayInBootMagicByte1      0x74u
#define kFblBmStayInBootMagicByte2      0x61u
#define kFblBmStayInBootMagicByte3      0x79u
#define kFblBmStayInBootMagicByte4      0x42u
#define kFblBmStayInBootMagicByte5      0x6Fu
#define kFblBmStayInBootMagicByte6      0x6Fu
#define kFblBmStayInBootMagicByte7      0x74u
#define FblBmSetStayInBootMagicFlag()   FblBmSetMagicFlag(StayInBoot)
#define FblBmChkStayInBootMagicFlag()   FblBmChkMagicFlag(StayInBoot)
#endif

#if defined( FBLBM_ENABLE_SECURE_BOOT )
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_KEY )

#define kFblBmInitKeysMagicByte0       0x49u
#define kFblBmInitKeysMagicByte1       0x6Eu
#define kFblBmInitKeysMagicByte2       0x69u
#define kFblBmInitKeysMagicByte3       0x74u
#define kFblBmInitKeysMagicByte4       0x4Bu
#define kFblBmInitKeysMagicByte5       0x65u
#define kFblBmInitKeysMagicByte6       0x79u
#define kFblBmInitKeysMagicByte7       0x73u
#define FblBmSetInitKeysMagicFlag()    FblBmSetMagicFlag(InitKeys)
#define FblBmChkInitKeysMagicFlag()    FblBmChkMagicFlag(InitKeys)
#endif

#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_KEY ) || \
       defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )

#define kFblBmInitCmacMagicByte0      0x49u
#define kFblBmInitCmacMagicByte1      0x6Eu
#define kFblBmInitCmacMagicByte2      0x69u
#define kFblBmInitCmacMagicByte3      0x74u
#define kFblBmInitCmacMagicByte4      0x43u
#define kFblBmInitCmacMagicByte5      0x6Du
#define kFblBmInitCmacMagicByte6      0x61u
#define kFblBmInitCmacMagicByte7      0x63u
#define FblBmSetInitCmacMagicFlag()     FblBmSetMagicFlag(InitCmac)
#define FblBmChkInitCmacMagicFlag()     FblBmChkMagicFlag(InitCmac)
#endif
#endif
#endif

#if defined( FBLBM_MAIN_ENABLE_MAGICFLAG )
#define FBLBM_MAIN_MAGICFLAG_START_SEC_VAR_NOINIT
#include "MemMap.hpp"
V_MEMRAM0 extern volatile V_MEMRAM1 vuint8                     V_MEMRAM2 fblBmMagicFlag[kFblBmNoOfMagicBytes];
#if defined( FBLBM_MAIN_ENABLE_FBLSTART_CHANNEL )
V_MEMRAM0 extern volatile V_MEMRAM1 vuint8                     V_MEMRAM2 fblBmFblStartChannel;
#endif
#if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )
V_MEMRAM0 extern volatile V_MEMRAM1 tFblBmFblStartParameter    V_MEMRAM2 fblBmFblStartParameter;
#endif
#if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )
V_MEMRAM0 extern volatile V_MEMRAM1 tFblBmApplStartParameter   V_MEMRAM2 fblBmApplStartParameter;
#endif
#define FBLBM_MAIN_MAGICFLAG_STOP_SEC_VAR_NOINIT
#include "MemMap.hpp"
#endif

#endif

