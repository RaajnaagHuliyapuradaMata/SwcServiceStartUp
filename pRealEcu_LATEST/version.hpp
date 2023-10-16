#ifndef _VERSION_H
#define _VERSION_H

#include "types.hpp"

#define cAPP_DESCRIPTOR_BLOCK_ROM_ADDRESS                      (void*)0x00077b00
#define cFBL_DESCRIPTOR_BLOCK_ROM_ADDRESS                      (void*)0x0001ff00
#define cAPPLICATION_START_ADDRESS                               (uint32)0x20000
#define cAPPLICATION_END_ADDRESS                                 (uint32)0x77BFF
#define cAPP                                                                   0
#define cFBL                                                                   1
#define cSW_VERSION_MAJOR                                              (uint8)02
#define cSW_VERSION_MINOR                                              (uint8)01
#define cSW_VERSION_MICRO                                           (uint16)0004
#define cTFS_CHANGESET                           'C','S','0','0','1','9','3','3'

#define PRODUCTION_SW                                                        0x0
#define DEVELOPMENT_SW                                                       0x1
#define SW_CATEGORY                                                PRODUCTION_SW
//#define SW_CATEGORY                                             DEVELOPMENT_SW

#define cSCHEMA_VERSION                                             (uint8) 0x01
#define cCOMPONENT_ID                                               (uint16)0x003A
#define cPCBA_ID                                                    (uint8) 0x01
#define cAUX_ID                                                     (uint8) 0x01
#define cMODE_ID                                                    (uint16)0x0000
#define cPROG_TYPE_BL                                               (uint8) 0x02
#define cPROG_TYPE_APP                                              (uint8) 0x05
#define cGENEALOGY_INDEX                                            (uint8) 0x01
#define cDL_PROTOCOL_VERS                                           (uint16)0x0001
#define cSTRING_ECU_PROGRAM_INFO_1_LENGTH                                     17
#define cSTRING_ECU_PROGRAM_INFO_2_LENGTH                                     38
#define cSTRING_SIZ_SCHEMA_VERS                                                1
#define cSTRING_SIZ_COMP_ID                                                    2
#define cSTRING_SIZ_PCBA_ID                                                    1
#define cSTRING_SIZ_AUX_ID                                                     1
#define cSTRING_SIZ_MODE_ID                                                    2
#define cSTRING_SIZ_PROG_TYPE                                                  1
#define cSTRING_SIZ_DL_PROT_VERS                                               2
#define cSTRING_SIZ_INDEX                                                      1
#define cSTRING_SIZ_MAJOR                                                      1
#define cSTRING_SIZ_MINOR                                                      1
#define cSTRING_SIZ_MICRO                                                      2
#define cSTRING_SIZ_CRC32                                                      4
#define cSTRING_SIZ_HASH                                                      16
#define cSTRING_SIZ_COMPANDSWTYPE ((cSTRING_SIZ_COMP_ID-1) + (cSTRING_SIZ_DL_PROT_VERS-1) + cSTRING_SIZ_PROG_TYPE)
#define cSTRING_SIZ_FULLGENBLOCK                                             133
#define cSTRING_SIZ_TFSCS                                                      8
#define cSTRING_IDX_SCHEMA_VERS                                                0
#define cSTRING_IDX_COMP_ID   cSTRING_IDX_SCHEMA_VERS + cSTRING_SIZ_SCHEMA_VERS
#define cSTRING_IDX_PCBA_ID   cSTRING_IDX_COMP_ID     + cSTRING_SIZ_COMP_ID
#define cSTRING_IDX_AUX_ID    cSTRING_IDX_PCBA_ID     + cSTRING_SIZ_PCBA_ID
#define cSTRING_IDX_MODE_ID   cSTRING_IDX_AUX_ID      + cSTRING_SIZ_AUX_ID
#define cSTRING_IDX_PROG_TYPE cSTRING_IDX_MODE_ID     + cSTRING_SIZ_MODE_ID
#define cSTRING_IDX_INDEX     cSTRING_IDX_PROG_TYPE   + cSTRING_SIZ_PROG_TYPE
#define cSTRING_IDX_MAJOR     cSTRING_IDX_INDEX       + cSTRING_SIZ_INDEX
#define cSTRING_IDX_MINOR     cSTRING_IDX_MAJOR       + cSTRING_SIZ_MAJOR
#define cSTRING_IDX_MICRO     cSTRING_IDX_MINOR       + cSTRING_SIZ_MINOR
#define cSTRING_IDX_CRC       cSTRING_IDX_MICRO       + cSTRING_SIZ_MICRO

typedef struct{
   uint8  ucSchemaVersion;
   uint8  ucUnused1;
   uint16 ushComponentId;
   uint8  ucPcbaId;
   uint8  ucAuxId;
   uint16 ushModeId;
   uint8  aucTfsChangeset[8];
   uint8  ucEcuProgramType;
   uint8  ucUnused2;
   uint16 ushDownloadProtocolVersion;
   uint32 ulStartupAddress;
   uint32 ulCrc32;
   uint8  aucUnused3[4];
   uint8  ucMajor;
   uint8  ucMinor;
   uint16 ushMicro;
   uint8  ucIndex;
   uint8  ucDummy1[183];
   uint32 ulCrc32App;
   uint8  ucHash[16];
   uint8  ucDummy2[14];
   uint8  ucChecksum[2];
}tDescriptorBlock;

extern uint8 VERSION_GetEcuProgramInformationPart1(uint8* ucData, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetEcuProgramInformationPart2(uint8* ucData, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetHmacSignature(uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetComponentAndSwType  (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern tDescriptorBlock* VERSION_GetPointerToDescriptorBlock(uint8 ucApplFbl);
extern uint32* VERSION_GetPointerToSHA256Hash(uint8 ucApplFbl);
extern uint8 VERSION_GetPcbaId              (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetComponentId         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetModeId              (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetAuxId               (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetGenealogyVersion    (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_GetTfsChangeset        (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8 VERSION_ucDigitToAscii   (uint8 ucDigit);
static uint8 VERSION_ucDecimalToBcd   (uint8 ucNumber);
static uint8 VERSION_GetSchemaVersion (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetProgType      (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetMajor         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetMinor         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetMicro         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetIndex         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
static uint8 VERSION_GetCrc32         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);

#endif
