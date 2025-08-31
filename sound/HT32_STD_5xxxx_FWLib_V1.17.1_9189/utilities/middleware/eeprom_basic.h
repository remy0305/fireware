/*********************************************************************************************************//**
 * @file    eeprom_basic.h
 * @version $Rev:: 527          $
 * @date    $Date:: 2022-04-13 #$
 * @brief   The header file of EEPROM emulation APIs.
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
#ifndef __EEPROM_BASIC_H
#define __EEPROM_BASIC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_eeprom_config.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#ifndef EEPROM_BASIC_LENGTH
  #define EEPROM_BASIC_LENGTH                   LIBCFG_FLASH_PAGESIZE     /*!< Length Range: 4 ~ ( LIBCFG_FLASH_PAGESIZE ) in 4 bytes. */
#endif

#ifndef EEPROM_BASIC_START_ADDR
  #define EEPROM_BASIC_START_NUM                1           /*!< Start from the last Number page. Number Range: 1 ~ ( LIBCFG_FLASH_SIZE / LIBCFG_FLASH_PAGESIZE ) flash available space.  */
  #define EEPROM_BASIC_START_ADDR               (LIBCFG_FLASH_SIZE - LIBCFG_FLASH_PAGESIZE * EEPROM_BASIC_START_NUM) /*!< EEPROM basic use last Number page of the flash memory.          */
#endif

/* Exported functions --------------------------------------------------------------------------------------*/
u8 EEPROM_Init(void);
u8 EEPROM_Read(const u32 Address);
void EEPROM_Write(u32 DataAddr, u8 Data);

#ifdef __cplusplus
}
#endif

#endif
