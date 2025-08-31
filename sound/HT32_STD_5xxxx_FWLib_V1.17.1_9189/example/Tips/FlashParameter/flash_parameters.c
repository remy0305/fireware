/*********************************************************************************************************//**
 * @file    Tips/FlashParameter/flash_parameters.c
 * @version $Rev:: 8459         $
 * @date    $Date:: 2025-03-06 #$
 * @brief   The flash parameters.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "flash_parameters.h"

/* Parameter -----------------------------------------------------------------------------------------------*/
const Flash_Parameters_InitTypeDef Parameters = {0x12345678, 0xABCD, 0xEF};    //Setting parameters value.

/*
Note:
  The parameter types and address order are controlled by Flash_Parameters_InitTypeDef defined in 
  "flash_parameters.h", while the starting address for parameter configuration is specified in the
  "linker.lin" file.
*/
