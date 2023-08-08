#include "fbl_inc.hpp"

#include "EcuabCanTrcv.hpp"
#include "version.hpp"
#include "SUPPLIER1_Seca.hpp"

# include "SwcServiceDet.hpp"
# if(DET_ENABLED == STD_ON)
#   include "McalCan.hpp"
#   include "SwcServiceCanTp.hpp"
# endif
#include "BrsHw.hpp"
#include "EcuabCanIf.hpp"

#include "dr7f701013.dvf.hpp"
#if( FBLKBAPI_UDS1_VERSION != 0x0602u ) || \
    ( FBLKBAPI_UDS1_RELEASE_VERSION != 0x00u )
# error "Error in fbl_apXX.c: Source and Header file are inconsistent!"
#endif

#if( FBLKBAPI_UDS1_VERSION != _FBLKBAPI_OEM_VERSION ) || \
    ( FBLKBAPI_UDS1_RELEASE_VERSION != _FBLKBAPI_OEM_RELEASE_VERSION )
# error "Error in fbl_apXX.c: Source and v_ver.h are inconsistent!"
#endif

#if( FBLKBAPI_BRS_VERSION != 0x0100u ) || \
    ( FBLKBAPI_BRS_RELEASE_VERSION != 0x02u )
# error "Error in fbl_apxx.c: Source and header file are inconsistent!"
#endif
#if( FBLKBAPI_BRS_VERSION != _FBLKBAPI_HW_VERSION ) || \
    ( FBLKBAPI_BRS_RELEASE_VERSION != _FBLKBAPI_HW_RELEASE_VERSION )
# error "Error in fbl_apxx.c: Source and v_ver.h are inconsistent!"
#endif
#if( FBLKBAPI_VERSION != 0x0201u ) || \
    ( FBLKBAPI_RELEASE_VERSION != 0x00u )
# error "Error in FBL_APxx.C: Source and header file are inconsistent!"
#endif
#if( FBLKBAPI_VERSION != _FBLKBAPI_VERSION ) || \
    ( FBLKBAPI_RELEASE_VERSION != _FBLKBAPI_RELEASE_VERSION )
# error "Error in FBL_APxx.C: Source and V_VER.H are inconsistent!"
#endif

#if( FBLKBAPI_FRAME_UDS1_VERSION != 0x0502u ) || \
    ( FBLKBAPI_FRAME_UDS1_RELEASE_VERSION != 0x00u )
# error "Error in FBL_AP.C: Source and header file are inconsistent!"
#endif

#if( FBLKBAPI_FRAME_UDS1_VERSION != _FBLKBAPI_FRAME_OEM_VERSION )
# error "Error in fbl_apxx.c: Source and v_ver.h are inconsistent!"
#endif
#if( FBLKBAPI_FRAME_UDS1_RELEASE_VERSION != _FBLKBAPI_FRAME_OEM_RELEASE_VERSION )
# error "Error in fbl_apxx.c: Source and v_ver.h are inconsistent!"
#endif

#define kSeedAlreadyRequested             0x00u
#define kNewSeedRequest                   0x01u

#define MOSCC_AMPSEL_20_24_MHZ 0x00u
#define MOSCC_AMPSEL_16_20_MHZ 0x01u
#define MOSCC_AMPSEL_08_16_MHZ 0x02u
#define MOSCC_AMPSEL_08_MHZ    0x03u

#define MOSCC_AMPSEL    (MOSCC_AMPSEL_16_20_MHZ | 0x04)

#define MOSCST_STABILISATION  0xFFFFu

#define MOSCE_ENTRG     0x01u
#define MOSCE_DISTRG    0x02u

#define MOSCS_CLKACT    0x07u

#define PLLC_DIVIDER_VALUE    0x27u
#define PLLC_DIV_SEL          0x02u
#define PLLC_MOSC_FREQ        0x01u
#define PLLC_BSEL             0x00u

#define PLLC_INIT_VAL         ((((PLLC_BSEL<<16)|(PLLC_MOSC_FREQ<<11))|(PLLC_DIV_SEL<<8))|PLLC_DIVIDER_VALUE)

#define PLLE_ENTRG      0x01u
#define PLLE_DISTRG     0x02u

#define PLLS_CLKACT     0x07u

#define CKSC_CLOCK_DIVIDER 0x01u
#define CKSC_CLOCK_SOURCE  0x03u

# if defined( SEC_BYTE_ARRAY_SEED )
#  define FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED
# endif
# if defined( SEC_WORD_ARRAY_SEED )
#  define FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED
# endif
# if defined( SEC_BYTE_ARRAY_KEY )
#  define FBL_APPL_ENABLE_SEC_BYTE_ARRAY_KEY
# endif

#if defined( FBL_ENABLE_MULTIPLE_NODES ) || \
    defined( FBL_CW_ENABLE_MULTIPLE_NODES )
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 fblEcuHandle;
#endif

___asm(.globl __FBLENTRY)
___asm(__FBLENTRY:)
___asm(jr _fblmain)

#if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED ) || \
    defined( FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED )
V_MEMRAM0 static V_MEMRAM1 SecM_WordType V_MEMRAM2 secSeedInput[2u];
#else
V_MEMRAM0 static V_MEMRAM1 SecM_SeedType V_MEMRAM2 secSeedInput;
#endif
V_MEMRAM0 static V_MEMRAM1 SecM_SeedType V_MEMRAM2 seed;
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 securitySeedResponse;

static void InitCanPorts(void);
static void InitClocks(void);

void ApplFblInit( void ){
   vuint8 dummyNull[kEepSizeFingerprint];
   vuintx index;

  InitClocks();
  InitCanPorts();
  GPIO_Init();

  #ifdef FBL_SUPPLIER1_NVM
    ApplFblNvInit();
  #else
    (void)EepromDriver_InitSync(V_NULL);
  #endif

  VERSION_SyncPartnumber_315_433_from_Flash_to_Flash();

   for (index = 0u; index < kEepSizeFingerprint; index++){
      dummyNull[index] = 0x00u;
   }
   (void)ApplFblStoreFingerprint(dummyNull);

   securitySeedResponse = kNewSeedRequest;

}

void ApplFblStartup( vuint8 initposition ){
   switch(initposition){
      case (kFblInitPreCallback | kFblInitBaseInitialization):
      {
         break;
      }
      case (kFblInitPostCallback | kFblInitBaseInitialization):
      {
         ApplFblInit();
         break;
      }
      case (kFblInitPreCallback | kFblInitFblCommunication):
      {
         break;
      }
      case (kFblInitPostCallback | kFblInitFblCommunication):
      {
         break;
      }
      case (kFblInitPreCallback | kFblInitFblFinalize):
      {
         break;
      }
      case (kFblInitPostCallback | kFblInitFblFinalize):
      {
         break;
      }
      default:
      {
         assertFblInternal(0u, kFblSysAssertParameterOutOfRange);
         break;
      }
   }
}

tFblResult ApplFblCheckProgConditions( void ){
# if defined( FBL_DIAG_ENABLE_CHECK_PROGRAMMING_PRECONDITIONS )
   vuint16 diagRespDataLen;
#endif
   tFblResult result;

   result = kFblOk;

#if defined( FBL_DIAG_ENABLE_CHECK_PROGRAMMING_PRECONDITIONS )
   diagRespDataLen = 3;
#endif

#if defined( FBL_DIAG_ENABLE_CHECK_PROGRAMMING_PRECONDITIONS )

   DiagProcessingDone(diagRespDataLen);
#endif

  return result;
}

tFblResult ApplFblCheckConditions( vuint8 * pbDiagData, tTpDataType diagReqDataLen ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)pbDiagData;
   (void)diagReqDataLen;
#endif

   return kFblOk;
}

vuint8 ApplFblCheckProgDependencies( void ){
   vuint8 result;
#if defined( FBL_ENABLE_PRESENCE_PATTERN )
   vuintx i;
#endif
   tBlockDescriptor iterBlock;
   tFblLbtBlockFilter blockFilter;
   vuint8 validityFlags[kEepSizeValidityFlags];

   result = kDiagCheckCompatibilityOk;

   if(!IsLogicalBlockTableValid()){
      result = kDiagCheckCompatibilityFailed;
   }
   else{
#if defined( FBL_ENABLE_PRESENCE_PATTERN )
      for (i = 0u; i < sizeof(validityFlags); i++)
      {
         validityFlags[i] = 0xFFu;
      }
      FblLbtBlockFilterInit(&blockFilter);
      iterBlock = FblLbtBlockFirst(&blockFilter);
      while (FblLbtBlockDone() == FALSE)
      {
         {
            if(FblNvPatternGet(&iterBlock, kFblNvPatternId_BlockValidity) == kFblOk)
            {
               validityFlags[(iterBlock.blockNr >> 3u)] &= FblInvert8Bit(1u << (iterBlock.blockNr & 7u));
            }
         }

         iterBlock = FblLbtBlockNext();
      }
#else
      if(ApplFblNvReadValidityFlags(validityFlags) != kFblOk)
      {
         result = kDiagCheckCompatibilityFailed;
      }
#endif
      if(result == kDiagCheckCompatibilityOk)
      {
         FblLbtBlockFilterInit(&blockFilter);
         FblLbtBlockFilterSetMandatoryType(&blockFilter, TRUE);
         iterBlock = FblLbtBlockFirst(&blockFilter);
         while ((FblLbtBlockDone() == FALSE) && (result == kDiagCheckCompatibilityOk))
         {
            if((validityFlags[(iterBlock.blockNr >> 3u)] & (1u << (iterBlock.blockNr & 7u))) != 0u)
            {
               result = kDiagCheckCompatibilityBlockMissing;
            }

            iterBlock = FblLbtBlockNext();
         }
      }
   }

#if defined( FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK )
#else

   if(result == kDiagCheckCompatibilityOk){
      if(ApplFblValidateApp() != kFblOk)
      {
         result = kDiagCheckCompatibilityFailed;
      }
   }
#endif

   return result;
}

void ApplTrcvrNormalMode( void ){
		vuint32 ulWakeupFactorRegisterContent;
		ulWakeupFactorRegisterContent = WUF0;
		if(ulWakeupFactorRegisterContent == FALSE)
		{
			EcuabTrcv_Normal();
		}
}

void ApplTrcvrSleepMode( void ){
  EcuabTrcv_Standby();
}

void ApplFblSetVfp( void ){
#if defined (BRSHW_VOLTAGE_FOR_FLASH_PROGRAMMING_AVAILABLE)
   BrsHwSetVfp();
#endif
}

void ApplFblResetVfp( void ){
#if defined (BRSHW_VOLTAGE_FOR_FLASH_PROGRAMMING_AVAILABLE)
   BrsHwResetVfp();
#endif
}

void ApplFblReset( void ){
   BrsHwSoftwareResetECU();
}

# define FBLAP_RAMCODE_START_SEC_CODE
# include "MemMap.hpp"

vuint8 ApplFblSecuritySeedInit( void ){
#if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED ) || \
    defined( FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED )
   secSeedInput[1u] += secSeedInput[0u];
   secSeedInput[0u]  = FblGetTimerValue();
#else
   secSeedInput.seedY += secSeedInput.seedX;
   secSeedInput.seedX = FblGetTimerValue();
#endif

   return kFblOk;
}
# define FBLAP_RAMCODE_STOP_SEC_CODE
# include "MemMap.hpp"

vuint8 ApplFblSecuritySeed( void ){
   vuint8 result;
#if defined( FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED )
   vuintx i, j;
#endif

   result = kFblOk;

   if(securitySeedResponse != kSeedAlreadyRequested){
#if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED ) || \
    defined( FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED )

      while (0u == secSeedInput[1u])
      {
         (void)ApplFblSecuritySeedInit();
      }

# if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED )
#  if( SEC_WORD_TYPE_SIZE > SEC_SEED_LENGTH )
      FblMemSetInteger(SEC_SEED_LENGTH, secSeedInput[1u], seed);
#  else
      FblMemSetInteger(SEC_WORD_TYPE_SIZE, secSeedInput[1u], seed);
#  endif
# else
      seed[0u] = secSeedInput[1u];
# endif

      if(SECM_OK == SecM_GenerateSeed(&seed))
      {
# if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED )
#  if( SEC_WORD_TYPE_SIZE > SEC_SEED_LENGTH )
         secSeedInput[0u] += FblMemGetInteger(SEC_SEED_LENGTH, seed);
#  else
         secSeedInput[0u] += FblMemGetInteger(SEC_WORD_TYPE_SIZE, seed);
#  endif
# else
         secSeedInput[0u] += seed[0u];
# endif
      }
      else
      {
         result = kFblFailed;
      }
#else

      while ((0u == secSeedInput.seedX) || (0u == secSeedInput.seedY))
      {
         (void)ApplFblSecuritySeedInit();
      }

      if(SECM_OK == SecM_GenerateSeed(&secSeedInput))
      {
         seed = secSeedInput;
      }
      else
      {
         result = kFblFailed;
      }
#endif
   }

   if(kFblOk == result){
#if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED )
      (void)MEMCPY(&DiagBuffer[kDiagFmtSeedKeyStart], seed, SEC_SEED_LENGTH);
#elif defined( FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED )
      for ((i = 0u, j = kDiagFmtSeedKeyStart); i < SEC_SEED_WORD_LENGTH; (i++, j += SEC_WORD_TYPE_SIZE))
      {
         FblMemSetInteger(SEC_WORD_TYPE_SIZE, seed[i], &DiagBuffer[j]);
      }
#else
      FblMemSetInteger(SEC_SEED_LENGTH, seed.seedX, &DiagBuffer[kDiagFmtSeedKeyStart]);
#endif

      securitySeedResponse = kSeedAlreadyRequested;
   }

   return result;
}

vuint8 ApplFblSecurityKey( void ){
   vuint8 result;

#if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_KEY )
#else
   SecM_KeyType key;
#endif

   result = kFblFailed;

   securitySeedResponse = kNewSeedRequest;

#if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_KEY )
   if(SECM_OK == SecM_CompareKey(&DiagBuffer[kDiagFmtSeedKeyStart], seed))
#else
   key = FblMemGetInteger(SEC_KEY_LENGTH, &DiagBuffer[kDiagFmtSeedKeyStart]);
   if(SECM_OK == SecM_CompareKey(key, seed))
#endif
   {
      result = kFblOk;
   }

   return result;
}

vuint8 ApplFblSecurityInit( void ){
#if defined( FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED ) || \
    defined( FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED )
   secSeedInput[0u] = 0u;
   secSeedInput[1u] = 0u;

#else
   secSeedInput.seedX = 0u;
   secSeedInput.seedY = 0u;
#endif

   return kFblOk;
}

#if defined( FBL_ENABLE_DATA_PROCESSING )

tFblResult ApplFblInitDataProcessing( tProcParam * procParam ){
   tFblResult result;

   result = kFblOk;

   return result;
}

tFblResult ApplFblDataProcessing( tProcParam * procParam ){
   tFblResult result;

   result = kFblOk;

   if(procParam->dataLength > procParam->dataOutMaxLength){
      procParam->dataOutLength = procParam->dataOutMaxLength;
   }
   else{
      procParam->dataOutLength = procParam->dataLength;
   }

   procParam->dataLength = procParam->dataOutLength;

   FblLookForWatchdogVoid();
   (void)MEMCPY(procParam->dataOutBuffer, procParam->dataBuffer, procParam->dataOutLength);

   return result;
}

tFblResult ApplFblDeinitDataProcessing( tProcParam * procParam ){
   tFblResult result;

   result = ApplFblDataProcessing(procParam);

   return result;
}
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )

tFblResult ApplFblInitStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam ){
   tFblResult result;

   result = kFblFailed;

   return result;
}

tFblResult ApplFblStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam ){
   tFblResult result;

   result = kFblFailed;

   return result;
}

tFblResult ApplFblFinalizeStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam ){
   tFblResult result;

   result = kFblFailed;

   return result;
}

tFblResult ApplFblDeinitStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam ){
   tFblResult result;

   result = kFblFailed;

   return result;
}
#endif

#if defined( FBL_ENABLE_APPL_TASK ) || \
    defined( FBL_ENABLE_APPL_TIMER_TASK )

typedef struct{
  uint32 rRSCAN0RMNB;
  uint32 rRSCAN0GCTR;
  uint32 rRSCAN0TMIEC0;
  uint32 rRSCAN0GSTS;
  uint32 rRSCAN0C0STS;
  uint32 rRSCAN0GCFG;
  uint32 rRSCAN0C0CFG;
  uint32 rRSCAN0C0CTR;
  uint32 rRSCAN0RFCC0;
  uint32 rRSCAN0RFSTS0;
  uint32 rRSCAN0GAFLCFG0;
  uint32 rRSCAN0GAFLID0;
  uint32 rRSCAN0GAFLM;
  uint32 rRSCAN0GAFLP0;
  uint32 rRSCAN0GAFLP1;

}register_content;

typedef struct{
  uint32 rCKSC_CPUCLKS_CTL    ;
  uint32 rCKSC_CPUCLKS_ACT    ;
  uint32 rCKSC_CPUCLKD_CTL    ;
  uint32 rCKSC_CPUCLKD_ACT    ;
  uint32 rCKSC_ICANS_CTL      ;
  uint32 rCKSC_ICANS_ACT      ;
  uint32 rCKSC_ICANS_STPM     ;
  uint32 rCKSC_ICANOSCD_CTL   ;
  uint32 rCKSC_ICANOSCD_ACT   ;
  uint32 rCKSC_ICANOSCD_STPM  ;

}clockreg_content;

volatile register_content regs;
volatile clockreg_content creg;
#define point_to(x) *((uint32*)(x))
#define rCLOCK_BASE_ADDRESS 0xFFF81000

void ApplFblTask( void ){
   static V_MEMRAM1 vuint16 V_MEMRAM2 flashlight;

   regs.rRSCAN0RMNB =      point_to(kCanBaseAdr + 0xa4);
   regs.rRSCAN0GCTR =      point_to(kCanBaseAdr + 0x88);
   regs.rRSCAN0TMIEC0 =    point_to(kCanBaseAdr + 0x390);
   regs.rRSCAN0GSTS =      point_to(kCanBaseAdr + 0x8c);
   regs.rRSCAN0C0STS =     point_to(kCanBaseAdr + 0x8);
   regs.rRSCAN0GCFG =      point_to(kCanBaseAdr + 0x84);
   regs.rRSCAN0C0CFG =     point_to(kCanBaseAdr + 0x0);
   regs.rRSCAN0C0CTR =     point_to(kCanBaseAdr + 0x4);
   regs.rRSCAN0RFCC0 =     point_to(kCanBaseAdr + 0xb8);
   regs.rRSCAN0RFSTS0 =    point_to(kCanBaseAdr + 0xd8);
   regs.rRSCAN0GAFLCFG0 =  point_to(kCanBaseAdr + 0x9c);
   regs.rRSCAN0GAFLID0 =   point_to(kCanBaseAdr + 0x500);
   regs.rRSCAN0GAFLM =     point_to(kCanBaseAdr + 0x504);
   regs.rRSCAN0GAFLP0 =    point_to(kCanBaseAdr + 0x508);
   regs.rRSCAN0GAFLP1 =    point_to(kCanBaseAdr + 0x50c);

   creg.rCKSC_CPUCLKS_CTL   = point_to(rCLOCK_BASE_ADDRESS + 0x9000);
   creg.rCKSC_CPUCLKS_ACT   = point_to(rCLOCK_BASE_ADDRESS + 0x9008);
   creg.rCKSC_CPUCLKD_CTL   = point_to(rCLOCK_BASE_ADDRESS + 0x9100);
   creg.rCKSC_CPUCLKD_ACT   = point_to(rCLOCK_BASE_ADDRESS + 0x9108);
   creg.rCKSC_ICANS_CTL     = point_to(rCLOCK_BASE_ADDRESS + 0x9900);
   creg.rCKSC_ICANS_ACT     = point_to(rCLOCK_BASE_ADDRESS + 0x9908);
   creg.rCKSC_ICANS_STPM    = point_to(rCLOCK_BASE_ADDRESS + 0x9918);
   creg.rCKSC_ICANOSCD_CTL  = point_to(rCLOCK_BASE_ADDRESS + 0x9A00);
   creg.rCKSC_ICANOSCD_ACT  = point_to(rCLOCK_BASE_ADDRESS + 0x9A08);
   creg.rCKSC_ICANOSCD_STPM = point_to(rCLOCK_BASE_ADDRESS + 0x9A18);

   flashlight++;
   if(flashlight >= 500u){
      flashlight = 0u;

      #ifdef DEBUG_PORTS_ACTIVE
      TP3(GPIO_input_read(GPIO_TP3) ^ 0x01);
      TP0(0);
      #endif

#if defined( FBL_ENABLE_VECTOR_HW )

#  if defined ( BRS_ENABLE_SUPPORT_LEDS )
      BrsHwTogglePin(BRSHW_TOGGLEPIN_LED);
#  endif
#endif
   }
}
#endif

#if defined( FBL_ENABLE_APPL_TASK ) ||\
    defined( FBL_ENABLE_APPL_STATE_TASK )

void ApplFblStateTask( void ){
}
#endif

#if defined( FBL_ENABLE_ASSERTION )

void ApplFblFatalError( FBL_DECL_ASSERT_EXTENDED_INFO(vuint8 errorCode) ){
#if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   (void)errorCode;
#endif
}
#endif

#if(DET_ENABLED == STD_ON)
# define FBLAP_RAMCODE_START_SEC_CODE
# include "MemMap.hpp"

# if((DET_AR_RELEASE_MAJOR_VERSION >= 4u) && (DET_AR_RELEASE_MINOR_VERSION >= 3u))
FUNC(Std_ReturnType, DET_CODE) ApplFbl_DetEntryHandler( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId )
# else
FUNC(boolean, DET_APPL_CODE) ApplFbl_DetEntryHandler( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId )
# endif
{
   Std_ReturnType result = E_OK;

   switch(ModuleId){
      case CANTP_MODULE_ID:
      {
         switch(ErrorId)
         {
            case CANTP_E_INVALID_RX_BUFFER:
            case CANTP_E_INVALID_RX_LENGTH:
            case CANTP_E_INVALID_TATYPE:
            case CANTP_E_INVALID_FRAME_TYPE:
            case CANTP_E_RX_TIMEOUT_AR:
            case CANTP_E_RX_TIMEOUT_BR:
            case CANTP_E_RX_TIMEOUT_CR:
            case CANTP_E_RX_INVALID_SN:
            case CANTP_E_RX_WFTMAX:
            case CANTP_E_RX_RESTART:
            case CANTP_E_NO_ERROR:
            {
               result = E_NOT_OK;
               break;
            }
            default:
            {
               break;
            }
         }
         break;
      }
      case CAN_MODULE_ID:
      {
         switch(ErrorId)
         {
            case CAN_E_DATALOST:
            {
               result = E_NOT_OK;
               break;
            }
            default:
            {
               break;
            }
         }
         break;
      }
      default:
      {
         break;
      }
   }

   return result;
}
# define FBLAP_RAMCODE_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

#if defined( FBL_ENABLE_MULTIPLE_NODES ) || \
    defined( FBL_ENABLE_CAN_CONFIGURATION) || \
    defined( FBL_CW_ENABLE_MULTIPLE_NODES )

void ApplFblCanParamInit( void ){
   vuint8 currentEcu = 1;

   if(FblMainGetStartFromAppl()){
   }
   switch(currentEcu){
      case 0:
      {
         fblEcuHandle = FBL_ECU_HDLE_Demo_0_CAN11;
         break;
      }
      case 1:
      {
         fblEcuHandle = FBL_ECU_HDLE_Demo_1_CAN29;
         break;
      }
   }
}
#endif

void ApplFblCanBusOff( void ){
   ApplFblReset();
}

#if defined( FBL_ENABLE_SLEEPMODE )

void ApplFblBusSleep( void ){
   CanInit(0);

#if defined( FBL_WATCHDOG_ON )

   while (FblLookForWatchdog() != FBL_WD_TRIGGERED){
      ;
   }
#endif

   if(CanSleep() == kCanOk){
      ApplTrcvrSleepMode();

      while (CanHwIsSleep(CanGetStatus()) != 0)
      {
         ;
      }
   }

   ApplFblReset();
}
#endif

void ApplFblStartApplication( void ){
   JSR_APPL();

#if defined( FBL_ENABLE_SYSTEM_CHECK )

   while (1){
      ;
   }
#endif
}

static void InitCanPorts(void){
  FBL_P0   &=   FblInvert16Bit(1 << 1);
  FBL_PM0  &=   FblInvert16Bit(1 << 1);
  FBL_PMC0 &=   FblInvert16Bit(1 << 1);

  FBL_P10   &=   FblInvert16Bit(1 << 3);
  FBL_PM10  &=   FblInvert16Bit(1 << 3);
  FBL_PMC10 &=   FblInvert16Bit(1 << 3);

  FBL_PFCAE10    &=  FblInvert16Bit(1 << 0);
  FBL_PFCE10     &=  FblInvert16Bit(1 << 0);
  FBL_PFC10      |=   (1 << 0);
  FBL_PM10       |=   (1 << 0);
  FBL_PMC10      |=   (1 << 0);

  FBL_PFCAE10    &=  FblInvert16Bit(1 << 1);
  FBL_PFCE10     &=  FblInvert16Bit(1 << 1);
  FBL_PFC10      |=   (1 << 1);
  FBL_P10        |=   (1 << 1);
  FBL_PM10       &=  FblInvert16Bit(1 << 1);
  FBL_PMC10      |=   (1 << 1);

}

static void InitClocks(void){
  FBL_MOSCC = MOSCC_AMPSEL;
  FBL_MOSCST = MOSCST_STABILISATION;
  FBL_PROT_WRITE0(FBL_MOSCE, MOSCE_ENTRG);
  while(FBL_MOSCS != MOSCS_CLKACT );

  FBL_PLLC = PLLC_INIT_VAL;
  FBL_PROT_WRITE1(FBL_PLLE, PLLE_ENTRG);
  while(FBL_PLLS != PLLS_CLKACT);

  FBL_PROT_WRITE1(FBL_CKSC_CPUCLKD_CTL, CKSC_CLOCK_DIVIDER);
  while(FBL_CKSC_CPUCLKD_ACT != CKSC_CLOCK_DIVIDER);

  FBL_PROT_WRITE1(FBL_CKSC_CPUCLKS_CTL, CKSC_CLOCK_SOURCE);
  while(FBL_CKSC_CPUCLKS_ACT != CKSC_CLOCK_SOURCE);

}

