

#ifndef BM_HDR_AP_H
#define BM_HDR_AP_H

#include "fbl_def.hpp"
#include "bm_types.hpp"
#include "bm_hdr.hpp"

#if defined( FBLBM_ENABLE_SECURE_BOOT )
# if defined( FBLBMHDR_ENABLE_CUSTOM_VERIFY_AREAS )
tFblResult ApplFblBmHdrCustomVerifyAreasEnable(tFblBmHdrTargetHandle targetHandle);
tFblResult ApplFblBmHdrCustomVerifyAreas(tFblBmHdrTargetHandle targetHandle, const V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo);
# endif
#endif

#endif

