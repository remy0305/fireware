/*********************************************************************************************************//**
 * @file    i2c_master.h
 * @version $Rev:: 1243         $
 * @date    $Date:: 2024-06-12 #$
 * @brief   The header file of I2C Master (interrupt mode with buffer).
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
#ifndef __I2C_MASTER_H
#define __I2C_MASTER_H

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup I2C I2C
  * @{
  */

/** @addtogroup I2C_Master I2C Master
  * @{
  */

/* Includes ------------------------------------------------------------------------------------------------*/
/* If i2c_master_config.h is missing, 
   1. please copy utilities/middleware/i2c_master_config_templet.h to the folder of main program
   2. and change the file name to i2c_master_config.h. */
#include "i2c_master_config.h"
#include "ht32_board_config.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#if (I2C_MASTER_SW_TIMEOUT_MODE == 2)
#define I2CMASTER_GETTICK   Time_GetTick            /* Call from external function                          */
#endif

/* Exported typedef ----------------------------------------------------------------------------------------*/
/**
 * @brief I2C Master status
 */
typedef enum
{
  I2C_MASTER_GOING        = 0,
  I2C_MASTER_FINISH       = 1,
  I2C_MASTER_SW_TIMEOUT   = 2,
  I2C_MASTER_NACK         = 3,
  I2C_MASTER_BUSERR       = 4,
  I2C_MASTER_HW_TIMEOUT   = 5,
} I2CMaster_Status_Enum;

/**
 * @brief I2C Master command
 */
typedef enum
{
  I2C_MASTER_CMD_READ          = 0,
  I2C_MASTER_CMD_WRITE         = 1,
  I2C_MASTER_CMD_WRITEREAD     = 2,
  I2C_MASTER_CMD_WRITESTOPREAD = 3,
} I2CMaster_CMD_Enum;

/**
 * @brief I2C Master buffer struct
 */
typedef struct
{
  u8 *puBuffer;
  u32 uLength;
} I2CMaster_BufferTypedef;

/**
 * @brief I2C Master struct
 */
typedef struct
{
  u32 uSlaveAddress;
  I2CMaster_BufferTypedef Tx;
  I2CMaster_BufferTypedef Rx;
  u32 uTimeout_us;
  I2CMaster_CMD_Enum Command;
  bool isDynamicOnOff_I2C;
} I2CMaster_Typedef;

/* Exported constants --------------------------------------------------------------------------------------*/
#define   I2C_MASTER_CH0    0
#define   I2C_MASTER_CH1    1
#define   I2C_MASTER_CH2    2
#define   I2C_MASTER_CH3    3

/* Exported macro ------------------------------------------------------------------------------------------*/
#define DIFF_TICK(start,current)      ((current) >= (start) ? (u32)(current - start) : (u32)(0xFFFFFFFF - start + current + 1))

#if (I2C_MASTER_SW_TIMEOUT_BASE >= 1000000)
#define TRANSFER_TIMER(us)            (u32) (us * (I2C_MASTER_SW_TIMEOUT_BASE / 1000000))
#else
#define TRANSFER_TIMER(us)            (u32) (us / (1000000 / I2C_MASTER_SW_TIMEOUT_BASE))
#endif

#ifdef HTCFG_I2CM_CH0
#define I2CM_CH0_IRQ                   STRCAT2(HTCFG_I2CM_CH0, _IRQn)
#define I2CM_CH0_IRQHandler            STRCAT2(HTCFG_I2CM_CH0, _IRQHandler)
#endif
#ifdef HTCFG_I2CM_CH1
#define I2CM_CH1_IRQ                   STRCAT2(HTCFG_I2CM_CH1, _IRQn)
#define I2CM_CH1_IRQHandler            STRCAT2(HTCFG_I2CM_CH1, _IRQHandler)
#endif
#ifdef HTCFG_I2CM_CH2
#define I2CM_CH2_IRQ                   STRCAT2(HTCFG_I2CM_CH2, _IRQn)
#define I2CM_CH2_IRQHandler            STRCAT2(HTCFG_I2CM_CH2, _IRQHandler)
#endif
#ifdef HTCFG_I2CM_CH3
#define I2CM_CH3_IRQ                   STRCAT2(HTCFG_I2CM_CH3, _IRQn)
#define I2CM_CH3_IRQHandler            STRCAT2(HTCFG_I2CM_CH3, _IRQHandler)
#endif

/* Exported functions --------------------------------------------------------------------------------------*/
void I2CMaster_Init(u32 CH, u32 uMasterAddress, u32 uClockSpeed);
void I2CMaster_Write(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_Read(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_WriteRead(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_WriteStopRead(u32 CH, I2CMaster_Typedef *pI2CMaster);
void I2CMaster_Start(u32 CH, I2CMaster_Typedef *pI2CMaster);
I2CMaster_Status_Enum I2CMaster_GetStatus(u32 CH);
u32 I2CMaster_GetRxIndex(u32 CH);
void I2CMaster_UpdateRxLength(u32 CH, u32 uLength);

void I2CMaster_IRQHandler(u32 CH);
void I2CMaster_TimeoutHandler(void);

#if FREERTOS_I2C
#include "FreeRTOS.h"
#include "semphr.h"

void I2CMaster_Init_FreeRTOS(u32 CH, u32 uMasterAddress, u32 uClockSpeed);
u32 I2CMaster_Write_FreeRTOS(u32 CH, I2CMaster_Typedef *pI2CMaster, u32 Timeout);
u32 I2CMaster_Read_FreeRTOS(u32 CH, I2CMaster_Typedef *pI2CMaster, u32 Timeout);
u32 I2CMaster_WriteRead_FreeRTOS(u32 CH, I2CMaster_Typedef *pI2CMaster, u32 Timeout);
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif
