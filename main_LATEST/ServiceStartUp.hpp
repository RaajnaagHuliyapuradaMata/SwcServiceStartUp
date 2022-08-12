#pragma once
/******************************************************************************/
/* File   : ServiceStartUp.hpp                                                       */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ConstServiceStartUp.hpp"
#include "CfgServiceStartUp.hpp"
#include "ServiceStartUp_core.hpp"
#include "infServiceStartUp_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_ServiceStartUp:
      INTERFACES_EXPORTED_SERVICESTARTUP
      public abstract_module
   ,  public class_ServiceStartUp_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstServiceStartUp_Type* lptrConst = (ConstServiceStartUp_Type*)NULL_PTR;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, SERVICESTARTUP_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, SERVICESTARTUP_CONST,       SERVICESTARTUP_APPL_CONST) lptrConstModule
         ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICESTARTUP_CONFIG_DATA, SERVICESTARTUP_APPL_CONST) lptrCfgModule
      );
      FUNC(void, SERVICESTARTUP_CODE) DeInitFunction (void);
      FUNC(void, SERVICESTARTUP_CODE) MainFunction   (void);
      SERVICESTARTUP_CORE_FUNCTIONALITIES
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern VAR(module_ServiceStartUp, SERVICESTARTUP_VAR) ServiceStartUp;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

