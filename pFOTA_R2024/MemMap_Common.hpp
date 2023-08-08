

#ifdef START_SEC_CONST_8
# define START_SEC_CONST_8BIT
# undef START_SEC_CONST_8

#elif defined START_SEC_CONST_16
# define START_SEC_CONST_16BIT
# undef START_SEC_CONST_16

#elif defined START_SEC_CONST_32
# define START_SEC_CONST_32BIT
# undef START_SEC_CONST_32

#elif defined START_SEC_CONST_64
# define START_SEC_CONST_64BIT
# undef START_SEC_CONST_64

#elif defined START_SEC_CONST_FAST_8
# define START_SEC_CONST_FAST_8BIT
# undef START_SEC_CONST_FAST_8

#elif defined START_SEC_CONST_FAST_16
# define START_SEC_CONST_FAST_16BIT
# undef START_SEC_CONST_FAST_16

#elif defined START_SEC_CONST_FAST_32
# define START_SEC_CONST_FAST_32BIT
# undef START_SEC_CONST_FAST_32

#elif defined START_SEC_CONST_FAST_64
# define START_SEC_CONST_FAST_64BIT
# undef START_SEC_CONST_FAST_64

#elif defined START_SEC_VAR_INIT_8
# define START_SEC_VAR_INIT_8BIT
# undef START_SEC_VAR_INIT_8

#elif defined START_SEC_VAR_INIT_16
# define START_SEC_VAR_INIT_16BIT
# undef START_SEC_VAR_INIT_16

#elif defined START_SEC_VAR_INIT_32
# define START_SEC_VAR_INIT_32BIT
# undef START_SEC_VAR_INIT_32

#elif defined START_SEC_VAR_INIT_64
# define START_SEC_VAR_INIT_64BIT
# undef START_SEC_VAR_INIT_64

#elif defined START_SEC_VAR_NO_INIT_8
# define START_SEC_VAR_NOINIT_8BIT
# undef START_SEC_VAR_NO_INIT_8

#elif defined START_SEC_VAR_NO_INIT_16
# define START_SEC_VAR_NOINIT_16BIT
# undef START_SEC_VAR_NO_INIT_16

#elif defined START_SEC_VAR_NO_INIT_32
# define START_SEC_VAR_NOINIT_32BIT
# undef START_SEC_VAR_NO_INIT_32

#elif defined START_SEC_VAR_NO_INIT_64
# define START_SEC_VAR_NOINIT_64BIT
# undef START_SEC_VAR_NO_INIT_64

#elif defined START_SEC_VAR_NO_INIT_UNSPECIFIED
# define START_SEC_VAR_NOINIT_UNSPECIFIED
# undef START_SEC_VAR_NO_INIT_UNSPECIFIED

#elif defined START_SEC_VAR_CLEARED_8
# define START_SEC_VAR_ZERO_INIT_8BIT
# undef START_SEC_VAR_CLEARED_8

#elif defined START_SEC_VAR_CLEARED_16
# define START_SEC_VAR_ZERO_INIT_16BIT
# undef START_SEC_VAR_CLEARED_16

#elif defined START_SEC_VAR_CLEARED_32
# define START_SEC_VAR_ZERO_INIT_32BIT
# undef START_SEC_VAR_CLEARED_32

#elif defined START_SEC_VAR_CLEARED_64
# define START_SEC_VAR_ZERO_INIT_64BIT
# undef START_SEC_VAR_CLEARED_64

#elif defined START_SEC_VAR_CLEARED_UNSPECIFIED
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef START_SEC_VAR_CLEARED_UNSPECIFIED

#elif defined START_SEC_VAR_FAST_INIT_8
# define START_SEC_VAR_FAST_INIT_8BIT
# undef START_SEC_VAR_FAST_INIT_8

#elif defined START_SEC_VAR_FAST_INIT_16
# define START_SEC_VAR_FAST_INIT_16BIT
# undef START_SEC_VAR_FAST_INIT_16

#elif defined START_SEC_VAR_FAST_INIT_32
# define START_SEC_VAR_FAST_INIT_32BIT
# undef START_SEC_VAR_FAST_INIT_32

#elif defined START_SEC_VAR_FAST_INIT_64
# define START_SEC_VAR_FAST_INIT_64BIT
# undef START_SEC_VAR_FAST_INIT_64

#elif defined START_SEC_VAR_FAST_NO_INIT_8
# define START_SEC_VAR_FAST_NOINIT_8BIT
# undef START_SEC_VAR_FAST_NO_INIT_8

#elif defined START_SEC_VAR_FAST_NO_INIT_16
# define START_SEC_VAR_FAST_NOINIT_16BIT
# undef START_SEC_VAR_FAST_NO_INIT_16

#elif defined START_SEC_VAR_FAST_NO_INIT_32
# define START_SEC_VAR_FAST_NOINIT_32BIT
# undef START_SEC_VAR_FAST_NO_INIT_32

#elif defined START_SEC_VAR_FAST_NO_INIT_64
# define START_SEC_VAR_FAST_NOINIT_64BIT
# undef START_SEC_VAR_FAST_NO_INIT_64

#elif defined START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
# define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED

#elif defined START_SEC_VAR_FAST_CLEARED_8
# define START_SEC_VAR_FAST_ZERO_INIT_8BIT
# undef START_SEC_VAR_FAST_CLEARED_8

#elif defined START_SEC_VAR_FAST_CLEARED_16
# define START_SEC_VAR_FAST_ZERO_INIT_16BIT
# undef START_SEC_VAR_FAST_CLEARED_16

#elif defined START_SEC_VAR_FAST_CLEARED_32
# define START_SEC_VAR_FAST_ZERO_INIT_32BIT
# undef START_SEC_VAR_FAST_CLEARED_32

#elif defined START_SEC_VAR_FAST_CLEARED_64
# define START_SEC_VAR_FAST_ZERO_INIT_64BIT
# undef START_SEC_VAR_FAST_CLEARED_64

#elif defined START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
# define START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef START_SEC_VAR_FAST_CLEARED_UNSPECIFIED

#elif defined START_SEC_VAR_NOCACHE_INIT_8
# define START_SEC_VAR_NOCACHE_INIT_8BIT
# undef START_SEC_VAR_NOCACHE_INIT_8

#elif defined START_SEC_VAR_NOCACHE_INIT_16
# define START_SEC_VAR_NOCACHE_INIT_16BIT
# undef START_SEC_VAR_NOCACHE_INIT_16

#elif defined START_SEC_VAR_NOCACHE_INIT_32
# define START_SEC_VAR_NOCACHE_INIT_32BIT
# undef START_SEC_VAR_NOCACHE_INIT_32

#elif defined START_SEC_VAR_NOCACHE_INIT_64
# define START_SEC_VAR_NOCACHE_INIT_64BIT
# undef START_SEC_VAR_NOCACHE_INIT_64

#elif defined START_SEC_VAR_NOCACHE_NO_INIT_8
# define START_SEC_VAR_NOCACHE_NOINIT_8BIT
# undef START_SEC_VAR_NOCACHE_NO_INIT_8

#elif defined START_SEC_VAR_NOCACHE_NO_INIT_16
# define START_SEC_VAR_NOCACHE_NOINIT_16BIT
# undef START_SEC_VAR_NOCACHE_NO_INIT_16

#elif defined START_SEC_VAR_NOCACHE_NO_INIT_32
# define START_SEC_VAR_NOCACHE_NOINIT_32BIT
# undef START_SEC_VAR_NOCACHE_NO_INIT_32

#elif defined START_SEC_VAR_NOCACHE_NO_INIT_64
# define START_SEC_VAR_NOCACHE_NOINIT_64BIT
# undef START_SEC_VAR_NOCACHE_NO_INIT_64

#elif defined START_SEC_VAR_NOCACHE_NO_INIT_UNSPECIFIED
# define START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
# undef START_SEC_VAR_NOCACHE_NO_INIT_UNSPECIFIED

#elif defined START_SEC_VAR_NOCACHE_CLEARED_8
# define START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
# undef START_SEC_VAR_NOCACHE_CLEARED_8

#elif defined START_SEC_VAR_NOCACHE_CLEARED_16
# define START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
# undef START_SEC_VAR_NOCACHE_CLEARED_16

#elif defined START_SEC_VAR_NOCACHE_CLEARED_32
# define START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
# undef START_SEC_VAR_NOCACHE_CLEARED_32

#elif defined START_SEC_VAR_NOCACHE_CLEARED_64
# define START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT
# undef START_SEC_VAR_NOCACHE_CLEARED_64

#elif defined START_SEC_VAR_NOCACHE_CLEARED_UNSPECIFIED
# define START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
# undef START_SEC_VAR_NOCACHE_CLEARED_UNSPECIFIED

#endif

#ifdef MEMMAP_DETECT_ANY_ERROR

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CODE))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CODE is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CODE_FAST))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CODE_FAST is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CODE_ISR))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CODE_ISR is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_PBCFG))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_PBCFG_GLOBALROOT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_PBCFG_GLOBALROOT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_PBCFG))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CODE))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CODE is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CODE_FAST))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CODE_FAST is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CODE_ISR))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CODE_ISR is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_PBCFG))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_PBCFG_GLOBALROOT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_PBCFG_GLOBALROOT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_PBCFG))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CODE))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CODE is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CODE_FAST))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CODE_FAST is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CODE_ISR))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CODE_ISR is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_PBCFG))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_PBCFG_GLOBALROOT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_PBCFG_GLOBALROOT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_PBCFG))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

#else

# if(((defined CODE_SEC_OPEN) || (defined CONST_SEC_OPEN) || (defined VAR_SEC_OPEN)) && \
      ((defined START_SEC_CODE                                                      ) || \
       (defined START_SEC_CODE_FAST                                                 ) || \
       (defined START_SEC_CODE_ISR                                                  ) || \
       (defined START_SEC_CONST_8BIT                                                ) || \
       (defined START_SEC_CONST_16BIT                                               ) || \
       (defined START_SEC_CONST_32BIT                                               ) || \
       (defined START_SEC_CONST_64BIT                                               ) || \
       (defined START_SEC_CONST_UNSPECIFIED                                         ) || \
       (defined START_SEC_CONST_FAST_8BIT                                           ) || \
       (defined START_SEC_CONST_FAST_16BIT                                          ) || \
       (defined START_SEC_CONST_FAST_32BIT                                          ) || \
       (defined START_SEC_CONST_FAST_64BIT                                          ) || \
       (defined START_SEC_CONST_FAST_UNSPECIFIED                                    ) || \
       (defined START_SEC_CONST_PBCFG                                               ) || \
       (defined START_SEC_PBCFG_GLOBALROOT                                          ) || \
       (defined START_SEC_VAR_INIT_8BIT                                             ) || \
       (defined START_SEC_VAR_INIT_16BIT                                            ) || \
       (defined START_SEC_VAR_INIT_32BIT                                            ) || \
       (defined START_SEC_VAR_INIT_64BIT                                            ) || \
       (defined START_SEC_VAR_INIT_UNSPECIFIED                                      ) || \
       (defined START_SEC_VAR_NOINIT_8BIT                                           ) || \
       (defined START_SEC_VAR_NOINIT_16BIT                                          ) || \
       (defined START_SEC_VAR_NOINIT_32BIT                                          ) || \
       (defined START_SEC_VAR_NOINIT_64BIT                                          ) || \
       (defined START_SEC_VAR_NOINIT_UNSPECIFIED                                    ) || \
       (defined START_SEC_VAR_PBCFG                                                 ) || \
       (defined START_SEC_VAR_ZERO_INIT_8BIT                                        ) || \
       (defined START_SEC_VAR_ZERO_INIT_16BIT                                       ) || \
       (defined START_SEC_VAR_ZERO_INIT_32BIT                                       ) || \
       (defined START_SEC_VAR_ZERO_INIT_64BIT                                       ) || \
       (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED                                 ) || \
       (defined START_SEC_VAR_FAST_INIT_8BIT                                        ) || \
       (defined START_SEC_VAR_FAST_INIT_16BIT                                       ) || \
       (defined START_SEC_VAR_FAST_INIT_32BIT                                       ) || \
       (defined START_SEC_VAR_FAST_INIT_64BIT                                       ) || \
       (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED                                 ) || \
       (defined START_SEC_VAR_FAST_NOINIT_8BIT                                      ) || \
       (defined START_SEC_VAR_FAST_NOINIT_16BIT                                     ) || \
       (defined START_SEC_VAR_FAST_NOINIT_32BIT                                     ) || \
       (defined START_SEC_VAR_FAST_NOINIT_64BIT                                     ) || \
       (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED                               ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT                                   ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT                                  ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT                                  ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT                                  ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED                            ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_8BIT                                     ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_16BIT                                    ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_32BIT                                    ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_64BIT                                    ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED                              ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT                                   ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT                                  ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT                                  ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT                                  ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED                            ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT                                ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT                               ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT                               ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT                               ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED                         )    \
      ))
#  error "MemMap_Common.h: New section opened before closing the former one. Please close the former code/const/data section before opening a new one. (Check_1)"
# endif

#endif

#ifdef START_SEC_CODE
# define CODE_SEC_OPEN

# undef START_SEC_CODE
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CODE" is the obsolete one!"
# endif

#elif defined START_SEC_CODE_FAST
# define CODE_SEC_OPEN

# undef START_SEC_CODE_FAST
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CODE_FAST" is the obsolete one!"
# endif

#elif defined START_SEC_CODE_ISR
# define CODE_SEC_OPEN

# undef START_SEC_CODE_ISR
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CODE_ISR" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_8BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_16BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_32BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_64BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_UNSPECIFIED
# define CONST_SEC_OPEN

# undef START_SEC_CONST_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_FAST_8BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_FAST_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_FAST_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_FAST_16BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_FAST_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_FAST_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_FAST_32BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_FAST_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_FAST_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_FAST_64BIT
# define CONST_SEC_OPEN

# undef START_SEC_CONST_FAST_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_FAST_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_FAST_UNSPECIFIED
# define CONST_SEC_OPEN

# undef START_SEC_CONST_FAST_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_FAST_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_CONST_PBCFG
# define CONST_SEC_OPEN

# undef START_SEC_CONST_PBCFG
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_CONST_PBCFG" is the obsolete one!"
# endif

#elif defined START_SEC_PBCFG_GLOBALROOT
# define CONST_SEC_OPEN

# undef START_SEC_PBCFG_GLOBALROOT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_PBCFG_GLOBALROOT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_INIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_INIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_INIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_INIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_INIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_INIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_INIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_INIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_INIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_INIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_INIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_INIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_INIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_INIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_INIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOINIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOINIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOINIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOINIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOINIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOINIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOINIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOINIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOINIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOINIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOINIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOINIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOINIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOINIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOINIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_PBCFG
# define VAR_SEC_OPEN

# undef START_SEC_VAR_PBCFG
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_PBCFG" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_ZERO_INIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_ZERO_INIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_ZERO_INIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_ZERO_INIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_ZERO_INIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_ZERO_INIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_ZERO_INIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_ZERO_INIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_ZERO_INIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_ZERO_INIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_ZERO_INIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_ZERO_INIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_ZERO_INIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_INIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_INIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_INIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_INIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_INIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_INIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_INIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_INIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_INIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_INIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_INIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_INIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_INIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_INIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_INIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_NOINIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_NOINIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_NOINIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_NOINIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_NOINIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_NOINIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_NOINIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_NOINIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_NOINIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_NOINIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_NOINIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_NOINIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_NOINIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_ZERO_INIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_ZERO_INIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_ZERO_INIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_ZERO_INIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_ZERO_INIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_ZERO_INIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_ZERO_INIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_ZERO_INIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_ZERO_INIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_ZERO_INIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_ZERO_INIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_ZERO_INIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_INIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_INIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_INIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_INIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_INIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_INIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_INIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_INIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_INIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_INIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_INIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_INIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_NOINIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_NOINIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_NOINIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_NOINIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_NOINIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_NOINIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_NOINIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_NOINIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_NOINIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_NOINIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_NOINIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_NOINIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT" is the obsolete one!"
# endif

#elif defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
# define VAR_SEC_OPEN

# undef START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED
# undef MEMMAP_ERROR
# ifdef MEMMAP_DETECT_ANY_ERROR
#  error "The DEFINE: "START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED" is the obsolete one!"
# endif

#elif defined STOP_SEC_CODE
# if defined CODE_SEC_OPEN
#  undef CODE_SEC_OPEN

#  undef STOP_SEC_CODE
#  undef MEMMAP_ERROR
# else
#  error "MemMap_Common.h: Code section closed but not opened one. Please close a code section [== usage of *_STOP_SEC_CODE_*] only if you have opened one [== usage of *_START_SEC_CODE_*]!"
# endif

#elif defined STOP_SEC_CONST
# if defined CONST_SEC_OPEN
#  undef CONST_SEC_OPEN

#  undef STOP_SEC_CONST
#  undef MEMMAP_ERROR
# else
#  error "MemMap_Common.h: Const section closed but not opened one. Please close a const section [== usage of *_STOP_SEC_CONST_*] only if you have opened one [== usage of *_START_SEC_CONST_*]!"
# endif

#elif defined STOP_SEC_VAR
# if defined VAR_SEC_OPEN
#  undef VAR_SEC_OPEN

#  undef STOP_SEC_VAR
#  undef MEMMAP_ERROR
# else
#  error "MemMap_Common.h: Var section closed but not opened one. Please close a var section [== usage of *_STOP_SEC_VAR_*] only if you have opened one [== usage of *_START_SEC_VAR_*]!"
# endif
#else

#endif

#include "Os_MemMap.hpp"

#ifdef MEMMAP_ERROR
# error "MemMap_Common.h: Wrong pragma command / unknown memory section used. Please use only valid pragma commands and known memory sections."
#endif

#ifdef MEMMAP_DETECT_ANY_ERROR

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CODE))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CODE is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CODE_FAST))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CODE_FAST is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CODE_ISR))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CODE_ISR is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_FAST_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_CONST_PBCFG))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_CONST_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_PBCFG_GLOBALROOT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_PBCFG_GLOBALROOT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_PBCFG))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CODE_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED))
#  error "Section: CODE_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CODE))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CODE is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CODE_FAST))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CODE_FAST is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CODE_ISR))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CODE_ISR is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_FAST_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_CONST_PBCFG))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_CONST_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_PBCFG_GLOBALROOT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_PBCFG_GLOBALROOT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_PBCFG))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined CONST_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED))
#  error "Section: CONST_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CODE))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CODE is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CODE_FAST))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CODE_FAST is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CODE_ISR))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CODE_ISR is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_FAST_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_FAST_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_CONST_PBCFG))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_CONST_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_PBCFG_GLOBALROOT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_PBCFG_GLOBALROOT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOINIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_PBCFG))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_PBCFG is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT is still defined as well. Please remove the obsolete define!"
# endif

# if((defined VAR_SEC_OPEN) && (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED))
#  error "Section: VAR_SEC_OPEN opened but in addition: START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED is still defined as well. Please remove the obsolete define!"
# endif

#else
# if(((defined CODE_SEC_OPEN) || (defined CONST_SEC_OPEN) || (defined VAR_SEC_OPEN)) && \
      ((defined START_SEC_CODE                                                      ) || \
       (defined START_SEC_CODE_FAST                                                 ) || \
       (defined START_SEC_CODE_ISR                                                  ) || \
       (defined START_SEC_CONST_8BIT                                                ) || \
       (defined START_SEC_CONST_16BIT                                               ) || \
       (defined START_SEC_CONST_32BIT                                               ) || \
       (defined START_SEC_CONST_64BIT                                               ) || \
       (defined START_SEC_CONST_UNSPECIFIED                                         ) || \
       (defined START_SEC_CONST_FAST_8BIT                                           ) || \
       (defined START_SEC_CONST_FAST_16BIT                                          ) || \
       (defined START_SEC_CONST_FAST_32BIT                                          ) || \
       (defined START_SEC_CONST_FAST_64BIT                                          ) || \
       (defined START_SEC_CONST_FAST_UNSPECIFIED                                    ) || \
       (defined START_SEC_CONST_PBCFG                                               ) || \
       (defined START_SEC_PBCFG_GLOBALROOT                                          ) || \
       (defined START_SEC_VAR_INIT_8BIT                                             ) || \
       (defined START_SEC_VAR_INIT_16BIT                                            ) || \
       (defined START_SEC_VAR_INIT_32BIT                                            ) || \
       (defined START_SEC_VAR_INIT_64BIT                                            ) || \
       (defined START_SEC_VAR_INIT_UNSPECIFIED                                      ) || \
       (defined START_SEC_VAR_NOINIT_8BIT                                           ) || \
       (defined START_SEC_VAR_NOINIT_16BIT                                          ) || \
       (defined START_SEC_VAR_NOINIT_32BIT                                          ) || \
       (defined START_SEC_VAR_NOINIT_64BIT                                          ) || \
       (defined START_SEC_VAR_NOINIT_UNSPECIFIED                                    ) || \
       (defined START_SEC_VAR_PBCFG                                                 ) || \
       (defined START_SEC_VAR_ZERO_INIT_8BIT                                        ) || \
       (defined START_SEC_VAR_ZERO_INIT_16BIT                                       ) || \
       (defined START_SEC_VAR_ZERO_INIT_32BIT                                       ) || \
       (defined START_SEC_VAR_ZERO_INIT_64BIT                                       ) || \
       (defined START_SEC_VAR_ZERO_INIT_UNSPECIFIED                                 ) || \
       (defined START_SEC_VAR_FAST_INIT_8BIT                                        ) || \
       (defined START_SEC_VAR_FAST_INIT_16BIT                                       ) || \
       (defined START_SEC_VAR_FAST_INIT_32BIT                                       ) || \
       (defined START_SEC_VAR_FAST_INIT_64BIT                                       ) || \
       (defined START_SEC_VAR_FAST_INIT_UNSPECIFIED                                 ) || \
       (defined START_SEC_VAR_FAST_NOINIT_8BIT                                      ) || \
       (defined START_SEC_VAR_FAST_NOINIT_16BIT                                     ) || \
       (defined START_SEC_VAR_FAST_NOINIT_32BIT                                     ) || \
       (defined START_SEC_VAR_FAST_NOINIT_64BIT                                     ) || \
       (defined START_SEC_VAR_FAST_NOINIT_UNSPECIFIED                               ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_8BIT                                   ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_16BIT                                  ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_32BIT                                  ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_64BIT                                  ) || \
       (defined START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED                            ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_8BIT                                     ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_16BIT                                    ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_32BIT                                    ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_64BIT                                    ) || \
       (defined START_SEC_VAR_NOCACHE_INIT_UNSPECIFIED                              ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_8BIT                                   ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_16BIT                                  ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_32BIT                                  ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_64BIT                                  ) || \
       (defined START_SEC_VAR_NOCACHE_NOINIT_UNSPECIFIED                            ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_8BIT                                ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_16BIT                               ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_32BIT                               ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_64BIT                               ) || \
       (defined START_SEC_VAR_NOCACHE_ZERO_INIT_UNSPECIFIED                         )    \
      ))
#  error "MemMap_Common.h: New section opened before closing the former one. Please close the former code/const/data section before opening a new one. (Check_2)"
# endif

#endif

#ifdef MEMMAP_DETECT_ANY_ERROR
# undef MEMMAP_DETECT_ANY_ERROR
#endif

