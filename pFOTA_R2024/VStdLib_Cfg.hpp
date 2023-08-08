#if !defined (VSTDLIB_CFG_H)
# define VSTDLIB_CFG_H

# define VSTDLIB_USE_LIBRARY_FUNCTIONS STD_OFF
# define VSTDLIB_RUNTIME_OPTIMIZATION STD_ON
# define VSTDLIB_USE_JUMPTABLES STD_ON
# define VSTDLIB_DEV_ERROR_DETECT STD_OFF
# define VSTDLIB_DEV_ERROR_REPORT STD_OFF
# define VSTDLIB_VERSION_INFO_API STD_OFF
# define VSTDLIB_DUMMY_STATEMENT(v) (void)(v)

# if(VSTDLIB_USE_LIBRARY_FUNCTIONS == STD_ON)
#  error "Verify the setting for VSTDLIB_SUPPORT_LARGE_DATA and fill the macros in this section with correct values!"
#  define VSTDLIB_SUPPORT_LARGE_DATA             STD_ON
#  define VStdLib_MemClr(pDst, nCnt)             memset((pDst), 0, (nCnt))
#  define VStdLib_MemSet(pDst, nPattern, nCnt)   memset((pDst), (nPattern), (nCnt))
#  define VStdLib_MemCpy(pDst, pSrc, nCnt)       memcpy((pDst), (pSrc), (nCnt))
#  define VStdLib_MemCpy16(pDst, pSrc, nCnt)     memcpy((pDst), (pSrc), ((nCnt)<<1))
#  define VStdLib_MemCpy32(pDst, pSrc, nCnt)     memcpy((pDst), (pSrc), ((nCnt)<<2))
# endif

# if defined(VSTD_ENABLE_INTCTRL_HANDLING) || defined(VSTD_ENABLE_DEFAULT_INTCTRL) || \
     defined(VSTD_ENABLE_OSEK_INTCTRL) || defined(VSTD_ENABLE_APPL_INTCTRL)
#  error "VStdLib_GenericAsr does not support interrupt control handling, provide a mapping in this section!"
# endif

# define VSTDLIB_CFG_MAJOR_VERSION     (2u)
# define VSTDLIB_CFG_MINOR_VERSION     (0u)

#endif

