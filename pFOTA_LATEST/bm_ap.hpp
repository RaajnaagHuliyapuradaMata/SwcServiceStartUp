

#ifndef BM_AP_H
#define BM_AP_H

#define FBLBM_AP_VERSION               0x0301u
#define FBLBM_AP_RELEASE_VERSION       0x01u

#define FBLBM_AP_API_VERSION_MAJOR     0x03u

#define FBLBM_AP_API_VERSION_MINOR     0x00u

#define FBLBM_AP_API_VERSION_RELEASE   0x00u

#include "FblBm_Cfg.hpp"
#include "bm_types.hpp"
#include "bm_hdr.hpp"

#include "fbl_inc.hpp"

#if defined( FBLBM_ENABLE_STANDALONE_MODE )
#define FblRealTimeSupport()     FblLookForWatchdog()
#endif

void ApplFblBmPowerOnPre(void);
void ApplFblBmPowerOnPost(void);
void ApplFblBmInitPre(void);
void ApplFblBmInitPost(void);

#if defined( FBLBM_AP_CALLOUT_RESET )
void ApplFblBmReset(void);
#endif

#if defined( FBLBM_AP_CALLOUT_CHECK_TARGET_VALIDITY )
tFblResult ApplFblBmCheckTargetValidity(tFblBmHdrTargetHandle targetHandle);
#endif
#if defined( FBLBM_AP_CALLOUT_IS_VALIDBLOCK )
tFblResult ApplFblBmIsValidBlock(tFblBmHdrTargetHandle targetHandle
   ,  const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * pLogicalBlock);
#endif
#if defined( FBLBM_AP_CALLOUT_START_SOFTWARE )
void ApplFblBmStartSoftware(const V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 V_MEMRAM3 * bmHeader);
#endif

#if defined( FBLBM_ENABLE_SECURE_BOOT )
#if defined( FBLBM_AP_CALLOUT_GET_KEYEMPTY )
tFblBmKeyEmptyResult ApplFblBmGetKeyEmpty(void);
#endif
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
#if defined( FBLBM_AP_CALLOUT_GET_FBL_CMACERASED )
tFblBmMacEmptyResult ApplFblBmGetFblCmacErased( const tFblBmBlockInfo * fblBlockInfo );
#endif
#endif
#endif

#if !defined( FBL_ENABLE_FBL_START )
#if defined( FBLBM_AP_CALLOUT_CHECKREPROGFLAG )
tFblResult ApplFblBmCheckReprogFlag(void);
#endif
#endif

#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
#if defined( FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_INIT )
tFblResult ApplFblBmSearchUpdaterHeaderInit(void);
#endif
#if defined( FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_HEADER_ADDRESS )
tFblResult ApplFblBmSearchUpdaterHeaderAddress(vuint32 * headerAddress);
#endif
#if defined( FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_NEXT )
tFblResult ApplFblBmSearchUpdaterHeaderNext(void);
#endif
#endif

#if defined( FBLBM_AP_CALLOUT_FATAL_ERROR )
void ApplFblBmFatalError(tFblBmError error);
#endif

#if defined( FBLBM_ENABLE_STANDALONE_MODE )
#if defined( FBL_ENABLE_ASSERTION )
void ApplFblFatalError( FBL_DECL_ASSERT_EXTENDED_INFO(vuint8 errorCode) );
#endif
#endif

#endif

