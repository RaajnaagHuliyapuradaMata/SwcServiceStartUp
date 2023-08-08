

#ifndef __FBL_FSM_CFG_H__
#define __FBL_FSM_CFG_H__

#define FBL_FSM_MAX_HIERARCHY_DEPTH    8u

#define FBL_FSM_DISABLE_DEBUGGING

#if defined( FBL_FSM_ENABLE_DEBUGGING )
# include <stdio.h>
#endif

#if defined( FBL_FSM_ENABLE_DEBUGGING )

# define FBL_FSM_DEBUG_PRINT1(instance, currentState, pendingState)  (void)printf("Fsm%d: St %d -> %d\n", instance, currentState, pendingState)
# define FBL_FSM_DEBUG_PRINT2(instance, event, state)                (void)printf("Fsm%d: Ev %d/St %d\n", instance, event, state)
# define FBL_FSM_DEBUG_PRINT3(instance, guard)                       (void)printf("Fsm%d: Gu %d\n", instance, guard)
# define FBL_FSM_DEBUG_ERROR_PRINT(instance)                         (void)printf("Fsm%d: ERROR at %s:%d\n", instance, __FUNCTION__, __LINE__)
#else
# define FBL_FSM_DEBUG_PRINT1(instance, currentState, pendingState)
# define FBL_FSM_DEBUG_PRINT2(instance, event, state)
# define FBL_FSM_DEBUG_PRINT3(instance, guard)
# define FBL_FSM_DEBUG_ERROR_PRINT(instance)
#endif

#endif

