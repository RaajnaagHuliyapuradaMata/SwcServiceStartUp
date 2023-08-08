

#ifndef BM_HDR_H
#define BM_HDR_H

#define FBLBM_HDR_VERSION           0x0102u
#define FBLBM_HDR_RELEASE_VERSION   0x00u

#include "FblBmHdr_Cfg.hpp"

tFblResult FblBmHdrCheckConsistency( const V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 V_MEMRAM3 * pBmHeader );
tFblBmHdrCheckBmHeaderResult FblBmHdrFindValidHeader(tFblBmHdrTargetHandle targetHandle,
   V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo);
tFblBmHdrCheckBmHeaderResult FblBmHdrGetBmHeader(tFblBmHdrTargetHandle targetHandle, tFblAddress bmHeaderAddress,
   V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 V_MEMRAM3 * bmHeader);
#if defined( FBLBM_ENABLE_SECURE_BOOT )
tFblBmHdrCheckBmHeaderResult FblBmHdrVerifyBmHeader(tFblBmHdrTargetHandle targetHandle,
   const V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo);
tFblResult FblBmHdrVerifyAreas(tFblBmHdrTargetHandle targetHandle,
   const V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo);
#endif

#endif

