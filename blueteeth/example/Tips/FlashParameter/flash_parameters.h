/*********************************************************************************************************//**
 * @file    Tips/FlashParameter/flash_parameters.h
 * @version $Rev:: 8341         $
 * @date    $Date:: 2025-01-24 #$
 * @brief   The header file of the flash parameters.
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

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __FLASH_PARAMETERS_H
#define __FLASH_PARAMETERS_H

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

typedef __PACKED_H struct{
  u32 parameter1;                /*!< 0x000         parameter1 size is 4 bytes (32 bits)                    */
  u16 parameter2;                /*!< 0x004         parameter2 size is 2 bytes (16 bits)                    */
  u8  parameter3;                /*!< 0x006         parameter3 size is 1 byte (8 bits)                      */
} __PACKED_F Flash_Parameters_InitTypeDef;

#endif
