

#include "fbl_inc.hpp"

#define FBLVTAB_RH850_VERSION           0x0103
#define FBLVTAB_RH850_RELEASE_VERSION   0x03

#if(FBLVTAB_RH850_VERSION != _FBLVTAB_HW_VERSION) ||\
    (FBLVTAB_RH850_RELEASE_VERSION != _FBLVTAB_HW_RELEASE_VERSION)
# error "Error in FBL_VECT.C: Source and V_VER.H are inconsistent!"
#endif

#if defined(V_COMP_DIABDATA_RH850)
# define ___asm(c)               __asm_(c)
# define __asm_(c)               asm(" " #c);
# define __as1(c, d)             __as1_(c, d)
# define __as1_(c, d)            asm(" " #c " , " #d);
# define __as2(c, d, e)          __as2_(c, d, e)
# define __as2_(c, d, e)         asm(" " #c " , " #d " , " #e);
# define lp                      r31
# define FBL_ISR_BASE_ENTRY(x)   ___asm(jr x)
# define FBL_ISR_SYNCP           ___asm(syncp)
# define FBL_ISR_ALIGNMENT       ___asm(.alignn 16)

# define FBL_ISR_ENTRY(x)        ___asm(.word x)
# define FBL_ISR_KEYWORD         __interrupt__
#elif defined(V_COMP_GHS_RH850) ||\
      defined(V_COMP_IAR_RH850)
# define ___asm(c)               __asm_(c)
# define __asm_(c)               asm(" " #c);
# define __as1(c, d)             __as1_(c, d)
# define __as1_(c, d)            asm(" " #c " , " #d);
# define __as2(c, d, e)          __as2_(c, d, e)
# define __as2_(c, d, e)         asm(" " #c " , " #d " , " #e);
# define FBL_ISR_BASE_ENTRY(x)   ___asm(jr x)
# define FBL_ISR_SYNCP           ___asm(syncp)
# define FBL_ISR_ALIGNMENT       ___asm(.align 16)
# define FBL_ISR_ENTRY(x)        ___asm(.word x)
# define FBL_ISR_KEYWORD         __interrupt
#endif

#if defined (V_COMP_GHS_RH850)
___asm(.align 512)
__as1(.section ".intvect",.text)
#elif defined (V_COMP_DIABDATA_RH850)
___asm(.section .intvect)
___asm(.alignn 512)
#endif

___asm(_reset:)
___asm(.globl _reset)

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)
   FBL_ISR_ALIGNMENT

   FBL_ISR_SYNCP
   FBL_ISR_BASE_ENTRY(__usr_init)

