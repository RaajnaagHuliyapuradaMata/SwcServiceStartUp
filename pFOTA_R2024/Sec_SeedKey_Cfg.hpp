

#ifndef __SEC_SEEDKEY_CFG_H__
#define __SEC_SEEDKEY_CFG_H__

#include "Std_Types.hpp"

#define SECACCESS_HIS_VECTOR_VERSION            0x0100u
#define SECACCESS_HIS_VECTOR_RELEASE_VERSION    0x00u

#define SECACCESS_API_REFERENCE_VERSION_MAJOR      0x01u

#define SECACCESS_API_REFERENCE_VERSION_MINOR      0x00u

#define SECACCESS_API_REFERENCE_VERSION_RELEASE    0x00u

#define SUPPLIER1_SECA_WITH_CMAC STD_ON

#if(SUPPLIER1_SECA_WITH_CMAC == STD_ON)

#define SEC_SEED_LENGTH       16u

#define SEC_KEY_LENGTH        16u

#else

#define SEC_SEED_LENGTH       4u

#define SEC_KEY_LENGTH        4u
#endif

#define SEC_BYTE_ARRAY_SEED

#define SEC_BYTE_ARRAY_KEY

#endif

