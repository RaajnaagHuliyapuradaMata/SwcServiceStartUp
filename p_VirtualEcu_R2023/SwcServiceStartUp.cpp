/******************************************************************************/
/* File   : SwcServiceStartUp.cpp                                             */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "SwcServiceStartUp.hpp"

#include "infSwcServiceEcuMSwcServiceStartUp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define OS_MAIN FUNC(int, SWCSERVICESTARTUP_CODE) main //TBD: move to Os.h

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
OS_MAIN(
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
      cout<<endl
          <<argv[0]
          <<" Version: R"
          <<STD_AR_RELEASE_VERSION_MAJOR
          <<"."
          <<STD_AR_RELEASE_VERSION_MINOR
          <<endl;
   }
#else
#endif

   infSwcServiceEcuMSwcServiceStartUp_InitFunction();
   infSwcServiceEcuMSwcServiceStartUp_DeInitFunction();

   return e_Shutdown;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

