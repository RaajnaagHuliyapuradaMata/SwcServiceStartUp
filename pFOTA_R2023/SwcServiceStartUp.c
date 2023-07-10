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

#include "SwcServiceStartUp.h"

#include "LibAutosar_StateMachine.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#define LibAutosar_mGetLengthArray(arr)        (sizeof(arr) / sizeof((arr)[0u])) //TBD: Move to LibAutosar

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      SwcServiceStartUp_eError_None
   ,  SwcServiceStartUp_eError_HeaderREAD_FAILED
   ,  SwcServiceStartUp_eError_HeaderMAGIC_FAILED
   ,  SwcServiceStartUp_eError_HeaderVERSION_FAILED
   ,  SwcServiceStartUp_eError_HeaderLENGTH_FAILED
   ,  SwcServiceStartUp_eError_VALIDITY_FAILED
   ,  SwcServiceStartUp_eError_FBL_BMHEADER_INCORRECT
   ,  SwcServiceStartUp_eError_FBL_VERIFICATION_FAILED
   ,  SwcServiceStartUp_eError_KEY_NOT_AVAILABLE
   ,  SwcServiceStartUp_eError_UpdaterSEARCH_INIT_FAILED
   ,  SwcServiceStartUp_eError_UpdaterSEARCH_NEXT_FINISHED
   ,  SwcServiceStartUp_eError_UpdaterHEADER_ADDRESS
   ,  SwcServiceStartUp_eError_UpdaterHEADER_READ_ERROR
   ,  SwcServiceStartUp_eError_UpdaterHEADER_CONSISTENCY
   ,  SwcServiceStartUp_eError_UpdaterHEADER_TYPE
   ,  SwcServiceStartUp_eError_UpdaterBLOCK_VALIDITY
   ,  SwcServiceStartUp_eError_UpdaterHEADER_CMAC_READ
   ,  SwcServiceStartUp_eError_UpdaterHEADER_CMAC_VERIFY
   ,  SwcServiceStartUp_eError_UpdaterVERIFY
   ,  SwcServiceStartUp_eError_LoaderPOINTER_NULL
   ,  SwcServiceStartUp_eError_LoaderTOO_LARGE
   ,  SwcServiceStartUp_eError_LoaderSIZE
   ,  SwcServiceStartUp_eError_LoaderGET_MAC
   ,  SwcServiceStartUp_eError_LoaderGET_FBL_MAC
   ,  SwcServiceStartUp_eError_ReProgLoaderDESCR
   ,  SwcServiceStartUp_eError_ReProgLoaderINVALID
   ,  SwcServiceStartUp_eError_ReProgLoaderBMHEADER_INCORRECT
   ,  SwcServiceStartUp_eError_ReProgLoaderVERIFY_HEADER
   ,  SwcServiceStartUp_eError_ReProgLoaderVERIFY_AREAS
   ,  SwcServiceStartUp_eError_ReProgLoaderMAGIC_FLAG
   ,  SwcServiceStartUp_eError_ReProgLoaderBLOCK_COUNT
   ,  SwcServiceStartUp_eError_TargetLIST_INIT
   ,  SwcServiceStartUp_eError_TargetINVALID
   ,  SwcServiceStartUp_eError_TargetNO_VALID_HEADER
   ,  SwcServiceStartUp_eError_TargetVERIFICATION_FAILED
   ,  SwcServiceStartUp_eError_TargetINVALID_ADDRESS
   ,  SwcServiceStartUp_eError_TargetDEP_MANDATORY_MISSING
   ,  SwcServiceStartUp_eError_TargetDEP_NO_VALID_HEADER
   ,  SwcServiceStartUp_eError_TargetDEP_VERIFY_FAILED
   ,  SwcServiceStartUp_eError_END_OF_MAIN_REACHED
   ,  SwcServiceStartUp_eError_ApplCheckMAC_READ_FAIL
   ,  SwcServiceStartUp_eError_ApplCheckMAC_BUF_LENGTH
   ,  SwcServiceStartUp_eError_ApplCheckMAC_READ_FAIL_LENGTH
}Type_SwcServiceStartUp_eError;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
static const Type_LibAutosarStateMachine_stInfoState CfgSwcServiceStartUp_castTableMachineStates[] = { //TBD: Move to Cfg
   0
/*
      {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_PowerOn)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_Init)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckSwcServiceStartUpValidity)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterEnabled)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterSearchInit)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterCheck)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_FailsafeUpdaterSearchNext)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallFailsafeUpdater)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_SecureBootEnabled)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckKeyAvailability)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallSwcServiceStartUpInitKey)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_InitSwcServiceStartUpMacEnabled)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckSwcServiceStartUpMacErased)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallSwcServiceStartUpInitCmac)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_StayInBootEnabled)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckApplStartFlag)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckSwcServiceStartUpLbt)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckReprogFlag)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_ReprogLbtEnabled)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckReprogLbt)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_TargetListInit)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_TargetCheck)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_TargetListNext)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallTarget)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckSwcServiceStartUpVerification)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CheckSwcServiceStartUpVerificationStayInBoot)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallSwcServiceStartUp)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_CallSwcServiceStartUpStayInBoot)}
   ,  {FBL_FSM_DEFAULT_STATE, FBLBM_SIZE_AND_ARRAY(g_BmState_Fail)}
*/
};

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
static Type_LibAutosarStateMachine_tContext tContextStateMachine; //TBD: Local scope?

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void LibAutosarStateMachine_vHookError(Type_SwcServiceStartUp_eError leError){
   UNUSED(leError);
   while(1){
      ;
   }
}

int main(void){ /*BootManager*/
   tContextStateMachine.pcstInfoState = CfgSwcServiceStartUp_castTableMachineStates;
   tContextStateMachine.u16NumStates  = LibAutosar_mGetLengthArray(CfgSwcServiceStartUp_castTableMachineStates);

   LibAutosarStateMachine_vInitFunction(
        &tContextStateMachine
      ,  LibAutosarStateMachine_eStatePowerOn
   );

   while(
         tContextStateMachine.eState
      != LibAutosarStateMachine_eStateFail
   ){
      LibAutosarStateMachine_vTriggerEvent(
            &tContextStateMachine
         ,  LibAutosarStateMachine_eEventContinue
      );
      LibAutosarStateMachineState_vRunnable(&tContextStateMachine);
   }
   LibAutosarStateMachine_vHookError(SwcServiceStartUp_eError_END_OF_MAIN_REACHED); //TBD: Det
   return 0;
}

/*
int fblmain(void){ //Bootloader
   SwcServiceStartUpInitPowerOn();
   SwcServiceStartUpInit(kSwcServiceStartUpInitBaseInitialization);
   SwcServiceStartUpCheckProgrammingRequest();
   SwcServiceStartUpInit(kSwcServiceStartUpInitSwcServiceStartUpCommunication);
#ifdef(FBL_ENABLE_STAY_IN_BOOT)
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

