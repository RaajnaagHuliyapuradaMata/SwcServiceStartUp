

#ifndef V_CFG_H
#define V_CFG_H

#include "Platform_Types.hpp"

#ifndef V_GEN_GENERATOR_MSR
# define V_GEN_GENERATOR_MSR
#endif

#if defined( CPU_TYPE_64 )
# if(CPU_TYPE == CPU_TYPE_64)
#  if !defined( C_CPUTYPE_64BIT )
#   define C_CPUTYPE_64BIT
#  endif
# endif
#endif

#if(CPU_TYPE == CPU_TYPE_32)
# if !defined( C_CPUTYPE_32BIT )
#  define C_CPUTYPE_32BIT
# endif
#endif

#if(CPU_TYPE == CPU_TYPE_16)
# if !defined( C_CPUTYPE_16BIT )
#  define C_CPUTYPE_16BIT
# endif
#endif

#if(CPU_TYPE == CPU_TYPE_8)
# if !defined( C_CPUTYPE_8BIT )
#  define C_CPUTYPE_8BIT
# endif
#endif

#if(CPU_BIT_ORDER == LSB_FIRST)
# if !defined( C_CPUTYPE_BITORDER_LSB2MSB )
#  define C_CPUTYPE_BITORDER_LSB2MSB
# endif
#endif

#if(CPU_BIT_ORDER == MSB_FIRST)
# if !defined( C_CPUTYPE_BITORDER_MSB2LSB )
#  define C_CPUTYPE_BITORDER_MSB2LSB
# endif
#endif

#endif

