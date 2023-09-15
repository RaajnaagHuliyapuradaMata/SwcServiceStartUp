#ifndef SECA_SUPPLIER1_H
#define SECA_SUPPLIER1_H

#include "BrsTypes.hpp"
#include "hmac_sha2.hpp"

#define c_Seca_Locked     0x00
#define c_Seca_WaitForKey 0x01
#define c_Seca_Unlocked   0x02

#define SECA_LEVEL_APPLICATION  3
#define SECA_LEVEL_PROGRAMMING  5

extern uint8 SECA_Level03_GetSecurityLock(void);
extern void SECA_Level03_SetSecurityLock(void);
extern void SECA_ComputeKeyFromSeed(uint8* seed, uint16 sizeSeed, uint8* key, uint16 maxSizeKey, uint16* sizeKey);
extern uint8 SECA_Level03_ProcessRequestSeed(void);
extern uint8 SECA_Level03_ProcessSendKey(uint8* pucDiagData);

#endif
