/*********************************************************************************************************//**
 * @file    USART/Retarget/main.c
 * @version $Rev:: 7438         $
 * @date    $Date:: 2023-12-21 #$
 * @brief   Main program.
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup Retarget
  * @{
  */

/* Private macro -------------------------------------------------------------------------------------------*/
#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
#define GET_MS()  (u32)TIME_TICK2MS(Time_GetTick())
#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
ErrStatus WaitLSEClockReady(u32 uTimeout_ms);
ErrStatus HSIAutoTrimConfig(CKCU_ATC_TypeDef CLKSRC, u32 uTimeout_ms);
#endif

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  int input;

  #ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
  Time_Init();
  if (WaitLSEClockReady(2000) == ERROR)
  {
    #if 1
    // Wait for LSE clock Ready timeout, do the error handling here
    while(1);
    #endif
  }

  if (HSIAutoTrimConfig(CKCU_ATC_LSE, 2000) == ERROR)
  {
    #if 1
    // Wait for HSI Auto Trim Ready timeout, do the error handling here
    while(1);
    #endif
  }
  #endif

  { /* Enable peripheral clock of Rx GPIO                                                                   */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.HTCFG_UART_RX_GPIO_CLK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                     */
  GPIO_PullResistorConfig(HTCFG_UART_RX_GPIO_PORT, HTCFG_UART_RX_GPIO_PIN, GPIO_PR_UP);

  RETARGET_Configuration();

  /* Send "Hello World!" string 10 times                                                                    */
  for (input = 0; input < 10; input++)
  {
    printf("Hello World! %d\r\n", (int)input);
  }

  /* Get Rx character and and print out                                                                     */
  while (1)
  {
    printf("Please input key for printf....");
    input = getchar();
    printf("\r\nYour input is %c[0x%x]\r\n\r\n", input, input);
  }
}

#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
/*********************************************************************************************************//**
  * @brief  Wait LSE Clock Ready
  * @retval None
  ***********************************************************************************************************/
ErrStatus WaitLSEClockReady(u32 uTimeout_ms)
{
  u32 start=GET_MS();

  while (CKCU_GetClockReadyStatus(CKCU_FLAG_LSERDY) == RESET)
  {
    if (GET_MS() - start > uTimeout_ms)
    {
      return ERROR;
    }
  }

  return SUCCESS;
}

/*********************************************************************************************************//**
  * @brief  Auto Trim by LSE configuration.
  * @retval None
  ***********************************************************************************************************/
ErrStatus HSIAutoTrimConfig(CKCU_ATC_TypeDef CLKSRC, u32 uTimeout_ms)
{
  u32 start;
  CKCU_HSIAutoTrimClkConfig(CLKSRC);
  CKCU_HSIAutoTrimCmd(ENABLE);

  start=GET_MS();
  if (uTimeout_ms != 0)
  {
    while (CKCU_HSIAutoTrimIsReady() == FALSE)
    {
      if (GET_MS() - start > uTimeout_ms)
      {
         return ERROR;
      }
    }
  }

  return SUCCESS;
}
#endif

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
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
