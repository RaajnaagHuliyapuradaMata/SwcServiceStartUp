

#ifndef FBLLIB_NVPATTERN_OEM_H
#define FBLLIB_NVPATTERN_OEM_H

#define FBL_NVPATTERN_DISABLE_MULTIPLE_VALIDATION

#define FBL_NVPATTERN_DISABLE_BLOCK_PROPERTIES

typedef enum{
    kFblNvPatternId_Invalid = 0u
   ,kFblNvPatternId_BlockValidity
   ,kFblNvPatternId_ApplValidity
#if defined( FBL_NVPATTERN_ENABLE_BLOCK_PROPERTIES )
   ,kFblNvPatternId_Separator
   ,kFblNvProperty_ModuleRev
   ,kFblNvProperty_PartitionRev
#endif
   ,kFblNvPatternId_Last
}tFblNvPatternId;

#if defined( FBL_NVPATTERN_ENABLE_BLOCK_PROPERTIES )
typedef struct{
   IO_SizeType length;
   tFblNvPatternId dependentPattern;
}tFblBlockProperty;
#endif

#if defined ( FBL_NVPATTERN_ENABLE_MULTIPLE_VALIDATION )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 fblNvPatternMultiplicity[];
#endif

#if defined( FBL_NVPATTERN_ENABLE_BLOCK_PROPERTIES )
V_MEMROM0 extern V_MEMROM1 tFblBlockProperty V_MEMROM2 fblNvBlockProperties[];
#endif

#endif

