/*********************************************************************************************************//**
 * @file    USART/PDMA/main.c
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

/** @addtogroup USART_PDMA
  * @{
  */

/* Private macro -------------------------------------------------------------------------------------------*/
#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
#define GET_MS()  (u32)TIME_TICK2MS(Time_GetTick())
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define RX_BUFFER_SIZE                            (64)
#define RX_FULL_CHECK                             (0) // Use PDMA Block end interrupt to check the Rx full status

/* Private function prototypes -----------------------------------------------------------------------------*/
void PDMA_Configuration(void);
void UxART_Configuration(void);

u32 UxART_PDMA_Tx(uc8 *TxBuffer, u32 length);
u32 UxART_PDMA_RxReadByte(u8* pBuf);
u32 UxART_PDMA_RxReadBlock(u8* pBuf, u32 uLen);
u32 UxART_PDMA_RxGetLength(void);
u32 UxART_PDMA_RxIsFull(void);

void UxART_RxMainRoutine(void);
void LED_Toggle(void);

#ifdef HTCFG_HSI_AUTO_TRIM_BY_LSE
ErrStatus WaitLSEClockReady(u32 uTimeout_ms);
ErrStatus HSIAutoTrimConfig(CKCU_ATC_TypeDef CLKSRC, u32 uTimeout_ms);
#endif

/* Private macro -------------------------------------------------------------------------------------------*/
#define GetRxBufferReadIndex()                    gRxBufferReadIndex
#define GetRxBufferWriteIndex()                   (RX_BUFFER_SIZE - HTCFG_PDMA_CURRENT_TRANSFER_SIZE)
#define IsRxBufferEmpty()                         (GetRxBufferWriteIndex() == GetRxBufferReadIndex())
#define IsRxBufferFull()                          ((GetRxBufferWriteIndex() + 1) == RX_BUFFER_SIZE ? (0 == GetRxBufferReadIndex()) : ((GetRxBufferWriteIndex() + 1) == GetRxBufferReadIndex()))

/* Global variables ----------------------------------------------------------------------------------------*/
PDMACH_InitTypeDef gPDMACH_TxStructure;
PDMACH_InitTypeDef gPDMACH_RxStructure;

vu32 gIsUxART_PDMA_TxBusy = FALSE;

u8 gRxBuffer[RX_BUFFER_SIZE];

/* Private variables ---------------------------------------------------------------------------------------*/
u32 gRxBufferReadIndex = 0;
uc8 gHelloString[] = "Hello, this is USART Tx/Rx PDMA example. Please enter characters.....\r\n";

u8 gTempBuffer[64];

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

  PDMA_Configuration();
  UxART_Configuration();

  /* Send hello information by PDMA mode                                                                    */
  UxART_PDMA_Tx(gHelloString, sizeof(gHelloString) - 1);

  while (1)
  {
    UxART_RxMainRoutine();
    LED_Toggle();
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the PDMA.
  * @retval None
  ***********************************************************************************************************/
void PDMA_Configuration(void)
{
  /* Enable peripheral clock of PDMA                                                                        */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.PDMA   = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Tx PDMA channel configuration                                                                          */
  gPDMACH_TxStructure.PDMACH_SrcAddr = (u32)NULL;
  gPDMACH_TxStructure.PDMACH_DstAddr = (u32)&HTCFG_UART_PORT->DR;
  gPDMACH_TxStructure.PDMACH_BlkCnt = 0;
  gPDMACH_TxStructure.PDMACH_BlkLen = 1;
  gPDMACH_TxStructure.PDMACH_DataSize = WIDTH_8BIT;
  gPDMACH_TxStructure.PDMACH_Priority = M_PRIO;
  gPDMACH_TxStructure.PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
  #if 0 // Config and Enable DMA when Start Tx
  PDMA_Config(HTCFG_TX_PDMA_CH, &gPDMACH_TxStructure);
  PDMA_EnaCmd(HTCFG_TX_PDMA_CH, ENABLE);
  #endif
  PDMA_IntConfig(HTCFG_TX_PDMA_CH, PDMA_INT_GE | PDMA_INT_TC, ENABLE);

  /* Rx PDMA channel configuration                                                                          */
  gPDMACH_RxStructure.PDMACH_SrcAddr = (u32)&HTCFG_UART_PORT->DR;
  gPDMACH_RxStructure.PDMACH_DstAddr = (u32)gRxBuffer;
  gPDMACH_RxStructure.PDMACH_BlkCnt = RX_BUFFER_SIZE;
  gPDMACH_RxStructure.PDMACH_BlkLen = 1;
  gPDMACH_RxStructure.PDMACH_DataSize = WIDTH_8BIT;
  gPDMACH_RxStructure.PDMACH_Priority = H_PRIO;
  gPDMACH_RxStructure.PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC | AUTO_RELOAD;
  PDMA_Config(HTCFG_RX_PDMA_CH, &gPDMACH_RxStructure);
  PDMA_EnaCmd(HTCFG_RX_PDMA_CH, ENABLE);
  #if 0 // Auto Reload by PDMA
  PDMA_IntConfig(HTCFG_RX_PDMA_CH, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  #endif

  #if (RX_FULL_CHECK == 1)
  PDMA_IntConfig(HTCFG_RX_PDMA_CH, PDMA_INT_GE | PDMA_INT_BE, ENABLE);
  #endif

  NVIC_EnableIRQ(HTCFG_PDMA_IRQ);
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
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
    USART_Init(HTCFG_UART_PORT, &USART_InitStructure);
  }

  #if 0 // Enable UxART TX DMA when Start Tx
  /* Enable UxART TX trigger DMA                                                                            */
  USART_PDMACmd(HTCFG_UART_PORT, USART_PDMAREQ_TX, ENABLE);
  #endif

  /* Enable UxART RX trigger DMA                                                                            */
  USART_PDMACmd(HTCFG_UART_PORT, USART_PDMAREQ_RX, ENABLE);

  /* Enable UxART Tx and Rx function                                                                        */
  USART_TxCmd(HTCFG_UART_PORT, ENABLE);
  USART_RxCmd(HTCFG_UART_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  UxART send a buffer by PDMA.
  * @retval None
  ***********************************************************************************************************/
u32 UxART_PDMA_Tx(uc8 *TxBuffer, u32 length)
{
  /* Wait until previou Tx finished                                                                         */
  while (gIsUxART_PDMA_TxBusy == TRUE);

  /* UxART Tx PDMA channel configuration                                                                    */
  gPDMACH_TxStructure.PDMACH_SrcAddr = (u32)TxBuffer;
  gPDMACH_TxStructure.PDMACH_BlkCnt = length;
  PDMA_Config(HTCFG_TX_PDMA_CH, &gPDMACH_TxStructure);
  PDMA_EnaCmd(HTCFG_TX_PDMA_CH, ENABLE);

  gIsUxART_PDMA_TxBusy = TRUE;
  USART_PDMACmd(HTCFG_UART_PORT, USART_PDMAREQ_TX, ENABLE);

  return length;
}

/*********************************************************************************************************//**
  * @brief  Read byte from Rx buffer.
  * @retval 0: No Data, 1 Read Success
  ***********************************************************************************************************/
u32 UxART_PDMA_RxReadByte(u8 *pBuf)
{
  if (IsRxBufferEmpty())
  {
    return 0;
  }
  else
  {
    *pBuf = gRxBuffer[gRxBufferReadIndex++];
    if (gRxBufferReadIndex == RX_BUFFER_SIZE)
    {
      gRxBufferReadIndex = 0;
    }
    return 1;
  }
}

/*********************************************************************************************************//**
  * @brief  Read block from Rx buffer.
  * @retval Data length
  ***********************************************************************************************************/
u32 UxART_PDMA_RxReadBlock(u8 *pBuf, u32 uLen)
{
  u32 i = 0;
  for (i = 0; i < uLen; i++)
  {
    if (IsRxBufferEmpty())
    {
      break;
    }
    *pBuf++ = gRxBuffer[gRxBufferReadIndex++];
    if (gRxBufferReadIndex == RX_BUFFER_SIZE)
    {
      gRxBufferReadIndex = 0;
    }
  }
  return i;
}

/*********************************************************************************************************//**
  * @brief  Get Rx data length.
  * @retval Data length
  ***********************************************************************************************************/
u32 UxART_PDMA_RxGetLength(void)
{
  u32 uWrite = GetRxBufferWriteIndex();
  u32 uRead = GetRxBufferReadIndex();

  if (uWrite >= uRead)
  {
    return (uWrite - uRead);
  }
  else
  {
    return (RX_BUFFER_SIZE - uRead + uWrite);
  }
}

/*********************************************************************************************************//**
  * @brief  Check Rx is full or not.
  * @retval 0: Rx is not full, 1: Rx is full
  ***********************************************************************************************************/
u32 UxART_PDMA_RxIsFull(void)
{
  return (IsRxBufferFull());
}

/*********************************************************************************************************//**
  * @brief  UxART Rx Main Routine.
  * @retval None
  ***********************************************************************************************************/
void UxART_RxMainRoutine(void)
{
  #if 1
  if (UxART_PDMA_RxReadByte(gTempBuffer)) // Process data after 1 byte received
  {
    // Do data process here

    #if 1 // Loopback Rx data to Tx
    UxART_PDMA_Tx((uc8 *)&gTempBuffer, 1);
    #endif
  }
  #else
  if (UxART_PDMA_RxGetLength() >= 5)      // Process data after 5 byte received
  {
    u32 uLen;
    uLen = UxART_PDMA_RxReadBlock(gTempBuffer, UxART_PDMA_RxGetLength());
    // Do data process here

    #if 1 // Loopback Rx data to Tx
    UxART_PDMA_Tx((uc8 *)gTempBuffer, uLen);
    #endif
  }
  #endif
}

/*********************************************************************************************************//**
  * @brief  LED Toggle function.
  * @retval None
  ***********************************************************************************************************/
void LED_Toggle(void)
{
  static u32 j = 0; // Global variable to control LED timing

  j++;

  if (j == 1000000)
  {
    j = 0;
    HT32F_DVB_LEDToggle(HT_LED1);
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
