#ifndef BM_HDR_TYPES_H
#define BM_HDR_TYPES_H

#include "FblBmHdr_Cfg.hpp"

typedef enum{
   FBLBMHDR_CHKHDR_OK
   ,  FBLBMHDR_CHKHDR_BLOCK_INVALID
   ,  FBLBMHDR_CHKHDR_READ_FAIL
   ,  FBLBMHDR_CHKHDR_HEADER_INCONSISTENT
   ,  FBLBMHDR_CHKHDR_WRONG_TARGET
   ,  FBLBMHDR_CHKHDR_GET_MAC_FAIL
   ,  FBLBMHDR_CHKHDR_VERIFICATION_FAIL
   ,  FBLBMHDR_CHKHDR_NOT_FOUND
}tFblBmHdrCheckBmHeaderResult;

#endif

