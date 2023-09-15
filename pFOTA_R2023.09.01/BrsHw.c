#include "BrsHw.hpp"

#if defined (VGEN_ENABLE_CAN_DRV)
#if defined (VGEN_ENABLE_IF_ASRIFCAN)

#include "McalCan.hpp"

#include "v_def.hpp"
#include "fbl_sfr.hpp"
#else

#include "can_inc.hpp"
#endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
#if defined (VGEN_ENABLE_IF_ASRIFLIN)

#include "Lin.hpp"
#else

#include "lin_api.hpp"
#include "sio_cfg.hpp"
#endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
#include "Fr.hpp"
#if !defined (FR_CHANNEL_A_USED) && !defined (FR_CHANNEL_B_USED)
#error "Could not detect DrvFr channel configuration automatically. Please define here manually, which channel is used within your configuration."*/

#endif
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
#include "Eth.hpp"
#endif

#if !defined (BRS_ENABLE_FBL_SUPPORT)

#include "BrsMain.hpp"
#endif

#if !defined (VGEN_ENABLE_DRVPORT)
#include "BrsHw_Ports.hpp"
#endif

#if defined (VGEN_ENABLE_DRVDIO)
#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
#include "Dio.hpp"
#if defined (VGEN_ENABLE_DRVPORT)
#define BRSHW_PORT_LOGIC_HIGH STD_HIGH
#define BRSHW_PORT_LOGIC_LOW STD_LOW
#else
#error "LED alive mechanism and MCAL does only work proper if DrvPort and DrvDio are used together!"
#endif
#endif
#else
#if defined (VGEN_ENABLE_DRVPORT)
#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
      defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
      defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
#error "LED alive mechanism and MCAL does only work proper if DrvPort and DrvDio are used together!"
#endif
#endif
#endif

#if(BRSHW_VERSION != 0x0204u)
#error "Header and source file are inconsistent!"
#endif
#if(BRSHW_BUGFIX_VERSION != 0x19u)
#error "Different versions of bugfix in Header and Source used!"
#endif

#if defined (BRS_COMP_GHS)
#else
#error "Unknown compiler specified!"
#endif

#define BRSHWNOP10() ___asm(nop);___asm(nop);___asm(nop);___asm(nop);___asm(nop);___asm(nop);___asm(nop);___asm(nop);___asm(nop);___asm(nop)

#if defined (BRSHW_PROTECTION_GROUP_A)
#define PROTCMD0    BRSHW_IOS(uint32 , 0xFFF80000)
#define PROTCMD1    BRSHW_IOS(uint32 , 0xFFF88000)
#define PROTCMDD1   BRSHW_IOS(uint32 , 0xFFF87000)
#define PROTCMDMRST BRSHW_IOS(uint32 , 0xFFF8F480)

#elif defined (BRSHW_PROTECTION_GROUP_B)
#define PROTCMD1    BRSHW_IOS(uint32 , 0xFFF8B000)

#elif defined (BRSHW_PROTECTION_GROUP_NONE)

#else
#error "Unknown BRSHW_PROTECTION_GROUP configured. Check BrsHw_DerivativeList.h for your Derivative."
#endif

#define PROT_WRITEX(reg,val) (reg)=(uint32)(val);               \
                             (reg)=(uint32)(~(val));   \
                             (reg)=(uint32)(val);

#define PROT_WRITE0(reg,val) PROTCMD0=0xa5;     \
                             PROT_WRITEX(reg,val)

#define PROT_WRITE1(reg,val) PROTCMD1=0xa5;     \
                             PROT_WRITEX(reg,val)

#define PROT_WRITE2(reg,val) PROTCMD2=0xa5;     \
                             PROT_WRITEX(reg,val)

#define PROT_WRITE3(reg,val) PROTCMDD1=0xa5;   \
                             PROT_WRITEX(reg,val)

#define PROT_WRITE4(reg,val) PROTCMDMRST=0xa5;   \
                             PROT_WRITEX(reg,val)

#if defined (BRS_ENABLE_FBL_SUPPORT)
#define FLMDPCMD BRSHW_IOS(uint32 , 0xFFA00004)
#define FLMDPS   BRSHW_IOS(uint32 , 0XFFA00008)
#define FLMDCNT  BRSHW_IOS(uint32 , 0xFFA00000)

#define PROT_WRITE_VFP(reg,val) FLMDPCMD=0xa5;  \
                                PROT_WRITEX(reg,val)
#endif

#if defined (VGEN_ENABLE_CAN_DRV)
#if defined (VGEN_ENABLE_IF_ASRIFCAN)
#if(CAN_INTLOCK == CAN_APPL)
#define C_INT_BY_APPL
#endif
#else
#if defined (C_ENABLE_OSEK_CAN_INTCTRL)
#define C_INT_BY_APPL
#endif
#endif
#endif

uint8 const kBrsHwMainVersion   = (uint8)(BRSHW_VERSION >> 8);
uint8 const kBrsHwSubVersion    = (uint8)(BRSHW_VERSION & 0xFF);
uint8 const kBrsHwBugfixVersion = (uint8)(BRSHW_BUGFIX_VERSION);

static uint8 bBrsHwIntDiCounter;

volatile uint32 bBrsHwRegisterPSW;

#if defined (BRSHW_PLL_GROUP_A) || defined (BRSHW_PLL_GROUP_A1) || defined (BRSHW_PLL_GROUP_A2) || \
    defined (BRSHW_PLL_GROUP_A3)|| defined (BRSHW_PLL_GROUP_A4)
#define PLL_BASE_ADDRESS  0xFFF89000

#define PLLE0      BRSHW_IOS(uint32, PLL_BASE_ADDRESS)
#define PLLS0      BRSHW_IOS(uint32, PLL_BASE_ADDRESS + 0x04)
#define PLLC0      BRSHW_IOS(uint32, PLL_BASE_ADDRESS + 0x08)

#if defined (BRSHW_PLL_GROUP_A1) || defined (BRSHW_PLL_GROUP_A2) || defined (BRSHW_PLL_GROUP_A4)
#define PLLE1    BRSHW_IOS(uint32, PLL_BASE_ADDRESS + 0x100)
#define PLLS1    BRSHW_IOS(uint32, PLL_BASE_ADDRESS + 0x104)
#define PLLC1    BRSHW_IOS(uint32, PLL_BASE_ADDRESS + 0x108)
#endif
#if defined (BRSHW_PLL_GROUP_A2)
#define PLL1CLK   480
#define PLLFIXCLK PLL1CLK
#endif

#elif defined (BRSHW_PLL_GROUP_B) || \
      defined (BRSHW_PLL_GROUP_B1)
#if !(BRS_TIMEBASE_CLOCK==160)
#error "The selected CPU frequency is not supported for your derivative (please choose 160 MHz)."
#endif
#if !(BRS_OSC_CLK==16)
#error "The selected clock frequency of main oscillator is not support (supported: 16 MHz only)."
#endif

#define CLK_HSB 80

#define BRSHW_TIMER_CLK  CLK_HSB

#elif defined (BRSHW_PLL_GROUP_C)
#if !((BRS_TIMEBASE_CLOCK == BRSHW_CPU_MAX_FREQUENCY) || (BRS_TIMEBASE_CLOCK == BRSHW_CPU_MAX_FREQUENCY/2) || (BRS_TIMEBASE_CLOCK == BRSHW_CPU_MAX_FREQUENCY/4))
#error "The selected CPU frequency is not supported for your derivative (please choose BRSHW_CPU_MAX_FREQUENCY devided by 1, 2 or 4 )."
#endif
#if !(BRS_OSC_CLK == 20)
#error "The selected clock frequency of main oscillator is not support (supported: 20 MHz only)."
#endif

#define CLKC_LSB 40
#define CLKC_HSB 80

#if defined (BRSHW_TIMER_GROUP_B)
#define BRSHW_TIMER_CLK  CLKC_LSB
#else
#define BRSHW_TIMER_CLK  CLKC_HSB
#endif

#define PLL0CLKS   BRSHW_IOS(uint32, 0xFFF88004)
#define PLL0CLKC1  BRSHW_IOS(uint32, 0xFFF88200)

#elif defined (BRSHW_PLL_GROUP_D)

#define OPBT1     BRSHW_IOS(uint32, 0xFFCD0034)

#if(BRS_TIMEBASE_CLOCK!=240) || ((BRS_OSC_CLK!=16)&&(BRS_OSC_CLK!=24))
#error "BrsHw was verified successful with Oscillator=16MHz|24MHz and Cpu-Frequency=240MHz only. Renesas verified, that other frequencies cause errors on v1 versions of this chip."
#endif

#if(BRS_TIMEBASE_CLOCK==240)
#define BRSHW_CLKD0DIV 0x01
#define BRSHW_TIMER_CLK  80
#define BRSHW_CLKD1DIV 0x01
# elif(BRS_TIMEBASE_CLOCK==160)
#define BRSHW_CLKD0DIV 0x02
#define BRSHW_TIMER_CLK  80
#define BRSHW_CLKD1DIV 0x02
# elif(BRS_TIMEBASE_CLOCK==80)
#define BRSHW_CLKD0DIV 0x04
#define BRSHW_TIMER_CLK  40
#define BRSHW_CLKD1DIV 0x04
#else
#error "The selected CPU clock is not yet supported by this BrsHw implemention. For assumed OPBT1.PLL0FREQ=2, 240,160 or 80 MHz are supported."
#endif

#elif defined (BRSHW_PLL_GROUP_F)

#define OPBT1     BRSHW_IOS(uint32, 0xFFCD0034)
#define OPBT0     BRSHW_IOS(uint32, 0xFFCD0030)

#if(BRS_TIMEBASE_CLOCK!=120) || ((BRS_OSC_CLK!=16) && (BRS_OSC_CLK!=20) && (BRS_OSC_CLK!=24))
#error "The supported Oscillator-Frequency=16||20||24MHz and Cpu-Frequency=120MHz only."
#endif

#if(BRS_TIMEBASE_CLOCK==120)
#define BRSHW_CLKD0DIV 0x01
#define BRSHW_TIMER_CLK  40
#define BRSHW_CLKD1DIV 0x01
#else
#error "The selected CPU clock is not yet supported by this BrsHw implemention. For assumed OPBT1.PLL0FREQ=2, 240,160 or 80 MHz are supported."
#endif

#else
#error "Unknown BRSHW_PLL_GROUP configured. Check BrsHw_DerivativeList.h for your Derivative."
#endif

#if defined (BRSHW_CLOCK_GROUP_A) || defined (BRSHW_CLOCK_GROUP_A1) || defined (BRSHW_CLOCK_GROUP_A2)
#define CLOCK_BASE_ADDRESS    0xFFF81000

#define MOSCE      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x100)
#define MOSCS      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x104)
#define MOSCC      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x108)
#define MOSCST     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x10C)

#define SOSCE      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x200)
#define SOSCS      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x204)
#define SOSCST     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x20C)

#define ROSCE      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS        )
#define ROSCS      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x04 )

#define CKSC_CPUCLKS_CTL   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9000)
#define CKSC_CPUCLKS_ACT   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9008)
#define CKSC_CPUCLKD_CTL   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9100)
#define CKSC_CPUCLKD_ACT   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9108)

#if defined (BRSHW_CLOCK_GROUP_A2)
#define CKSC_PPLLCLKS_CTL  BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9010)
#define CKSC_PPLLCLKS_ACT  BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9018)
#endif

#if defined (BRSHW_CLOCK_GROUP_A1)
#define CKSC_IPPL0S_CTL      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x8200)
#define CKSC_IPPL0S_ACT      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x8208)
#define CKSC_IPPL1S_CTL      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x8300)
#define CKSC_IPPL1S_ACT      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x8308)
#define CKDV_ICLKJITD_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x43C0)
#define CKDV_ICLKJITD_STAT   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x43C4)
#define CKSC_ICLKJITS_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4400)
#define CKSC_ICLKJITS_ACT    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4408)
#define CKDV_ICLKFIXD_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4700)
#define CKDV_ICLKFIXD_STAT   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4704)
#define CKSC_ICLKFIXS_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4740)
#define CKSC_ICLKFIXS_ACT    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4748)
#define CKSC_IRSCAND_CTL     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4780)
#define CKSC_IRSCAND_ACT     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4788)
#define CKSC_IRSCANXINS_CTL  BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4800)
#define CKSC_IRSCANXINS_ACT  BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4808)
#define CKSC_IRLINS_CTL      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4500)
#define CKSC_IRLINS_ACT      BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4508)
#define CKSC_IPCRSCANS_CTL   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4140)
#define CKSC_IPCRSCANS_ACT   BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4148)
#define CKSC_ICLKFIXS_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4740)
#define CKSC_ICLKFIXS_ACT    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4748)
#define CKSC_ITAUB01S_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4740)
#define CKSC_ITAUB01S_ACT    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4748)
#define CKSC_IXCCLKS_CTL     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4180)
#define CKSC_IXCCLKS_ACT     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4188)
#define CKSC_IXCETNBS_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x41C0)
#define CKSC_IXCETNBS_ACT    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x41C8)
#define CKSC_IPCETNBS_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4280)
#define CKSC_IPCETNBS_ACT    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x4288)

#define MRSTC                BRSHW_IOS(uint32, 0xFFF8F400)

#else
#define CKSC_ICANOSCD_CTL    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9A00)
#define CKSC_ICANOSCD_ACT    BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9A08)
#define CKSC_ICANS_CTL       BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9900)
#define CKSC_ICANS_ACT       BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9908)
#define CKSC_ILIND_CTL       BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9800)
#define CKSC_ILIND_ACT       BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9808)
#define CKSC_ILINS_CTL       BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9400)
#define CKSC_ILINS_ACT       BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9408)
#define CKSC_IPERI1S_CTL     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9200)
#define CKSC_IPERI1S_ACT     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9208)
#define CKSC_IPERI2S_CTL     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9300)
#define CKSC_IPERI2S_ACT     BRSHW_IOS(uint32, CLOCK_BASE_ADDRESS + 0x9308)
#endif

#if defined (BRSHW_CLOCK_GROUP_A1)
#define CLKJIT  BRS_TIMEBASE_CLOCK/6
#define CLKFIX  PLLFIXCLK/6
#define BRSHW_TIMER_CLK  CLKFIX/8
# elif defined (BRSHW_CLOCK_GROUP_A2)
#if(BRS_TIMEBASE_CLOCK==80)
#define BRSHW_TIMER_CLK  BRS_TIMEBASE_CLOCK/2
#  elif   (BRS_TIMEBASE_CLOCK==96)
#define BRSHW_TIMER_CLK  ((BRS_TIMEBASE_CLOCK/2) - 8)
#  elif   (BRS_TIMEBASE_CLOCK==120)
#define BRSHW_TIMER_CLK  BRS_TIMEBASE_CLOCK/3
#  elif(BRS_TIMEBASE_CLOCK==160)
#define BRSHW_TIMER_CLK  BRS_TIMEBASE_CLOCK/4
#  elif(BRS_TIMEBASE_CLOCK==240)
#define BRSHW_TIMER_CLK  BRS_TIMEBASE_CLOCK/6

#else
#error Derivatives within this CLOCK_GROUP only supports 80,96,120,160 or 240 MHz for TIMEBASE_CLOCK !
#endif

#else
#define BRSHW_TIMER_CLK  BRS_TIMEBASE_CLOCK/2
#endif

#elif defined (BRSHW_CLOCK_GROUP_B)

#elif defined (BRSHW_CLOCK_GROUP_C)
#define CKSC0CTL            BRSHW_IOS(uint32, 0xFFF89000)
#define CKSC0ACT            BRSHW_IOS(uint32, 0xFFF89008)
#define CLKD0DIV            BRSHW_IOS(uint32, 0xFFF88800)
#define CLKD0STAT           BRSHW_IOS(uint32, 0xFFF88804)
#define CKSC1CTL            BRSHW_IOS(uint32, 0xFFF89040)
#define CKSC1ACT            BRSHW_IOS(uint32, 0xFFF89048)

#elif defined (BRSHW_CLOCK_GROUP_D)
#define CLKD0DIV   BRSHW_IOS(uint32, 0xFFF88800)
#define CLKD0STAT  BRSHW_IOS(uint32, 0xFFF88804)
#define CLKD1DIV   BRSHW_IOS(uint32, 0xFFF88808)
#define CLKD1STAT  BRSHW_IOS(uint32, 0xFFF8880C)
#define CKSC0C     BRSHW_IOS(uint32, 0xFFF89000)
#define CKSC0S     BRSHW_IOS(uint32, 0xFFF89008)

#else
#error "Unknown BRSHW_CLOCK_GROUP configured. Check BrsHw_DerivativeList.h for your Derivative."
#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_A)

#define ICP0            0xFFFF903A
#define ICP1            0xFFFF903C
#define ICP2            0xFFFF903E
#define ICP3            0xFFFFA044
#define ICP4            0xFFFFA046
#define ICP5            0xFFFFA048

#define ICTAUD0I0       0xFFFF9000
#define BRS_TIMER_ICR   ICTAUD0I0

#define ICRCANGERR0     0xFFFF901C
#define ICRCANGRECC0    0xFFFF901E

#define ICRCAN0ERR      0xFFFF9020
#define ICRCAN0REC      0xFFFF9022
#define ICRCAN0TRX      0xFFFF9024
#define ICPx_CAN0       ICP0

#define ICRCAN1ERR      0xFFFFA0D2
#define ICRCAN1REC      0xFFFFA0D4
#define ICRCAN1TRX      0xFFFFA0D6
#define ICPx_CAN1       ICP1

#define ICRCAN2ERR      0xFFFFA1A2
#define ICRCAN2REC      0xFFFFA1A4
#define ICRCAN2TRX      0xFFFFA1A6
#define ICPx_CAN2       ICP2

#define ICRCAN3ERR      0xFFFFA1A8
#define ICRCAN3REC      0xFFFFA1AA
#define ICRCAN3TRX      0xFFFFA1AC
#define ICPx_CAN3       ICP3

#define ICRCAN4ERR      0xFFFFA210
#define ICRCAN4REC      0xFFFFA212
#define ICRCAN4TRX      0xFFFFA214
#define ICPx_CAN4       ICP4

#define ICRCAN5ERR      0xFFFFA22E
#define ICRCAN5REC      0xFFFFA230
#define ICRCAN5TRX      0xFFFFA232
#define ICPx_CAN5       ICP5

#define ICRLIN20         0xFFFFA064
#define ICRLIN21         0xFFFFA066
#define ICRLIN22         0xFFFFA134
#define ICRLIN23         0xFFFFA136
#define ICRLIN24         0xFFFFA1B4
#define ICRLIN25         0xFFFFA1B6
#define ICRLIN26         0xFFFFA216
#define ICRLIN27         0xFFFFA218
#define ICRLIN28         0xFFFFA22A
#define ICRLIN29         0xFFFFA22C

#define ICRLIN30         0xFFFF9032
#define ICRLIN30UR0      0xFFFF9034
#define ICRLIN30UR1      0xFFFF9036
#define ICRLIN30UR2      0xFFFF9038

#define ICRLIN31         0xFFFFA0E0
#define ICRLIN31UR0      0xFFFF90E2
#define ICRLIN31UR1      0xFFFF90E4
#define ICRLIN31UR2      0xFFFF90E6

#define ICRLIN32         0xFFFFA138
#define ICRLIN32UR0      0xFFFFA13A
#define ICRLIN32UR1      0xFFFFA13C
#define ICRLIN32UR2      0xFFFFA13E

#define ICRLIN33         0xFFFFA1B8
#define ICRLIN33UR0      0xFFFFA1BA
#define ICRLIN33UR1      0xFFFFA1BC
#define ICRLIN33UR2      0xFFFFA1BE

#define ICRLIN34         0xFFFFA1C0
#define ICRLIN34UR0      0xFFFFA1C2
#define ICRLIN34UR1      0xFFFFA1C4
#define ICRLIN34UR2      0xFFFFA1C6

#define ICRLIN35         0xFFFFA1C8
#define ICRLIN35UR0      0xFFFFA1CA
#define ICRLIN35UR1      0xFFFFA1CC
#define ICRLIN35UR2      0xFFFFA1CE

#elif defined (BRSHW_INTERRUPT_TABLE_GROUP_B)
#define BRS_ICR_CH_AD(n) (0xFFFFB040 + ((n - 32)*2))

#define ICP0             BRS_ICR_CH_AD(32)
#define ICP1             BRS_ICR_CH_AD(33)
#define ICP2             BRS_ICR_CH_AD(34)
#define ICP3             BRS_ICR_CH_AD(35)
#define ICP4             BRS_ICR_CH_AD(36)
#define ICP5             BRS_ICR_CH_AD(128)
#define ICP6             BRS_ICR_CH_AD(129)
#define ICP7             BRS_ICR_CH_AD(130)
#define ICP8             BRS_ICR_CH_AD(131)
#define ICP9             BRS_ICR_CH_AD(132)
#define ICP10            BRS_ICR_CH_AD(296)
#define ICP11            BRS_ICR_CH_AD(297)
#define ICP12            BRS_ICR_CH_AD(298)

#define ICTAUD0I0       BRS_ICR_CH_AD(141)
#define BRS_TIMER_ICR   ICTAUD0I0

#define ICRCANGERR0     BRS_ICR_CH_AD(189)
#define ICRCANGRECC0    BRS_ICR_CH_AD(190)

#define ICRCAN0ERR      BRS_ICR_CH_AD(183)
#define ICRCAN0REC      BRS_ICR_CH_AD(184)
#define ICRCAN0TRX      BRS_ICR_CH_AD(185)
#define ICPx_CAN0       ICP5

#define ICRCAN1ERR      BRS_ICR_CH_AD(186)
#define ICRCAN1REC      BRS_ICR_CH_AD(187)
#define ICRCAN1TRX      BRS_ICR_CH_AD(188)
#define ICPx_CAN1       ICP6

#define ICRLIN30UR0     BRS_ICR_CH_AD(116)
#define ICRLIN30UR1     BRS_ICR_CH_AD(115)
#define ICRLIN30UR2     BRS_ICR_CH_AD(114)

#define ICRLIN31UR0     BRS_ICR_CH_AD(119)
#define ICRLIN31UR1     BRS_ICR_CH_AD(118)
#define ICRLIN31UR2     BRS_ICR_CH_AD(117)

#define ICFLX0LINE0     BRS_ICR_CH_AD(194)
#define ICFLX0LINE1     BRS_ICR_CH_AD(195)
#define ICFLX0TIM0      BRS_ICR_CH_AD(196)
#define ICFLX0TIM1      BRS_ICR_CH_AD(197)
#define ICFLX0TIM2      BRS_ICR_CH_AD(198)

#elif defined (BRSHW_INTERRUPT_TABLE_GROUP_C)

#define ICP0            0xFFFFB04A
#define ICP1            0xFFFFB04C
#define ICP2            0xFFFFB04E
#define ICP3            0xFFFFB056
#define ICP4            0xFFFFB058
#define ICP5            0xFFFFB05A
#define ICP6            0xFFFFB100

#define ICTAUD0I0       0xFFFEEA10
#define BRS_TIMER_ICR   ICTAUD0I0

#define ICRCANGERR0     0xFFFEEA2C
#define ICRCANGRECC0    0xFFFEEA2E

#define ICRCAN0ERR      0xFFFEEA30
#define ICRCAN0REC      0xFFFEEA32
#define ICRCAN0TRX      0xFFFEEA34
#define ICPx_CAN0       ICP0

#define ICRCAN1ERR      0xFFFFB0E2
#define ICRCAN1REC      0xFFFFB0E4
#define ICRCAN1TRX      0xFFFFB0E6
#define ICPx_CAN1       ICP1

#define ICRCAN2ERR      0xFFFFB1B2
#define ICRCAN2REC      0xFFFFB1B4
#define ICRCAN2TRX      0xFFFFB1B6
#define ICPx_CAN2       ICP2

#define ICRCAN3ERR      0xFFFFB1B8
#define ICRCAN3REC      0xFFFFB1BA
#define ICRCAN3TRX      0xFFFFB1BC
#define ICPx_CAN3       ICP3

#define ICRCAN4ERR      0xFFFFB220
#define ICRCAN4REC      0xFFFFB222
#define ICRCAN4TRX      0xFFFFB224
#define ICPx_CAN4       ICP4

#define ICRCAN5ERR      0xFFFFB23E
#define ICRCAN5REC      0xFFFFB240
#define ICRCAN5TRX      0xFFFFB242
#define ICPx_CAN5       ICP5

#define ICRCANGERR1     0xFFFFB27E
#define ICRCANGRECC1    0xFFFFB280

#define ICRCAN6ERR      0xFFFFB282
#define ICRCAN6REC      0xFFFFB284
#define ICRCAN6TRX      0xFFFFB286
#define ICPx_CAN6       ICP6

#define ICRLIN20        0xFFFFB074
#define ICRLIN21        0xFFFFB076
#define ICRLIN22        0xFFFFB144
#define ICRLIN23        0xFFFFB146
#define ICRLIN24        0xFFFFB1C4
#define ICRLIN25        0xFFFFB1C6
#define ICRLIN26        0xFFFFB226
#define ICRLIN27        0xFFFFB228
#define ICRLIN28        0xFFFFB23A
#define ICRLIN29        0xFFFFB23C
#define ICRLIN210       0xFFFFB288
#define ICRLIN211       0xFFFFB28A

#define ICRLIN30        0xFFFFB042
#define ICRLIN30UR0     0xFFFFB044
#define ICRLIN30UR1     0xFFFFB046
#define ICRLIN30UR2     0xFFFFB048

#define ICRLIN31        0xFFFFB0F0
#define ICRLIN31UR0     0xFFFFB0F2
#define ICRLIN31UR1     0xFFFFB0F4
#define ICRLIN31UR2     0xFFFFB0F6

#define ICRLIN32        0xFFFFB148
#define ICRLIN32UR0     0xFFFFB14A
#define ICRLIN32UR1     0xFFFFB14C
#define ICRLIN32UR2     0xFFFFB14E

#define ICRLIN33        0xFFFFB1C8
#define ICRLIN33UR0     0xFFFFB1CA
#define ICRLIN33UR1     0xFFFFB1CC
#define ICRLIN33UR2     0xFFFFB1CE

#define ICRLIN34        0xFFFFB1D0
#define ICRLIN34UR0     0xFFFFB1D2
#define ICRLIN34UR1     0xFFFFB1D4
#define ICRLIN34UR2     0xFFFFB1D6

#define ICRLIN35        0xFFFFB1D8
#define ICRLIN35UR0     0xFFFFB1DA
#define ICRLIN35UR1     0xFFFFB1DC
#define ICRLIN35UR2     0xFFFFB1DE

#define ICFLX0LINE0     0xFFFFB166
#define ICFLX0LINE1     0xFFFFB168
#define ICFLX0TIM0      0xFFFFB16A
#define ICFLX0TIM1      0xFFFFB16C
#define ICFLX0TIM2      0xFFFFB16E

#define ICETNB0DATA     0xFFFFB276

#elif defined (BRSHW_INTERRUPT_TABLE_GROUP_D)
#define BRS_ICR_CH_AD1(n) (0xFFFEEA00 + (n *2))
#define BRS_ICR_CH_AD2(n) (0xFFFFB040 + ((n - 32)*2))

#define BRS_ICR_CH_AD(n) ( n <= 31 ? BRS_ICR_CH_AD1(n) : BRS_ICR_CH_AD2(n) )

#define FSGD0BPROT0 0xFFC4C000
#define FSGD0BPROT1 0xFFC4C004

#define PEGSP       0xFFFEE60C
#define PEGG0MK     0xFFFEE680
#define PEGG0BA     0xFFFEE684

#define ICP0             BRS_ICR_CH_AD(6)
#define ICP1             BRS_ICR_CH_AD(7)
#define ICP2             BRS_ICR_CH_AD(8)
#define ICP3             BRS_ICR_CH_AD(9)
#define ICP4             BRS_ICR_CH_AD(10)
#define ICP5             BRS_ICR_CH_AD(11)
#define ICP6             BRS_ICR_CH_AD(12)
#define ICP7             BRS_ICR_CH_AD(13)
#define ICP8             BRS_ICR_CH_AD(14)
#define ICP9             BRS_ICR_CH_AD(15)
#define ICP10            BRS_ICR_CH_AD(16)

#define ICTAUB0I0       BRS_ICR_CH_AD(17)
#define BRS_TIMER_ICR   ICTAUB0I0

#define ICRCANGERR0     BRS_ICR_CH_AD(69)
#define ICRCANGRECC0    BRS_ICR_CH_AD(70)

#define ICRCAN0ERR      BRS_ICR_CH_AD(71)
#define ICRCAN0REC      BRS_ICR_CH_AD(72)
#define ICRCAN0TRX      BRS_ICR_CH_AD(73)
#define ICPx_CAN0       ICP6

#define ICRCAN1ERR      BRS_ICR_CH_AD(118)
#define ICRCAN1REC      BRS_ICR_CH_AD(119)
#define ICRCAN1TRX      BRS_ICR_CH_AD(120)
#define ICPx_CAN1       ICP8

#define ICRCAN2ERR      BRS_ICR_CH_AD(180)
#define ICRCAN2REC      BRS_ICR_CH_AD(181)
#define ICRCAN2TRX      BRS_ICR_CH_AD(182)
#define ICPx_CAN2       ICP10

#define ICRLIN30UR0     BRS_ICR_CH_AD(83)
#define ICRLIN30UR1     BRS_ICR_CH_AD(82)
#define ICRLIN30UR2     BRS_ICR_CH_AD(81)
#define ICRLIN30        ICRLIN30UR0

#define ICRLIN31UR0     BRS_ICR_CH_AD(86)
#define ICRLIN31UR1     BRS_ICR_CH_AD(85)
#define ICRLIN31UR2     BRS_ICR_CH_AD(84)
#define ICRLIN31        ICRLIN31UR0

#define ICRLIN32UR0     BRS_ICR_CH_AD(217)
#define ICRLIN32UR1     BRS_ICR_CH_AD(216)
#define ICRLIN32UR2     BRS_ICR_CH_AD(215)
#define ICRLIN32        ICRLIN32UR0

#define ICRLIN33UR0     BRS_ICR_CH_AD(220)
#define ICRLIN33UR1     BRS_ICR_CH_AD(219)
#define ICRLIN33UR2     BRS_ICR_CH_AD(218)
#define ICRLIN33        ICRLIN33UR0

#define ICETNB0DATA     BRS_ICR_CH_AD(244)

#elif defined (BRSHW_INTERRUPT_TABLE_GROUP_E)
#define BRS_ICR_CH_AD1(n) (0xFFFEEA00 + (n *2))
#define BRS_ICR_CH_AD2(n) (0xFFFFB040 + ((n - 32)*2))

#define BRS_ICR_CH_AD(n) ( n <= 31 ? BRS_ICR_CH_AD1(n) : BRS_ICR_CH_AD2(n) )

#define IRQ0             BRS_ICR_CH_AD(9)
#define IRQ1             BRS_ICR_CH_AD(10)
#define IRQ2             BRS_ICR_CH_AD(11)
#define IRQ3             BRS_ICR_CH_AD(12)
#define IRQ4             BRS_ICR_CH_AD(13)
#define IRQ5             BRS_ICR_CH_AD(14)
#define IRQ6             BRS_ICR_CH_AD(15)
#define IRQ7             BRS_ICR_CH_AD(16)

#define OVIC0           BRS_ICR_CH_AD(78)
#define BRS_TIMER_ICR   OVIC0

#define ICRCANGERR0     BRS_ICR_CH_AD(413)
#define ICRCANGRECC0    BRS_ICR_CH_AD(412)

#define ICRCAN0ERR      BRS_ICR_CH_AD(415)
#define ICRCAN0TRX      BRS_ICR_CH_AD(416)
#define ICPx_CAN0       IRQ0

#define ICRCAN1ERR      BRS_ICR_CH_AD(418)
#define ICRCAN1TRX      BRS_ICR_CH_AD(419)
#define ICPx_CAN1       IRQ1

#define ICRCAN2ERR      BRS_ICR_CH_AD(421)
#define ICRCAN2TRX      BRS_ICR_CH_AD(422)
#define ICPx_CAN2       IRQ2

#define ICRCAN3ERR      BRS_ICR_CH_AD(424)
#define ICRCAN3TRX      BRS_ICR_CH_AD(425)
#define ICPx_CAN3       IRQ3

#define ICRLIN20        BRS_ICR_CH_AD(429)
#define ICRLIN28        BRS_ICR_CH_AD(429)

#define ICFLX0LINE0     BRS_ICR_CH_AD(401)
#define ICFLX0LINE1     BRS_ICR_CH_AD(402)
#define ICFLX0TIM0      BRS_ICR_CH_AD(403)
#define ICFLX0TIM1      BRS_ICR_CH_AD(404)
#define ICFLX0TIM2      BRS_ICR_CH_AD(405)

#elif defined (BRSHW_INTERRUPT_TABLE_GROUP_F)
#define BRS_ICR_CH_AD1(n) (0xFFFEEA00 + (n *2))
#define BRS_ICR_CH_AD2(n) (0xFFFFB040 + ((n - 32)*2))

#define BRS_ICR_CH_AD(n) ( n <= 31 ? BRS_ICR_CH_AD1(n) : BRS_ICR_CH_AD2(n) )

#define IRQ0             BRS_ICR_CH_AD(9)
#define IRQ1             BRS_ICR_CH_AD(10)
#define IRQ2             BRS_ICR_CH_AD(11)
#define IRQ3             BRS_ICR_CH_AD(12)
#define IRQ4             BRS_ICR_CH_AD(13)
#define IRQ5             BRS_ICR_CH_AD(14)
#define IRQ6             BRS_ICR_CH_AD(15)
#define IRQ7             BRS_ICR_CH_AD(16)

#define ICTAUD0I0       BRS_ICR_CH_AD(82)
#define BRS_TIMER_ICR   ICTAUD0I0

#define ICRCANGERR0     BRS_ICR_CH_AD(187)
#define ICRCANGRECC0    BRS_ICR_CH_AD(186)

#define ICRCAN0ERR      BRS_ICR_CH_AD(189)
#define ICRCAN0TRX      BRS_ICR_CH_AD(190)
#define ICPx_CAN0

#define ICRCAN1ERR      BRS_ICR_CH_AD(192)
#define ICRCAN1TRX      BRS_ICR_CH_AD(193)
#define ICPx_CAN1

#define ICRCAN2ERR      BRS_ICR_CH_AD(195)
#define ICRCAN2TRX      BRS_ICR_CH_AD(196)
#define ICPx_CAN2

#define ICRCAN3ERR      BRS_ICR_CH_AD(198)
#define ICRCAN3TRX      BRS_ICR_CH_AD(199)
#define ICPx_CAN3

#define ICRLIN20        BRS_ICR_CH_AD(200)
#define ICRLIN21        BRS_ICR_CH_AD(201)
#define ICRLIN22        BRS_ICR_CH_AD(202)

#elif defined (BRSHW_INTERRUPT_TABLE_GROUP_G)

#define INTSTM00        0xFFFFB052
#define BRS_TIMER_ICR   INTSTM00

#define INTP0      0xFFFFB040
#define INTP1      0xFFFFB042
#define INTP2      0xFFFFB044
#define INTP3      0xFFFFB046
#define INTP4      0xFFFFB048
#define INTP5      0xFFFFB100
#define INTP6      0xFFFFB102
#define INTP7      0xFFFFB104
#define INTP8      0xFFFFB106
#define INTP9      0xFFFFB108
#define INTP10     0xFFFFB10A
#define INTP11     0xFFFFB10C

#define FCLA0CTL0  0xFFC34000
#define FCLA0CTL1  0xFFC34004
#define FCLA0CTL2  0xFFC34008
#define FCLA0CTL3  0xFFC3400C

#define INTMTTCANI0  0xFFFFB158
#define INTMTTCANI1  0xFFFFB15A
#define INTMTTCANFE  0xFFFFB15C
#define ICPx_CAN0    INTP0

#define INTMCAN0I0   0xFFFFB15E
#define INTMCAN0I1   0xFFFFB160
#define INTMCAN0FE   0xFFFFB162
#define ICPx_CAN1    INTP1

#define INTMCAN1I0   0xFFFFB164
#define INTMCAN1I1   0xFFFFB166
#define INTMCAN1FE   0xFFFFB168
#define ICPx_CAN2    INTP2

#define INTMCAN2I0   0xFFFFB16A
#define INTMCAN2I1   0xFFFFB16C
#define INTMCAN2FE   0xFFFFB16E
#define ICPx_CAN3    INTP3

#define ICRLIN30UR0  0xFFFFB0D0
#define ICRLIN30UR1  0xFFFFB0CE
#define ICRLIN30UR2  0xFFFFB0CC

#define ICRLIN31UR0  0xFFFFB0D6
#define ICRLIN31UR1  0xFFFFB0D4
#define ICRLIN31UR2  0xFFFFB0D2

#define ICRLIN32UR0  0xFFFFB0DC
#define ICRLIN32UR1  0xFFFFB0DA
#define ICRLIN32UR2  0xFFFFB0D8

#define ICRLIN33UR0  0xFFFFB0E2
#define ICRLIN33UR1  0xFFFFB0E0
#define ICRLIN33UR2  0xFFFFB0DE

#define ICFLX0LINE0      0xFFFFB174
#define ICFLX0LINE1      0xFFFFB176

#define INTETNA0    0xFFFFB170
#define INTETNA1    0xFFFFB172

#elif defined (BRSHW_INTERRUPT_TABLE_GROUP_H)
#define BRS_ICR_CH_AD1(n) (0xFFFEEA00 + (n *2))
#define BRS_ICR_CH_AD2(n) (0xFFFFB040 + ((n - 32)*2))

#define BRS_ICR_CH_AD(n) ( n <= 31 ? BRS_ICR_CH_AD1(n) : BRS_ICR_CH_AD2(n) )

#define IRQ0             BRS_ICR_CH_AD(9)
#define IRQ1             BRS_ICR_CH_AD(10)
#define IRQ2             BRS_ICR_CH_AD(11)
#define IRQ3             BRS_ICR_CH_AD(12)
#define IRQ4             BRS_ICR_CH_AD(13)
#define IRQ5             BRS_ICR_CH_AD(14)
#define IRQ6             BRS_ICR_CH_AD(15)
#define IRQ7             BRS_ICR_CH_AD(16)

#define ICTAUD0I0       BRS_ICR_CH_AD(98)
#define BRS_TIMER_ICR   ICTAUD0I0

#define ICRCANGERR0     BRS_ICR_CH_AD(264)
#define ICRCANGRECC0    BRS_ICR_CH_AD(263)

#define ICRCAN0ERR      BRS_ICR_CH_AD(266)
#define ICRCAN0TRX      BRS_ICR_CH_AD(267)
#define ICPx_CAN0

#define ICRCAN1ERR      BRS_ICR_CH_AD(269)
#define ICRCAN1TRX      BRS_ICR_CH_AD(270)
#define ICPx_CAN1

#define ICRCAN2ERR      BRS_ICR_CH_AD(272)
#define ICRCAN2TRX      BRS_ICR_CH_AD(273)
#define ICPx_CAN2

#define ICRCAN3ERR      BRS_ICR_CH_AD(275)
#define ICRCAN3TRX      BRS_ICR_CH_AD(276)
#define ICPx_CAN3

#else
#error "Unknown BRSHW_INTERRUPT_TABLE_GROUP configured. Check BrsHw_DerivativeList.h for your Derivative."
#endif

#if defined (BRSHW_PORT_GROUP_A)
#define PORT_BASE_ADDRESS  0xFFC10000

#define P(n)        BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0000 + (0x4*n))
#define PSR(n)      BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0100 + (0x4*n))
#define PPR(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0200 + (0x4*n))
#define PM(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0300 + (0x4*n))
#define PMC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0400 + (0x4*n))
#define PFC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0500 + (0x4*n))
#define PFCE(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0600 + (0x4*n))
#define PNOT(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0700 + (0x4*n))
#define PMSR(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0800 + (0x4*n))
#define PMCSR(n)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0900 + (0x4*n))
#define PFCAE(n)    BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0A00 + (0x4*n))
#define PIBC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4000 + (0x4*n))
#define PBDC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4100 + (0x4*n))
#define PU(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4300 + (0x4*n))
#define PIPC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4200 + (0x4*n))
#define PODC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4500 + (0x4*n))
#define PDSC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4600 + (0x4*n))
#define PIS(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4700 + (0x4*n))
#define PPROTS(n)   BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4B00 + (0x4*n))
#define PPCMD(n)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4C00 + (0x4*n))

#define FCLA0CTL(n) BRSHW_IOS(uint8,  0xFFC34020 + (0x4*n))

#elif defined (BRSHW_PORT_GROUP_B) || defined (BRSHW_PORT_GROUP_B1) || defined (BRSHW_PORT_GROUP_B2)
#define PORT_BASE_ADDRESS  0xFFC10000

#define P(n)        BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0000 + (0x40*n))
#define PSR(n)      BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0004 + (0x40*n))
#define PNOT(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0008 + (0x40*n))
#define PPR(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x000C + (0x40*n))
#define PM(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0010 + (0x40*n))
#define PMC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0014 + (0x40*n))
#define PFC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0018 + (0x40*n))
#define PFCE(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x001C + (0x40*n))
#define PMSR(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0020 + (0x40*n))
#define PMCSR(n)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0024 + (0x40*n))
#define PFCAE(n)    BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0028 + (0x40*n))
#define PIBC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4000 + (0x40*n))
#define PBDC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4004 + (0x40*n))
#define PU(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x400C + (0x40*n))
#define PODC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4014 + (0x40*n))
#define PISA(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x402C + (0x40*n))
#define PPROTS(n)   BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4034 + (0x40*n))
#define PPCMD(n)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4030 + (0x40*n))
#define PDSC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4018 + (0x40*n))
#define PIPC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4008 + (0x40*n))
#define PD(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4010 + (0x40*n))

#if defined (BRSHW_PORT_GROUP_B)

#define DNFAnEN(n)  BRSHW_IOS(uint8,  0xFFC30004 + (0x100*n))
#define FCLA1CTL(n) BRSHW_IOS(uint8,  0xFFC34020 + (0x4*n))
#endif

#if defined (BRSHW_PORT_GROUP_B1)

#define EXINTCTL  BRSHW_IOS(uint16,  0xFFC00010);
#endif

#if defined (BRSHW_PORT_GROUP_B2)

#endif

#elif defined (BRSHW_PORT_GROUP_C)
#define PORTU0_BASE_ADDRESS  0xFF618000
#define PORTUn_BASE_ADDRESS  0xFF610000
#define PORTU0_PROT_BASE_ADDRESS  0xFFC18000
#define PORTUn_PROT_BASE_ADDRESS  0xFFC10000

#define PORT_BASE_ADDRESS(n)      (n == 0 ? PORTU0_BASE_ADDRESS : PORTUn_BASE_ADDRESS)
#define PORT_PROT_BASE_ADDRESS(n) (n == 0 ? PORTU0_PROT_BASE_ADDRESS : PORTUn_PROT_BASE_ADDRESS)

#define P(n)        BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x0000 + (0x40*n))
#define PSR(n)      BRSHW_IOS(uint32, PORT_BASE_ADDRESS(n) + 0x0004 + (0x40*n))
#define PNOT(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x0008 + (0x40*n))
#define PPR(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x000C + (0x40*n))
#define PM(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x0010 + (0x40*n))
#define PMC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x0014 + (0x40*n))
#define PFC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x0018 + (0x40*n))
#define PFCE(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x001C + (0x40*n))
#define PMSR(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS(n) + 0x0020 + (0x40*n))
#define PMCSR(n)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS(n) + 0x0024 + (0x40*n))
#define PFCAE(n)    BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x0028 + (0x40*n))
#define PIBC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x4000 + (0x40*n))
#define PBDC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x4004 + (0x40*n))
#define PIPC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x4008 + (0x40*n))
#define PU(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x400C + (0x40*n))
#define PODC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS(n) + 0x4014 + (0x40*n))
#define PDSC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS(n) + 0x4018 + (0x40*n))
#define PISA(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS(n) + 0x4024 + (0x40*n))
#define PPCMD(n)    BRSHW_IOS(uint8,  PORT_PROT_BASE_ADDRESS(n) + 0x402C + (0x40 * n))
#define PPROTS(n)   BRSHW_IOS(uint8,  PORT_PROT_BASE_ADDRESS(n) + 0x4034 + (0x40 * n))

#define FCLA0CTL(n) BRSHW_IOS(uint8,  0xFFC34000 + (0x4*n))
#define FCLA1CTL(n) BRSHW_IOS(uint8,  0xFFC34100 + (0x4*n))

#elif defined (BRSHW_PORT_GROUP_D)
#define PORT_BASE1_ADDRESS  0xFF610000
#define PORT_BASE2_ADDRESS  0xFFC10000

#define P(n)        BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x0000 + (0x40 * n))
#define PSR(n)      BRSHW_IOS(uint32, PORT_BASE1_ADDRESS + 0x0004 + (0x40 * n))
#define PNOT(n)     BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x0008 + (0x40 * n))
#define PPR(n)      BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x000C + (0x40 * n))
#define PM(n)       BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x0010 + (0x40 * n))
#define PMC(n)      BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x0014 + (0x40 * n))
#define PFC(n)      BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x0018 + (0x40 * n))
#define PFCE(n)     BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x001C + (0x40 * n))
#define PMSR(n)     BRSHW_IOS(uint32, PORT_BASE1_ADDRESS + 0x0020 + (0x40 * n))
#define PMCSR(n)    BRSHW_IOS(uint32, PORT_BASE1_ADDRESS + 0x0024 + (0x40 * n))
#define PFCAE(n)    BRSHW_IOS(uint16, PORT_BASE1_ADDRESS + 0x0028 + (0x40 * n))
#define PINV(n)     BRSHW_IOS(uint32, PORT_BASE1_ADDRESS + 0x0030 + (0x40 * n))
#define PIBC(n)     BRSHW_IOS(uint16, PORT_BASE2_ADDRESS + 0x4000 + (0x40 * n))
#define PBDC(n)     BRSHW_IOS(uint16, PORT_BASE2_ADDRESS + 0x4004 + (0x40 * n))
#define PIPC(n)     BRSHW_IOS(uint16, PORT_BASE2_ADDRESS + 0x4008 + (0x40 * n))
#define PU(n)       BRSHW_IOS(uint16, PORT_BASE2_ADDRESS + 0x400C + (0x40 * n))
#define PD(n)       BRSHW_IOS(uint16, PORT_BASE2_ADDRESS + 0x4010 + (0x40 * n))
#define PDSC(n)     BRSHW_IOS(uint32, PORT_BASE2_ADDRESS + 0x4018 + (0x40 * n))
#define PUCC(n)     BRSHW_IOS(uint32, PORT_BASE2_ADDRESS + 0x4028 + (0x40 * n))
#define PPCMD(n)    BRSHW_IOS(uint8,  PORT_BASE2_ADDRESS + 0x402C + (0x40 * n))
#define PPROTS(n)   BRSHW_IOS(uint8,  PORT_BASE2_ADDRESS + 0x4034 + (0x40 * n))
#define PCR(n,m)    BRSHW_IOS(uint32, PORT_BASE1_ADDRESS + 0x2000 + (0x40 * n) + (0x04 * m))

#define EXINTCTL         BRSHW_IOS(uint16, 0xFFC00010)

#elif defined (BRSHW_PORT_GROUP_F)
#define PORT_BASE_ADDRESS  0xFFC10000

#define P(n)        BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0000 + (0x40*n))
#define PSR(n)      BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0004 + (0x40*n))
#define PNOT(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0008 + (0x40*n))
#define PPR(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x000C + (0x40*n))
#define PM(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0010 + (0x40*n))
#define PMC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0014 + (0x40*n))
#define PFC(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0018 + (0x40*n))
#define PFCE(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x001C + (0x40*n))
#define PMSR(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0020 + (0x40*n))
#define PMCSR(n)    BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x0024 + (0x40*n))
#define PINV(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x0030 + (0x40*n))
#define PIBC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4000 + (0x40*n))
#define PBDC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4004 + (0x40*n))
#define PIPC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4008 + (0x40*n))
#define PU(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x400C + (0x40*n))
#define PD(n)       BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4010 + (0x40*n))
#define PODC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4014 + (0x40*n))
#define PDSC(n)     BRSHW_IOS(uint32, PORT_BASE_ADDRESS + 0x4018 + (0x40*n))
#define PIS(n)      BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x401C + (0x40*n))
#define PUCC(n)     BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4028 + (0x40*n))
#define PODCE(n)    BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x4038 + (0x40*n))
#define PCR(n,m)    BRSHW_IOS(uint16, PORT_BASE_ADDRESS + 0x2000 + (0x40*n) + (0x4*m))

#else
#error "Unknown BRSHW_PORT_GROUP configed. Check BrsHw_DerivativeList.h for your Derivative."
#endif

#if defined (BRSHW_POWER_DOWN_MODES)
#define MSR_LM2  0xFFF86210
#define MSR_LM3  0xFFF81710
#define MSR_LM4  0xFFF81810
#define MSR_LM5  0xFFF81910
#define MSR_LM6  0xFFF81A10
#define MSR_LM7  0xFFF81B10
#define MSR_LM8  0xFFF81C10
#define MSR_LM10 0xFFF81E10
#define MSR_LM11 0xFFF81F10
#define MSR_LM12 0xFFF82010
#endif

#if defined (BRSHW_RESET_GROUP_A)
#define SWRESA   BRSHW_IOS(uint32,0xFFF80A04)

#elif defined (BRSHW_RESET_GROUP_B)
#define SWRESA   BRSHW_IOS(uint32,0xFFF8AC18)

#elif defined (BRSHW_RESET_GROUP_C)
#define SWSRESA0 BRSHW_IOS(uint32,0xFFF81100)

#else
#error "Unknown BRSHW_RESET_GROUP configed. Check BrsHw_DerivativeList.h for your Derivative."
#endif

void BrsHwPreInitPowerOn(void){
#if defined (BRSHW_POWER_DOWN_MODES)
#if defined (VGEN_ENABLE_CAN_DRV)
  BRSHW_IOS(uint32, MSR_LM3) = 0x00;
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
  BRSHW_IOS(uint32, MSR_LM6) = 0x00;
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
  BRSHW_IOS(uint32, MSR_LM11) = 0x00;
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
  BRSHW_IOS(uint32, MSR_LM4) = 0x00;
#endif

#error "If you need addiditional peripherals, you can deactivate their power-down modes here." */

#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_D)

  BRSHW_IOS(uint32, PEGG0MK) = 0xFFFFF000u;
  BRSHW_IOS(uint32, PEGG0BA) = 0xFEB800F7u;
  BRSHW_IOS(uint16, PEGSP)   = 0x1u;

  BRSHW_IOS(uint32, FSGD0BPROT0) = 0x07FFFFFF;

#if defined (VGEN_ENABLE_DRVETH__BASEASR)

  BRSHW_IOS(uint32, FSGD0BPROT1) = 0x07FFFFFF;
#endif
#endif
}

void BrsHwWatchdogInitPowerOn(void){
}

void BrsHwPllInitPowerOn(void){
#if !defined (VGEN_ENABLE_DRVMCU)

#if(BRS_TIMEBASE_CLOCK > BRSHW_CPU_MAX_FREQUENCY)
#error "The selected derivative does not support frequencies above BRSHW_CPU_MAX_FREQUENCY (please find the defined value inside BrsHw_DerivativeList.h)."
#endif

#if defined (BRSHW_PLL_GROUP_A) || defined (BRSHW_PLL_GROUP_A1) || defined (BRSHW_PLL_GROUP_A2) || \
     defined (BRSHW_PLL_GROUP_A3)|| defined (BRSHW_PLL_GROUP_A4)

#if defined (BRSHW_PLL_GROUP_A4)
#if !((BRS_OSC_CLK==8) || (BRS_OSC_CLK==16) || (BRS_OSC_CLK==20) || (BRS_OSC_CLK==24))
#error "The selected clock frequency of main oscillator is not supported (PLL_GROUP_A4 supports: 8, 16, 20 and 24 MHz)."
#endif

#  elif defined (BRSHW_PLL_GROUP_A3)
#if !((BRS_OSC_CLK==16) || (BRS_OSC_CLK==20) || (BRS_OSC_CLK==24))

#error "The selected clock frequency of main oscillator is not supported (PLL_GROUP_A3 supports: 16, 20 and 24 MHz)."
#endif

#  elif defined (BRSHW_PLL_GROUP_A2)
#if !((BRS_OSC_CLK==8) || (BRS_OSC_CLK==12) || (BRS_OSC_CLK==16))
#error "The selected clock frequency of main oscillator is not supported (PLL_GROUP_A2 supports: 8, 12 and 16 MHz)."
#endif

#else
#if !((BRS_OSC_CLK==8) || (BRS_OSC_CLK==12) || (BRS_OSC_CLK==16) || (BRS_OSC_CLK==20) || (BRS_OSC_CLK==24))
#error "The selected clock frequency of main oscillator is not supported (supported: 8, 12, 16, 20 and 24 MHz)."
#endif
#endif

  PROT_WRITE0(MOSCE, 0x02);
  while((MOSCS & 0x04) == 0x04);

#if defined (BRSHW_PLL_GROUP_A3) || defined (BRSHW_PLL_GROUP_A4)
#if(BRS_OSC_CLK == 8)
  MOSCC = 0x03;
#endif
#if(BRS_OSC_CLK == 16)
  MOSCC = 0x02;
#   elif(BRS_OSC_CLK == 20)
  MOSCC = 0x01;
#   elif(BRS_OSC_CLK == 24)
  MOSCC = 0x00;
#endif

#  elif defined (BRSHW_PLL_GROUP_A2)
#if(BRS_OSC_CLK == 8)
  MOSCC = 0x05;
#   elif(BRS_OSC_CLK == 12) || (BRS_OSC_CLK == 16)
  MOSCC = 0x04;
#endif

#else
#if(BRS_OSC_CLK == 8)
  MOSCC = 0x03;
#   elif(BRS_OSC_CLK == 12) || (BRS_OSC_CLK == 16)
  MOSCC = 0x02;
#   elif(BRS_OSC_CLK == 20)
  MOSCC = 0x01;
#   elif(BRS_OSC_CLK == 24)
  MOSCC = 0x00;
#endif
#endif

#if defined (BRSHW_PLL_GROUP_A2) || defined (BRSHW_PLL_GROUP_A3) || defined (BRSHW_PLL_GROUP_A4)
  MOSCST = 0x1FFFF;
#else
  MOSCST = 0xFFFF;
#endif

  PROT_WRITE0(MOSCE, 0x01);
  while((MOSCS & 0x04) != 0x04);

  PROT_WRITE1(PLLE0, 0x02);
  while((PLLS0 & 0x04) == 0x04);

#if defined (BRSHW_PLL_GROUP_A4)
#if(BRSHW_CPU_MAX_FREQUENCY == 120 || BRSHW_CPU_MAX_FREQUENCY == 160 || BRSHW_CPU_MAX_FREQUENCY == 240)
#if(BRS_TIMEBASE_CLOCK == 120 || BRS_TIMEBASE_CLOCK == 160 || BRS_TIMEBASE_CLOCK == 240)
#     if(BRS_OSC_CLK == 8)
#define M_DIVIDER  0
#define NR_VALUE  59
#     elif(BRS_OSC_CLK == 16)
#define M_DIVIDER  1
#define NR_VALUE  59
#     elif(BRS_OSC_CLK == 20)
#define M_DIVIDER  1
#define NR_VALUE  47
#     elif(BRS_OSC_CLK == 24)
#define M_DIVIDER  1
#define NR_VALUE  39
#     endif
#    else

#error "The selected CPU frequency is not supported (please choose 120 MHz, 160 MHz or 240 MHz)."
#endif
#   else
#error "The max CPU frequency of the selected derivative is not verified."
#endif

#  elif defined (BRSHW_PLL_GROUP_A3)
#if(BRSHW_CPU_MAX_FREQUENCY == 80 || BRSHW_CPU_MAX_FREQUENCY == 96 || BRSHW_CPU_MAX_FREQUENCY == 120)
#if(BRS_TIMEBASE_CLOCK == 80 || BRS_TIMEBASE_CLOCK == 96 || BRS_TIMEBASE_CLOCK == 120)
#     if(BRS_OSC_CLK == 16)
#define M_DIVIDER  1
#define NR_VALUE  59
#     elif(BRS_OSC_CLK == 20)
#define M_DIVIDER  1
#define NR_VALUE  47
#     elif(BRS_OSC_CLK == 24)
#define M_DIVIDER  1
#define NR_VALUE  39
#     endif
#    else

#error "The selected CPU frequency is not yet supported (please choose 80 MHz, 96 MHz or 120 MHz)."
#endif
#   else
#error "The max CPU frequency of the selected derivative is not yet verified."
#endif

#else
#if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 12))
#define M_DIVIDER 0x0
#   elif((BRS_OSC_CLK == 16) || (BRS_OSC_CLK == 20))
#define M_DIVIDER 0x1
#   elif(BRS_OSC_CLK == 24)
#define M_DIVIDER 0x2
#endif

#if((BRSHW_CPU_MAX_FREQUENCY == 80) || (BRSHW_CPU_MAX_FREQUENCY == 96))
#if((BRS_TIMEBASE_CLOCK >= 60) && (BRS_TIMEBASE_CLOCK <= 80))
#define P_DIVIDER 0x2

#     if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 16) || (BRS_OSC_CLK == 24))
#define NR_VALUE ((BRS_TIMEBASE_CLOCK/2) - 1)
#     elif(BRS_OSC_CLK == 12)
#define NR_VALUE ((BRS_TIMEBASE_CLOCK/4) +6)
#     elif(BRS_OSC_CLK == 20)
#define NR_VALUE ((BRS_TIMEBASE_CLOCK*2/5) -1)
#     endif
#    elif((BRS_TIMEBASE_CLOCK >= 30) && (BRS_TIMEBASE_CLOCK <= 60))
#define P_DIVIDER 0x4
#     if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 12) || (BRS_OSC_CLK == 16))
#define NR_VALUE (BRS_TIMEBASE_CLOCK - 1)
#     elif(BRS_OSC_CLK == 20)
#define NR_VALUE (BRS_TIMEBASE_CLOCK*4/5)
#     else
#error "The selected clock frequency of main oscillator is not yet supported for your derivative"
#     endif
#    else
#error "The selected CPU frequency is not yet supported (please choose min >30..80 MHz)."
#endif

#   elif(BRSHW_CPU_MAX_FREQUENCY == 120)
#if((BRS_TIMEBASE_CLOCK >= 80) && (BRS_TIMEBASE_CLOCK <= 120))
#define P_DIVIDER 0x2
#     if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 16))
#define NR_VALUE ((BRS_TIMEBASE_CLOCK/2) - 1)
#     elif(BRS_OSC_CLK == 20)
#define NR_VALUE ((BRS_TIMEBASE_CLOCK*2/5) -1)
#     endif

#    elif((BRS_TIMEBASE_CLOCK >= 40) && (BRS_TIMEBASE_CLOCK < 80))
#define P_DIVIDER 0x3
#     if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 16))
#define NR_VALUE (BRS_TIMEBASE_CLOCK - 1)
#     elif(BRS_OSC_CLK == 20)
#define NR_VALUE ((BRS_TIMEBASE_CLOCK*4/5) -1)
#     else
#error "The selected clock frequency of main oscillator is not yet supported for your derivative"
#     endif
#    else
#error "The selected CPU frequency is not yet supported (please choose min 40..120 MHz)."
#endif

#   elif((BRSHW_CPU_MAX_FREQUENCY == 240) || (BRSHW_CPU_MAX_FREQUENCY == 200) || (BRSHW_CPU_MAX_FREQUENCY == 160))
#if((BRS_TIMEBASE_CLOCK > 160) && (BRS_TIMEBASE_CLOCK <= 320))
#define P_DIVIDER 0x1
#     if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 16))
#define NR_VALUE ((BRS_TIMEBASE_CLOCK/4) - 1)
#     elif(BRS_OSC_CLK == 20)
#define NR_VALUE ((BRS_TIMEBASE_CLOCK/5) - 1)
#     else
#error "The selected clock frequency of main oscillator is not yet supported for your derivative"
#     endif
#    elif((BRS_TIMEBASE_CLOCK > 80) && (BRS_TIMEBASE_CLOCK <= 160))
#define P_DIVIDER 0x2
#     if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 16))
#define NR_VALUE ((BRS_TIMEBASE_CLOCK/2) -1)
#     elif(BRS_OSC_CLK == 20)
#define NR_VALUE ((BRS_TIMEBASE_CLOCK*2/5) -1)
#     else
#error "The selected clock frequency of main oscillator is not yet supported for your derivative"
#     endif
#    elif((BRS_TIMEBASE_CLOCK > 40) && (BRS_TIMEBASE_CLOCK <= 80))
#define P_DIVIDER 0x3
#     if((BRS_OSC_CLK == 8) || (BRS_OSC_CLK == 16))
#define NR_VALUE (BRS_TIMEBASE_CLOCK -1)
#     elif(BRS_OSC_CLK == 20)
#define NR_VALUE ((BRS_TIMEBASE_CLOCK*4/5) -1)
#     else
#error "The selected clock frequency of main oscillator is not yet supported for your derivative"
#     endif
#    else
#error "The selected CPU frequency is not yet supported (please choose min >40 .. 240 MHz)."
#endif

#   else
#error "The max CPU frequency of the selected derivative is not yet verified."
#endif
#endif

#if defined (BRSHW_PLL_GROUP_A4)

  PLLC0 =
    (0x6                  << 24U) |
    (0x1                  << 14U) |
    (((M_DIVIDER) & 0x03) << 11U) |
    ((NR_VALUE) & 0x7F);

  PROT_WRITE1(PLLE0, 0x01);
  while((PLLS0 & 0x04) != 0x04);

  PROT_WRITE1(PLLE1, 0x02);
  while((PLLS1 & 0x04) == 0x04);

  PLLC1 =
    (0x1                  << 16U) |
    (((M_DIVIDER) & 0x03) << 11U) |
    (0x3                  <<  8U) |
    ((NR_VALUE) & 0x3F);

  PROT_WRITE1(PLLE1, 0x01);
  while((PLLS1 & 0x04) != 0x04);

#  elif defined (BRSHW_PLL_GROUP_A3)

  PLLC0 =
    (0x1                  << 16U) |
    (((M_DIVIDER) & 0x03) << 11U) |
    (0x3                  <<  8U) |
    ((NR_VALUE) & 0x3F);

  PROT_WRITE1(PLLE0, 0x01);
  while((PLLS0 & 0x04) != 0x04);

#  elif defined (BRSHW_PLL_GROUP_A2)

#if((BRS_TIMEBASE_CLOCK > 180) && (BRS_TIMEBASE_CLOCK <= 200))
#define FVV_VCOOUT_RANGE 0x1
#   elif((BRS_TIMEBASE_CLOCK > 160) && (BRS_TIMEBASE_CLOCK <= 180))
#define FVV_VCOOUT_RANGE 0x0
#   elif((BRS_TIMEBASE_CLOCK > 150) && (BRS_TIMEBASE_CLOCK <= 160))
#define FVV_VCOOUT_RANGE 0x7
#   elif((BRS_TIMEBASE_CLOCK > 140) && (BRS_TIMEBASE_CLOCK <= 150))
#define FVV_VCOOUT_RANGE 0x6
#   elif((BRS_TIMEBASE_CLOCK > 130) && (BRS_TIMEBASE_CLOCK <= 140))
#define FVV_VCOOUT_RANGE 0x5
#   elif((BRS_TIMEBASE_CLOCK > 120) && (BRS_TIMEBASE_CLOCK <= 130))
#define FVV_VCOOUT_RANGE 0x4
#   elif((BRS_TIMEBASE_CLOCK > 110) && (BRS_TIMEBASE_CLOCK <= 120))
#define FVV_VCOOUT_RANGE 0x3
#   elif((BRS_TIMEBASE_CLOCK > 100) && (BRS_TIMEBASE_CLOCK <= 110))
#define FVV_VCOOUT_RANGE 0x2
#   elif((BRS_TIMEBASE_CLOCK > 90) && (BRS_TIMEBASE_CLOCK <= 100))
#define FVV_VCOOUT_RANGE 0x1
#   elif((BRS_TIMEBASE_CLOCK > 80) && (BRS_TIMEBASE_CLOCK <= 90))
#define FVV_VCOOUT_RANGE 0x0
#   else
#error "The selected CPU frequency is not yet supported (please choose min >80 .. 200 MHz)."
#endif

  PLLC0 =
    (FVV_VCOOUT_RANGE <<29U) |
    (M_DIVIDER <<11U) |
    (P_DIVIDER << 8U) |
    (NR_VALUE);

  PROT_WRITE1(PLLE0, 0x01);
  while((PLLS0 & 0x04) != 0x04);

#if(BRSHW_CPU_MAX_FREQUENCY == 240)
#define P_DIVIDER_PLL1 0x1
#define FVV_VCOOUT_RANGE_PLL1 0x3
#define NR_VALUE_PLL1 ((960/BRS_OSC_CLK)-1)
#   else
#define P_DIVIDER_PLL1 0x0
#define FVV_VCOOUT_RANGE_PLL1 0x0
#define NR_VALUE_PLL1 ((480/BRS_OSC_CLK)-1)
#endif

  PROT_WRITE1(PLLE1, 0x02);
  while((PLLS1 & 0x04) == 0x04);

  PLLC1 =
    (FVV_VCOOUT_RANGE_PLL1 << 29U) |
    (0x0 << 11U) |
    (P_DIVIDER_PLL1 << 8U) |
    (NR_VALUE_PLL1);

  PROT_WRITE1(PLLE1, 0x01);
  while((PLLS1 & 0x04) != 0x04);

#else

  PLLC0 =
    (M_DIVIDER <<11U) |
    (P_DIVIDER << 8U) |
    (NR_VALUE);

  PROT_WRITE1(PLLE0, 0x01);
  while((PLLS0 & 0x04) != 0x04);

#if defined (BRSHW_PLL_GROUP_A1)

  PROT_WRITE1(PLLE1, 0x02);

  PLLC1 =
    (M_DIVIDER <<11U) |
    (P_DIVIDER << 8U) |
    (NR_VALUE);

  PROT_WRITE1(PLLE1, 0x01);
  while((PLLS1 & 0x04) != 0x04);
#endif
#endif

#if defined (BRSHW_CLOCK_GROUP_A2)

  PROT_WRITE1(CKSC_PPLLCLKS_CTL, 0x03);
  while(CKSC_PPLLCLKS_ACT!=0x03);

#if defined (BRSHW_PLL_GROUP_A4)

#if(BRSHW_CPU_MAX_FREQUENCY == 240)
  PROT_WRITE1(CKSC_CPUCLKD_CTL, 0x29);
  while(CKSC_CPUCLKD_ACT!=0x29);
#    elif(BRSHW_CPU_MAX_FREQUENCY == 160)
  PROT_WRITE1(CKSC_CPUCLKD_CTL, 0x31);
  while(CKSC_CPUCLKD_ACT!=0x31);
#    elif(BRSHW_CPU_MAX_FREQUENCY == 120)
  PROT_WRITE1(CKSC_CPUCLKD_CTL, 0x11);
  while(CKSC_CPUCLKD_ACT!=0x11);
#endif

  PROT_WRITE1(CKSC_CPUCLKS_CTL, 0x0);
  while(CKSC_CPUCLKS_ACT!=0x0);

#   elif defined (BRSHW_PLL_GROUP_A3)

#if(BRSHW_CPU_MAX_FREQUENCY == 120)
  PROT_WRITE1(CKSC_CPUCLKD_CTL, 0x11);
  while(CKSC_CPUCLKD_ACT!=0x11);
#    elif(BRSHW_CPU_MAX_FREQUENCY == 96)
  PROT_WRITE1(CKSC_CPUCLKD_CTL, 0x09);
  while(CKSC_CPUCLKD_ACT!=0x09);
#    elif(BRSHW_CPU_MAX_FREQUENCY == 80)
  PROT_WRITE1(CKSC_CPUCLKD_CTL, 0x01);
  while(CKSC_CPUCLKD_ACT!=0x01);
#endif

  PROT_WRITE1(CKSC_CPUCLKS_CTL, 0x03);
  while(CKSC_CPUCLKS_ACT!=0x03);

#   else
#error "CPU clock domain has not been configured yet."
#endif

#if defined (VGEN_ENABLE_CAN_DRV)

  PROT_WRITE1(CKSC_ICANS_CTL, 0x03);
  while(CKSC_ICANS_ACT!=0x03);

  PROT_WRITE1(CKSC_ICANOSCD_CTL, 0x01);
  while(CKSC_ICANOSCD_ACT!=0x01);

  PROT_WRITE1(CKSC_IPERI2S_CTL, 0x01);
  while(CKSC_IPERI2S_ACT!=0x01);
#endif

#if defined (VGEN_ENABLE_LIN_DRV)

  PROT_WRITE1(CKSC_ILINS_CTL, 0x01);
  while(CKSC_ILINS_ACT!=0x01);
#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN30_0)

  PROT_WRITE1(CKSC_ILIND_CTL, 0x01);
  while(CKSC_ILIND_ACT!=0x01);
#endif
#endif

#endif

#if defined (BRSHW_CLOCK_GROUP_A1)

  PROT_WRITE1(CKSC_IPPL0S_CTL, 0x01);
  while(CKSC_IPPL0S_ACT!=0x01);

  PROT_WRITE1(CKSC_IPPL1S_CTL, 0x01);
  while(CKSC_IPPL1S_ACT!=0x01);

  PROT_WRITE3(CKSC_ICLKJITS_CTL, 0x01);
  while(CKSC_ICLKJITS_ACT!=0x01);

  PROT_WRITE3(CKSC_ICLKFIXS_CTL, 0x01);
  while(CKSC_ICLKFIXS_ACT!=0x01);
#endif

#if defined (BRSHW_CLOCK_GROUP_A) || defined (BRSHW_CLOCK_GROUP_A1)

  PROT_WRITE1(CKSC_CPUCLKD_CTL, 0x01);
  while(CKSC_CPUCLKD_ACT!=0x01);

  PROT_WRITE1(CKSC_CPUCLKS_CTL, 0x03);
  while(CKSC_CPUCLKS_ACT!=0x03);

#if defined (VGEN_ENABLE_CAN_DRV)
#if defined (BRSHW_CLOCK_GROUP_A1)

  PROT_WRITE3(CKSC_IRSCAND_CTL, 0x01);
  while(CKSC_IRSCAND_ACT!=0x01);

  PROT_WRITE3(CKSC_IPCRSCANS_CTL, 0x01);
  while(CKSC_IPCRSCANS_ACT!=0x01);

  PROT_WRITE3(CKSC_IRSCANXINS_CTL, 0x01);
  while(CKSC_IRSCANXINS_ACT!=0x01);
#    else

  PROT_WRITE1(CKSC_ICANOSCD_CTL, 0x01);
  while(CKSC_ICANOSCD_ACT!=0x01);

  PROT_WRITE1(CKSC_ICANS_CTL, 0x03);
  while(CKSC_ICANS_ACT!=0x03);
#endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_CLOCK_GROUP_A1)

  PROT_WRITE3(CKSC_IRLINS_CTL, 0x01);
  while( CKSC_IRLINS_ACT!=0x01);
#    else

  PROT_WRITE1(CKSC_ILIND_CTL, 0x01);
  while(CKSC_ILIND_ACT!=0x01);

  PROT_WRITE1(CKSC_ILINS_CTL, 0x01);
  while(CKSC_ILINS_ACT!=0x01);
#endif
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
#     if defined (BRSHW_CLOCK_GROUP_A1)

  PROT_WRITE4(MRSTC, 0x4);

  PROT_WRITE3(CKSC_IPCETNBS_CTL, 0x01);
  while(CKSC_IPCETNBS_ACT!=0x01);

  PROT_WRITE4(MRSTC, 0x2004);

  PROT_WRITE3(CKSC_IXCCLKS_CTL, 0x01);
  while(CKSC_IXCCLKS_ACT  !=0x01);

  PROT_WRITE3(CKSC_IXCETNBS_CTL, 0x01);
  while(CKSC_IXCETNBS_ACT !=0x01);
#endif
#endif
#endif
#endif

#if defined (BRSHW_PLL_GROUP_C)

  while(PLL0CLKS!=0x07);

  PROT_WRITE1(CKSC0CTL, 0x23);

#if(BRSHW_CPU_MAX_FREQUENCY==320)

  BrsHwTime100NOP();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
#  elif(BRSHW_CPU_MAX_FREQUENCY==240)

  BrsHwTime100NOP();
  BRSHWNOP10();
#  elif(BRSHW_CPU_MAX_FREQUENCY==160)

  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
#else
#error "this specific maximun frequencies is not yet support"
#endif

  while(CKSC0ACT!=0x23);

#if(BRS_TIMEBASE_CLOCK == BRSHW_CPU_MAX_FREQUENCY/4)
  PROT_WRITE1(CLKD0DIV, 0x04);
# elif(BRS_TIMEBASE_CLOCK == BRSHW_CPU_MAX_FREQUENCY/2)
  PROT_WRITE1(CLKD0DIV, 0x02);
# elif(BRS_TIMEBASE_CLOCK == BRSHW_CPU_MAX_FREQUENCY)
  PROT_WRITE1(CLKD0DIV, 0x01);
#else
#error "Other Cpu-Frequency as PLL0 with division 1/1, 1/2, 1/4 are not possible for this derivative"
#endif

  PROT_WRITE1(CKSC1CTL, 0x24);

#if(BRSHW_CPU_MAX_FREQUENCY==320)

  BrsHwTime100NOP();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
#  elif(BRSHW_CPU_MAX_FREQUENCY==240)

  BrsHwTime100NOP();
  BRSHWNOP10();
#  elif(BRSHW_CPU_MAX_FREQUENCY==160)

  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
#else
#error "this specific maximun frequencies is not yet support"
#endif

  while(CLKD0STAT!=0x1);

  while(CKSC1ACT!=0x24);

#endif

#if defined (BRSHW_PLL_GROUP_D)
#if !( (BRS_OSC_CLK==16) || (BRS_OSC_CLK==20) || (BRS_OSC_CLK==24))
#error "The selected clock frequency of main oscillator is not supported (supported: 16, 20 and 24 MHz)."
#endif

  uint32 OptionByte1 = OPBT1;

  uint32 PLL0FREQ = OptionByte1 & 0xC0000000;

  uint32 PLL0NDIV = OptionByte1 & 0x000007F8;

  uint32 PLL0MDIV = OptionByte1 & 0x00003800;

  uint32 CLKOUT;

  uint32 estimatedCLKOUT;

  PLL0FREQ =  PLL0FREQ >> 30;
  PLL0NDIV = (PLL0NDIV >> 3)  + 0x1;
  PLL0MDIV = (PLL0MDIV >> 11) + 0x1;

#if(BRS_TIMEBASE_CLOCK == 240)
  estimatedCLKOUT = 480;
  if(PLL0FREQ != 0x2)
#  elif(BRS_TIMEBASE_CLOCK == 160)
  estimatedCLKOUT = 320;
  if(PLL0FREQ != 0x1)
#  elif(BRS_TIMEBASE_CLOCK == 120)
  estimatedCLKOUT = 480;
  if(PLL0FREQ != 0x0)
#else
#error "The selected CPU frequency is not yet supported"
#endif
  {
    while(1){
    }
  }

#if(BRS_OSC_CLK == 16)
  CLKOUT = ((BRS_OSC_CLK * PLL0NDIV) / PLL0MDIV);

#  elif(BRS_OSC_CLK == 20)
  CLKOUT = ((BRS_OSC_CLK * PLL0NDIV) / PLL0MDIV);
#  elif(BRS_OSC_CLK == 24)
  CLKOUT = ((BRS_OSC_CLK * PLL0NDIV) / PLL0MDIV);
#else
#error "The selected clock frequency of main oscillator is not yet supported"
#endif
  if(CLKOUT != estimatedCLKOUT){
    while(1){
    }
  }

  CKSC0C = 0x01;
  while(CKSC0S!=0x01);

  CLKD0DIV=BRSHW_CLKD0DIV;
  while(CLKD0STAT!=0x03);

  CLKD1DIV=BRSHW_CLKD1DIV;
  while(CLKD1STAT!=0x03);
#endif

#if defined (BRSHW_PLL_GROUP_F)
#if !( (BRS_OSC_CLK==16) || (BRS_OSC_CLK==20) || (BRS_OSC_CLK==24))
#error "The selected clock frequency of main oscillator is not supported (supported: 16, 20 and 24 MHz)."
#endif

  uint32 OptionByte1 = OPBT1;

  uint32 PLL0FREQ = OptionByte1 & 0xC0000000;

  uint32 PLL0NDIV = OptionByte1 & 0x000007F8;

  uint32 PLL0MDIV = OptionByte1 & 0x00003800;

  uint32 PLL0PDIV = OptionByte1 & 0x00000007;

  uint32 CLKOUT;

  uint32 estimatedCLKOUT;

  PLL0FREQ =  PLL0FREQ >> 30;
  PLL0NDIV = (PLL0NDIV >> 3)  + 0x1;
  PLL0MDIV = (PLL0MDIV >> 11) + 0x1;
  PLL0PDIV = PLL0PDIV + 0x1;

#if(BRS_TIMEBASE_CLOCK == 120)
  estimatedCLKOUT = 240;
  if(PLL0FREQ != 0x3)
#else
#error "The selected CPU frequency is not yet supported"
#endif
  {
    while(1){
    }
  }

#if(BRS_OSC_CLK == 16)
  CLKOUT = (((BRS_OSC_CLK * PLL0NDIV) / PLL0MDIV) / PLL0PDIV);

#  elif(BRS_OSC_CLK == 20)
  CLKOUT = (((BRS_OSC_CLK * PLL0NDIV) / PLL0MDIV) / PLL0PDIV);
#  elif(BRS_OSC_CLK == 24)
  CLKOUT = (((BRS_OSC_CLK * PLL0NDIV) / PLL0MDIV) / PLL0PDIV);
#else
#error "The selected clock frequency of main oscillator is not yet supported"
#endif
  if(CLKOUT != estimatedCLKOUT){
    while(1){
    }
  }

  CKSC0C = 0x01;
  while(CKSC0S!=0x01);

  CLKD0DIV=BRSHW_CLKD0DIV;
  while(CLKD0STAT!=0x03);

  CLKD1DIV=BRSHW_CLKD1DIV;
  while(CLKD1STAT!=0x03);
#endif

#endif
}

#if !defined (VGEN_ENABLE_DRVPORT)

void BrsHwInitPortAlternative(brsHw_Port_PortType p){
#if defined (BRSHW_PORT_GROUP_A)

  if((p.portGroup == BRSHW_PORT_PORTGROUP_0) && (p.portNumber == BRSHW_PORT_PORTNUMBER_0)){
    PPCMD(p.portGroup) = 0xA5;

    BRSHWNOP10();
    PODC(p.portGroup) &= ~(1 << p.portNumber);
    BRSHWNOP10();
    PODC(p.portGroup) ^= ~(1 << p.portNumber);
    BRSHWNOP10();
    PODC(p.portGroup) &= ~(1 << p.portNumber);
    if(PPROTS(p.portGroup) == 1)
      while(1);
  }
#endif

  if(p.portAlternative == BRSHW_PORT_ALT_0){
    PMC(p.portGroup) &= ~(1 << p.portNumber);
  }
  else{
    PIBC(p.portGroup) &=  ~(1 << p.portNumber);

#if !defined(BRSHW_PORT_GROUP_F)
    PFCAE(p.portGroup) &= ~(1 << p.portNumber);
#endif
    PFCE(p.portGroup) &= ~(1 << p.portNumber);
    PFC(p.portGroup) &= ~(1 << p.portNumber);

#if !defined(BRSHW_PORT_GROUP_F)

    if(((p.portAlternative - 1) & 0x4) == 0x4){
      PFCAE(p.portGroup) |= (1 << p.portNumber);
    }
#endif

    if(((p.portAlternative - 1) & 0x2) == 0x2){
      PFCE(p.portGroup) |= (1 << p.portNumber);
    }

    if(((p.portAlternative - 1) & 0x1) == 0x1){
      PFC(p.portGroup) |= (1 << p.portNumber);
    }
    PMC(p.portGroup) |= (1 << p.portNumber);
  }
}

void BrsHwInitPortInput(brsHw_Port_PortType p){
  PM(p.portGroup)    |=  (1 << p.portNumber);
  BrsHwInitPortAlternative(p);

  if(p.portAlternative == BRSHW_PORT_ALT_0)
    PIBC(p.portGroup)  |=  (1 << p.portNumber);
}

void BrsHwInitPortOutput(brsHw_Port_PortType p){
  PM(p.portGroup) &= ~(1 << p.portNumber);
  BrsHwInitPortAlternative(p);
}

void BrsHwInitPortConfig(brsHw_Port_PortType p, brsHw_Port_ConfType n){
  if(n.PortPullUp == PORT_PULL_UP_ENABLED){
    PU(p.portGroup) |= (1 << p.portNumber);
  }
  else{
    PU(p.portGroup) &= ~(1 << p.portNumber);
  }

  if(n.PortIPControl == PORT_IP_CONTROL_ENABLED){
    PIPC(p.portGroup)  |= (1 << p.portNumber);
  }
  else{
    PIPC(p.portGroup)  &= ~(1 << p.portNumber);
  }

  if(n.PortDriveStrength == PORT_DRIVE_STRENGTH_CONTROL_ENABLED){
    if(n.PortProtectionCMD == PORT_PROTECTION_COMMAND_ENABLED){
#if !defined(BRSHW_PORT_GROUP_F)
      PPCMD(p.portGroup) = 0xA5;
#endif
      BRSHWNOP10();
      PDSC(p.portGroup) |= (1 << p.portNumber);
      BRSHWNOP10();
      PDSC(p.portGroup) ^= ~(1 << p.portNumber);
      BRSHWNOP10();
      PDSC(p.portGroup) |= (1 << p.portNumber);
#if !defined(BRSHW_PORT_GROUP_F)
      if(PPROTS(p.portGroup) == 1)
        while(1);
#endif
    }
    else{
      PDSC(p.portGroup) |= (1 << p.portNumber);
    }
  }
  else{
    if(n.PortProtectionCMD == PORT_PROTECTION_COMMAND_ENABLED){
#if !defined(BRSHW_PORT_GROUP_F)
      PPCMD(p.portGroup) = 0xA5;
#endif
      BRSHWNOP10();
      PDSC(p.portGroup) &= ~(1 << p.portNumber);
      BRSHWNOP10();
      PDSC(p.portGroup) ^= ~(1 << p.portNumber);
      BRSHWNOP10();
      PDSC(p.portGroup) &= ~(1 << p.portNumber);
#if !defined(BRSHW_PORT_GROUP_F)
      if(PPROTS(p.portGroup) == 1)
        while(1);
#endif
    }
    else{
      PDSC(p.portGroup) &= ~(1 << p.portNumber);
    }
  }

  if(n.PortBidirectionalMode == PORT_BIDIRECTIONAL_MODE_ENABLED){
    PBDC(p.portGroup) |= (1 << p.portNumber);
  }
  else{
    PBDC(p.portGroup) &= ~(1 << p.portNumber);
  }
}

#if defined (BRS_ENABLE_FBL_SUPPORT)
#define BRS_START_SEC_RAM_CODE
#include "Brs_MemMap.hpp"
#endif

void BrsHwPort_SetLevel(brsHw_Port_PortType p, uint8 Level){
  if(Level != BRSHW_PORT_LOGIC_LOW){
    P(p.portGroup) |= (1 << p.portNumber);
  }
  else{
    P(p.portGroup) &= ~(1 << p.portNumber);
  }
}
#if defined (BRS_ENABLE_FBL_SUPPORT)
#define BRS_STOP_SEC_RAM_CODE
#include "Brs_MemMap.hpp"
#endif

uint8 BrsHwPort_GetLevel(brsHw_Port_PortType p){
  uint32 temp;
  temp = PPR(p.portGroup);
  temp &= (1 << p.portNumber);

  if(temp != 0x00000000){
    return BRSHW_PORT_LOGIC_HIGH;
  }
  else{
    return BRSHW_PORT_LOGIC_LOW;
  }
}

#if defined (BRS_ENABLE_TCM_SUPPORT)

void BrsHw_WriteDio_TCM_SDA_OUT(uint8 Level){
  BrsHwPort_SetLevel(BRSHW_PORT_TCM_SDA_OUT, Level);
}

void BrsHw_WriteDio_TCM_CLK_OUT(uint8 Level){
  BrsHwPort_SetLevel(BRSHW_PORT_TCM_CLK_OUT, Level);
}

uint8 BrsHw_ReadDio_TCM_SDA_IN(void){
  return BrsHwPort_GetLevel(BRSHW_PORT_TCM_SDA_IN);
}

uint8 BrsHw_ReadDio_TCM_CLK_IN(void){
  return BrsHwPort_GetLevel(BRSHW_PORT_TCM_CLK_IN);
}
#endif
#endif

#include "McalDio.hpp"

void BrsHwPortInitPowerOn(void){
#if defined (VGEN_ENABLE_DRVPORT)
#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
     defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
#error "Configure the valid toggle pins within your DrvPort config. Or disable the depending BRS mechanism."*/
#endif

#else
#if defined (BRS_ENABLE_SUPPORT_LEDS)
  BrsHwInitPortOutput(BRSHW_PORT_LED);

  BrsHwTogglePin(BRSHW_TOGGLEPIN_LED);
#endif

#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_WD);
#endif

#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  BrsHwInitPortOutput(BRSHW_PORT_TOGGLE_CUSTOM);
#endif

#if defined (BRS_ENABLE_TCM_SUPPORT)
  BrsHwInitPortOutput(BRSHW_PORT_TCM_CLK_OUT);
  BrsHwInitPortOutput(BRSHW_PORT_TCM_SDA_OUT);
  BrsHwInitPortInput(BRSHW_PORT_TCM_SDA_IN);
  BrsHwInitPortInput(BRSHW_PORT_TCM_CLK_IN);
#if defined (BRSHW_USE_TCM_EXT_IRQ)
  BrsHwInitPortInput(BRSHW_PORT_TCM_INTA_IN);
  BrsHwInitPortInput(BRSHW_PORT_TCM_INTB_IN);
#endif
#endif

#if defined (BRSHW_PORT_GROUP_B2)

#if defined (VGEN_ENABLE_DRVFR__BASEASR) && defined (VGEN_ENABLE_LIN_DRV)
#if((defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_2) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN32_0) || defined (SIO_ENABLE_RLIN3_2)) && defined (VGEN_ENABLE_DRVFR__BASEASR))
#if(FR_CHANNEL_A_USED == STD_ON)
#error "No possibility to configure LIN on Port 7.5 (RLIN32TX) and Flexray on Port 7.5 (FLX1TXDA) simultaneously"
#endif
#endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR) && defined (VGEN_ENABLE_DRVETH__BASEASR)
#error "No possibility to configure FlexRay Modul 2 and Ethernet Modul 2 simultaneously"
#error "No possibility to configure FlexRay Modul 1 and Ethernet Modul 1 simultaneously"
#endif
#endif

#if defined (VGEN_ENABLE_CAN_DRV)
#if defined (kCanPhysToLogChannelIndex_0)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN0_RX);
  McalDio_InitFunction();
#if defined(_BRSHW_PORT_CAN0_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#endif
#if defined (_BRSHW_PORT_CAN0_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN0_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN0_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#endif

#if defined (BRSHW_ENABLE_CAN_WAKEUP_FILTER)
#if defined (BRSHW_PORT_GROUP_A)
  FCLA0CTL(0) = 0x02;
#endif
#if defined (BRSHW_PORT_GROUP_B)
  FCLA1CTL(5) = 0x02;
  DNFAnEN(2) |= (1 << 1);
#endif
#if defined (BRSHW_PORT_GROUP_B1)
  EXINTCTL |= (1 << 5);

  BrsHwInitPortInput(BRSHW_PORT_CAN0_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_B2)
  FCLA0CTL2 |= (1 << 1);

  BrsHwInitPortInput(BRSHW_PORT_CAN0_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_C)
  FCLA0CTL(7) = 0x02;
#endif
#if defined (BRSHW_PORT_GROUP_D)
  EXINTCTL |= (1 << 1);

  BrsHwInitPortInput(BRSHW_PORT_CAN0_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_F)
  FCLA0CTL6 |= (1 << 1);

  BrsHwInitPortInput(BRSHW_PORT_CAN0_WAKEUP);
#endif
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN1_RX);
#if defined(_BRSHW_PORT_CAN1_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#endif
#if defined (_BRSHW_PORT_CAN1_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN1_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN1_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#endif

#if defined (BRSHW_ENABLE_CAN_WAKEUP_FILTER)
#if defined (BRSHW_PORT_GROUP_A)
  FCLA0CTL(1) = 0x02;
#endif
#if defined (BRSHW_PORT_GROUP_B)
  FCLA1CTL(6) = 0x02;
  DNFAnEN(2) |= (1 << 2);
#endif
#if defined (BRSHW_PORT_GROUP_B1)
  EXINTCTL |= (1 << 7);

  BrsHwInitPortInput(BRSHW_PORT_CAN1_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_B2)
  FCLA0CTL3 |= (1 << 1);

  BrsHwInitPortInput(BRSHW_PORT_CAN1_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_C)
  FCLA1CTL(1) = 0x02;
#endif
#if defined (BRSHW_PORT_GROUP_D)
  EXINTCTL |= (1 << 3);

  BrsHwInitPortInput(BRSHW_PORT_CAN1_WAKEUP);
#endif
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_2)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN2_RX);
#if defined(_BRSHW_PORT_CAN2_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#endif
#if defined (_BRSHW_PORT_CAN2_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN2_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN2_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#endif

#if defined (BRSHW_ENABLE_CAN_WAKEUP_FILTER)
#if defined (BRSHW_PORT_GROUP_A)
  FCLA0CTL(2) = 0x02;
#endif
#if defined (BRSHW_PORT_GROUP_B1)
  EXINTCTL |= (1 << 9);

  BrsHwInitPortInput(BRSHW_PORT_CAN2_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_B2)
  FCLA0CTL4 |= (1 << 1);

  BrsHwInitPortInput(BRSHW_PORT_CAN2_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_C)
  FCLA1CTL(3) = 0x02;
#endif
#if defined (BRSHW_PORT_GROUP_D)
  EXINTCTL |= (1 << 5);

  BrsHwInitPortInput(BRSHW_PORT_CAN2_WAKEUP);
#endif
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_3)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN3_RX);
#if defined(_BRSHW_PORT_CAN3_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#endif
#if defined (_BRSHW_PORT_CAN3_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN3_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN3_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#endif

#if defined (BRSHW_ENABLE_CAN_WAKEUP_FILTER)
#if defined (BRSHW_PORT_GROUP_A)
  FCLA0CTL(3) = 0x02;
#endif
#if defined (BRSHW_PORT_GROUP_B1)
  EXINTCTL |= (1 << 11);

  BrsHwInitPortInput(BRSHW_PORT_CAN3_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_B2)
  FCLA0CTL5 |= (1 << 1);

  BrsHwInitPortInput(BRSHW_PORT_CAN3_WAKEUP);
#endif
#if defined (BRSHW_PORT_GROUP_D)
  EXINTCTL |= (1 << 7);

  BrsHwInitPortInput(BRSHW_PORT_CAN3_WAKEUP);
#endif
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_4)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN4_RX);
#if defined(_BRSHW_PORT_CAN4_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#endif
#if defined (_BRSHW_PORT_CAN4_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN4_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN4_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#endif

#if defined (BRSHW_ENABLE_CAN_WAKEUP_FILTER)
#if defined (BRSHW_PORT_GROUP_A)
  FCLA0CTL(4) = 0x02;
#endif
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_5)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TX);
  BrsHwInitPortInput(BRSHW_PORT_CAN5_RX);
#if defined(_BRSHW_PORT_CAN5_TRCV_STB)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_STB);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_STB, BRSHW_PORT_LOGIC_HIGH);
#endif
#if defined (_BRSHW_PORT_CAN5_TRCV_EN)
  BrsHwInitPortOutput(BRSHW_PORT_CAN5_TRCV_EN);
  BrsHwPort_SetLevel(BRSHW_PORT_CAN5_TRCV_EN, BRSHW_PORT_LOGIC_HIGH);
#endif

#if defined (BRSHW_ENABLE_CAN_WAKEUP_FILTER)
#if defined (BRSHW_PORT_GROUP_A)
  FCLA0CTL(5) = 0x02;
#endif
#endif
#endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_0) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_0) || defined (SIO_ENABLE_RLIN2_0)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_0_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_0_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_0_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_0_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_1) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_1) || defined (SIO_ENABLE_RLIN2_1)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_1_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_1_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_1_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_1_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_2) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_2) || defined (SIO_ENABLE_RLIN2_2)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_2_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_2_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_2_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_2_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_3) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_3) || defined (SIO_ENABLE_RLIN2_3)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_3_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_3_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_3_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_3_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_4) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN241_0) || defined (SIO_ENABLE_RLIN2_4)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_4_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_4_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_4_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_4_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_5) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN241_1) || defined (SIO_ENABLE_RLIN2_5)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_5_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_5_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_5_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_5_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_6) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN241_2) || defined (SIO_ENABLE_RLIN2_6)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_6_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_6_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_6_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_6_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_7) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN241_3) || defined (SIO_ENABLE_RLIN2_7)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_7_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_7_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_7_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_7_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_8) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN210_0) || defined (SIO_ENABLE_RLIN2_8)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_8_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_8_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_8_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_8_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_9) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN211_0) || defined (SIO_ENABLE_RLIN2_9)
  BrsHwInitPortOutput(BRSHW_PORT_LIN2_9_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN2_9_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_9_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN2_9_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_10) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN242_2) || defined (SIO_ENABLE_RLIN2_10)
#error "Port config for your LIN channel not yet implemented"
#endif
#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_11) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN242_3) || defined (SIO_ENABLE_RLIN2_11)
#error "Port config for your LIN channel not yet implemented"
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_0) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN30_0) || defined (SIO_ENABLE_RLIN3_0)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_0_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_0_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_0_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_0_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_1) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN31_0) || defined (SIO_ENABLE_RLIN3_1)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_1_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_1_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_1_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_1_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_2) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN32_0) || defined (SIO_ENABLE_RLIN3_2)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_2_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_2_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_2_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_2_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_3) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN33_0) || defined (SIO_ENABLE_RLIN3_3)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_3_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_3_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_3_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_3_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_4) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN34_0) || defined (SIO_ENABLE_RLIN3_4)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_4_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_4_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_4_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_4_RX, BRSHW_PORT_CONF_LIN);
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_5) || defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN35_0) || defined (SIO_ENABLE_RLIN3_5)
  BrsHwInitPortOutput(BRSHW_PORT_LIN3_5_TX);
  BrsHwInitPortInput(BRSHW_PORT_LIN3_5_RX);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_5_TX, BRSHW_PORT_CONF_LIN);
  BrsHwInitPortConfig(BRSHW_PORT_LIN3_5_RX, BRSHW_PORT_CONF_LIN);
#endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
#if(FR_CHANNEL_A_USED == STD_ON)
  BrsHwInitPortOutput(BRSHW_PORT_FLX0_A_TX);
  BrsHwInitPortOutput(BRSHW_PORT_FLX0_A_EN);
  BrsHwInitPortInput(BRSHW_PORT_FLX0_A_RX);
#endif
#if(FR_CHANNEL_B_USED == STD_ON)
  BrsHwInitPortOutput(BRSHW_PORT_FLX0_B_TX);
  BrsHwInitPortOutput(BRSHW_PORT_FLX0_B_EN);
  BrsHwInitPortInput(BRSHW_PORT_FLX0_B_RX);
#endif
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)

  BrsHwInitPortInput(BRSHW_PORT_ETH0TXCLK);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0TXD0);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0TXD1);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0TXD2);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0TXD3);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0TXEN);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0TXERR);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0TXD0, BRSHW_PORT_CONF_ETH0TXD);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0TXD1, BRSHW_PORT_CONF_ETH0TXD);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0TXD2, BRSHW_PORT_CONF_ETH0TXD);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0TXD3, BRSHW_PORT_CONF_ETH0TXD);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0TXEN, BRSHW_PORT_CONF_ETH0TXEN);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0TXERR, BRSHW_PORT_CONF_ETH0TXERR);

  BrsHwInitPortInput(BRSHW_PORT_ETH0RXCLK);
  BrsHwInitPortInput(BRSHW_PORT_ETH0RXD0);
  BrsHwInitPortInput(BRSHW_PORT_ETH0RXD1);
  BrsHwInitPortInput(BRSHW_PORT_ETH0RXD2);
  BrsHwInitPortInput(BRSHW_PORT_ETH0RXD3);
  BrsHwInitPortInput(BRSHW_PORT_ETH0RXDV);
  BrsHwInitPortInput(BRSHW_PORT_ETH0RXERR);
  BrsHwInitPortInput(BRSHW_PORT_ETH0CRS);
  BrsHwInitPortInput(BRSHW_PORT_ETH0COL);

  BrsHwInitPortInput(BRSHW_PORT_ETH0MDIO);
  BrsHwInitPortOutput(BRSHW_PORT_ETH0MDC);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0MDIO, BRSHW_PORT_CONF_ETH0MDIO);
  BrsHwInitPortConfig(BRSHW_PORT_ETH0MDC, BRSHW_PORT_CONF_ETH0MDC);

#if defined (BRSHW_PORT_ETH0_RESET)
  BrsHwInitPortOutput(BRSHW_PORT_ETH0RESET);

  BRSHWNOP10();

  BrsHwPort_SetLevel(BRSHW_PORT_ETH0RESET, BRSHW_PORT_LOGIC_HIGH);
#endif
#endif

#endif
}

void BrsHwDisableInterruptAtPowerOn(void){
  bBrsHwIntDiCounter = 0;
  ___asm(di);
}

void BrsHwEnableInterruptAtPowerOn(void){
  ___asm(ei);
}

unsigned int BrsHwReadPsw(void);

___asm(_BrsHwReadPsw:)

  __as1(stsr 5,r10)

  ___asm(jmp    [lp])

void BrsHwDisableInterrupt(void){
  unsigned int bLocalBrsHwRegisterPSW;

  if(bBrsHwIntDiCounter == 0){
    bLocalBrsHwRegisterPSW = BrsHwReadPsw();
      ___asm(di);
    if((bLocalBrsHwRegisterPSW&0x20)==0){
    }

    bBrsHwRegisterPSW=bLocalBrsHwRegisterPSW;
  }

  bBrsHwIntDiCounter++;
}

void BrsHwRestoreInterrupt(void){
  if(bBrsHwIntDiCounter == 0){
  }

  bBrsHwIntDiCounter--;
  if(bBrsHwIntDiCounter == 0){
    if((bBrsHwRegisterPSW&0x20)==0){
       ___asm(ei);
    }
  }
}

void BrsHwSoftwareResetECU(void){
  BrsHwDisableInterrupt();

#if defined (BRSHW_RESET_GROUP_A)

  FBL_RESFC = 0x000007ffu;

  PROT_WRITE0(SWRESA,0x1);
  while(SWRESA!=0x1);

#elif defined (BRSHW_RESET_GROUP_B)
  PROT_WRITE1(SWRESA,0x1);

#elif defined (BRSHW_RESET_GROUP_C)
  SWSRESA0 = 0x1;
#endif

  while(1){
  }
}

#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
#if defined (BRS_ENABLE_FBL_SUPPORT)
#define BRS_START_SEC_RAM_CODE
#include "Brs_MemMap.hpp"
#endif

void BrsHwTogglePin(brsHw_TogglePin Pin){
#if defined (VGEN_ENABLE_DRVDIO)
#error "Configure the valid DioChannel for the toggle pins within your DrvDio config and set it as value for BrsHw_Dio_ToggleX_Channel. Or disable the depending BRS mechanism."*/
#if defined (BRS_ENABLE_SUPPORT_LEDS)
  Dio_ChannelType BrsHw_Dio_ToggleLED_Channel = DioConf_DioChannel_DioChannel_LED;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  static Dio_ChannelType BrsHw_Dio_ToggleWD_Channel = DioConf_DioChannel_DioChannel_WD;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  static Dio_ChannelType BrsHw_Dio_ToggleCUSTOM_Channel = DioConf_DioChannel_DioChannel_CUSTOM;
#endif
#endif

#if defined (BRS_ENABLE_SUPPORT_LEDS)
  static uint8 BrsHw_ToggleSwitch_LED = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  static uint8 BrsHw_ToggleSwitch_WD = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  static uint8 BrsHw_ToggleSwitch_CUSTOM = BRSHW_PORT_LOGIC_HIGH;
#endif

  switch(Pin){
#if defined (BRS_ENABLE_SUPPORT_LEDS)
    case BRSHW_TOGGLEPIN_LED:
#if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleLED_Channel, BrsHw_ToggleSwitch_LED & 0x01);
#else
      BrsHwPort_SetLevel(BRSHW_PORT_LED, BrsHw_ToggleSwitch_LED & 0x01);
#endif
      BrsHw_ToggleSwitch_LED++;
      break;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
    case BRSHW_TOGGLEPIN_WD:
#if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleWD_Channel, BrsHw_ToggleSwitch_WD & 0x01);
#else
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_WD, BrsHw_ToggleSwitch_WD & 0x01);
#endif
      BrsHw_ToggleSwitch_WD++;
      break;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
    case BRSHW_TOGGLEPIN_CUSTOM:
#if defined (VGEN_ENABLE_DRVDIO)
      Dio_WriteChannel(BrsHw_Dio_ToggleCUSTOM_Channel, BrsHw_ToggleSwitch_CUSTOM & 0x01);
#else
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_CUSTOM, BrsHw_ToggleSwitch_CUSTOM & 0x01);
#endif
      BrsHw_ToggleSwitch_CUSTOM++;
      break;
#endif
    default:
      break;
  }
}
#if defined (BRS_ENABLE_FBL_SUPPORT)
#define BRS_STOP_SEC_RAM_CODE
#include "Brs_MemMap.hpp"
#endif
#endif

void BrsHwTime100NOP(void){
  BrsHwDisableInterrupt();

  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();
  BRSHWNOP10();

  BrsHwRestoreInterrupt();
}

#if defined (BRSASR_ENABLE_SAFECTXSUPPORT)

void BrsHw_EnableHwAccess(void){
}
#else

#endif

#if defined (BRS_ENABLE_FBL_SUPPORT)

void BrsHwSetVfp (void){
  do
  {
    PROT_WRITE_VFP(FLMDCNT, 0x01);
  } while((FLMDPS & 0x01) == 0x01);
}

void BrsHwResetVfp (void){
  do
  {
    PROT_WRITE_VFP(FLMDCNT, 0x00);
  } while((FLMDPS & 0x01) == 0x01);
}
#endif

#if !defined (BRS_ENABLE_FBL_SUPPORT)

BRS_ISR_KEYWORD void BrsHW_core_exception_handler(void){
  BrsMainExceptionHandler(kBrsInterruptHandlerNotInstalled, BRSERROR_MODULE_BRSHW, (uint16)0);
}

#endif
