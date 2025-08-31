/*************************************************************************************************************
 * @file    BME34M101_HT32/src/BME34M101.h
 * @version V1.0.1
 * @date    2024-10-10
 * @brief   The header file of BME34M101 driver.
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
#ifndef __BME34M101_H
#define __BME34M101_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
/*
  !!! PORTING !!!
  Include related header files.
*/
#include "ht32.h"
#include "i2c_master_config.h"
#include "ht32_board_config.h"
#include "bmduino_check.h"

#include "middleware/uart_module.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef enum {
  BME34M101_SUCCESS,
  BME34M101_FAILURE
} BME34M101_selStatus;
/* Exported constants --------------------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------------------------------------*/

/* CMD code
0x01: Get soil moisture values
0x02: Get soil temperature values
0x11: Get the number of cascaded modules
0x12: Get module connection status
*/
#define BME34M101_BROADCAST_ID             (0x00)	//broadcast ID

#define BME34M101_READ_OK                  (0)
#define BME34M101_CHECK_ERROR              (1)
#define BME34M101_TIMEOUT_ERROR            (2)

#define BME34M101_UART_TXTIMEOUT           (1000) // uint:baud clock
#define BME34M101_UART_RXTIMEOUT_BYTE      (10) // uint:ms
/* Exported variables --------------------------------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------------------------------------*/
BME34M101_selStatus BME34M101_selSerial(uint32_t serial_number);
void BME34M101_Init(void);
bool BME34M101_isConnected(void);
uint8_t BME34M101_getNumber(void);
uint8_t BME34M101_getMoisture(uint8_t id);
uint8_t BME34M101_getTemperature(uint8_t id);
void BME34M101_getAllMoisture(uint8_t moisBuff[]);
void BME34M101_getAllTemperature(uint8_t tempBuff[]);

void BME34M101_writeBytes(uint8_t wbuf[], uint8_t wlen);
uint8_t BME34M101_readBytes(uint8_t rbuf[], uint8_t rlen);
void _BME34M101_delayMs(uint32_t count);

#ifdef __cplusplus
}
#endif

#endif

