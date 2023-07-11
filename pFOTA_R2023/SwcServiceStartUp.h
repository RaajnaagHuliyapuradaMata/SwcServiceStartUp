#pragma once
/******************************************************************************/
/* File   : SwcServiceStartUp.h                                               */
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
typedef enum{
      SwcServiceStartUp_eError_None
   ,  SwcServiceStartUp_eError_HeaderREAD_FAILED
   ,  SwcServiceStartUp_eError_HeaderMAGIC_FAILED
   ,  SwcServiceStartUp_eError_HeaderVERSION_FAILED
   ,  SwcServiceStartUp_eError_HeaderLENGTH_FAILED
   ,  SwcServiceStartUp_eError_VALIDITY_FAILED
   ,  SwcServiceStartUp_eError_SWCSERVICESTARTUP_BMHEADER_INCORRECT
   ,  SwcServiceStartUp_eError_SWCSERVICESTARTUP_VERIFICATION_FAILED
   ,  SwcServiceStartUp_eError_KEY_NOT_AVAILABLE
   ,  SwcServiceStartUp_eError_UpdaterSEARCH_INIT_FAILED
   ,  SwcServiceStartUp_eError_UpdaterSEARCH_NEXT_FINISHED
   ,  SwcServiceStartUp_eError_UpdaterHEADER_ADDRESS
   ,  SwcServiceStartUp_eError_UpdaterHEADER_READ_ERROR
   ,  SwcServiceStartUp_eError_UpdaterHEADER_CONSISTENCY
   ,  SwcServiceStartUp_eError_UpdaterHEADER_TYPE
   ,  SwcServiceStartUp_eError_UpdaterBLOCK_VALIDITY
   ,  SwcServiceStartUp_eError_UpdaterHEADER_CMAC_READ
   ,  SwcServiceStartUp_eError_UpdaterHEADER_CMAC_VERIFY
   ,  SwcServiceStartUp_eError_UpdaterVERIFY
   ,  SwcServiceStartUp_eError_LoaderPOINTER_NULL
   ,  SwcServiceStartUp_eError_LoaderTOO_LARGE
   ,  SwcServiceStartUp_eError_LoaderSIZE
   ,  SwcServiceStartUp_eError_LoaderGET_MAC
   ,  SwcServiceStartUp_eError_LoaderGET_SWCSERVICESTARTUP_MAC
   ,  SwcServiceStartUp_eError_ReProgLoaderDESCR
   ,  SwcServiceStartUp_eError_ReProgLoaderINVALID
   ,  SwcServiceStartUp_eError_ReProgLoaderBMHEADER_INCORRECT
   ,  SwcServiceStartUp_eError_ReProgLoaderVERIFY_HEADER
   ,  SwcServiceStartUp_eError_ReProgLoaderVERIFY_AREAS
   ,  SwcServiceStartUp_eError_ReProgLoaderMAGIC_FLAG
   ,  SwcServiceStartUp_eError_ReProgLoaderBLOCK_COUNT
   ,  SwcServiceStartUp_eError_TargetLIST_INIT
   ,  SwcServiceStartUp_eError_TargetINVALID
   ,  SwcServiceStartUp_eError_TargetNO_VALID_HEADER
   ,  SwcServiceStartUp_eError_TargetVERIFICATION_FAILED
   ,  SwcServiceStartUp_eError_TargetINVALID_ADDRESS
   ,  SwcServiceStartUp_eError_TargetDEP_MANDATORY_MISSING
   ,  SwcServiceStartUp_eError_TargetDEP_NO_VALID_HEADER
   ,  SwcServiceStartUp_eError_TargetDEP_VERIFY_FAILED
   ,  SwcServiceStartUp_eError_END_OF_MAIN_REACHED
   ,  SwcServiceStartUp_eError_ApplCheckMAC_READ_FAIL
   ,  SwcServiceStartUp_eError_ApplCheckMAC_BUF_LENGTH
   ,  SwcServiceStartUp_eError_ApplCheckMAC_READ_FAIL_LENGTH
}Type_SwcServiceStartUp_eError;

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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

