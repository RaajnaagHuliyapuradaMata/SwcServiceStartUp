

#ifndef FBL_HW_H
#define FBL_HW_H

#define FBLDRVCAN_RH850RSCANCRX_VERSION          0x0126u
#define FBLDRVCAN_RH850RSCANCRX_RELEASE_VERSION  0x01u

#if defined( FBL_USE_OWN_MEMCPY )
#else
#include <string.h>
#endif
#include "fbl_sfr.hpp"

#if defined( FBL_ENABLE_BUSTYPE_CAN )
# define FBLDRVCAN_REFERENCE_IMPLEMENTATION 0x0100u

#endif

#if defined( V_CPU_RH850 )

# if defined( FBL_USE_OWN_MEMCPY )
#  define MEMCPY(dst, src, len) \
          ownmemcpy((void *)(dst), (V_MEMRAM1_FAR void V_MEMRAM2_FAR V_MEMRAM3 const *)(src), (tFblLength)(len))
# else
#  define MEMCPY(dst, src, len) memcpy((void *)(dst), (V_MEMROM2 void *)(src), (size_t)(len))
# endif
#endif

#if defined( V_CPU_RH850 )

# define RESETVECT                         0x0u
# define APPLSTART                         (*((volatile vuint32 *)&ApplIntJmpTable[1u]))
# define FblCheckBootVectTableIsValid()    (((volatile vuint32*)ApplIntJmpTable)[0u] == APPLVECT_FROM_BOOT)

# define JSR(x) (*((void(*)(void))x))()

# define JSR_APPL()         JSR(APPLSTART)
# define JSR_RESET()        JSR(RESETVECT)

# define FblFlashAddressGet3Bytes(a)    (FBL_ADDR_TYPE)(((a)[0u] << 16u) + ((a)[1u] << 8u) + (a)[2u])
# define FblDownloadLengthGet3Bytes(a)  (FBL_MEMSIZE_TYPE)(((a)[0u] << 16u) + ((a)[1u] << 8u) + (a)[2u])

# define FblFlashAddressGet4Bytes(a)    (FBL_ADDR_TYPE)(((a)[0u] << 24u) + ((a)[1u] << 16u) + ((a)[2u] << 8u) + (a)[3u])
# define FblDownloadLengthGet4Bytes(a)  (FBL_MEMSIZE_TYPE)(((a)[0u] << 24u) + ((a)[1u] << 16u) + ((a)[2u] << 8u) + (a)[3u])

#  define FblHwRestoreFblContext()        { \
                                              \
                                             __asm(" .extern __tp "); \
                                             __asm(" .extern __gp "); \
                                              \
                                             __asm(" movhi hi(__gp),zero,gp"); \
                                             __asm(" movea lo(__gp),gp,gp"); \
                                              \
                                             __asm(" movhi hi(__tp),zero,tp"); \
                                             __asm(" movea lo(__tp),tp,tp"); \
                                          }

#  define FblTimerStopp()              FBL_TAUX0TT |= 0x0007u;
#  define FblTimerGet()                ((FBL_ICTAUX0I0 & 0x1000u) == 0x1000u)
#  define FblTimerReset()              FBL_ICTAUX0I0 &= (vuint16)~0x1000u

# if defined( V_COMP_RENESAS )
#  define FblInterruptDisable()        __DI()
#  define FblInterruptEnable()         __EI()
# else
#  define FblInterruptDisable()        __asm("  di")
#  define FblInterruptEnable()         __asm("  ei")
# endif

# define FblBootProtect()
#endif

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

void FblTimerInit( void );

#define FBLHW_START_SEC_CODE
#include "MemMap.hpp"
#if defined( V_CPU_RH850 )
vuint16 FblGetTimerValue( void );
#endif
#define FBLHW_STOP_SEC_CODE
#include "MemMap.hpp"

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

vuint8 FblReadByte( FBL_ADDR_TYPE address );
FBL_MEMSIZE_TYPE FblReadBlock( FBL_ADDR_TYPE address, vuint8 * buffer, FBL_MEMSIZE_TYPE length );
#if defined( FBL_USE_OWN_MEMCPY )
#  define MEMCPY_START_SEC_CODE
#  include "MemMap.hpp"
void * ownmemcpy(void * dest, V_MEMRAM1_FAR void V_MEMRAM2_FAR V_MEMRAM3 const * source, tFblLength size);
#  define MEMCPY_STOP_SEC_CODE
#  include "MemMap.hpp"
#endif

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

#endif

