

#include "fbl_inc.hpp"
#include "fbl_nvpattern.hpp"

#if( FBLLIB_NVPATTERN_VERSION != 0x0104u ) || \
    ( FBLLIB_NVPATTERN_RELEASE_VERSION != 0x02u )
# error "Error in fbl_nvpattern.c: Source and header file are inconsistent!"
#endif

#if( FBLLIB_NVPATTERN_VERSION != _FBLLIB_NVPATTERN_VERSION ) || \
    ( FBLLIB_NVPATTERN_RELEASE_VERSION != _FBLLIB_NVPATTERN_RELEASE_VERSION )
# error "Error in fbl_nvpattern.c: Source and v_ver.h are inconsistent!"
#endif

#define kFblNvMarkerValue                       {0x73u, 0x6Au, 0x29u, 0x3Eu}
#define kFblNvMaskValue                         {0x8Cu, 0x95u, 0xD6u, 0xC1u}
#define kFblNvPatternSize                       4u

#define PAGE_ALIGN(len, align)                  (((len) + ((align) - 1u)) & ~((align) - 1u))

#define IS_POWOFTWO(val)                        (((val) & ~((val) - 1u)) == (val))

#if( FBL_MAX_SEGMENT_SIZE < kFblNvPatternSize )
#define kFblNvPatternSegmentSize               PAGE_ALIGN(kFblNvPatternSize, FBL_MAX_SEGMENT_SIZE)
#else
#define kFblNvPatternSegmentSize               FBL_MAX_SEGMENT_SIZE
#endif

#define IS_VALID_PATTERN_ID(id)                 (((id) > kFblNvPatternId_Invalid)   && ((id) < kFblNvPatternId_Separator))
#define IS_VALID_PROPERTY_ID(id)                (((id) > kFblNvPatternId_Separator) && ((id) < kFblNvPatternId_Last))

#define DONT_COMPARE                            (vuint8*)0u

typedef struct{
   vuint32  alignDummy;
   vuint8   data[kFblNvPatternSegmentSize];
}tFblNvPatternAlignedBuffer;

typedef enum{
   NoMemSegment = 0u
   ,  ReadError
   ,  Erased
   ,  UnexpectedValue
   ,  ExpectedValue
}tFblNvPatternItemState;

typedef struct{
   tFblNvPatternItemState markerState;
   tFblNvPatternItemState maskState;
}tFblNvPatternState;

V_MEMRAM0 static V_MEMRAM1 tFblNvPatternAlignedBuffer V_MEMRAM2 pageBuffer;

static tFblResult FblNvPatternWritePageAligned( const vuint8* pSrcBuffer, IO_PositionType add, vuint32 length );
static tFblNvPatternItemState FblNvPatternGetPatternItemState( IO_PositionType patternAddress, IO_SizeType length, const vuint8* compareValue );
static tFblNvPatternState FblNvPatternGetPatternState( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * pBlockDescriptor
   ,                                                      tFblNvPatternId patternId
   ,                                                      V_MEMRAM1 IO_PositionType V_MEMRAM2 V_MEMRAM3 * pPatternAddress
   ,                                                      V_MEMRAM1 IO_SizeType V_MEMRAM2 V_MEMRAM3 * pPatternLength );

static tFblResult FblNvPatternWritePageAligned( const vuint8* pSrcBuffer, IO_PositionType add, IO_SizeType length ){
   tFblResult result;
   IO_SizeType i;
   IO_SizeType writeGranularity;
   IO_SizeType actualWriteLength;
   IO_SizeType lengthWritten;

   result = kFblOk;
   lengthWritten = 0u;

   while(length > 0u){
      (void)FblRealTimeSupport();

      if(length > kFblNvPatternSegmentSize)
      {
         writeGranularity = kFblNvPatternSegmentSize;
         actualWriteLength = kFblNvPatternSegmentSize;
      }
      else
      {
         writeGranularity = PAGE_ALIGN(length, MemDriver_SegmentSize);
         actualWriteLength = length;
      }

      for(i = 0u; i < actualWriteLength; i++)
      {
         pageBuffer.data[i] = pSrcBuffer[i + lengthWritten];
      }

      if(actualWriteLength < kFblNvPatternSegmentSize)
      {
         for(i = actualWriteLength; i < writeGranularity; i++)
         {
            pageBuffer.data[i] = 0u;
         }
      }

      if(MemDriver_RWriteSync(pageBuffer.data, writeGranularity, add) != IO_E_OK)
      {
         result = kFblFailed;
         break;
      }

      add += actualWriteLength;
      length -= actualWriteLength;
      lengthWritten += actualWriteLength;
   }

   return result;
}

static tFblNvPatternItemState FblNvPatternGetPatternItemState( IO_PositionType patternAddress, IO_SizeType length, const vuint8* compareValue){
   tFblNvPatternItemState itemState;
   vuint8 memErasedValue;
   IO_SizeType currentReadLength;
   vuint32 i;

   itemState = NoMemSegment;

#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES )
      memErasedValue = memDrvLst[FlashBlock[memSegment].device].erasedValue;
#else
      memErasedValue = FBL_FLASH_DELETED;
#endif

   while(length > 0u){
      if(length > kFblNvPatternSegmentSize)
      {
         currentReadLength = kFblNvPatternSegmentSize;
      }
      else
      {
         currentReadLength = length;
      }

      switch(MemDriver_RReadSync(pageBuffer.data, currentReadLength, patternAddress))
      {
         case IO_E_OK:
         case IO_E_ERASED:
         {
            itemState = Erased;
            break;
        }
        default:
        {
           itemState = ReadError;
           assertFbl(0u, kFblSysAssertParameterOutOfRange);
           break;
        }
      }

      if(itemState == Erased)
      {
         for(i = 0u; i < currentReadLength; i++)
         {
            if((compareValue != DONT_COMPARE) && (pageBuffer.data[i] == compareValue[i]))
            {
               itemState = ExpectedValue;
            }
            else if(pageBuffer.data[i] != memErasedValue)
            {
               itemState = UnexpectedValue;
               assertFbl(0u, kFblSysAssertParameterOutOfRange);
               break;
            }
            else
            {
            }
         }
      }

      if((itemState == UnexpectedValue) || (itemState == ReadError))
      {
         break;
      }

      length -= currentReadLength;
   }

   return itemState;
}

static tFblNvPatternState FblNvPatternGetPatternState( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * pBlockDescriptor
   ,                                                      tFblNvPatternId patternId
   ,                                                      V_MEMRAM1 IO_PositionType V_MEMRAM2 V_MEMRAM3 * pPatternAddress
   ,                                                      V_MEMRAM1 IO_SizeType V_MEMRAM2 V_MEMRAM3 * pPatternLength ){
   vuint32              multiplicity;
   tFblNvPatternState   patternState;
   IO_PositionType      patternAddress;

   vuint8 fblMarkerValue[kFblNvPatternSize] = kFblNvMarkerValue;
   vuint8 fblMaskValue[kFblNvPatternSize] = kFblNvMaskValue;

   patternAddress = *pPatternAddress;
   patternState.markerState = NoMemSegment;
   patternState.maskState = NoMemSegment;
   memSegment = -1;

   if(IS_VALID_PATTERN_ID(patternId)){
      memSegment = FblNvPatternGetBaseAddrByBlockDescriptor(pBlockDescriptor, patternId, &patternAddress, pPatternLength);
   }

   if(memSegment >= 0){
#if defined( FBL_NVPATTERN_ENABLE_MULTIPLE_VALIDATION )

      multiplicity = fblNvPatternMultiplicity[(patternId - 1)];
#else
      multiplicity = 1u;
#endif
   }
   else{
      multiplicity = 0u;
   }

   while(multiplicity >= 1u){
      (void)FblRealTimeSupport();

      patternState.markerState = FblNvPatternGetPatternItemState(patternAddress, kFblNvPatternSize, fblMarkerValue);
      patternState.maskState = FblNvPatternGetPatternItemState((patternAddress + *pPatternLength), kFblNvPatternSize, fblMaskValue);

      if(     ((patternState.markerState == ExpectedValue) && (patternState.maskState == Erased))
            || ((patternState.markerState == Erased)        && (patternState.maskState == Erased)))
      {
         break;
      }

      patternAddress += (*pPatternLength * 2u);

      multiplicity--;
   }

   *pPatternAddress = patternAddress;

   return patternState;
}

vsint16 FblNvPatternGetBaseAddr( vuint8 blockNr
   ,                                tFblNvPatternId patternId
   ,                                V_MEMRAM1 IO_PositionType V_MEMRAM2 V_MEMRAM3 * pPatternAddress
   ,                                V_MEMRAM1 IO_SizeType V_MEMRAM2 V_MEMRAM3 * pPatternLength ){
   tBlockDescriptor  blockDescriptor;
   tFblResult        result;

   result = FblLbtGetBlockDescriptorByNr(blockNr, &blockDescriptor);

   if(result == kFblOk){
      memSegment = FblNvPatternGetBaseAddrByBlockDescriptor(&blockDescriptor, patternId, pPatternAddress, pPatternLength);
   }
   else{
      memSegment = -1;
   }

   return memSegment;
}

vsint16 FblNvPatternGetBaseAddrByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                                 tFblNvPatternId patternId
   ,                                                 V_MEMRAM1 IO_PositionType V_MEMRAM2 V_MEMRAM3 * pPatternAddress
   ,                                                 V_MEMRAM1 IO_SizeType V_MEMRAM2 V_MEMRAM3 * pPatternLength ){
   IO_PositionType   lastBlockAddress;
   IO_SizeType       patternLength;
   IO_SizeType       offsetLength;
   vuintx            i;
   vuintx            upperBound;

   lastBlockAddress = blockDescriptor->blockStartAddress + (blockDescriptor->blockLength - 1u);

   memSegment = FblMemSegmentNrGet(lastBlockAddress);

   if(memSegment >= 0){
      assertFbl(IS_POWOFTWO(MemDriver_SegmentSize), kFblSysAssertParameterOutOfRange);

      patternLength = PAGE_ALIGN(kFblNvPatternSize, MemDriver_SegmentSize);

      offsetLength = 0u;

      upperBound = (vuintx)((patternId > kFblNvPatternId_Separator) ? (kFblNvPatternId_Separator - 1) : patternId);

      for(i = 0u; i < upperBound; i++)
      {
#if defined( FBL_NVPATTERN_ENABLE_MULTIPLE_VALIDATION )
         offsetLength += (patternLength * (fblNvPatternMultiplicity[i] * 2u));
#else
         offsetLength += (patternLength * 2u);
#endif
      }

#if defined( FBL_NVPATTERN_ENABLE_BLOCK_PROPERTIES )

      upperBound = (vuintx)((patternId > kFblNvPatternId_Separator) ? ((patternId - kFblNvPatternId_Separator)) : 0);

      for(i = 0u; i < upperBound; i++)
      {
         offsetLength += PAGE_ALIGN(fblNvBlockProperties[i].length, MemDriver_SegmentSize);
         patternLength = PAGE_ALIGN(fblNvBlockProperties[i].length, MemDriver_SegmentSize);
      }
#endif

      *pPatternLength  = patternLength;
      *pPatternAddress = (lastBlockAddress - offsetLength) + 1u;

      assertFbl(*pPatternAddress >= blockDescriptor->blockStartAddress, kFblSysAssertParameterOutOfRange);

      assertFbl(FblMemSegmentNrGet(*pPatternAddress) == memSegment, kFblSysAssertParameterOutOfRange);
   }
   else{
      assertFbl(0u, kFblSysAssertParameterOutOfRange);
   }

   return memSegment;
}

tFblResult FblNvPatternSet( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, tFblNvPatternId patternId ){
   tBlockDescriptor localBlockDescriptor;
   tFblResult result;

   result = kFblFailed;

   result = FblLbtGetBlockDescriptorByNr(blockDescriptor->blockNr, &localBlockDescriptor);

   if(result == kFblOk){
      result = FblNvPatternSetByBlockDescriptor(&localBlockDescriptor, patternId);
   }

   return result;
}

tFblResult FblNvPatternSetByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                            tFblNvPatternId patternId ){
   IO_PositionType               patternAddress;
   IO_SizeType                   patternLength;
   tFblResult                    result;
   tFblNvPatternState            patternState;

   vuint8 fblMarkerValue[kFblNvPatternSize] = kFblNvMarkerValue;

   result = kFblFailed;

   patternState = FblNvPatternGetPatternState(blockDescriptor, patternId, &patternAddress, &patternLength);

   if(patternState.markerState == Erased){
      if(kFblOk == FblNvPatternWritePageAligned(fblMarkerValue, patternAddress, kFblNvPatternSize))
      {
         patternState = FblNvPatternGetPatternState(blockDescriptor, patternId, &patternAddress, &patternLength);
         if(patternState.markerState == ExpectedValue)
         {
            result = kFblOk;
         }
      }
   }
   else if((patternState.markerState == ExpectedValue) && (patternState.maskState == Erased)){
      result = kFblOk;
   }
   else{
   }

   return result;
}

tFblResult FblNvPatternClr( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, tFblNvPatternId patternId ){
   tBlockDescriptor localBlockDescriptor;
   tFblResult result;

   result = kFblFailed;

   result = FblLbtGetBlockDescriptorByNr(blockDescriptor->blockNr, &localBlockDescriptor);

   if(result == kFblOk){
      result = FblNvPatternClrByBlockDescriptor(&localBlockDescriptor, patternId);
   }

   return result;
}

tFblResult FblNvPatternClrByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                            tFblNvPatternId patternId ){
   tFblResult                    result;
   IO_PositionType               patternAddress;
   IO_SizeType                   patternLength;
   tFblNvPatternState            patternState;

   vuint8 fblMaskValue[kFblNvPatternSize] = kFblNvMaskValue;

   result = kFblFailed;

   patternState = FblNvPatternGetPatternState(blockDescriptor, patternId, &patternAddress, &patternLength);

   if((patternState.markerState == ExpectedValue) && (patternState.maskState == Erased)){
      result = FblNvPatternWritePageAligned(fblMaskValue, (patternAddress + patternLength), kFblNvPatternSize);
   }
   else{
      result = kFblOk;
   }

   return result;
}

tFblResult FblNvPatternGet( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, tFblNvPatternId patternId ){
   tBlockDescriptor localBlockDescriptor;
   tFblResult result;

   result = kFblFailed;

   result = FblLbtGetBlockDescriptorByNr(blockDescriptor->blockNr, &localBlockDescriptor);

   if(result == kFblOk){
      result = FblNvPatternGetByBlockDescriptor(&localBlockDescriptor, patternId);
   }

   return result;
}

tFblResult FblNvPatternGetByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                            tFblNvPatternId patternId ){
   IO_PositionType      patternAddress;
   IO_SizeType          patternLength;
   tFblNvPatternState   patternState;
   tFblResult           result;

   result = kFblFailed;

   patternState = FblNvPatternGetPatternState(blockDescriptor, patternId, &patternAddress, &patternLength);
   if((patternState.markerState == ExpectedValue) && (patternState.maskState == Erased)){
      result = kFblOk;
   }

   return result;
}

#if defined( FBL_NVPATTERN_ENABLE_BLOCK_PROPERTIES )

tFblResult FblNvPatternGetProperty( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                     tFblNvPatternId propertyId
   ,                                     IO_SizeType bufferLength
   ,                                     vuint8* pDestBuffer ){
   tBlockDescriptor localBlockDescriptor;
   tFblResult result;

   result = kFblFailed;

   result = FblLbtGetBlockDescriptorByNr(blockDescriptor->blockNr, &localBlockDescriptor);

   if(result == kFblOk){
      result = FblNvPatternGetPropertyByBlockDescriptor(&localBlockDescriptor, propertyId, bufferLength, pDestBuffer);
   }

   return result;
}

tFblResult FblNvPatternGetPropertyByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                                      tFblNvPatternId propertyId
   ,                                                      IO_SizeType bufferLength
   ,                                                      vuint8* pDestBuffer ){
   IO_PositionType      propertyAddress;
   IO_SizeType          propertyLength;
   IO_SizeType          sizeToRead;
   tFblNvPatternId      depPattern;
   tFblResult           result;

   result = kFblFailed;
   sizeToRead = 0ul;

   if(IS_VALID_PROPERTY_ID(propertyId)){
      sizeToRead = fblNvBlockProperties[propertyId - kFblNvPatternId_Separator - 1].length;
      depPattern = fblNvBlockProperties[propertyId - kFblNvPatternId_Separator - 1].dependentPattern;

      if(sizeToRead <= bufferLength)
      {
         if(depPattern != kFblNvPatternId_Invalid)
         {
            result = FblNvPatternGetByBlockDescriptor(blockDescriptor, depPattern);
         }
         else
         {
            result = kFblOk;
         }
      }
   }

   if(result == kFblOk){
      if(FblNvPatternGetBaseAddrByBlockDescriptor(blockDescriptor, propertyId, &propertyAddress, &propertyLength) >= 0)
      {
         if(MemDriver_RReadSync(pDestBuffer, sizeToRead, propertyAddress) == IO_E_OK)
         {
            result = kFblOk;
         }
      }
   }

   return result;
}

tFblResult FblNvPatternSetProperty( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                     const vuint8* pSrcBuffer
   ,                                     tFblNvPatternId propertyId ){
   tBlockDescriptor localBlockDescriptor;
   tFblResult result;

   result = kFblFailed;

   result = FblLbtGetBlockDescriptorByNr(blockDescriptor->blockNr, &localBlockDescriptor);

   if(result == kFblOk){
      result = FblNvPatternSetPropertyByBlockDescriptor(&localBlockDescriptor, pSrcBuffer, propertyId);
   }

   return result;
}

tFblResult FblNvPatternSetPropertyByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                                      const vuint8* pSrcBuffer
   ,                                                      tFblNvPatternId propertyId ){
   IO_PositionType         propertyAddress;
   IO_SizeType             propertyLength;
   IO_SizeType             actualPropertyLength;
   tFblResult              result;

   result = kFblFailed;

   if(IS_VALID_PROPERTY_ID(propertyId)){
      if(FblNvPatternGetBaseAddrByBlockDescriptor(blockDescriptor, propertyId, &propertyAddress, &propertyLength) >= 0)
      {
         actualPropertyLength = fblNvBlockProperties[propertyId - kFblNvPatternId_Separator - 1].length;
         if(FblNvPatternGetPatternItemState(propertyAddress, actualPropertyLength, DONT_COMPARE) == Erased)
         {
            result = FblNvPatternWritePageAligned(pSrcBuffer, propertyAddress, actualPropertyLength);
         }
      }
   }

   return result;
}
#endif

#if(!IS_POWOFTWO(FBL_MAX_SEGMENT_SIZE))
# error "FBL_MAX_SEGMENT_SIZE must be a power of two."
#endif

