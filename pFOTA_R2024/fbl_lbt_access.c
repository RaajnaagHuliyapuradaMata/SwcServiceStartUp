

#include "fbl_inc.hpp"

#if( FBLLIB_LBT_VERSION != 0x0102u ) || \
    ( FBLLIB_LBT_RELEASE_VERSION != 0x00u )
# error "Error in fbl_lbt_access.c: Source and header file are inconsistent!"
#endif

#if( FBLLIB_LBT_VERSION != _FBLLIB_LBT_VERSION ) || \
    ( FBLLIB_LBT_RELEASE_VERSION != _FBLLIB_LBT_RELEASE_VERSION )
# error "Error in fbl_lbt_access.c: Source and v_ver.h are inconsistent!"
#endif

V_MEMRAM0 static V_MEMRAM1 tFblLbtBlockNr V_MEMRAM2 fblLbtBlockIteratorNr;
V_MEMRAM0 static V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 fblLbtBlockIteratorFilter;
V_MEMRAM0 static V_MEMRAM1 boolean V_MEMRAM2 fblLbtBlockIteratorDone;
V_MEMRAM0 static V_MEMRAM1 tLogicalBlockTable V_MEMROM2 V_MEMROM3 * V_MEMRAM1 V_MEMRAM2 fblLbtActive;

static boolean FblLbtBlockFilterHit(const V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter,
                                    const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor);
#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )
static tFblResult FblLbtBlockCompare(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * block1,
                                     const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * block2);
static tFblResult FblLbtCheckReferences(void);
#endif

static boolean FblLbtBlockFilterHit(const V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter,
                                    const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor){
   boolean result;

   result = TRUE;

   if(blockFilter->mandatoryType.enabled == TRUE){
      if(blockDescriptor->mandatoryType == TRUE)
      {
         result = (blockFilter->mandatoryType.value == TRUE) ? TRUE : FALSE;
      }
      else
      {
         result = (blockFilter->mandatoryType.value == FALSE) ? TRUE : FALSE;
      }
   }

#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )

   if(blockFilter->blockType.enabled == TRUE){
      if(result == TRUE)
      {
         result = (boolean)((blockDescriptor->blockType == blockFilter->blockType.value) ? TRUE : FALSE);
      }
   }
#endif

   return result;
}

#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )

static tFblResult FblLbtBlockCompare(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * block1,
                                     const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * block2){
   tFblResult result;

   result = kFblOk;

   if(   (block1->blockNr           != block2->blockNr)
       || (block1->mandatoryType     != block2->mandatoryType)
       || (block1->blockStartAddress != block2->blockStartAddress)
       || (block1->blockLength       != block2->blockLength)
#if defined( FBL_LBT_ENABLE_BLOCK_INDEX )
       || (block1->blockIndex        != block2->blockIndex)
#endif
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )
       || (block1->blockType         != block2->blockType)
#endif
#if defined( FBL_LBT_ENABLE_HEADER_ADDRESS )
       || (block1->headerAddress     != block2->headerAddress)
#endif
#if defined( FBL_LBT_ENABLE_BM_HEADER_ADDRESS )
       || (block1->bmHeaderAddress   != block2->bmHeaderAddress)
#endif
#if defined( FBL_LBT_ENABLE_MAX_PROG_ATTEMPTS )
       || (block1->maxProgAttempts   != block2->maxProgAttempts)
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_INPUT )
       || (block1->verifyInput       != block2->verifyInput)
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PROCESSED )
       || (block1->verifyProcessed   != block2->verifyProcessed)
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PIPELINED )
       || (block1->verifyPipelined   != block2->verifyPipelined)
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_OUTPUT )
       || (block1->verifyOutput      != block2->verifyOutput)
#endif
      ){
      result = kFblFailed;
   }

   return result;
}

static tFblResult FblLbtCheckReferences(void){
   tFblResult result;
   tFblLbtBlockFilter blockFilter;
   tBlockDescriptor newLbtBlock;
   vuint8 tableIdx;

   result = kFblOk;

   FblLbtBlockFilterInit(&blockFilter);
   for (newLbtBlock = FblLbtBlockFirst(&blockFilter);
        FblLbtBlockDone() == FALSE;
        newLbtBlock = FblLbtBlockNext()){
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )

      result = kFblFailed;
      for (tableIdx = 0u; tableIdx < fblLbtBlockTypes.typeCount; tableIdx++)
      {
         if(newLbtBlock.blockType == fblLbtBlockTypes.type[tableIdx])
         {
            result = kFblOk;
            break;
         }
      }
#endif

#if defined( FBL_LBT_ENABLE_VERIFY_INPUT )
      if(result == kFblOk)
      {
         result = kFblFailed;
         for (tableIdx = 0u; tableIdx < fblLbtVerificationFunc.funcCount; tableIdx++)
         {
            if(newLbtBlock.verifyInput == fblLbtVerificationFunc.func[tableIdx])
            {
               result = kFblOk;
               break;
            }
         }
      }
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PROCESSED )
      if(result == kFblOk)
      {
         result = kFblFailed;
         for (tableIdx = 0u; tableIdx < fblLbtVerificationFunc.funcCount; tableIdx++)
         {
            if(newLbtBlock.verifyProcessed == fblLbtVerificationFunc.func[tableIdx])
            {
               result = kFblOk;
               break;
            }
         }
      }
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_PIPELINED )
      if(result == kFblOk)
      {
         result = kFblFailed;
         for (tableIdx = 0u; tableIdx < fblLbtVerificationFunc.funcCount; tableIdx++)
         {
            if(newLbtBlock.verifyPipelined == fblLbtVerificationFunc.func[tableIdx])
            {
               result = kFblOk;
               break;
            }
         }
      }
#endif
#if defined( FBL_LBT_ENABLE_VERIFY_OUTPUT )
      if(result == kFblOk)
      {
         result = kFblFailed;
         for (tableIdx = 0u; tableIdx < fblLbtVerificationFunc.funcCount; tableIdx++)
         {
            if(newLbtBlock.verifyOutput == fblLbtVerificationFunc.func[tableIdx])
            {
               result = kFblOk;
               break;
            }
         }
      }
#endif

      if(result != kFblOk)
      {
         break;
      }
   }

   return result;
}
#endif

void FblLbtInitPowerOn(void){
   fblLbtActive = &FblLogicalBlockTable;
}

void FblLbtBlockFilterInit(V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter){
   blockFilter->mandatoryType.enabled = FALSE;
#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )
   blockFilter->blockType.enabled = FALSE;
#endif
}

void FblLbtBlockFilterSetMandatoryType(V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter,
                                       tFblLbtMandatoryType mandatoryType){
   blockFilter->mandatoryType.value = mandatoryType;
   blockFilter->mandatoryType.enabled = TRUE;
}

#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )

void FblLbtBlockFilterSetBlockType(V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter,
                                   tFblLbtBlockType blockType){
   blockFilter->blockType.value = blockType;
   blockFilter->blockType.enabled = TRUE;
}
#endif

tBlockDescriptor FblLbtBlockFirst(const V_MEMRAM1 tFblLbtBlockFilter V_MEMRAM2 V_MEMRAM3 * blockFilter){
   fblLbtBlockIteratorNr = 0u;
   fblLbtBlockIteratorFilter = *blockFilter;
   fblLbtBlockIteratorDone = FALSE;

   return FblLbtBlockNext();
}

tBlockDescriptor FblLbtBlockNext(void){
   tBlockDescriptor blockDescriptor;
   boolean filterResult;

   blockDescriptor = FblLogicalBlockTable.logicalBlock[0u];

   filterResult = FALSE;

   while (fblLbtBlockIteratorNr < fblLbtActive->noOfBlocks){
      blockDescriptor = fblLbtActive->logicalBlock[fblLbtBlockIteratorNr];

      fblLbtBlockIteratorNr++;

      filterResult = FblLbtBlockFilterHit(&fblLbtBlockIteratorFilter, &blockDescriptor);
      if(filterResult == TRUE)
      {
         break;
      }
   }

   if((fblLbtBlockIteratorNr >= fblLbtActive->noOfBlocks) && (filterResult == FALSE)){
      fblLbtBlockIteratorDone = TRUE;
   }

   return blockDescriptor;
}

boolean FblLbtBlockDone(void){
   return fblLbtBlockIteratorDone;
}

tFblLbtBlockCount FblLbtGetBlockCount(void){
   return (tFblLbtBlockCount)fblLbtActive->noOfBlocks;
}

tFblLbtMagicFlag FblLbtGetMagicFlag(void){
   return (tFblLbtMagicFlag)fblLbtActive->magicFlag;
}

tFblResult FblLbtGetBlockNrByAddressLength(tFblAddress address, tFblLength length,
                                           V_MEMRAM1 tFblLbtBlockNr V_MEMRAM2 V_MEMRAM3 * blockNr){
   tFblResult result;
   tBlockDescriptor localBlockDescriptor;
   tFblLbtBlockFilter blockFilter;

   result = kFblFailed;

   FblLbtBlockFilterInit(&blockFilter);

   for (localBlockDescriptor = FblLbtBlockFirst(&blockFilter);
        FblLbtBlockDone() == FALSE;
        localBlockDescriptor = FblLbtBlockNext()){
      result = FblLbtCheckRangeContained(address, length,
                                         localBlockDescriptor.blockStartAddress,
                                         localBlockDescriptor.blockLength);
      if(result == kFblOk)
      {
         *blockNr = localBlockDescriptor.blockNr;
         break;
      }
   }

   return result;
}

tFblResult FblLbtGetBlockDescriptorByNr(tFblLbtBlockNr blockNr,
                                        V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor){
   tFblResult result;

   result = kFblFailed;

   if(blockNr < fblLbtActive->noOfBlocks){
     *blockDescriptor = fblLbtActive->logicalBlock[blockNr];
     result = kFblOk;
   }

   return result;
}

tFblResult FblLbtGetBlockDescriptorByAddressLength(tFblAddress address, tFblLength length,
                                                   V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor){
   tFblResult result;
   tFblLbtBlockNr localBlockNr;

   result = FblLbtGetBlockNrByAddressLength(address, length, &localBlockNr);

   if(result == kFblOk){
      result = FblLbtGetBlockDescriptorByNr(localBlockNr, blockDescriptor);
   }

   return result;
}

#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )

tFblResult FblLbtGetBlockDescriptorByType(tFblLbtBlockType blockType,
                                          V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor){
   tFblResult result;
   tBlockDescriptor localBlockDescriptor;
   tFblLbtBlockFilter blockFilter;

   result = kFblFailed;

   FblLbtBlockFilterInit(&blockFilter);

   for (localBlockDescriptor = FblLbtBlockFirst(&blockFilter);
        FblLbtBlockDone() == FALSE;
        localBlockDescriptor = FblLbtBlockNext()){
      if(localBlockDescriptor.blockType == blockType)
      {
         *blockDescriptor = localBlockDescriptor;
         result = kFblOk;
         break;
      }
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_BLOCK_TYPE )

tFblResult FblLbtGetBlockTypeByNr(tFblLbtBlockNr blockNr,
                                  V_MEMRAM1 tFblLbtBlockType V_MEMRAM2 V_MEMRAM3 * blockType){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.blockType = 0uL;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *blockType = blockDescriptor.blockType;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_BLOCK_INDEX )

tFblResult FblLbtGetBlockIndexByNr(tFblLbtBlockNr blockNr, V_MEMRAM1 tFblLbtBlockIndex V_MEMRAM2 V_MEMRAM3 * blockIndex){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.blockIndex = 0uL;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *blockIndex = blockDescriptor.blockIndex;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_HEADER_ADDRESS )

tFblResult FblLbtGetBlockHeaderAddressByNr(tFblLbtBlockNr blockNr,
                                           V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * blockHeaderAddress){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.headerAddress = 0uL;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *blockHeaderAddress = blockDescriptor.headerAddress;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_BM_HEADER_ADDRESS )

tFblResult FblLbtGetBlockBmHeaderAddressByNr(tFblLbtBlockNr blockNr,
                                             V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * bmHeaderAddress){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.bmHeaderAddress = 0uL;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *bmHeaderAddress = blockDescriptor.bmHeaderAddress;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_MAX_PROG_ATTEMPTS )

tFblResult FblLbtGetBlockMaxProgAttemptsByNr(tFblLbtBlockNr blockNr,
                                             V_MEMRAM1 tFblLbtMaxProgAttempts V_MEMRAM2 V_MEMRAM3 * maxProgAttempts){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.maxProgAttempts = 0u;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *maxProgAttempts = blockDescriptor.maxProgAttempts;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_VERIFY_INPUT )

tFblResult FblLbtGetBlockVerifyInputFuncByNr(tFblLbtBlockNr blockNr,
                                             V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyInput = (tExportFct)0;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyInput;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_VERIFY_PROCESSED )

tFblResult FblLbtGetBlockVerifyProcessedFuncByNr(tFblLbtBlockNr blockNr,
                                                 V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyProcessed = (tExportFct)0;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyProcessed;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_VERIFY_PIPELINED )

tFblResult FblLbtGetBlockVerifyPipelinedFuncByNr(tFblLbtBlockNr blockNr,
                                                 V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyPipelined = (tExportFct)0;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyPipelined;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_VERIFY_OUTPUT )

tFblResult FblLbtGetBlockVerifyOutputFuncByNr(tFblLbtBlockNr blockNr,
                                              V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyOutput = (tExportFct)0uL;

   if(FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyOutput;
      result = kFblOk;
   }

   return result;
}
#endif

#if defined( FBL_LBT_ENABLE_BLOCK_INDEX )

tFblResult FblLbtGetBlockDescriptorByIndex(tFblLbtBlockIndex blockIndex,
                                           V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor){
   tFblResult result;
   tBlockDescriptor localBlockDescriptor;
   tFblLbtBlockFilter blockFilter;

   result = kFblFailed;

   FblLbtBlockFilterInit(&blockFilter);

   for (localBlockDescriptor = FblLbtBlockFirst(&blockFilter);
        FblLbtBlockDone() == FALSE;
        localBlockDescriptor = FblLbtBlockNext()){
      if(localBlockDescriptor.blockIndex == blockIndex)
      {
         *blockDescriptor = localBlockDescriptor;
         result = kFblOk;
         break;
      }
   }

   return result;
}

tFblResult FblLbtGetBlockNrByIndex(tFblLbtBlockIndex blockIndex,
   V_MEMRAM1 tFblLbtBlockNr V_MEMRAM2 V_MEMRAM3 * blockNr){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.blockNr = 0u;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *blockNr = blockDescriptor.blockNr;
      result = kFblOk;
   }

   return result;
}

# if defined( FBL_LBT_ENABLE_BLOCK_TYPE )

tFblResult FblLbtGetBlockTypeByIndex(tFblLbtBlockIndex blockIndex,
                                     V_MEMRAM1 tFblLbtBlockType V_MEMRAM2 V_MEMRAM3 * blockType){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.blockType = 0uL;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *blockType = blockDescriptor.blockType;
      result = kFblOk;
   }

   return result;
}
# endif

# if defined( FBL_LBT_ENABLE_HEADER_ADDRESS )

tFblResult FblLbtGetBlockHeaderAddressByIndex(tFblLbtBlockIndex blockIndex,
                                              V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * blockHeaderAddress){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.headerAddress = 0uL;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *blockHeaderAddress = blockDescriptor.headerAddress;
      result = kFblOk;
   }

   return result;
}
# endif

# if defined( FBL_LBT_ENABLE_BM_HEADER_ADDRESS )

tFblResult FblLbtGetBlockBmHeaderAddressByIndex(tFblLbtBlockIndex blockIndex,
                                                V_MEMRAM1 tFblAddress V_MEMRAM2 V_MEMRAM3 * bmHeaderAddress){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.bmHeaderAddress = 0uL;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *bmHeaderAddress = blockDescriptor.bmHeaderAddress;
      result = kFblOk;
   }

   return result;
}
# endif

# if defined( FBL_LBT_ENABLE_MAX_PROG_ATTEMPTS )

tFblResult FblLbtGetBlockMaxProgAttemptsByIndex(tFblLbtBlockIndex blockIndex,
                                                V_MEMRAM1 tFblLbtMaxProgAttempts V_MEMRAM2 V_MEMRAM3 * maxProgAttempts){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.maxProgAttempts = 0u;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *maxProgAttempts = blockDescriptor.maxProgAttempts;
      result = kFblOk;
   }

   return result;
}
# endif

# if defined( FBL_LBT_ENABLE_VERIFY_INPUT )

tFblResult FblLbtGetBlockVerifyInputFuncByIndex(tFblLbtBlockIndex blockIndex,
                                                V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyInput = (tExportFct)0;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyInput;
      result = kFblOk;
   }

   return result;
}
# endif

# if defined( FBL_LBT_ENABLE_VERIFY_PROCESSED )

tFblResult FblLbtGetBlockVerifyProcessedFuncByIndex(tFblLbtBlockIndex blockIndex,
                                                    V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyProcessed = (tExportFct)0;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyProcessed;
      result = kFblOk;
   }

   return result;
}
# endif

# if defined( FBL_LBT_ENABLE_VERIFY_PIPELINED )

tFblResult FblLbtGetBlockVerifyPipelinedFuncByIndex(tFblLbtBlockIndex blockIndex,
                                                    V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyPipelined = (tExportFct)0;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyPipelined;
      result = kFblOk;
   }

   return result;
}
# endif

# if defined( FBL_LBT_ENABLE_VERIFY_OUTPUT )

tFblResult FblLbtGetBlockVerifyOutputFuncByIndex(tFblLbtBlockIndex blockIndex,
                                                 V_MEMRAM1 tExportFct V_MEMRAM2 V_MEMRAM3 * blockVerifyFunc){
   tFblResult result;
   tBlockDescriptor blockDescriptor;

   result = kFblFailed;

   blockDescriptor.verifyOutput = (tExportFct)0;

   if(FblLbtGetBlockDescriptorByIndex(blockIndex, &blockDescriptor) == kFblOk){
      *blockVerifyFunc = blockDescriptor.verifyOutput;
      result = kFblOk;
   }

   return result;
}
# endif
#endif

tFblResult FblLbtCheckAddressRange(tFblAddress address, tFblAddress rangeStart, tFblLength rangeLength){
   tFblResult result;

   result = kFblFailed;

   if(    (address >= rangeStart)
       && ((address - rangeStart) < rangeLength) ){
      result = kFblOk;
   }

   return result;
}

tFblResult FblLbtCheckRangeContained(tFblAddress address, tFblLength length, tFblAddress rangeStart, tFblLength rangeLength){
   tFblResult result;

   result = kFblFailed;

   if((FblLbtCheckAddressRange(address, rangeStart, rangeLength) == kFblOk)
       && (length <= rangeLength)
       && ((address - rangeStart) <= (rangeLength - length)) ){
      result = kFblOk;
   }

   return result;
}

#if defined( FBL_LBT_ENABLE_REPROGRAMMABLE_LBT )

tFblResult FblLbtCheckConsistency(void){
   tFblResult result;
   tFblLbtBlockNr localBlockNr;
   tBlockDescriptor baseBlock, newBlock;

   result = kFblOk;

   FblLbtActivateLbtBlock();

   if(fblLbtActive->noOfBlocks > (tFblLbtBlockCount)FBL_LBT_BLOCK_COUNT){
      result = kFblFailed;
   }

   if((result == kFblOk) && (fblLbtActive->magicFlag != FblLogicalBlockTable.magicFlag)){
      result = kFblFailed;
   }

   if(result == kFblOk){
      for (localBlockNr = 0u; localBlockNr < FblLogicalBlockTable.noOfBlocks; localBlockNr++)
      {
         baseBlock = FblLogicalBlockTable.logicalBlock[localBlockNr];
         result = FblLbtGetBlockDescriptorByNr(localBlockNr, &newBlock);
         if(result == kFblOk)
         {
            result = FblLbtBlockCompare(&baseBlock, &newBlock);
         }
         if(result != kFblOk)
         {
            break;
         }
      }
   }

   if(result == kFblOk){
      result = FblLbtCheckReferences();
   }

   FblLbtInitPowerOn();

   return result;
}

void FblLbtActivateLbtBlock(void){
   fblLbtActive = (V_MEMROM1 tLogicalBlockTable V_MEMROM2 V_MEMROM3 *)FblLogicalBlockTable.logicalBlock[FBL_MTAB_LBT_BLOCK_NUMBER].blockStartAddress;
}
#endif

void FblLbtActivateLbtBlockByAddress(tFblAddress address){
   fblLbtActive = (V_MEMROM1 tLogicalBlockTable V_MEMROM2 V_MEMROM3 *)address;
}

