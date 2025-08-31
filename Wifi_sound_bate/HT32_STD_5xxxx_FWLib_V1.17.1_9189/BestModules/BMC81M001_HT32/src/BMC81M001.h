/*********************************************************************************************************//**
 * @file    BMC81M001_HT32/src/BMC81M001.h
 * @version V1.0.1
 * @date    2024-10-10
 * @brief   The header file of BMC81M001 driver.
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
#ifndef _BMC81M001_H
#define _BMC81M001_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "i2c_master_config.h"
#include "ht32_board_config.h"
#include "bmduino_check.h"
#include "string.h"
#include "middleware/i2c_master.h"
#include "middleware/uart_module.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef enum {
  BMC81M001_SUCCESS,
  BMC81M001_FAILURE
} BMC81M001_selStatus;
/* Exported constants --------------------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------------------------------------*/

#define BMC81M001_UART_TXTIMEOUT          1000   //uint:baud clock
#define BMC81M001_UART_RXTIMEOUT_BYTE     10      //uint:ms

#define BMC81M001_baudRate 115200
#define BMC81M001_SEND_SUCCESS 1
#define BMC81M001_SEND_FAIL 0

#define RES_MAX_LENGTH 200
/* Exported variables --------------------------------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------------------------------------*/
BMC81M001_selStatus BMC81M001_selSerial(uint32_t serial_number);
void BMC81M001_Init(uint32_t BaudRate); 
bool BMC81M001_connectToAP(char ssid[],char pass[]);
bool BMC81M001_connectTCP(char ip[],int port);
bool BMC81M001_writeDataTcp(int Dlength,char Dbuffer[]);
bool BMC81M001_readDataTcp(char readbuff[]);
bool BMC81M001_configMqtt(char clientid[],char username[],char password[],char mqtt_host[],int server_port);
bool BMC81M001_setPublishTopic(char publishtopic[]);
bool BMC81M001_setSubscribetopic(char subscribetopic[]);
bool BMC81M001_setTopic(char topic[]);
bool BMC81M001_writeByte(char Dbuffer[],int Dlength,char topic[]);
void BMC81M001_readIotData(char IotReciveBuff[],int *IotReciveBufflen,char IotReciveTopic[]);
bool BMC81M001_reset(void);
void BMC81M001_writeBytes(char wbuf[]);
void BMC81M001_readBytes(uint8_t rbuf[],int timeout, uint8_t reTry);
int BMC81M001_sendATCommand(char StringstrCmd[],uint8_t reTry);
void BMC81M001_arrayAdd(char array1[],char array2[]);
void _BMC81M001_clearBuf(void);
void _BMC81M001_delay(vu32 count);
void BMC81M001_clearResponse(char Dbuffer[]);
int BMC81M001_arrayFind(char array1[],char array2);
#ifdef __cplusplus
}
#endif

#endif

