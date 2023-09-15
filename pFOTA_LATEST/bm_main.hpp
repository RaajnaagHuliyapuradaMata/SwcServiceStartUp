

#ifndef BM_MAIN_H
#define BM_MAIN_H

#define FBLBM_MAIN_VERSION             0x0304u
#define FBLBM_MAIN_RELEASE_VERSION     0x01u

#define FBLBM_API_VERSION_MAJOR        0x03u

#define FBLBM_API_VERSION_MINOR        0x00u

#define FBLBM_API_VERSION_RELEASE      0x00u

#include "bm_types.hpp"
#include "bm_ap.hpp"
#include "bm_hdr.hpp"

#define FBLBM_ARRAY_SIZE(arr)                            (sizeof(arr) / sizeof((arr)[0u]))

#define FBLBM_HOOK_NONE                                  (tFblBmFunc)0

#if defined( FBLBM_ENABLE_STANDALONE_MODE )

typedef V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *        tFblMemRamData;

typedef const V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 *  tFblMemConstRamData;

#define GetRcrRpInProgress()             ((vuint8)0x00u)
#endif

#if defined( FBL_CW_LOCKS_TASKS ) || \
    defined( FBLCW_LOCKS_TASKS )

#if !defined( FBL_CW_API_REFERENCE_VERSION_MAJOR )

#define FBL_CW_API_REFERENCE_VERSION_MAJOR     0x01u

#define FBL_CW_API_REFERENCE_VERSION_MINOR     0x00u

#define FBL_CW_API_REFERENCE_VERSION_RELEASE   0x00u
#endif
#if !defined( FBL_CW_CFG_PTR )
#define FBL_CW_CFG_PTR V_NULL
#endif
#else
#define FBL_CW_LOCKS_TASKS
#define FBLCW_LOCKS_TASKS
#define FblCwIsTimerTaskAllowed()        ((vuint8)0x00u)
#define FblCwIsStateTaskAllowed()        ((vuint8)0x00u)
#define FblCwRetransmitRP()
#define FblCwClrInit()
#define FblCwTimerTask()
#define FblCwStateTask()
#endif

#define FBLBM_HEADER_START_SEC_CONST
#include "MemMap.hpp"
V_MEMROM0 extern V_MEMROM1 tFblBmHeader V_MEMROM2 FblBmHeader;
#define FBLBM_HEADER_STOP_SEC_CONST
#include "MemMap.hpp"

#if defined( FBLBM_ENABLE_STANDALONE_MODE )
void FblMemSetInteger( vuintx count, vuint32 input, tFblMemRamData buffer );
vuint32 FblMemGetInteger( vuintx count, tFblMemConstRamData buffer );
#endif

#if defined( FBL_ENABLE_FBL_START )
#define FBLBM_MAIN_FBLSTART_START_SEC_CODE
#include "MemMap.hpp"
#if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )
void V_CALLBACK_NEAR FblStart( FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_FIRST
   V_MEMRAM1 void V_MEMRAM2 V_MEMRAM3 * pFblStartParam, vuint8 length );
#else
void V_CALLBACK_NEAR FblStart( FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_ONLY );
#endif
#define FBLBM_MAIN_FBLSTART_STOP_SEC_CODE
#include "MemMap.hpp"
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )
#define FBLBM_MAIN_APPLSTART_START_SEC_CODE
#include "MemMap.hpp"
#if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )
void ApplStart( V_MEMRAM1 void V_MEMRAM2 V_MEMRAM3 * pApplStartParam, vuint8 length )
#else
void ApplStart(void);
#endif
#define FBLBM_MAIN_APPLSTART_STOP_SEC_CODE
#include "MemMap.hpp"
#endif

#endif

