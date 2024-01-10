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

#include "Types_CfgSwcServiceStartUp.hpp"
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
#define OS_MAIN()                                                 int main(void)

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

//TBD: Move defines and objects to CfgXxx.c
#include "CfgSwcServiceStartUp.hpp"
#include "rba_DiagLib_MemUtils.hpp"
#include "FeeFblBlockInterfaceX.hpp"
#include "ProductionFlashInterfaceX.hpp"

#define CfgSwcServiceStartUp_dAddressDescriptorBlock_App   ((void*)  0x00077b00)
#define CfgSwcServiceStartUp_dAddressDescriptorBlock_Fbl   ((void*)  0x0001ff00)
#define CfgSwcServiceStartUp_dVersionSoftwareMajor         ((uint8)  0x02)
#define CfgSwcServiceStartUp_dVersionSoftwareMinor         ((uint8)  0x01)
#define CfgSwcServiceStartUp_dVersionSoftwareMicro         ((uint16) 0x0004)
#define CfgSwcServiceStartUp_dVersionSchema                ((uint8)  0x01)
#define CfgSwcServiceStartUp_dIdComponent                  ((uint16) 0x003A)
#define CfgSwcServiceStartUp_dIdPcba                       ((uint8)  0x01)
#define CfgSwcServiceStartUp_dIdAux                        ((uint8)  0x00)
#define CfgSwcServiceStartUp_dIdMode                       ((uint16) 0x0000)
#define CfgSwcServiceStartUp_dTypeProg_Fbl                 ((uint8)  0x02)
#define CfgSwcServiceStartUp_dTypeProg_App                 ((uint8)  0x05)
#define CfgSwcServiceStartUp_dIndexGenealogy               ((uint8)  0x01)
#define CfgSwcServiceStartUp_dVersionProtocolDL            ((uint16) 0x0001)
#define cTFS_CHANGESET                         {'C','S','0','0','1','9','3','3'}

#ifndef _EcuVirtual
#pragma ghs startdata
#pragma ghs section rodata=".roAPP_METADATA"
#endif
const tDescriptorBlock DescriptorBlock = {
      CfgSwcServiceStartUp_dVersionSchema
   ,  0xff
   ,  CfgSwcServiceStartUp_dIdComponent
   ,  CfgSwcServiceStartUp_dIdPcba
   ,  CfgSwcServiceStartUp_dIdAux
   ,  CfgSwcServiceStartUp_dIdMode
   ,  cTFS_CHANGESET
   ,  CfgSwcServiceStartUp_dTypeProg_App
   ,  0xff
   ,  CfgSwcServiceStartUp_dVersionProtocolDL
   ,  ((uint32)0x00000000)
   ,  ((uint32)0x00000000)
   ,  {0xff, 0xff, 0xff, 0xff}
   ,  CfgSwcServiceStartUp_dVersionSoftwareMajor
   ,  CfgSwcServiceStartUp_dVersionSoftwareMinor
   ,  CfgSwcServiceStartUp_dVersionSoftwareMicro
   ,  CfgSwcServiceStartUp_dIndexGenealogy
   ,  {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}
   ,  ((uint32)0x00000000)
   ,  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
   ,  {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}
   ,  {0xCC, 0xCC}
};
#ifndef _EcuVirtual
#pragma ghs enddata
#endif

static uint8 VERSION_ucDecimalToBcd   (uint8 ucNumber);
static uint8 VERSION_GetSchemaVersion (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetProgType      (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetMajor         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetMinor         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetMicro         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetIndex         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetCrc32         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);

tDescriptorBlock* VERSION_GetPointerToDescriptorBlock(
   uint8 ucApplFbl
){
   if(ucApplFbl == cAPP){return (tDescriptorBlock*)CfgSwcServiceStartUp_dAddressDescriptorBlock_App;}
   else                 {return (tDescriptorBlock*)CfgSwcServiceStartUp_dAddressDescriptorBlock_Fbl;}
}

#include "DcmMemCheck.hpp"
#include "LibAutosar_Crc.hpp"
#include "CfgSwcServiceStartUp.hpp"

#include "SwcServiceStartUp.hpp"

boolean DcmVerifyApplicationMemory(void){
   tDescriptorBlock* pApplMetaData = VERSION_GetPointerToDescriptorBlock(cAPP);
   return(
         *((uint32*)&(pApplMetaData->ucHash[0]))
      == LibAutosarCrc_u32Calculate(
               (const uint8*)0x20100U
            ,  0x57ae0U
            ,  LibAutosarCrc_dValueInitial32
            ,  TRUE
         )
   )
   ?  TRUE
   :  FALSE
   ;
}

uint8 VERSION_ucDigitToAscii(
   uint8 ucDigit
){
   uint8 ucAsciiValue;
        if(ucDigit <=   9){ucAsciiValue = ucDigit + 48;}
   else if(ucDigit <= 0xf){ucAsciiValue = ucDigit + 55;}
   else                   {ucAsciiValue = '?';}
   return ucAsciiValue;
}

static uint8 VERSION_ucDecimalToBcd(
   uint8 ucNumber
){
   static uint8 ucBcdValue = 0xffu;
   static uint8 ucLsb;
   static uint8 ucMsb;
   if(
         ucNumber
      <  (uint8)100
   ){
      ucLsb = ucNumber % 10u;
      ucMsb = ucNumber / 10u;
      ucBcdValue = (ucMsb << 4u) + ucLsb;
   }
   return (ucBcdValue);
}

void VERSION_GetSoftware_ID(
   uint8* ucData
){
   ucData += VERSION_GetMajor(ucData, cSTRING_SIZ_MAJOR, cMETADATA_APP);
   ucData += VERSION_GetMinor(ucData, cSTRING_SIZ_MINOR, cMETADATA_APP);
   ucData += VERSION_GetMicro(ucData, cSTRING_SIZ_MICRO, cMETADATA_APP);
   ucData += VERSION_GetCrc32(ucData, cSTRING_SIZ_CRC32, cMETADATA_APP);
}

uint8 VERSION_GetEcuProgramInformationPart1(
      uint8* ucData
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
   if(
         ucLen
      <  cSTRING_ECU_PROGRAM_INFO_1_LENGTH
   ){
      return 0;
   }
   else{
      ucData += VERSION_GetSchemaVersion (ucData, cSTRING_SIZ_SCHEMA_VERS, ucApplFbl);
      ucData += VERSION_GetComponentId   (ucData, cSTRING_SIZ_COMP_ID,     ucApplFbl);
      ucData += VERSION_GetPcbaId        (ucData, cSTRING_SIZ_PCBA_ID,     ucApplFbl);
      ucData += VERSION_GetAuxId         (ucData, cSTRING_SIZ_AUX_ID,      ucApplFbl);
      ucData += VERSION_GetModeId        (ucData, cSTRING_SIZ_MODE_ID,     ucApplFbl);
      ucData += VERSION_GetProgType      (ucData, cSTRING_SIZ_PROG_TYPE,   ucApplFbl);
      ucData += VERSION_GetIndex         (ucData, cSTRING_SIZ_INDEX,       ucApplFbl);
      ucData += VERSION_GetMajor         (ucData, cSTRING_SIZ_MAJOR,       ucApplFbl);
      ucData += VERSION_GetMinor         (ucData, cSTRING_SIZ_MINOR,       ucApplFbl);
      ucData += VERSION_GetMicro         (ucData, cSTRING_SIZ_MICRO,       ucApplFbl);
      ucData += VERSION_GetCrc32         (ucData, cSTRING_SIZ_CRC32,       ucApplFbl);
      return cSTRING_ECU_PROGRAM_INFO_1_LENGTH;
   }
}

uint8 VERSION_GetEcuProgramInformationPart2(
      uint8* ucData
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
   uint8 i;
   if(
         ucLen
      <  cSTRING_ECU_PROGRAM_INFO_2_LENGTH
   ){
      return 0;
   }
   else{
      if(
            ucApplFbl
         == cAPP
      ){
         ucData += FEEFBL_GetProgAttemptsCounter(ucData);
         ucData += FEEFBL_GetMaxProgAttemptsCounter(ucData);
         ucData += PRODFLASH_GetApplicationSignature(ucData);
      }
      else{
         for(
            i = 0;
            i < kEepSizeProgAttemptsCounter;
            i ++
         ){
            ucData = 0;
            ucData++;
         }
         for(
            i = 0;
            i < kEepSizeMaxProgAttemptsCounter;
            i ++
         ){
            ucData = 0;
            ucData++;
         }
         ucData += VERSION_GetHmacSignature(
               ucData
            ,  cSTRING_SIZ_HASH
            ,  ucApplFbl
         );
      }
      for(
         i = 0;
         i < 16;
         i ++
      ){
         ucData[i] = 0xff;
      }
      return cSTRING_ECU_PROGRAM_INFO_2_LENGTH;
   }
}

uint8 VERSION_GetHmacSignature(
      uint8* pBuffer
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
  tDescriptorBlock* pDescBlock;
   if(
         ucLen
      >= cSTRING_SIZ_HASH
   ){
      pDescBlock = VERSION_GetPointerToDescriptorBlock(
         ucApplFbl
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->ucHash)
         ,  cSTRING_SIZ_HASH
      );
      return cSTRING_SIZ_HASH;
   }
   else{
      return 0;
   }
}

uint8 VERSION_GetComponentId(
      uint8* pBuffer
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
   tDescriptorBlock* pDescBlock;
   if(
         ucLen
      >= cSTRING_SIZ_COMP_ID
   ){
      pDescBlock = VERSION_GetPointerToDescriptorBlock(
         ucApplFbl
      );
      pBuffer[0] = (uint8)((pDescBlock->ushComponentId & 0xff00)>>8);
      pBuffer[1] = (uint8) (pDescBlock->ushComponentId & 0x00ff);
      return cSTRING_SIZ_COMP_ID;
   }
   else{
      return 0;
   }
}

uint8 VERSION_GetPcbaId(
      uint8* pBuffer
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
   tDescriptorBlock* pDescBlock;
   if(
         ucLen
      >= cSTRING_SIZ_PCBA_ID
   ){
      pDescBlock = VERSION_GetPointerToDescriptorBlock(
         ucApplFbl
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->ucPcbaId)
         ,  cSTRING_SIZ_PCBA_ID
      );
      return cSTRING_SIZ_PCBA_ID;
   }
   else{
      return 0;
   }
}

uint8 VERSION_GetAuxId(
      uint8* pBuffer
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
   tDescriptorBlock* pDescBlock;
   if(
         ucLen
      >= cSTRING_SIZ_AUX_ID
   ){
      pDescBlock = VERSION_GetPointerToDescriptorBlock(
         ucApplFbl
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->ucAuxId)
         ,  cSTRING_SIZ_AUX_ID
      );
      return cSTRING_SIZ_AUX_ID;
   }
   else{
      return 0;
   }
}

uint8 VERSION_GetModeId(
      uint8* pBuffer
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
   tDescriptorBlock* pDescBlock;
   if(
         ucLen
      >= cSTRING_SIZ_MODE_ID
   ){
      pDescBlock = VERSION_GetPointerToDescriptorBlock(
         ucApplFbl
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->ushModeId)
         ,  cSTRING_SIZ_MODE_ID
      );
      return cSTRING_SIZ_MODE_ID;
   }
   else{
      return 0;
   }
}

uint8 VERSION_GetComponentAndSwType(
      uint8* pBuffer
   ,  uint8  ucLen
   ,  uint8  ucApplFbl
){
   tDescriptorBlock* pDescBlock;
   if(
         ucLen
      >= cSTRING_SIZ_COMPANDSWTYPE
   ){
      pDescBlock = VERSION_GetPointerToDescriptorBlock(
         ucApplFbl
      );
      pBuffer[0] = VERSION_ucDecimalToBcd(
         pDescBlock->ushComponentId
      );
      pBuffer[1] = VERSION_ucDecimalToBcd(
         pDescBlock->ucSchemaVersion
      );
      pBuffer[2] = VERSION_ucDecimalToBcd(
         pDescBlock->ucEcuProgramType
      );
      return cSTRING_SIZ_COMPANDSWTYPE;
   }
   else{
      return 0;
   }
}

uint8 VERSION_GetGenealogyVersion(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_SCHEMA_VERS){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    RBA_DIAGLIB_MEMCPY(&pBuffer[0], (const uint8*)&(pDescBlock->ucSchemaVersion), cSTRING_SIZ_SCHEMA_VERS);
    return cSTRING_SIZ_SCHEMA_VERS;
  }
  else{
    return 0;
  }
}

uint8 VERSION_GetTfsChangeset(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_TFSCS){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    RBA_DIAGLIB_MEMCPY(&pBuffer[0], (const uint8*)&(pDescBlock->aucTfsChangeset), cSTRING_SIZ_TFSCS);
    return cSTRING_SIZ_TFSCS;
  }
  else{
    return 0;
  }
}

uint32* VERSION_GetPointerToSHA256Hash(uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  uint32* pHash;
  pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
  pHash = (uint32*)&(pDescBlock->ucHash);
  return pHash;
}

static uint8 VERSION_GetSchemaVersion(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_SCHEMA_VERS){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    pBuffer[0] = VERSION_ucDecimalToBcd(pDescBlock->ucSchemaVersion);
    return ucLen;
  }
  else{
    return 0;
  }
}

static uint8 VERSION_GetProgType(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_PROG_TYPE){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    pBuffer[0] = VERSION_ucDecimalToBcd(pDescBlock->ucEcuProgramType);
    return ucLen;
  }
  else{
    return 0;
  }
}

static uint8 VERSION_GetMajor(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_MAJOR){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    pBuffer[0] = VERSION_ucDecimalToBcd(pDescBlock->ucMajor);
    return ucLen;
  }
  else{
    return 0;
  }
}

static uint8 VERSION_GetMinor(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_MINOR){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    pBuffer[0] = VERSION_ucDecimalToBcd(pDescBlock->ucMinor);
    return ucLen;
  }
  else{
    return 0;
  }
}

static uint8 VERSION_GetMicro(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_MICRO){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    pBuffer[0] = VERSION_ucDecimalToBcd((uint8)(pDescBlock->ushMicro / 100u));
    pBuffer[1] = VERSION_ucDecimalToBcd((uint8)(pDescBlock->ushMicro % 100));
    return cSTRING_SIZ_MICRO;
  }
  else{
    return 0;
  }
}

static uint8 VERSION_GetIndex(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_INDEX){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    pBuffer[0] = VERSION_ucDecimalToBcd(pDescBlock->ucIndex);
    return ucLen;
  }
  else{
    return 0;
  }
}

static uint8 VERSION_GetCrc32(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl){
  tDescriptorBlock* pDescBlock;
  if(ucLen >= cSTRING_SIZ_CRC32){
    pDescBlock = VERSION_GetPointerToDescriptorBlock(ucApplFbl);
    RBA_DIAGLIB_MEMCPY(&pBuffer[0], (const uint8*)&(pDescBlock->ulCrc32App), cSTRING_SIZ_CRC32);
    return ucLen;
  }
  else{
    return 0;
  }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
