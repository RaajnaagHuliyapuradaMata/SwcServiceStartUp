#pragma once
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


/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define FlashPageSize                   (128U)
#define FlashSectorSize                 (4096U)
#define addr_USER_CFLASH_WR_PROT_EN     (0x3925u)
#define addr_USER_CFLASH_WR_PROT_DIS    (0x391Du)
#define addr_USER_CFLASH_RD_PROT_EN     (0x3915u)
#define addr_USER_CFLASH_RD_PROT_DIS    (0x390Du)
#define addr_USER_DFLASH_WR_PROT_EN     (0x3905u)
#define addr_USER_DFLASH_WR_PROT_DIS    (0x38FDu)
#define addr_USER_DFLASH_RD_PROT_EN     (0x38F5u)
#define addr_USER_DFLASH_RD_PROT_DIS    (0x38EDu)
#define addr_USER_OPENAB                (0x38E5u)
#define addr_USER_PROG                  (0x38DDu)
#define addr_USER_ERASEPG               (0x38D5u)
#define addr_USER_ABORTPROG             (0x38CDu)
#define addr_USER_NVMRDY                (0x38C5u)
#define addr_USER_READ_CAL              (0x38BDu)
#define addr_USER_NVM_CONFIG            (0x38B5u)
#define addr_USER_NVM_ECC2ADDR          (0x38ADu)
#define addr_USER_MAPRAM_INIT           (0x389Du)
#define addr_USER_READ_100TP            (0x3875u)
#define addr_USER_100TP_PROG            (0x386Du)
#define addr_USER_ERASE_SECTOR          (0x3865u)
#define addr_USER_RAM_MBIST_START       (0x384Du)
#define addr_USER_NVM_ECC_CHECK         (0x3845u)
#define addr_USER_ECC_CHECK             (0x383Du)
#define addr_USER_ERASEPG_VERIFY        (0x3885u)
#define addr_USER_ERASE_SECTOR_VERIFY   (0x388Du)
#define addr_USER_VERIFY_PAGE           (0x3895u)
/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef union{
  uint32 reg;
  struct{
    uint32           : 8;
    uint32 Step      : 8;
    uint32 Clock     : 2;
    uint32 Package   : 2;
    uint32 SalesCode : 4;
    uint32 Family    : 8;
  }bit;
}TCustomerID;

typedef struct{
  uint8 offset;
  uint8 date;
}TData;

typedef struct{
  uint8 count;
  TData data[127];
}T100TP_Data;

typedef union{
  uint8   reg;
  struct{
    uint8 GlobFail  :  1;
    uint8 OffsetFail:  1;
    uint8 CustIDFail:  1;
    uint8           :  4;
    uint8 ExecFail  :  1;
  }bit;
}TUser_100TP_Prog;

typedef union{
  uint8   reg;
  struct{
    uint8 RAM_Branch   : 1;
    uint8 CorrAct      : 1;
  }bit;
}TProgFlag;

typedef union{
  uint8   reg;
  struct{
    uint8 GlobFail   :  1;
    uint8            :  3;
    uint8 VerifyFail :  1;
    uint8 EmergExit  :  1;
    uint8 SparePgFail:  1;
    uint8 ExecFail   :  1;
  }bit;
}TUser_Prog;

typedef union{
  uint8   reg;
  struct{
    uint8 ABFail   :  1;
    uint8          :  6;
    uint8 ExecFail :  1;
  }bit;
}TUser_OpenAB;

typedef union{
  uint8   reg;
  struct{
    uint8 GlobFail      :  1;
    uint8               :  4;
    uint8 DoubleMapping :  1;
    uint8 FaultyPage    :  1;
    uint8 ExecFail      :  1;
  }bit;
}TUser_MAPRAM_Init;

typedef union{
  uint8   reg;
  struct{
    uint8 SBE           :  1;
    uint8 DBE           :  1;
    uint8               :  5;
    uint8 ExecFail      :  1;
  }bit;
}TUser_NVM_ECC_Check;

typedef union{
  uint8   reg;
  struct{
    uint8 SBE           :  1;
    uint8 DBE           :  1;
    uint8               :  5;
    uint8 ExecFail      :  1;
  }bit;
}TUser_ECC_Check;

typedef union{
  uint8   reg;
  struct{
    uint8 GlobFail      :  1;
    uint8 VerifyFail    :  1;
    uint8               :  4;
    uint8 MapRAMFail    :  1;
    uint8 ExecFail      :  1;
  }bit;
}TUser_ERASE_SECTOR_VERIFY;

typedef union{
  uint8   reg;
  struct{
    uint8 GlobFail      :  1;
    uint8 VerifyFail    :  1;
    uint8               :  4;
    uint8 MapRAMFail    :  1;
    uint8 ExecFail      :  1;
  }bit;
}TUser_ERASEPG_VERIFY;

typedef union{
  uint8   reg;
  struct{
    uint8 GlobFail       :  1;
    uint8 VerifyEraseFail:  1;
    uint8 VerifyProgFail :  1;
    uint8                :  4;
    uint8 ExecFail       :  1;
  }bit;
}TUser_VERIFY_PAGE;

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
extern bool  USER_CFLASH_WR_PROT_EN   (uint16 cflash_pw);
extern bool  USER_CFLASH_WR_PROT_DIS  (uint16 cflash_pw);
extern bool  USER_CFLASH_RD_PROT_EN   (uint16 cflash_pw);
extern bool  USER_CFLASH_RD_PROT_DIS  (uint16 cflash_pw);
extern bool  USER_DFLASH_WR_PROT_EN   (uint16 dflash_pw);
extern bool  USER_DFLASH_WR_PROT_DIS  (uint16 dflash_pw);
extern bool  USER_DFLASH_RD_PROT_EN   (uint16 dflash_pw);
extern bool  USER_DFLASH_RD_PROT_DIS  (uint16 dflash_pw);
extern uint8 USER_OPENAB              (const uint32 NVMPAGEAddr);
extern uint8 USER_PROG                (const uint8 PROG_FLAG);
extern uint8 USER_ERASEPG             (const uint32 *NVMPageAddr, const uint8 XRAM_RTNE_BRNCHNG);
extern bool  USER_ABORTPROG           (void);
extern bool  USER_NVMRDY              (void);
extern uint8 USER_READ_CAL            (const uint8 NumOfBytes, const uint8 CSAddr, const uint16 RAMAddr);
extern bool  USER_NVM_CONFIG          (const uint8 *NVMSize, const uint8 *MapRAMSize);
extern uint8 USER_NVM_ECC2ADDR        (const uint16 *ecc2addr);
extern uint8 USER_MAPRAM_INIT         (void);
extern bool  USER_READ_100TP          (const uint8 OTP_Page_Sel, const uint8 DataOffset, const uint32 *HundredTPData);
extern uint8 USER_100TP_PROG          (const uint8 OTP_Page_Sel);
extern uint8 USER_ERASE_SECTOR        (const uint32 NVMSectorAddr);
extern uint8 USER_RAM_MBIST_START     (const uint16 RAM_MBIST_Stop_Addr, const uint16 RAM_MBIST_Start_addr);
extern uint8 USER_NVM_ECC_CHECK       (void);
extern uint8 USER_ECC_CHECK           (const uint32 *ecc2addr);
extern uint8 USER_ERASE_SECTOR_VERIFY (const uint32 sector_addr);
extern uint8 USER_ERASEPG_VERIFY      (const uint32 page_addr);
extern uint8 USER_VERIFY_PAGE         (const uint32 page_addr);
extern uint8 ProgramPage              (uint32 addr, const uint8 *buf, uint8 Branch, uint8 Correct, uint8 FailPageErase);
extern bool  GetCustomerID            (const TCustomerID *CustID);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

