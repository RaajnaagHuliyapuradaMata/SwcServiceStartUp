/******************************************************************************/
/* File   : ServiceStartUp.cpp                                                */
/*                                                                            */
/* Author : Nagaraja HULIYAPURADA MATA                                        */
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
/* All rights reserved. Copyright © 1982 Nagaraja HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/NagarajaHuliyapuradaMata?tab=repositories               */
/*                                                                            */
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
#define SERVICESTARTUP_AR_RELEASE_VERSION_MAJOR                                4
#define SERVICESTARTUP_AR_RELEASE_VERSION_MINOR                                3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(SERVICESTARTUP_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible SERVICESTARTUP_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(SERVICESTARTUP_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible SERVICESTARTUP_AR_RELEASE_VERSION_MINOR!"
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
VAR(module_ServiceStartUp, SERVICESTARTUP_VAR) ServiceStartUp;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, SERVICESTARTUP_CODE) module_ServiceStartUp::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, SERVICESTARTUP_CONST,       SERVICESTARTUP_APPL_CONST) lptrConstModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICESTARTUP_CONFIG_DATA, SERVICESTARTUP_APPL_CONST) lptrCfgModule
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
         ,  SERVICESTARTUP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICESTARTUP_CODE) module_ServiceStartUp::DeInitFunction(
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
         ,  SERVICESTARTUP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICESTARTUP_CODE) module_ServiceStartUp::MainFunction(
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
         ,  SERVICESTARTUP_E_UNINIT
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
      cout<<endl<<argv[0]<<" Version: R"<<SERVICESTARTUP_AR_RELEASE_VERSION_MAJOR<<"."<<SERVICESTARTUP_AR_RELEASE_VERSION_MINOR;
   }
#else
#endif

   ServiceEcuM.InitFunction();

   return e_Shutdown;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

