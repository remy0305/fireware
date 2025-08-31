/*********************************************************************************************************//**
 * @file    USART/LIN_Slave/lin.h
 * @version $Rev:: 7548         $
 * @date    $Date:: 2024-01-30 #$
 * @brief   The header file of LIN bus.
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
#ifndef __LIN_H
#define __LIN_H

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup LIN_Slave
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define LIN_BAUDRATE                              (19200)
#define GET_TICK()                                (Time_GetTick())

/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef struct
{
  union {
  u8 uPID;
  u8 uLINState;
  };
  u8 *pBuffer;
  u8 uLnegth;
} LIN_RxInfoTypeDef;

typedef void (*LIN_PIDHandler_CallBack_TypeDef)(u8);

/* Exported constants --------------------------------------------------------------------------------------*/
#define LIN_TIMEOUT                               (-1)
#define LIN_ERROR                                 (-2)
#define LIN_CHECKSUMERROR                         (-3)
#define LIN_NOTUSE                                (0)
#define LIN_PROCESS                               (1)
#define LIN_FINISH                                (2)

#define LIN_CHECKSUM_CLASSIC                      (0)
#define LIN_CHECKSUM_ENHANCED                     (1)

// For gLINState
#define LIN_IDLE                                  (0x00)
#define LIN_SEND_BREAK                            (0x10)
#define LIN_BREAK_DETECTED                        (0x20)
#define LIN_SYNCED                                (0x30)
#define LIN_PID                                   (0x40)
#define LIN_TX                                    (0x50)
#define LIN_TX_END                                (0x51)
#define LIN_RX                                    (0x60)
#define LIN_RX_READY                              (0x61)
#define LIN_RX_DEFAULT                            (0x62)

#define LIN_SYNC_ERROR                            (0x3A)
#define LIN_PID_ERROR                             (0x4A)
#define LIN_RX_OVERWRITE                          (0x6A)
#define LIN_RX_CHECKSUMERROR                      (0x6B)
#define LIN_STATE_ERROR                           (0xE0)

/* Exported macro ------------------------------------------------------------------------------------------*/
#define LIN_MAX_FRAME_TIME(BYTES)                 ((((13 + 1 + 10 + 10 + (BYTES * 10) + 10) * 1000000) / LIN_BAUDRATE) * 1.4) // Break + Delimiter + SYNC + PID + n BYTES + Checksum
#define LIN_MAX_HEADER_TIME                       ((((13 + 1 + 10 + 10) * 1000000) / LIN_BAUDRATE) * 1.4) // Break + Delimiter + SYNC + PID
#define LIN_MAX_RESPONSE_TIME(BYTES)              (((((BYTES * 10) + 10) * 1000000) / LIN_BAUDRATE) * 1.4) // n BYTES + Checksum
#define LIN_GETID(PID)                            (PID & 0x3F)

/* Exported variables --------------------------------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------------------------------------*/
void LIN_Init(u8 *pRxBuffer, LIN_PIDHandler_CallBack_TypeDef pUserPIDHandlerCallBack);
void LIN_ResetState(void);

ErrStatus LIN_StartFrame(u8 uPID); // For Master Only
void LIN_SendResponse(u8 uPID, u8 *pBuffer, u8 uLength, u8 uCheckSumMode);
void LIN_SetTxRxAttributes(u8 uNextState, u8 *pBuffer, u8 uExpectRxLength, u8 uCheckSumMode);

bool LIN_IsPIDReady(void);
u8 LIN_GetPID(void);
s32 LIN_GetStatus(LIN_RxInfoTypeDef *pRxInfo);

void LIN_BreakHandler(void);
void LIN_RxHandler(u8 uData);
ErrStatus LIN_TxHandler(void);
ErrStatus LIN_TxFinishHandler(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __LIN_H ------------------------------------------------------------------------------------------*/
