/******************************************************************************/
/* File   : SwcServiceStartUp.hpp                                             */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern uint8                                        SwcServiceStartUp_u8GetEcuProgramInformationPart1 (uint8* lptru8Data,  uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetEcuProgramInformationPart2 (uint8* lptru8Data,  uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetHmacSignature              (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetComponentAndSwType         (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern Type_CfgSwcServiceStartUp_stDescriptorBlock* SwcServiceStartUp_ptrstGetDescriptorBlock         (Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint32*                                      SwcServiceStartUp_ptru32GetPointerToSHA256Hash    (Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetPcbaId                     (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetComponentId                (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetModeId                     (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetAuxId                      (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetGenealogyVersion           (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8GetTfsChangeset               (uint8* pBuffer, uint8 lu8Len, Type_CfgSwcServiceStartUp_eProgramSw leProgramSw);
extern uint8                                        SwcServiceStartUp_u8DigitToAscii                  (uint8 ucDigit);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
