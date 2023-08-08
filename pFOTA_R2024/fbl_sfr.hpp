

#ifndef FBL_SFR_H
#define FBL_SFR_H

#define FBL_SFR_VERSION             0x0126u
#define FBL_SFR_RELEASE_VERSION     0x01u

#if defined( V_CPU_RH850 )

# define FBL_MOSCE                  (*(volatile vuint32*)0xFFF81100uL)
# define FBL_MOSCS                  (*(volatile vuint32*)0xFFF81104uL)
# define FBL_MOSCC                  (*(volatile vuint32*)0xFFF81108uL)
# define FBL_MOSCST                 (*(volatile vuint32*)0xFFF8110CuL)

# define FBL_SOSCE                  (*(volatile vuint32*)0xFFF81200uL)
# define FBL_SOSCS                  (*(volatile vuint32*)0xFFF81204uL)
# define FBL_ROSCS                  (*(volatile vuint32*)0xFFF81004uL)

# define FBL_PLLE                   (*(volatile vuint32*)0xFFF89000uL)
# define FBL_PLLS                   (*(volatile vuint32*)0xFFF89004uL)
# define FBL_PLLC                   (*(volatile vuint32*)0xFFF89008uL)

# define FBL_PLL0E                  FBL_PLLE
# define FBL_PLL0S                  FBL_PLLS
# define FBL_PLL0C                  FBL_PLLC

# define FBL_PLL1E                  (*(volatile vuint32*)0xFFF89100uL)
# define FBL_PLL1S                  (*(volatile vuint32*)0xFFF89104uL)
# define FBL_PLL1C                  (*(volatile vuint32*)0xFFF89108uL)

# define FBL_CKSC_CPUCLKS_CTL       (*(volatile vuint32*)0xFFF8A000uL)
# define FBL_CKSC_CPUCLKS_ACT       (*(volatile vuint32*)0xFFF8A008uL)
# define FBL_CKSC_CPUCLKD_CTL       (*(volatile vuint32*)0xFFF8A100uL)
# define FBL_CKSC_CPUCLKD_ACT       (*(volatile vuint32*)0xFFF8A108uL)

# define FBL_CKSC_ICANS_CTL         (*((volatile vuint32 *)0xFFF8A900uL))
# define FBL_CKSC_ICANS_ACT         (*((volatile vuint32 *)0xFFF8A908uL))

# define FBL_CKSC_ICANOSCD_CTL      (*(volatile vuint32*)0xFFF8AA00uL)
# define FBL_CKSC_ICANOSCD_ACT      (*(volatile vuint32*)0xFFF8AA08uL)

# define FBL_PROTCMD0               (*(volatile vuint32*)0xFFF80000uL)
# define FBL_PROTS0                 (*(volatile vuint32*)0xFFF80004uL)
# define FBL_PROTCMD1               (*(volatile vuint32*)0xFFF88000uL)
# define FBL_PROTS1                 (*(volatile vuint32*)0xFFF88004uL)

#define FBL_FLMDCNT                 (*(volatile vuint32*)0xFFA00000uL)
#define FBL_FLMDPCMD                (*(volatile vuint32*)0xFFA00004uL)
#define FBL_FLMDPS                  (*(volatile vuint32*)0xFFA00008uL)

# define FBL_SEG_CONT               (*(volatile vuint16*)0xFFFF8C00uL)
# define FBL_SEG_FLAG               (*(volatile vuint16*)0xFFFF8C02uL)

# define kSegContRome               0x0002u
# define kSegFlagRomf               0x0002u

#define kEccProtWrite               0x4000u
#define kEccNotificationDisable     0x00u
#define kEccCorrectionDisable       0x0002u
#define kEccClearError              0x01u
#define kEccClearErrorExt           0x0Fu

 # define kEccUncorrectableError     0x0002u

# define FBL_ECC_base               (0xFFC62000uL)

# define FBL_ECC_base_VCI           (FBL_ECC_base + 0x0200u)
# define FBL_ECC_base_PE1           (FBL_ECC_base + 0x0400u)
# define FBL_ECC_base_PE2           (FBL_ECC_base + 0x0600u)
# define FBL_ECC_base_PCU           (FBL_ECC_base + 0x0800u)

# define FBL_ECC_base_used        FBL_ECC_base

# define FBL_CFECCCTL_OFFSET        0x0000u
# define FBL_CFFSTERSTR_OFFSET      0x0004u
# define FBL_CFERRINT_OFFSET        0x0030u
# define FBL_CFFSTSTC_OFFSET        0x0024u
# define FBL_CFOVFSTC_OFFSET        0x002Cu

#define FBL_CODE_FLASH_ECC_CTL          (*(volatile tFblEccCtl*)   (FBL_ECC_base_used + FBL_CFECCCTL_OFFSET    ))
# define FBL_CODE_FLASH_ECC_FSTSTC      (*(volatile vuint8 *)      (FBL_ECC_base_used + FBL_CFFSTSTC_OFFSET    ))
# define FBL_CODE_FLASH_ECC_OVFSTC      (*(volatile vuint8 *)      (FBL_ECC_base_used + FBL_CFOVFSTC_OFFSET    ))
# define FBL_CODE_FLASH_ECC_ERRINT      (*(volatile tFblEccErrInt*)(FBL_ECC_base_used + FBL_CFERRINT_OFFSET    ))
# define FBL_CODE_FLASH_ECC_FSTERSTR    (*(volatile vuint32*)      (FBL_ECC_base_used + FBL_CFFSTERSTR_OFFSET  ))

# define FBL_CODE_FLASH_ECC_ERROR_CLEAR() { \
                                             FBL_CODE_FLASH_ECC_FSTSTC = kEccClearError; \
                                             FBL_CODE_FLASH_ECC_OVFSTC = kEccClearError; \
                                          }

typedef vuint16 tFblEccCtl;
typedef vuint8  tFblEccErrInt;

#define kEccDFProtWrite              0x4000u
#define kEccDFNotificationDisable    0x00u
#define kEccDFCorrectionDisable      0x0002u
#define kEccDFClearError             0x01u
#define kEccDFUncorrectableError     0x02u

# define FBL_ECC_DF_base               (0xFFC66000uL)

#define FBL_DFECCCTL_OFFSET          0x0000u
#define FBL_DFERSTR_OFFSET           0x0004u
#define FBL_DFERSTC_OFFSET           0x0008u
#define FBL_DFERRINT_OFFSET          0x0014u

#define FBL_DATA_FLASH_ECC_CTL       (*(volatile tFblEccDFCtl*)   (FBL_ECC_DF_base + FBL_DFECCCTL_OFFSET  ))
#define FBL_DATA_FLASH_ECC_ERSTR     (*(volatile vuint8*)         (FBL_ECC_DF_base + FBL_DFERSTR_OFFSET   ))
#define FBL_DATA_FLASH_ECC_ERSTC     (*(volatile vuint8*)         (FBL_ECC_DF_base + FBL_DFERSTC_OFFSET   ))
#define FBL_DATA_FLASH_ECC_ERRINT    (*(volatile tFblEccErrDFInt*)(FBL_ECC_DF_base + FBL_DFERRINT_OFFSET  ))

#define FBL_DATA_FLASH_ECC_ERROR_CLEAR()    FBL_DATA_FLASH_ECC_ERSTC  = kEccDFClearError

typedef vuint16 tFblEccDFCtl;
typedef vuint8  tFblEccErrDFInt;

#define FBL_PROT_WRITEX(protreg, statreg, reg, val) do {                               \
                                                          (protreg)=(vuint32)0xA5u;    \
                                                          (reg)=(vuint32)(val);        \
                                                          (reg)=FblInvert32Bit(val);   \
                                                          (reg)=(vuint32)(val);        \
                                                       } while (((statreg) & 0x01u) == 0x01u);

# define FBL_PROT_WRITE0(reg, val)   FBL_PROT_WRITEX(FBL_PROTCMD0, FBL_PROTS0, reg, val)
# define FBL_PROT_WRITE1(reg, val)   FBL_PROT_WRITEX(FBL_PROTCMD1, FBL_PROTS1, reg, val)

#define FBL_PROT_WRITE_FLMDCNT(val)  FBL_PROT_WRITEX(FBL_FLMDPCMD, FBL_FLMDPS, FBL_FLMDCNT, val)

# define FBL_PORTn_base           0xFFC10000uL

# define FBL_P(n)        (*(volatile vuint16*)(FBL_PORTn_base + 0x0000u + ((n)*4u)))
# define FBL_PSR(n)      (*(volatile vuint16*)(FBL_PORTn_base + 0x0100u + ((n)*4u)))
# define FBL_PPR(n)      (*(volatile vuint16*)(FBL_PORTn_base + 0x0200u + ((n)*4u)))
# define FBL_PM(n)       (*(volatile vuint16*)(FBL_PORTn_base + 0x0300u + ((n)*4u)))
# define FBL_PMC(n)      (*(volatile vuint16*)(FBL_PORTn_base + 0x0400u + ((n)*4u)))
# define FBL_PFC(n)      (*(volatile vuint16*)(FBL_PORTn_base + 0x0500u + ((n)*4u)))
# define FBL_PFCE(n)     (*(volatile vuint16*)(FBL_PORTn_base + 0x0600u + ((n)*4u)))
# define FBL_PFCAE(n)    (*(volatile vuint16*)(FBL_PORTn_base + 0x0A00u + ((n)*4u)))
# define FBL_PIBC(n)     (*(volatile vuint16*)(FBL_PORTn_base + 0x4000u + ((n)*4u)))
# define FBL_PBDC(n)     (*(volatile vuint16*)(FBL_PORTn_base + 0x4100u + ((n)*4u)))
# define FBL_PIPC(n)     (*(volatile vuint16*)(FBL_PORTn_base + 0x4200u + ((n)*4u)))
# define FBL_PODC(n)     (*(volatile vuint32*)(FBL_PORTn_base + 0x4500u + ((n)*4u)))

#define FBL_P0           FBL_P(0u)
#define FBL_PSR0         FBL_PSR(0u)
#define FBL_PPR0         FBL_PPR(0u)
#define FBL_PM0          FBL_PM(0u)
#define FBL_PMC0         FBL_PMC(0u)
#define FBL_PFC0         FBL_PFC(0u)
#define FBL_PFCE0        FBL_PFCE(0u)
#define FBL_PFCAE0       FBL_PFCAE(0u)
#define FBL_PIBC0        FBL_PIBC(0u)
#define FBL_PBDC0        FBL_PBDC(0u)
#define FBL_PIPC0        FBL_PIPC(0u)
#define FBL_PODC0        FBL_PODC(0u)

#define FBL_P1           FBL_P(1u)
#define FBL_PSR1         FBL_PSR(1u)
#define FBL_PPR1         FBL_PPR(1u)
#define FBL_PM1          FBL_PM(1u)
#define FBL_PMC1         FBL_PMC(1u)
#define FBL_PFC1         FBL_PFC(1u)
#define FBL_PFCE1        FBL_PFCE(1u)
#define FBL_PFCAE1       FBL_PFCAE(1u)
#define FBL_PIBC1        FBL_PIBC(1u)
#define FBL_PBDC1        FBL_PBDC(1u)
#define FBL_PIPC1        FBL_PIPC(1u)
#define FBL_PODC1        FBL_PODC(1u)

#define FBL_P2           FBL_P(2u)
#define FBL_PSR2         FBL_PSR(2u)
#define FBL_PPR2         FBL_PPR(2u)
#define FBL_PM2          FBL_PM(2u)
#define FBL_PMC2         FBL_PMC(2u)
#define FBL_PFC2         FBL_PFC(2u)
#define FBL_PFCE2        FBL_PFCE(2u)
#define FBL_PFCAE2       FBL_PFCAE(2u)
#define FBL_PIBC2        FBL_PIBC(2u)
#define FBL_PBDC2        FBL_PBDC(2u)
#define FBL_PIPC2        FBL_PIPC(2u)
#define FBL_PODC2        FBL_PODC(2u)

#define FBL_P8           FBL_P(8u)
#define FBL_PSR8         FBL_PSR(8u)
#define FBL_PPR8         FBL_PPR(8u)
#define FBL_PM8          FBL_PM(8u)
#define FBL_PMC8         FBL_PMC(8u)
#define FBL_PFC8         FBL_PFC(8u)
#define FBL_PFCE8        FBL_PFCE(8u)
#define FBL_PFCAE8       FBL_PFCAE(8u)
#define FBL_PIBC8        FBL_PIBC(8u)
#define FBL_PBDC8        FBL_PBDC(8u)
#define FBL_PIPC8        FBL_PIPC(8u)
#define FBL_PODC8        FBL_PODC(8u)

#define FBL_P9           FBL_P(9u)
#define FBL_PSR9         FBL_PSR(9u)
#define FBL_PPR9         FBL_PPR(9u)
#define FBL_PM9          FBL_PM(9u)
#define FBL_PMC9         FBL_PMC(9u)
#define FBL_PFC9         FBL_PFC(9u)
#define FBL_PFCE9        FBL_PFCE(9u)
#define FBL_PFCAE9       FBL_PFCAE(9u)
#define FBL_PIBC9        FBL_PIBC(9u)
#define FBL_PBDC9        FBL_PBDC(9u)
#define FBL_PIPC9        FBL_PIPC(9u)
#define FBL_PODC9        FBL_PODC(9u)

#define FBL_P10          FBL_P(10u)
#define FBL_PSR10        FBL_PSR(10u)
#define FBL_PPR10        FBL_PPR(10u)
#define FBL_PM10         FBL_PM(10u)
#define FBL_PMC10        FBL_PMC(10u)
#define FBL_PFC10        FBL_PFC(10u)
#define FBL_PFCE10       FBL_PFCE(10u)
#define FBL_PFCAE10      FBL_PFCAE(10u)
#define FBL_PIBC10       FBL_PIBC(10u)
#define FBL_PBDC10       FBL_PBDC(10u)
#define FBL_PIPC10       FBL_PIPC(10u)
#define FBL_PODC10       FBL_PODC(10u)

#define FBL_P11          FBL_P(11u)
#define FBL_PSR11        FBL_PSR(11u)
#define FBL_PPR11        FBL_PPR(11u)
#define FBL_PM11         FBL_PM(11u)
#define FBL_PMC11        FBL_PMC(11u)
#define FBL_PFC11        FBL_PFC(11u)
#define FBL_PFCE11       FBL_PFCE(11u)
#define FBL_PFCAE11      FBL_PFCAE(11u)
#define FBL_PIBC11       FBL_PIBC(11u)
#define FBL_PBDC11       FBL_PBDC(11u)
#define FBL_PIPC11       FBL_PIPC(11u)
#define FBL_PODC11       FBL_PODC(11u)

#define FBL_P12          FBL_P(12u)
#define FBL_PSR12        FBL_PSR(12u)
#define FBL_PPR12        FBL_PPR(12u)
#define FBL_PM12         FBL_PM(12u)
#define FBL_PMC12        FBL_PMC(12u)
#define FBL_PFC12        FBL_PFC(12u)
#define FBL_PFCE12       FBL_PFCE(12u)
#define FBL_PFCAE12      FBL_PFCAE(12u)
#define FBL_PIBC12       FBL_PIBC(12u)
#define FBL_PBDC12       FBL_PBDC(12u)
#define FBL_PIPC12       FBL_PIPC(12u)
#define FBL_PODC12       FBL_PODC(12u)

#define FBL_P18          FBL_P(18u)
#define FBL_PSR18        FBL_PSR(18u)
#define FBL_PPR18        FBL_PPR(18u)
#define FBL_PM18         FBL_PM(18u)
#define FBL_PMC18        FBL_PMC(18u)
#define FBL_PFC18        FBL_PFC(18u)
#define FBL_PFCE18       FBL_PFCE(18u)
#define FBL_PFCAE18      FBL_PFCAE(18u)
#define FBL_PIBC18       FBL_PIBC(18u)
#define FBL_PBDC18       FBL_PBDC(18u)
#define FBL_PIPC18       FBL_PIPC(18u)
#define FBL_PODC18       FBL_PODC(18u)

#define FBL_P20          FBL_P(20u)
#define FBL_PSR20        FBL_PSR(20u)
#define FBL_PPR20        FBL_PPR(20u)
#define FBL_PM20         FBL_PM(20u)
#define FBL_PMC20        FBL_PMC(20u)
#define FBL_PFC20        FBL_PFC(20u)
#define FBL_PFCE20       FBL_PFCE(20u)
#define FBL_PFCAE20      FBL_PFCAE(20u)
#define FBL_PIBC20       FBL_PIBC(20u)
#define FBL_PBDC20       FBL_PBDC(20u)
#define FBL_PIPC20       FBL_PIPC(20u)
#define FBL_PODC20       FBL_PODC(20u)

#define FBL_P21          FBL_P(21u)
#define FBL_PSR21        FBL_PSR(21u)
#define FBL_PRR21        FBL_PRR(21u)
#define FBL_PM21         FBL_PM(21u)
#define FBL_PMC21        FBL_PMC(21u)
#define FBL_PFC21        FBL_PFC(21u)
#define FBL_PFCE21       FBL_PFCE(21u)
#define FBL_PIBC21       FBL_PIBC(21u)
#define FBL_PBDC21       FBL_PBDC(21u)
#define FBL_PIPC21       FBL_PIPC(21u)
#define FBL_PU21         FBL_PU(21u)
#define FBL_PDSC21       FBL_PDSC(21u)
#define FBL_PODC21       FBL_PODC(21u)

#define FBL_P44          FBL_P(44u)
#define FBL_PM44         FBL_PM(44u)

#define FBL_P45          FBL_P(45u)
#define FBL_PM45         FBL_PM(45u)

# define FBL_JPORT0_BASE_ADDRESS  0xFFC20000uL
# define FBL_JPORTM0_OFFSET       0x00000030uL

# define FBL_JP0       (*(volatile vuint8*)(FBL_JPORT0_BASE_ADDRESS + 0x00u ))
# define FBL_JPM0      (*(volatile vuint8*)(FBL_JPORT0_BASE_ADDRESS + FBL_JPORTM0_OFFSET ))

# define FBL_TAUDn_user_base   0xFFE20000uL
# define FBL_TAUXn_user_base   FBL_TAUDn_user_base

#define FBL_TAUX0CDR0    (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0000u))
#define FBL_TAUX0CDR1    (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0004u))
#define FBL_TAUX0CDR2    (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0008u))

#define FBL_TAUX0CNT0    (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0080u))
#define FBL_TAUX0CNT1    (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0084u))
#define FBL_TAUX0CNT2    (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0088u))

#define FBL_TAUX0CMOR0   (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0200u))
#define FBL_TAUX0CMOR1   (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0204u))
#define FBL_TAUX0CMOR2   (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0208u))

#define FBL_TAUX0CMUR0   (*(volatile vuint8* )(FBL_TAUXn_user_base + 0x00C0u))
#define FBL_TAUX0CMUR1   (*(volatile vuint8* )(FBL_TAUXn_user_base + 0x00C4u))
#define FBL_TAUX0CMUR2   (*(volatile vuint8* )(FBL_TAUXn_user_base + 0x00C8u))

#define FBL_TAUX0CSR0    (*(volatile vuint8* )(FBL_TAUXn_user_base + 0x0140u))
#define FBL_TAUX0CSR1    (*(volatile vuint8* )(FBL_TAUXn_user_base + 0x0144u))
#define FBL_TAUX0CSR2    (*(volatile vuint8* )(FBL_TAUXn_user_base + 0x0148u))

#define FBL_TAUX0TPS     (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0240u))
#define FBL_TAUX0TS      (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x01C4u))
#define FBL_TAUX0TT      (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x01C8u))

#define FBL_TAUX0RDE     (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0260u))
#define FBL_TAUX0RDM     (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0264u))
#define FBL_TAUX0RDS     (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x0268u))
#define FBL_TAUX0RDC     (*(volatile vuint16*)(FBL_TAUXn_user_base + 0x026Cu))

# if defined( C_PROCESSOR_F1L ) || defined( C_PROCESSOR_R1M ) || defined( C_PROCESSOR_R1L )
#  define FBL_ICTAUX0I0  (*(volatile vuint16*)0xFFFF9000uL)
# elif defined( C_PROCESSOR_F1H ) || defined( C_PROCESSOR_F1K ) || defined( C_PROCESSOR_F1M )
#  define FBL_ICTAUX0I0  (*(volatile vuint16*)0xFFFEEA10uL)
# else
#  error "Unsupported derivative"
# endif

# define FBL_RESF        (*(volatile vuint32*)0xFFF80760uL)
# define FBL_RESFC       (*(volatile vuint32*)0xFFF80768uL)
# define FBL_SWRESA      (*(volatile vuint32*)0xFFF80A04uL)

#define FBL_SW_RESET() FBL_PROT_WRITE0(FBL_SWRESA, 0x01u);

# define FBL_WDTA0       0xFFED0000uL
# define FBL_WDTA1       0xFFED1000uL

#define FBL_WDTA0WDTE    (*(volatile vuint8 *)(FBL_WDTA0 + 0x00u))
#define FBL_WDTA0EVAC    (*(volatile vuint8 *)(FBL_WDTA0 + 0x04u))
#define FBL_WDTA0REF     (*(volatile vuint8 *)(FBL_WDTA0 + 0x08u))
#define FBL_WDTA0MD      (*(volatile vuint8 *)(FBL_WDTA0 + 0x0Cu))

# define FBL_WDTA1WDTE   (*(volatile vuint8 *)(FBL_WDTA1 + 0x00u))
# define FBL_WDTA1EVAC   (*(volatile vuint8 *)(FBL_WDTA1 + 0x04u))
# define FBL_WDTA1REF    (*(volatile vuint8 *)(FBL_WDTA1 + 0x08u))
# define FBL_WDTA1MD     (*(volatile vuint8 *)(FBL_WDTA1 + 0x0Cu))
#endif

#if defined( FBL_ENABLE_BUSTYPE_CAN )
#endif

#endif

