

#ifndef _BRSHW_DERIVATIVELIST_H_
#define _BRSHW_DERIVATIVELIST_H_

#if defined (BRS_DERIVATIVE_701006) || \
    defined (BRS_DERIVATIVE_701010) || \
    defined (BRS_DERIVATIVE_701012) || \
    defined (BRS_DERIVATIVE_701013) || \
    defined (BRS_DERIVATIVE_701014) || \
    defined (BRS_DERIVATIVE_701015) || \
    defined (BRS_DERIVATIVE_701018) || \
    defined (BRS_DERIVATIVE_701019) || \
    defined (BRS_DERIVATIVE_701020) || \
    defined (BRS_DERIVATIVE_701022) || \
    defined (BRS_DERIVATIVE_701023) || \
    defined (BRS_DERIVATIVE_701024) || \
    defined (BRS_DERIVATIVE_701025) || \
    defined (BRS_DERIVATIVE_701026) || \
    defined (BRS_DERIVATIVE_701027) || \
    defined (BRS_DERIVATIVE_701028) || \
    defined (BRS_DERIVATIVE_701029) || \
    defined (BRS_DERIVATIVE_701030) || \
    defined (BRS_DERIVATIVE_701031) || \
    defined (BRS_DERIVATIVE_701035)  || \
    defined (BRS_DERIVATIVE_701044) || \
    defined (BRS_DERIVATIVE_701045)
#define BRSHW_CPU_MAX_FREQUENCY     80
#define BRSHW_INTERRUPT_TABLE_GROUP_A
#define BRSHW_PLL_GROUP_A
#define BRSHW_CLOCK_GROUP_A
#define BRSHW_TIMER_GROUP_A        0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701003) || \
      defined (BRS_DERIVATIVE_701043) || \
      defined (BRS_DERIVATIVE_701049) || \
      defined (BRS_DERIVATIVE_701053) || \
      defined (BRS_DERIVATIVE_701054) || \
      defined (BRS_DERIVATIVE_701057)
#define BRSHW_CPU_MAX_FREQUENCY     96
#define BRSHW_INTERRUPT_TABLE_GROUP_A
#define BRSHW_PLL_GROUP_A
#define BRSHW_CLOCK_GROUP_A
#define BRSHW_TIMER_GROUP_A        0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701544) || \
      defined (BRS_DERIVATIVE_701545) || \
      defined (BRS_DERIVATIVE_701548) || \
      defined (BRS_DERIVATIVE_701549) || \
      defined (BRS_DERIVATIVE_701564) || \
      defined (BRS_DERIVATIVE_701565) || \
      defined (BRS_DERIVATIVE_701569) || \
      defined (BRS_DERIVATIVE_701552) || \
      defined (BRS_DERIVATIVE_701568)
#define BRSHW_CPU_MAX_FREQUENCY     120
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A1
#define BRSHW_CLOCK_GROUP_A
#define BRSHW_TIMER_GROUP_A        0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701501) || \
      defined (BRS_DERIVATIVE_701502) || \
      defined (BRS_DERIVATIVE_701503) || \
      defined (BRS_DERIVATIVE_701507) || \
      defined (BRS_DERIVATIVE_701522) || \
      defined (BRS_DERIVATIVE_701527) || \
      defined (BRS_DERIVATIVE_701529) || \
      defined (BRS_DERIVATIVE_701530) || \
      defined (BRS_DERIVATIVE_701531) || \
      defined (BRS_DERIVATIVE_701534)
#define BRSHW_CPU_MAX_FREQUENCY     120
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A1
#define BRSHW_CLOCK_GROUP_A
#define BRSHW_TIMER_GROUP_A        0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701562) || \
      defined (BRS_DERIVATIVE_701567) || \
      defined (BRS_DERIVATIVE_701577) || \
      defined (BRS_DERIVATIVE_701580) || \
      defined (BRS_DERIVATIVE_701581) || \
      defined (BRS_DERIVATIVE_701582) || \
      defined (BRS_DERIVATIVE_701583) || \
      defined (BRS_DERIVATIVE_701587) || \
      defined (BRS_DERIVATIVE_701620) || \
      defined (BRS_DERIVATIVE_701621) || \
      defined (BRS_DERIVATIVE_701623)
#define BRSHW_CPU_MAX_FREQUENCY     120
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A3
#define BRSHW_CLOCK_GROUP_A2
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701602)
#define BRSHW_CPU_MAX_FREQUENCY     80
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A3
#define BRSHW_CLOCK_GROUP_A2
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701684) || \
      defined (BRS_DERIVATIVE_701686) || \
      defined (BRS_DERIVATIVE_701689) || \
      defined (BRS_DERIVATIVE_701692)
#define BRSHW_CPU_MAX_FREQUENCY     120
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A3
#define BRSHW_CLOCK_GROUP_A2
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701649) || \
      defined (BRS_DERIVATIVE_701647)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A4
#define BRSHW_CLOCK_GROUP_A2
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701638)
#define BRSHW_CPU_MAX_FREQUENCY     160
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A4
#define BRSHW_CLOCK_GROUP_A2
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701708) || \
      defined (BRS_DERIVATIVE_701709) || \
      defined (BRS_DERIVATIVE_701711)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_C
#define BRSHW_PLL_GROUP_A4
#define BRSHW_CLOCK_GROUP_A2
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701062) || \
      defined (BRS_DERIVATIVE_701064) || \
      defined (BRS_DERIVATIVE_701070)
#define BRSHW_CPU_MAX_FREQUENCY     96
#define BRSHW_INTERRUPT_TABLE_GROUP_A
#define BRSHW_PLL_GROUP_A
#define BRSHW_CLOCK_GROUP_A
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_A
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701307) || \
      defined (BRS_DERIVATIVE_701310) || \
      defined (BRS_DERIVATIVE_701311) || \
      defined (BRS_DERIVATIVE_701312) || \
      defined (BRS_DERIVATIVE_701318) || \
      defined (BRS_DERIVATIVE_701320) || \
      defined (BRS_DERIVATIVE_701364)
#define BRSHW_CPU_MAX_FREQUENCY     160
#define BRSHW_INTERRUPT_TABLE_GROUP_B
#define BRSHW_PLL_GROUP_B
#define BRSHW_CLOCK_GROUP_B
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_B
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701378) || \
      defined (BRS_DERIVATIVE_701383) || \
      defined (BRS_DERIVATIVE_701381)
#define BRSHW_CPU_MAX_FREQUENCY     160
#define BRSHW_INTERRUPT_TABLE_GROUP_B
#define BRSHW_PLL_GROUP_B
#define BRSHW_CLOCK_GROUP_B
#define BRSHW_TIMER_GROUP_A       0xFFE20000
#define BRSHW_PORT_GROUP_B
#define BRSHW_PROTECTION_GROUP_NONE
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_C

#elif defined (BRS_DERIVATIVE_701373)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_G
#define BRSHW_PLL_GROUP_D
#define BRSHW_CLOCK_GROUP_D
#define BRSHW_TIMER_GROUP_C       0xFFDD8000
#define BRSHW_PORT_GROUP_B2
#define BRSHW_PROTECTION_GROUP_NONE
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_POWER_DOWN_MODES
#define BRSHW_RESET_GROUP_C

#elif defined (BRS_DERIVATIVE_701325) || \
      defined (BRS_DERIVATIVE_701327) || \
      defined (BRS_DERIVATIVE_701371) || \
      defined (BRS_DERIVATIVE_701372)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_G
#define BRSHW_PLL_GROUP_D
#define BRSHW_CLOCK_GROUP_D
#define BRSHW_TIMER_GROUP_C       0xFFDD8000
#define BRSHW_PORT_GROUP_B2
#define BRSHW_PROTECTION_GROUP_NONE
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_POWER_DOWN_MODES
#define BRSHW_RESET_GROUP_C

#elif defined (BRS_DERIVATIVE_701391)
#define BRSHW_CPU_MAX_FREQUENCY     120
#define BRSHW_INTERRUPT_TABLE_GROUP_G
#define BRSHW_PLL_GROUP_E
#define BRSHW_CLOCK_GROUP_D
#define BRSHW_TIMER_GROUP_C       0xFFDD8000
#define BRSHW_PORT_GROUP_E
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_C

#elif defined (BRS_DERIVATIVE_701400) || \
      defined (BRS_DERIVATIVE_701401) || \
      defined (BRS_DERIVATIVE_701402) || \
      defined (BRS_DERIVATIVE_701403)
#define BRSHW_CPU_MAX_FREQUENCY     120
#define BRSHW_INTERRUPT_TABLE_GROUP_D
#define BRSHW_PLL_GROUP_A2
#define BRSHW_CLOCK_GROUP_A1
#define BRSHW_TIMER_GROUP_A       0xFFE30000
#define BRSHW_PORT_GROUP_C
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701416)
#define BRSHW_CPU_MAX_FREQUENCY     120
#define BRSHW_INTERRUPT_TABLE_GROUP_D
#define BRSHW_PLL_GROUP_A2
#define BRSHW_CLOCK_GROUP_A1
#define BRSHW_TIMER_GROUP_A       0xFFE30000
#define BRSHW_PORT_GROUP_C
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701404) || \
      defined (BRS_DERIVATIVE_701405) || \
      defined (BRS_DERIVATIVE_701442) || \
      defined (BRS_DERIVATIVE_701462)
#define BRSHW_CPU_MAX_FREQUENCY     160
#define BRSHW_INTERRUPT_TABLE_GROUP_D
#define BRSHW_PLL_GROUP_A2
#define BRSHW_CLOCK_GROUP_A1
#define BRSHW_TIMER_GROUP_A       0xFFE30000
#define BRSHW_PORT_GROUP_C
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701406) || \
      defined (BRS_DERIVATIVE_701407)
#define BRSHW_CPU_MAX_FREQUENCY     200
#define BRSHW_INTERRUPT_TABLE_GROUP_D
#define BRSHW_PLL_GROUP_A2
#define BRSHW_CLOCK_GROUP_A1
#define BRSHW_TIMER_GROUP_A       0xFFE30000
#define BRSHW_PORT_GROUP_C
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701408) || \
      defined (BRS_DERIVATIVE_701412) || \
      defined (BRS_DERIVATIVE_701428) || \
      defined (BRS_DERIVATIVE_701441) || \
      defined (BRS_DERIVATIVE_701461)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_D
#define BRSHW_PLL_GROUP_A2
#define BRSHW_CLOCK_GROUP_A1
#define BRSHW_TIMER_GROUP_A       0xFFE30000
#define BRSHW_PORT_GROUP_C
#define BRSHW_PROTECTION_GROUP_A
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#define BRSHW_RESET_GROUP_A

#elif defined (BRS_DERIVATIVE_701201)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_E
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_B
#define BRSHW_PORT_GROUP_D
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701205)
#define BRSHW_CPU_MAX_FREQUENCY     160
#define BRSHW_INTERRUPT_TABLE_GROUP_E
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_B
#define BRSHW_PORT_GROUP_D
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701202) || \
      defined (BRS_DERIVATIVE_701216)
#define BRSHW_CPU_MAX_FREQUENCY     320
#define BRSHW_INTERRUPT_TABLE_GROUP_E
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_B
#define BRSHW_PORT_GROUP_D
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701204)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_E
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_B
#define BRSHW_PORT_GROUP_D
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701Z11)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_E
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_B
#define BRSHW_PORT_GROUP_D
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701Z12)
#define BRSHW_CPU_MAX_FREQUENCY     320
#define BRSHW_INTERRUPT_TABLE_GROUP_E
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_B
#define BRSHW_PORT_GROUP_D
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701260) || \
      defined (BRS_DERIVATIVE_701263) || \
      defined (BRS_DERIVATIVE_701270)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_F
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_A      0xFFE20000
#define BRSHW_PORT_GROUP_B1
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#elif defined (BRS_DERIVATIVE_701276)
#define BRSHW_CPU_MAX_FREQUENCY     240
#define BRSHW_INTERRUPT_TABLE_GROUP_H
#define BRSHW_PLL_GROUP_C
#define BRSHW_CLOCK_GROUP_C
#define BRSHW_TIMER_GROUP_A      0xFFE20000
#define BRSHW_PORT_GROUP_B1
#define BRSHW_PROTECTION_GROUP_B
#define BRSHW_RESET_GROUP_B

#else
#error "Configured derivative (Makefile.config) not yet supported"
#endif

#endif
