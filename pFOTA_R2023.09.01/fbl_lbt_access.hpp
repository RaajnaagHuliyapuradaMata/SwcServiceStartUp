

#ifndef FBL_LBT_ACCESS_H
#define FBL_LBT_ACCESS_H

#define FBLLIB_LBT_VERSION           0x0102u
#define FBLLIB_LBT_RELEASE_VERSION   0x00u

#include "Platform_Types.hpp"

typedef struct{
   tFblLbtMandatoryType    value;
   boolean                 enabled;
}tFblLbtMandatoryFilter;

#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )

typedef struct{
   tFblLbtBlockType        value;
   boolean                 enabled;
}tFblLbtTypeFilter;
#endif

typedef struct{
   tFblLbtMandatoryFilter  mandatoryType;
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )
   tFblLbtTypeFilter       blockType;
#endif
}tFblLbtBlockFilter;

void FblLbtInitPowerOn(void);

void FblLbtBlockFilterInit(V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter);
void FblLbtBlockFilterSetMandatoryType(V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter, tFblLbtMandatoryType mandatoryType);
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )
void FblLbtBlockFilterSetBlockType(V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter, tFblLbtBlockType blockType);
#endif

tFblLbtBlockCount FblLbtGetBlockCount(void);
tFblLbtMagicFlag FblLbtGetMagicFlag(void);
tFblResult FblLbtGetBlockNrByAddressLength(tFblAddress address, tFblLength length, V_MEMRAM1 tFblLbtBlockNr V_MEMRAM2 V_MEMRAM3 * blockNr);

tFblResult FblLbtGetBlockDescriptorByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor);
tFblResult FblLbtGetBlockDescriptorByAddressLength(tFblAddress address, tFblLength length, V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor);
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )
tFblResult FblLbtGetBlockDescriptorByType(tFblLbtBlockType blockType, V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor);
#endif
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )
tFblResult FblLbtGetBlockTypeByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tFblLbtBlockType V_MEMRAM2 V_MEMRAM3 * blockType);
#endif
#if defined( FBL_LBT_ENABLE_BLOCK_INDEX )
tFblResult FblLbtGetBlockIndexByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tFblLbtBlockIndex V_MEMRAM2 V_MEMRAM3 * blockIndex);
#endif
#if defined( FBL_LBT_ENABLE_HEADER_ADDRESS )
tFblResult FblLbtGetBlockHeaderAddressByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * blockHeaderAddress);
#endif
#if defined( FBL_LBT_ENABLE_BM_HEADER_ADDRESS )
tFblResult FblLbtGetBlockBmHeaderAddressByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * bmHeaderAddress);
#endif
#if defined( FBL_LBT_ENABLE_MAX_PROG_ATTEMPTS )
tFblResult FblLbtGetBlockMaxProgAttemptsByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tFblLbtMaxProgAttempts V_MEMRAM2 V_MEMRAM3 * maxProgAttempts);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_INPUT )
tFblResult FblLbtGetBlockVerifyInputFuncByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PROCESSED )
tFblResult FblLbtGetBlockVerifyProcessedFuncByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PIPELINED )
tFblResult FblLbtGetBlockVerifyPipelinedFuncByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_OUTPUT )
tFblResult FblLbtGetBlockVerifyOutputFuncByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif

#if defined( FBL_LBT_ENABLE_BLOCK_INDEX )
tFblResult FblLbtGetBlockDescriptorByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor);
tFblResult FblLbtGetBlockNrByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tFblLbtBlockNr V_MEMRAM2 V_MEMRAM3 * blockNr);
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )
tFblResult FblLbtGetBlockTypeByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tFblLbtBlockType V_MEMRAM2 V_MEMRAM3 * blockType);
#endif
#if defined( FBL_LBT_ENABLE_HEADER_ADDRESS )
tFblResult FblLbtGetBlockHeaderAddressByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * blockHeaderAddress);
#endif
#if defined( FBL_LBT_ENABLE_BM_HEADER_ADDRESS )
tFblResult FblLbtGetBlockBmHeaderAddressByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * bmHeaderAddress);
#endif
#if defined( FBL_LBT_ENABLE_MAX_PROG_ATTEMPTS )
tFblResult FblLbtGetBlockMaxProgAttemptsByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tFblLbtMaxProgAttempts V_MEMRAM2 V_MEMRAM3 * maxProgAttempts);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_INPUT )
tFblResult FblLbtGetBlockVerifyInputFuncByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PROCESSED )
tFblResult FblLbtGetBlockVerifyProcessedFuncByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PIPELINED )
tFblResult FblLbtGetBlockVerifyPipelinedFuncByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_OUTPUT )

tFblResult FblLbtGetBlockVerifyOutputFuncByIndex(tFblLbtBlockIndex blockIndex, V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc);
#endif
#endif

tBlockDescriptor FblLbtBlockFirst(const V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter);
tBlockDescriptor FblLbtBlockNext(void);
boolean FblLbtBlockDone(void);

tFblResult FblLbtCheckAddressRange(tFblAddress address, tFblAddress rangeStart, tFblLength rangeLength);
tFblResult FblLbtCheckRangeContained(tFblAddress address, tFblLength length, tFblAddress rangeStart, tFblLength rangeLength);

#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )
tFblResult FblLbtCheckConsistency(void);
void FblLbtActivateLbtBlock(void);
#endif
void FblLbtActivateLbtBlockByAddress(tFblAddress address);

#endif

