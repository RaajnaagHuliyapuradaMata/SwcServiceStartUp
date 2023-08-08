

#ifndef BRS_MEMMAP_ERROR
  #define BRS_MEMMAP_ERROR
#endif

#ifdef BRS_START_SEC_RAM_CODE

   # pragma ghs startdata
   # pragma ghs section text=".RAMCODE"

  #undef BRS_START_SEC_RAM_CODE
  #undef BRS_MEMMAP_ERROR
#endif

#ifdef BRS_STOP_SEC_RAM_CODE

     # pragma ghs section
     # pragma ghs enddata

  #undef BRS_STOP_SEC_RAM_CODE
  #undef BRS_MEMMAP_ERROR
#endif

#ifdef BRS_START_SEC_RAM_CONST

   # pragma ghs startdata
   # pragma ghs section rodata=".RAMCONST"

  #undef BRS_START_SEC_RAM_CONST
  #undef BRS_MEMMAP_ERROR
#endif

#ifdef BRS_STOP_SEC_RAM_CONST

   # pragma ghs section
   # pragma ghs enddata

  #undef BRS_STOP_SEC_RAM_CONST
  #undef BRS_MEMMAP_ERROR
#endif

#if defined (BRS_MEMMAP_ERROR)
  #error "Error in Brs_MemMap.h: MemMap section is not included!"
#endif
