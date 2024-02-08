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
#include "CfgSwcServiceStartUp.hpp"
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
   infMcalDioSwcApplEcuM_vInitFunction();
   infMcalAdcSwcApplEcuM_vInitFunction();
   infMcalMcuSwcApplEcuM_InitFunction();
   infMcalWdgSwcApplEcuM_InitFunction();
   infSwcServiceNvMSwcApplEcuM_InitFunction();
   infSwcServiceEcuMSwcServiceStartUp_InitFunction();
}

#include "rba_DiagLib_MemUtils.hpp"
#include "FeeFblBlockInterfaceX.hpp"
#include "ProductionFlashInterfaceX.hpp"

#pragma ghs startdata
#pragma ghs section rodata=".roAPP_METADATA"
const Type_CfgSwcServiceStartUp_stDescriptorBlock CfgSwcServiceStartUp_stDescriptorBlock = {
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
   ,  (uint32)0x00000000
   ,  (uint32)0x00000000
   ,  0xff, 0xff, 0xff, 0xff
   ,  CfgSwcServiceStartUp_dVersionSoftwareMajor
   ,  CfgSwcServiceStartUp_dVersionSoftwareMinor
   ,  CfgSwcServiceStartUp_dVersionSoftwareMicro
   ,  CfgSwcServiceStartUp_dIndexGenealogy
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
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
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0x00000000
   ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   ,  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
   ,  0xCC, 0xCC
};
#pragma ghs enddata

static uint8 SwcServiceStartUp_u8DecimalToBcd     (uint8 ucNumber);
static uint8 SwcServiceStartUp_u8GetSchemaVersion (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
static uint8 SwcServiceStartUp_u8GetProgType      (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
static uint8 SwcServiceStartUp_u8GetMajor         (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
static uint8 SwcServiceStartUp_u8GetMinor         (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
static uint8 SwcServiceStartUp_u8GetMicro         (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
static uint8 SwcServiceStartUp_u8GetIndex         (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
static uint8 SwcServiceStartUp_u8GetCrc32         (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);

Type_CfgSwcServiceStartUp_stDescriptorBlock* SwcServiceStartUp_ptrstGetDescriptorBlock(
   Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   if(leProgramSw == CfgSwcServiceStartUp_eProgramSw_App){return (Type_CfgSwcServiceStartUp_stDescriptorBlock*)CfgSwcServiceStartUp_dAddressDescriptorBlock_App;}
   else                                                  {return (Type_CfgSwcServiceStartUp_stDescriptorBlock*)CfgSwcServiceStartUp_dAddressDescriptorBlock_Fbl;}
}

#include "LibAutosar_Crc.hpp"

boolean DcmVerifyApplicationMemory(void){
   Type_CfgSwcServiceStartUp_stDescriptorBlock* pApplMetaData = SwcServiceStartUp_ptrstGetDescriptorBlock(CfgSwcServiceStartUp_eProgramSw_App);

   return(
         *((uint32*)&(pApplMetaData->u8Hash[0]))
      == LibAutosarCrc_u32Calculate(
               (const uint8*) 0x20100U
            ,                 0x57ae0U
            ,  LibAutosarCrc_dValueInitial32
            ,  TRUE
         )
   )
   ? TRUE
   : FALSE
   ;
}

uint8 SwcServiceStartUp_u8DigitToAscii(
   uint8 ucDigit
){
   uint8 ucAsciiValue;
        if(ucDigit <=   9){ucAsciiValue = ucDigit + 48;}
   else if(ucDigit <= 0xf){ucAsciiValue = ucDigit + 55;}
   else                   {ucAsciiValue = '?';}
   return ucAsciiValue;
}

static uint8 SwcServiceStartUp_u8DecimalToBcd(
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

void SwcServiceStartUp_u8GetSoftware_ID(
   uint8* lptru8Data
){
   lptru8Data += SwcServiceStartUp_u8GetMajor(lptru8Data, cSTRING_SIZ_MAJOR, CfgSwcServiceStartUp_eProgramSw_App);
   lptru8Data += SwcServiceStartUp_u8GetMinor(lptru8Data, cSTRING_SIZ_MINOR, CfgSwcServiceStartUp_eProgramSw_App);
   lptru8Data += SwcServiceStartUp_u8GetMicro(lptru8Data, cSTRING_SIZ_MICRO, CfgSwcServiceStartUp_eProgramSw_App);
   lptru8Data += SwcServiceStartUp_u8GetCrc32(lptru8Data, cSTRING_SIZ_CRC32, CfgSwcServiceStartUp_eProgramSw_App);
}

uint8 SwcServiceStartUp_u8GetEcuProgramInformationPart1(
      uint8* lptru8Data
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   if(
         lu8Len
      <  cSTRING_ECU_PROGRAM_INFO_1_LENGTH
   ){
      return 0;
   }
   else{
      lptru8Data += SwcServiceStartUp_u8GetSchemaVersion (lptru8Data, cSTRING_SIZ_SCHEMA_VERS, leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetComponentId   (lptru8Data, cSTRING_SIZ_COMP_ID,     leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetPcbaId        (lptru8Data, cSTRING_SIZ_PCBA_ID,     leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetAuxId         (lptru8Data, cSTRING_SIZ_AUX_ID,      leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetModeId        (lptru8Data, cSTRING_SIZ_MODE_ID,     leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetProgType      (lptru8Data, cSTRING_SIZ_PROG_TYPE,   leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetIndex         (lptru8Data, cSTRING_SIZ_INDEX,       leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetMajor         (lptru8Data, cSTRING_SIZ_MAJOR,       leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetMinor         (lptru8Data, cSTRING_SIZ_MINOR,       leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetMicro         (lptru8Data, cSTRING_SIZ_MICRO,       leProgramSw);
      lptru8Data += SwcServiceStartUp_u8GetCrc32         (lptru8Data, cSTRING_SIZ_CRC32,       leProgramSw);
      return cSTRING_ECU_PROGRAM_INFO_1_LENGTH;
   }
}

uint8 SwcServiceStartUp_u8GetEcuProgramInformationPart2(
      uint8* lptru8Data
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   uint8 i;
   if(
         lu8Len
      <  cSTRING_ECU_PROGRAM_INFO_2_LENGTH
   ){
      return 0;
   }
   else{
      if(
            leProgramSw
         == CfgSwcServiceStartUp_eProgramSw_App
      ){
         lptru8Data += FEEFBL_GetProgAttemptsCounter(lptru8Data);
         lptru8Data += FEEFBL_GetMaxProgAttemptsCounter(lptru8Data);
         lptru8Data += PRODFLASH_GetApplicationSignature(lptru8Data);
      }
      else{
         for(
            i = 0;
            i < kEepSizeProgAttemptsCounter;
            i ++
         ){
            lptru8Data = 0;
            lptru8Data++;
         }
         for(
            i = 0;
            i < kEepSizeMaxProgAttemptsCounter;
            i ++
         ){
            lptru8Data = 0;
            lptru8Data++;
         }
         lptru8Data += SwcServiceStartUp_u8GetHmacSignature(
               lptru8Data
            ,  cSTRING_SIZ_HASH
            ,  leProgramSw
         );
      }
      for(
         i = 0;
         i < 16;
         i ++
      ){
         lptru8Data[i] = 0xff;
      }
      return cSTRING_ECU_PROGRAM_INFO_2_LENGTH;
   }
}

uint8 SwcServiceStartUp_u8GetHmacSignature(
      uint8* pBuffer
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
   if(
         lu8Len
      >= cSTRING_SIZ_HASH
   ){
      pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(
         leProgramSw
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->u8Hash)
         ,  cSTRING_SIZ_HASH
      );
      return cSTRING_SIZ_HASH;
   }
   else{
      return 0;
   }
}

uint8 SwcServiceStartUp_u8GetComponentId(
      uint8* pBuffer
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
   if(
         lu8Len
      >= cSTRING_SIZ_COMP_ID
   ){
      pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(
         leProgramSw
      );
      pBuffer[0] = pDescBlock->u16IdComponent & 0xff00;
      pBuffer[1] = pDescBlock->u16IdComponent & 0x00ff;
      return cSTRING_SIZ_COMP_ID;
   }
   else{
      return 0;
   }
}

uint8 SwcServiceStartUp_u8GetPcbaId(
      uint8* pBuffer
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
   if(
         lu8Len
      >= cSTRING_SIZ_PCBA_ID
   ){
      pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(
         leProgramSw
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->u8IdPcba)
         ,  cSTRING_SIZ_PCBA_ID
      );
      return cSTRING_SIZ_PCBA_ID;
   }
   else{
      return 0;
   }
}

uint8 SwcServiceStartUp_u8GetAuxId(
      uint8* pBuffer
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
   if(
         lu8Len
      >= cSTRING_SIZ_AUX_ID
   ){
      pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(
         leProgramSw
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->u8IdAux)
         ,  cSTRING_SIZ_AUX_ID
      );
      return cSTRING_SIZ_AUX_ID;
   }
   else{
      return 0;
   }
}

uint8 SwcServiceStartUp_u8GetModeId(
      uint8* pBuffer
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
   if(
         lu8Len
      >= cSTRING_SIZ_MODE_ID
   ){
      pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(
         leProgramSw
      );
      RBA_DIAGLIB_MEMCPY(
            pBuffer
         ,  (const uint8*)&(pDescBlock->u16IdMode)
         ,  cSTRING_SIZ_MODE_ID
      );
      return cSTRING_SIZ_MODE_ID;
   }
   else{
      return 0;
   }
}

uint8 SwcServiceStartUp_u8GetComponentAndSwType(
      uint8* pBuffer
   ,  uint8  lu8Len
   ,  Type_CfgSwcServiceStartUp_eProgramSw leProgramSw
){
   Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
   if(
         lu8Len
      >= cSTRING_SIZ_COMPANDSWTYPE
   ){
      pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(
         leProgramSw
      );
      pBuffer[0] = SwcServiceStartUp_u8DecimalToBcd(
         pDescBlock->u16IdComponent
      );
      pBuffer[1] = SwcServiceStartUp_u8DecimalToBcd(
         pDescBlock->u8VersionSchema
      );
      pBuffer[2] = SwcServiceStartUp_u8DecimalToBcd(
         pDescBlock->u8TypeProgramEcu
      );
      return cSTRING_SIZ_COMPANDSWTYPE;
   }
   else{
      return 0;
   }
}

uint8 SwcServiceStartUp_u8GetGenealogyVersion(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_SCHEMA_VERS){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    RBA_DIAGLIB_MEMCPY(&pBuffer[0], (const uint8*)&(pDescBlock->u8VersionSchema), cSTRING_SIZ_SCHEMA_VERS);
    return cSTRING_SIZ_SCHEMA_VERS;
  }
  else{
    return 0;
  }
}

uint8 SwcServiceStartUp_u8GetTfsChangeset(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_TFSCS){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    RBA_DIAGLIB_MEMCPY(&pBuffer[0], (const uint8*)&(pDescBlock->au8ChangesetTfs), cSTRING_SIZ_TFSCS);
    return cSTRING_SIZ_TFSCS;
  }
  else{
    return 0;
  }
}

uint32* SwcServiceStartUp_ptru32GetPointerToSHA256Hash(Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  uint32* pHash;
  pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
  pHash = (uint32*)&(pDescBlock->u8Hash);
  return pHash;
}

static uint8 SwcServiceStartUp_u8GetSchemaVersion(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_SCHEMA_VERS){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    pBuffer[0] = SwcServiceStartUp_u8DecimalToBcd(pDescBlock->u8VersionSchema);
    return lu8Len;
  }
  else{
    return 0;
  }
}

static uint8 SwcServiceStartUp_u8GetProgType(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_PROG_TYPE){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    pBuffer[0] = SwcServiceStartUp_u8DecimalToBcd(pDescBlock->u8TypeProgramEcu);
    return lu8Len;
  }
  else{
    return 0;
  }
}

static uint8 SwcServiceStartUp_u8GetMajor(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_MAJOR){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    pBuffer[0] = SwcServiceStartUp_u8DecimalToBcd(pDescBlock->u8VersionMajor);
    return lu8Len;
  }
  else{
    return 0;
  }
}

static uint8 SwcServiceStartUp_u8GetMinor(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_MINOR){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    pBuffer[0] = SwcServiceStartUp_u8DecimalToBcd(pDescBlock->u8VersionMinor);
    return lu8Len;
  }
  else{
    return 0;
  }
}

static uint8 SwcServiceStartUp_u8GetMicro(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_MICRO){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    pBuffer[0] = SwcServiceStartUp_u8DecimalToBcd((uint8)(pDescBlock->u16VersionMicro / 100u));
    pBuffer[1] = SwcServiceStartUp_u8DecimalToBcd((uint8)(pDescBlock->u16VersionMicro % 100));
    return cSTRING_SIZ_MICRO;
  }
  else{
    return 0;
  }
}

static uint8 SwcServiceStartUp_u8GetIndex(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_INDEX){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    pBuffer[0] = SwcServiceStartUp_u8DecimalToBcd(pDescBlock->u8Index);
    return lu8Len;
  }
  else{
    return 0;
  }
}

static uint8 SwcServiceStartUp_u8GetCrc32(uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw){
  Type_CfgSwcServiceStartUp_stDescriptorBlock* pDescBlock;
  if(lu8Len >= cSTRING_SIZ_CRC32){
    pDescBlock = SwcServiceStartUp_ptrstGetDescriptorBlock(leProgramSw);
    RBA_DIAGLIB_MEMCPY(&pBuffer[0], (const uint8*)&(pDescBlock->u32CrcApp), cSTRING_SIZ_CRC32);
    return lu8Len;
  }
  else{
    return 0;
  }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
