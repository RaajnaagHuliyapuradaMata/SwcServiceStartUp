/******************************************************************************/
/* File   : StartUp.cpp                                                       */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "infStartUp_EcuM.hpp"
#include "infStartUp_Dcm.hpp"
#include "infStartUp_SchM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define STARTUP_AR_RELEASE_VERSION_MAJOR                                       4
#define STARTUP_AR_RELEASE_VERSION_MINOR                                       3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(STARTUP_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible STARTUP_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(STARTUP_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible STARTUP_AR_RELEASE_VERSION_MINOR!"
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
      FUNC(void, STARTUP_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, STARTUP_CONFIG_DATA, STARTUP_APPL_CONST) lptrCfgModule
      );
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
#include "CfgStartUp.hpp"

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_StartUp, STARTUP_VAR) StartUp(
   {
         STARTUP_AR_RELEASE_VERSION_MAJOR
      ,  STARTUP_AR_RELEASE_VERSION_MINOR
      ,  0x00
      ,  0xFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, STARTUP_CODE) module_StartUp::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, STARTUP_CONFIG_DATA, STARTUP_APPL_CONST) lptrCfgModule
){
#if(STD_ON == StartUp_InitCheck)
   if(E_OK == IsInitDone){
#if(STD_ON == StartUp_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
      if(NULL_PTR == lptrCfgModule){
#if(STD_ON == StartUp_DevErrorDetect)
         Det_ReportError(
         );
#endif
      }
      else{
         if(STD_LOW){
// check lptrCfgModule for memory faults
            lptrCfg = lptrCfgModule;
         }
         else{
// use PBcfgCanIf as back-up configuration
//            lptrCfg = &PBcfgStartUp;
         }
      }
      IsInitDone = E_OK;
#if(STD_ON == StartUp_InitCheck)
   }
#endif
}

FUNC(void, STARTUP_CODE) module_StartUp::DeInitFunction(void){
#if(STD_ON == StartUp_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == StartUp_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
      IsInitDone = E_NOT_OK;
#if(STD_ON == StartUp_InitCheck)
   }
#endif
}

FUNC(void, STARTUP_CODE) module_StartUp::MainFunction(void){
#if(STD_ON == StartUp_InitCheck)
   if(E_OK != IsInitDone){
#if(STD_ON == StartUp_DevErrorDetect)
      Det_ReportError(
      );
#endif
   }
   else{
#endif
#if(STD_ON == StartUp_InitCheck)
   }
#endif
}

typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

#include "infEcuM_StartUp.hpp"

#if(STD_ON == _ReSIM)
#include <iostream>
#include <fstream>
using namespace std;
using std::ios;
#else
#endif

int main(
#if(STD_ON == _ReSIM)
      int   argc
   ,  char* argv[]
#else
   void
#endif
){
#if(STD_ON == _ReSIM)
   if(1 >= argc){
      std::cout<<"USAGE: TBD"<<std::endl;
   }
   else{
      std::cout<<argv[0]<<" Version: "<<STARTUP_AR_RELEASE_VERSION_MAJOR<<"."<<STARTUP_AR_RELEASE_VERSION_MINOR<<std::endl;
      std::ifstream fin(
            argv[1]
         ,  ios::in
      );
      fin.close();
   }
#else
#endif

//   gptrinfEcuM_StartUp->InitFunction();

   return e_Shutdown;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

