/*********************************************************************************************************//**
 * @file    CAN/Recv_Interrupt/ht32f5xxxx_01_it.c
 * @version $Rev:: 8488         $
 * @date    $Date:: 2025-03-17 #$
 * @brief   This file provides all interrupt service routine.
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "recv_Interrupt.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup CAN_Examples CAN
  * @{
  */

/** @addtogroup Recv_Interrupt
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define CAN_RECV_BUFFER_SIZE            256

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  #if 1

  static vu32 gIsContinue = 0;
  /*--------------------------------------------------------------------------------------------------------*/
  /* For development FW, MCU run into the while loop when the hardfault occurred.                           */
  /* 1. Stack Checking                                                                                      */
  /*    When a hard fault exception occurs, MCU push following register into the stack (main or process     */
  /*    stack). Confirm R13(SP) value in the Register Window and typing it to the Memory Windows, you can   */
  /*    check following register, especially the PC value (indicate the last instruction before hard fault).*/
  /*    SP + 0x00    0x04    0x08    0x0C    0x10    0x14    0x18    0x1C                                   */
  /*           R0      R1      R2      R3     R12      LR      PC    xPSR                                   */
  while (gIsContinue == 0)
  {
  }
  /* 2. Step Out to Find the Clue                                                                           */
  /*    Change the variable "gIsContinue" to any other value than zero in a Local or Watch Window, then     */
  /*    step out the HardFault_Handler to reach the first instruction after the instruction which caused    */
  /*    the hard fault.                                                                                     */
  /*--------------------------------------------------------------------------------------------------------*/

  #else

  /*--------------------------------------------------------------------------------------------------------*/
  /* For production FW, you shall consider to reboot the system when hardfault occurred.                    */
  /*--------------------------------------------------------------------------------------------------------*/
  NVIC_SystemReset();

  #endif
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles CAN0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void CAN0_IRQHandler(void)
{
  extern void CAN_MainRoutine(void);
  u8 rxBuffer[CAN_RECV_BUFFER_SIZE];

  CAN_MainRoutine();

  /* Clear all message objects' interrupt pending flag                                                      */
  CAN_ClearAllMsgPendingFlag(HTCFG_CAN_PORT);

  if (CAN_GetFlagStatus(HTCFG_CAN_PORT, CAN_FLAG_RXOK))
  {
    u32 i;
   /* Receiving message process                                                                             */
    u32 dataLength;
    CAN_RxStatus_TypeDef rx_status;

    /* Receive gRx1Msg Message                                                                              */
    rx_status = CAN_Receive(HTCFG_CAN_PORT, &gRx1Msg, rxBuffer, &dataLength);
    if (rx_status == MSG_OVER_RUN)
    {
      printf("ID[%X] rx message over run\r\n", gRx1Msg.Id);
    }
    else if (rx_status == MSG_OBJ_NOT_SET)
    {
      printf("gRx1Msg message not set  \r\n");
    }
    else if (rx_status == MSG_RX_FINISH)
    {
      for (i = 0; i < dataLength; i++)
      {
        if (gRx1MsgBufferIndex >= CAN_RECV1_BUFFER_SIZE)
        {
          printf("gRx1Msg message overrun\r\n");
          break;
        }
        gRx1MsgBuffer[gRx1MsgBufferIndex++] = rxBuffer[i];
      }
    }

    /* Receive gRx2Msg Message                                                                              */
    rx_status = CAN_Receive(HTCFG_CAN_PORT, &gRx2Msg, rxBuffer, &dataLength);
    if (rx_status  == MSG_OVER_RUN)
    {
      printf("ID[%X] rx message over run\r\n", gRx2Msg.Id);
    }
    else if (rx_status == MSG_OBJ_NOT_SET)
    {
      printf("rx message not set  \r\n");
    }
    else if (rx_status == MSG_RX_FINISH)
    {
      for (i = 0; i < dataLength; i++)
      {
        if (gRx2MsgBufferIndex >= CAN_RECV2_BUFFER_SIZE)
        {
          printf("gRx2Msg message overrun\r\n");
          break;
        }
        gRx2MsgBuffer[gRx2MsgBufferIndex++] = rxBuffer[i];
      }
    }

    /* Receive gRx3Msg Message                                                                              */
    rx_status = CAN_Receive(HTCFG_CAN_PORT, &gRx3Msg, rxBuffer, &dataLength);
    if (rx_status  == MSG_OVER_RUN)
    {
      printf("ID[%X] rx message over run\r\n", gRx3Msg.Id);
    }
    else if (rx_status == MSG_OBJ_NOT_SET)
    {
      printf("rx message not set  \r\n");
    }
    else if (rx_status == MSG_RX_FINISH)
    {
      for (i = 0; i < dataLength; i++)
      {
        if (gRx3MsgBufferIndex >= CAN_RECV3_BUFFER_SIZE)
        {
          printf("gRx3Msg message overrun\r\n");
          break;
        }
        gRx3MsgBuffer[gRx3MsgBufferIndex++] = rxBuffer[i];
      }
    }
    CAN_ClearFlag(HTCFG_CAN_PORT, CAN_FLAG_RXOK); /* Clear RXOK Flag                                        */
  }

  if (CAN_GetFlagStatus(HTCFG_CAN_PORT, CAN_FLAG_TXOK))
  {
   /* Transmit message finished                                                                             */
    CAN_ClearFlag(HTCFG_CAN_PORT, CAN_FLAG_TXOK); /* Clear TXOK flag                                        */
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
