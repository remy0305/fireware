/*********************************************************************************************************//**
 * @file    USART/Polling/main.c
 * @version $Rev:: 8175         $
 * @date    $Date:: 2024-09-23 #$
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

/** @addtogroup Polling
  * @{
  */

/* Private macro -------------------------------------------------------------------------------------------*/
#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
#define GET_MS()  (u32)TIME_TICK2MS(Time_GetTick())
#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
void UxART_Configuration(void);
void UxART_TxTest(void);
void UxART_RxTest_Block(void);
void UxART_RxTest_NonBlock(void);

void UxART_TxSend(u16 Data);

void LED_Demo(void);

#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
ErrStatus WaitLSEClockReady(u32 uTimeout_ms);
ErrStatus HSIAutoTrimConfig(CKCU_ATC_TypeDef CLKSRC, u32 uTimeout_ms);
#endif

/* Private variables ---------------------------------------------------------------------------------------*/
uc8 gHelloString[] = "Hello, this is USART Tx/Rx Polling example. Please enter characters.....\r\n";

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
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

  HT32F_DVB_LEDInit(HT_LED1);

  UxART_Configuration();

  UxART_TxTest();

  while (1)
  {
    #if 0 // Blocking mode
    {
      UxART_RxTest_Block();       // Wait until get UxART data
    }
    #else // Non-Blocking mode
    {
      UxART_RxTest_NonBlock();    // Return if no UxART data, LED can toggle by "LED_Demo()".
    }
    #endif

    LED_Demo();
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the UxART
  * @retval None
  ***********************************************************************************************************/
void UxART_Configuration(void)
{
  #if 0 // Use following function to configure the IP clock speed.
  // The UxART IP clock speed must be faster 16x then the baudrate.
  CKCU_SetPeripPrescaler(CKCU_PCLK_UxARTn, CKCU_APBCLKPRE_DIV2);
  #endif

  { /* Enable peripheral clock of AFIO, UxART                                                               */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.AFIO                   = 1;
    CKCUClock.Bit.HTCFG_UART_RX_GPIO_CLK = 1;
    CKCUClock.Bit.HTCFG_UART_IPN         = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                     */
  GPIO_PullResistorConfig(HTCFG_UART_RX_GPIO_PORT, HTCFG_UART_RX_GPIO_PIN, GPIO_PR_UP);

  /* Config AFIO mode as UxART function.                                                                    */
  AFIO_GPxConfig(HTCFG_UART_TX_GPIO_ID, HTCFG_UART_TX_AFIO_PIN, AFIO_FUN_USART_UART);
  AFIO_GPxConfig(HTCFG_UART_RX_GPIO_ID, HTCFG_UART_RX_AFIO_PIN, AFIO_FUN_USART_UART);

  {
    /* UxART configured as follow:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - None parity bit
    */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    USART_InitTypeDef USART_InitStructure = {0};
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
    USART_Init(HTCFG_UART_PORT, &USART_InitStructure);
  }

  /* Enable UxART Tx and Rx function                                                                        */
  USART_TxCmd(HTCFG_UART_PORT, ENABLE);
  USART_RxCmd(HTCFG_UART_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  UxART Tx Test.
  * @retval None
  ***********************************************************************************************************/
void UxART_TxTest(void)
{
  u32 i;
  u8 *uPtr = (u8 *)gHelloString;
  u32 uLen = sizeof(gHelloString) - 1;

  /* Send a buffer from UxART to terminal                                                                   */
  for (i = 0; i < uLen; i++)
  {
    UxART_TxSend(uPtr[i]);
  }
}

/*********************************************************************************************************//**
  * @brief  UxART Rx Test - Blocking mode.
  * @retval None
  ***********************************************************************************************************/
void UxART_RxTest_Block(void)
{
  u16 uData;

  /* Waits until the Rx FIFO/DR is not empty then get data from them                                        */
  while (USART_GetFlagStatus(HTCFG_UART_PORT, USART_FLAG_RXDR) == RESET);
  uData = USART_ReceiveData(HTCFG_UART_PORT);

  #if 1 // Loop back Rx data to Tx for test
  UxART_TxSend(uData);
  #endif
}

/*********************************************************************************************************//**
  * @brief  UxART Rx Test - Non-Blocking mode
  * @retval None
  ***********************************************************************************************************/
void UxART_RxTest_NonBlock(void)
{
  u16 uData;

  /* Waits until the Rx FIFO/DR is not empty then get data from them                                        */
  if (USART_GetFlagStatus(HTCFG_UART_PORT, USART_FLAG_RXDR) == SET)
  {
    uData = USART_ReceiveData(HTCFG_UART_PORT);

    #if 1 // Loop back Rx data to Tx for test
    UxART_TxSend(uData);
    #endif
  }
}

/*********************************************************************************************************//**
  * @brief  UxART Tx Send Byte.
  * @param  Data: the data to be transmitted.
  * @retval None
  ***********************************************************************************************************/
void UxART_TxSend(u16 Data)
{
  while (USART_GetFlagStatus(HTCFG_UART_PORT, USART_FLAG_TXC) == RESET);
  USART_SendData(HTCFG_UART_PORT, Data);
}

/*********************************************************************************************************//**
  * @brief  LED Demo.
  * @retval None
  ***********************************************************************************************************/
void LED_Demo(void)
{
  static u32 uDelay = 0;

  uDelay++;

  if (uDelay == 200000)
  {
    HT32F_DVB_LEDToggle(HT_LED1);
    uDelay = 0;
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
