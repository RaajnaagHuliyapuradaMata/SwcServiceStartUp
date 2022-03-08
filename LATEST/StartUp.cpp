/*****************************************************/
/* File   : StartUp.cpp                              */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "module.h"
#include "StartUp_EcuM.h"
#include "StartUp_SchM.h"

#include "EcuM_StartUp.h"

/*****************************************************/
/* #DEFINES                                          */
/*****************************************************/
#define _ReSIM 0

/*****************************************************/
/* MACROS                                            */
/*****************************************************/

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/
typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

class module_StartUp:
      public abstract_module
{
   public:
      FUNC(void, STARTUP_CODE) InitFunction   (void);
      FUNC(void, STARTUP_CODE) DeInitFunction (void);
      FUNC(void, STARTUP_CODE) MainFunction   (void);
};

/*****************************************************/
/* CONSTS                                            */
/*****************************************************/

/*****************************************************/
/* PARAMS                                            */
/*****************************************************/

/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
module_StartUp StartUp;
infEcuMClient* gptrinfEcuMClient_StartUp = &StartUp;
infSchMClient* gptrinfSchMClient_StartUp = &StartUp;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
FUNC(void, STARTUP_CODE) module_StartUp::InitFunction(void){
}

FUNC(void, STARTUP_CODE) module_StartUp::DeInitFunction(void){
}

FUNC(void, STARTUP_CODE) module_StartUp::MainFunction(void){
}

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

/*****************************************************/
/* EOF                                               */
/*****************************************************/

