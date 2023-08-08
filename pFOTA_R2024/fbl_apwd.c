#include "fbl_inc.hpp"

#include "BrsHw.hpp"
# include "SwcServiceDet.hpp"
# if(DET_ENABLED == STD_ON)
#   include "McalCan.hpp"
#   include "SwcServiceCanTp.hpp"
# endif

#if( FBLKBAPI_FRAMEWD_VERSION != 0x0310u ) || \
    ( FBLKBAPI_FRAMEWD_RELEASE_VERSION != 0x01u )
# error "Error in FBL_APWD.C: Source and header file are inconsistent!"
#endif

#if( FBLKBAPI_FRAMEWD_VERSION != _FBLKBAPI_FRAMEWD_VERSION ) || \
    ( FBLKBAPI_FRAMEWD_RELEASE_VERSION != _FBLKBAPI_FRAMEWD_RELEASE_VERSION )
# error "Error in FBL_APWD.C: Source and V_VER.H are inconsistent!"
#endif

#define kSeedAlreadyRequested             0x00u
#define kNewSeedRequest                   0x01u

# if defined( SEC_BYTE_ARRAY_SEED )
#  define FBL_APPL_ENABLE_SEC_BYTE_ARRAY_SEED
# endif
# if defined( SEC_WORD_ARRAY_SEED )
#  define FBL_APPL_ENABLE_SEC_WORD_ARRAY_SEED
# endif
# if defined( SEC_BYTE_ARRAY_KEY )
#  define FBL_APPL_ENABLE_SEC_BYTE_ARRAY_KEY
# endif

void ApplFblWDInit( void ){
#if defined( FBL_WATCHDOG_ON )
   WDTimer = (tWdTime)FBL_WATCHDOG_TIME;
#endif
   FBL_WDTA0MD = (vuint8) 0x47;
   FBL_WDTA0WDTE = (vuint8) 0xAC;
}

void ApplFblWDLong( void ){
}

void ApplFblWDShort( void ){
}

# define WDTRIGGER_START_SEC_CODE
# include "MemMap.hpp"

void V_CALLBACK_NEAR ApplFblWDTrigger( void ){
  FBL_WDTA0WDTE = (vuint8) 0xAC;
}
# define WDTRIGGER_STOP_SEC_CODE
# include "MemMap.hpp"

