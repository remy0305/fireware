/*********************************************************************************************************//**
 * @file    eeprom_emulation.h
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
#ifndef __EEPROM_EMULATION_H
#define __EEPROM_EMULATION_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_eeprom_config.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#ifndef EEPROM_EMU_LENGTH
  #define EEPROM_EMU_LENGTH           (LIBCFG_FLASH_PAGESIZE / 4 - 2)        /*!< Length Range: 1 ~ ( LIBCFG_FLASH_PAGESIZE / 4 - 2 ) in bytes. */
#endif

#ifndef EEPROM_EMU_START_ADDR
  #define EEPROM_EMU_START_NUM        (2)        /*!< Start from the last Number page. Number Range: 2 ~ ( LIBCFG_FLASH_SIZE / LIBCFG_FLASH_PAGESIZE ) flash available space. */
  #define EEPROM_EMU_START_ADDR       (LIBCFG_FLASH_SIZE - LIBCFG_FLASH_PAGESIZE * EEPROM_EMU_START_NUM) /*!< EEPROM emulation use last Number page of the flash memory.      */
#endif

/* Exported constants --------------------------------------------------------------------------------------*/
#define EEPROM_EMU_PAGE_SIZE          (LIBCFG_FLASH_PAGESIZE)   /*!< Flash Page Size                        */

#define EEPROM_EMU_PAGE0_BASE_ADDR    (EEPROM_EMU_START_ADDR + 0x000)
#define EEPROM_EMU_PAGE0_END_ADDR     (EEPROM_EMU_START_ADDR + (EEPROM_EMU_PAGE_SIZE - 1))

#define EEPROM_EMU_PAGE1_BASE_ADDR    (EEPROM_EMU_START_ADDR + EEPROM_EMU_PAGE_SIZE)
#define EEPROM_EMU_PAGE1_END_ADDR     (EEPROM_EMU_START_ADDR + (2 * EEPROM_EMU_PAGE_SIZE - 1))

/* Exported types ------------------------------------------------------------------------------------------*/
/**
 * @brief EEPROM Emulation status
 */
typedef enum
{
  EEPROM_EMU_PAGE0_ACTIVE    = 0,
  EEPROM_EMU_PAGE1_ACTIVE    = 1,
  EEPROM_EMU_NO_ACTIVE_PAGE  = 2,
  EEPROM_EMU_FLASH_ERROR     = 3,
  EEPROM_EMU_PAGE_FULL       = 4,
  EEPROM_EMU_DATA_NOT_FOUND  = 5,
  EEPROM_EMU_OPERATION_FAIL  = 6,
  EEPROM_EMU_OPERATION_OK    = 7
}EEPROM_EMU_State;

/* Exported functions --------------------------------------------------------------------------------------*/
EEPROM_EMU_State EEPROM_Init(void);
EEPROM_EMU_State EEPROM_Read(u16 DataAddr, u16 *Data);
EEPROM_EMU_State EEPROM_Write(u16 DataAddr, u16 Data);

#ifdef __cplusplus
}
#endif

#endif
