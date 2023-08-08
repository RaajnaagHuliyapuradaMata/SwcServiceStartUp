

#include "fbl_inc.hpp"

#if( FBLWD_VERSION != 0x0301u ) || \
    ( FBLWD_RELEASE_VERSION != 0x00u )
# error "Error in fbl_wd.c: Source and header file are inconsistent!"
#endif

#if( FBLWD_VERSION != _FBLWD_VERSION ) || \
    ( FBLWD_RELEASE_VERSION != _FBLWD_RELEASE_VERSION )
# error "Error in fbl_wd.c: Source and v_ver.h are inconsistent!"
#endif

# if !defined( kFblGenericEventMargin )
#  define kFblGenericEventMargin (kFblDiagTimeP2Star/2u)
# endif

# define PerformGenericEventAction()         \
   {                                         \
      if(GetRcrRpInProgress()               \
          )                                  \
      {                                      \
         FblCwRetransmitRP();                \
         SetP2Timer(kFblDiagTimeP2Star);     \
      }                                      \
   }

V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 P2Timer;
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 WDInitFlag;

#if defined( FBL_WATCHDOG_ON )
V_MEMRAM0 V_MEMRAM1 tWdTime V_MEMRAM2 WDTimer;

#endif

#define FBLWD_INIT_START_SEC_CODE
#include "MemMap.hpp"
void V_API_NEAR FblInitWatchdog( void ){
   wdGenericEventTimer = 0x00u;
   SetWDInit();

#if defined( FBL_DEF_ENABLE_NON_KB_MAIN )
   ApplFblWDInit();
#endif
}
#define FBLWD_INIT_STOP_SEC_CODE
#include "MemMap.hpp"

#define FBLWD_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"
void V_API_NEAR FblLookForWatchdogVoid( void ){
   (void)FblLookForWatchdog();
}
#define FBLWD_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

#define FBLWD_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"
vuint8 V_API_NEAR FblLookForWatchdog( void ){
   vuint8 retValue = FBL_NO_TRIGGER;

   if(GetWDInit()){
      if(FblTimerGet() != 0x00u)
      {
         FblTimerReset();
         retValue |= FBL_TM_TRIGGERED;

         if(wdGenericEventTimer > 0x00u)
         {
            wdGenericEventTimer--;
            if(wdGenericEventTimer < kFblGenericEventMargin)
            {
               PerformGenericEventAction();
            }
         }

# if defined( FBL_WATCHDOG_ON )
         if(WDTimer != 0x00u)
         {
            WDTimer--;
            if(WDTimer == 0x00u)
            {
               ApplFblWDTrigger();
               WDTimer = FBL_WATCHDOG_TIME;
               retValue |= FBL_WD_TRIGGERED;
            }
         }
# endif

         if(0u != FblCwIsTimerTaskAllowed())
         {
            FblCwTimerTask();
         }

# if defined( FBL_WD_TIMER_TASK )

         FBL_WD_TIMER_TASK();
# endif
      }
   }

   if(0u != FblCwIsStateTaskAllowed()){
      FblCwStateTask();
   }

# if defined( FBL_WD_STATE_TASK )

   FBL_WD_STATE_TASK();
# endif

   return retValue;
}
#define FBLWD_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

