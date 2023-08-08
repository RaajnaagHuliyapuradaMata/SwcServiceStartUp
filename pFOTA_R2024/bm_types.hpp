

#ifndef BM_TYPES_H
#define BM_TYPES_H

#include "fbl_def.hpp"
#include "Fbl_Lbt.hpp"
#include "bm_hdr_types.hpp"
#include "FblBm_Cfg.hpp"

#include "bm_shared.hpp"

#define FBLBM_HEADER_MAGIC_VALUE          0x05ECB007u
#define FBLBM_HEADER_MAJOR_VERSION        0x0001u
#define FBLBM_HEADER_MINOR_VERSION        0x0000u
#define FBLBM_HEADER_END_MAGIC_VALUE      0xCEC41160u

#if defined( FBLBM_MAIN_ENABLE_FBLSTART_CHANNEL )
# define FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_ONLY     vuint8 channel
# define FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_FIRST    vuint8 channel,
# define FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE               channel
#else
# define FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_ONLY     void
# define FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_FIRST
# define FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE               0u
#endif

#define FblBmHeaderTable  ((V_MEMROM1_FAR tFblBmHeader V_MEMROM2_FAR V_MEMROM3 *)(FBLBM_HEADER_ADDRESS))
#define FblBmHeaderLocal  ((V_MEMROM1_FAR tFblBmHeader V_MEMROM2_FAR V_MEMROM3 *)(&FblBmHeader))

#if defined( FBL_ENABLE_FBL_START )
# if defined( FBLBM_MAIN_ENABLE_FBLSTART_CHANNEL )
#  if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )
#   define CallFblStart(channel, pParam, length)   (FblBmHeaderTable->pFblStartFct)(channel, pParam, length)
#  else
#   define CallFblStart(channel)                   (FblBmHeaderTable->pFblStartFct)(channel)
#  endif
# else
#  if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )
#   define CallFblStart(pParam, length)            (FblBmHeaderTable->pFblStartFct)(pParam, length)
#  else
#   define CallFblStart()                          (FblBmHeaderTable->pFblStartFct)()
#  endif
# endif
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )
# if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )
#  define CallApplStart(pParam, length)   (FblBmHeaderTable->pApplStartFct)(pParam, length)
# else
#  define CallApplStart()                 (FblBmHeaderTable->pApplStartFct)()
# endif
#endif

typedef struct{
   tBlockDescriptor logicalBlock;
   tFblBmHdrHeader  bmHeader;
}tFblBmBlockInfo;

typedef enum{
   FBLBM_ERROR_NO_ERROR = 0u,
   FBLBM_ERROR_HEADER_READ_FAILED,
   FBLBM_ERROR_HEADER_MAGIC_FAILED,
   FBLBM_ERROR_HEADER_VERSION_FAILED,
   FBLBM_ERROR_HEADER_LENGTH_FAILED,
   FBLBM_ERROR_VALIDITY_FAILED,
   FBLBM_ERROR_FBL_BMHEADER_INCORRECT,
   FBLBM_ERROR_FBL_VERIFICATION_FAILED,
   FBLBM_ERROR_KEY_NOT_AVAILABLE,
   FBLBM_ERROR_UPDATER_SEARCH_INIT_FAILED,
   FBLBM_ERROR_UPDATER_SEARCH_NEXT_FINISHED,
   FBLBM_ERROR_UPDATER_HEADER_ADDRESS,
   FBLBM_ERROR_UPDATER_HEADER_READ_ERROR,
   FBLBM_ERROR_UPDATER_HEADER_CONSISTENCY,
   FBLBM_ERROR_UPDATER_HEADER_TYPE,
   FBLBM_ERROR_UPDATER_BLOCK_VALIDITY,
   FBLBM_ERROR_UPDATER_HEADER_CMAC_READ,
   FBLBM_ERROR_UPDATER_HEADER_CMAC_VERIFY,
   FBLBM_ERROR_UPDATER_VERIFY,
   FBLBM_ERROR_LBT_POINTER_NULL,
   FBLBM_ERROR_LBT_TOO_LARGE,
   FBLBM_ERROR_LBT_SIZE,
   FBLBM_ERROR_LBT_GET_MAC,
   FBLBM_ERROR_LBT_GET_FBL_MAC,
   FBLBM_ERROR_REPROG_LBT_DESCR,
   FBLBM_ERROR_REPROG_LBT_INVALID,
   FBLBM_ERROR_REPROG_LBT_BMHEADER_INCORRECT,
   FBLBM_ERROR_REPROG_LBT_VERIFY_HEADER,
   FBLBM_ERROR_REPROG_LBT_VERIFY_AREAS,
   FBLBM_ERROR_REPROG_LBT_MAGIC_FLAG,
   FBLBM_ERROR_REPROG_LBT_BLOCK_COUNT,
   FBLBM_ERROR_TARGET_LIST_INIT,
   FBLBM_ERROR_TARGET_INVALID,
   FBLBM_ERROR_TARGET_NO_VALID_HEADER,
   FBLBM_ERROR_TARGET_VERIFICATION_FAILED,
   FBLBM_ERROR_TARGET_INVALID_ADDRESS,
   FBLBM_ERROR_TARGET_DEP_MANDATORY_MISSING,
   FBLBM_ERROR_TARGET_DEP_NO_VALID_HEADER,
   FBLBM_ERROR_TARGET_DEP_VERIFY_FAILED,
   FBLBM_ERROR_END_OF_MAIN_REACHED,
   FBLBM_ERROR_AP_CHECK_MAC_READ_FAIL,
   FBLBM_ERROR_AP_CHECK_MAC_BUF_LENGTH,
   FBLBM_ERROR_AP_CHECK_MAC_READ_FAIL_LENGTH
}tFblBmError;

typedef enum{
   FBLBM_KEY_IS_NOT_AVAILABLE,
   FBLBM_KEY_IS_AVAILABLE
}tFblBmKeyEmptyResult;

typedef enum{
   FBLBM_MAC_IS_NOT_AVAILABLE,
   FBLBM_MAC_IS_AVAILABLE
}tFblBmMacEmptyResult;

# if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )

typedef FBL_CALL_TYPE void (*tFblStrtFct)(void* pParam, vuint8 length);
# else

typedef FBL_CALL_TYPE void (*tFblStrtFct)(void);
# endif

# if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )

typedef FBL_CALL_TYPE void (*tApplStrtFct)(void* pParam, vuint8 length);
# else

typedef FBL_CALL_TYPE void (*tApplStrtFct)(void);
# endif

typedef struct{
   vuint32 magic;
   vuint16 majorVersion;
   vuint16 minorVersion;
   tFblAddress fblHeaderAddress;
   tFblStrtFct pFblStartFct;
   tApplStrtFct pApplStartFct;
   vuint32 checksum;
   vuint32 end_magic;
}tFblBmHeader;

#endif

