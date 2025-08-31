/*********************************************************************************************************//**
 * @file    BM7701_00_1_HT32/src/BM7701_00_1.h
 * @version V1.0.1
 * @date    2024-09-23
 * @brief   The header file of BM7701_00_1 driver.
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
#ifndef _BM7701_00_1_H
#define _BM7701_00_1_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "i2c_master_config.h"
#include "ht32_board_config.h"
#include "bmduino_check.h"

#include "middleware/i2c_master.h"
#include "middleware/uart_module.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef struct 
{  
  u8    key;
  u8    serial;
  u8    checksum;
} KEY_MESSAGE;

typedef enum {
  BM7701_00_1_SUCCESS,
  BM7701_00_1_FAILURE
} BM7701_00_1_selStatus;
/* Exported constants --------------------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------------------------------------*/

#define BM7701_00_1_UART_TXTIMEOUT          1000   //uint:baud clock
#define BM7701_00_1_UART_RXTIMEOUT_BYTE     10      //uint:ms

#define BM7701_00_1_READ_OK          0
#define BM7701_00_1_READ_ERROR       1
#define BM7701_00_1_TIMEOUT_ERROR    2


#define BM7701_00_1_EVT_RETURN_TIME 150 

#define BM7701_00_1_DISABLE         false
#define BM7701_00_1_ENABLE          true

#define BM7701_00_1_COMMAND          0x77      //Command
#define BM7701_00_1_EVENT            0x78      //Event

#define BM7701_00_1_API_CONNECTED      0x81
#define BM7701_00_1_API_DISCONNECTED   0x82
#define BM7701_00_1_DATA_RECEIVED      0x83
#define BM7701_00_1_API_ERROR          0x84


#define BM7701_00_1_BAUD_9600          9600
#define BM7701_00_1_BAUD_14400         14400
#define BM7701_00_1_BAUD_19200         19200
#define BM7701_00_1_BAUD_38400         38400
#define BM7701_00_1_BAUD_57600         57600
#define BM7701_00_1_BAUD_115200        115200
#define BM7701_00_1_BAUD_125000        125000


#define BM7701_00_1_FEATURE_DIR        0x00
#define BM7701_00_1_FEATURE_OR         0x10
#define BM7701_00_1_FEATURE_AND        0x20

#define BM7701_00_1_APPEND_NAME        0x00
#define BM7701_00_1_NO_APPEND_NAME     0x10


#define BM7701_00_1_ADV_DATA_NOT_APPEND_NAME     0x00000004
#define BM7701_00_1_SW_PARA_UPDATA               0x00000010
#define BM7701_00_1_SW_PARA_ERASE                0x00000020
#define BM7701_00_1_AUTO_SEND_SATUS              0x00000080
#define BM7701_00_1_EXTERNAL32K                  0x00001000
#define BM7701_00_1_RF_CALIB_FORCE               0x02000000
#define BM7701_00_1_CLOCK_32K_OUT                0x20000000


#define BM7701_00_1_SW_BOOT              0x00000000
#define BM7701_00_1_SW_STACK             0x00002000
#define BM7701_00_1_SW_APP1              0x0001A000
#define BM7701_00_1_SW_APP2              0x00020E00           //BlockAddr


#define BM7701_00_1_NORMAL              0x00
#define BM7701_00_1_DEEPSLEEP           0x01
#define BM7701_00_1_POWERDOWN           0x15


#define BM7701_00_1_API_UnknowService_OP     0xFFF0
#define BM7701_00_1_API_NotifyFFF1_OP        0xFFF1
#define BM7701_00_1_API_WithoutResponse_OP   0xFFF2
#define BM7701_00_1_API_STATUS_OP            0x0000
#define BM7701_00_1_API_DISCONN_OP           0x0002
#define BM7701_00_1_API_CONN_INTV_OP         0x0003
#define BM7701_00_1_API_CONN_INTV1_OP        0x0004
#define BM7701_00_1_API_BD_NAME_OP           0x0005
#define BM7701_00_1_API_BD_ADDR_OP           0x0006
#define BM7701_00_1_API_ADV_EN_OP            0x0007
#define BM7701_00_1_API_ADV_INTV_OP          0x0008
#define BM7701_00_1_API_ADV_DATA_OP          0x0009
#define BM7701_00_1_API_SCAN_DATA_OP         0x000A
#define BM7701_00_1_API_TX_POWER_OP          0x000B
#define BM7701_00_1_API_XTAL_OFFSET_OP       0x000E
#define BM7701_00_1_API_PEER_BD_ADDR_OP      0x000F
#define BM7701_00_1_API_FEATURE_OP           0x0010
#define BM7701_00_1_API_VERSION_OP           0x0020
#define BM7701_00_1_API_POWER_SAVING_OP      0x0025
#define BM7701_00_1_API_BAUDRATE_OP          0x0026
#define BM7701_00_1_API_BAUDRATE_MAX_OP      0x0027
#define BM7701_00_1_API_RESET_OP             0x0028
#define BM7701_00_1_API_WHILELIST_OP         0x002A

/* Exported variables --------------------------------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------------------------------------*/
BM7701_00_1_selStatus BM7701_00_1_selSerial(uint32_t serial_number);
void BM7701_00_1_Init(uint32_t BaudRate);
bool BM7701_00_1_setAdvCtrl(bool ctrl);                                                                                //Turn on broadcast
bool BM7701_00_1_disconnect(void);                                                                                                 //Disconnect 
bool BM7701_00_1_writeData(uint8_t dataBuf[],uint8_t length);                                                                       //BC7701 Send Data
bool BM7701_00_1_readData(uint8_t receiveBuff[],uint8_t length);   
bool BM7701_00_1_setAdvIntv(uint16_t min,uint16_t max,uint8_t advMap);                                                          //Set Advertise Interval
bool BM7701_00_1_setAdvData(uint8_t appendName,uint8_t length,uint8_t AdvData[]);                                                                  //Set Advertise Data
bool BM7701_00_1_setScanData(uint8_t length,uint8_t scanData[]);                                                                //Set Scan Data
bool BM7701_00_1_setConnIntv(uint16_t interval);                                                                               //Set Connected Interval
bool BM7701_00_1_setConnIntv1(uint16_t minIntv,uint16_t maxIntv,uint16_t latency,uint16_t timeout);                            //Set Connected Interval1 
bool BM7701_00_1_setName(uint8_t length,uint8_t name[]);                                                                        //Set Device Name
bool BM7701_00_1_setAddress(uint8_t address[]);                                                                                 //Set MAC address                                
bool BM7701_00_1_setFeature(uint8_t cmdFlag,uint32_t codeFeature);                                                                           //Set Feature
bool BM7701_00_1_setPowerSaving(uint8_t mode);                                                                                   //Enter Sleep mode
bool BM7701_00_1_setWhiteList(bool erase,uint8_t whiteListAddr[],uint8_t mask[]);                                                //Set Whilelist addr
bool BM7701_00_1_setTXpower(uint8_t power);                                                                                    //Set TX power
bool BM7701_00_1_setCrystalOffset(uint8_t cload);                                                                                  //Set Xtal Cload
bool BM7701_00_1_restoreDefault(void);                                                                                              //Software Reset,no save configuration                                                                 
bool BM7701_00_1_reset(void);                                                                                          //Software Reset,save configuration                                                                                               //BC7701 Receive Data
void BM7701_00_1_wakeUp(void);                                                                                                  //Dummy wake up from deepsleep/powerdown mode  
bool BM7701_00_1__sendCMD(uint16_t type,uint8_t cmd_flag,uint8_t cmd_length,uint8_t value[]);
void BM7701_00_1_sendCMD_NoResponse(uint16_t type,uint8_t cmd_flag,uint8_t cmd_length,uint8_t value[]);
void BM7701_00_1_writeBytes(uint8_t wbuf[], uint8_t wlen);
uint8_t BM7701_00_1_readBytes(uint8_t rbuf[], uint8_t rlen);
uint8_t  BM7701_00_1_analysis(void);
void _BM7701_00_1_clearBuf(void);
void _BM7701_00_1_delay(vu32 count);


#ifdef __cplusplus
}
#endif

#endif

