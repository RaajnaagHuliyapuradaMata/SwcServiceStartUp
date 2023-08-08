

#ifndef __FBL_FSM_H__
#define __FBL_FSM_H__

#define FBLLIB_FSM_VERSION           0x0101u
#define FBLLIB_FSM_RELEASE_VERSION   0x01u

#define FBL_FSM_DEFAULT_STATE          ((tFblFsmState)-1)

#define FBL_FSM_TRIGGER_NONE()                                    { FblFsmEventHandlerDefault, kFblFsmDefaultEvent_None,  FBL_FSM_DEFAULT_STATE }

#define FBL_FSM_TRIGGER_ENTRY(action)                             { (action),                  kFblFsmDefaultEvent_Entry, FBL_FSM_DEFAULT_STATE }

#define FBL_FSM_TRIGGER_EXIT(action)                              { (action),                  kFblFsmDefaultEvent_Exit,  FBL_FSM_DEFAULT_STATE }

#define FBL_FSM_TRIGGER_ANY(action, state)                        { (action),                  kFblFsmDefaultEvent_Any,   (state)               }

#define FBL_FSM_TRIGGER_INTERNAL(event, action)                   { (action),                  (event),                   FBL_FSM_DEFAULT_STATE }

#define FBL_FSM_TRIGGER_TRANSITION(event, state)                  { FblFsmEventHandlerDefault, (event),                   (state)               }

#define FBL_FSM_TRIGGER_TRANSITION_ACTION(event, action, state)   { (action),                  (event),                   (state)               }

#define FBL_FSM_TRIGGER_CHOICE(guard, state)                      { (guard),                   kFblFsmDefaultEvent_Entry, (state)               }

#define FBL_FSM_TRIGGER_CHOICE_ELSE(state)                        { FblFsmEventHandlerDefault, kFblFsmDefaultEvent_Entry, (state)               }

#define FBL_FSM_TRIGGER_UNCONDITIONAL(state)                      { FblFsmEventHandlerDefault, kFblFsmDefaultEvent_Entry, (state)               }

#define FBL_FSM_TRIGGER_UNCONDITIONAL_ACTION(action, state)       { (action),                  kFblFsmDefaultEvent_Entry, (state)               }

typedef vuint16 tFblFsmState;

typedef vuint16 tFblFsmEvent;

#if defined( FBL_FSM_ENABLE_DEBUGGING )

typedef vuint8 tFblFsmInstance;
#endif

typedef enum{
   kFblFsmDefaultEvent_None,
   kFblFsmDefaultEvent_Entry,
   kFblFsmDefaultEvent_Exit,
   kFblFsmDefaultEvent_Any,

   kFblFsmDefaultEvent_Count
}tFblFsmDefaultEvents;

typedef enum{
   kFblFsmGuard_True,
   kFblFsmGuard_False,
   kFblFsmGuard_Overwrite
}tFblFsmGuard;

typedef struct sFblFsmContext tFblFsmContext;

typedef V_MEMRAM1 tFblFsmContext V_MEMRAM2 V_MEMRAM3 * tFblFsmContextPtr;

typedef tFblFsmGuard (* tFblFsmEventHandler)( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event );

typedef struct{
   tFblFsmEventHandler  handler;
   tFblFsmEvent         trigger;
   tFblFsmState         nextState;
}tFblFsmEventEntry;

typedef struct{
   tFblFsmState   superState;
   vuint16        triggerCount;

   V_MEMROM1 tFblFsmEventEntry V_MEMROM2 V_MEMROM3 * triggers;
}tFblFsmStateDefinition;

struct sFblFsmContext
{
   V_MEMROM1 tFblFsmStateDefinition V_MEMROM2 V_MEMROM3 * stateDefinitions;
   vuint16           stateCount;
   tFblFsmState      state;
   tFblFsmState      pendingState;
   tFblFsmEvent      pendingEvent;
#if defined( FBL_FSM_ENABLE_DEBUGGING )
   tFblFsmInstance   instance;
#endif
};

#if defined( __cplusplus )
extern "C" {
#endif

void FblFsmInitPowerOn( void );
void FblFsmInit( tFblFsmContextPtr const pFsmContext, tFblFsmState initialState );
void FblFsmDeinit( tFblFsmContextPtr const pFsmContext );
void FblFsmStateTask( tFblFsmContextPtr const pFsmContext );
void FblFsmTriggerEvent( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event );
tFblFsmGuard FblFsmEventHandlerDefault( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event );

#if defined( __cplusplus )
}
#endif

#endif

