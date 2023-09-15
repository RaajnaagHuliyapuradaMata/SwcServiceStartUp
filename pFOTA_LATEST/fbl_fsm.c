#include "fbl_fsm_inc.hpp"

#if( FBLLIB_FSM_VERSION != 0x0101u ) || \
    ( FBLLIB_FSM_RELEASE_VERSION != 0x01u )
# error "Error in FBL_FSM.C: Source and header file are inconsistent!"
#endif

typedef enum{
   kFsmIterateHierarchy_Disabled
   ,  kFsmIterateHierarchy_Enabled
}tFsmIterateHierarchy;

static void FblFsmHandleEvent( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event, tFsmIterateHierarchy iterate);
static vuint8 FblFsmGetStateHierachy( const V_MEMRAM1 tFblFsmContext V_MEMRAM2 V_MEMRAM3 * const pFsmContext, tFblFsmState state
   ,                                     V_MEMRAM1 tFblFsmState V_MEMRAM2 V_MEMRAM3 * hierarchy );

#if defined( FBL_FSM_ENABLE_DEBUGGING )
static tFblFsmInstance g_Instance;
#endif

static vuint8 FblFsmGetStateHierachy( const V_MEMRAM1 tFblFsmContext V_MEMRAM2 V_MEMRAM3 * const pFsmContext
   ,                                     tFblFsmState state
   ,                                     V_MEMRAM1 tFblFsmState V_MEMRAM2 V_MEMRAM3 * hierarchy ){
   vuint8 index;
   index = 0u;
   while(FBL_FSM_DEFAULT_STATE != state){
      if( (index >= FBL_FSM_MAX_HIERARCHY_DEPTH)
        || (state >= pFsmContext->stateCount))
      {
         FBL_FSM_DEBUG_ERROR_PRINT(pFsmContext->instance);
         index = 0u;
         state = FBL_FSM_DEFAULT_STATE;
      }
      else
      {
         hierarchy[index] = state;
         index++;
         state = pFsmContext->stateDefinitions[state].superState;
      }
   }

   return index;
}

static void FblFsmHandleEvent(
      tFblFsmContextPtr const pFsmContext
   ,  tFblFsmEvent            event
   ,  tFsmIterateHierarchy    iterate
){
             vuint16                                      index;
             vuint16                                      hierarchy;
             tFblFsmState                                 state;
             tFblFsmGuard                                 guard;
   V_MEMROM1 tFblFsmStateDefinition V_MEMROM2 V_MEMROM3 * stateDef;
   V_MEMROM1 tFblFsmEventEntry      V_MEMROM2 V_MEMROM3 * triggers;

   state     = pFsmContext->state;
   hierarchy = 0u;

   FBL_FSM_DEBUG_PRINT2(pFsmContext->instance, event, state);
   while(
         (FBL_FSM_DEFAULT_STATE != state)
      && (state < pFsmContext->stateCount)
   ){
      stateDef = &pFsmContext->stateDefinitions[state];
      triggers = stateDef->triggers;
      for(
         index = 0u;
         index < stateDef->triggerCount;
         index++
      ){
         if(
               (triggers[index].trigger == event)
            || (triggers[index].trigger == kFblFsmDefaultEvent_Any)
         ){
            guard = triggers[index].handler(pFsmContext, event);
            FBL_FSM_DEBUG_PRINT3(pFsmContext->instance, guard);
            if(kFblFsmGuard_False != guard){
               if(kFblFsmGuard_True == guard){
                  pFsmContext->pendingState = triggers[index].nextState;
               }
               else{
               }
               state = FBL_FSM_DEFAULT_STATE;
               break;
            }
            else{
            }
         }
      }
      if(FBL_FSM_DEFAULT_STATE != state){
         if(kFsmIterateHierarchy_Enabled == iterate){
            hierarchy++;
            if(hierarchy < FBL_FSM_MAX_HIERARCHY_DEPTH){
               state = stateDef->superState;
            }
            else{
               FBL_FSM_DEBUG_ERROR_PRINT(pFsmContext->instance);
               state = FBL_FSM_DEFAULT_STATE;
            }
         }
         else{
            state = FBL_FSM_DEFAULT_STATE;
         }
      }
   }

#if defined( FBL_FSM_ENABLE_DEBUGGING )
   if(
         (state >= pFsmContext->stateCount)
      && (FBL_FSM_DEFAULT_STATE != state)
   ){
      FBL_FSM_DEBUG_ERROR_PRINT(pFsmContext->instance);
   }
#endif
}

void FblFsmInitPowerOn(void){
#if defined( FBL_FSM_ENABLE_DEBUGGING )
   g_Instance = 0u;
#endif
}

void FblFsmInit( tFblFsmContextPtr const pFsmContext, tFblFsmState initialState ){
#if defined( FBL_FSM_ENABLE_DEBUGGING )
   pFsmContext->instance = g_Instance;
   g_Instance++;
#endif

   pFsmContext->state = FBL_FSM_DEFAULT_STATE;
   pFsmContext->pendingState = initialState;
   pFsmContext->pendingEvent = kFblFsmDefaultEvent_None;
   FblFsmStateTask(pFsmContext);
}

void FblFsmDeinit( tFblFsmContextPtr const pFsmContext ){
   pFsmContext->state = FBL_FSM_DEFAULT_STATE;
   pFsmContext->pendingState = FBL_FSM_DEFAULT_STATE;
   pFsmContext->pendingEvent = kFblFsmDefaultEvent_None;
}

void FblFsmStateTask( tFblFsmContextPtr const pFsmContext ){
   tFblFsmEvent   event;
   tFblFsmState   stateHierarchyExit[FBL_FSM_MAX_HIERARCHY_DEPTH];
   tFblFsmState   stateHierarchyEntry[FBL_FSM_MAX_HIERARCHY_DEPTH];
   tFblFsmState   currentState;
   tFblFsmState   pendingState;
   vsint8         index;
   vuint8         exitCount;
   vuint8         entryCount;
   vsint8         exitIndex;
   vsint8         entryIndex;
   event = pFsmContext->pendingEvent;
   if(kFblFsmDefaultEvent_None != event){
      pFsmContext->pendingEvent = kFblFsmDefaultEvent_None;
      FblFsmHandleEvent(pFsmContext, event, kFsmIterateHierarchy_Enabled);
   }

   while(FBL_FSM_DEFAULT_STATE != pFsmContext->pendingState){
      currentState = pFsmContext->state;
      pendingState = pFsmContext->pendingState;
      FBL_FSM_DEBUG_PRINT1(pFsmContext->instance, currentState, pendingState);
      pFsmContext->pendingState = FBL_FSM_DEFAULT_STATE;
      exitCount = FblFsmGetStateHierachy(pFsmContext, currentState, stateHierarchyExit);
      entryCount = FblFsmGetStateHierachy(pFsmContext, pendingState, stateHierarchyEntry);
      if(currentState == pendingState)
      {
         exitIndex = 0;
         entryIndex = 0;
      }
      else
      {
         exitIndex = (vsint8)(exitCount - 1);
         entryIndex = (vsint8)(entryCount - 1);
         while( (exitIndex >= 0)
               && (stateHierarchyExit[exitIndex] == stateHierarchyEntry[entryIndex]) )
         {
            exitIndex--;
            entryIndex--;
         }
      }
      for(index = 0; index <= exitIndex; index++)
      {
         pFsmContext->state = stateHierarchyExit[index];
         FblFsmHandleEvent(pFsmContext, kFblFsmDefaultEvent_Exit, kFsmIterateHierarchy_Disabled);
      }
      for(index = entryIndex; index >= 0; index--)
      {
         pFsmContext->state = stateHierarchyEntry[index];
         FblFsmHandleEvent(pFsmContext, kFblFsmDefaultEvent_Entry, kFsmIterateHierarchy_Disabled);
      }
      pFsmContext->state = pendingState;
   }
}

void FblFsmTriggerEvent( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event ){
   pFsmContext->pendingEvent = event;
}

tFblFsmGuard FblFsmEventHandlerDefault( tFblFsmContextPtr const pFsmContext, tFblFsmEvent event ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)pFsmContext;
   (void)event;
#endif
   return kFblFsmGuard_True;
}

