#define BM_HDR_SOURCE

#include "fbl_inc.hpp"
#include "bm_main.hpp"
#include "fbl_lbt_access.hpp"
#include "bm_hdr_ap.hpp"

#if defined( FBLBM_ENABLE_SECURE_BOOT )
#include "fbl_secboot.hpp"
#endif

#if( FBLBM_HDR_VERSION != 0x0102u ) || \
    ( FBLBM_HDR_RELEASE_VERSION != 0x00u )
# error "Error in BM_HDR.C: Source and Header file are inconsistent!"
#endif

tFblBmHdrCheckBmHeaderResult FblBmHdrGetBmHeader(tFblBmHdrTargetHandle targetHandle, tFblAddress bmHeaderAddress
   ,  V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 V_MEMRAM3 * bmHeader){
   tFblBmHdrCheckBmHeaderResult result;
   result = FBLBMHDR_CHKHDR_OK;

   if(FblReadProm(bmHeaderAddress, (vuint8 *)bmHeader, sizeof(tFblBmHdrHeader)) != sizeof(tFblBmHdrHeader)){
      result = FBLBMHDR_CHKHDR_READ_FAIL;
   }
   if(result == FBLBMHDR_CHKHDR_OK){
      if(bmHeader->bmTargetHandle != targetHandle){
         result = FBLBMHDR_CHKHDR_WRONG_TARGET;
      }
   }
   if(result == FBLBMHDR_CHKHDR_OK){
      if(kFblOk != FblBmHdrCheckConsistency(bmHeader)){
         result = FBLBMHDR_CHKHDR_HEADER_INCONSISTENT;
      }
   }
   return result;
}

#if defined( FBLBM_ENABLE_SECURE_BOOT )
tFblBmHdrCheckBmHeaderResult FblBmHdrVerifyBmHeader(
                      tFblBmHdrTargetHandle                       targetHandle
   ,  const V_MEMRAM1 tFblBmBlockInfo       V_MEMRAM2 V_MEMRAM3 * pBlockInfo
){
   tFblBmHdrCheckBmHeaderResult result;
   vuint8 bmHeaderMac[FBLSB_MAC_LENGTH];
   vuint8 bmHeaderMacLength;
   uint32 macId;
   result = FBLBMHDR_CHKHDR_OK;
   bmHeaderMacLength = sizeof(bmHeaderMac);
   if(
         kFblOk
      != ApplFblSbGetBmHeaderMac(
               &pBlockInfo->logicalBlock
            ,  bmHeaderMac
            ,  bmHeaderMacLength
         )
   ){
      result = FBLBMHDR_CHKHDR_GET_MAC_FAIL;
   }
   if(result == FBLBMHDR_CHKHDR_OK){
      macId = FblBmHdr_GetFblSbMacId(targetHandle);
      if(
            kFblOk
         != FblSb_MacVerify(
                  macId
               ,  (vuint32)&pBlockInfo->bmHeader
               ,  sizeof(tFblBmHdrHeader)
               ,  bmHeaderMac
               ,  bmHeaderMacLength
            )
      ){
         result = FBLBMHDR_CHKHDR_VERIFICATION_FAIL;
      }
   }
   return result;
}
#endif

tFblResult FblBmHdrCheckConsistency( const V_MEMRAM1 tFblBmHdrHeader V_MEMRAM2 V_MEMRAM3 * pBmHeader ){
   tFblResult result;
   vuintx i;
   result = kFblOk;
   if(pBmHeader->bmMagicFlag != FBLBMHDR_MAGIC_FLAG){
      result = kFblFailed;
   }

#if defined( FBLBM_ENABLE_SECURE_BOOT )
   if(result == kFblOk){
      if(pBmHeader->bmVerificationListEntries > FBLBMHDR_NUM_OF_VERIFICATION_ENTRIES){
         result = kFblFailed;
      }
   }
#endif

   if(
         (result == kFblOk)
      && (pBmHeader->bmEntryAddress != FBLBMHDR_ENTRY_ADDRESS_INVALID)
   ){
      result = kFblFailed;
      for(i = 0; i < pBmHeader->bmVerificationListEntries; i++){
         if(
               (pBmHeader->bmEntryAddress >= pBmHeader->bmVerificationList[i].address)
            && (pBmHeader->bmEntryAddress < (pBmHeader->bmVerificationList[i].address + pBmHeader->bmVerificationList[i].length))
         ){
            result = kFblOk;
            break;
         }
      }
   }
   return result;
}

tFblBmHdrCheckBmHeaderResult FblBmHdrFindValidHeader(tFblBmHdrTargetHandle targetHandle
   ,  V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo){
   tFblBmHdrCheckBmHeaderResult result;
   tFblLbtBlockFilter blockFilter;
   result = FBLBMHDR_CHKHDR_NOT_FOUND;
   FblLbtBlockFilterInit(&blockFilter);
   pBlockInfo->logicalBlock = FblLbtBlockFirst(&blockFilter);
   while(FblLbtBlockDone() == FALSE){
      if(kFblOk == FBLBM_CALLOUT_IS_VALIDBLOCK(targetHandle, &pBlockInfo->logicalBlock)){
         result = FblBmHdrGetBmHeader(targetHandle, pBlockInfo->logicalBlock.bmHeaderAddress, &pBlockInfo->bmHeader);
      }
      else{
         result = FBLBMHDR_CHKHDR_BLOCK_INVALID;
      }

#if defined( FBLBM_ENABLE_SECURE_BOOT )
      if(FBLBMHDR_CHKHDR_OK == result){
         result = FblBmHdrVerifyBmHeader(targetHandle, pBlockInfo);
      }
#endif

      if(result == FBLBMHDR_CHKHDR_OK){
         break;
      }
      pBlockInfo->logicalBlock = FblLbtBlockNext();
   }
   return result;
}

#if defined( FBLBM_ENABLE_SECURE_BOOT )
tFblResult FblBmHdrVerifyAreas(tFblBmHdrTargetHandle targetHandle
   ,  const V_MEMRAM1 tFblBmBlockInfo V_MEMRAM2 V_MEMRAM3 * pBlockInfo){
   tFblResult result;
   vuintx areaIndex;
   vuint8 mac[FBLSB_MAC_LENGTH];
   uint32 macId;

#if defined( FBLBMHDR_ENABLE_CUSTOM_VERIFY_AREAS )
   if(ApplFblBmHdrCustomVerifyAreasEnable(targetHandle) == kFblOk){
      result = ApplFblBmHdrCustomVerifyAreas(targetHandle, pBlockInfo);
   }
   else
#endif
   {
      for(areaIndex = 0u; areaIndex < pBlockInfo->bmHeader.bmVerificationListEntries; areaIndex++){
         result = ApplFblSbGetLogicalBlockMac(&pBlockInfo->logicalBlock, mac, FBLSB_MAC_LENGTH, areaIndex);
         if(result == kFblOk){
            macId = FblBmHdr_GetFblSbMacId(targetHandle);
            result = FblSb_MacVerify(macId, pBlockInfo->bmHeader.bmVerificationList[areaIndex].address
   ,           pBlockInfo->bmHeader.bmVerificationList[areaIndex].length, mac, FBLSB_MAC_LENGTH);
         }
         if(result != kFblOk){
            result = kFblFailed;
            break;
         }
      }
   }
   return result;
}
#endif

