/*********************************************************************************************************//**
 * @file    uart_module.c
 * @version $Rev:: 1476         $
 * @date    $Date:: 2025-03-03 #$
 * @brief   The UART Module (interrupt mode with buffer).
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
#include "uart_module.h"
#include "common/ring_buffer.h"

/* Private types -------------------------------------------------------------------------------------------*/
typedef struct
{
  HT_USART_TypeDef *pUARTx;
  u8 uFIFOMode;
  u8 uIsTxFinished;
} UARTModule_StateTypeDef;

/* Private constants ---------------------------------------------------------------------------------------*/
#ifdef HTCFG_UARTM_CH0
#define _TX0_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM0_TX_GPIO_PORT)
#define _TX0_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM0_TX_GPIO_PIN)
#define _RX0_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM0_RX_GPIO_PORT)
#define _RX0_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM0_RX_GPIO_PIN)
#define _RX0_GPIO_CLK             STRCAT2(P,         HTCFG_UARTM0_RX_GPIO_PORT)
#define _RX0_GPIO_PORT            STRCAT2(HT_GPIO,   HTCFG_UARTM0_RX_GPIO_PORT)
#define _RX0_GPIO_PIN             STRCAT2(GPIO_PIN_, HTCFG_UARTM0_RX_GPIO_PIN)
#define _UART_CH0                 STRCAT2(HT_,       HTCFG_UARTM_CH0)
#define _UART_INT0                STRCAT2(HTCFG_UARTM_CH0, _IRQn)
#undef  _UART_MODULE_SUPPORT_CNT
#define _UART_MODULE_SUPPORT_CNT  (1)
#endif

#ifdef HTCFG_UARTM_CH1
#define _TX1_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM1_TX_GPIO_PORT)
#define _TX1_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM1_TX_GPIO_PIN)
#define _RX1_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM1_RX_GPIO_PORT)
#define _RX1_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM1_RX_GPIO_PIN)
#define _RX1_GPIO_CLK             STRCAT2(P,         HTCFG_UARTM1_RX_GPIO_PORT)
#define _RX1_GPIO_PORT            STRCAT2(HT_GPIO,   HTCFG_UARTM1_RX_GPIO_PORT)
#define _RX1_GPIO_PIN             STRCAT2(GPIO_PIN_, HTCFG_UARTM1_RX_GPIO_PIN)
#define _UART_CH1                 STRCAT2(HT_,       HTCFG_UARTM_CH1)
#define _UART_INT1                STRCAT2(HTCFG_UARTM_CH1, _IRQn)
#undef  _UART_MODULE_SUPPORT_CNT
#define _UART_MODULE_SUPPORT_CNT  (2)
#endif

#ifdef HTCFG_UARTM_CH2
#define _TX2_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM2_TX_GPIO_PORT)
#define _TX2_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM2_TX_GPIO_PIN)
#define _RX2_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM2_RX_GPIO_PORT)
#define _RX2_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM2_RX_GPIO_PIN)
#define _RX2_GPIO_CLK             STRCAT2(P,         HTCFG_UARTM2_RX_GPIO_PORT)
#define _RX2_GPIO_PORT            STRCAT2(HT_GPIO,   HTCFG_UARTM2_RX_GPIO_PORT)
#define _RX2_GPIO_PIN             STRCAT2(GPIO_PIN_, HTCFG_UARTM2_RX_GPIO_PIN)
#define _UART_CH2                 STRCAT2(HT_,       HTCFG_UARTM_CH2)
#define _UART_INT2                STRCAT2(HTCFG_UARTM_CH2, _IRQn)
#undef  _UART_MODULE_SUPPORT_CNT
#define _UART_MODULE_SUPPORT_CNT  (3)
#endif

#ifdef HTCFG_UARTM_CH3
#define _TX3_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM3_TX_GPIO_PORT)
#define _TX3_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM3_TX_GPIO_PIN)
#define _RX3_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM3_RX_GPIO_PORT)
#define _RX3_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM3_RX_GPIO_PIN)
#define _RX3_GPIO_CLK             STRCAT2(P,         HTCFG_UARTM3_RX_GPIO_PORT)
#define _RX3_GPIO_PORT            STRCAT2(HT_GPIO,   HTCFG_UARTM3_RX_GPIO_PORT)
#define _RX3_GPIO_PIN             STRCAT2(GPIO_PIN_, HTCFG_UARTM3_RX_GPIO_PIN)
#define _UART_CH3                 STRCAT2(HT_,       HTCFG_UARTM_CH3)
#define _UART_INT3                STRCAT2(HTCFG_UARTM_CH3, _IRQn)
#undef  _UART_MODULE_SUPPORT_CNT
#define _UART_MODULE_SUPPORT_CNT  (4)
#endif

#ifdef HTCFG_UARTM_CH4
#define _TX4_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM4_TX_GPIO_PORT)
#define _TX4_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM4_TX_GPIO_PIN)
#define _RX4_GPIO_ID              STRCAT2(GPIO_P,    HTCFG_UARTM4_RX_GPIO_PORT)
#define _RX4_AFIO_PIN             STRCAT2(AFIO_PIN_, HTCFG_UARTM4_RX_GPIO_PIN)
#define _RX4_GPIO_CLK             STRCAT2(P,         HTCFG_UARTM4_RX_GPIO_PORT)
#define _RX4_GPIO_PORT            STRCAT2(HT_GPIO,   HTCFG_UARTM4_RX_GPIO_PORT)
#define _RX4_GPIO_PIN             STRCAT2(GPIO_PIN_, HTCFG_UARTM4_RX_GPIO_PIN)
#define _UART_CH4                 STRCAT2(HT_,       HTCFG_UARTM_CH4)
#define _UART_INT4                STRCAT2(HTCFG_UARTM_CH4, _IRQn)
#undef  _UART_MODULE_SUPPORT_CNT
#define _UART_MODULE_SUPPORT_CNT  (5)
#endif

#define UART_MODULE_SUPPORT_CH                (_UART_MODULE_SUPPORT_CNT)

/* Private function prototypes -----------------------------------------------------------------------------*/
static void _UARTM_IRQHandler(u32 CH);

/* Private macro -------------------------------------------------------------------------------------------*/
#define __DBG_Printf(...)

#if (UART_MODULE_DEBUG_MODE == 1)
  #undef __DBG_Printf
  #define __DBG_Printf printf
  #warning "================================ Debug Mode Warning ===================================="
  #warning " Debug mode has been enable which degrade the performance.                              "
  #warning " After all debug operation is finished, please remember to turn off debug mode.         "
  #warning "========================================================================================"
#endif

/* Global variables ----------------------------------------------------------------------------------------*/
Buffer_TypeDef gUART_Tx[UART_MODULE_SUPPORT_CH];
Buffer_TypeDef gUART_Rx[UART_MODULE_SUPPORT_CH];
__ALIGN4 u8 guUART_TxBuffer[UART_MODULE_SUPPORT_CH][HTCFG_UARTM0_TX_BUFFER_SIZE]; // To be modify to reduce RAM usage (support different size of each channel), now only HTCFG_UARTM0_TX_BUFFER_SIZE used
__ALIGN4 u8 guUART_RxBuffer[UART_MODULE_SUPPORT_CH][HTCFG_UARTM0_RX_BUFFER_SIZE]; // To be modify to reduce RAM usage (support different size of each channel), now only HTCFG_UARTM0_TX_BUFFER_SIZE used

#if FREERTOS_UART
SemaphoreHandle_t Semphr[UART_MODULE_SUPPORT_CH];
StaticSemaphore_t Semphr_Buffer[UART_MODULE_SUPPORT_CH];
SemaphoreHandle_t Mutex_TX[UART_MODULE_SUPPORT_CH];
SemaphoreHandle_t Mutex_RX[UART_MODULE_SUPPORT_CH];
StaticSemaphore_t Mutex_TX_Buffer[UART_MODULE_SUPPORT_CH];
StaticSemaphore_t Mutex_RX_Buffer[UART_MODULE_SUPPORT_CH];
u32 Transfer_Result[UART_MODULE_SUPPORT_CH];
#endif

/* Private variables ---------------------------------------------------------------------------------------*/
static UARTModule_StateTypeDef gUARTModuleState[UART_MODULE_SUPPORT_CH];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  UART Module init function.
  * @param  CH
  * @param  pUART_Init
  * @param  uRxTimeOutValue
  * @retval None
  ***********************************************************************************************************/
void UARTM_Init(u32 CH, USART_InitTypeDef *pUART_Init, u32 uRxTimeOutValue)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  #if (AUTO_CK_CONTROL == 0)
  CKCUClock.Bit.AFIO       = 1;
  #endif

  #ifdef HTCFG_UARTM_CH0
  if (CH == UARTM_CH0)
  {
    gUARTModuleState[CH].pUARTx = _UART_CH0;
    Buffer_Init(&gUART_Tx[CH], guUART_TxBuffer[CH], HTCFG_UARTM0_TX_BUFFER_SIZE);
    Buffer_Init(&gUART_Rx[CH], guUART_RxBuffer[CH], HTCFG_UARTM0_RX_BUFFER_SIZE);

    /* Enable UART & AFIO APB clock                                                                         */
    CKCUClock.Bit.HTCFG_UARTM_CH0 = 1;
    CKCUClock.Bit._RX0_GPIO_CLK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                   */
    GPIO_PullResistorConfig(_RX0_GPIO_PORT, _RX0_GPIO_PIN, GPIO_PR_UP);

    /* Configure AFIO as UART mode                                                                          */
    AFIO_GPxConfig(_TX0_GPIO_ID, _TX0_AFIO_PIN, AFIO_FUN_USART_UART);
    AFIO_GPxConfig(_RX0_GPIO_ID, _RX0_AFIO_PIN, AFIO_FUN_USART_UART);

    NVIC_EnableIRQ(_UART_INT0);

    #ifdef HT_USART0
    if ((_UART_CH0 == HT_USART0)
        #ifdef LIBCFG_USART1
        || (_UART_CH0 == HT_USART1)
        #endif
       )
    {
      USART_RXTLConfig(_UART_CH0, UART_MODULE_FIFO_LEVEL);
      USART_SetTimeOutValue(_UART_CH0, uRxTimeOutValue);
      USART_IntConfig(_UART_CH0, USART_INT_TOUT, ENABLE);
      gUARTModuleState[CH].uFIFOMode = 1;
    }
    #endif
  }
  #endif

  #ifdef HTCFG_UARTM_CH1
  if (CH == UARTM_CH1)
  {
    gUARTModuleState[CH].pUARTx = _UART_CH1;
    Buffer_Init(&gUART_Tx[CH], guUART_TxBuffer[CH], HTCFG_UARTM1_TX_BUFFER_SIZE);
    Buffer_Init(&gUART_Rx[CH], guUART_RxBuffer[CH], HTCFG_UARTM1_RX_BUFFER_SIZE);

    /* Enable UART & AFIO APB clock                                                                         */
    CKCUClock.Bit.HTCFG_UARTM_CH1 = 1;
    CKCUClock.Bit._RX1_GPIO_CLK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                   */
    GPIO_PullResistorConfig(_RX1_GPIO_PORT, _RX1_GPIO_PIN, GPIO_PR_UP);

    /* Configure AFIO as UART mode                                                                          */
    AFIO_GPxConfig(_TX1_GPIO_ID, _TX1_AFIO_PIN, AFIO_FUN_USART_UART);
    AFIO_GPxConfig(_RX1_GPIO_ID, _RX1_AFIO_PIN, AFIO_FUN_USART_UART);

    NVIC_EnableIRQ(_UART_INT1);

    #ifdef HT_USART0
    if ((_UART_CH1 == HT_USART0)
        #ifdef LIBCFG_USART1
        || (_UART_CH1 == HT_USART1)
        #endif
       )
    {
      USART_RXTLConfig(_UART_CH1, UART_MODULE_FIFO_LEVEL);
      USART_SetTimeOutValue(_UART_CH1, uRxTimeOutValue);
      USART_IntConfig(_UART_CH1, USART_INT_TOUT, ENABLE);
      gUARTModuleState[CH].uFIFOMode = 1;
    }
    #endif
  }
  #endif

  #ifdef HTCFG_UARTM_CH2
  if (CH == UARTM_CH2)
  {
    gUARTModuleState[CH].pUARTx = _UART_CH2;
    Buffer_Init(&gUART_Tx[CH], guUART_TxBuffer[CH], HTCFG_UARTM2_TX_BUFFER_SIZE);
    Buffer_Init(&gUART_Rx[CH], guUART_RxBuffer[CH], HTCFG_UARTM2_RX_BUFFER_SIZE);

    /* Enable UART & AFIO APB clock                                                                         */
    CKCUClock.Bit.HTCFG_UARTM_CH2 = 1;
    CKCUClock.Bit._RX2_GPIO_CLK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                   */
    GPIO_PullResistorConfig(_RX2_GPIO_PORT, _RX2_GPIO_PIN, GPIO_PR_UP);

    /* Configure AFIO as UART mode                                                                          */
    AFIO_GPxConfig(_TX2_GPIO_ID, _TX2_AFIO_PIN, AFIO_FUN_USART_UART);
    AFIO_GPxConfig(_RX2_GPIO_ID, _RX2_AFIO_PIN, AFIO_FUN_USART_UART);

    NVIC_EnableIRQ(_UART_INT2);

    #ifdef HT_USART0
    if ((_UART_CH2 == HT_USART0)
        #ifdef LIBCFG_USART1
        || (_UART_CH2 == HT_USART1)
        #endif
       )
    {
      USART_RXTLConfig(_UART_CH2, UART_MODULE_FIFO_LEVEL);
      USART_SetTimeOutValue(_UART_CH2, uRxTimeOutValue);
      USART_IntConfig(_UART_CH2, USART_INT_TOUT, ENABLE);
      gUARTModuleState[CH].uFIFOMode = 1;
    }
    #endif
  }
  #endif

  #ifdef HTCFG_UARTM_CH3
  if (CH == UARTM_CH3)
  {
    gUARTModuleState[CH].pUARTx = _UART_CH3;
    Buffer_Init(&gUART_Tx[CH], guUART_TxBuffer[CH], HTCFG_UARTM3_TX_BUFFER_SIZE);
    Buffer_Init(&gUART_Rx[CH], guUART_RxBuffer[CH], HTCFG_UARTM3_RX_BUFFER_SIZE);

    /* Enable UART & AFIO APB clock                                                                         */
    CKCUClock.Bit.HTCFG_UARTM_CH3 = 1;
    CKCUClock.Bit._RX3_GPIO_CLK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                   */
    GPIO_PullResistorConfig(_RX3_GPIO_PORT, _RX3_GPIO_PIN, GPIO_PR_UP);

    /* Configure AFIO as UART mode                                                                          */
    AFIO_GPxConfig(_TX3_GPIO_ID, _TX3_AFIO_PIN, AFIO_FUN_USART_UART);
    AFIO_GPxConfig(_RX3_GPIO_ID, _RX3_AFIO_PIN, AFIO_FUN_USART_UART);

    NVIC_EnableIRQ(_UART_INT3);

    #ifdef HT_USART0
    if ((_UART_CH3 == HT_USART0)
        #ifdef LIBCFG_USART1
        || (_UART_CH3 == HT_USART1)
        #endif
       )
    {
      USART_RXTLConfig(_UART_CH3, UART_MODULE_FIFO_LEVEL);
      USART_SetTimeOutValue(_UART_CH3, uRxTimeOutValue);
      USART_IntConfig(_UART_CH3, USART_INT_TOUT, ENABLE);
      gUARTModuleState[CH].uFIFOMode = 1;
    }
    #endif
  }
  #endif

  #ifdef HTCFG_UARTM_CH4
  if (CH == UARTM_CH4)
  {
    gUARTModuleState[CH].pUARTx = _UART_CH4;
    Buffer_Init(&gUART_Tx[CH], guUART_TxBuffer[CH], HTCFG_UARTM4_TX_BUFFER_SIZE);
    Buffer_Init(&gUART_Rx[CH], guUART_RxBuffer[CH], HTCFG_UARTM4_RX_BUFFER_SIZE);

    /* Enable UART & AFIO APB clock                                                                         */
    CKCUClock.Bit.HTCFG_UARTM_CH4 = 1;
    CKCUClock.Bit._RX4_GPIO_CLK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                   */
    GPIO_PullResistorConfig(_RX4_GPIO_PORT, _RX4_GPIO_PIN, GPIO_PR_UP);

    /* Configure AFIO as UART mode                                                                          */
    AFIO_GPxConfig(_TX4_GPIO_ID, _TX4_AFIO_PIN, AFIO_FUN_USART_UART);
    AFIO_GPxConfig(_RX4_GPIO_ID, _RX4_AFIO_PIN, AFIO_FUN_USART_UART);

    NVIC_EnableIRQ(_UART_INT4);

    #ifdef HT_USART0
    if ((_UART_CH4 == HT_USART0)
        #ifdef LIBCFG_USART1
        || (_UART_CH4 == HT_USART1)
        #endif
       )
    {
      USART_RXTLConfig(_UART_CH4, UART_MODULE_FIFO_LEVEL);
      USART_SetTimeOutValue(_UART_CH4, uRxTimeOutValue);
      USART_IntConfig(_UART_CH4, USART_INT_TOUT, ENABLE);
      gUARTModuleState[CH].uFIFOMode = 1;
    }
    #endif
  }
  #endif

  USART_Init(gUARTModuleState[CH].pUARTx, pUART_Init);
  USART_TxCmd(gUARTModuleState[CH].pUARTx, ENABLE);
  USART_RxCmd(gUARTModuleState[CH].pUARTx, ENABLE);
  #if defined(USART_INT_OE)
  USART_IntConfig(gUARTModuleState[CH].pUARTx, USART_INT_RXDR | USART_INT_OE, ENABLE);
  #else
  USART_IntConfig(gUARTModuleState[CH].pUARTx, USART_INT_RXDR, ENABLE);
  #endif
}

/*********************************************************************************************************//**
  * @brief  UART module write byte (Tx).
  * @param  CH
  * @param  uData
  * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
u32 UARTM_WriteByte(u32 CH, u8 uData)
{
  u32 uResult;
  uResult = Buffer_WriteByte(&gUART_Tx[CH], uData);
  if (uResult == TRUE)
  {
    gUARTModuleState[CH].uIsTxFinished = FALSE;
    #if (LIBCFG_USART_V01)
    USART_IntConfig(gUARTModuleState[CH].pUARTx, USART_INT_TXDE, ENABLE);
    #else
    USART_IntConfig(gUARTModuleState[CH].pUARTx, USART_INT_TXDE | USART_INT_TXC, ENABLE);
    #endif
  }

  return uResult;
}

/*********************************************************************************************************//**
  * @brief  UART module write (Tx).
  * @param  CH
  * @param  pBuffer
  * @param  uLength
  * @retval success write count
  ***********************************************************************************************************/
u32 UARTM_Write(u32 CH, u8 *pBuffer, u32 uLength)
{
  u32 uResult;
  u32 uFreeSpace = gUART_Tx[CH].uSize - 1 - Buffer_GetLength(&gUART_Tx[CH]);
  if (uLength > uFreeSpace)
  {
    return 0;
  }
  uResult = Buffer_Write(&gUART_Tx[CH], pBuffer, uLength);
  if (uResult > 0)
  {
    gUARTModuleState[CH].uIsTxFinished = FALSE;
    #if (LIBCFG_USART_V01)
    USART_IntConfig(gUARTModuleState[CH].pUARTx, USART_INT_TXDE, ENABLE);
    #else
    USART_IntConfig(gUARTModuleState[CH].pUARTx, USART_INT_TXDE | USART_INT_TXC, ENABLE);
    #endif
  }

  return uResult;
}

/*********************************************************************************************************//**
  * @brief  UART module read byte (Rx).
  * @param  CH
  * @param  pData
  * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
u32 UARTM_ReadByte(u32 CH, u8 *pData)
{
  return (Buffer_ReadByte(&gUART_Rx[CH], pData));
}

/*********************************************************************************************************//**
  * @brief  UART module read (Rx).
  * @param  CH
  * @param  pBuffer
  * @param  uLength
  * @retval Read count
  ***********************************************************************************************************/
u32 UARTM_Read(u32 CH, u8 *pBuffer, u32 uLength)
{
  return (Buffer_Read(&gUART_Rx[CH], pBuffer, uLength));
}

/*********************************************************************************************************//**
  * @brief  Get Read buffer length (Rx).
  * @param  CH
  * @retval uLength
  ***********************************************************************************************************/
u32 UARTM_GetReadBufferLength(u32 CH)
{
  return (Buffer_GetLength(&gUART_Rx[CH]));
}

/*********************************************************************************************************//**
  * @brief  Get Write buffer length (Tx).
  * @param  CH
  * @retval uLength
  ***********************************************************************************************************/
u32 UARTM_GetWriteBufferLength(u32 CH)
{
  return (Buffer_GetLength(&gUART_Tx[CH]));
}

/*********************************************************************************************************//**
  * @brief  Get Tx Status.
  * @param  CH
  * @retval TRUE for TX is Finished, FALSE for TX is not Finished
  ***********************************************************************************************************/
u8 UARTM_IsTxFinished(u32 CH)
{
  return (gUARTModuleState[CH].uIsTxFinished);
}

/*********************************************************************************************************//**
  * @brief  Discard Read buffer.
  * @param  CH
  * @retval None
  ***********************************************************************************************************/
void UARTM_DiscardReadBuffer(u32 CH)
{
  Buffer_Discard(&gUART_Rx[CH]);
}

#if defined(UART0_IRQ_HANDLER) || defined(UART1_IRQ_HANDLER) || defined(UART2_IRQ_HANDLER) || defined(UART3_IRQ_HANDLER) || defined(UART4_IRQ_HANDLER) || defined(USART0_IRQ_HANDLER) || defined(USART1_IRQ_HANDLER) || defined(USART2_IRQ_HANDLER)
#if defined(HT_USART0) && defined(USART0_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void USART0_IRQHandler(void)
{
  USART0_IRQ_HANDLER();
}
#endif
#if defined(HT_USART1) && defined(USART1_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void USART1_IRQHandler(void)
{
  USART1_IRQ_HANDLER();
}
#endif
#if defined(HT_USART2) && defined(USART2_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void USART2_IRQHandler(void)
{
  USART2_IRQ_HANDLER();
}
#endif
#if defined(USE_HT32F52357_67)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UART0_UART2_IRQHandler(void)
{
  #if defined(HT_UART0) && defined(UART0_IRQ_HANDLER)
  UART0_IRQ_HANDLER();
  #endif
  #if defined(HT_UART2) && defined(UART2_IRQ_HANDLER)
  UART2_IRQ_HANDLER();
  #endif
}
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UART1_UART3_IRQHandler(void)
{
  #if defined(HT_UART1) && defined(UART1_IRQ_HANDLER)
  UART1_IRQ_HANDLER();
  #endif
  #if defined(HT_UART3) && defined(UART3_IRQ_HANDLER)
  UART3_IRQ_HANDLER();
  #endif
}
#else
#if defined(HT_UART0) && defined(UART0_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UART0_IRQHandler(void)
{
  UART0_IRQ_HANDLER();
}
#endif
#if defined(HT_UART1) && defined(UART1_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UART1_IRQHandler(void)
{
  UART1_IRQ_HANDLER();
}
#endif
#if defined(HT_UART2) && defined(UART2_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UART2_IRQHandler(void)
{
  UART2_IRQ_HANDLER();
}
#endif
#if defined(HT_UART3) && defined(UART3_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UART3_IRQHandler(void)
{
  UART3_IRQ_HANDLER();
}
#endif
#if defined(HT_UART4) && defined(UART4_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UART4_IRQHandler(void)
{
  UART4_IRQ_HANDLER();
}
#endif
#endif
#else
#ifdef HTCFG_UARTM_CH0
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UARTM_CH0_IRQHandler(void)
{
  _UARTM_IRQHandler(UARTM_CH0);
}
#endif

#ifdef HTCFG_UARTM_CH1
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UARTM_CH1_IRQHandler(void)
{
  _UARTM_IRQHandler(UARTM_CH1);
}
#endif

#ifdef HTCFG_UARTM_CH2
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UARTM_CH2_IRQHandler(void)
{
  _UARTM_IRQHandler(UARTM_CH2);
}
#endif

#ifdef HTCFG_UARTM_CH3
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UARTM_CH3_IRQHandler(void)
{
  _UARTM_IRQHandler(UARTM_CH3);
}
#endif

#ifdef HTCFG_UARTM_CH4
/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
void UARTM_CH4_IRQHandler(void)
{
  _UARTM_IRQHandler(UARTM_CH4);
}
#endif
#endif

/*********************************************************************************************************//**
  * @brief  This function handles UART interrupt.
  * @param  CH
  * @retval None
  ***********************************************************************************************************/
static void _UARTM_IRQHandler(u32 CH)
{
  u8 uTempData;
  s32 i;
  UARTModule_StateTypeDef *pUARTMState = &gUARTModuleState[CH];
  if (pUARTMState->pUARTx == 0)
  {
    return;
  }
#if LIBCFG_USART_V01
  if (USART_GetFlagStatus(pUARTMState->pUARTx, USART_FLAG_RLSI))
  {
    if (pUARTMState->pUARTx->SR & USART_LSR_OE)
    {
      __DBG_Printf("Rx Over Run!\n\r");
      while (1);
    }
  }
#else
  if (USART_GetFlagStatus(pUARTMState->pUARTx, USART_FLAG_OE))
  {
    __DBG_Printf("Rx Over Run!\n\r");
    while (1);
  }
#endif
  if (USART_GetFlagStatus(pUARTMState->pUARTx, USART_FLAG_TXDE))
  {
    if (Buffer_isEmpty(&gUART_Tx[CH]))
    {
      USART_IntConfig(pUARTMState->pUARTx, USART_INT_TXDE, DISABLE);
    }
    else
    {
      if (pUARTMState->uFIFOMode == 1)
      {
        for (i = 6; i != 0; i--)
        {
          Buffer_ReadByte(&gUART_Tx[CH], &uTempData);
          pUARTMState->pUARTx->DR = uTempData;
          if (Buffer_isEmpty(&gUART_Tx[CH]))
          {
            break;
          }
        }
      }
      else
      {
        Buffer_ReadByte(&gUART_Tx[CH], &uTempData);
        pUARTMState->pUARTx->DR = uTempData;
      }
    }
  }

  if (pUARTMState->uFIFOMode == 0)
  {
    /*------------------------------------------------------------------------------------------------------*/
    /* Move data from UART FIFO to buffer when Rx FIFO level reached                                        */
    /*------------------------------------------------------------------------------------------------------*/
    if (USART_GetFlagStatus(pUARTMState->pUARTx, USART_FLAG_RXDR))
    {
      #if (UART_MODULE_DEBUG_MODE == 1)
      if (Buffer_isFull(&gUART_Rx[CH]))
      {
        /*--------------------------------------------------------------------------------------------------*/
        /* Should not reach here! It means the buffer for USART is full.                                    */
        /*--------------------------------------------------------------------------------------------------*/
        __DBG_Printf("UART Rx Buffer Full!\n\r");
        while (1);
      }
      #endif
      Buffer_WriteByte(&gUART_Rx[CH], (pUARTMState->pUARTx->DR & (u32)0x000000FF));
    }
  }
  else
  {
    /*------------------------------------------------------------------------------------------------------*/
    /* Move data from USART FIFO to buffer when Rx timeout                                                  */
    /*------------------------------------------------------------------------------------------------------*/
    if (USART_GetFlagStatus(pUARTMState->pUARTx, USART_FLAG_TOUT))
    {
      #ifndef LIBCFG_USART_V01
      USART_ClearFlag(pUARTMState->pUARTx, USART_FLAG_TOUT);
      #endif
      while (USART_GetFIFOStatus(pUARTMState->pUARTx, USART_FIFO_RX))
      {
        #if (UART_MODULE_DEBUG_MODE == 1)
        if (Buffer_isFull(&gUART_Rx[CH]))
        {
          /*------------------------------------------------------------------------------------------------*/
          /* Should not reach here! It means the buffer for USART is full.                                  */
          /*------------------------------------------------------------------------------------------------*/
          __DBG_Printf("UART Rx Buffer Full!\n\r");
          while (1);
        }
        #endif
        Buffer_WriteByte(&gUART_Rx[CH], (pUARTMState->pUARTx->DR & (u32)0x000000FF));
      }
    }

    /*------------------------------------------------------------------------------------------------------*/
    /* Move data from USART FIFO to buffer when Rx FIFO level reached                                       */
    /*------------------------------------------------------------------------------------------------------*/
    if (USART_GetFlagStatus(pUARTMState->pUARTx, USART_FLAG_RXDR))
    {
      while (USART_GetFIFOStatus(pUARTMState->pUARTx, USART_FIFO_RX))
      {
        #if (UART_MODULE_DEBUG_MODE == 1)
        if (Buffer_isFull(&gUART_Rx[CH]))
        {
          /*------------------------------------------------------------------------------------------------*/
          /* Should not reach here! It means the buffer for USART is full.                                  */
          /*------------------------------------------------------------------------------------------------*/
          __DBG_Printf("UART Rx Buffer Full!\n\r");
          while (1);
        }
        #endif
        Buffer_WriteByte(&gUART_Rx[CH], (pUARTMState->pUARTx->DR & (u32)0x000000FF));
      }
    }
  }

  #if (LIBCFG_USART_V01)
  // Did not supptor TXC interrupt.
  // Use "while (USART_GetFlagStatus(HTCFG_UART_PORT, USART_FLAG_TXC) == RESET);" instead.
  #else
  if (USART_GetIntStatus(pUARTMState->pUARTx, USART_INT_TXC) &&
      USART_GetFlagStatus(pUARTMState->pUARTx, USART_FLAG_TXC))
  {
    USART_IntConfig(pUARTMState->pUARTx, USART_INT_TXC, DISABLE);
    pUARTMState->uIsTxFinished = TRUE;

    #if FREERTOS_UART
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    #endif
  }
  #endif
}

#if FREERTOS_UART
void UARTM_Init_FreeRTOS(u32 CH, USART_InitTypeDef *pUART_Init, u32 uRxTimeOutValue)
{
  taskENTER_CRITICAL();
  UARTM_Init(CH, pUART_Init, uRxTimeOutValue);
  Semphr[CH] = xSemaphoreCreateBinaryStatic(&Semphr_Buffer[CH]);
  Mutex_TX[CH] = xSemaphoreCreateMutexStatic(&Mutex_TX_Buffer[CH]);
  Mutex_RX[CH] = xSemaphoreCreateMutexStatic(&Mutex_RX_Buffer[CH]);
  taskEXIT_CRITICAL();
}

u32 UARTM_WriteByte_FreeRTOS(u32 CH, u8 uData, u32 Timeout)
{
  TimeOut_t Tick_Base;

  vTaskSetTimeOutState(&Tick_Base);

  if (xSemaphoreTake(Mutex_TX[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  taskENTER_CRITICAL();
  UARTM_WriteByte(CH, uData);
  xSemaphoreTake(Semphr[CH], 0);
  taskEXIT_CRITICAL();

  if (xTaskCheckForTimeOut(&Tick_Base, &Timeout) != pdFALSE )
  {
    xSemaphoreGive(Mutex_TX[CH]);
    return FALSE;
  }

  if (xSemaphoreTake(Semphr[CH], Timeout) == pdFALSE)
  {
    xSemaphoreGive(Mutex_TX[CH]);
    return FALSE;
  }

  xSemaphoreGive(Mutex_TX[CH]);

  return Transfer_Result[CH];
}

u32 UARTM_Write_FreeRTOS(u32 CH, u8 *pBuffer, u32 uLength, u32 Timeout)
{
  TimeOut_t Tick_Base;

  vTaskSetTimeOutState(&Tick_Base);

  if (xSemaphoreTake(Mutex_TX[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  taskENTER_CRITICAL();
  UARTM_Write(CH, pBuffer, uLength);
  xSemaphoreTake(Semphr[CH], 0);
  taskEXIT_CRITICAL();

  if (xTaskCheckForTimeOut(&Tick_Base, &Timeout) != pdFALSE )
  {
    xSemaphoreGive(Mutex_TX[CH]);
    return FALSE;
  }

  if (xSemaphoreTake(Semphr[CH], Timeout) == pdFALSE)
  {
    xSemaphoreGive(Mutex_TX[CH]);
    return FALSE;
  }

  xSemaphoreGive(Mutex_TX[CH]);

  return Transfer_Result[CH];
}

u32 UARTM_ReadByte_FreeRTOS(u32 CH, u8 *pData, u32 Timeout)
{
  u32 uResult = FALSE;

  if (xSemaphoreTake(Mutex_RX[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  uResult = UARTM_ReadByte(CH, pData);

  xSemaphoreGive(Mutex_RX[CH]);

  return uResult;
}

u32 UARTM_Read_FreeRTOS(u32 CH, u8 *pBuffer, u32 uLength, u32 Timeout)
{
  u32 uResult = 0;

  if (xSemaphoreTake(Mutex_RX[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  uResult = UARTM_Read(CH, pBuffer, uLength);

  xSemaphoreGive(Mutex_RX[CH]);

  return uResult;
}

u32 UARTM_DiscardReadBuffer_FreeRTOS(u32 CH, u32 Timeout)
{
  if (xSemaphoreTake(Mutex_RX[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  UARTM_DiscardReadBuffer(CH);
  xSemaphoreGive(Mutex_RX[CH]);

  return TRUE;
}
#endif
