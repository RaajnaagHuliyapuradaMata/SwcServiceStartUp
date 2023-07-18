/******************************************************************************/
/* File   : SwcServiceStartUp.c                                               */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.h"

#include "Types_SwcServiceStartUp.h"

#include "CfgSwcServiceStartUp.h"
#include "infSwcServiceDetSwcServiceStartUp.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static Type_LibAutosarStateMachine_tContext ltContextStateMachine;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
int main(void){ /*BootManager*/
   LibAutosarStateMachine_vInitFunction(
        &ltContextStateMachine
      ,  LibAutosarStateMachine_eStatePowerOn
      ,  CfgSwcServiceStartUp_dNumMachineStates
      ,  CfgSwcServiceStartUp_castTableMachineStates
   );

   while(
         ltContextStateMachine.eState
      != LibAutosarStateMachine_eStateFail
   ){
      LibAutosarStateMachine_vTriggerEvent(
           &ltContextStateMachine
         ,  LibAutosarStateMachine_eEventContinue
      );
      LibAutosarStateMachineState_vRunnable(&ltContextStateMachine);
   }
   SwcServiceDet_tReportError(
         SwcServiceDet_eIdModuleSwcServiceStartUp
      ,  infSwcServiceDetSwcServiceStartUp_dIdInstance_TBD
      ,  infSwcServiceDetSwcServiceStartUp_dIdApi_TBD
      ,  SwcServiceStartUp_eError_END_OF_MAIN_REACHED
   );
   return 0;
}

/*
int startupmain(void){ //Bootloader
   SwcServiceStartUpInitPowerOn();
   SwcServiceStartUpInit(kSwcServiceStartUpInitBaseInitialization);
   SwcServiceStartUpCheckProgrammingRequest();
   SwcServiceStartUpInit(kSwcServiceStartUpInitSwcServiceStartUpCommunication);
#ifdef(SWCSERVICESTARTUP_ENABLE_STAY_IN_BOOT)
   SwcServiceStartUpRepeatCheckForStartMsg();
#endif
   SwcServiceStartUpInit(kSwcServiceStartUpInitSwcServiceStartUpFinalize);
   SwcServiceStartUpRepeat();
   SwcServiceStartUpDeinit();
   ApplSwcServiceStartUpReset();
   return 0;
}
*/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

