#include "ProductionFlashInterface.hpp"
#include "Fls.hpp"
#include "r_fdl.hpp"
#include "McalDio.hpp"

#ifdef _RST_VS_EDITOR_SUPPORT_
  Dcm__Union_ProductionData DCM__UN_ProductionDataFlash;
#else
  Dcm__Union_ProductionData PROD_DATA DCM__UN_ProductionDataFlash;
#endif

static void PRODFLASH__WriteProductionDataMember(Dcm__Enum_ProductionDataMembers EN_Member, const uint8 *PU8_Data, const uint8 U8_Length){
  uint8 AU8_FlashBlockBuffer[DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE];
  uint32 U32_AddressOfMember = 0U;
  uint16 U16_SizeOfMember = 0U;
  uint8 U8_StartBlockNumber = 0U;
  uint8 U8_EndBlockNumber = 0U;
  uint8 U8_BlockNumberCounter = 0U;
  uint8 U8_BufferCounter = 0U;
  uint8 U8_BytesToWrite = U8_Length;

  U32_AddressOfMember = PRODFLASH__GetAddressOfMember(EN_Member);

  U16_SizeOfMember = PRODFLASH__GetSizeOfMember(EN_Member);

  U8_StartBlockNumber = PRODFLASH__GetStartBlockNumber(U32_AddressOfMember);

  U8_EndBlockNumber = PRODFLASH__GetEndBlockNumber(U32_AddressOfMember, U16_SizeOfMember);

  for(U8_BlockNumberCounter = U8_StartBlockNumber; U8_BlockNumberCounter <= U8_EndBlockNumber; U8_BlockNumberCounter++){
    uint8 U8_StartPositionOfWrite = 0U;
    uint8 U8_CurrentPositionOfWrite = 0U;

    for(U8_BufferCounter = 0U; U8_BufferCounter < DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE; U8_BufferCounter++){
      AU8_FlashBlockBuffer[U8_BufferCounter] = *(&DCM__UN_ProductionDataFlash.AU8_Production_Data_Array[0] + (U8_BlockNumberCounter * DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE) + U8_BufferCounter);
    }

    PRODFLASH__EraseFlashBlock(U8_BlockNumberCounter);

    if(U8_BlockNumberCounter == U8_StartBlockNumber){
      U8_StartPositionOfWrite = (uint8) (U32_AddressOfMember % DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE);
    }
    else{
      U8_StartPositionOfWrite = 0U;
    }

    U8_CurrentPositionOfWrite = U8_StartPositionOfWrite;
    while((U8_CurrentPositionOfWrite < DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE) && (U8_BytesToWrite > 0U)){
      AU8_FlashBlockBuffer[U8_CurrentPositionOfWrite] = PU8_Data[U8_Length - U8_BytesToWrite];
      U8_CurrentPositionOfWrite++;
      U8_BytesToWrite--;
    }

    PRODFLASH__WriteFlashBlock(U8_BlockNumberCounter, (uint8 *) AU8_FlashBlockBuffer);
  }

}

static uint16 PRODFLASH__GetSizeOfMember(Dcm__Enum_ProductionDataMembers EN_Member){
  uint16 U16_SizeOfMember = 0U;

  switch(EN_Member){
    case DCM__E_RESERVED_1:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index1_Reserved);
      break;
    case DCM__E_CUSTOMER_HW_PART_NUMBER_433:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index2_CustomerHwPartNumber433);
      break;
    case DCM__E_CUSTOMER_HW_PART_NUMBER_315:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index3_CustomerHwPartNumber315);
      break;
    case DCM__E_HUF_SPECIFIC_HW_NUMBER_433:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index4_HufSpecificHw433);
      break;
    case DCM__E_HUF_SPECIFIC_HW_NUMBER_315:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index5_HufSpecificHw315);
      break;
    case DCM__E_HARDWARE_VERSION_INFO:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index6_HardwareVersionInfo);
      break;
    case DCM__E_CUSTOMER_PART_NUMBER_433:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index7_CustomerPartNumber433);
      break;
    case DCM__E_CUSTOMER_PART_NUMBER_315:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index8_CustomerPartNumber315);
      break;
    case DCM__E_SUPPLIER_NUMBER:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index9_SupplierNumber);
      break;
    case DCM__E_PRODUCTION_DAY:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index10_ProductionDay);
      break;
    case DCM__E_CUSTOMER_ECU_SERIAL_NUMBER:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index11_CustomerECUSerialNumber);
      break;
    case DCM__E_RIVIAN_APPL_SWFP_TESTER_SERIAL_NO:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index12_RivianApplSwFpTesterSerialNo);
      break;
    case DCM__E_RIVIAN_APPL_SWFP_PROGRAMMING_DATE:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index13_RivianApplSwFpProgrammingDate);
      break;
    case DCM__E_RIVIAN_BL_SWFP_TESTER_SERIAL_NO:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index14_RivianBlFpTesterSerialNo);
      break;
    case DCM__E_RIVIAN_BL_SWFP_PROGRAMMING_DATE:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index15_RivianBlFpProgrammingDate);
      break;
    case DCM__E_RIVIAN_VIN:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index16_RivianVIN);
      break;
    case DCM__E_RIVIAN_MANUF_SUPP_MODE:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index17_RivianManufSuppMode);
      break;
    case DCM__E_RIVIAN_GENEALOGY_VERSION:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index18_RivianGenealogyVersion);
      break;
    case DCM__E_RIVIAN_COMPONENT_ID:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index19_RivianComponentId);
      break;
    case DCM__E_RIVIAN_PCBA_ID:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index20_RivianPcbaId);
      break;
    case DCM__E_RIVIAN_AUX_ID:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index21_RivianAuxId);
      break;
    case DCM__E_RIVIAN_MODE_ID:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index22_RivianModeId);
      break;
    case DCM__E_RIVIAN_BOARD_PART_NUMBER:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index23_RivianBoardPartNumber);
      break;
    case DCM__E_RIVIAN_BOARD_SERIAL_NUMBER:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index24_RivianBoardSerialNumber);
      break;
    case DCM__E_RIVIAN_ECU_PART_NUMBER:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index25_RivianEcuPartNumber);
      break;
    case DCM__E_RIVIAN_ECU_SERIAL_NUMBER:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index26_RivianEcuSerialNumber);
      break;
    case DCM__E_RIVIAN_APPLICATION_SIGNATURE:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index27_RivianApplicationSignature);
      break;
    case DCM__E_RIVIAN_GENEALOGY_CRC32:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index28_RivianGenealogyCrc32);
      break;
    case DCM__E_SUPPLIER1_EOL_CHECKER_BYTE:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index29_SUPPLIER1EolCheckerByte);
      break;
    case DCM__E_RESERVED_2:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index30_Reserved);
      break;
    case DCM__E_APPLICATION_CHECKSUM:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index31_ApplicationChecksum);
      break;
    case DCM__E_RESERVED_3:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index32_Reserved);
      break;
    case DCM__E_ITAC_SERIAL_NUMBER:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index33_iTACSerialNumber);
      break;
    case DCM__E_RESERVED_4:
      U16_SizeOfMember = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index34_Reserved);
      break;
    default:
      break;
  }

  return U16_SizeOfMember;
}

static uint32 PRODFLASH__GetAddressOfMember(Dcm__Enum_ProductionDataMembers EN_Member){
  uint32 U32_AddressOfMember = 0U;

  switch(EN_Member){
    case DCM__E_RESERVED_1:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index1_Reserved[0];
      break;
    case DCM__E_CUSTOMER_HW_PART_NUMBER_433:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index2_CustomerHwPartNumber433[0];
      break;
    case DCM__E_CUSTOMER_HW_PART_NUMBER_315:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index3_CustomerHwPartNumber315[0];
      break;
    case DCM__E_HUF_SPECIFIC_HW_NUMBER_433:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index4_HufSpecificHw433[0];
      break;
    case DCM__E_HUF_SPECIFIC_HW_NUMBER_315:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index5_HufSpecificHw315[0];
      break;
    case DCM__E_HARDWARE_VERSION_INFO:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index6_HardwareVersionInfo[0];
      break;
    case DCM__E_CUSTOMER_PART_NUMBER_433:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index7_CustomerPartNumber433[0];
      break;
    case DCM__E_CUSTOMER_PART_NUMBER_315:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index8_CustomerPartNumber315[0];
      break;
    case DCM__E_SUPPLIER_NUMBER:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index9_SupplierNumber[0];
      break;
    case DCM__E_PRODUCTION_DAY:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index10_ProductionDay[0];
      break;
    case DCM__E_CUSTOMER_ECU_SERIAL_NUMBER:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index11_CustomerECUSerialNumber[0];
      break;
    case DCM__E_RIVIAN_APPL_SWFP_TESTER_SERIAL_NO:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index12_RivianApplSwFpTesterSerialNo[0];
      break;
    case DCM__E_RIVIAN_APPL_SWFP_PROGRAMMING_DATE:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index13_RivianApplSwFpProgrammingDate[0];
      break;
    case DCM__E_RIVIAN_BL_SWFP_TESTER_SERIAL_NO:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index14_RivianBlFpTesterSerialNo[0];
      break;
    case DCM__E_RIVIAN_BL_SWFP_PROGRAMMING_DATE:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index15_RivianBlFpProgrammingDate[0];
      break;
    case DCM__E_RIVIAN_VIN:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index16_RivianVIN[0];
      break;
    case DCM__E_RIVIAN_MANUF_SUPP_MODE:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index17_RivianManufSuppMode[0];
      break;
    case DCM__E_RIVIAN_GENEALOGY_VERSION:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index18_RivianGenealogyVersion[0];
      break;
    case DCM__E_RIVIAN_COMPONENT_ID:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index19_RivianComponentId[0];
      break;
    case DCM__E_RIVIAN_PCBA_ID:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index20_RivianPcbaId[0];
      break;
    case DCM__E_RIVIAN_AUX_ID:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index21_RivianAuxId[0];
      break;
    case DCM__E_RIVIAN_MODE_ID:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index22_RivianModeId[0];
      break;
    case DCM__E_RIVIAN_BOARD_PART_NUMBER:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index23_RivianBoardPartNumber[0];
      break;
    case DCM__E_RIVIAN_BOARD_SERIAL_NUMBER:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index24_RivianBoardSerialNumber[0];
      break;
    case DCM__E_RIVIAN_ECU_PART_NUMBER:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index25_RivianEcuPartNumber[0];
      break;
    case DCM__E_RIVIAN_ECU_SERIAL_NUMBER:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index26_RivianEcuSerialNumber[0];
      break;
    case DCM__E_RIVIAN_APPLICATION_SIGNATURE:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index27_RivianApplicationSignature[0];
      break;
    case DCM__E_RIVIAN_GENEALOGY_CRC32:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index28_RivianGenealogyCrc32[0];
      break;
    case DCM__E_SUPPLIER1_EOL_CHECKER_BYTE:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index29_SUPPLIER1EolCheckerByte[0];
      break;
    case DCM__E_RESERVED_2:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index30_Reserved[0];
      break;
    case DCM__E_APPLICATION_CHECKSUM:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index31_ApplicationChecksum[0];
      break;
    case DCM__E_RESERVED_3:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index32_Reserved[0];
      break;
    case DCM__E_ITAC_SERIAL_NUMBER:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index33_iTACSerialNumber[0];
      break;
    case DCM__E_RESERVED_4:
      U32_AddressOfMember = (uint32) &DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index34_Reserved[0];
    default:
      break;
  }

  return U32_AddressOfMember;
}

static uint8 PRODFLASH__GetStartBlockNumber(uint32 U32_AddressOfMember){
  uint8 U8_StartBlockNumber = 0U;
  uint32 U32_ProductionDataStartAddress = (uint32) &DCM__UN_ProductionDataFlash.AU8_Production_Data_Array[0];

  U8_StartBlockNumber = (uint8) ((U32_AddressOfMember - U32_ProductionDataStartAddress) / DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE);

  return U8_StartBlockNumber;
}

static uint8 PRODFLASH__GetEndBlockNumber(uint32 U32_AddressOfMember, uint16 U16_SizeOfMember){
  uint8 U8_EndBlockNumber = 0U;
  uint32 U32_ProductionDataStartAddress = (uint32) &DCM__UN_ProductionDataFlash.AU8_Production_Data_Array[0];

  U8_EndBlockNumber = (uint8) (((U32_AddressOfMember - U32_ProductionDataStartAddress) + ((uint32) U16_SizeOfMember)) / DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE);

  return U8_EndBlockNumber;
}

static void PRODFLASH__EraseFlashBlock(uint8 U8_BlockNumber){
  r_fdl_request_t S_FdlRequest;

  S_FdlRequest.command_enu = R_FDL_CMD_ERASE;
  S_FdlRequest.idx_u32 = U8_BlockNumber;
  S_FdlRequest.cnt_u16 = 1;
  S_FdlRequest.accessType_enu = R_FDL_ACCESS_USER;

  R_FDL_Execute (&S_FdlRequest);

  while(S_FdlRequest.status_enu == R_FDL_BUSY){
   R_FDL_Handler ();
  }

  if(S_FdlRequest.status_enu != R_FDL_OK){
  }
}

static void PRODFLASH__WriteFlashBlock(uint8 U8_BlockNumber, uint8 *PU8_Data){
  r_fdl_request_t S_FdlRequest;

  S_FdlRequest.command_enu = R_FDL_CMD_WRITE;
  S_FdlRequest.idx_u32 = (U8_BlockNumber * DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE);
  S_FdlRequest.cnt_u16 = DCM__PRODUCTION_DATA_FLASH_BLOCK_SIZE;
  S_FdlRequest.bufAddr_u32 = (uint32_t) &PU8_Data[0];
  S_FdlRequest.accessType_enu = R_FDL_ACCESS_USER;

  R_FDL_Execute(&S_FdlRequest);

  while(S_FdlRequest.status_enu == R_FDL_BUSY){
    R_FDL_Handler();
  }

  if(S_FdlRequest.status_enu != R_FDL_OK){
  }
}

uint8* PRODFLASH_GetGenealogyBlockStartAddress(void){
  return (uint8*)DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index18_RivianGenealogyVersion;
}

uint8 PRODFLASH_GetCustomerHwPartNumber(uint8* ucData){
  uint8 ucCounter;
  uint8* pHwVersionNumber;
  uint8 ucSize;

  if(McalDio_GetFrequencySetting() == cFREQUENCY_433){
    ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index2_CustomerHwPartNumber433);
    pHwVersionNumber = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index2_CustomerHwPartNumber433;
  }
  else{
    ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index3_CustomerHwPartNumber315);
    pHwVersionNumber = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index3_CustomerHwPartNumber315;
  }

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = pHwVersionNumber[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetCustomerEcuPartNumber(uint8* ucData){
  uint8 ucCounter;
  uint8* pEcuPartNumber;
  uint8 ucSize;

  if(McalDio_GetFrequencySetting() == cFREQUENCY_433){
    ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index7_CustomerPartNumber433);
    pEcuPartNumber = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index7_CustomerPartNumber433;
  }
  else{
    ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index8_CustomerPartNumber315);
    pEcuPartNumber = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index8_CustomerPartNumber315;
  }

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = pEcuPartNumber[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetVin(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index16_RivianVIN);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index16_RivianVIN[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetEcuProgramFingerprintApplication(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index12_RivianApplSwFpTesterSerialNo);
  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index12_RivianApplSwFpTesterSerialNo[ucCounter];
  }

  ucSize += sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index13_RivianApplSwFpProgrammingDate);
  for(ucCounter = ucCounter; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index13_RivianApplSwFpProgrammingDate[ucCounter];
  }
  return ucSize;
}

uint8 PRODFLASH_GetEcuProgramFingerprintBootloader(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index14_RivianBlFpTesterSerialNo);
  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index14_RivianBlFpTesterSerialNo[ucCounter];
  }

  ucSize += sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index15_RivianBlFpProgrammingDate);
  for(ucCounter = ucCounter; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index15_RivianBlFpProgrammingDate[ucCounter];
  }
  return ucSize;
}

uint8 PRODFLASH_GetRivianEcuSerialNumber(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index26_RivianEcuSerialNumber);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index26_RivianEcuSerialNumber[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetRivianBoardSerialNumber(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index24_RivianBoardSerialNumber);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index24_RivianBoardSerialNumber[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetRivianEcuPartNumber(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index25_RivianEcuPartNumber);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index25_RivianEcuPartNumber[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetRivianBoardPartNumber(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index23_RivianBoardPartNumber);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index23_RivianBoardPartNumber[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetManufacturingSupportMode(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index17_RivianManufSuppMode);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index17_RivianManufSuppMode[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetApplicationSignature(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index27_RivianApplicationSignature);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index27_RivianApplicationSignature[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetGenealogyCrc32(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index28_RivianGenealogyCrc32);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index28_RivianGenealogyCrc32[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetGenealogyVersion(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index18_RivianGenealogyVersion);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index18_RivianGenealogyVersion[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetPcbaId(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index20_RivianPcbaId);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index20_RivianPcbaId[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetAuxId(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index21_RivianAuxId);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index21_RivianAuxId[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetComponentId(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index19_RivianComponentId);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index19_RivianComponentId[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetModeId(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index22_RivianModeId);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index22_RivianModeId[ucCounter];
  }

  return ucSize;
}

uint8 PRODFLASH_GetEolCheckerByte(uint8* ucData){
  uint8 ucCounter;
  uint8 ucSize;

  ucSize = sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index29_SUPPLIER1EolCheckerByte);

  for(ucCounter = 0U; ucCounter < ucSize; ucCounter++){
    ucData[ucCounter] = DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index29_SUPPLIER1EolCheckerByte[ucCounter];
  }

  return ucSize;
}

void PRODFLASH_PutVin(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_VIN, ucData, sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index16_RivianVIN));
}

void PRODFLASH_PutFingerprintApp(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_APPL_SWFP_TESTER_SERIAL_NO, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index12_RivianApplSwFpTesterSerialNo));
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_APPL_SWFP_PROGRAMMING_DATE, &ucData[20], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index13_RivianApplSwFpProgrammingDate));
}

void PRODFLASH_PutRivianBoardPartnumber(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_BOARD_PART_NUMBER, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index23_RivianBoardPartNumber));
}

void PRODFLASH_PutRivianBoardSerialnumber(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_BOARD_SERIAL_NUMBER, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index24_RivianBoardSerialNumber));
}

void PRODFLASH_PutRivianEcuPartnumber(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_ECU_PART_NUMBER, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index25_RivianEcuPartNumber));
}

void PRODFLASH_PutRivianEcuSerialnumber(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_ECU_SERIAL_NUMBER, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index26_RivianEcuSerialNumber));
}

void PRODFLASH_PutManufacturingSupportMode(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_MANUF_SUPP_MODE, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index17_RivianManufSuppMode));
}

void PRODFLASH_PutAuxId(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_AUX_ID, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index21_RivianAuxId));
}

void PRODFLASH_PutPcbaId(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_PCBA_ID, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index20_RivianPcbaId));
}

void PRODFLASH_PutComponentId(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_COMPONENT_ID, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index19_RivianComponentId));
}

void PRODFLASH_PutModeId(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_MODE_ID, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index22_RivianModeId));
}

void PRODFLASH_PutGenealogyVersion(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_GENEALOGY_VERSION, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index18_RivianGenealogyVersion));
}

void PRODFLASH_PutApplicationSignature(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_APPLICATION_SIGNATURE, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index27_RivianApplicationSignature));
}

void PRODFLASH_PutGenealogyCrc32(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_RIVIAN_GENEALOGY_CRC32, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index28_RivianGenealogyCrc32));
}

void PRODFLASH_PutEolCheckerByte(const uint8* ucData){
  PRODFLASH__WriteProductionDataMember(DCM__E_SUPPLIER1_EOL_CHECKER_BYTE, &ucData[0], sizeof(DCM__UN_ProductionDataFlash.Struct_Split_Production_Data.AU8_Index29_SUPPLIER1EolCheckerByte));
}