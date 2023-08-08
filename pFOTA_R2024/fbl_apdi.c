#include "fbl_inc.hpp"

#include "SUPPLIER1_Seca.hpp"
#include "ProductionFlashInterfaceX.hpp"
#include "EcuabFee_FblBlockInterface.hpp"
#include "SUPPLIER1_CustomFunctions.hpp"
#include "Version.hpp"
#include "McalDio.hpp"

#if( FBLKBAPI_FRAMEDIAG_UDS1_VERSION != 0x0403u ) || \
    ( FBLKBAPI_FRAMEDIAG_UDS1_RELEASE_VERSION != 0x00u )
# error "Error in FBL_APDI.C: Source and header file are inconsistent!"
#endif

#if( FBLKBAPI_FRAMEDIAG_UDS1_VERSION != _FBLKBAPI_FRAMEDIAG_OEM_VERSION )
# error "Error in fbl_apdi.c: Source and v_ver.h are inconsistent!"
#endif
#if( FBLKBAPI_FRAMEDIAG_UDS1_RELEASE_VERSION != _FBLKBAPI_FRAMEDIAG_OEM_RELEASE_VERSION )
# error "Error in fbl_apdi.c: Source and v_ver.h are inconsistent!"
#endif

#if !defined( kDiagRslReadDataByIdentifier )
# define kDiagRslReadDataByIdentifier kDiagRslWriteDataByIdentifier
#endif

#if !defined( GetSecurityUnlock )
# define GetSecurityUnlock() FblDiagGetSecurityUnlock()
#endif

#if defined( FBL_ENABLE_USERSERVICE )

void ApplDiagUserService( vuint8 * pbDiagData, tTpDataType diagReqDataLen ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pbDiagData;
   (void)diagReqDataLen;
#endif

   switch(diagServiceCurrent){
      default:
      {
         DiagNRCServiceNotSupported();
         break;
      }
   }
}
#endif

#if defined( FBL_ENABLE_USERSUBFUNCTION )

void ApplDiagUserSubFunction( vuint8 * pbDiagData, tTpDataType diagReqDataLen ){
  uint8 ucResult;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)diagReqDataLen;
#endif

   switch(diagServiceCurrent){
      case kDiagSidSecurityAccess:
      {
        if(pbDiagData[0] == 0x03)
        {
          if(SECA_Level03_ProcessRequestSeed() == kFblOk)
          {
            DiagProcessingDone(kDiagRslSecurityAccessSeed);
          }
          else
          {
            DiagNRCConditionsNotCorrect();
          }
        }

        else if(pbDiagData[0] == 0x04)
        {
          DiagExRCRResponsePending(kForceSendResponsePending);

          ucResult = SECA_Level03_ProcessSendKey(pbDiagData);

          switch(ucResult)
          {
            case kFblOk:
            DiagProcessingDone(kDiagRslSecurityAccessKey);
            break;

            case 0x01:
            DiagNRCRequestSequenceError();
            break;

            case 0x02:
            DiagNRCInvalidKey();
            break;

            default:
            DiagNRCConditionsNotCorrect();
            break;
          }

        }

        else
        {
          DiagNRCSubFunctionNotSupported();
        }
        break;
      }

      default:
      {
         DiagNRCSubFunctionNotSupported();
         break;
      }
   }
}
#endif

#if defined( FBL_ENABLE_USERROUTINE )

void ApplDiagUserRoutine( vuint8 * pbDiagData, tTpDataType diagReqDataLen ){
   uint16 diagRespDataLen = 0;
   uint8  ucSubFunc;
   uint16 ushRoutineId;
   uint8  ucSubContent;
   uint8  aucKey[SEC_KEY_LENGTH];
   uint8  ucCount;

   ucSubFunc = pbDiagData[0];
   ushRoutineId = (pbDiagData[1] << 8) + pbDiagData[2];

   if(ucSubFunc != 0x1){
      DiagNRCRequestOutOfRange();
   }

   else if(ushRoutineId != 0x0207){
      DiagNRCRequestOutOfRange();
   }

   else if((diagReqDataLen-4) != SEC_KEY_LENGTH){
      DiagNRCIncorrectMessageLengthOrInvalidFormat();
   }

   else if(!GetSecurityUnlock()){
      DiagNRCSecurityAccessDenied();
   }

   else{
     ucSubContent = pbDiagData[3];

     for (ucCount = 0; ucCount < SEC_KEY_LENGTH; ucCount++)
     {
       aucKey[ucCount] = pbDiagData[4+ucCount];
     }

#if(SEED_KEY_ALGORITHM==SEED_KEY_USE_HMAC_SHA256)
	 switch(ucSubContent)
     {
       case 0x01:
       ApplFblNvWriteSecKey_UDSBOOTKEY(aucKey);
       pbDiagData[4] = 0x00;
       diagRespDataLen = 5;
       break;

       case 0x02:
       ApplFblNvWriteSecKey_UDSAPPKEY(aucKey);
       pbDiagData[4] = 0x00;
       diagRespDataLen = 5;
       break;

       case 0x03:
       ApplFblNvWriteSecKey_UDSMSGKEY(aucKey);
       pbDiagData[4] = 0x00;
       diagRespDataLen = 5;
       break;

       default:
       DiagNRCRequestOutOfRange();
       break;
     }
#endif
   }
   diagRespDataLen = 5;
   DiagProcessingDone(diagRespDataLen);

}
#endif

void ApplFblReadDataByIdentifier( vuint8 * pbDiagData, tTpDataType diagReqDataLen ){
   typedef struct {
      vuint16   did;
      vuint16   maxSize;
   } tDid;

   static V_MEMROM1 tDid V_MEMROM2 didTable[] =
   {
      { 0xF123u, 3u  },

      { cCustSubFuncBootloaderSWID     , cDiagDataLenBootloaderSWID     },
      { cCustSubFuncApplicationSWID    , cDiagDataLenApplicationSWID    },
      { cCustSubFuncFingerprintFbl     , cDiagDataLenFingerprintFbl     },
      { cCustSubFuncFingerprintApp     , cDiagDataLenFingerprintApp     },
      { cCustSubFuncEcuSerialnumber    , cDiagDataLenEcuSerialnumber    },
      { cCustSubFuncBoardSerialnumber  , cDiagDataLenBoardSerialnumber  },
      { cCustSubFuncEcuPartnumber      , cDiagDataLenEcuPartnumber      },
      { cCustSubFuncBoardPartnumber    , cDiagDataLenBoardPartnumber    },
      { cCustSubFuncCompAndSwType      , cDiagDataLenCompAndSwType      },
      { cCustSubFuncManufSupport       , cDiagDataLenManufSupport       },
      { cCustSubFuncGenealogyVersion   , cDiagDataLenGenealogyVersion   },
      { cCustSubFuncGenealogyCrc32     , cDiagDataLenGenealogyCrc32     },
      { cCustSubFuncFullGenealogyBlock , cDiagDataLenFullGenealogyBlock },
      { cCustSubFuncEepromBlockStatus  , cDiagDataLenEepromBlockStatus  },
      { cCustSubFuncAuxId              , cDiagDataLenAuxId              },
      { cCustSubFuncModeId             , cDiagDataLenModeId             },
      { cCustSubFuncApplicationSig     , cDiagDataLenApplicationSig     },
      { cCustSubFuncVin                , cDiagDataLenVin                },
      { cCustSubFuncActiveDiagSession  , cDiagDataLenActiveDiagSession  },
      { cCustSubFuncTfsChangesetFbl    , cDiagDataLenTfsChangesetFbl    }

   };

   vuint16 diagRespDataLen;
   vuint16 didIdx;
   vuint16 outIdx;
   vuint16 outIdxAdd;
   vuint16 currentDid;
   vuint16 didNo;
   vuint8  didBuffer[(FBL_MAX_DID_COUNT << 1)];
   vuint16 i, j;
   vuint8* diagData;

   if(   (diagReqDataLen < kDiagRqlReadDataByIdentifier)
       || ((diagReqDataLen % 2) != 0)
      ){
      DiagNRCIncorrectMessageLengthOrInvalidFormat();
      return;
   }

   didNo = (diagReqDataLen / 2);

   if(didNo > FBL_MAX_DID_COUNT){
      DiagNRCRequestOutOfRange();
      return;
   }

   for (i = 0u; i < diagReqDataLen; i++){
      didBuffer[i] = pbDiagData[i];
   }

   outIdx = 0u;
   didIdx = 0u;
   for (i = 0u; i < didNo; i++){
      currentDid =  ((vuint16)didBuffer[didIdx]) << 8;
      currentDid |= (vuint16)didBuffer[didIdx + 1];

      diagData = &pbDiagData[outIdx];

      diagData[0] = didBuffer[didIdx];
      diagData[1] = didBuffer[didIdx + 1];

      didIdx += 2u;

      outIdxAdd = 0u;
      for (j = 0u; j < (sizeof(didTable)/sizeof(tDid)); j++)
      {
         if(didTable[j].did == currentDid)
         {
            outIdxAdd = didTable[j].maxSize + kDiagRslReadDataByIdentifier;
            break;
         }
      }

      if(outIdxAdd != 0u)
      {
         if((outIdx + outIdxAdd) > (FBL_DIAG_BUFFER_LENGTH - 1u))
         {
            DiagNRCRequestOutOfRange();
            return;
         }

         switch(currentDid)
         {
            case 0xF123u:
            {
               DiagNRCSubFunctionNotSupported();
               break;
            }

            case cCustSubFuncBootloaderSWID:
            {
              diagData[2] = 1;
              diagData += 3;
              diagData += VERSION_GetEcuProgramInformationPart1(diagData, cSTRING_ECU_PROGRAM_INFO_1_LENGTH, cFBL);
              diagData += VERSION_GetEcuProgramInformationPart2(diagData, cSTRING_ECU_PROGRAM_INFO_2_LENGTH, cFBL);
              diagData += FEEFBL_GetTesterSerialNumber(diagData, cFBL);
              diagData += FEEFBL_GetProgrammingDate(diagData, cFBL);
              break;
            }

            case cCustSubFuncApplicationSWID:
            {
              diagData[2] = 1;
              diagData += 3;
              diagData += VERSION_GetEcuProgramInformationPart1(diagData, cSTRING_ECU_PROGRAM_INFO_1_LENGTH, cAPP);
              diagData += VERSION_GetEcuProgramInformationPart2(diagData, cSTRING_ECU_PROGRAM_INFO_2_LENGTH, cAPP);
              diagData += FEEFBL_GetTesterSerialNumber(diagData, cAPP);
              diagData += FEEFBL_GetProgrammingDate(diagData, cAPP);
              break;
            }

            case cCustSubFuncFingerprintFbl:
            {
              diagData[2] = 1;
              diagData += 3;
              diagData += FEEFBL_GetTesterSerialNumber(diagData, cFBL);
              diagData += FEEFBL_GetProgrammingDate(diagData, cFBL);
              break;
            }

            case cCustSubFuncFingerprintApp:
            {
              diagData[2] = 1;
              diagData += 3;
              diagData += FEEFBL_GetTesterSerialNumber(diagData, cAPP);
              diagData += FEEFBL_GetProgrammingDate(diagData, cAPP);
              break;
            }

            case cCustSubFuncEcuSerialnumber:
            {
              (void)PRODFLASH_GetRivianEcuSerialNumber(&diagData[2]);
              break;
            }

            case cCustSubFuncBoardSerialnumber:
            {
              (void)PRODFLASH_GetRivianBoardSerialNumber(&diagData[2]);
              break;
            }

            case cCustSubFuncEcuPartnumber:
            {
              (void)PRODFLASH_GetRivianEcuPartNumber(&diagData[2]);
              break;
            }

            case cCustSubFuncBoardPartnumber:
            {
              (void)PRODFLASH_GetRivianBoardPartNumber(&diagData[2]);
              break;
            }

            case cCustSubFuncCompAndSwType:
            {
              (void)VERSION_GetComponentAndSwType(&diagData[2], cSTRING_SIZ_COMPANDSWTYPE, cFBL);
              break;
            }

            case cCustSubFuncManufSupport:
            {
              (void)PRODFLASH_GetManufacturingSupportMode(&diagData[2]);
              break;
            }

            case cCustSubFuncGenealogyVersion:
            {
              (void)PRODFLASH_GetGenealogyVersion(&diagData[2]);
              break;
            }

            case cCustSubFuncGenealogyCrc32:
            {
              (void)PRODFLASH_GetGenealogyCrc32(&diagData[2]);
              break;
            }

            case cCustSubFuncFullGenealogyBlock:
            {
              diagData+=2;
              diagData += PRODFLASH_GetGenealogyVersion(diagData);
              diagData += PRODFLASH_GetComponentId(diagData);
              diagData += PRODFLASH_GetPcbaId(diagData);
              diagData += PRODFLASH_GetAuxId(diagData);
              diagData += PRODFLASH_GetModeId(diagData);
              diagData += PRODFLASH_GetRivianBoardPartNumber(diagData);
              diagData += PRODFLASH_GetRivianBoardSerialNumber(diagData);
              diagData += PRODFLASH_GetRivianEcuPartNumber(diagData);
              diagData += PRODFLASH_GetRivianEcuSerialNumber(diagData);
              diagData += PRODFLASH_GetApplicationSignature(diagData);
              diagData += PRODFLASH_GetGenealogyCrc32(diagData);
              break;
            }

            case cCustSubFuncEepromBlockStatus:
            {
              diagData[2] = 0xff;
              diagData[3] = 0xff;
              break;
            }

            case cCustSubFuncAuxId:
            {
              PRODFLASH_GetAuxId(&diagData[2]);
              break;
            }

            case cCustSubFuncModeId:
            {
              PRODFLASH_GetModeId(&diagData[2]);
              break;
            }

            case cCustSubFuncApplicationSig:
            {
              PRODFLASH_GetApplicationSignature(&diagData[2]);
              break;
            }

            case cCustSubFuncVin:
            {
              PRODFLASH_GetVin(&diagData[2]);
              break;
            }

            case cCustSubFuncActiveDiagSession:
            {
              if(GetDiagDefaultSession() == TRUE)
              {
                diagData[2] = 1;
              }
              else if(GetDiagProgrammingSession() == TRUE)
              {
                diagData[2] = 2;
              }
              else if(GetDiagExtendedSession() == TRUE)
              {
                diagData[2] = 3;
              }
              else
              {
                diagData[2] = 0;
              }
              break;
            }

            case cCustSubFuncTfsChangesetFbl:
            {
              VERSION_GetTfsChangeset(&diagData[2], cSTRING_SIZ_TFSCS, cFBL);
              break;
            }

            default:
            {
               DiagNRCSubFunctionNotSupported();
               break;
            }
         }

         outIdx += outIdxAdd;
      }
   }

   if(outIdx == 0){
      DiagNRCRequestOutOfRange();
   }

   diagRespDataLen = outIdx;

   DiagProcessingDone(diagRespDataLen);
}

vuint8 ApplFblWriteDataByIdentifier( vuint8 * pbDiagData, tTpDataType diagReqDataLen ){
   vuint16 diagFmtDataId;
   vuint8 result;

#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)diagReqDataLen;
#endif

   result = kFblOk;

   diagFmtDataId =  (vuint16)pbDiagData[0] << 8;
   diagFmtDataId |= (vuint16)pbDiagData[1];

   switch(diagFmtDataId){
      case (kDiagWriteFingerprint):
      {
         if(DiagDataLength != kDiagRqlWriteDataByIdentifierFingerPrint)
         {
            DiagNRCIncorrectMessageLengthOrInvalidFormat();
            result = kFblFailed;
         }
         else if(!GetDiagProgrammingSession())
         {
            DiagNRCRequestOutOfRange();
            result = kFblFailed;
         }

         else if(!GetSecurityUnlock())
         {
            DiagNRCSecurityAccessDenied();
            result = kFblFailed;
         }
         else
         {
            if(ApplFblStoreFingerprint(&pbDiagData[kDiagFmtDataIdSize]) == kFblOk)
            {
               result = kDiagReturnValidationOk;
            }
            else
            {
               DiagNRCConditionsNotCorrect();
               result = kFblFailed;
            }
         }
      }
      break;

      default:
      {
         DiagNRCRequestOutOfRange();
         result = kFblFailed;
      }
      break;
   }

   return result;
}

#if defined( FBL_ENABLE_DEBUG_STATUS )

void ApplFblInitErrStatus( void ){
   errStatFlashDrvVersion[0] = 0;
   errStatFlashDrvVersion[1] = 0;
   errStatFlashDrvVersion[2] = 0;
   errStatFlashDrvErrorCode = 0;
   errStatErrorCode = 0;
   errStatFblStates = 0;
   errStatLastServiceId = 0;
   errStatDescriptor.blockNr = 0;
   errStatDescriptor.blockStartAddress = 0;
}
#endif

