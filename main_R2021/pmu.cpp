/******************************************************************************/
/* File   : Template.hpp                                                      */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "types.hpp"

#include "pmu.hpp"

#include "tle987x.hpp"
#include "sfr_access.hpp"
#include "wdt1.hpp"
#include "cmsis_misra.hpp"
#include "pmu_defines.hpp"
#include "RTE_Components.hpp"

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
void PMU_Init(void){
#ifndef RTE_DEVICE_BF_STEP
#if((PMU_VDDEXT_CTRL & 1u) == 1u)
   (void)PMU_VDDEXT_On();
   PMU->VDDEXT_CTRL.reg = (uint8) PMU_VDDEXT_CTRL;
#else
   PMU->VDDEXT_CTRL.reg = (uint8) PMU_VDDEXT_CTRL;
#endif
#else
   PMU->VDDEXT_CTRL.reg = (uint8) PMU_VDDEXT_CTRL;
#endif
   PMU->CNF_CYC_SENSE.reg = (uint8) PMU_CNF_CYC_SENSE;
   PMU->CNF_CYC_SAMPLE_DEL.reg = (uint8) PMU_CNF_CYC_SAMPLE_DEL;
   PMU->CNF_CYC_WAKE.reg = (uint8) PMU_CNF_CYC_WAKE;
#if(CONFIGWIZARD == 1)
   PMU->CNF_PMU_SETTINGS.reg = (uint8) PMU_CNF_PMU_SETTING;
#else
   PMU->CNF_PMU_SETTINGS.reg = (uint8) PMU_CNF_PMU_SETTINGS;
#endif
   PMU->PMU_SUPPLY_STS.reg = (uint8) PMU_PMU_SUPPLY_STS;
   PMU->LIN_WAKE_EN.reg = (uint8) PMU_LIN_WAKE_EN;
   PMU->WAKE_CONF_GPIO0_CYC.reg = (uint8) PMU_WAKE_CONF_GPIO0_CYC;
   PMU->WAKE_CONF_GPIO0_FALL.reg = (uint8) PMU_WAKE_CONF_GPIO0_FALL;
   PMU->WAKE_CONF_GPIO0_RISE.reg = (uint8) PMU_WAKE_CONF_GPIO0_RISE;
   PMU->WAKE_CONF_GPIO1_CYC.reg = (uint8) PMU_WAKE_CONF_GPIO1_CYC;
   PMU->WAKE_CONF_GPIO1_FALL.reg = (uint8) PMU_WAKE_CONF_GPIO1_FALL;
   PMU->WAKE_CONF_GPIO1_RISE.reg = (uint8) PMU_WAKE_CONF_GPIO1_RISE;
   PMU->CNF_RST_TFB.reg = (uint8) PMU_CNF_RST_TFB;
   PMU->CNF_WAKE_FILTER.reg = (uint8) PMU_CNF_WAKE_FILTER;
}
/*
#ifdef RTE_DEVICE_BF_STEP
bool PMU_VDDEXT_On(void){
  bool bRet = false;
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_ENABLE_Pos, (uint8)PMU_VDDEXT_CTRL_ENABLE_Msk, 1u);
  Delay_us(200u);
  if(u1_Field_Rd8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_STABLE_Pos, (uint8)PMU_VDDEXT_CTRL_STABLE_Msk) == 1u){
    bRet = true;
  }
  return(bRet) ;
}
#else
bool PMU_VDDEXT_On(void){
  bool result;
  result = false;
  CMSIS_Irq_Dis();
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 0u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  PMU->VDDEXT_CTRL.reg = 1u;
  CMSIS_Irq_En();
  Delay_us(200u);
  if((PMU->VDDEXT_CTRL.reg & (uint8)PMU_VDDEXT_STABLE) == (uint8)PMU_VDDEXT_STABLE){
    result = true;
  }
  return(result);
}
#endif

void PMU_VDDEXT_Int_En(void){
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Pos, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Msk, 1u);
}

void PMU_VDDEXT_Int_Dis(void){
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Pos, (uint8)PMU_VDDEXT_CTRL_FAIL_EN_Msk, 0u);
}

void PMU_VDDC_Int_En(void){
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk, 1u);
}

void PMU_VDDC_Int_Dis(void){
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_1V5_FAIL_EN_Msk, 0u);
}

void PMU_VDDP_Int_En(void){
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk, 1u);
}

void PMU_VDDP_Int_Dis(void){
  Field_Mod8(&PMU->PMU_SUPPLY_STS.reg, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Pos, (uint8)PMU_PMU_SUPPLY_STS_PMU_5V_FAIL_EN_Msk, 0u);
}

uint8 PMU_Get_Reset_Status(void){
  return u8_Field_Rd8(&PMU->PMU_RESET_STS1.reg, 0u, 0xFFu);
}

void PMU_Clear_Reset_Status(void){
  Field_Wrt8all(&PMU->PMU_RESET_STS1.reg, 0u);
}

uint8 PMU_VDDEXT_Off(void){
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_ENABLE_Pos, (uint8)PMU_VDDEXT_CTRL_ENABLE_Msk, 0u);
  return u1_Field_Rd8(&PMU->VDDEXT_CTRL.reg, (uint8)PMU_VDDEXT_CTRL_STABLE_Pos, (uint8)PMU_VDDEXT_CTRL_STABLE_Msk);
}

void PMU_VDDEXT_Short_Clr(void){
  Field_Clr8(&PMU->VDDEXT_CTRL.reg, 0x08);
}

void PMU_VDDEXT_Set(uint8 FlagMask){
  Field_Mod8(&PMU->VDDEXT_CTRL.reg, 0u, (uint8)FlagMask, 0xFFu);
}
*/
/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

