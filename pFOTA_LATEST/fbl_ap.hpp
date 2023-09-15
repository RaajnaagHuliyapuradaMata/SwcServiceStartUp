

#ifndef __FBL_AP_H__
#define __FBL_AP_H__

#define FBLKBAPI_VERSION                           0x0201u
#define FBLKBAPI_RELEASE_VERSION                   0x00u

#define FBLKBAPI_BRS_VERSION          0x0100u
#define FBLKBAPI_BRS_RELEASE_VERSION  0x02u

#define FBLKBAPI_UDS1_VERSION                    0x0602u
#define FBLKBAPI_UDS1_RELEASE_VERSION            0x00u

#define FBLKBAPI_FRAME_UDS1_VERSION               0x0502u
#define FBLKBAPI_FRAME_UDS1_RELEASE_VERSION       0x00u

#define FBL_MAX_DID_COUNT   8u

#if defined( FBL_ENABLE_DATA_PROCESSING )
#if !defined( GetOemProcessingModeSupported )

#define GetOemProcessingModeSupported(m) (GetOemCompressionMode((m)) || GetOemEncryptionMode((m)))
#endif

#if !defined( GetOemCompressionMode )
#if defined( FBL_ENABLE_COMPRESSION_MODE )

#define GetOemCompressionMode(m) ((FblDiagGetCompressionMode(m) & kDiagSubDefaultCompression) == kDiagSubDefaultCompression)
#   else

#define GetOemCompressionMode(m) (0 != 0)
#endif
#endif

#if !defined( GetOemEncryptionMode )
#if defined( FBL_ENABLE_ENCRYPTION_MODE )

#define GetOemEncryptionMode(m) ((FblDiagGetEncryptionMode(m) & kDiagSubDefaultEncryption) == kDiagSubDefaultEncryption)
#   else

#define GetOemEncryptionMode(m) (0 != 0)
#endif
#endif
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT)
#if !defined( GetOemStreamModeSupported )
#define GetOemStreamModeSupported(m) ((FblDiagGetCompressionMode(m) & kDiagSubDefaultDelta) == kDiagSubDefaultDelta)
#endif
#endif

#if defined( FBL_ENABLE_MULTIPLE_NODES ) || \
    defined( FBL_CW_ENABLE_MULTIPLE_NODES )
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 fblEcuHandle;
#endif

void ApplFblInit(void);
void ApplFblStartup( vuint8 initposition );
tFblResult ApplFblCheckProgConditions(void);
tFblResult ApplFblCheckConditions( vuint8 * pbDiagData, tTpDataType diagReqDataLen );
vuint8 ApplFblCheckProgDependencies(void);
void ApplTrcvrNormalMode(void);
void ApplTrcvrSleepMode(void);
void ApplFblSetVfp(void);
void ApplFblResetVfp(void);
void ApplFblReset(void);
#define FBLAP_RAMCODE_START_SEC_CODE_EXPORT
#include "MemMap.hpp"
vuint8 ApplFblSecuritySeedInit(void);
#define FBLAP_RAMCODE_STOP_SEC_CODE_EXPORT
#include "MemMap.hpp"
vuint8 ApplFblSecuritySeed(void);
vuint8 ApplFblSecurityKey(void);
vuint8 ApplFblSecurityInit(void);
#if defined( FBL_ENABLE_DATA_PROCESSING )
tFblResult ApplFblInitDataProcessing( tProcParam * procParam );
tFblResult ApplFblDataProcessing( tProcParam * procParam );
tFblResult ApplFblDeinitDataProcessing( tProcParam * procParam );
#endif
#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
tFblResult ApplFblInitStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam );
tFblResult ApplFblStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam );
tFblResult ApplFblFinalizeStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam );
tFblResult ApplFblDeinitStreamOutput( V_MEMRAM1 tFblMemStreamProcessing V_MEMRAM2 V_MEMRAM3 * streamParam );
#endif
#if defined( FBL_ENABLE_APPL_TASK ) || \
    defined( FBL_ENABLE_APPL_TIMER_TASK )
void ApplFblTask(void);
#endif
#if defined( FBL_ENABLE_APPL_TASK ) ||\
    defined( FBL_ENABLE_APPL_STATE_TASK )
void ApplFblStateTask(void);
#endif

#if defined( FBL_ENABLE_ASSERTION )
void ApplFblFatalError( FBL_DECL_ASSERT_EXTENDED_INFO(vuint8 errorCode) );
#endif

void ApplFblCanBusOff(void);

#if defined( FBL_ENABLE_MULTIPLE_NODES ) || \
    defined( FBL_ENABLE_CAN_CONFIGURATION) || \
    defined( FBL_CW_ENABLE_MULTIPLE_NODES )
void ApplFblCanParamInit(void);
#endif

#if defined( FBL_ENABLE_SLEEPMODE )
void ApplFblBusSleep(void);
#endif

void ApplFblStartApplication(void);

#endif

