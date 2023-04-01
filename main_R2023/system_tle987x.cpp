/******************************************************************************/
/* File   : system_tle987x.cpp                                                */
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
#include "bsl_defines.hpp"
#include "scu.hpp"
#include "wdt1.hpp"
#include "tle_variants.hpp"

#include "system_tle987x.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if defined (__CC_ARM) || defined(__ARMCC_VERSION)
  #if(CONFIGWIZARD == 1)
    #if(NAC_NAD_EN == 1)
    const uint32 p_NACNAD __attribute__((section(sNADStart), used)) = (uint32)NAD_NAC;
    #endif
  #else
    #if(BSL_NAC_NAD_EN == 1u)
    const uint32 p_NACNAD __attribute__((section(sNADStart), used)) = (uint32)BSL_NAD_NAC;
    #endif
  #endif
#elif defined(__IAR_SYSTEMS_ICC__)
  #if(BSL_NAC_NAD_EN == 1u)
  const uint32 p_NACNAD @ "NACStart" = (uint32)BSL_NAD_NAC;
  #endif
#else
  #error Unsupported compiler!
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

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
void SystemInit(void){
  CPU.VTOR.reg   = ProgFlashStart;
  SCU_ClkInit();
  SysTick_Init();
  WDT1_Init();
  TIMER2->T2CON1.reg = 0;
  TIMER21->T2CON1.reg = 0;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

