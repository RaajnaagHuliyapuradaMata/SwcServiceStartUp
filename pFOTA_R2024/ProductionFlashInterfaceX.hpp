#ifndef PRODUCTION_FLASH_INTERFACE_X_H
#define PRODUCTION_FLASH_INTERFACE_X_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "fbl_inc.hpp"

#define cPART_IS_FLASHED          0xff
#define cPART_PASSED_SUPPLIER1_EOL   0xaa
#define cPART_HAD_FIRST_STARTUP   0x55
#define cPART_PASSED_LMC_EOL      0x66

extern uint8* PRODFLASH_GetGenealogyBlockStartAddress(void);
extern uint8 PRODFLASH_GetCustomerEcuPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetRivianBoardPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetManufacturingSupportMode(uint8* ucData);
extern uint8 PRODFLASH_GetRivianEcuPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetRivianBoardSerialNumber(uint8* ucData);
extern uint8 PRODFLASH_GetRivianEcuSerialNumber(uint8* ucData);
extern uint8 PRODFLASH_GetEcuProgramFingerprintBootloader(uint8* ucData);
extern uint8 PRODFLASH_GetEcuProgramFingerprintApplication(uint8* ucData);
extern uint8 PRODFLASH_GetVin(uint8* ucData);
extern uint8 PRODFLASH_GetCustomerEcuSerialNumber(uint8* ucData);
extern uint8 PRODFLASH_GetCustomerHwPartNumber(uint8* ucData);
extern uint8 PRODFLASH_GetApplicationSignature(uint8* ucData);
extern uint8 PRODFLASH_GetGenealogyCrc32(uint8* ucData);
extern uint8 PRODFLASH_GetGenealogyVersion(uint8* ucData);
extern uint8 PRODFLASH_GetPcbaId(uint8* ucData);
extern uint8 PRODFLASH_GetAuxId(uint8* ucData);
extern uint8 PRODFLASH_GetComponentId(uint8* ucData);
extern uint8 PRODFLASH_GetModeId(uint8* ucData);
extern uint8 PRODFLASH_GetEolCheckerByte(uint8* ucData);

extern void PRODFLASH_PutVin(const uint8* ucData);
extern void PRODFLASH_PutFingerprintApp(const uint8* ucData);
extern void PRODFLASH_PutRivianEcuSerialnumber(const uint8* ucData);
extern void PRODFLASH_PutRivianEcuPartnumber(const uint8* ucData);
extern void PRODFLASH_PutRivianBoardSerialnumber(const uint8* ucData);
extern void PRODFLASH_PutRivianBoardPartnumber(const uint8* ucData);
extern void PRODFLASH_PutManufacturingSupportMode(const uint8* ucData);
extern void PRODFLASH_PutApplicationSignature(const uint8* ucData);
extern void PRODFLASH_PutGenealogyCrc32(const uint8* ucData);
extern void PRODFLASH_PutGenealogyVersion(const uint8* ucData);
extern void PRODFLASH_PutPcbaId(const uint8* ucData);
extern void PRODFLASH_PutAuxId(const uint8* ucData);
extern void PRODFLASH_PutComponentId(const uint8* ucData);
extern void PRODFLASH_PutModeId(const uint8* ucData);
extern void PRODFLASH_PutEolCheckerByte(const uint8* ucData);

#ifdef __cplusplus
}
#endif
#endif
