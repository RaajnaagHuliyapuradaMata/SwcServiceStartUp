

#ifndef FBL_MAIN_H
#define FBL_MAIN_H

#include "fbl_main_types.hpp"

#define FBL_MAIN_VERSION           0x0402u
#define FBL_MAIN_RELEASE_VERSION   0x00u

#define kFblMainStateStartFromReset             0u
#define kFblMainStateStartFromAppl              1u
#define kFblMainStateStartFromXcp               2u
#define kFblMainStateApplicationValid           3u
#define kFblMainStateWaitStartMessage           4u
#define kFblMainStateStartMessageReceived       5u
#define kFblMainStateFblShutdownRequest         6u

#define kFblMainNumberOfStates                  7u

#define GetFblMainState(state)                  FBL_STATE_TEST(fblMainStates, (state))
#define SetFblMainState(state)                  FBL_STATE_SET(fblMainStates, state)
#define ClrFblMainState(state)                  FBL_STATE_CLR(fblMainStates, state)

#define FblMainGetStartFromReset()              GetFblMainState( kFblMainStateStartFromReset )
#define FblMainGetStartFromAppl()               GetFblMainState( kFblMainStateStartFromAppl )
#define FblMainGetStartFromXcp()                GetFblMainState( kFblMainStateStartFromXcp )
#define FblMainGetApplicationValid()            GetFblMainState( kFblMainStateApplicationValid )
#define FblMainGetWaitStartMessage()            GetFblMainState( kFblMainStateWaitStartMessage )
#define FblMainGetStartMessageReceived()        GetFblMainState( kFblMainStateStartMessageReceived )
#define FblMainGetFblShutdownRequest()          GetFblMainState( kFblMainStateFblShutdownRequest )

#define FblMainSetFblShutdownRequest()          SetFblMainState( kFblMainStateFblShutdownRequest )
#define FblMainClrFblShutdownRequest()          ClrFblMainState( kFblMainStateFblShutdownRequest )
#define FblSetShutdownRequest()                 FblMainSetFblShutdownRequest()

#define kFblInitPowerOn                      0x00u
#define kFblInitBaseInitialization           0x01u
#define kFblInitFblCommunication             0x02u
#define kFblInitFblFinalize                  0x03u

#define kFblInitPreCallback                  0x00u
#define kFblInitPostCallback                 0x80u

#if !defined( FBL_CW_API_REFERENCE_VERSION_MAJOR )

#define FBL_CW_API_REFERENCE_VERSION_MAJOR     0x01u

#define FBL_CW_API_REFERENCE_VERSION_MINOR     0x00u

#define FBL_CW_API_REFERENCE_VERSION_RELEASE   0x00u
#endif

#if !defined( FBL_CW_CFG_PTR )
#define FBL_CW_CFG_PTR V_NULL
#endif

V_MEMRAM0 extern V_MEMRAM1_NEAR tFblStateBitmap V_MEMRAM2_NEAR fblMainStates[FBL_STATE_INDEX(kFblMainNumberOfStates - 1u) + 1u];

#define FBLHEADER_START_SEC_CONST
#include "MemMap.hpp"
V_MEMROM0 extern V_MEMROM1 tFblHeader V_MEMROM2 FblHeader;
#define FBLHEADER_STOP_SEC_CONST
#include "MemMap.hpp"

int V_API_NEAR fblmain(void);

#if defined( kDiagCallCycle )
#if( kDiagCallCycle != 1u )
#   error "Diagnostic task call cycle has to be configured to 1ms."
#endif
#endif

#endif

