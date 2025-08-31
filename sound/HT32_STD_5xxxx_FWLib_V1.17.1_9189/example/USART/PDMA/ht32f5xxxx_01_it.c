/*********************************************************************************************************//**
 * @file    USART/PDMA/ht32f5xxxx_01_it.c
 * @version $Rev:: 4873         $
 * @date    $Date:: 2015-09-16 #
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
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup USART_PDMA
  * @{
  */


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
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
void SysTick_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CHn interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_PDMA_IRQHandler(void)
{
  extern u32 UxART_PDMA_RxIsFull(void);
  extern vu32 gIsUxART_PDMA_TxBusy;

  #if 0 // Auto Reload by PDMA
  extern PDMACH_InitTypeDef gPDMACH_RxStructure;
  extern u8 gRxBuffer[];
  if (PDMA_GetFlagStatus(HTCFG_RX_PDMA_CH, PDMA_FLAG_TC))
  {
    /* Clear interrupt flags                                                                                */
    PDMA_ClearFlag(HTCFG_RX_PDMA_CH, PDMA_FLAG_TC);

    /* Reload Rx PDMA                                                                                       */
    gPDMACH_RxStructure.PDMACH_DstAddr = (u32)gRxBuffer;
    PDMA_Config(HTCFG_RX_PDMA_CH, &PDMACH_RxStructure);

    /* Enable Rx PDMA                                                                                       */
    PDMA_EnaCmd(HTCFG_RX_PDMA_CH, ENABLE);
  }
  #endif

  #if 1 // Check Rx Full by PDMA Block end interrupt
  if (PDMA_GetFlagStatus(HTCFG_RX_PDMA_CH, PDMA_FLAG_BE))
  {
    /* Clear interrupt flags                                                                                */
    PDMA_ClearFlag(HTCFG_RX_PDMA_CH, PDMA_FLAG_BE);

    if (UxART_PDMA_RxIsFull())
    {
      printf("\r\n\r\nRx Buffer Full\r\n\r\n");
      while (1); // Reach here means Rx Buffer Full
    }
  }
  #endif

  if (PDMA_GetFlagStatus(HTCFG_TX_PDMA_CH, PDMA_FLAG_TC))
  {
    /* Clear interrupt flags                                                                                */
    PDMA_ClearFlag(HTCFG_TX_PDMA_CH, PDMA_FLAG_TC);

    gIsUxART_PDMA_TxBusy = FALSE;
    USART_PDMACmd(HTCFG_UART_PORT, USART_PDMAREQ_TX, DISABLE);
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
