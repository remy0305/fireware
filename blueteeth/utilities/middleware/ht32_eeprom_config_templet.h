/*********************************************************************************************************//**
 * @file    ht32_eeprom_config.h
 * @version $Rev:: 699          $
 * @date    $Date:: 2022-12-16 #$
 * @brief   The header file of eeprom configuration.
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
#ifndef __HT32_EEPROM_CONFIG_H
#define __HT32_EEPROM_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#define EEPROM_EMU_SEQUENTIAL_ADDR                (1)  /* Sequential address can only use address like (0, 1, 2 ,3...), non sequential address (20, 24, 30...) is not allowed.  */
                                                       /* It helps to remove "u16 EEPROM_VarAddrTab[EEPROM_EMU_LENGTH]" to save memory size.                                    */
                                                       /* This feature requires the "eeprom_emulation.c" SVN version >= 698.                                                    */

#define EEPROM_EMU_LENGTH                         (4)  /*!< Length Range: 1 ~ (LIBCFG_FLASH_PAGESIZE / 4 - 2 ). */

#define EEPROM_EMU_START_NUM                      (2)  /*!< Start from the last number page. Number Range: 2 ~ (LIBCFG_FLASH_SIZE / LIBCFG_FLASH_PAGESIZE ).   */

#define EEPROM_EMU_START_ADDR                     (LIBCFG_FLASH_SIZE - LIBCFG_FLASH_PAGESIZE * EEPROM_EMU_START_NUM)
                                                       /*!< EEPROM emulation use last Number page of the flash memory.                                         */

#ifdef __cplusplus
}
#endif

#endif
