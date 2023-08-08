

#include "BrsHw.hpp"

#if defined (VGEN_ENABLE_CAN_DRV)
# if defined (VGEN_ENABLE_IF_ASRIFCAN)

  #include "McalCan.hpp"
# else

  #include "can_inc.hpp"
# endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
# if defined (VGEN_ENABLE_IF_ASRIFLIN)

  #include "Lin.hpp"
# else

  #include "lin_api.hpp"
  #include "sio_cfg.hpp"
# endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
  #include "Fr.hpp"
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
  #include "Eth.hpp"
#endif

#if defined (BRS_COMP_GHS)
#else
  #error "Unknown compiler specified!"
#endif

#if defined (VGEN_ENABLE_CAN_DRV) && defined (C_ENABLE_DIRECT_INTERRUPT_BRANCH)
  #error "Only table based interrupt branching is supported by BRS"
#endif

#if defined (BRS_COMP_GHS)
#if defined (BRS_ENABLE_FBL_SUPPORT)
  ___asm(.global __usr_init)
  #define _BrsHW_core_exception_handler __usr_init
#endif

___asm(.extern __usr_init)

# if defined (BRS_COMP_GHS)
___asm(.align 4)
__as1(.section .intvect,.text)
# endif

___asm(;)
___asm(;)

___asm(.globl Vector_0x00)
___asm(Vector_0x00:)
    BRS_ISR_BASE_ENTRY(__usr_init)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x10)
___asm(Vector_0x10:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x20)
___asm(Vector_0x20:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x30)
___asm(Vector_0x30:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x40)
___asm(Vector_0x40:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x50)
___asm(Vector_0x50:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x60)
___asm(Vector_0x60:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x70)
___asm(Vector_0x70:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x80)
___asm(Vector_0x80:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x90)
___asm(Vector_0x90:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0xA0)
___asm(Vector_0xA0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0xB0)
___asm(Vector_0xB0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0xC0)
___asm(Vector_0xC0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0xD0)
___asm(Vector_0xD0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0xE0)
___asm(Vector_0xE0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0xF0)
___asm(Vector_0xF0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x100)
___asm(Vector_0x100:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x110)
___asm(Vector_0x110:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x120)
___asm(Vector_0x120:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x130)
___asm(Vector_0x130:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x140)
___asm(Vector_0x140:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x150)
___asm(Vector_0x150:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x160)
___asm(Vector_0x160:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x170)
___asm(Vector_0x170:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x180)
___asm(Vector_0x180:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x190)
___asm(Vector_0x190:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x1A0)
___asm(Vector_0x1A0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x1B0)
___asm(Vector_0x1B0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x1C0)
___asm(Vector_0x1C0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x1D0)
___asm(Vector_0x1D0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x1E0)
___asm(Vector_0x1E0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT

___asm(.globl Vector_0x1F0)
___asm(Vector_0x1F0:)
    BRS_ISR_BASE_ENTRY(_BrsHW_core_exception_handler)
    BRS_ISR_ALIGNMENT
#endif

