/******************************************************************************/
/* File   : SwcServiceStartUp.cpp                                             */
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
   return e_Shutdown;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

