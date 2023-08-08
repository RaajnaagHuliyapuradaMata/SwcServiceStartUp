

#ifndef __FBL_APWD_H__
#define __FBL_APWD_H__

#define FBLKBAPI_FRAMEWD_VERSION                0x0310u
#define FBLKBAPI_FRAMEWD_RELEASE_VERSION        0x01u

void ApplFblWDInit( void );
void ApplFblWDLong( void );
void ApplFblWDShort( void );
# define WDTRIGGER_START_SEC_CODE_EXPORT
# include "MemMap.hpp"
void V_CALLBACK_NEAR ApplFblWDTrigger( void );
# define WDTRIGGER_STOP_SEC_CODE_EXPORT
# include "MemMap.hpp"

#endif

