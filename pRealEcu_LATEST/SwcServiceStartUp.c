/******************************************************************************/
/* File   : SwcServiceStartUp.c                                               */
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

#include "infMcalAdcSwcApplEcuM.hpp"
#include "infMcalDioSwcApplEcuM.hpp"
#include "infMcalGptSwcApplEcuM.hpp"
#include "infMcalMcuSwcApplEcuM.hpp"
#include "infMcalWdgSwcApplEcuM.hpp"
#include "infSwcServiceEcuMSwcServiceStartUp.hpp"
#include "infSwcServiceNvMSwcApplEcuM.hpp"
#include "infSwcServiceOsSwcApplEcuM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
OS_MAIN(){
   infMcalGptSwcApplEcuM_InitFunction();
   infSwcServiceOsSwcApplEcuM_InitFunction();
   infMcalDioSwcApplEcuM_vInitFunction();
   infMcalAdcSwcApplEcuM_vInitFunction();
   infMcalMcuSwcApplEcuM_InitFunction();
   infMcalWdgSwcApplEcuM_InitFunction();
   infSwcServiceNvMSwcApplEcuM_InitFunction();
   infSwcServiceEcuMSwcServiceStartUp_InitFunction();
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
