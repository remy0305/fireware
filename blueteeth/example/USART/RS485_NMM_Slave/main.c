/*********************************************************************************************************//**
 * @file    USART/RS485_NMM_Slave/main.c
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

#include "rs485.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup RS485_NMM_Slave
  * @{
  */

#define ENABLE_ADDRESS_RESPONSE                   (1)
#define ENABLE_HELLO_STR                          (1)
#define ENABLE_TX_ADDRESS                         (1)

/* Private macro -------------------------------------------------------------------------------------------*/
#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
#define GET_MS()  (u32)TIME_TICK2MS(Time_GetTick())
#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
void UxART_Configuration(void);
void UxART_RS485MainRoutine(void);
void UxART_SendAddress(u8 uAddress);
void UxARD_SendData(u8 *pBuffer, u32 uLength);

u32 UxART_RxTest(void);
void UxART_TxTest(void);

#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
ErrStatus WaitLSEClockReady(u32 uTimeout_ms);
ErrStatus HSIAutoTrimConfig(CKCU_ATC_TypeDef CLKSRC, u32 uTimeout_ms);
#endif

/* Global variables ----------------------------------------------------------------------------------------*/
vu32 guSlaveState = RS485_STATE_IDLE;

uc8  *gURTx_Ptr;
vu32 gURTx_Length = 0;
u8  *gURRx_Ptr;
vu32 gURRx_Length = 0;

vu32 gIsTxFinished = FALSE;

/* Private variables ---------------------------------------------------------------------------------------*/
uc8 gHelloString[] = "RS485 Slave is addressed! Please change to Parity Space and enter 5 characters...\r\n";
u8 gTx_Buffer[128];
u8 gRx_Buffer[128];

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
  HT32F_DVB_LEDInit(HT_LED2);

  gURRx_Ptr = gRx_Buffer;

  UxART_Configuration();

  while (1)
  {
    UxART_RS485MainRoutine();
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
  AFIO_GPxConfig(HTCFG_UART_RTS_GPIO_ID, HTCFG_UART_RTS_AFIO_PIN, AFIO_FUN_USART_UART); // RS485 TXE

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
    USART_InitStructure.USART_Parity = USART_PARITY_MARK;
    USART_InitStructure.USART_Mode = USART_MODE_RS485;
    USART_Init(HTCFG_UART_PORT, &USART_InitStructure);
  }

  /* RS485 NMM mode, TXE active high, with default Parity Mark                                              */
  USART_RS485NMMCmd(HTCFG_UART_PORT, ENABLE);
  USART_RS485TxEnablePolarityConfig(HTCFG_UART_PORT, USART_RS485POLARITY_HIGH);
  USART_StickParityCmd(HTCFG_UART_PORT, ENABLE);
  USART_StickParityConfig(HTCFG_UART_PORT, USART_STICK_HIGH); // Set Parity high as address packet

  /* Set 0 ~ 255 guard time between latest Tx bit and TXE(RTS) inactive                                     */
  USART_SetGuardTime(HTCFG_UART_PORT, 4);

  /* Enable UxART interrupt of NVIC                                                                         */
  NVIC_EnableIRQ(HTCFG_UART_IRQn);

  /* Enable UxART Rx interrupt                                                                              */
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_RXDR | USART_INT_RSADD, ENABLE);

  /* Enable UxART Tx function                                                                               */
  USART_TxCmd(HTCFG_UART_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  UxART Tx Test.
  * @retval None
  ***********************************************************************************************************/
void UxART_RS485MainRoutine(void)
{
  switch (guSlaveState)
  {
    case RS485_STATE_ADDRESSED:
    {
      #if (ENABLE_ADDRESS_RESPONSE == 1)
      UxART_SendAddress(HTCFG_RS485_MASTER_ADDR);
      #endif
      guSlaveState = RS485_STATE_ADDR_RESPONSE;
      break;
    }
    case RS485_STATE_ADDR_RESPONSE:
    {
      if (gIsTxFinished == TRUE)
      {
        #if (ENABLE_HELLO_STR == 1)
        UxARD_SendData((u8 *)gHelloString, sizeof(gHelloString) - 1);
        #endif
        guSlaveState = RS485_STATE_RX;
      }
      break;
    }
    case RS485_STATE_RX:
    {
      if (UxART_RxTest() != 0)
      {
        #if (ENABLE_TX_ADDRESS)
        UxART_SendAddress(HTCFG_RS485_MASTER_ADDR);
        #endif
        guSlaveState = RS485_STATE_TX_ADDR;
      }
      break;
    }
    case RS485_STATE_TX_ADDR:
    {
      if (gIsTxFinished == TRUE)
      {
        UxART_TxTest();
        guSlaveState = RS485_STATE_TX;
      }
    }
    case RS485_STATE_TX:
    {
      if (gIsTxFinished == TRUE)
      {
        gURRx_Length = 0;
        guSlaveState = RS485_STATE_RX;
      }
    }
    default:
    {
      break;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Send address packet.
  * @retval None
  ***********************************************************************************************************/
void UxART_SendAddress(u8 uAddress)
{
  /* !!! NOTICE !!!
     A delay may need here for RS485 TX/RX direction changing.
  */
  //...

  USART_StickParityConfig(HTCFG_UART_PORT, USART_STICK_HIGH); // Set Parity high as address packet

  gTx_Buffer[0] = HTCFG_RS485_MASTER_ADDR;

  gIsTxFinished = FALSE;
  gURTx_Ptr = gTx_Buffer;
  gURTx_Length = 1;
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_TXDE | USART_INT_TXC, ENABLE);

  #if 0 // Set 1 for blocking-mode
  while (gURTx_Length != 0);      // Latest byte move to UxART shift register, but the transmission may be on going.
  while (gIsTxFinished == FALSE); // Set by TXC interrupt, transmission is finished.
  #endif
}

/*********************************************************************************************************//**
  * @brief  Send UART data by interrupt mode.
  * @param  pBuffer: buffer for sned
  * @param  uLength: data length
  * @retval None
  ***********************************************************************************************************/
void UxARD_SendData(u8 *pBuffer, u32 uLength)
{
  /* !!! NOTICE !!!
     A delay may need here for RS485 TX/RX direction changing.
  */
  //...

  USART_StickParityConfig(HTCFG_UART_PORT, USART_STICK_LOW); // Set Parity low as data packet

  gIsTxFinished = FALSE;
  gURTx_Ptr = (u8 *)pBuffer;
  gURTx_Length = uLength;
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_TXDE | USART_INT_TXC, ENABLE);

  #if 0 // Set 1 for blocking-mode
  while (gURTx_Length != 0);      // Latest byte move to UxART shift register, but the transmission may be on going.
  while (gIsTxFinished == FALSE); // Set by TXC interrupt, transmission is finished.
  #endif
}

/*********************************************************************************************************//**
  * @brief  UxART Rx Test.
  * @retval None
  ***********************************************************************************************************/
u32 UxART_RxTest(void)
{
  u32 uResult = 0;

  /* Waiting for receive 5 data                                                                             */
  if (gURRx_Length >= 5)
  {
    // Process Rx data by gRx_Buffer[] and gURRx_Length here
    // .....

    uResult = 1;
  }

  return uResult;
}

/*********************************************************************************************************//**
  * @brief  UxART Tx Test..
  * @retval None
  ***********************************************************************************************************/
void UxART_TxTest(void)
{
  #if 1 // Loop back Rx data to Tx for test
  u32 i;
  for (i = 0; i < 5; i++)
  {
    gTx_Buffer[i] = gRx_Buffer[i];
  }

  UxARD_SendData(gTx_Buffer, 5);
  #endif
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
