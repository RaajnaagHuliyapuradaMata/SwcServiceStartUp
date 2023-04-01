/******************************************************************************/
/* File   : Template.hpp                                                      */
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
#include "bootrom.hpp"
#include "wdt1.hpp"
#include "cmsis_misra.hpp"

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
#ifndef UNIT_TESTING_LV2
  bool  (*const USER_CFLASH_WR_PROT_EN)   (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_WR_PROT_EN;
  bool  (*const USER_CFLASH_WR_PROT_DIS)  (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_WR_PROT_DIS;
  bool  (*const USER_CFLASH_RD_PROT_EN)   (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_RD_PROT_EN;
  bool  (*const USER_CFLASH_RD_PROT_DIS)  (const uint16 cflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_CFLASH_RD_PROT_DIS;
  bool  (*const USER_DFLASH_WR_PROT_EN)   (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_WR_PROT_EN;
  bool  (*const USER_DFLASH_WR_PROT_DIS)  (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_WR_PROT_DIS;
  bool  (*const USER_DFLASH_RD_PROT_EN)   (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_RD_PROT_EN;
  bool  (*const USER_DFLASH_RD_PROT_DIS)  (const uint16 dflash_pw)                                                         = (bool  (*)(const uint16)) addr_USER_DFLASH_RD_PROT_DIS;
  uint8 (*const USER_OPENAB)              (const uint32 NVMPAGEAddr)                                                       = (uint8 (*)(const uint32)) addr_USER_OPENAB;
  uint8 (*const USER_PROG)                (const uint8 PROG_FLAG)                                                          = (uint8 (*)(const uint8)) addr_USER_PROG;
  uint8 (*const USER_ERASEPG)             (const uint32 *NVMPageAddr, const uint8 XRAM_RTNE_BRNCHNG)                      = (uint8 (*)(const uint32 *, const uint8)) addr_USER_ERASEPG;
  bool  (*const USER_ABORTPROG)           (void)                                                                           = (bool  (*)(void)) addr_USER_ABORTPROG;
  bool  (*const USER_NVMRDY)              (void)                                                                           = (bool  (*)(void)) addr_USER_NVMRDY;
  uint8 (*const USER_READ_CAL)            (const uint8 NumOfBytes, const uint8 CSAddr, const uint16 RAMAddr)               = (uint8 (*)(const uint8, const uint8, const uint16)) addr_USER_READ_CAL;
  bool  (*const USER_NVM_CONFIG)          (const uint8 *NVMSize, const uint8 *MapRAMSize)                                = (bool  (*)(const uint8 *, const uint8 *)) addr_USER_NVM_CONFIG;
  uint8 (*const USER_NVM_ECC2ADDR)        (const uint16 *ecc2addr)                                                        = (uint8 (*)(const uint16 *)) addr_USER_NVM_ECC2ADDR;
  uint8 (*const USER_MAPRAM_INIT)         (void)                                                                           = (uint8 (*)(void)) addr_USER_MAPRAM_INIT;
  bool  (*const USER_READ_100TP)          (const uint8 OTP_Page_Sel, const uint8 DataOffset, const uint32 *HundredTPData) = (bool  (*)(const uint8, const uint8, const uint32 *)) addr_USER_READ_100TP;
  uint8 (*const USER_100TP_PROG)          (const uint8 OTP_Page_Sel)                                                       = (uint8 (*)(const uint8)) addr_USER_100TP_PROG;
  uint8 (*const USER_ERASE_SECTOR)        (const uint32 NVMSectorAddr)                                                     = (uint8 (*)(const uint32)) addr_USER_ERASE_SECTOR;
  uint8 (*const USER_RAM_MBIST_START)     (const uint16 RAM_MBIST_Stop_Addr, const uint16 RAM_MBIST_Start_addr)            = (uint8 (*)(const uint16, const uint16)) addr_USER_RAM_MBIST_START;
  uint8 (*const USER_NVM_ECC_CHECK)       (void)                                                                           = (uint8 (*)(void)) addr_USER_NVM_ECC_CHECK;
  uint8 (*const USER_ECC_CHECK)           (const uint32 *ecc2addr)                                                         = (uint8 (*)(const uint32 *)) addr_USER_ECC_CHECK;
  #ifdef RTE_DEVICE_BF_STEP
    uint8 (*const USER_ERASE_SECTOR_VERIFY) (const uint32 sector_addr)                                                       = (uint8 (*)(const uint32)) addr_USER_ERASE_SECTOR_VERIFY;
    uint8 (*const USER_ERASEPG_VERIFY)      (const uint32 page_addr)                                                         = (uint8 (*)(const uint32)) addr_USER_ERASEPG_VERIFY;
    uint8 (*const USER_VERIFY_PAGE)         (const uint32 page_addr)                                                         = (uint8 (*)(const uint32)) addr_USER_VERIFY_PAGE;
  #endif
#endif

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
uint8 ProgramPage(uint32 addr, const uint8 *buf, uint8 Branch, uint8 Correct, uint8 FailPageErase){
  uint8 i;
  uint8 res;

  uint8 *pc = (uint8 *) addr;
  CMSIS_Irq_Dis();
  WDT1_SOW_Service(1u);
  res = USER_OPENAB(addr);
  (void)WDT1_Service();
  if(res == (uint8)0){
    for(i = 0u; i < (uint8)FlashPageSize; i++){
      pc[i] = buf[i];
    }
    WDT1_SOW_Service(1u);
    res = USER_PROG((uint8)(((FailPageErase & (uint8)1) << 2u) |
                            ((Correct & (uint8)1) << 1u) | (Branch & (uint8)1)));
    (void)WDT1_Service();
  }
  CMSIS_Irq_En();
   return(res);
}

bool GetCustomerID(const TCustomerID *CustID){
  bool res;
  CMSIS_Irq_Dis();
  WDT1_SOW_Service(1u);
  res = USER_READ_100TP((uint8)0x11, (uint8)0, (const uint32 *)CustID);
  (void)WDT1_Service();
  CMSIS_Irq_En();
   return(res);
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

