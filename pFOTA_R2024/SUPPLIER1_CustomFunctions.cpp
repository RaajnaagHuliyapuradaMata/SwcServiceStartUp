#ifdef __cplusplus
extern "C"
{
#endif

#include "SUPPLIER1_CustomFunctions.hpp"
#include "ProductionFlashInterfaceX.hpp"
#include "EcuabFee_FblBlockInterface.hpp"
#include "Version.hpp"
#include "hmac_sha2.hpp"
#include "LibAutosar_Crc.hpp"
#include "fbl_diag_core.hpp"

#ifdef _RST_VS_EDITOR_SUPPORT_
#define RRAM_WUFCOPY
#else
#define RRAM_WUFCOPY __attribute__ ((section (".rwufcopy")))
#endif

/******************************************************************************/
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************************/
extern vuint8 FblDiagDownloadCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen);

FUNC(void, MYCOM_BL_STATUS_MSG_CODE) MyCom_Bl_Status_Msg_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, MYCOM_BL_STATUS_MSG_APPL_DATA) PduInfoPtr){
}

FUNC(void, MYCOM_BL_STATUS_MSG_CODE) MyCom_Bl_Status_Msg_TxConfirmation(PduIdType TxPduId){
}

/******************************************************************************/
#ifdef __cplusplus
}
#endif
/******************************************************************************/
/******************************************************************************/

uint8 ucBootFault = 0;
static volatile uint32 RRAM_WUFCOPY ulWakeupFactorRegisterContent;
static volatile uint32 RRAM_WUFCOPY ulControl;

uint32 SUPPLIER1_GetWakeupFactorRramCopy(void){
  return ulWakeupFactorRegisterContent;
}

void SUPPLIER1_SetWakeupFactorRramCopy(uint32 ulWuf){
  ulWakeupFactorRegisterContent = ulWuf;
  ulControl = !ulWakeupFactorRegisterContent;
}

void SUPPLIER1_ClearWakeupFactorRramCopy(void){
  ulWakeupFactorRegisterContent = 0;
  ulControl = 0;
}

uint8 SUPPLIER1_CustomDid_WriteFingerprint(uint8* pbDiagData, uint16* DiagDataLength){
  uint8 result;

  if(*DiagDataLength != (cDiagDataLenFingerprintApp + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }
  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }
  else{
    if(ApplFblStoreFingerprint(&pbDiagData[kDiagFmtDataIdSize+1]) == kFblOk){
        result = kFblOk;
    }
    else{
        DiagNRCConditionsNotCorrect();
        result = kFblFailed;
    }
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteBoardPartnumber(uint8* pbDiagData, uint16* DiagDataLength){
    uint8 result;

  if(*DiagDataLength != (cDiagDataLenBoardPartnumber + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutRivianBoardPartnumber(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteBoardSerialnumber(uint8* pbDiagData, uint16* DiagDataLength){
    uint8 result;

  if(*DiagDataLength != (cDiagDataLenBoardSerialnumber + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutRivianBoardSerialnumber(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteEcuPartnumber(uint8* pbDiagData, uint16* DiagDataLength){
    uint8 result;

  if(*DiagDataLength != (cDiagDataLenEcuPartnumber + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutRivianEcuPartnumber(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteEcuSerialnumber(uint8* pbDiagData, uint16* DiagDataLength){
  uint8 result;

  if(*DiagDataLength != (cDiagDataLenEcuSerialnumber + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutRivianEcuSerialnumber(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteManufSupport(uint8* pbDiagData, uint16* DiagDataLength){
  uint8 result;

  if(*DiagDataLength != (cDiagDataLenManufSupport + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutManufacturingSupportMode(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteVin(uint8* pbDiagData, uint16* DiagDataLength){
  uint8 result;

  if(*DiagDataLength != (cDiagDataLenVin + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutVin(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteAuxId(uint8* pbDiagData, uint16* DiagDataLength){
  uint8 result;

  if(*DiagDataLength != (cDiagDataLenAuxId + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutAuxId(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

uint8 SUPPLIER1_CustomDid_WriteModeId(uint8* pbDiagData, uint16* DiagDataLength){
  uint8 result;

  if(*DiagDataLength != (cDiagDataLenModeId + 2)){
    DiagNRCIncorrectMessageLengthOrInvalidFormat();
    result = kFblFailed;
  }
  else if(!GetDiagProgrammingSession()){
    DiagNRCRequestOutOfRange();
    result = kFblFailed;
  }

  else if(!FblDiagGetSecurityUnlock()){
    DiagNRCSecurityAccessDenied();
    result = kFblFailed;
  }

  else{
    PRODFLASH_PutModeId(&pbDiagData[kDiagFmtDataIdSize]);
    result = kFblOk;
  }

  return result;
}

boolean SUPPLIER1_IsMemoryInitialized(uint8* ucBuffer, uint8 ucLength){
  boolean bResult = TRUE;
  uint8 i;

  for (i=0; i<ucLength; i++){
    if(ucBuffer[i] != 0xff){
      bResult = FALSE;
    }
  }
  return bResult;
}

boolean SUPPLIER1_HwidCheck(void){
  uint8   ucID_BL[2];
  uint8   ucID_APP[2];
  boolean bResult = TRUE;

  PRODFLASH_GetAuxId(ucID_BL);
  VERSION_GetAuxId(ucID_APP, cSTRING_SIZ_AUX_ID, cAPP);

  if(ucID_APP[0] != ucID_BL[0]){
    bResult = FALSE;
  }

  if(bResult == TRUE){
    PRODFLASH_GetModeId(ucID_BL);
    VERSION_GetModeId(ucID_APP, cSTRING_SIZ_MODE_ID, cAPP);
    if((ucID_APP[0] != ucID_BL[0]) || (ucID_APP[1] != ucID_BL[1])){
      bResult = FALSE;
    }
  }

  if(bResult == TRUE){
    PRODFLASH_GetComponentId(ucID_BL);
    VERSION_GetComponentId(ucID_APP, cSTRING_SIZ_COMP_ID, cAPP);
    if((ucID_APP[0] != ucID_BL[0]) || (ucID_APP[1] != ucID_BL[1])){
      bResult = FALSE;
    }
  }

  if(bResult == TRUE){
    PRODFLASH_GetPcbaId(ucID_BL);
    VERSION_GetPcbaId(ucID_APP, cSTRING_SIZ_PCBA_ID, cAPP);
    if(ucID_APP[0] != ucID_BL[0]){
      bResult = FALSE;
    }
  }

  if(bResult == FALSE){
    ucBootFault |= 0x8;
  }

  return bResult;
}

boolean SUPPLIER1_ApplicationSignatureCheck(vuint8 *pbDiagData, tCwDataLengthType diagReqDataLen){
	tFblDiagNrc serviceNrc;
	vuint8 checkResult;
	tFblResult result;

	
	FblRealTimeSupport();

	
	serviceNrc = kDiagErrorNone;
	checkResult = kDiagCheckVerificationFailed;

	
	if((!FblDiagGetFingerprintValid())
		|| (!FblDiagGetTransferDataSucceeded())
		|| (!FblDiagGetChecksumAllowed())
		)
	{
		serviceNrc = kDiagNrcConditionsNotCorrect;
	}

	if(serviceNrc == kDiagErrorNone)
	{
		
		serviceNrc = FblMemRemapStatus(FblMemBlockEndIndication());
	}

	if(serviceNrc == kDiagErrorNone)
	{
		
		(void)FblRealTimeSupport();

		
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
		(void)SecM_InitVerification(V_NULL);
#endif
		checkResult = FblDiagDownloadCheck(pbDiagData, diagReqDataLen);
#if defined( FBL_MEM_ENABLE_VERIFY_OUTPUT )
		(void)SecM_DeinitVerification(V_NULL);
#endif
	}
	else
	{
		
		FblDiagSetError(serviceNrc);
	}

	if(DiagGetError() != kDiagErrorNone)
	{
		
		result = kFblFailed;
	}
	else
	{
		
		pbDiagData[kDiagLocFmtRoutineStatus] = checkResult;
		DiagProcessingDone(kDiagRslRoutineControlCheckRoutine);
		result = kFblOk;
	}

	return result;
}

static volatile uint32            pStartOfApplication;
static volatile uint32            pEndOfApplication;
static volatile uint32            ulLength;
static volatile uint32            ulCrc32;
static volatile tDescriptorBlock* pDescriptorBlock;
static volatile uint32            ulCrcRom;
static boolean SUPPLIER1_ApplicationCrc32Check(void){
  boolean bResult = TRUE;
  uint8   i;

  pStartOfApplication = cAPPLICATION_START_ADDRESS;
  pEndOfApplication = (uint32)VERSION_GetPointerToSHA256Hash(cAPP) - 4;
  ulLength = (uint32)pEndOfApplication - pStartOfApplication;

  ulCrc32 = Crc_CalculateCRC32((Crc_DataRefType)pStartOfApplication, ulLength, 0xFFFFFFFF);
  pDescriptorBlock = VERSION_GetPointerToDescriptorBlock(cAPP);
  ulCrcRom = pDescriptorBlock->ulCrc32App;

  for (i=0; i<4; i++){
    if(((uint8*)&ulCrc32)[i] != ((uint8*)&pDescriptorBlock->ulCrc32App)[3-i]){
      bResult = FALSE;
    }
  }

    if(bResult == FALSE){
    ucBootFault |= 0x2;
  }

  return bResult;
}

uint32 SUPPLIER1_CalcGenealogyBlockCrc32(void){
  uint8* pGenealogyBlock;
  uint32 ulCrc32;

  pGenealogyBlock = PRODFLASH_GetGenealogyBlockStartAddress();
  ulCrc32 = Crc_CalculateCRC32((Crc_DataRefType)pGenealogyBlock, (cSTRING_SIZ_FULLGENBLOCK-cSTRING_SIZ_GEN_CRC32), 0x00000000);

  return ulCrc32;
}

boolean SUPPLIER1_CustomerSpecificValidityChecks(void){
  uint8 ucResult = FALSE;
  uint8 ucManufMode;
  uint8 ucAppValid;
  uint8 ucHwidValid;
  uint8 ucEolCheckerByte;
  uint32 ulGenealogyCrc32;
  uint8 aucHashFromGenealogyBlock[cSTRING_SIZ_HASH];

  uint8 ucBlockValid = 0xFE;

  PRODFLASH_GetEolCheckerByte(&ucEolCheckerByte);
  if(ucEolCheckerByte == cPART_PASSED_SUPPLIER1_EOL){
    ulGenealogyCrc32 = SUPPLIER1_CalcGenealogyBlockCrc32();
    PRODFLASH_PutGenealogyCrc32((const uint8*)&ulGenealogyCrc32);
  }

  PRODFLASH_GetEolCheckerByte(&ucEolCheckerByte);
  if(ucEolCheckerByte != cPART_PASSED_LMC_EOL){
	  ucEolCheckerByte = cPART_HAD_FIRST_STARTUP;
	  PRODFLASH_PutEolCheckerByte((const uint8*)&ucEolCheckerByte);
  }

  PRODFLASH_GetManufacturingSupportMode(&ucManufMode);
  ApplFblNvReadApplValidity(&ucAppValid);
  ucHwidValid = SUPPLIER1_HwidCheck();
  PRODFLASH_GetApplicationSignature(aucHashFromGenealogyBlock);

  if(ucHwidValid == TRUE){
    if(ucManufMode == cMANUF_MODE_RIVIAN){
      if(ucAppValid == kEepApplConsistent)
      {
        if(SUPPLIER1_ApplicationCrc32Check() == TRUE)
        {
          ApplFblNvWriteValidityFlags(&ucBlockValid);
          ucResult = TRUE;
        }
      }
      else
      {
         ucBootFault |= 0x1;
         ucResult = TRUE;
      }
    }
    else{
      if(SUPPLIER1_ApplicationCrc32Check() == TRUE)
      {
        ApplFblNvWriteValidityFlags(&ucBlockValid);
        ucResult = TRUE;
      }
    }
  }

  return ucResult;
}

uint8 SUPPLIER1_GetFaultFlag(void){
  return ucBootFault;
}

#ifdef __cplusplus
}
#endif
