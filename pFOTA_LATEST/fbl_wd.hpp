

#ifndef __FBL_WD_H__
#define __FBL_WD_H__

#define FBLWD_VERSION            0x0301u
#define FBLWD_RELEASE_VERSION    0x00u

#define FBL_NO_TRIGGER     0x00u
#define FBL_WD_TRIGGERED   0x03u
#define FBL_TM_TRIGGERED   0x02u

#define GetWDInit()        (WDInitFlag == 0x01u)
#define SetWDInit()        (WDInitFlag = 0x01u)
#define ClrWDInit()        (WDInitFlag = 0x00u)

#define wdGenericEventTimer P2Timer

#define GetP2Timer()       (P2Timer)
#define SetP2Timer(val)    (P2Timer = (val))
#define ClrP2Timer()       (P2Timer = 0x00u)

V_MEMRAM0 extern V_MEMRAM1 vuint16 V_MEMRAM2 P2Timer;
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 WDInitFlag;

#if defined( FBL_WATCHDOG_ON )
#if( FBL_WATCHDOG_TIME > 255u )
typedef vuint16 tWdTime;
#else
typedef vuint8 tWdTime;
#endif

V_MEMRAM0 extern V_MEMRAM1 tWdTime V_MEMRAM2 WDTimer;
#endif

#define FBLWD_INIT_START_SEC_CODE
#include "MemMap.hpp"
void V_API_NEAR FblInitWatchdog (void);
#define FBLWD_INIT_STOP_SEC_CODE
#include "MemMap.hpp"

#define FBLWD_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"
void V_API_NEAR FblLookForWatchdogVoid(void);
#define FBLWD_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

#define FBLWD_RAMCODE_START_SEC_CODE
#include "MemMap.hpp"
vuint8 V_API_NEAR FblLookForWatchdog(void);
#define FBLWD_RAMCODE_STOP_SEC_CODE
#include "MemMap.hpp"

#endif

