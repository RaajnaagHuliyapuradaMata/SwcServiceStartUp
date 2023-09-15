

#define BM_SHARED_SOURCE

#include "fbl_def.hpp"
#include "bm_shared.hpp"

#if defined( FBLBM_MAIN_ENABLE_MAGICFLAG )
#define FBLBM_MAIN_MAGICFLAG_START_SEC_VAR_NOINIT
#include "MemMap.hpp"

V_MEMRAM0 volatile V_MEMRAM1 vuint8                      V_MEMRAM2 fblBmMagicFlag[kFblBmNoOfMagicBytes];
#if defined( FBLBM_MAIN_ENABLE_FBLSTART_CHANNEL )
V_MEMRAM0 volatile V_MEMRAM1 vuint8                      V_MEMRAM2 fblBmFblStartChannel;
#endif
#if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )
V_MEMRAM0 volatile V_MEMRAM1 tFblBmStartParamter         V_MEMRAM2 fblBmFblStartParameter;
#endif
#if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )
V_MEMRAM0 volatile V_MEMRAM1 tFblBmApplStartParamter     V_MEMRAM2 fblBmApplStartParameter;
#endif
#define FBLBM_MAIN_MAGICFLAG_STOP_SEC_VAR_NOINIT
#include "MemMap.hpp"
#endif

