/******************************************************************************/
/* File   : StartUp.cpp                                                       */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.hpp"
#include "infStartUp_EcuM.hpp"
#include "infStartUp_Dcm.hpp"
#include "infStartUp_SchM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define STARTUP_AR_RELEASE_MAJOR_VERSION                                       4
#define STARTUP_AR_RELEASE_MINOR_VERSION                                       3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(STARTUP_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION)
   #error "Incompatible STARTUP_AR_RELEASE_MAJOR_VERSION!"
#endif

#if(STARTUP_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)
   #error "Incompatible STARTUP_AR_RELEASE_MINOR_VERSION!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_StartUp:
      public abstract_module
{
   public:
      module_StartUp(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, STARTUP_CODE) InitFunction   (void);
      FUNC(void, STARTUP_CODE) DeInitFunction (void);
      FUNC(void, STARTUP_CODE) MainFunction   (void);
};

extern VAR(module_StartUp, STARTUP_VAR) StartUp;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, STARTUP_VAR, STARTUP_CONST) gptrinfEcuMClient_StartUp = &StartUp;
CONSTP2VAR(infDcmClient,  STARTUP_VAR, STARTUP_CONST) gptrinfDcmClient_StartUp  = &StartUp;
CONSTP2VAR(infSchMClient, STARTUP_VAR, STARTUP_CONST) gptrinfSchMClient_StartUp = &StartUp;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
//#include "CfgStartUp.hpp"

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_StartUp, STARTUP_VAR) StartUp(
   {
         0x0000
      ,  0xFFFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, STARTUP_CODE) module_StartUp::InitFunction(void){
   StartUp.IsInitDone = E_OK;
}

FUNC(void, STARTUP_CODE) module_StartUp::DeInitFunction(void){
   StartUp.IsInitDone = E_NOT_OK;
}

FUNC(void, STARTUP_CODE) module_StartUp::MainFunction(void){
}

typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

#include "infEcuM_StartUp.hpp"

#define _ReSIM                                                                 0

int main(
#if(_ReSIM == STD_ON)
#else
   void
#endif
){
#if(_ReSIM == STD_ON)
//   std::cout<<argv[0]<<" Version: "<<AUTOSAR_VERSION_MAJOR<<"."<<AUTOSAR_VERSION_MINOR<<std::endl;
#else
#endif

   gptrinfEcuMClient_EcuM->InitFunction();

   return e_Shutdown;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

