/******************************************************************************/
/* File   : Template.hpp                                                      */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "types.hpp"

#include "tle987x.hpp"
#include "tle_device.hpp"
#include "Emo.hpp"
#include "Emo_RAM.hpp"
#include "adc1.hpp"
#include "wdt1.hpp"

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
//ADC1_Type    device_ADC1;
//ADC2_Type    device_ADC2;
//ADC34_Type   device_ADC34;
//BDRV_Type    device_BDRV;
//CCU6_Type    device_CCU6;
//CSA_Type     device_CSA;
//CPU_Type     device_CPU;
//DMA_Type     device_DMA;
//GPT12E_Type  device_GPT12E;
//LIN_Type     device_LIN;
//MF_Type      device_MF;
//MON_Type     device_MON;
//PMU_Type     device_PMU;
//PORT_Type    device_PORT;
//SCU_Type     device_SCU;
//SCUPM_Type   device_SCUPM;
//SSC1_Type    device_SSC1;
//SSC2_Type    device_SSC2;
//TIMER2x_Type device_TIMER2;
//TIMER2x_Type device_TIMER21;
//TIMER3_Type  device_TIMER3;
//UART_Type    device_UART1;
//UART_Type    device_UART2;

ADC1_Type    *ADC1;//    = &device_ADC1;
ADC2_Type    *ADC2;//    = &device_ADC2;
ADC34_Type   *ADC34;//   = &device_ADC34;
BDRV_Type    *BDRV;//    = &device_BDRV;
CCU6_Type    *CCU6;//    = &device_CCU6;
CSA_Type     *CSA;//     = &device_CSA;
CPU_Type     *CPU;//     = &device_CPU;
DMA_Type     *DMA;//     = &device_DMA;
GPT12E_Type  *GPT12E;//  = &device_GPT12E;
LIN_Type     *LIN;//     = &device_LIN;
MF_Type      *MF;//      = &device_MF;
MON_Type     *MON;//     = &device_MON;
PMU_Type     *PMU;//     = &device_PMU;
PORT_Type    *PORT;//    = &device_PORT;
SCU_Type     *SCU;//     = &device_SCU;
SCUPM_Type   *SCUPM;//   = &device_SCUPM;
SSC1_Type    *SSC1;//    = &device_SSC1;
SSC2_Type    *SSC2;//    = &device_SSC2;
TIMER2x_Type *TIMER2;//  = &device_TIMER2;
TIMER2x_Type *TIMER21;// = &device_TIMER21;
TIMER3_Type  *TIMER3;//  = &device_TIMER3;
UART_Type    *UART1;//   = &device_UART1;
UART_Type    *UART2;//   = &device_UART2;

static void Main_lStartMotor (void);
static void Main_lStopMotor  (void);
static void Poti_Handler     (void);

int main(void){
   TLE_Init();
   Emo_Init();
   while(1){
      (void)WDT1_Service();
      Poti_Handler();
   }
}

static void Main_lStartMotor(void){
   uint32 Error;
   Error = EMO_ERROR_NONE;
   if(Error == EMO_ERROR_NONE){
      Error = Emo_StartMotor((uint32)1u);
   }
   if(Error == EMO_ERROR_NONE){
      __NOP();
   }
   else{
      __NOP();
   }
}

static void Main_lStopMotor(void){
   uint32 Error;
   Error = Emo_StopMotor();
   if(Error != EMO_ERROR_NONE){
      __NOP();
   }
}

static void Poti_Handler(void){
   uint16 mV;
   if(
         true
      == ADC1_GetChResult_mV(&mV, ADC1_CH4)
   ){
      Emo_setspeedreferenz(mV / 2);
      if(mV > 1000){
         Main_lStartMotor();
      }
      else if(mV < 800){
         Main_lStopMotor();
      }
      else{}
   }
}

/*
void BDRV_Diag_Supply(void){
   Main_lStopMotor();
}

void BDRV_Diag(void){
   Main_lStopMotor();
}
*/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

