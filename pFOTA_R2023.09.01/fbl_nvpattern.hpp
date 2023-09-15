

#ifndef __FBLLIB_NVPATTERN_H__
#define __FBLLIB_NVPATTERN_H__

#define FBLLIB_NVPATTERN_VERSION           0x0104u
#define FBLLIB_NVPATTERN_RELEASE_VERSION   0x02u

#include "fbl_nvpattern_oem.hpp"

#ifndef FBL_NVPATTERN_ENABLE_BLOCK_PROPERTIES
#define kFblNvPatternId_Separator           kFblNvPatternId_Last
#endif

vsint16 FblNvPatternGetBaseAddr( vuint8 blockNr
   ,                                tFblNvPatternId patternId
   ,                                V_MEMRAM1 IO_PositionType V_MEMRAM2 V_MEMRAM3 * pPatternAddress
   ,                                V_MEMRAM1 IO_SizeType V_MEMRAM2 V_MEMRAM3 * pPatternLength );
vsint16 FblNvPatternGetBaseAddrByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,                                                 tFblNvPatternId patternId
   ,                                                 V_MEMRAM1 IO_PositionType V_MEMRAM2 V_MEMRAM3 * pPatternAddress
   ,                                                 V_MEMRAM1 IO_SizeType V_MEMRAM2 V_MEMRAM3 * pPatternLength );
tFblResult FblNvPatternSet( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, tFblNvPatternId patternId );
tFblResult FblNvPatternSetByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,  tFblNvPatternId patternId );
tFblResult FblNvPatternClr( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, tFblNvPatternId patternId );
tFblResult FblNvPatternClrByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,  tFblNvPatternId patternId );
tFblResult FblNvPatternGet( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, tFblNvPatternId patternId );
tFblResult FblNvPatternGetByBlockDescriptor( const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,  tFblNvPatternId patternId );

#if defined( FBL_NVPATTERN_ENABLE_BLOCK_PROPERTIES )
tFblResult FblNvPatternGetProperty(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,     tFblNvPatternId propertyId
   ,     IO_SizeType bufferLength
   ,     vuint8* pDestBuffer );
tFblResult FblNvPatternGetPropertyByBlockDescriptor(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,     tFblNvPatternId propertyId
   ,     IO_SizeType bufferLength
   ,     vuint8* pDestBuffer );
tFblResult FblNvPatternSetProperty(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,     const vuint8* pSrcBuffer
   ,     tFblNvPatternId propertyId);
tFblResult FblNvPatternSetPropertyByBlockDescriptor(const V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor
   ,     const vuint8* pSrcBuffer
   ,     tFblNvPatternId propertyId);
#endif

#endif

