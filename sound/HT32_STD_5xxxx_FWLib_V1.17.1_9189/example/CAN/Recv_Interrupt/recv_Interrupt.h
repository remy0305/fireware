/*********************************************************************************************************//**
 * @file    CAN/Recv_Interrupt/recv_Interrupt.h
 * @version $Rev:: 8177         $
 * @date    $Date:: 2024-09-24 #$
 * @brief   The header file of Recv_Interrupt example.
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
#ifndef __RECV_INTERRUPT_H
#define __RECV_INTERRUPT_H

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define CAN_RECV1_FIFO_SIZE     (1)
#define CAN_RECV2_FIFO_SIZE     (1)
#define CAN_RECV3_FIFO_SIZE     (20)

#define CAN_RECV1_BUFFER_SIZE   (CAN_RECV1_FIFO_SIZE * 8)
#define CAN_RECV2_BUFFER_SIZE   (CAN_RECV2_FIFO_SIZE * 8)
#define CAN_RECV3_BUFFER_SIZE   (CAN_RECV3_FIFO_SIZE * 8)

/* Exported variables --------------------------------------------------------------------------------------*/
extern CAN_MSG_TypeDef gRx1Msg;
extern CAN_MSG_TypeDef gRx2Msg;
extern CAN_MSG_TypeDef gRx3Msg;

extern u8 gRx1MsgBuffer[CAN_RECV1_BUFFER_SIZE];
extern u8 gRx2MsgBuffer[CAN_RECV2_BUFFER_SIZE];
extern u8 gRx3MsgBuffer[CAN_RECV3_BUFFER_SIZE];

extern u32 gRx1MsgBufferIndex;
extern u32 gRx2MsgBufferIndex;
extern u32 gRx3MsgBufferIndex;

#ifdef __cplusplus
}
#endif

#endif
