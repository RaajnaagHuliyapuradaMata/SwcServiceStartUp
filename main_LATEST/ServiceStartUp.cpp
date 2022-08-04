/******************************************************************************/
/* File   : ServiceStartUp.cpp                                                       */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "ServiceStartUp.hpp"
#include "infServiceStartUp_Imp.hpp"

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

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_ServiceStartUp, STARTUP_VAR) ServiceStartUp;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, STARTUP_CODE) module_ServiceStartUp::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, STARTUP_CONST,       STARTUP_APPL_CONST) lptrConstModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   STARTUP_CONFIG_DATA, STARTUP_APPL_CONST) lptrCfgModule
){
#if(STD_ON == ServiceStartUp_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrConstModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrConst = (const ConstServiceStartUp_Type*)lptrConstModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == ServiceStartUp_DevErrorDetect)
         ServiceDet_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == ServiceStartUp_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == ServiceStartUp_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  STARTUP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, STARTUP_CODE) module_ServiceStartUp::DeInitFunction(
   void
){
#if(STD_ON == ServiceStartUp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServiceStartUp_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == ServiceStartUp_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  STARTUP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, STARTUP_CODE) module_ServiceStartUp::MainFunction(
   void
){
#if(STD_ON == ServiceStartUp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == ServiceStartUp_InitCheck)
   }
   else{
#if(STD_ON == ServiceStartUp_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  STARTUP_E_UNINIT
      );
#endif
   }
#endif
}

typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

#include "ServiceEcuM.hpp"

#if(STD_ON == _ReSIM)
#include <iostream>
using namespace std;
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
   if(0 >= argc){
      cout<<"USAGE: TBD"<<endl;
   }
   else{
      cout<<endl<<argv[0]<<" Version: R"<<STARTUP_AR_RELEASE_VERSION_MAJOR<<"."<<STARTUP_AR_RELEASE_VERSION_MINOR;
   }
#else
#endif

   ServiceEcuM.InitFunction();

   return e_Shutdown;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

