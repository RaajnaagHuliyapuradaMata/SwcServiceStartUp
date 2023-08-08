

#include "fbl_inc.hpp"

#if( FBLMIO_VERSION != 0x0301u ) || \
    ( FBLMIO_RELEASE_VERSION != 0x01u )
# error "Error in FBL_MIO.C: Source and header file are inconsistent!"
#endif

#if( FBLMIO_VERSION != _FBLMIO_VERSION ) || \
    ( FBLMIO_RELEASE_VERSION != _FBLMIO_RELEASE_VERSION )
# error "Error in FBL_MIO.C: Source and V_VER.H are inconsistent!"
#endif

#if !defined( FBL_MIO_ENABLE_SEGMENT_CACHING ) || \
    !defined( FBL_MIO_DISABLE_SEGMENT_CACHING )
# define FBL_MIO_ENABLE_SEGMENT_CACHING
#endif

#define FBLMIO_START_SEC_VAR
#include "MemMap.hpp"

V_MEMRAM0 V_MEMRAM1      vuint8              V_MEMRAM2      memDrvDeviceActive;
V_MEMRAM0 V_MEMRAM1      vuint8              V_MEMRAM2      memDrvFunctionActive;

V_MEMRAM0 V_MEMRAM1      vsint16             V_MEMRAM2      memSegment;

#if defined( FBL_MIO_ENABLE_SEGMENT_CACHING )
V_MEMRAM0 static V_MEMRAM1 vsint16              V_MEMRAM2      cachedSegment;
V_MEMRAM0 static V_MEMRAM1 tFlashBlock          V_MEMRAM2      cachedBlock;
#endif
V_MEMRAM0 static V_MEMRAM1 vsint16              V_MEMRAM2      nextValidSegment;

#define FBLMIO_STOP_SEC_VAR
#include "MemMap.hpp"

#define FBLMIO_START_SEC_CODE
#include "MemMap.hpp"

void MemDriver_InitPowerOn( void ){
   memDrvDeviceActive   = kMioDeviceIdle;
   memDrvFunctionActive = kMioFunctionNone;

   memSegment = -1;
   nextValidSegment = -1;

#if defined( FBL_MIO_ENABLE_SEGMENT_CACHING )

   cachedSegment = 0;
   cachedBlock.begin = FlashBlock[0].begin;
   cachedBlock.end = FlashBlock[0].end;
#endif
}

vsint16 FblMemSegmentNrGet( tFblAddress address ){
   vsint16 segment;
   tFblAddress localAddress;

   localAddress = address;

#if defined( FBL_MIO_ENABLE_SEGMENT_CACHING )

   if(   ( localAddress >= cachedBlock.begin )
       && ( localAddress <= cachedBlock.end )
      ){
      segment = cachedSegment;
   }
   else{
      nextValidSegment = 0;
      while (nextValidSegment < (vsint16)kNrOfFlashBlock)
      {
         if(((vuint8)nextValidSegment & (vuint8)0x0Fu) == (vuint8)0x00u)
         {
            (void)FblRealTimeSupport();
         }

         if(FlashBlock[nextValidSegment].end >= localAddress)
         {
            break;
         }

         nextValidSegment++;
      }

      if(nextValidSegment < (vsint16)kNrOfFlashBlock)
      {
         if(localAddress >= FlashBlock[nextValidSegment].begin)
         {
            segment = nextValidSegment;

            cachedBlock.begin = FlashBlock[segment].begin;
            cachedBlock.end = FlashBlock[segment].end;
         }
         else
         {
            segment = -1;

            if(nextValidSegment <= 0)
            {
               cachedBlock.begin = 0x00u;
            }
            else
            {
               cachedBlock.begin = FlashBlock[nextValidSegment - 1].end + 1u;
            }

            cachedBlock.end = FlashBlock[nextValidSegment].begin - 1u;
         }
      }
      else
      {
         segment = -1;

         cachedBlock.begin = FlashBlock[kNrOfFlashBlock - 1u].end + 1u;

         cachedBlock.end = (tFblAddress)(-1);
      }

      cachedSegment = segment;
   }
#else

   segment = (vsint16)(kNrOfFlashBlock - 1u);

   while (segment >= 0){
      if(  (localAddress >= FlashBlock[segment].begin)
         && (localAddress <= FlashBlock[segment].end) )
      {
         nextValidSegment = segment;

         break;
      }

      if(((vuint8)segment & (vuint8)0x0Fu) == (vuint8)0x00u)
      {
         (void)FblRealTimeSupport();
      }

      segment--;
   }
#endif

   return segment;
}

tFblResult FblMemGetDeviceByAddr(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * device){
   tFblResult result;
   vsint16 localMemSegment;

   result = kFblFailed;

   localMemSegment = FblMemSegmentNrGet(address);
   if(localMemSegment >= 0){
#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES )
      *device = FlashBlock[localMemSegment].device;
#else
      *device = kMioDeviceInternalFlash;
#endif
      result = kFblOk;
   }

   return result;
}

tFblResult FblMemGetDeviceByRange(tFblAddress address, tFblLength length, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * device){
   tFblResult result;
   vuint8 localDevice;
   vsint16 localMemSegmentStart;
   vsint16 localMemSegmentEnd;
#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES )
   vsint16 localMemSegment;
#endif

   result = kFblFailed;

   if(length == 0u){
      result = FblMemGetDeviceByAddr(address, device);
   }
   else{
      localMemSegmentStart = FblMemSegmentNrGet(address);
      localMemSegmentEnd = FblMemSegmentNrGet(address + (length - 1u));

      if(   (localMemSegmentStart >= 0)
          && (localMemSegmentEnd >= 0)
         )
      {
         result = kFblOk;
#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES )

         localDevice = FlashBlock[localMemSegmentStart].device;

         for (localMemSegment = localMemSegmentStart + 1; localMemSegment <= localMemSegmentEnd; localMemSegment++)
         {
            if(localDevice != FlashBlock[localMemSegment].device)
            {
               result = kFblFailed;
               break;
            }
         }
#else
         localDevice = kMioDeviceInternalFlash;
#endif
      }

      if(result == kFblOk)
      {
         *device = localDevice;
      }
   }

   return result;
}

tFblLength FblReadProm(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * buffer, tFblLength length){
   tFblLength actualReadCount;

   (void)FblReadPromExt(address, buffer, length , &actualReadCount);

   return actualReadCount;
}

IO_ErrorType FblReadPromExt(tFblAddress address, V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * buffer, tFblLength length,
   V_MEMRAM1 tFblLength V_MEMRAM2 V_MEMRAM3 * actualReadCount){
   IO_ErrorType result;
   tFblAddress localAddress;
   V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * localBuffer;
   tFblLength localLength;
   tFblLength localActualReadCount;
   tFblLength currentReadCount;
   vsint16    nextMemSegment;

   localAddress = address;
   localLength = length;
   localBuffer = buffer;
   localActualReadCount = 0u;
   result = IO_E_OK;

   (void)FblRealTimeSupport();

   memSegment = FblMemSegmentNrGet(localAddress);

   if(memSegment < 0){
      if(nextValidSegment < (vsint16)kNrOfFlashBlock)
      {
         if(
               (localAddress < FlashBlock[nextValidSegment].begin) &&
               (localLength > (FlashBlock[nextValidSegment].begin - localAddress))
            )
         {
            memSegment = nextValidSegment;

            localLength -= (FlashBlock[memSegment].begin - localAddress);

            localAddress = FlashBlock[memSegment].begin;
         }
      }
   }

   nextMemSegment = memSegment;

   if(memSegment >= 0){
      while (localLength > 0u)
      {
         if((localAddress + (localLength - 1u)) > FlashBlock[memSegment].end)
         {
            currentReadCount = (FlashBlock[memSegment].end - localAddress) + 1u;

            nextMemSegment++;

            if(nextMemSegment < (vsint16)kNrOfFlashBlock)
            {
               localLength = ((FlashBlock[nextMemSegment].begin - localAddress) < localLength)
                  ? (localLength - (FlashBlock[nextMemSegment].begin - localAddress)) : 0u;
            }
            else

            {
               localLength = 0u;
            }
         }
         else
         {
            currentReadCount = localLength;
            localLength = 0u;
         }

         switch(MemDriver_RReadSync(localBuffer, currentReadCount, localAddress))
         {
            case IO_E_ERASED:
            {
               result = IO_E_ERASED;
            }
            case IO_E_OK:
            {
               memSegment = nextMemSegment;
               localBuffer = (vuint8 *)&localBuffer[currentReadCount];
               localAddress = FlashBlock[memSegment].begin;
               localActualReadCount += currentReadCount;
               break;
            }
            default:
            {
               localLength = 0u;
               result = IO_E_NOT_OK;
               break;
            }
         }

         (void)FblRealTimeSupport();
      }
   }
   else{
      localActualReadCount = 0u;
   }

   *actualReadCount = localActualReadCount;

   return result;
}

#if defined( FBL_ENABLE_MULTIPLE_MEM_DEVICES )

IO_ErrorType V_API_NEAR MemDriver_InitSync( void * address ){
   vuintx i;
   IO_ErrorType result = IO_E_OK;
   IO_ErrorType rc;

   {
      for (i = 0u; i < kNrOfMemDrv; i++)
      {
         MemDriver_InitBegin(i);
         rc = (*memDrvLst[i].init)(address);
         MemDriver_InitEnd(i);

         if(rc != IO_E_OK)
         {
            result = rc;
            break;
         }
      }
   }

   return result;
}

IO_ErrorType V_API_NEAR MemDriver_DeinitSync( void * address ){
   vuintx i;
   IO_ErrorType result = IO_E_OK;

   for (i = 0u; i < kNrOfMemDrv; i++){
      result = (*memDrvLst[i].deinit)(address);
      if(result != IO_E_OK)
      {
         break;
      }
   }
   return result;
}

IO_ErrorType V_API_NEAR MemDriver_RWriteSync(IO_MemPtrType buf, IO_SizeType len, IO_PositionType addr){
   IO_ErrorType result;
   MemDriver_RWriteBegin(FlashBlock[memSegment].device);
   result = (*memDrvLst[FlashBlock[memSegment].device].write)((buf), (len), (addr));
   MemDriver_RWriteEnd(FlashBlock[memSegment].device);
   return result;
}

IO_ErrorType V_API_NEAR MemDriver_REraseSync(IO_SizeType len, IO_PositionType addr){
   IO_ErrorType result;
   MemDriver_REraseBegin(FlashBlock[memSegment].device);
   result = (*memDrvLst[FlashBlock[memSegment].device].erase) ((len), (addr));
   MemDriver_REraseEnd(FlashBlock[memSegment].device);
   return result;
}

#else

IO_ErrorType V_API_NEAR MemDriver_InitSync( void * address ){
   IO_ErrorType result;
   MemDriver_InitBegin(kMioDeviceInternalFlash);
   result = FlashDriver_InitSync(address);
   MemDriver_InitEnd(kMioDeviceInternalFlash);

   return result;
}

IO_ErrorType V_API_NEAR MemDriver_DeinitSync( void * address ){
   IO_ErrorType result;

      MemDriver_DeinitBegin(kMioDeviceInternalFlash);
      result = FlashDriver_DeinitSync(address);
      MemDriver_DeinitEnd(kMioDeviceInternalFlash);

   return result;
}

IO_ErrorType V_API_NEAR MemDriver_RWriteSync( IO_MemPtrType buf, IO_SizeType len, IO_PositionType addr ){
   IO_ErrorType result;
   MemDriver_RWriteBegin(kMioDeviceInternalFlash);
   result = FlashDriver_RWriteSync(buf, len, addr);
   MemDriver_RWriteEnd(kMioDeviceInternalFlash);
   return result;
}

IO_ErrorType V_API_NEAR MemDriver_REraseSync( IO_SizeType len, IO_PositionType addr ){
   IO_ErrorType result;
   MemDriver_REraseBegin((kMioDeviceInternalFlash));
   result = FlashDriver_REraseSync(len, addr);
   MemDriver_REraseEnd((kMioDeviceInternalFlash));
   return result;
}

#endif

#define FBLMIO_STOP_SEC_CODE
#include "MemMap.hpp"

