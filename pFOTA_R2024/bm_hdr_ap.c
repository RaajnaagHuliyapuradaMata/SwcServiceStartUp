

#define BM_HDR_AP_C

#include "fbl_def.hpp"
#include "bm_main.hpp"
#include "bm_hdr_ap.hpp"

#if defined( FBLBM_ENABLE_SECURE_BOOT )
# include "SwcServiceCsm.hpp"
#endif

#define FBLBMHDRAP_START_SEC_CODE
#include "MemMap.hpp"

#if defined( FBLBM_ENABLE_SECURE_BOOT )
# if defined( FBLBMHDR_ENABLE_CUSTOM_VERIFY_AREAS )

tFblResult ApplFblBmHdrCustomVerifyAreasEnable(tFblBmHdrTargetHandle targetHandle){
   tFblResult result;

#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)targetHandle;
#  endif

   result = kFblFailed;

   return result;
}

tFblResult ApplFblBmHdrCustomVerifyAreas(tFblBmHdrTargetHandle targetHandle,
   const V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo){
   tFblResult result;

#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )

   (void)targetHandle;
   (void)pBlockInfo;
#  endif

   result = kFblFailed;

   return result;
}
# endif
#endif

#define FBLBMHDRAP_STOP_SEC_CODE
#include "MemMap.hpp"

