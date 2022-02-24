//#include "AUTOSAR_Cfg.h"
#include "module.h"
#include "StartUp_EcuM.h"
#include "StartUp_SchM.h"

#include "EcuM_StartUp.h"

#define _ReSIM 0

typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

class module_StartUp:
      public abstract_module
   ,  public interface_StartUp_EcuM
   ,  public interface_StartUp_SchM
{
   public:
      FUNC(void, STARTUP_CODE) InitFunction   (void);
      FUNC(void, STARTUP_CODE) DeInitFunction (void);
      FUNC(void, STARTUP_CODE) MainFunction   (void);
};

module_StartUp StartUp;

interface_StartUp_EcuM *EcuM_Client_ptr_StartUp = &StartUp;
interface_StartUp_SchM *SchM_Client_ptr_StartUp = &StartUp;

FUNC(void, STARTUP_CODE) InitFunction(void){
}

FUNC(void, STARTUP_CODE) DeInitFunction(void){
}

FUNC(void, STARTUP_CODE) MainFunction(void){
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

   StartUp_Client_ptr_EcuM->InitFunction();

   return e_Shutdown;
}

