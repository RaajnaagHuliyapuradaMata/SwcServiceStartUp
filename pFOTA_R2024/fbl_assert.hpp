

#ifndef __FBL_ASSERT_H__
#define __FBL_ASSERT_H__

#if defined( FBL_ENABLE_ASSERTION )

#define kFblSysAssertMissingForcedRCRRP               0x00u

#define kFblSysAssertInitializationFailed             0x10u

#define kFblSysAssertServiceReqBeforeResp             0x20u
#define kFblSysAssertServiceMainHandlerInvalid        0x21u
#define kFblSysAssertDet                              0x22u

#define kFblSysAssertWdBufferOverflow                 0x40u

#define kFblSysAssertParameterOutOfRange              0x50u

#define kFblSysAssertRepeatedCallOnConcludedService   0x60u

#define kFblSysAssertStateNotIdle                     0x70u
#define kFblSysAssertNoBufferAvailable                0x71u

#include "fbl_assert_oem.hpp"

# if defined( __LINE__ ) && defined( __FILE__ ) && defined( FBL_ENABLE_ASSERTION_EXTENDED_INFO )
#  define FBL_DECL_ASSERT_EXTENDED_INFO(n)       const vuint8* module, vuint16 line, n
#  define FBL_USED_ASSERT_EXTENDED_INFO(n)       __FILE__, __LINE__,(n)
# else
#  define FBL_DECL_ASSERT_EXTENDED_INFO(n)        n
#  define FBL_USED_ASSERT_EXTENDED_INFO(n)       (n)
# endif

# define assertFbl(p, e)         if(!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e))
# define assertFblUser(p, e)     if(!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e))
# define assertFblGen(p, e)      if(!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e))
# define assertFblInternal(p, e) if(!(p)) ApplFblFatalError(FBL_USED_ASSERT_EXTENDED_INFO(e))
#else
# define assertFbl(p, e)
# define assertFblUser(p, e)
# define assertFblGen(p, e)
# define assertFblInternal(p, e)
#endif

#endif

