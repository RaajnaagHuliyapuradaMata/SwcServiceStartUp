

#ifndef _BRSHW_ISRDEF_H_
#define _BRSHW_ISRDEF_H_

#if defined(C_ENABLE_SLEEP_WAKEUP) && defined(C_ENABLE_BUSWAKEUP_SUPPORT)
#define BRSHW_ENABLE_CAN_WAKEUP_FILTER
#endif
#if !defined(C_ENABLE_WAKEUP_POLLING) && defined(BRSHW_ENABLE_CAN_WAKEUP_FILTER)
#define BRSHW_ENABLE_CAN_WAKEUP_ISR
#endif

#if defined (VGEN_ENABLE_LIN_DRV)

#if !defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#if defined (LIN_USE_THREE_INT_SOURCES) || defined (SIO_USE_THREE_INT_SOURCES)
#define BRSHW_LIN_USE_THREE_INT_SOURCES
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_0)
#define BRSHW_ISR_RLIN240_0 BRS_ISR_DEFINE(LinIsr_2_0)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_0)
#define BRSHW_ISR_RLIN240_0 BRS_ISR_DEFINE(LinIsr_240_0)
# elif defined (SIO_ENABLE_RLIN2_0)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN240_0 BRS_ISR_DEFINE(l_ifc_rx_2_0)
#else
#define BRSHW_ISR_RLIN240_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_1)
#define BRSHW_ISR_RLIN240_1 BRS_ISR_DEFINE(LinIsr_2_1)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_1)
#define BRSHW_ISR_RLIN240_1 BRS_ISR_DEFINE(LinIsr_240_1)
# elif defined (SIO_ENABLE_RLIN2_1)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN240_1 BRS_ISR_DEFINE(l_ifc_rx_2_1)
#else
#define BRSHW_ISR_RLIN240_1 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_2)
#define BRSHW_ISR_RLIN240_2 BRS_ISR_DEFINE(LinIsr_2_2)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_2)
#define BRSHW_ISR_RLIN240_2 BRS_ISR_DEFINE(LinIsr_240_2)
# elif defined (SIO_ENABLE_RLIN2_2)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN240_2 BRS_ISR_DEFINE(l_ifc_rx_2_2)
#else
#define BRSHW_ISR_RLIN240_2 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_3)
#define BRSHW_ISR_RLIN240_3 BRS_ISR_DEFINE(LinIsr_2_3)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_3)
#define BRSHW_ISR_RLIN240_3 BRS_ISR_DEFINE(LinIsr_240_3)
# elif defined (SIO_ENABLE_RLIN2_3)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN240_3 BRS_ISR_DEFINE(l_ifc_rx_2_3)
#else
#define BRSHW_ISR_RLIN240_3 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_4)
#define BRSHW_ISR_RLIN241_0 BRS_ISR_DEFINE(LinIsr_2_4)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN240_0)
#define BRSHW_ISR_RLIN241_0 BRS_ISR_DEFINE(LinIsr_240_0)
# elif defined (SIO_ENABLE_RLIN2_4)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN241_0 BRS_ISR_DEFINE(l_ifc_rx_2_4)
#else
#define BRSHW_ISR_RLIN241_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_5)
#define BRSHW_ISR_RLIN241_1 BRS_ISR_DEFINE(LinIsr_2_5)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN241_1)
#define BRSHW_ISR_RLIN241_1 BRS_ISR_DEFINE(LinIsr_241_1)
# elif defined (SIO_ENABLE_RLIN2_5)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN241_1 BRS_ISR_DEFINE(l_ifc_rx_2_5)
#else
#define BRSHW_ISR_RLIN241_1 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_6)
#define BRSHW_ISR_RLIN241_2 BRS_ISR_DEFINE(LinIsr_2_6)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN241_2)
#define BRSHW_ISR_RLIN241_2 BRS_ISR_DEFINE(LinIsr_241_2)
# elif defined (SIO_ENABLE_RLIN2_6)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN241_2 BRS_ISR_DEFINE(l_ifc_rx_2_6)
#else
#define BRSHW_ISR_RLIN241_2 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_7)
#define BRSHW_ISR_RLIN241_3 BRS_ISR_DEFINE(LinIsr_2_7)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN241_3)
#define BRSHW_ISR_RLIN241_3 BRS_ISR_DEFINE(LinIsr_241_3)
# elif defined (SIO_ENABLE_RLIN2_7)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN241_3 BRS_ISR_DEFINE(l_ifc_rx_2_7)
#else
#define BRSHW_ISR_RLIN241_3 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_8)
#define BRSHW_ISR_RLIN242_0 BRS_ISR_DEFINE(LinIsr_2_8)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN210_0)
#define BRSHW_ISR_RLIN242_0 BRS_ISR_DEFINE(LinIsr_210_0)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN242_0)
#define BRSHW_ISR_RLIN242_0 BRS_ISR_DEFINE(LinIsr_242_0)
# elif defined (SIO_ENABLE_RLIN2_8)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN242_0 BRS_ISR_DEFINE(l_ifc_rx_2_8)
#else
#define BRSHW_ISR_RLIN242_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_9)
#define BRSHW_ISR_RLIN242_1 BRS_ISR_DEFINE(LinIsr_2_9)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN211_0)
#define BRSHW_ISR_RLIN242_1 BRS_ISR_DEFINE(LinIsr_211_0)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN242_1)
#define BRSHW_ISR_RLIN242_1 BRS_ISR_DEFINE(LinIsr_242_1)
# elif defined (SIO_ENABLE_RLIN2_9)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN242_1 BRS_ISR_DEFINE(l_ifc_rx_2_9)
#else
#define BRSHW_ISR_RLIN242_1 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_10)
#define BRSHW_ISR_RLIN242_2 BRS_ISR_DEFINE(LinIsr_2_10)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN212_0)
#define BRSHW_ISR_RLIN242_2 BRS_ISR_DEFINE(LinIsr_212_0)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN242_2)
#define BRSHW_ISR_RLIN242_2 BRS_ISR_DEFINE(LinIsr_242_2)
# elif defined (SIO_ENABLE_RLIN2_10)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN242_2 BRS_ISR_DEFINE(l_ifc_rx_2_10)
#else
#define BRSHW_ISR_RLIN242_2 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN2_11)
#define BRSHW_ISR_RLIN242_3 BRS_ISR_DEFINE(LinIsr_2_11)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN213_0)
#define BRSHW_ISR_RLIN242_3 BRS_ISR_DEFINE(LinIsr_213_0)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN242_3)
#define BRSHW_ISR_RLIN242_3 BRS_ISR_DEFINE(LinIsr_242_3)
# elif defined (SIO_ENABLE_RLIN2_11)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN242_3 BRS_ISR_DEFINE(l_ifc_rx_2_11)
#else
#define BRSHW_ISR_RLIN242_3 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_0)
#define BRSHW_ISR_RLIN30_0 BRS_ISR_DEFINE(LinIsr_3_0)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN30_0)
#define BRSHW_ISR_RLIN30_0 BRS_ISR_DEFINE(LinIsr_30_0)
# elif defined (SIO_ENABLE_RLIN3_0)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN30_0 BRS_ISR_DEFINE(l_ifc_rx_3_0)
#else
#define BRSHW_ISR_RLIN30_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_1)
#define BRSHW_ISR_RLIN31_0 BRS_ISR_DEFINE(LinIsr_3_1)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN31_0)
#define BRSHW_ISR_RLIN31_0 BRS_ISR_DEFINE(LinIsr_31_0)
# elif defined (SIO_ENABLE_RLIN3_1)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN31_0 BRS_ISR_DEFINE(l_ifc_rx_3_1)
#else
#define BRSHW_ISR_RLIN31_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_2)
#define BRSHW_ISR_RLIN32_0 BRS_ISR_DEFINE(LinIsr_3_2)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN32_0)
#define BRSHW_ISR_RLIN32_0 BRS_ISR_DEFINE(LinIsr_32_0)
# elif defined (SIO_ENABLE_RLIN3_2)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN32_0 BRS_ISR_DEFINE(l_ifc_rx_3_2)
#else
#define BRSHW_ISR_RLIN32_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_3)
#define BRSHW_ISR_RLIN33_0 BRS_ISR_DEFINE(LinIsr_3_3)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN33_0)
#define BRSHW_ISR_RLIN33_0 BRS_ISR_DEFINE(LinIsr_33_0)
# elif defined (SIO_ENABLE_RLIN3_3)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN33_0 BRS_ISR_DEFINE(l_ifc_rx_3_3)
#else
#define BRSHW_ISR_RLIN33_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_4)
#define BRSHW_ISR_RLIN34_0 BRS_ISR_DEFINE(LinIsr_3_4)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN34_0)
#define BRSHW_ISR_RLIN34_0 BRS_ISR_DEFINE(LinIsr_34_0)
# elif defined (SIO_ENABLE_RLIN3_4)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN34_0 BRS_ISR_DEFINE(l_ifc_rx_3_4)
#else
#define BRSHW_ISR_RLIN34_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif

#if defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN3_5)
#define BRSHW_ISR_RLIN35_0 BRS_ISR_DEFINE(LinIsr_3_5)
# elif defined (LIN_ENABLE_HARDWARE_INTERFACE_RLIN35_0)
#define BRSHW_ISR_RLIN35_0 BRS_ISR_DEFINE(LinIsr_35_0)
# elif defined (SIO_ENABLE_RLIN3_5)
#if defined (SIO_ECUTYPE_MASTER)
#define BRSHW_ISR_RLIN35_0 BRS_ISR_DEFINE(l_ifc_rx_3_5)
#else
#define BRSHW_ISR_RLIN35_0 BRS_ISR_DEFINE(l_ifc_rx)
#endif
#endif
#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_A)

#if defined(VGEN_ENABLE_CAN_DRV)

#if !defined (C_ENABLE_ERROR_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_OVERRUN)
#define BrsDummyInterrupt568 BRS_ISR_DEFINE(CanIsrGlobalStatus)
#endif
#if(!defined(C_ENABLE_RX_BASICCAN_POLLING ) || defined(C_ENABLE_INDIVIDUAL_POLLING)) && defined(C_ENABLE_RX_BASICCAN_OBJECTS)
#define BrsDummyInterrupt572 BRS_ISR_DEFINE(CanIsrRxFifo)
#endif

#if defined (kCanPhysToLogChannelIndex_0)
#if !defined(C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt576 BRS_ISR_DEFINE(CanIsrStatus_0)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt584 BRS_ISR_DEFINE(CanIsrTx_0)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt628 BRS_ISR_DEFINE(CanIsrWakeup_0)
#endif
#endif

#if defined( kCanPhysToLogChannelIndex_1 )
#if !defined(C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt932 BRS_ISR_DEFINE(CanIsrStatus_1)
#endif
#if !defined(C_ENABLE_TX_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt940 BRS_ISR_DEFINE(CanIsrTx_1)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt632 BRS_ISR_DEFINE(CanIsrWakeup_1)
#endif
#endif

#if defined( kCanPhysToLogChannelIndex_2 )
#if !defined(C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1348 BRS_ISR_DEFINE(CanIsrStatus_2)
#endif
#if !defined(C_ENABLE_TX_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1356 BRS_ISR_DEFINE(CanIsrTx_2)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt636 BRS_ISR_DEFINE(CanIsrWakeup_2)
#endif
#endif

#if defined( kCanPhysToLogChannelIndex_3 )
#if !defined(C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1360 BRS_ISR_DEFINE(CanIsrStatus_3)
#endif
#if !defined(C_ENABLE_TX_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1368 BRS_ISR_DEFINE(CanIsrTx_3)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt648 BRS_ISR_DEFINE(CanIsrWakeup_3)
#endif
#endif

#if defined( kCanPhysToLogChannelIndex_4 )
#if !defined(C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1568 BRS_ISR_DEFINE(CanIsrStatus_4)
#endif
#if !defined(C_ENABLE_TX_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1576 BRS_ISR_DEFINE(CanIsrTx_4)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt652 BRS_ISR_DEFINE(CanIsrWakeup_4)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_5)
#if !defined(C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1628 BRS_ISR_DEFINE(CanIsrStatus_5)
#endif
#if !defined(C_ENABLE_TX_POLLING) || defined(C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1636 BRS_ISR_DEFINE(CanIsrTx_5)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt656 BRS_ISR_DEFINE(CanIsrWakeup_5)
#endif
#endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_ISR_RLIN240_0)
#define BrsDummyInterrupt712  BRSHW_ISR_RLIN240_0
#endif

#if defined (BRSHW_ISR_RLIN240_1)
#define BrsDummyInterrupt716  BRSHW_ISR_RLIN240_1
#endif

#if defined (BRSHW_ISR_RLIN240_2)
#define BrsDummyInterrupt1128 BRSHW_ISR_RLIN240_2
#endif

#if defined (BRSHW_ISR_RLIN240_3)
#define BrsDummyInterrupt1132 BRSHW_ISR_RLIN240_3
#endif

#if defined (BRSHW_ISR_RLIN241_0)
#define BrsDummyInterrupt1384 BRSHW_ISR_RLIN241_0
#endif

#if defined (BRSHW_ISR_RLIN241_1)
#define BrsDummyInterrupt1388 BRSHW_ISR_RLIN241_1
#endif

#if defined (BRSHW_ISR_RLIN241_2)
#define BrsDummyInterrupt1580 BRSHW_ISR_RLIN241_2
#endif

#if defined (BRSHW_ISR_RLIN241_3)
#define BrsDummyInterrupt1584 BRSHW_ISR_RLIN241_3
#endif

#if defined (BRSHW_ISR_RLIN242_0)
#define BrsDummyInterrupt1620 BRSHW_ISR_RLIN242_0
#endif

#if defined (BRSHW_ISR_RLIN242_1)
#define BrsDummyInterrupt1624 BRSHW_ISR_RLIN242_1
#endif

#if defined (BRSHW_ISR_RLIN30_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt616 BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt620 BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt624 BRSHW_ISR_RLIN30_0
#   else
#define BrsDummyInterrupt612 BRSHW_ISR_RLIN30_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN31_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt964 BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt968 BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt972 BRSHW_ISR_RLIN31_0
#   else
#define BrsDummyInterrupt960 BRSHW_ISR_RLIN31_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN32_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1140 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt1144 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt1148 BRSHW_ISR_RLIN32_0
#   else
#define BrsDummyInterrupt1136 BRSHW_ISR_RLIN32_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN33_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1396 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt1400 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt1404 BRSHW_ISR_RLIN33_0
#   else
#define BrsDummyInterrupt1392 BRSHW_ISR_RLIN33_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN34_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1412 BRSHW_ISR_RLIN34_0
#define BrsDummyInterrupt1416 BRSHW_ISR_RLIN34_0
#define BrsDummyInterrupt1420 BRSHW_ISR_RLIN34_0
#   else
#define BrsDummyInterrupt1408 BRSHW_ISR_RLIN34_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN35_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1428 BRSHW_ISR_RLIN35_0
#define BrsDummyInterrupt1432 BRSHW_ISR_RLIN35_0
#define BrsDummyInterrupt1436 BRSHW_ISR_RLIN35_0
#   else
#define BrsDummyInterrupt1424 BRSHW_ISR_RLIN35_0
#endif
#endif
#endif

#define BrsDummyInterrupt512 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)
#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_B)

#if defined (VGEN_ENABLE_CAN_DRV)

#if !defined (C_ENABLE_ERROR_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_OVERRUN)
#define BrsDummyInterrupt1268 BRS_ISR_DEFINE(CanIsrGlobalStatus)
#endif
#if(!defined (C_ENABLE_RX_BASICCAN_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)
#define BrsDummyInterrupt1272 BRS_ISR_DEFINE(CanIsrRxFifo)
#endif

#if defined (kCanPhysToLogChannelIndex_0)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1244 BRS_ISR_DEFINE(CanIsrStatus_0)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1252 BRS_ISR_DEFINE(CanIsrTx_0)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt1024 BRS_ISR_DEFINE(CanIsrWakeup_0)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1256 BRS_ISR_DEFINE(CanIsrStatus_1)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1264 BRS_ISR_DEFINE(CanIsrTx_1)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt1028 BRS_ISR_DEFINE(CanIsrWakeup_1)
#endif
#endif
#endif

#if defined(VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_ISR_RLIN30_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt968  BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt972  BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt976  BRSHW_ISR_RLIN30_0
#else
#error "P1M works only with 3 LIN interrupt sources"
#endif
#endif

#if defined (BRSHW_ISR_RLIN31_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt980  BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt984  BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt988  BRSHW_ISR_RLIN31_0
#else
#error "P1M works only with 3 LIN interrupt sources"
#endif
#endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
#if(FR_CFG_STATUS_ISR_LINE == 0)
#define BrsDummyInterrupt1288  BRS_ISR_DEFINE(Fr_IrqLine0)
#else
#define BrsDummyInterrupt1292  BRS_ISR_DEFINE(Fr_IrqLine1)
#endif

#define BrsDummyInterrupt1296    BRS_ISR_DEFINE(Fr_IrqTimer0)

#if(FR_RELATIVE_TIMER_ENABLE == STD_ON)
#define BrsDummyInterrupt1300  BRS_ISR_DEFINE(Fr_IrqTimer1)
#endif
#endif

#define BrsDummyInterrupt1076 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)

#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_C)

#if defined (VGEN_ENABLE_CAN_DRV)

#if !defined (C_ENABLE_ERROR_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_OVERRUN)
#define BrsDummyInterrupt600 BRS_ISR_DEFINE(CanIsrGlobalStatus)
#endif
#if(!defined (C_ENABLE_RX_BASICCAN_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)
#define BrsDummyInterrupt604 BRS_ISR_DEFINE(CanIsrRxFifo)
#endif

#if defined (kCanPhysToLogChannelIndex_0)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt608 BRS_ISR_DEFINE(CanIsrStatus_0)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt616 BRS_ISR_DEFINE(CanIsrTx_0)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt660 BRS_ISR_DEFINE(CanIsrWakeup_0)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt964 BRS_ISR_DEFINE(CanIsrStatus_1)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt972 BRS_ISR_DEFINE(CanIsrTx_1)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt664 BRS_ISR_DEFINE(CanIsrWakeup_1)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_2)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1380 BRS_ISR_DEFINE(CanIsrStatus_2)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1388 BRS_ISR_DEFINE(CanIsrTx_2)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt668 BRS_ISR_DEFINE(CanIsrWakeup_2)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_3)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1392 BRS_ISR_DEFINE(CanIsrStatus_3)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1400 BRS_ISR_DEFINE(CanIsrTx_3)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt684 BRS_ISR_DEFINE(CanIsrWakeup_3)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_4)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1600 BRS_ISR_DEFINE(CanIsrStatus_4)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1608 BRS_ISR_DEFINE(CanIsrTx_4)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt688 BRS_ISR_DEFINE(CanIsrWakeup_4)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_5)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1660 BRS_ISR_DEFINE(CanIsrStatus_5)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1668 BRS_ISR_DEFINE(CanIsrTx_5)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt692 BRS_ISR_DEFINE(CanIsrWakeup_5)
#endif
#endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_ISR_RLIN240_0)
#define BrsDummyInterrupt744 BRSHW_ISR_RLIN240_0
#endif

#if defined (BRSHW_ISR_RLIN240_1)
#define BrsDummyInterrupt748 BRSHW_ISR_RLIN240_1
#endif

#if defined (BRSHW_ISR_RLIN240_2)
#define BrsDummyInterrupt1160 BRSHW_ISR_RLIN240_2
#endif

#if defined (BRSHW_ISR_RLIN240_3)
#define BrsDummyInterrupt1164 BRSHW_ISR_RLIN240_3
#endif

#if defined (BRSHW_ISR_RLIN241_0)
#define BrsDummyInterrupt1416 BRSHW_ISR_RLIN241_0
#endif

#if defined (BRSHW_ISR_RLIN241_1)
#define BrsDummyInterrupt1420 BRSHW_ISR_RLIN241_1
#endif

#if defined (BRSHW_ISR_RLIN241_2)
#define BrsDummyInterrupt1612 BRSHW_ISR_RLIN241_2
#endif

#if defined (BRSHW_ISR_RLIN241_3)
#define BrsDummyInterrupt1616 BRSHW_ISR_RLIN241_3
#endif

#if defined (BRSHW_ISR_RLIN242_0)
#define BrsDummyInterrupt1652 BRSHW_ISR_RLIN242_0
#endif

#if defined (BRSHW_ISR_RLIN242_1)
#define BrsDummyInterrupt1656 BRSHW_ISR_RLIN242_1
#endif

#if defined (BRSHW_ISR_RLIN242_2)
#define BrsDummyInterrupt1808 BRSHW_ISR_RLIN242_2
#endif

#if defined (BRSHW_ISR_RLIN242_3)
#define BrsDummyInterrupt1812 BRSHW_ISR_RLIN242_3
#endif

#if defined (BRSHW_ISR_RLIN30_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt648 BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt652 BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt656 BRSHW_ISR_RLIN30_0
#   else
#define BrsDummyInterrupt644 BRSHW_ISR_RLIN30_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN31_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt996 BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt1000 BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt1004 BRSHW_ISR_RLIN31_0
#   else
#define BrsDummyInterrupt992 BRSHW_ISR_RLIN31_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN32_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1172 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt1176 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt1180 BRSHW_ISR_RLIN32_0
#   else
#define BrsDummyInterrupt1168 BRSHW_ISR_RLIN32_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN33_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1428 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt1432 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt1436 BRSHW_ISR_RLIN33_0
#   else
#define BrsDummyInterrupt1424 BRSHW_ISR_RLIN33_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN34_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1444 BRSHW_ISR_RLIN34_0
#define BrsDummyInterrupt1448 BRSHW_ISR_RLIN34_0
#define BrsDummyInterrupt1452 BRSHW_ISR_RLIN34_0
#   else
#define BrsDummyInterrupt1440 BRSHW_ISR_RLIN34_0
#endif
#endif

#if defined (BRSHW_ISR_RLIN35_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1460 BRSHW_ISR_RLIN35_0
#define BrsDummyInterrupt1464 BRSHW_ISR_RLIN35_0
#define BrsDummyInterrupt1468 BRSHW_ISR_RLIN35_0
#   else
#define BrsDummyInterrupt1456 BRSHW_ISR_RLIN35_0
#endif
#endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
#if(FR_CFG_STATUS_ISR_LINE == 0)
#define BrsDummyInterrupt1228 BRS_ISR_DEFINE(Fr_IrqLine0)
#else
#define BrsDummyInterrupt1232 BRS_ISR_DEFINE(Fr_IrqLine1)
#endif

#define BrsDummyInterrupt1236 BRS_ISR_DEFINE(Fr_IrqTimer0)

#if(FR_RELATIVE_TIMER_ENABLE == STD_ON)
#define BrsDummyInterrupt1240 BRS_ISR_DEFINE(Fr_IrqTimer1)
#endif
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
#define BrsDummyInterrupt1772 BRS_ISR_DEFINE(EthIsr_0)
#endif

#define BrsDummyInterrupt544 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)

#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_D)

#if defined (VGEN_ENABLE_CAN_DRV)

#if !defined (C_ENABLE_ERROR_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_OVERRUN)
#define BrsDummyInterrupt788 BRS_ISR_DEFINE(CanIsrGlobalStatus)
#endif
#if(!defined (C_ENABLE_RX_BASICCAN_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)
#define BrsDummyInterrupt792 BRS_ISR_DEFINE(CanIsrRxFifo)
#endif

#if defined (kCanPhysToLogChannelIndex_0)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt796 BRS_ISR_DEFINE(CanIsrStatus_0)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt804 BRS_ISR_DEFINE(CanIsrTx_0)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt560 BRS_ISR_DEFINE(CanIsrWakeup_0)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt984 BRS_ISR_DEFINE(CanIsrStatus_1)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt992 BRS_ISR_DEFINE(CanIsrTx_1)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt568 BRS_ISR_DEFINE(CanIsrWakeup_1)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_2)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1232 BRS_ISR_DEFINE(CanIsrStatus_2)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1240 BRS_ISR_DEFINE(CanIsrTx_2)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt576 BRS_ISR_DEFINE(CanIsrWakeup_2)
#endif
#endif
#endif

#if defined(VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_ISR_RLIN30_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt836  BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt840  BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt844  BRSHW_ISR_RLIN30_0
#   else
#error "D1M works only with 3 LIN interrupt sources"
#endif
#endif

#if defined (BRSHW_ISR_RLIN31_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt848  BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt852  BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt856  BRSHW_ISR_RLIN31_0
#   else
#error "D1M works only with 3 LIN interrupt sources"
#endif
#endif

#if defined (BRSHW_ISR_RLIN32_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1372 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt1376 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt1380 BRSHW_ISR_RLIN32_0
#   else
#error "D1M works only with 3 LIN interrupt sources"
#endif
#endif

#if defined (BRSHW_ISR_RLIN33_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt1384 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt1388 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt1392 BRSHW_ISR_RLIN33_0
#   else
#error "D1M works only with 3 LIN interrupt sources"
#endif
#endif
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
#define BrsDummyInterrupt1488 BRS_ISR_DEFINE(EthIsr_0)
#endif

#define BrsDummyInterrupt580 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)

#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_E)

#if defined (VGEN_ENABLE_CAN_DRV)

#if !defined (C_ENABLE_ERROR_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_OVERRUN)
#define BrsDummyInterrupt2164 BRS_ISR_DEFINE(CanIsrGlobalStatus)
#endif
#if(!defined (C_ENABLE_RX_BASICCAN_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)
#define BrsDummyInterrupt2160 BRS_ISR_DEFINE(CanIsrRxFifo)
#endif

#if defined (kCanPhysToLogChannelIndex_0)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt2172 BRS_ISR_DEFINE(CanIsrStatus_0)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt2176 BRS_ISR_DEFINE(CanIsrTx_0)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt548 BRS_ISR_DEFINE(CanIsrWakeup_0)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt2184 BRS_ISR_DEFINE(CanIsrStatus_1)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt2188 BRS_ISR_DEFINE(CanIsrTx_1)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt552 BRS_ISR_DEFINE(CanIsrWakeup_1)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_2)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt2196 BRS_ISR_DEFINE(CanIsrStatus_2)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt2200 BRS_ISR_DEFINE(CanIsrTx_2)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt556 BRS_ISR_DEFINE(CanIsrWakeup_2)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_3)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt2208 BRS_ISR_DEFINE(CanIsrStatus_3)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt2212 BRS_ISR_DEFINE(CanIsrTx_3)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt560 BRS_ISR_DEFINE(CanIsrWakeup_3)
#endif
#endif
#endif

#if defined (VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_ISR_RLIN240_0)
#define BrsDummyInterrupt2228 BRSHW_ISR_RLIN240_0
#endif
#if defined (BRSHW_ISR_RLIN242_0)
#define BrsDummyInterrupt2228 BRSHW_ISR_RLIN242_0
#endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
#if(FR_CFG_STATUS_ISR_LINE == 0)
#define BrsDummyInterrupt2116 BRS_ISR_DEFINE(Fr_IrqLine0)
#else
#define BrsDummyInterrupt2120 BRS_ISR_DEFINE(Fr_IrqLine1)
#endif

#define BrsDummyInterrupt2124 BRS_ISR_DEFINE(Fr_IrqTimer0)

#if(FR_RELATIVE_TIMER_ENABLE == STD_ON)
#define BrsDummyInterrupt2128 BRS_ISR_DEFINE(Fr_IrqTimer1)
#endif
#endif

#define BrsDummyInterrupt824 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)

#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_F)

#if defined (VGEN_ENABLE_CAN_DRV)

#if !defined (C_ENABLE_ERROR_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_OVERRUN)
#define BrsDummyInterrupt1256 BRS_ISR_DEFINE(CanIsrGlobalStatus)
#endif
#if(!defined (C_ENABLE_RX_BASICCAN_POLLING ) || defined (C_ENABLE_INDIVIDUAL_POLLING)) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)
#define BrsDummyInterrupt1260 BRS_ISR_DEFINE(CanIsrRxFifo)
#endif

#if defined (kCanPhysToLogChannelIndex_0)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1268 BRS_ISR_DEFINE(CanIsrStatus_0)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1272 BRS_ISR_DEFINE(CanIsrTx_0)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1280 BRS_ISR_DEFINE(CanIsrStatus_1)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1284 BRS_ISR_DEFINE(CanIsrTx_1)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_2)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1292 BRS_ISR_DEFINE(CanIsrStatus_2)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1296 BRS_ISR_DEFINE(CanIsrTx_2)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_3)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1304 BRS_ISR_DEFINE(CanIsrStatus_3)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1308 BRS_ISR_DEFINE(CanIsrTx_3)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif
#endif

#if defined(VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_ISR_RLIN240_0)
#define BrsDummyInterrupt1312 BRSHW_ISR_RLIN240_0
#endif

#if defined (BRSHW_ISR_RLIN240_1)
#define BrsDummyInterrupt1316 BRSHW_ISR_RLIN240_1
#endif

#if defined (BRSHW_ISR_RLIN240_2)
#define BrsDummyInterrupt1320 BRSHW_ISR_RLIN240_2
#endif
#endif

#define BrsDummyInterrupt840 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)

#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_G)

#if defined (VGEN_ENABLE_CAN_DRV)

#if defined (kCanPhysToLogChannelIndex_0)
#define BrsDummyInterrupt1200 BRS_ISR_DEFINE(CanIsr_0)
#define BrsDummyInterrupt1204 BRS_ISR_DEFINE(CanIsr_0)
#define BrsDummyInterrupt1208 BRS_ISR_DEFINE(CanIsr_0)
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt644 BRS_ISR_DEFINE(CanIsrWakeup_0)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
#define BrsDummyInterrupt1212 BRS_ISR_DEFINE(CanIsr_1)
#define BrsDummyInterrupt1216 BRS_ISR_DEFINE(CanIsr_1)
#define BrsDummyInterrupt1220 BRS_ISR_DEFINE(CanIsr_1)
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt648 BRS_ISR_DEFINE(CanIsrWakeup_1)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_2)
#define BrsDummyInterrupt1224 BRS_ISR_DEFINE(CanIsr_2)
#define BrsDummyInterrupt1228 BRS_ISR_DEFINE(CanIsr_2)
#define BrsDummyInterrupt1232 BRS_ISR_DEFINE(CanIsr_2)
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt652 BRS_ISR_DEFINE(CanIsrWakeup_2)
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_3)
#define BrsDummyInterrupt1236 BRS_ISR_DEFINE(CanIsr_3)
#define BrsDummyInterrupt1240 BRS_ISR_DEFINE(CanIsr_3)
#define BrsDummyInterrupt1244 BRS_ISR_DEFINE(CanIsr_3)
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#define BrsDummyInterrupt656 BRS_ISR_DEFINE(CanIsrWakeup_3)
#endif
#endif
#endif

#if defined(VGEN_ENABLE_LIN_DRV)
#if defined (BRSHW_ISR_RLIN30_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt920 BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt924 BRSHW_ISR_RLIN30_0
#define BrsDummyInterrupt928 BRSHW_ISR_RLIN30_0
#   else
#error "P1H works only with 3 LIN interrupt sources"
#endif
#endif

#if defined (BRSHW_ISR_RLIN31_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt932 BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt936 BRSHW_ISR_RLIN31_0
#define BrsDummyInterrupt940 BRSHW_ISR_RLIN31_0
#   else
#error "P1H works only with 3 LIN interrupt sources"
#endif
#endif

#if defined (BRSHW_ISR_RLIN32_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt944 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt948 BRSHW_ISR_RLIN32_0
#define BrsDummyInterrupt952 BRSHW_ISR_RLIN32_0
#   else
#error "P1H works only with 3 LIN interrupt sources"
#endif
#endif

#if defined (BRSHW_ISR_RLIN33_0)
#if defined (BRSHW_LIN_USE_THREE_INT_SOURCES)
#define BrsDummyInterrupt956 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt960 BRSHW_ISR_RLIN33_0
#define BrsDummyInterrupt964 BRSHW_ISR_RLIN33_0
#   else
#error "P1H works only with 3 LIN interrupt sources"
#endif
#endif
#endif

#if defined (VGEN_ENABLE_DRVFR__BASEASR)
#if(FR_CFG_STATUS_ISR_LINE == 0)
#define BrsDummyInterrupt1256 BRS_ISR_DEFINE(Fr_IrqLine0)
#else
#define BrsDummyInterrupt1260 BRS_ISR_DEFINE(Fr_IrqLine1)
#endif

#define BrsDummyInterrupt1264 BRS_ISR_DEFINE(Fr_IrqTimer0)

#if(FR_RELATIVE_TIMER_ENABLE == STD_ON)
#define BrsDummyInterrupt1268 BRS_ISR_DEFINE(Fr_IrqTimer1)
#endif
#endif

#if defined (VGEN_ENABLE_DRVETH__BASEASR)
#if(ETH_ENABLE_RX_INTERRUPT == STD_ON) || (ETH_ENABLE_TX_INTERRUPT == STD_ON)
#define BrsDummyInterrupt1248 BRS_ISR_DEFINE(EthIsr_0)
#if(ETH_MAX_CTRLS_TOTAL > 1)
#define BrsDummyInterrupt1252 BRS_ISR_DEFINE(EthIsr_1)
#endif
#endif
#endif

#define BrsDummyInterrupt676 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)

#endif

#if defined (BRSHW_INTERRUPT_TABLE_GROUP_H)

#if defined (VGEN_ENABLE_CAN_DRV)

#if !defined (C_ENABLE_ERROR_POLLING) && defined (C_ENABLE_RX_BASICCAN_OBJECTS) && defined (C_ENABLE_OVERRUN)
#define BrsDummyInterrupt1568 BRS_ISR_DEFINE(CanIsrGlobalStatus)
#endif
#if(!defined (C_ENABLE_RX_BASICCAN_POLLING ) || defined (C_ENABLE_INDIVIDUAL_POLLING)) && defined (C_ENABLE_RX_BASICCAN_OBJECTS)
#define BrsDummyInterrupt1564 BRS_ISR_DEFINE(CanIsrRxFifo)
#endif

#if defined (kCanPhysToLogChannelIndex_0)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1576 BRS_ISR_DEFINE(CanIsrStatus_0)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1580 BRS_ISR_DEFINE(CanIsrTx_0)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_1)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1588 BRS_ISR_DEFINE(CanIsrStatus_1)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1592 BRS_ISR_DEFINE(CanIsrTx_1)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_2)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1600 BRS_ISR_DEFINE(CanIsrStatus_2)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1604 BRS_ISR_DEFINE(CanIsrTx_2)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif

#if defined (kCanPhysToLogChannelIndex_3)
#if !defined (C_ENABLE_ERROR_POLLING)
#define BrsDummyInterrupt1612 BRS_ISR_DEFINE(CanIsrStatus_3)
#endif
#if !defined (C_ENABLE_TX_POLLING) || defined (C_ENABLE_INDIVIDUAL_POLLING)
#define BrsDummyInterrupt1616 BRS_ISR_DEFINE(CanIsrTx_3)
#endif
#if defined (BRSHW_ENABLE_CAN_WAKEUP_ISR)

#error "External Interrupts for CAN not implemented. Please configure in BrsIntTb.c and BrsHw.c!"
#endif
#endif

#endif

#define BrsDummyInterrupt904 BRS_ISR_DEFINE(BrsHwTimeBaseInterrupt)

#endif

#endif
