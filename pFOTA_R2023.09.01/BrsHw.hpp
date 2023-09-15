#ifndef _BRSHW_H_
#define _BRSHW_H_

#if !defined (BRS_COMP_GHS)
#define BRS_COMP_GHS
#endif
#if !defined (BRS_DERIVATIVE_701018)
#define BRS_DERIVATIVE_701018
#endif
#if !defined (BRS_OSC_CLK)
#ifdef _RST_VS_EDITOR_SUPPORT_
#define BRS_OSC_CLK 16
#else
#define BRS_OSC_CLK	8
#endif
#endif
#if !defined (BRS_TIMEBASE_CLOCK)
#define BRS_TIMEBASE_CLOCK	80
#endif

#include "BrsHw_DerivativeList.hpp"

#include "BrsCfg.hpp"

#if !defined (BASIC_RUNTIME_SYSTEM_TYPE_MSR4)

#include "v_cfg.hpp"

#include "BrsTypes.hpp"
#else

#include "Std_Types.hpp"
#endif

#define BRSHW_SOURCECODE_TEMPLATE_VERSION        0x0202u
#define BRSHW_SOURCECODE_TEMPLATE_BUGFIX_VERSION 0x00u

#define BRSHW_VERSION        0x0204u
#define BRSHW_BUGFIX_VERSION 0x19u

#define BRSHW_IOS(type, address) (*((volatile type *)(address)))

#if defined (BRS_COMP_GHS)
#define ___asm(c)               __asm_(c)
#define __asm_(c)               asm(" "#c);
#define __as1(c, d)             __as1_(c, d)
#define __as1_(c, d)            asm(" "#c " , "#d);
#define __as2(c, d, e)          __as2_(c, d, e)
#define __as2_(c, d, e)         asm(" "#c " , "#d " , "#e);
#define BRS_ISR_BASE_ENTRY(x)   ___asm(jr x)
#define BRS_ISR_ALIGNMENT       ___asm(nop)___asm(nop)___asm(nop)___asm(nop)___asm(nop)___asm(nop)
#define BRS_ISR_ENTRY(x)        ___asm(.word x)
#define BRS_ISR_KEYWORD         __interrupt
#define BRS_ISR_DEFINE(x)       _##x

#else
#error: "Compiler not yet supported"
#endif

#if !defined (BRS_ENABLE_FBL_SUPPORT)
#error "Configured OS_USECASE is not supported (Organi filtered because of ALM attributes or wrong set within Makefile.config)"
#endif

extern uint8 const kBrsHwMainVersion;
extern uint8 const kBrsHwSubVersion;
extern uint8 const kBrsHwBugfixVersion;

#define BRSHW_PREINIT_AVAILABLE
void BrsHwPreInitPowerOn(void);

void BrsHwWatchdogInitPowerOn(void);

void BrsHwPllInitPowerOn(void);

#if !defined (VGEN_ENABLE_DRVPORT)
#if defined (BRS_ENABLE_TCM_SUPPORT)

void BrsHw_WriteDio_TCM_CLK_OUT(uint8 Level);
void BrsHw_WriteDio_TCM_SDA_OUT(uint8 Level);
uint8 BrsHw_ReadDio_TCM_CLK_IN(void);
uint8 BrsHw_ReadDio_TCM_SDA_IN(void);
#endif
#endif

void BrsHwPortInitPowerOn(void);

#define BrsHwEvaBoardInitPowerOn()

void BrsHwDisableInterruptAtPowerOn(void);

void BrsHwEnableInterruptAtPowerOn(void);

void BrsHwDisableInterrupt(void);

void BrsHwRestoreInterrupt(void);

void BrsHwSoftwareResetECU(void);

#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
typedef enum{
  BRSHW_TOGGLEPIN_LED
   ,  BRSHW_TOGGLEPIN_WD
   ,  BRSHW_TOGGLEPIN_CUSTOM
}brsHw_TogglePin;

#if defined (BRS_ENABLE_SUPPORT_LEDS)

#define BRSHW_LED_SYSTEM_OK 0

#define BrsHwSetLed(x,y) BrsHwTogglePin(BRSHW_TOGGLEPIN_LED)
#endif

#if defined (BRS_ENABLE_FBL_SUPPORT)
#define BRS_START_SEC_RAM_CODE
#include "Brs_MemMap.hpp"
#endif

void BrsHwTogglePin(brsHw_TogglePin Pin);

#if defined (BRS_ENABLE_FBL_SUPPORT)
#define BRS_STOP_SEC_RAM_CODE
#include "Brs_MemMap.hpp"
#endif
#endif

void BrsHwTime100NOP(void);

#if defined (BRSASR_ENABLE_SAFECTXSUPPORT)

void BrsHw_EnableHwAccess(void);
#endif

#if defined (BRS_ENABLE_FBL_SUPPORT)
#define BRSHW_VOLTAGE_FOR_FLASH_PROGRAMMING_AVAILABLE

void BrsHwSetVfp(void);

void BrsHwResetVfp(void);
#endif

#endif
