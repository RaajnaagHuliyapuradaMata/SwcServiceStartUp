

#ifndef __FBL_APDI_H__
#define __FBL_APDI_H__

#define FBLKBAPI_FRAMEDIAG_UDS1_VERSION           0x0403u
#define FBLKBAPI_FRAMEDIAG_UDS1_RELEASE_VERSION   0x00u

#if defined( FBL_ENABLE_USERSERVICE )
void ApplDiagUserService( vuint8 * pbDiagData, tTpDataType diagReqDataLen );
#endif
#if defined( FBL_ENABLE_USERSUBFUNCTION )
void ApplDiagUserSubFunction( vuint8 * pbDiagData, tTpDataType diagReqDataLen );
#endif
#if defined( FBL_ENABLE_USERROUTINE )
void ApplDiagUserRoutine( vuint8 * pbDiagData, tTpDataType diagReqDataLen );
#endif
void ApplFblReadDataByIdentifier( vuint8 * pbDiagData, tTpDataType diagReqDataLen );
vuint8 ApplFblWriteDataByIdentifier( vuint8 * pbDiagData, tTpDataType diagReqDataLen );
#if defined( FBL_ENABLE_DEBUG_STATUS )
void ApplFblInitErrStatus( void );
#endif

#endif

