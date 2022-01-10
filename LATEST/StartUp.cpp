//#include "AUTOSAR_Cfg.h"

#include "Std_Types.h"
#include "EcuM.h"

#define _ReSIM 0

typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

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

   EcuM.InitFunction();

   return e_Shutdown;
}

