

#define BM_MAIN_SOURCE

#include "fbl_inc.hpp"

#include "fbl_main_types.hpp"
#include "bm_main.hpp"
#include "fbl_fsm.hpp"

#if defined( FBLBM_ENABLE_SECURE_BOOT )
# include "fbl_secboot.hpp"
#endif

#if( FBLBM_MAIN_VERSION != 0x0304u ) || \
    ( FBLBM_MAIN_RELEASE_VERSION != 0x01u )
# error "Error in BM_MAIN.C: Source and Header file are inconsistent!"
#endif

#if defined( FBLBM_AP_API_VERSION_MAJOR ) && \
    defined( FBLBM_AP_API_VERSION_MINOR )
#else
# error "Error in BM_MAIN.C: Interface version requirements not defined!"
#endif

#if( FBLBM_AP_API_VERSION_MAJOR != FBLBM_API_VERSION_MAJOR ) || \
    ( FBLBM_AP_API_VERSION_MINOR > FBLBM_API_VERSION_MINOR )
# error "Error in BM_MAIN.C: Interface version compatibility check failed!"
#endif

#if defined( FBLBM_AP_HW_API_VERSION_MAJOR )
# if defined( FBLBM_AP_HW_API_VERSION_MINOR )
# else
#  error "Error in BM_MAIN.C: Interface version requirements not defined!"
# endif

# if( FBLBM_AP_HW_API_VERSION_MAJOR != FBLBM_API_VERSION_MAJOR ) || \
     ( FBLBM_AP_HW_API_VERSION_MINOR > FBLBM_API_VERSION_MINOR )
#  error "Error in BM_MAIN.C: Interface version compatibility check failed!"
# endif
#endif

#if defined( FBLBM_AP_OEM_API_VERSION_MAJOR )
# if defined( FBLBM_AP_OEM_API_VERSION_MINOR )
# else
#  error "Error in BM_MAIN.C: Interface version requirements not defined!"
# endif

# if( FBLBM_AP_OEM_API_VERSION_MAJOR != FBLBM_API_VERSION_MAJOR ) || \
    ( FBLBM_AP_OEM_API_VERSION_MINOR > FBLBM_API_VERSION_MINOR )
#  error "Error in BM_MAIN.C: Interface version compatibility check failed!"
# endif
#endif

#define FBLBM_SIZE_AND_ARRAY(array)   FBLBM_ARRAY_SIZE(array), (array)

typedef enum{
   FBLBM_STATE_POWER_ON,
   FBLBM_STATE_INIT,
   FBLBM_STATE_CHECK_FBL_VALIDITY,
   FBLBM_STATE_FAILSAFE_UPDATER_ENABLED,
   FBLBM_STATE_FAILSAFE_UPDATER_SEARCH_INIT,
   FBLBM_STATE_FAILSAFE_UPDATER_CHECK,
   FBLBM_STATE_FAILSAFE_UPDATER_SEARCH_NEXT,
   FBLBM_STATE_CALL_FAILSAFE_UPDATER,
   FBLBM_STATE_SECURE_BOOT_ENABLED,
   FBLBM_STATE_CHECK_KEY_AVAILABILITY,
   FBLBM_STATE_CALL_FBL_INIT_KEY,
   FBLBM_STATE_INIT_FBL_MAC_ENABLED,
   FBLBM_STATE_CHECK_FBL_MAC_ERASED,
   FBLBM_STATE_CALL_FBL_INIT_CMAC,
   FBLBM_STATE_STAY_IN_BOOT_ENABLED,
   FBLBM_STATE_CHECK_APPL_START_FLAG,
   FBLBM_STATE_CHECK_FBL_LBT,
   FBLBM_STATE_CHECK_REPROG_FLAG,
   FBLBM_STATE_REPROG_LBT_ENABLED,
   FBLBM_STATE_CHECK_REPROG_LBT,
   FBLBM_STATE_TARGET_LIST_INIT,
   FBLBM_STATE_TARGET_CHECK,
   FBLBM_STATE_TARGET_LIST_NEXT,
   FBLBM_STATE_CALL_TARGET,
   FBLBM_STATE_CHECK_FBL_VERIFICATION,
   FBLBM_STATE_CHECK_FBL_VERIFICATION_STAY_IN_BOOT,
   FBLBM_STATE_CALL_FBL,
   FBLBM_STATE_CALL_FBL_STAY_IN_BOOT,
   FBLBM_STATE_FAIL
}tFblBmState;

typedef enum{
   FBLBM_EVENT_CONTINUE = kFblFsmDefaultEvent_Count
}tFblBmEvent;

static void FblBmDeinit(void);

static tFblFsmGuard FblBmState_PowerOn_Entry                (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
static tFblFsmGuard FblBmState_Init_Entry                   (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
static tFblFsmGuard FblBmState_CallFailsafeUpdater_Entry    (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_KEY)
static tFblFsmGuard FblBmState_CallFblInitKey_Entry         (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )
static tFblFsmGuard FblBmState_CallTarget_Entry             (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
static tFblFsmGuard FblBmState_CallFbl_Entry                (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )
static tFblFsmGuard FblBmState_CallFblStayInBoot_Entry      (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
static tFblFsmGuard FblBmState_CallFblInitCmac_Entry        (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
static tFblFsmGuard FblBmState_Fail_Entry                   (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);

static tFblFsmGuard FblBmState_CheckFblValidity             (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
static tFblFsmGuard FblBmState_FailsafeUpdaterSearchInit    (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
static tFblFsmGuard FblBmState_FailsafeUpdaterCheck         (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
static tFblFsmGuard FblBmState_FailsafeUpdaterSearchNext    (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
static tFblFsmGuard FblBmState_CheckKeyAvailability         (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
static tFblFsmGuard FblBmState_CheckFblMacErased            (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )
static tFblFsmGuard FblBmState_CheckApplStartFlag           (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
static tFblFsmGuard FblBmState_CheckReprogFlag              (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
static tFblFsmGuard FblBmState_CheckFblLbt                  (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )
static tFblFsmGuard FblBmState_CheckReprogLbt               (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )
static tFblFsmGuard FblBmState_TargetListInit               (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
static tFblFsmGuard FblBmState_TargetCheck                  (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
static tFblFsmGuard FblBmState_TargetListNext               (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);
#endif
static tFblFsmGuard FblBmState_CheckFblVerification         (tFblFsmContextPtr const pFsmContext, tFblFsmEvent event);

#define FBLBM_HEADER_START_SEC_CONST
#include "MemMap.hpp"

V_MEMROM0 V_MEMROM1 tFblBmHeader V_MEMROM2 FblBmHeader =
{
   FBLBM_HEADER_MAGIC_VALUE,
   FBLBM_HEADER_MAJOR_VERSION,
   FBLBM_HEADER_MINOR_VERSION,
   FBL_HEADER_ADDRESS,
#if defined( FBLBM_MAIN_ENABLE_FBL_START )
   (tFblStrtFct)FblStart,
#else
   (tFblStrtFct)V_NULL,
#endif
#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )
   (tApplStrtFct)ApplStart,
#else
   (tApplStrtFct)V_NULL,
#endif
   0u,
   FBLBM_HEADER_END_MAGIC_VALUE
};
#define FBLBM_HEADER_STOP_SEC_CONST
#include "MemMap.hpp"

#define FBLBM_START_SEC_VAR
#include "MemMap.hpp"

V_MEMRAM0 static V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 fblBmBlockInfo;

#if defined( FBLBM_ENABLE_STANDALONE_MODE )

V_MEMRAM0 static V_MEMRAM1 tFblHeader V_MEMRAM2 fblBmFblHeader;
#endif

V_MEMRAM0 static V_MEMRAM1 tFblFsmContext V_MEMRAM2 g_BmFsmContext;

#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )

V_MEMRAM0 static V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 g_BmFailsafeUpdaterBmHeader;
#endif

#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )

V_MEMRAM0 static V_MEMRAM1 vuintx V_MEMRAM2 g_BmTargetListIndex;

V_MEMRAM0 static V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 g_BmTargetBmHeader;
#endif

V_MEMRAM0 static V_MEMRAM1 tFblBmError V_MEMRAM2 g_BmError;

#define FBLBM_STOP_SEC_VAR
#include "MemMap.hpp"

#define FBLBM_START_SEC_CONST
#include "MemMap.hpp"

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_PowerOn[] = {
   FBL_FSM_TRIGGER_ENTRY(FblBmState_PowerOn_Entry),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_INIT)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_Init[] = {
   FBL_FSM_TRIGGER_ENTRY(FblBmState_Init_Entry),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_CHECK_FBL_VALIDITY)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckFblValidity[] = {
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckFblValidity, FBLBM_STATE_SECURE_BOOT_ENABLED),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAILSAFE_UPDATER_ENABLED)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_FailsafeUpdaterEnabled[] = {
#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_FAILSAFE_UPDATER_SEARCH_INIT)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_FAIL)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_FailsafeUpdaterSearchInit[] = {
#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_FailsafeUpdaterSearchInit, FBLBM_STATE_FAILSAFE_UPDATER_CHECK),
#endif
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_FailsafeUpdaterCheck[] = {
#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_FailsafeUpdaterCheck, FBLBM_STATE_CALL_FAILSAFE_UPDATER),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAILSAFE_UPDATER_SEARCH_NEXT),
#else
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_FailsafeUpdaterSearchNext[] = {
#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_FailsafeUpdaterSearchNext, FBLBM_STATE_FAILSAFE_UPDATER_CHECK),
#endif
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CallFailsafeUpdater[] = {
#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )
   FBL_FSM_TRIGGER_ENTRY(FblBmState_CallFailsafeUpdater_Entry),
#endif
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_SecureBootEnabled[] = {
#if defined( FBLBM_ENABLE_SECURE_BOOT )
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_CHECK_KEY_AVAILABILITY)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_CHECK_REPROG_FLAG)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckKeyAvailability[] = {
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckKeyAvailability, FBLBM_STATE_INIT_FBL_MAC_ENABLED),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_CALL_FBL_INIT_KEY)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CallFblInitKey[] = {
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_KEY)
   FBL_FSM_TRIGGER_ENTRY(FblBmState_CallFblInitKey_Entry),
#endif
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_InitFblMacEnabled[] = {
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_CHECK_FBL_MAC_ERASED)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_CHECK_REPROG_FLAG)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckFblMacErased[] = {
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckFblMacErased, FBLBM_STATE_CALL_FBL_INIT_CMAC),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_CHECK_REPROG_FLAG)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_FAIL)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CallFblInitCmac[] = {
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
   FBL_FSM_TRIGGER_ENTRY(FblBmState_CallFblInitCmac_Entry),
#endif
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_StayInBootEnabled[] = {
#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT)
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_CHECK_APPL_START_FLAG)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_CHECK_FBL_LBT)
#endif
 };

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckApplStartFlag[] = {
#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckApplStartFlag, FBLBM_STATE_CHECK_FBL_LBT),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_CHECK_FBL_VERIFICATION_STAY_IN_BOOT)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_FAIL)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckFblLbt[] = {
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckFblLbt, FBLBM_STATE_REPROG_LBT_ENABLED),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckReprogFlag[] = {
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckReprogFlag, FBLBM_STATE_CHECK_FBL_VERIFICATION),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_STAY_IN_BOOT_ENABLED)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_ReprogLbtEnabled[] = {
#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )
   FBL_FSM_TRIGGER_UNCONDITIONAL( FBLBM_STATE_CHECK_REPROG_LBT),
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL( FBLBM_STATE_TARGET_LIST_INIT)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckReprogLbt[] = {
#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckReprogLbt, FBLBM_STATE_TARGET_LIST_INIT),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_CHECK_FBL_VERIFICATION)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_FAIL)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_TargetListInit[] = {
#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_TargetListInit, FBLBM_STATE_TARGET_CHECK),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_CHECK_FBL_VERIFICATION)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_TargetCheck[] = {
#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_TargetCheck, FBLBM_STATE_CALL_TARGET),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_TARGET_LIST_NEXT)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_FAIL)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_TargetListNext[] = {
#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_TargetListNext, FBLBM_STATE_TARGET_CHECK),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_CHECK_FBL_VERIFICATION)
#else
   FBL_FSM_TRIGGER_UNCONDITIONAL(FBLBM_STATE_FAIL)
#endif
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CallTarget[] = {
#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )
   FBL_FSM_TRIGGER_ENTRY(FblBmState_CallTarget_Entry),
#endif
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckFblVerification[] = {
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckFblVerification, FBLBM_STATE_CALL_FBL),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CheckFblVerificationStayInBoot[] = {
   FBL_FSM_TRIGGER_TRANSITION_ACTION(FBLBM_EVENT_CONTINUE, FblBmState_CheckFblVerification, FBLBM_STATE_CALL_FBL_STAY_IN_BOOT),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CallFbl[] = {
   FBL_FSM_TRIGGER_ENTRY(FblBmState_CallFbl_Entry),
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_CallFblStayInBoot[] = {
#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT)
   FBL_FSM_TRIGGER_ENTRY(FblBmState_CallFblStayInBoot_Entry),
#endif
   FBL_FSM_TRIGGER_TRANSITION(FBLBM_EVENT_CONTINUE, FBLBM_STATE_FAIL)
};

V_MEMROM0 static V_MEMROM1 tFblFsmEventEntry V_MEMROM2 g_BmState_Fail[] = {
   FBL_FSM_TRIGGER_ENTRY(FblBmState_Fail_Entry)
};

V_MEMROM0 static V_MEMROM1 tFblFsmStateDefinition V_MEMROM2 bmFsmStates[] =
{
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_PowerOn) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_Init) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckFblValidity) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterEnabled) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterSearchInit) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterCheck) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterSearchNext) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallFailsafeUpdater) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_SecureBootEnabled) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckKeyAvailability) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallFblInitKey) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_InitFblMacEnabled) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckFblMacErased) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallFblInitCmac) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_StayInBootEnabled) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckApplStartFlag) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckFblLbt) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckReprogFlag) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_ReprogLbtEnabled) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckReprogLbt) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_TargetListInit) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_TargetCheck) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_TargetListNext) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallTarget) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckFblVerification) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckFblVerificationStayInBoot) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallFbl) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallFblStayInBoot) },
   { FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_Fail) }
};
#define FBLBM_STOP_SEC_CONST
#include "MemMap.hpp"

static tFblFsmGuard FblBmState_PowerOn_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   g_BmError = FBLBM_ERROR_NO_ERROR;

   FBLBM_CALLOUT_POWER_ON_PRE_HW();
   FBLBM_CALLOUT_POWER_ON_PRE_OEM();
   FBLBM_CALLOUT_POWER_ON_PRE();

   FblInterruptDisable();

   assertFblGen(FblBmHeaderLocal == FblBmHeaderTable, kFblSysAssertParameterOutOfRange);

   ClrWDInit();

   MemDriver_InitPowerOn();

#if !defined( FBLBM_ENABLE_STANDALONE_MODE )

# if( FBL_CW_API_REFERENCE_VERSION_MAJOR == 0x02u )
   FblCw_InitMemory();
# else
   FblCwClrInit();
# endif

   FblDiagInitPowerOn();
#endif

   FBLBM_CALLOUT_POWER_ON_POST_HW();
   FBLBM_CALLOUT_POWER_ON_POST_OEM();
   FBLBM_CALLOUT_POWER_ON_POST();

   return kFblFsmGuard_True;
}

static tFblFsmGuard FblBmState_Init_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   FBLBM_CALLOUT_INIT_PRE_HW();
   FBLBM_CALLOUT_INIT_PRE_OEM();
   FBLBM_CALLOUT_INIT_PRE();

#if defined( FBL_ENABLE_PRE_WDINIT )

   FblInitWatchdog();
#endif
#if defined( FBL_ENABLE_PRE_TIMERINIT )

   FblTimerInit();
#endif

#ifdef FBL_ENABLE_PRE_WDINIT

#else

   FblInitWatchdog();
#endif

#if defined( FBL_ENABLE_PRE_TIMERINIT )

#else

   FblTimerInit();
#endif

#if defined( FBLBM_ENABLE_SECURE_BOOT )

   FblSb_EcuMInit();
#endif

   FblLbtInitPowerOn();

   FBLBM_CALLOUT_INIT_POST_HW();
   FBLBM_CALLOUT_INIT_POST_OEM();
   FBLBM_CALLOUT_INIT_POST();

   return kFblFsmGuard_True;
}

#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )

static tFblFsmGuard FblBmState_CallFailsafeUpdater_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   FblBmDeinit();

   FBLBM_CALLOUT_CALL_FAILSAFE_UPDATER(&g_BmFailsafeUpdaterBmHeader);

   return kFblFsmGuard_True;
}
#endif

#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_KEY )

static tFblFsmGuard FblBmState_CallFblInitKey_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   FblBmDeinit();

   FblBmSetInitKeysMagicFlag();

   FBLBM_CALLOUT_CALL_FBL_INIT_KEYS(&fblBmBlockInfo.bmHeader);

   return kFblFsmGuard_True;
}
#endif

#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )

static tFblFsmGuard FblBmState_CallTarget_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
# endif

   FblBmDeinit();

   FBLBM_CALLOUT_CALL_TARGET(&g_BmTargetBmHeader);

   return kFblFsmGuard_True;
}
#endif

#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )

static tFblFsmGuard FblBmState_CallFblInitCmac_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   FblBmDeinit();

   FblBmSetInitCmacMagicFlag();

   FBLBM_CALLOUT_CALL_FBL_INIT_CMAC(&fblBmBlockInfo.bmHeader);

   return kFblFsmGuard_True;
}
#endif

static tFblFsmGuard FblBmState_CallFbl_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   FblBmDeinit();

   FBLBM_CALLOUT_CALL_FBL(&fblBmBlockInfo.bmHeader);

   return kFblFsmGuard_True;
}

# if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )

static tFblFsmGuard FblBmState_CallFblStayInBoot_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   FblBmDeinit();

   FblBmSetStayInBootMagicFlag();

   FBLBM_CALLOUT_CALL_FBL(&fblBmBlockInfo.bmHeader);

   return kFblFsmGuard_True;
}
#endif

static tFblFsmGuard FblBmState_Fail_Entry(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   FBLBM_CALLOUT_FATAL_ERROR(g_BmError);

   return kFblFsmGuard_False;
}

static tFblFsmGuard FblBmState_CheckFblValidity(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   result = kFblFsmGuard_True;

#if defined( FBLBM_ENABLE_STANDALONE_MODE )

   if(FblReadProm(FblBmHeader.fblHeaderAddress, (vuint8*) &fblBmFblHeader, sizeof(tFblHeader)) != sizeof(tFblHeader)){
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_HEADER_READ_FAILED;
   }

   if(kFblFsmGuard_True == result){
      if(fblBmFblHeader.magicFlag != FBL_MAIN_HEADER_MAGIC_FLAG)
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_HEADER_MAGIC_FAILED;
      }
   }

   if(kFblFsmGuard_True == result){
      fblBmBlockInfo.logicalBlock.blockStartAddress = fblBmFblHeader.fblStartAddress;
      fblBmBlockInfo.logicalBlock.blockLength = fblBmFblHeader.fblLength;
      fblBmBlockInfo.logicalBlock.bmHeaderAddress = (tFblAddress) fblBmFblHeader.bmHeader;
      fblBmBlockInfo.logicalBlock.mandatoryType = TRUE;
      fblBmBlockInfo.logicalBlock.blockNr = 0x00u;

      if(kFblOk != FBLBM_CALLOUT_IS_VALIDBLOCK(FBLBMHDR_TARGET_FBL, &fblBmBlockInfo.logicalBlock))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_VALIDITY_FAILED;
      }
   }

#else

   fblBmBlockInfo.logicalBlock.blockStartAddress = FblHeader.fblStartAddress;
   fblBmBlockInfo.logicalBlock.blockLength = FblHeader.fblLength;
   fblBmBlockInfo.logicalBlock.bmHeaderAddress = (tFblAddress) FblHeader.bmHeader;
   fblBmBlockInfo.logicalBlock.mandatoryType = TRUE;
   fblBmBlockInfo.logicalBlock.blockNr = 0x00u;

#endif

   if(kFblFsmGuard_True == result){
      if(FBLBMHDR_CHKHDR_OK != FblBmHdrGetBmHeader(FBLBMHDR_TARGET_FBL, fblBmBlockInfo.logicalBlock.bmHeaderAddress, &fblBmBlockInfo.bmHeader))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_FBL_BMHEADER_INCORRECT;
      }
   }

   return result;
}

#if defined( FBLBM_ENABLE_UPDATER_FAILSAFE )

static tFblFsmGuard FblBmState_FailsafeUpdaterSearchInit(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   if(kFblOk == FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_INIT()){
      result = kFblFsmGuard_True;
   }
   else{
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_UPDATER_SEARCH_INIT_FAILED;
   }
   return result;
}

static tFblFsmGuard FblBmState_FailsafeUpdaterCheck(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;
   tFblBmBlockInfo blockInfo;
   vuint32 headerAddress;
# if defined( FBLBM_ENABLE_SECURE_BOOT )
   vuint8 bmHeaderMac[FBLSB_MAC_LENGTH];
   vuint8 bmHeaderMacLength;
   uint32 macId;
# endif

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   result = kFblFsmGuard_True;
   if(kFblOk != FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_HEADER_ADDRESS(&headerAddress)){
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_UPDATER_HEADER_ADDRESS;
   }

   if(kFblFsmGuard_True == result){
      blockInfo.bmHeader.bmTargetHandle = FBLBMHDR_TARGET_FBLUPDATER;
      blockInfo.bmHeader.bmBlockStartAddress = 0u;
      blockInfo.bmHeader.bmBlockLength = 1u;
      blockInfo.bmHeader.bmEntryAddress = 0u;

      if(FblReadProm(headerAddress, (vuint8 *)&blockInfo.bmHeader, sizeof(tFblBmHdrHeader)) != sizeof(tFblBmHdrHeader))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_UPDATER_HEADER_READ_ERROR;
      }
   }

   if(kFblFsmGuard_True == result){
      if(blockInfo.bmHeader.bmTargetHandle != FBLBMHDR_TARGET_FBLUPDATER)
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_UPDATER_HEADER_TYPE;
      }
   }

   if(kFblFsmGuard_True == result){
      if( kFblOk != FblBmHdrCheckConsistency(&blockInfo.bmHeader))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_UPDATER_HEADER_CONSISTENCY;
      }
   }

   if(kFblFsmGuard_True == result){
      blockInfo.logicalBlock.blockStartAddress = blockInfo.bmHeader.bmBlockStartAddress;
      blockInfo.logicalBlock.blockLength = blockInfo.bmHeader.bmBlockLength;

      if(kFblOk != FBLBM_CALLOUT_IS_VALIDBLOCK(blockInfo.bmHeader.bmTargetHandle, &blockInfo.logicalBlock))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_UPDATER_BLOCK_VALIDITY;
      }
   }

# if defined( FBLBM_ENABLE_SECURE_BOOT )
   if(kFblFsmGuard_True == result){
      bmHeaderMacLength = sizeof(bmHeaderMac);

      if(kFblOk == ApplFblSbGetBmHeaderMac(&blockInfo.logicalBlock, bmHeaderMac, bmHeaderMacLength))
      {
         macId = FblBmHdr_GetFblSbMacId(blockInfo.bmHeader.bmTargetHandle);
      }
      else
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_UPDATER_HEADER_CMAC_READ;
      }
   }
   if(kFblFsmGuard_True == result){
      if(kFblOk != FblSb_MacVerify(macId, (vuint32)&blockInfo.bmHeader, sizeof(tFblBmHdrHeader), bmHeaderMac, bmHeaderMacLength))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_UPDATER_HEADER_CMAC_VERIFY;
      }
   }

   if(kFblFsmGuard_True == result){
      if(kFblOk != FblBmHdrVerifyAreas(blockInfo.bmHeader.bmTargetHandle, &blockInfo))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_UPDATER_VERIFY;
      }
   }
# endif

   if(kFblFsmGuard_True == result){
      g_BmFailsafeUpdaterBmHeader = blockInfo.bmHeader;
   }

   return result;
}

static tFblFsmGuard FblBmState_FailsafeUpdaterSearchNext(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   if(kFblOk == FBLBM_CALLOUT_SEARCH_FAILSAFE_UPDATER_NEXT()){
      result = kFblFsmGuard_True;
   }
   else{
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_UPDATER_SEARCH_NEXT_FINISHED;
   }

   return result;
}
#endif

static tFblFsmGuard FblBmState_CheckKeyAvailability(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

#if defined( FBLBM_ENABLE_SECURE_BOOT )
   if(FBLBM_KEY_IS_NOT_AVAILABLE == FBLBM_CALLOUT_GET_KEYEMPTY()){
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_KEY_NOT_AVAILABLE;
   }
   else{
      result = kFblFsmGuard_True;
   }
#else

   result = kFblFsmGuard_True;
#endif
   return result;
}

#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )

static tFblFsmGuard FblBmState_CheckFblMacErased(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   if(FBLBM_MAC_IS_AVAILABLE == FBLBM_CALLOUT_GET_FBL_CMACERASED(&fblBmBlockInfo)){
      result = kFblFsmGuard_False;
   }
   else{
      result = kFblFsmGuard_True;
   }
   return result;
}
#endif

#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )

static tFblFsmGuard FblBmState_CheckApplStartFlag( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event ){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   if(FblBmChkApplStartMagicFlag()){
      FblBmClrMagicFlag();
      result = kFblFsmGuard_True;
   }
   else{
      result = kFblFsmGuard_False;
   }

   return result;
}
#endif

static tFblFsmGuard FblBmState_CheckReprogFlag(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

#if defined( FBL_ENABLE_FBL_START )
   if(FblBmChkFblStartMagicFlag())
#else
   if(FBLBM_CALLOUT_CHECKREPROGFLAG() == kFblOk)
#endif
   {
      result = kFblFsmGuard_True;
   }
   else{
      result = kFblFsmGuard_False;
   }

   return result;
}

static tFblFsmGuard FblBmState_CheckFblLbt(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
#if defined( FBLBM_ENABLE_STANDALONE_MODE )
   tFblFsmGuard result;
   V_MEMROM1_FAR tLogicalBlockTable V_MEMROM2_FAR V_MEMROM3 * fblLbtPtr;
# if defined( FBLBM_ENABLE_SECURE_BOOT )
   uint8 mac[FBLSB_MAC_LENGTH];
   uint32 macLength;
   vuint32 lbtSize;
   uint32 macId;
# endif

# if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
# endif

   fblLbtPtr = fblBmFblHeader.pLogicalBlockTable;
   if(fblLbtPtr == ( V_MEMROM1_FAR tLogicalBlockTable V_MEMROM2_FAR V_MEMROM3 *) V_NULL){
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_LBT_POINTER_NULL;
   }
   else{
      if(fblLbtPtr->noOfBlocks > FBL_LBT_BLOCK_COUNT)
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_LBT_TOO_LARGE;
      }
      else
      {
         result = kFblFsmGuard_True;
      }
   }

# if defined( FBLBM_ENABLE_SECURE_BOOT )
   if(kFblFsmGuard_True == result){
      if(kFblOk != ApplFblSbGetLogicalBlockTableSize(&fblBmBlockInfo.logicalBlock, &lbtSize))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_LBT_SIZE;
      }
   }

   if(kFblFsmGuard_True == result){
      macLength = sizeof(mac);
      if(kFblOk != ApplFblSbGetLogicalBlockTableMac(&fblBmBlockInfo.logicalBlock, mac, macLength))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_LBT_GET_MAC;
      }
   }

   if(kFblFsmGuard_True == result){
      macId = FblBmHdr_GetFblSbMacId(FBLBMHDR_TARGET_FBL);
      if(kFblOk != FblSb_MacVerify(macId, (uint32) fblLbtPtr, lbtSize, (const vuint8 *) mac, macLength))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_LBT_GET_FBL_MAC;
      }
   }

# endif

   if(kFblFsmGuard_True == result){
      FblLbtActivateLbtBlockByAddress((tFblAddress)fblLbtPtr);
   }
   else{
      FblLbtInitPowerOn();
   }

   return result;
#else
# if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
# endif

   return kFblFsmGuard_True;
#endif
}

#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )

static tFblFsmGuard FblBmState_CheckReprogLbt( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event ){
   tFblFsmGuard result;

   V_MEMROM1 tLogicalBlockTable V_MEMROM2 V_MEMROM3 * reprogLbtPtr;
   tFblBmBlockInfo blockInfo;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   result = kFblFsmGuard_True;

   if(kFblOk != FblLbtGetBlockDescriptorByNr(FBL_LBT_LBT_BLOCK_NUMBER, &blockInfo.logicalBlock)){
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_REPROG_LBT_DESCR;
   }

   if(kFblFsmGuard_True == result){
      if(kFblOk != FBLBM_CALLOUT_IS_VALIDBLOCK(FBLBMHDR_TARGET_REPROGLBT, &blockInfo.logicalBlock))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_REPROG_LBT_INVALID;
      }
   }

   if(kFblFsmGuard_True == result){
      if(FBLBMHDR_CHKHDR_OK != FblBmHdrGetBmHeader(FBLBMHDR_TARGET_REPROGLBT, blockInfo.logicalBlock.bmHeaderAddress, &blockInfo.bmHeader))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_REPROG_LBT_BMHEADER_INCORRECT;
      }
   }

# if defined( FBLBM_ENABLE_SECURE_BOOT )
   if(kFblFsmGuard_True == result){
      if(FBLBMHDR_CHKHDR_OK != FblBmHdrVerifyBmHeader(FBLBMHDR_TARGET_REPROGLBT, &blockInfo))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_REPROG_LBT_VERIFY_HEADER;
      }
   }

   if(kFblFsmGuard_True == result){
      if(kFblOk != FblBmHdrVerifyAreas(FBLBMHDR_TARGET_REPROGLBT, &blockInfo))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_REPROG_LBT_VERIFY_AREAS;
      }
   }
# endif

   if(kFblFsmGuard_True == result){
      reprogLbtPtr = (V_MEMROM1 tLogicalBlockTable V_MEMROM2 V_MEMROM3 *) blockInfo.logicalBlock.blockStartAddress;

      if(reprogLbtPtr->magicFlag != FblLbtGetMagicFlag())
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_REPROG_LBT_MAGIC_FLAG;
      }
      else if(reprogLbtPtr->noOfBlocks > FBL_LBT_BLOCK_COUNT)
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_REPROG_LBT_BLOCK_COUNT;
      }
      else
      {
      }
   }

   if(kFblFsmGuard_True == result){
      FblLbtActivateLbtBlockByAddress((tFblAddress) reprogLbtPtr);
   }

   return result;
}
#endif

#if( FBLBM_BOOTTARGETLIST_SIZE > 0u )

static tFblFsmGuard FblBmState_TargetListInit(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   g_BmTargetListIndex = 0u;
   result = kFblFsmGuard_True;

   return result;
}

static tFblFsmGuard FblBmState_TargetCheck(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;
   tFblBmHdrTargetListEntry target;
   tFblBmHdrTargetHandle targetHandle;
   tFblBmBlockInfo blockInfoTarget;
   tFblBmBlockInfo blockInfoDep;
   vuintx index;
   tFblBmHdrCheckBmHeaderResult findHeaderResult;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   target = FblBm_BootTargetList[g_BmTargetListIndex];
   targetHandle = target.target;
   result = kFblFsmGuard_True;

   if(kFblOk != FBLBM_CALLOUT_CHECK_TARGET_VALIDITY(targetHandle)){
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_TARGET_INVALID;
   }

   if(kFblFsmGuard_True == result){
      if(FBLBMHDR_CHKHDR_OK != FblBmHdrFindValidHeader(targetHandle, &blockInfoTarget))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_TARGET_NO_VALID_HEADER;
      }
   }

#if defined( FBLBM_ENABLE_SECURE_BOOT )
   if(kFblFsmGuard_True == result){
      if(kFblOk != FblBmHdrVerifyAreas(targetHandle, &blockInfoTarget))
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_TARGET_VERIFICATION_FAILED;
      }
   }
#endif

   if(kFblFsmGuard_True == result){
      for(index = 0; index < target.dependenciesSize; index++)
      {
         targetHandle = target.dependencies[index].target;

         findHeaderResult = FblBmHdrFindValidHeader(targetHandle, &blockInfoDep);

         if(FBLBMHDR_CHKHDR_OK == findHeaderResult)
         {
#if defined( FBLBM_ENABLE_SECURE_BOOT )
            if(kFblOk != FblBmHdrVerifyAreas(targetHandle, &blockInfoDep))
            {
               result = kFblFsmGuard_False;
               g_BmError = FBLBM_ERROR_TARGET_DEP_VERIFY_FAILED;
            }
#endif
         }
         else
         {
            if(FBLBM_TARGET_TYPE_MANDATORY == target.dependencies[index].type)
            {
               result = kFblFsmGuard_False;
               g_BmError = FBLBM_ERROR_TARGET_DEP_MANDATORY_MISSING;
            }
            else
            {
            }
         }
         if(kFblFsmGuard_False == result)
         {
            break;
         }
      }
   }

   if(kFblFsmGuard_True == result){
      if(blockInfoTarget.bmHeader.bmEntryAddress == FBLBMHDR_ENTRY_ADDRESS_INVALID)
      {
         result = kFblFsmGuard_False;
         g_BmError = FBLBM_ERROR_TARGET_INVALID_ADDRESS;
         assertFbl(0u, kFblSysAssertParameterOutOfRange);
      }
   }

   if(kFblFsmGuard_True == result){
      g_BmTargetBmHeader = blockInfoTarget.bmHeader;
   }

   return result;
}

static tFblFsmGuard FblBmState_TargetListNext(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

   g_BmTargetListIndex++;
   if(FBLBM_BOOTTARGETLIST_SIZE > g_BmTargetListIndex){
      result = kFblFsmGuard_True;
   }
   else{
      result = kFblFsmGuard_False;
   }

   return result;
}
#endif

static tFblFsmGuard FblBmState_CheckFblVerification(tFblFsmContextPtr const pFsmContext, tFblFsmEvent event){
   tFblFsmGuard result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pFsmContext;
   (void)event;
#endif

#if defined( FBLBM_ENABLE_SECURE_BOOT )
   if(kFblOk != FblBmHdrVerifyAreas(FBLBMHDR_TARGET_FBL, &fblBmBlockInfo)){
      result = kFblFsmGuard_False;
      g_BmError = FBLBM_ERROR_FBL_VERIFICATION_FAILED;
   }
   else
#endif
   {
      result = kFblFsmGuard_True;
   }

   return result;
}

static void FblBmDeinit(void){
   FBLBM_CALLOUT_DEINIT_PRE_OEM();
   FBLBM_CALLOUT_DEINIT_PRE_HW();
   FBLBM_CALLOUT_DEINIT_PRE();

#if defined( FBL_WATCHDOG_ON )

   ApplFblWDLong();
#endif

   FblTimerStopp();

   FBLBM_CALLOUT_DEINIT_POST_OEM();
   FBLBM_CALLOUT_DEINIT_POST_HW();
   FBLBM_CALLOUT_DEINIT_POST();
}

#if defined( FBLBM_ENABLE_STANDALONE_MODE )

void FblMemSetInteger( vuintx count, vuint32 input, tFblMemRamData buffer){
   vuintx localCount;
   vuint32 localInput;

   localCount = count;
   localInput = input;

   while (localCount > 0u){
      localCount--;

      buffer[localCount] = (vuint8) (localInput & 0xFFu);

      localInput >>= 8u;
   }
}

vuint32 FblMemGetInteger( vuintx count, tFblMemConstRamData buffer){
   vuint32 output;
   vuintx idx;

   output = 0u;
   idx = 0u;

   while (idx < count){
      output <<= 8u;

      output |= (vuint32) buffer[idx];

      idx++;
   }

   return output;
}
#endif

int V_API_NEAR main(void){
   FblFsmInitPowerOn();

   g_BmFsmContext.stateDefinitions = bmFsmStates;
   g_BmFsmContext.stateCount = FBLBM_ARRAY_SIZE(bmFsmStates);
   FblFsmInit(&g_BmFsmContext, (tFblFsmState) FBLBM_STATE_POWER_ON);

   while (g_BmFsmContext.state != (tFblFsmState) FBLBM_STATE_FAIL){
      FblFsmTriggerEvent(&g_BmFsmContext, (tFblFsmEvent) FBLBM_EVENT_CONTINUE);
      FblFsmStateTask(&g_BmFsmContext);
   }

   FBLBM_CALLOUT_FATAL_ERROR(FBLBM_ERROR_END_OF_MAIN_REACHED);

   return 0;
}

#if defined( FBLBM_MAIN_ENABLE_FBL_START )
# define FBLBM_MAIN_FBLSTART_START_SEC_CODE
# include "MemMap.hpp"

#  if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )
void FblStart( FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_FIRST
   V_MEMRAM1 void V_MEMRAM2 V_MEMRAM3 * pFblStartParam, vuint8 length )
#  else
void FblStart( FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE_TYPE_ONLY )
#  endif
{
# if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )
   vuintx i;
# endif

   FblInterruptDisable();

   FblHwRestoreFblContext();

# if defined( FBLBM_MAIN_ENABLE_FBLSTART_PARAM )

   for (i = 0u; i < length; i++){
      ((vuint8*)&fblBmFblStartParameter)[i] = ((vuint8*)pFblStartParam)[i];
   }
# endif

#if defined( FBLBM_MAIN_ENABLE_FBLSTART_CHANNEL )
   fblBmFblStartChannel = FBLBM_MAIN_FBLSTART_CHANNEL_HANDLE;
#endif

   FblBmSetFblStartMagicFlag();

   FBLBM_CALLOUT_RESET();
}
# define FBLBM_MAIN_FBLSTART_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

#if defined( FBLBM_MAIN_ENABLE_STAY_IN_BOOT )
# define FBLBM_MAIN_APPLSTART_START_SEC_CODE
# include "MemMap.hpp"

# if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )
void ApplStart( V_MEMRAM1 void V_MEMRAM2 V_MEMRAM3 * pApplStartParam, vuint8 length )
# else
void ApplStart( void )
# endif
{
# if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )
   vuintx i;
# endif

   FblInterruptDisable();

   FblHwRestoreFblContext();
# if defined( FBLBM_MAIN_ENABLE_APPLSTART_PARAM )

   for (i = 0u; i < length; i++){
      ((vuint8*)&fblBmApplStartParameter)[i] = ((vuint8*)pApplStartParam)[i];
   }
# endif

   FblBmSetApplStartMagicFlag();

   FBLBM_CALLOUT_RESET();
}
# define FBLBM_MAIN_APPLSTART_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

