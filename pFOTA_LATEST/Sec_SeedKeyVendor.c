

#include "Sec.hpp"

#include "SUPPLIER1_Seca.hpp"

#if( SECACCESS_HIS_VECTOR_VERSION != 0x0100u ) || \
    ( SECACCESS_HIS_VECTOR_RELEASE_VERSION != 0x00u )
# error "Error in SEC_SEEDKEYVENDOR.C: Source and header file are inconsistent!"
#endif

#if defined( SEC_BYTE_ARRAY_SEED ) || \
    defined( SEC_WORD_ARRAY_SEED )

#if defined( SEC_BYTE_ARRAY_KEY )
#if( SEC_SEED_LENGTH != SEC_KEY_LENGTH )
#   error "Only identical seed and key lengths (in bytes) are supported by the example code!"
#endif
#else
#error "Only a combination of array for both seed and key is supported by the example code!"
#endif
#else

#if defined( SEC_BYTE_ARRAY_KEY )
#error "Only a combination of array for both seed and key is supported by the example code!"
#else
#if( SEC_SEED_LENGTH != 4u ) && \
      ( SEC_SEED_LENGTH != 8u )
#   error "Only seed lengths (in bytes) of 4 or 8 are supported by the example code!"
#endif
#if( SEC_KEY_LENGTH != 4u )
#   error "Only a key length (in bytes) of 4 is supported by the example code!"
#endif
#endif
#endif

#if defined( SEC_ENABLE_SEED_KEY_ASYMMETRIC )

SecM_StatusType SecM_ComputeKeyVendor( SecM_KeyType inputKey, SecM_ConstType constant
   ,  V_MEMRAM1 SecM_SeedStorageType V_MEMRAM2 V_MEMRAM3 * computedSeed ){
   SecM_StatusType   result;
   SecM_ByteFastType seedIndex;
   V_MEMRAM1 SecM_SeedBaseType V_MEMRAM2 V_MEMRAM3 * seedOutput;
#if defined( SEC_BYTE_ARRAY_SEED )
   SecM_ByteType     byteConstant[SEC_WORD_TYPE_SIZE];
# elif defined( SEC_WORD_ARRAY_SEED )
   SecM_WordType     temp;
   SecM_ByteFastType keyIndex;
#endif

   result = SECM_OK;

   seedOutput  = *computedSeed;

#if defined( SEC_BYTE_ARRAY_SEED )

   SecM_SetInteger(SEC_INITIAL_SEED_LENGTH, constant, byteConstant);

   for(seedIndex = 0u; seedIndex < SEC_SEED_LENGTH; seedIndex++){
      seedOutput[seedIndex] = inputKey[seedIndex] ^ byteConstant[seedIndex & (SEC_WORD_TYPE_SIZE - 1u)];
   }
# elif defined( SEC_WORD_ARRAY_SEED )

   keyIndex    = 0u;

   for(seedIndex = 0u; seedIndex < SEC_SEED_WORD_LENGTH; seedIndex++){
      temp = SecM_GetInteger(SEC_WORD_TYPE_SIZE, &inputKey[keyIndex]);

      keyIndex += SEC_WORD_TYPE_SIZE;

      seedOutput[seedIndex] = temp ^ constant;
   }
#endif

   return result;
}
#else

SecM_StatusType SecM_ComputeKeyVendor( SecM_SeedType inputSeed, SecM_ConstType constant
   ,  V_MEMRAM1 SecM_KeyStorageType V_MEMRAM2 V_MEMRAM3 * computedKey ){
   SecM_StatusType   result;
#if defined( SEC_BYTE_ARRAY_KEY )
#if(SUPPLIER1_SECA_WITH_CMAC == STD_OFF)
   SecM_ByteFastType seedIndex;
#endif
   V_MEMRAM1 SecM_KeyBaseType V_MEMRAM2 V_MEMRAM3 * keyOutput;
#endif
#if defined( SEC_BYTE_ARRAY_SEED )
   SecM_ByteType     byteConstant[SEC_WORD_TYPE_SIZE];
# elif defined( SEC_WORD_ARRAY_SEED )
   SecM_WordType     temp;
   SecM_ByteFastType keyIndex;
#endif

   uint16 ucSizeKey;

   result = SECM_OK;

#if defined( SEC_BYTE_ARRAY_SEED )

   keyOutput   = *computedKey;

   SecM_SetInteger(SEC_INITIAL_SEED_LENGTH, constant, byteConstant);

#if(SUPPLIER1_SECA_WITH_CMAC == STD_ON)
   SECA_ComputeKeyFromSeed(inputSeed, SEC_SEED_LENGTH, keyOutput, SEC_KEY_LENGTH, &ucSizeKey);
#else

   for(seedIndex = 0u; seedIndex < SEC_SEED_LENGTH; seedIndex++){
      keyOutput[seedIndex] = inputSeed[seedIndex] ^ byteConstant[seedIndex & (SEC_WORD_TYPE_SIZE - 1u)];
   }
#endif

# elif defined( SEC_WORD_ARRAY_SEED )

   keyOutput   = *computedKey;

   keyIndex    = 0u;

   for(seedIndex = 0u; seedIndex < SEC_SEED_WORD_LENGTH; seedIndex++){
      temp = inputSeed[seedIndex] ^ constant;

      SecM_SetInteger(SEC_WORD_TYPE_SIZE, temp, &keyOutput[keyIndex]);

      keyIndex += SEC_WORD_TYPE_SIZE;
   }
#else

#if( SEC_SEED_LENGTH == 4u )

   *computedKey = inputSeed.seedX ^ constant;

#else

   *computedKey = inputSeed.seedX ^ inputSeed.seedY ^ constant;
#endif
#endif

   return result;
}
#endif

