

#ifndef __APPL_VECT_H__
#define __APPL_VECT_H__

#define FBLVTABAPPL_RH850_VERSION          0x0104
#define FBLVTABAPPL_RH850_RELEASE_VERSION  0x00

#define APPLVECT_FROM_BOOT       0xA5000000UL

#define APPLVECT_FROM_APPL       0xAA000000UL

#define FBL_APPLVECT_START_SEC_CONST
#include "MemMap.hpp"

V_MEMROM0 extern V_MEMROM1 vuint32 V_MEMROM2 ApplIntJmpTable[2];

#define FBL_APPLVECT_STOP_SEC_CONST
#include "MemMap.hpp"

#endif

