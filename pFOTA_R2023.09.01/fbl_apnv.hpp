#ifndef __FBL_APNV_H__
#define __FBL_APNV_H__
#ifdef __cplusplus
extern "C"
{
#endif

#define FBLKBAPI_FRAMENV_UDS1_VERSION             0x0601u
#define FBLKBAPI_FRAMENV_UDS1_RELEASE_VERSION     0x00u
#define kEepValidateBlock                 0x01u
#define kEepInvalidateBlock               0x02u
#define kEepApplConsistent                0xD1u
#define kEepApplInconsistent              0xFFu
#define kEepSecAccessDelayActive          0xA7u
#define kEepSecAccessDelayInactive        0xFFu

#define ApplFblReadPromSwVersion(descriptor, buffer) \
   FblReadProm((descriptor).blockStartAddress, (buffer), kApplInfoSizeSwVersion)
#define ApplFblReadPromSwPartNumber(descriptor, buffer) \
   FblReadProm((descriptor).blockStartAddress+kApplInfoOffsetSwPartNumber, (buffer), kApplInfoSizeSwPartNumber)
#define ApplFblReadPromSwSupplierInformation(descriptor, buffer) \
   FblReadProm((descriptor).blockStartAddress+kApplInfoOffsetSwSupplierInformation, (buffer), kApplInfoSizeSwSupplierInformation)

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )

#define ApplFblGetSecAccessDelayFlag() \
   (ApplFblRWSecurityAccessDelayFlag(kEepReadData, 0u) != kEepSecAccessDelayInactive)
#define ApplFblSetSecAccessDelayFlag() \
   ApplFblRWSecurityAccessDelayFlag(kEepWriteData, kEepSecAccessDelayActive)
#define ApplFblClrSecAccessDelayFlag() \
   ApplFblRWSecurityAccessDelayFlag(kEepWriteData, kEepSecAccessDelayInactive)
#endif

#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )

#define ApplFblReadResetResponseFlag(buffer)      ApplFblNvReadResetResponseFlag(buffer)
#define ApplFblWriteResetResponseFlag(buffer)     ApplFblNvWriteResetResponseFlag(buffer)
#endif

tFblProgStatus ApplFblExtProgRequest(void);
tApplStatus ApplFblIsValidApp(void);
tFblResult ApplFblValidateBlock( tBlockDescriptor blockDescriptor );
tFblResult ApplFblInvalidateBlock( tBlockDescriptor blockDescriptor );
tFblResult ApplFblStoreFingerprint( vuint8 * buffer );
tFblResult ApplFblIncProgCounts( tBlockDescriptor blockDescriptor );
tFblResult ApplFblGetProgCounts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progCounts);
tFblResult ApplFblIncProgAttempts( tBlockDescriptor blockDescriptor );
tFblResult ApplFblGetProgAttempts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progAttempts );
tFblLbtMaxProgAttempts ApplFblGetPromMaxProgAttempts(tFblLbtBlockNr blockNr);
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
tFblResult ApplFblWriteSecAccessInvalidCount( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * invalidCount );
tFblResult ApplFblReadSecAccessInvalidCount( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * invalidCount );
#endif
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
vuint8 ApplFblRWSecurityAccessDelayFlag( vuint8 mode, vuint8 value );
#endif
void ApplFblErrorNotification( tFblErrorType errorType, tFblErrorCode errorCode );
tFblResult ApplFblAdjustLbtBlockData(tBlockDescriptor * blockDescriptor);
#if defined( SEC_DISABLE_CRC_TOTAL )
#else
tFblResult ApplFblWriteCRCTotal( V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, vuint32 crcStart, vuint32 crcLength, vuint32 crcValue );
#endif

#if defined( FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK )
#else
tFblResult ApplFblValidateApp(void);
tFblResult ApplFblInvalidateApp(void);
#endif

#if defined( FBL_CW_ENABLE_MULTIPLE_CONNECTIONS )
tFblResult ApplFblWriteDcmDslRxTesterSourceAddr(vuint8* buffer);
tFblResult ApplFblReadDcmDslRxTesterSourceAddr(vuint8* buffer);
#endif

#if defined( FBL_MEM_ENABLE_STREAM_OUTPUT )
tFblResult ApplFblErasePatternArea(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * logicalBlockDescriptor);
#endif

extern tFblResult ApplFblNvInit(void);

#ifdef __cplusplus
}
#endif
#endif


