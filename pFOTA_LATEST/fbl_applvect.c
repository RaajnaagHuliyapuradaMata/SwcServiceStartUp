

#include "v_cfg.hpp"
#if defined V_GEN_GENERATOR_MSR
#include "FblHal_Cfg.hpp"
#endif
#include "v_def.hpp"
#include "applvect.hpp"

#if( FBLVTABAPPL_RH850_VERSION != 0x0104 ) || \
    ( FBLVTABAPPL_RH850_RELEASE_VERSION != 0x00 )
# error "Error in applvect.c: Source and header file are inconsistent!"
#endif

#if defined( V_COMP_GHS ) || \
    defined( V_COMP_DIABDATA )
extern void _usr_init(void);
#define RESET_ENTRY_POINT (vuint32)_usr_init
#endif

#if defined( V_COMP_IAR )
extern void _iar_program_start(void);
#define RESET_ENTRY_POINT (vuint32)_iar_program_start
#endif

#if defined( V_COMP_RENESAS )
extern void _start(void);
#define RESET_ENTRY_POINT (vuint32)_start
#endif

#define FBL_APPLVECT_START_SEC_CONST
#include "MemMap.hpp"

V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 ApplIntJmpTable[2] = {APPLVECT_FROM_BOOT, RESET_ENTRY_POINT};

#define FBL_APPLVECT_STOP_SEC_CONST
#include "MemMap.hpp"

