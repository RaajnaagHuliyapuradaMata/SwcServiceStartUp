#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

#include "fbl_inc.hpp"

#define cCustSubFuncBootloaderSWID      0xF180u
#define cCustSubFuncApplicationSWID     0xF181u
#define cCustSubFuncCalibrationsSWID    0xF182u
#define cCustSubFuncFingerprintFbl      0xF183u
#define cCustSubFuncFingerprintApp      0xF184u
#define cCustSubFuncBoardPartnumber     0xF112u
#define cCustSubFuncBoardSerialnumber   0xF113u
#define cCustSubFuncEcuPartnumber       0xF191u
#define cCustSubFuncEcuSerialnumber     0xF18cu
#define cCustSubFuncCompAndSwType       0x0101u
#define cCustSubFuncModuleToProgram     0x0102u
#define cCustSubFuncManufSupport        0xF018u
#define cCustSubFuncGenealogyVersion    0xF110u
#define cCustSubFuncGenealogyCrc32      0xF116u
#define cCustSubFuncFullGenealogyBlock  0xF117u
#define cCustSubFuncEepromBlockStatus   0xF11Bu
#define cCustSubFuncAuxId               0xF11Cu
#define cCustSubFuncModeId              0xF11Du
#define cCustSubFuncApplicationSig      0xF200u
#define cCustSubFuncVin                 0xF190u
#define cCustSubFuncActiveDiagSession   0xF186u
#define cCustSubFuncTfsChangesetFbl     0xF101u

#define cDiagDataLenBootloaderSWID           18u
#define cDiagDataLenApplicationSWID          18u
#define cDiagDataLenCalibrationsSWID         18u
#define cDiagDataLenFingerprintFbl           24u
#define cDiagDataLenFingerprintApp           24u
#define cDiagDataLenEcuSerialnumber          18u
#define cDiagDataLenBoardSerialnumber        18u
#define cDiagDataLenEcuPartnumber            35u
#define cDiagDataLenBoardPartnumber          35u
#define cDiagDataLenCompAndSwType            3u
#define cDiagDataLenModuleToProgram          1u
#define cDiagDataLenManufSupport             1u
#define cDiagDataLenGenealogyVersion         1u
#define cDiagDataLenGenealogyCrc32           4u
#define cDiagDataLenFullGenealogyBlock       133u
#define cDiagDataLenEepromBlockStatus        2u
#define cDiagDataLenAuxId                    1u
#define cDiagDataLenModeId                   2u
#define cDiagDataLenApplicationSig           16u
#define cDiagDataLenVin                      17u
#define cDiagDataLenActiveDiagSession        1u
#define cDiagDataLenTfsChangesetFbl          8u

#define cFAULT_NO                     0u
#define cFAULT_HWID_MISMATCH          1u
#define cFAULT_HMAC_MISMATCH          2u
#define cFAULT_MEMORY_CORRUPT         3u

#define cMANUF_MODE_SUPPLIER1        0
#define cMANUF_MODE_RIVIAN        1

typedef struct stBootIdType{
  uint8 ucFaultFlag:4;
  uint8 ucVersion:4;
  uint8 ucLsbCompId;
  uint8 ucPcbaId;
  uint8 ucAuxId;
  uint16 ucModeId;
  uint8 ucUnused;
  uint8 ucCurrentSw;
}BootIdType;

extern uint8 SUPPLIER1_CustomDid_WriteFingerprint(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteBoardPartnumber(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteBoardSerialnumber(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteEcuPartnumber(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteEcuSerialnumber(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteManufSupport(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteVin(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteAuxId(uint8* pbDiagData, uint16* DiagDataLength);
extern uint8 SUPPLIER1_CustomDid_WriteModeId(uint8* pbDiagData, uint16* DiagDataLength);
extern boolean SUPPLIER1_IsMemoryInitialized(uint8* ucBuffer, uint8 ucLength);
extern boolean SUPPLIER1_ApplicationSignatureCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);
extern boolean SUPPLIER1_HwidCheck(void);
extern uint32 SUPPLIER1_CalcGenealogyBlockCrc32(void);
extern boolean SUPPLIER1_CustomerSpecificValidityChecks(void);
extern uint8 SUPPLIER1_GetFaultFlag(void);
extern void SUPPLIER1_SetWakeupFactorRramCopy(uint32 ulWuf);
extern uint32 SUPPLIER1_GetWakeupFactorRramCopy(void);
extern void SUPPLIER1_ClearWakeupFactorRramCopy(void);

#ifdef __cplusplus
}
#endif
