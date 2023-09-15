#include "fbl_inc.hpp"
#include "SUPPLIER1_CustomFunctions.hpp"

#if( FBL_MAIN_VERSION != 0x0402u ) || \
    ( FBL_MAIN_RELEASE_VERSION != 0x00u )
# error "Error in fbl_main.c: Source and header file are inconsistent!"
#endif

#if( FBL_MAIN_VERSION != _FBL_MAIN_VERSION ) || \
    ( FBL_MAIN_RELEASE_VERSION != _FBL_MAIN_RELEASE_VERSION)
# error "Error in fbl_main.c: Source and v_ver.h are inconsistent!"
#endif

#if defined( FBL_ENABLE_FBL_START )
#if !defined( FblStartReset )
#define FblStartReset() ApplFblReset()
#endif
#endif

#if defined( FBL_ENABLE_STAY_IN_BOOT )
#if !defined( kFblMainStartMessageDelay )
#define kFblMainStartMessageDelay 20u
#endif
#define kFblMainStartMessageReceived 0u
#define kFblMainStartMessageTimeout  1u
#endif

#define FblMainSetStartFromReset()                 SetFblMainState( kFblMainStateStartFromReset )
#define FblMainSetStartFromAppl()                  SetFblMainState( kFblMainStateStartFromAppl )
#define FblMainSetStartFromXcp()                   SetFblMainState( kFblMainStateStartFromXcp )
#define FblMainSetApplicationValid()               SetFblMainState( kFblMainStateApplicationValid )
#define FblMainSetWaitStartMessage()   {                                               \
                                       SetFblMainState( kFblMainStateWaitStartMessage );    \
                                       startMessageDelay = kFblMainStartMessageDelay + 1u;   \
                                       }
#define FblMainSetStartMessageReceived()           SetFblMainState( kFblMainStateStartMessageReceived )

#define FblMainClrStartFromReset()                 ClrFblMainState( kFblMainStateStartFromReset )
#define FblMainClrStartFromAppl()                  ClrFblMainState( kFblMainStateStartFromAppl )
#define FblMainClrStartFromXcp()                   ClrFblMainState( kFblMainStateStartFromXcp )
#define FblMainClrApplicationValid()               ClrFblMainState( kFblMainStateApplicationValid )
#define FblMainClrWaitStartMessage()               ClrFblMainState( kFblMainStateWaitStartMessage )
#define FblMainClrStartMessageReceived()           ClrFblMainState( kFblMainStateStartMessageReceived )

#if defined( FBLBM_ENABLE_STANDALONE_MODE )
#define FBLMAIN_ENABLE_STANDALONE_MODE
#endif

#define FBLHEADER_START_SEC_CONST
#include "MemMap.hpp"

V_MEMROM0 V_MEMROM1 tFblHeader V_MEMROM2 FblHeader = {
   FBL_MAIN_HEADER_MAGIC_FLAG
#if defined( FBL_MTAB_NO_OF_BLOCKS )
   ,(tFblHeaderLogicalBlockTablePtr)(&FblLogicalBlockTable)
   ,sizeof(FblLogicalBlockTable)
#else
   ,V_NULL
   ,0u
#endif
#if defined( FBL_ENABLE_COMMON_DATA )
   ,(tFblCommonDataPtr)(&fblCommonData)
#endif
   ,FBL_BLOCK_START_ADDRESS
   ,FBL_BLOCK_LENGTH
   ,&FblBmHdrHeader
};
#define FBLHEADER_STOP_SEC_CONST
#include "MemMap.hpp"

#if defined( FBL_ENABLE_STAY_IN_BOOT )
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 startMessageDelay;
#endif

V_MEMRAM0 V_MEMRAM1_NEAR tFblStateBitmap V_MEMRAM2_NEAR fblMainStates[FBL_STATE_INDEX(kFblMainNumberOfStates - 1u) + 1u];

static void FblCheckProgrammingRequest(void);
#if defined( FBL_ENABLE_STAY_IN_BOOT )
static void FblPostProcessStartMsg( vuintx startMsgResult );
static void FblRepeatCheckForStartMsg(void);
#endif

static void FblInitPowerOn(void);
static void FblInit( vuint8 initposition );
static void FblDeinit(void);
static void FblRepeat(void);

static void FblCheckProgrammingRequest(void){
   switch(ApplFblExtProgRequest()){
      case kProgRequest:
      {
         FblMainSetStartFromAppl();
         break;
      }
      case kProgRequestXcp:
      {
         FblMainSetStartFromXcp();
         break;
      }
#if defined( FBL_ENABLE_STAY_IN_BOOT )
      case kCheckStayInBootRequest:
      {
         FblMainSetWaitStartMessage();
         break;
      }
#endif
#if defined( FBLBM_ENABLE_SECURE_BOOT )
#if defined ( FBLBM_ENABLE_SECBOOT_FBL_INIT_KEY )
      case kInitKeysRequest:
#endif
#if defined( FBLBM_ENABLE_SECBOOT_FBL_INIT_MAC )
      case kInitMacsRequest:
#endif
#endif
      case kNoProgRequest:
      default:
      {
         FblMainSetStartFromReset();
         break;
      }
   }
}

#if defined( FBL_ENABLE_STAY_IN_BOOT )
static void FblPostProcessStartMsg(vuintx startMsgResult){
   switch(startMsgResult){
      case kFblMainStartMessageReceived:
      {
         FblMainSetStartMessageReceived();
         break;
      }
      case kFblMainStartMessageTimeout:
      {
         {
#if defined( FBL_NO_JSR_APPL )
#   else
            CallApplStart();
#endif
         }
         break;
      }
      default:
      {
         assertFblInternal(0u, kFblSysAssertParameterOutOfRange);
         break;
      }
   }

}
#endif

static void FblInitPowerOn(void){
   vuintx i;

   FblInterruptDisable();
   assertFblGen(FblHeaderLocal == FblHeaderTable, kFblSysAssertParameterOutOfRange);

   for(i = 0u; i < (sizeof(fblMainStates)/sizeof(fblMainStates[0])); i++){
      fblMainStates[i] = (tFblStateBitmap)0x00u;
   }
#if defined( FBL_ENABLE_STAY_IN_BOOT )
   startMessageDelay = 0u;
#endif

   ClrWDInit();

#if( FBL_CW_API_REFERENCE_VERSION_MAJOR == 0x02u )
   FblCw_InitMemory();
#else
   FblCwClrInit();
#endif

   FblDiagInitPowerOn();
   MemDriver_InitPowerOn();
   FblLbtInitPowerOn();

#if defined( FBL_ENABLE_SECMOD_VECTOR )
   (void)SecM_InitPowerOn(V_NULL);
#endif

}

static void FblInit( vuint8 initposition ){
   ApplFblStartup(kFblInitPreCallback | initposition);

   switch(initposition){
      case kFblInitBaseInitialization:
      {
#if defined( FBL_ENABLE_PRE_WDINIT )

         FblInitWatchdog();
#endif
#if defined( FBL_ENABLE_PRE_TIMERINIT )

         FblTimerInit();
#endif
         break;
      }

      case kFblInitFblCommunication:
      {
#if !defined( FBL_ENABLE_PRE_WDINIT )

         FblInitWatchdog();
#endif
#if !defined( FBL_ENABLE_PRE_TIMERINIT )

         FblTimerInit();
#endif

#if( FBL_CW_API_REFERENCE_VERSION_MAJOR == 0x02u )
         FblCw_Init(FBL_CW_CFG_PTR);
#else
         FblCwInit();
#endif

         FblDiagInit();
         break;
      }

      case kFblInitFblFinalize:
      {
         FblDiagPostInit();

#if defined( FBLBM_ENABLE_SECURE_BOOT )
#if defined( FBLSB_ENABLE_GENERATE_CMAC ) || \
     defined( FBLSB_ENABLE_KEY_GENERATION_INTERN )

         FblSb_EcuMInit();
#endif
#endif
         break;
      }

      default:
      {
         assertFblInternal(0u, kFblSysAssertParameterOutOfRange);
         break;
      }
   }

   ApplFblStartup(kFblInitPostCallback | initposition);
}

static void FblDeinit(void){
#if( FBL_CW_API_REFERENCE_VERSION_MAJOR == 0x02u )
   FblCw_Deinit();
#else
   FblCwDeinit();
#endif

#if defined( FBL_WATCHDOG_ON )
   ApplFblWDLong();
#endif

   FblTimerStopp();
}

#if defined( FBL_ENABLE_STAY_IN_BOOT )
static void FblRepeatCheckForStartMsg(void){
   FblCwSetCheckForStartMsg();
   while(FblMainGetWaitStartMessage()){
      if((FblLookForWatchdog() & FBL_TM_TRIGGERED) == FBL_TM_TRIGGERED){
         startMessageDelay--;
         if(startMessageDelay == 0u){
            if(SUPPLIER1_GetFaultFlag() == 0){
              if(SUPPLIER1_CustomerSpecificValidityChecks() == FALSE){
                FblCwSetStartMsgReceived();
                ResetTesterTimeout();
              }
              else{
                FblMainClrWaitStartMessage();
                FblPostProcessStartMsg(kFblMainStartMessageTimeout);
              }
            }
         }
      }
      if(FblCwCheckStartMessage() == kFblOk){
         FblMainClrWaitStartMessage();
         FblPostProcessStartMsg(kFblMainStartMessageReceived);
      }
   }
   FblCwClrCheckForStartMsg();
}
#endif

static void FblRepeat(void){
   while(!FblMainGetFblShutdownRequest()){
      if((FblLookForWatchdog() & FBL_TM_TRIGGERED) == FBL_TM_TRIGGERED){
          FblDiagTimerTask();
#if defined( FBL_ENABLE_APPL_TIMER_TASK )
            ApplFblTask();
#endif
      }
      FblDiagStateTask();
      FblCwIdleTask();
#if defined( FBL_ENABLE_APPL_STATE_TASK )
      ApplFblStateTask();
#endif
   }
}

#if defined( FBLMAIN_ENABLE_STANDALONE_MODE )
int V_API_NEAR main(void){
  return fblmain();
}
#endif

int V_API_NEAR fblmain(void){
   FblInitPowerOn();
   FblInit(kFblInitBaseInitialization);
   FblCheckProgrammingRequest();
   FblInit(kFblInitFblCommunication);

#if defined( FBL_ENABLE_STAY_IN_BOOT )
   FblRepeatCheckForStartMsg();
#endif

   FblInit(kFblInitFblFinalize);
   FblRepeat();
   FblDeinit();
   ApplFblReset();

   return 0;
}

