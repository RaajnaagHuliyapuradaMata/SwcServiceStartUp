#pragma once
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
extern uint8             VERSION_GetEcuProgramInformationPart1 (uint8* ucData,  uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetEcuProgramInformationPart2 (uint8* ucData,  uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetHmacSignature              (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetComponentAndSwType         (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern tDescriptorBlock* VERSION_GetPointerToDescriptorBlock   (uint8  ucApplFbl);
extern uint32*           VERSION_GetPointerToSHA256Hash        (uint8  ucApplFbl);
extern uint8             VERSION_GetPcbaId                     (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetComponentId                (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetModeId                     (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetAuxId                      (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetGenealogyVersion           (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_GetTfsChangeset               (uint8* pBuffer, uint8 ucLen, uint8 ucApplFbl);
extern uint8             VERSION_ucDigitToAscii                (uint8  ucDigit);


/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
