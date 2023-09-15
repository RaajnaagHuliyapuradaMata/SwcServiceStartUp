

#ifndef FBL_MAIN_TYPES_H
#define FBL_MAIN_TYPES_H

#include "bm_types.hpp"

#define FblHeaderTable  ((V_MEMROM1_FAR tFblHeader V_MEMROM2_FAR V_MEMROM3 *)(FBL_HEADER_ADDRESS))
#define FblHeaderLocal  ((V_MEMROM1_FAR tFblHeader V_MEMROM2_FAR V_MEMROM3 *)(&FblHeader))

#if defined( FBL_ENABLE_COMMON_DATA )
#define GetFblCommonDataPtr()   (FblHeaderTable->pFblCommonData)
#endif

#define FBL_MAIN_HEADER_MAGIC_FLAG    0x58462918u

#if defined( FBL_ENABLE_COMMON_DATA )

typedef V_MEMROM1_FAR void V_MEMROM2_FAR V_MEMROM3 * tFblCommonDataPtr;
#endif

typedef V_MEMROM1_FAR tLogicalBlockTable V_MEMROM2_FAR V_MEMROM3 * tFblHeaderLogicalBlockTablePtr;

typedef V_MEMROM1_FAR tFblBmHdrHeader V_MEMROM2_FAR V_MEMROM3 * tFblHeaderBmHeaderPtr;

typedef struct{
   vuint32 magicFlag;
   tFblHeaderLogicalBlockTablePtr pLogicalBlockTable;
   tFblLength logicalBlockTableSize;
#if defined( FBL_ENABLE_COMMON_DATA )
   tFblCommonDataPtr pFblCommonData;
#endif
   tFblAddress fblStartAddress;
   tFblLength fblLength;
   tFblHeaderBmHeaderPtr bmHeader;
}tFblHeader;

#endif

