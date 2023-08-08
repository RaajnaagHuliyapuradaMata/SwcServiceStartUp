

#ifndef __FBLWRAPPERFLASH_RH850RV40HIS_H__
#define __FBLWRAPPERFLASH_RH850RV40HIS_H__

#define FBLWRAPPERFLASH_RH850RV40HIS_VERSION           0x0111u
#define FBLWRAPPERFLASH_RH850RV40HIS_RELEASE_VERSION   0x00u

IO_ErrorType FlashDriver_InitSync ( void * );
IO_ErrorType FlashDriver_DeinitSync ( void * );
IO_ErrorType FlashDriver_RWriteSync ( IO_MemPtrType, IO_SizeType, IO_PositionType );
IO_ErrorType FlashDriver_REraseSync ( IO_SizeType, IO_PositionType );
IO_ErrorType FlashDriver_RReadSync ( IO_MemPtrType, IO_SizeType, IO_PositionType );
IO_U32 FlashDriver_GetVersionOfDriver( void );
#if defined( FLASH_ENABLE_SET_RESETVECTOR_API )
IO_ErrorType FlashDriver_SetResetVector ( IO_PositionType, IO_SizeType );
#endif
# if defined( FLASH_ENABLE_OPTIONBYTE_API )
IO_ErrorType FlashDriver_GetOptionByte ( IO_U32 *, IO_SizeType );
IO_ErrorType FlashDriver_SetOptionByte ( IO_U32 *, IO_SizeType );
# endif

# define FLASHCODE_START_SEC_VAR_EXPORT
# include "MemMap.hpp"
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 flashCode[FLASH_SIZE];
# define FLASHCODE_STOP_SEC_VAR_EXPORT
# include "MemMap.hpp"

#endif

