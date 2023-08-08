

#include "fbl_inc.hpp"

#if(FBLDRVCAN_RH850RSCANCRX_VERSION != 0x0126u) || \
    (FBLDRVCAN_RH850RSCANCRX_RELEASE_VERSION != 0x01u)
# error "Error in fbl_hw.c: Source and Header file are inconsistent!"
#endif
#if(FBLDRVCAN_RH850RSCANCRX_VERSION != _FBLDRVCAN_VERSION) || \
    (FBLDRVCAN_RH850RSCANCRX_RELEASE_VERSION != _FBLDRVCAN_RELEASE_VERSION)
# error "Error in fbl_hw.c: Source and v_ver.h are inconsistent!"
#endif

#if(FBL_SFR_VERSION != FBLDRVCAN_RH850RSCANCRX_VERSION)
# error "Check fbl_sfr.h version"
#endif

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

void FblTimerInit( void ){
#if defined( V_CPU_RH850 )

   FBL_TAUX0TT    = 0x0007u;

   FBL_TAUX0CMOR0 = 0x0801u;
   FBL_TAUX0CMOR1 = 0x3006u;
   FBL_TAUX0CMOR2 = 0x4000u;

   FBL_TAUX0CMUR0 = 0x00u;
   FBL_TAUX0CMUR1 = 0x00u;
   FBL_TAUX0CMUR2 = 0x00u;

   FBL_TAUX0RDE   = 0x0003u;
   FBL_TAUX0RDS   = 0x0000u;
   FBL_TAUX0RDC   = 0x0000u;
   FBL_TAUX0RDM   = 0x0000u;

   FBL_TAUX0TPS   = 0xFF00u | ((vuint16)FBL_TIMER_PRESCALER_VALUE);

   FBL_TAUX0CDR0  = FBL_TIMER_RELOAD_VALUE;
   FBL_TAUX0CDR1  = 0xFFFFu;
   FBL_TAUX0CDR2  = 0xFFFFu;

   FBL_TAUX0TS    = 0x0007u;
#endif
}

#define FBLHW_START_SEC_CODE
#include "MemMap.hpp"

#if defined( V_CPU_RH850 )

vuint16 FblGetTimerValue(void){
   return FBL_TAUX0CNT2;
}
#endif

#define FBLHW_STOP_SEC_CODE
#include "MemMap.hpp"

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

vuint8 FblReadByte( FBL_ADDR_TYPE address ){
   return *(V_MEMROM1_FAR vuint8 V_MEMROM2_FAR V_MEMROM3 *)address;
}

FBL_MEMSIZE_TYPE FblReadBlock( FBL_ADDR_TYPE address, vuint8 * buffer, FBL_MEMSIZE_TYPE length ){
   (void)MEMCPY (buffer, address, length);
   return length;
}

#if defined( FBL_USE_OWN_MEMCPY )
# define MEMCPY_START_SEC_CODE
# include "MemMap.hpp"

void * ownmemcpy(void * dest, V_MEMRAM1_FAR void V_MEMRAM2_FAR V_MEMRAM3 const * source, tFblLength size){
   tFblLength i;
   vuint8 * sd = (vuint8 *)dest;
# if defined( V_CPU_RH850 )
   vuint8 const * ss = (vuint8 const *)source;
# endif

   (void)FblLookForWatchdog();

   for(i = 0u; i < size; i++){
      if((i & (tFblLength)0x0Fu) == 0x00u)
      {
         (void)FblLookForWatchdog();
      }

# if defined( V_CPU_RH850 )
      sd[i] = ss[i];
# endif
   }

   return dest;
}
# define MEMCPY_STOP_SEC_CODE
# include "MemMap.hpp"
#endif

