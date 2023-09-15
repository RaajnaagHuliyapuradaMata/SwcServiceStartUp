

#ifndef IO_TYPES_H
#define IO_TYPES_H

#include "fbl_def.hpp"

#define IO_E_OK         0x00u
#define IO_E_NOT_OK     0x01u
#define IO_E_ERASED     0xE5u

typedef vuint8    IO_U8;
typedef vuint16   IO_U16;
typedef vuint32   IO_U32;
typedef vsint8    IO_S8;
typedef vsint16   IO_S16;
typedef vsint32   IO_S32;

#if( !defined( C_CPUTYPE_8BIT ) || \
    defined( FBL_PROCESSOR_BANKED ))
typedef vuint32   IO_SizeType;
typedef vuint32   IO_PositionType;
#else
typedef vuint16   IO_SizeType;
typedef vuint16   IO_PositionType;
#endif

typedef vuint16   IO_ErrorType;
typedef vuint8*   IO_MemPtrType;

#endif

