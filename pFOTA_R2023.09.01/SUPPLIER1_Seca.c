#include "aes.hpp"

#include "SUPPLIER1_Seca.hpp"
#include "EcuabFee_FblBlockInterface.hpp"
#include "SecM.hpp"
#include "fbl_inc.hpp"

static uint8 aucSeed[16];
static uint8 aucKey[16];
static uint8 aucCalculatedKeyReprogramming[16];
static uint8 ucSecaLevel03 = c_Seca_Locked;

uint8 SECA_Level03_GetSecurityLock(void){
	uint8 i;
	uint16 KeyLen_16 = 16;

	ucSecaLevel03 = c_Seca_Unlocked;

	for(i = 0; i < KeyLen_16; i++)
	{
		if(aucCalculatedKeyReprogramming[i] != (uint8)(*(aucKey + i)))
		{
			ucSecaLevel03 = c_Seca_Locked;
		}
	}

	return ucSecaLevel03;
}

void SECA_Level03_SetSecurityLock(void){
  ucSecaLevel03 = c_Seca_Locked;
}

uint8 SECA_Level03_ProcessRequestSeed(void){
  uint8 ucResult;

  if(ApplFblSecuritySeed() == kFblOk){
    ucSecaLevel03 = c_Seca_WaitForKey;
    ucResult = kFblOk;
  }
  else{
    DiagNRCConditionsNotCorrect();
    ucResult = kFblFailed;
  }

  return ucResult;
}

uint8 SECA_Level03_ProcessSendKey(uint8* pucDiagData){
  uint8 ucResult;

  if(ucSecaLevel03 != c_Seca_WaitForKey){
    ucResult = 0x01;
  }
  else{
    if(ApplFblSecurityKey() != kFblOk){
      ucSecaLevel03 = c_Seca_Locked;
      ucResult = 0x02;
    }

    else{
      ucSecaLevel03 = c_Seca_Unlocked;
      ucResult = kFblOk;
    }
  }

  return ucResult;
}

void SECA_ComputeKeyFromSeed(uint8* seed, uint16 sizeSeed, uint8* key, uint16 maxSizeKey, uint16* sizeKey){
#if(SEED_KEY_ALGORITHM==SEED_KEY_USE_HMAC_SHA256)
  uint8 aucSecretKey[16];

  if(ucSecaLevel03 == c_Seca_WaitForKey){
    FEEFBL_GetUdsAppKey(aucSecretKey);
  }
  else{
    FEEFBL_GetUdsBootKey(aucSecretKey);
  }

  hmac_sha256(aucSecretKey, maxSizeKey, (const uint8*)seed, sizeSeed, key, maxSizeKey);

  *sizeKey= maxSizeKey;
#elif(SEED_KEY_ALGORITHM==SEED_KEY_USE_AES256_CBC)
	
	struct AES_ctx tAesInput;
	uint8 aucVector[16];
	uint8 aucSymKey[32];

	
	
	FEEFBL_GetInitialVector(aucVector);
	FEEFBL_GetSymmetricKey(aucSymKey);

	FEEFBL_GetSymmetricKey(aucSymKey);

	if(sizeof(aucSeed) >= SEC_SEED_LENGTH)
	{
		MEMCPY(aucSeed, seed, SEC_SEED_LENGTH);
	}

	
	AES_init_ctx_iv(&tAesInput, aucSymKey, aucVector);
	AES_CBC_encrypt_buffer(&tAesInput, aucSeed, sizeof(aucSeed));

	if(sizeof(aucCalculatedKeyReprogramming) >= SEC_SEED_LENGTH)
	{
		MEMCPY(aucCalculatedKeyReprogramming, aucSeed, SEC_SEED_LENGTH);
		MEMCPY(key, aucSeed, SEC_SEED_LENGTH);
	}
#endif
}

#if 0

void SECA_MakeBackwardCompartibleToVers010205(void){
#define MAX_NUM_OF_FF_ALLOWED_FOR_BACKWARD_COMP 24
	static const uint8 aucSymmetricKey[32] = { 0xf6, 0x81, 0x0c, 0xe9, 0x9f, 0xc6, 0x7d, 0x89
   ,  										   0x0d, 0x97, 0xad, 0xcb, 0x8b, 0x18, 0x7e, 0x81
   ,  										   0xdf, 0x59, 0x06, 0x0d, 0xf4, 0xce, 0x4b, 0xd2
   ,  										   0xf5, 0x61, 0x95, 0x58, 0x7d, 0x49, 0x87, 0x75 };
	static const uint8 aucInitialVector[16] = { 0x48, 0x75, 0x33, 0x57, 0x86, 0x22, 0x47, 0xb1
   ,  										   0x20, 0xed, 0xe3, 0x7e, 0x0e, 0x74, 0x72, 0x6a };
	uint8 aucVector[kEepSizeSecKey_AES_INITIAL_VECTOR];
	uint8 aucSymKey[kEepSizeSecKey_AES_SYMMETRIC_KEY];
	uint8 num_of_0xff = 0;
	uint8 i;
	boolean bIV_identical = TRUE;

	FEEFBL_GetInitialVector(aucVector);
	FEEFBL_GetSymmetricKey(aucSymKey);

	for(i = 0; i < kEepSizeSecKey_AES_INITIAL_VECTOR; i++)
	{
		if(aucVector[i] != aucInitialVector[i])
		{
			bIV_identical = FALSE;
		}
	}

	if(bIV_identical)
	{
		FEEFBL_PutAesSymmetricKey((const uint8*)aucSymmetricKey);
	}
}
#endif

