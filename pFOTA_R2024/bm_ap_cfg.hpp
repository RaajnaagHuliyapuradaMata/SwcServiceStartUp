

#ifndef BM_AP_CFG_H
#define BM_AP_CFG_H

#if !defined( FBLBM_CALLOUT_POWER_ON_PRE_HW)
# define FBLBM_CALLOUT_POWER_ON_PRE_HW()
#endif

#if !defined( FBLBM_CALLOUT_POWER_ON_PRE_OEM )
# define FBLBM_CALLOUT_POWER_ON_PRE_OEM()
#endif

#if !defined( FBLBM_CALLOUT_POWER_ON_PRE )
# define FBLBM_CALLOUT_POWER_ON_PRE                            ApplFblBmPowerOnPre
#endif

#if !defined( FBLBM_CALLOUT_POWER_ON_POST_HW )
# define FBLBM_CALLOUT_POWER_ON_POST_HW()
#endif

#if !defined( FBLBM_CALLOUT_POWER_ON_POST_OEM )
# define FBLBM_CALLOUT_POWER_ON_POST_OEM()
#endif

#if !defined( FBLBM_CALLOUT_POWER_ON_POST )
# define FBLBM_CALLOUT_POWER_ON_POST                           ApplFblBmPowerOnPost
#endif

#if !defined( FBLBM_CALLOUT_INIT_PRE_HW )
# define FBLBM_CALLOUT_INIT_PRE_HW()
#endif

#if !defined( FBLBM_CALLOUT_INIT_PRE_OEM )
# define FBLBM_CALLOUT_INIT_PRE_OEM()
#endif

#if !defined( FBLBM_CALLOUT_INIT_PRE )
# define FBLBM_CALLOUT_INIT_PRE                                ApplFblBmInitPre
#endif

#if !defined( FBLBM_CALLOUT_INIT_POST_HW )
# define FBLBM_CALLOUT_INIT_POST_HW()
#endif

#if !defined( FBLBM_CALLOUT_INIT_POST_OEM )
# define FBLBM_CALLOUT_INIT_POST_OEM()
#endif

#if !defined( FBLBM_CALLOUT_INIT_POST )
# define FBLBM_CALLOUT_INIT_POST                               ApplFblBmInitPost
#endif

#if !defined( FBLBM_CALLOUT_DEINIT_PRE_HW )
# define FBLBM_CALLOUT_DEINIT_PRE_HW()
#endif

#if !defined( FBLBM_CALLOUT_DEINIT_PRE_OEM )
# define FBLBM_CALLOUT_DEINIT_PRE_OEM()
#endif

#if !defined( FBLBM_CALLOUT_DEINIT_PRE )
# define FBLBM_CALLOUT_DEINIT_PRE()
#endif

#if !defined( FBLBM_CALLOUT_DEINIT_POST_HW )
# define FBLBM_CALLOUT_DEINIT_POST_HW()
#endif

#if !defined( FBLBM_CALLOUT_DEINIT_POST_OEM )
# define FBLBM_CALLOUT_DEINIT_POST_OEM()
#endif

#if !defined( FBLBM_CALLOUT_DEINIT_POST )
# define FBLBM_CALLOUT_DEINIT_POST()
#endif

#if !defined( FBLBM_CALLOUT_RESET )
# define FBLBM_CALLOUT_RESET                                   ApplFblBmReset
# define FBLBM_AP_CALLOUT_RESET
#endif

#if !defined( FBLBM_CALLOUT_CHECK_TARGET_VALIDITY )
# define FBLBM_CALLOUT_CHECK_TARGET_VALIDITY                   ApplFblBmCheckTargetValidity
# define FBLBM_AP_CALLOUT_CHECK_TARGET_VALIDITY
#endif

#if !defined( FBLBM_CALLOUT_IS_VALIDBLOCK )
# define FBLBM_CALLOUT_IS_VALIDBLOCK                           ApplFblBmIsValidBlock
# define FBLBM_AP_CALLOUT_IS_VALIDBLOCK
#endif

#if !defined( FBLBM_CALLOUT_CALL_TARGET )
# define FBLBM_CALLOUT_CALL_TARGET                             ApplFblBmStartSoftware
# if !defined( FBLBM_AP_CALLOUT_START_SOFTWARE )
#  define FBLBM_AP_CALLOUT_START_SOFTWARE
# endif
#endif

#if !defined( FBLBM_CALLOUT_CALL_FBL )
# define FBLBM_CALLOUT_CALL_FBL                                ApplFblBmStartSoftware
# if !defined( FBLBM_AP_CALLOUT_START_SOFTWARE )
#  define FBLBM_AP_CALLOUT_START_SOFTWARE
# endif
#endif

#if !defined( FBLBM_CALLOUT_CALL_FBL_INIT_KEYS )
# define FBLBM_CALLOUT_CALL_FBL_INIT_KEYS                      ApplFblBmStartSoftware
# if !defined( FBLBM_AP_CALLOUT_START_SOFTWARE )
#  define FBLBM_AP_CALLOUT_START_SOFTWARE
# endif
#endif

#if !defined( FBLBM_CALLOUT_CALL_FBL_INIT_CMAC )
# define FBLBM_CALLOUT_CALL_FBL_INIT_CMAC                      ApplFblBmStartSoftware
# if !defined( FBLBM_AP_CALLOUT_START_SOFTWARE )
#  define FBLBM_AP_CALLOUT_START_SOFTWARE
# endif
#endif

#if !defined( FBLBM_CALLOUT_CALL_FAILSAFE_UPDATER )
# define FBLBM_CALLOUT_CALL_FAILSAFE_UPDATER                   ApplFblBmStartSoftware
# if !defined( FBLBM_AP_CALLOUT_START_SOFTWARE )
#  define FBLBM_AP_CALLOUT_START_SOFTWARE
# endif
#endif

#if !defined( FBLBM_CALLOUT_GET_KEYEMPTY )
# define FBLBM_CALLOUT_GET_KEYEMPTY                            ApplFblBmGetKeyEmpty
# define FBLBM_AP_CALLOUT_GET_KEYEMPTY
#endif

#if !defined( FBLBM_CALLOUT_GET_FBL_CMACERASED )
# define FBLBM_CALLOUT_GET_FBL_CMACERASED                      ApplFblBmGetFblCmacErased
# define FBLBM_AP_CALLOUT_GET_FBL_CMACERASED
#endif

#if !defined( FBL_ENABLE_FBL_START )
# if !defined( FBLBM_CALLOUT_CHECKREPROGFLAG )
#  define FBLBM_CALLOUT_CHECKREPROGFLAG                        ApplFblBmCheckReprogFlag
#  define FBLBM_AP_CALLOUT_CHECKREPROGFLAG
# endif
#endif

#if !defined( FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_INIT )
#define FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_INIT             ApplFblBmSearchUpdaterHeaderInit
# define FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_INIT
#endif

#if !defined( FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_HEADER_ADDRESS )
#define FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_HEADER_ADDRESS   ApplFblBmSearchUpdaterHeaderAddress
# define FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_HEADER_ADDRESS
#endif

#if !defined( FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_NEXT )
#define FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_NEXT             ApplFblBmSearchUpdaterHeaderNext
# define FBLBM_AP_CALLOUT_SEARCH_FAILSAFE_UPDATER_NEXT
#endif

#if !defined( FBLBM_CALLOUT_FATAL_ERROR )
# define FBLBM_CALLOUT_FATAL_ERROR                             ApplFblBmFatalError
# define FBLBM_AP_CALLOUT_FATAL_ERROR
#endif

#endif

