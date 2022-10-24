/******************************************************************************/
/* File   : Template.hpp                                                      */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "types.hpp"

#include "tle_device.hpp"

#include "Mat.hpp" //TBD: remove
#include "ApplSwcFoc.hpp"

#include "wdt1.hpp"
#include "isr.hpp" //TBD: move to ISR

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
extern void Poti_Handler     (void); //To be moved as per architecture

int main(void){
   TLE_Init();
   Emo_Init();

   while(1){
      (void)WDT1_Service();
      Poti_Handler();
      GPT1_IRQHandler(); //TBD: move to ISR
   }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

