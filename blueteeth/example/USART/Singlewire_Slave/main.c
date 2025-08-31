/*********************************************************************************************************//**
 * @file    USART/Singlewire_Slave/main.c
 * @version $Rev:: 8470         $
 * @date    $Date:: 2025-03-06 #$
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

/** @addtogroup Singlewire_Slave
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void UxART_Configuration(void);
void UxART_Slave_Tx(void);
u8 buffer_compare(uc8* pbuffer1 ,uc8* pbuffer2 ,vu32 buffer_length);

/* Global variables ----------------------------------------------------------------------------------------*/
uc8  *gURTx_Ptr;
u32 gURTx_Length = 0;
u8  *gURRx_Ptr;
u32 gURRx_Length = 0;

vu32 gRx_Match_Flag = FALSE;

/* Private variables ---------------------------------------------------------------------------------------*/
uc8 gMasterString[] = "0123456789";
uc8 gSlaveString[] = "ABCDEFGHIJ";
u8 gTx_Buffer[128];
u8 gRx_Buffer[128];

u32 gURMaster_Length = sizeof(gMasterString) - 1;
u32 gURSlave_Length = sizeof(gSlaveString) - 1;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);
  HT32F_DVB_LEDInit(HT_LED3);

  gURRx_Ptr = gRx_Buffer;

  UxART_Configuration();

  while (1)
  {
    if(gRx_Match_Flag)
    {
      if(buffer_compare(gMasterString ,gRx_Buffer ,gURMaster_Length))
      {
        HT32F_DVB_LEDOn(HT_LED1);
        HT32F_DVB_LEDOn(HT_LED2);
        HT32F_DVB_LEDOn(HT_LED3);
      }
      else
      {
        HT32F_DVB_LEDOff(HT_LED1);
        HT32F_DVB_LEDOff(HT_LED2);
        HT32F_DVB_LEDOff(HT_LED3);
      }
      UxART_Slave_Tx();
    }
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
    CKCUClock.Bit.HTCFG_UART_RTX_GPIO_CLK = 1;
    CKCUClock.Bit.HTCFG_UART_IPN         = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Turn on UxART RTx internal pull up resistor to prevent unknow state                                    */
  GPIO_PullResistorConfig(HTCFG_UART_RTX_GPIO_PORT, HTCFG_UART_RTX_GPIO_PIN, GPIO_PR_UP);

  /* Turn on UxART RTx open drain                                                                           */
  GPIO_OpenDrainConfig(HTCFG_UART_RTX_GPIO_PORT, HTCFG_UART_RTX_GPIO_PIN, ENABLE);

  /* Config AFIO mode as UxART function                                                                     */
  AFIO_GPxConfig(HTCFG_UART_RTX_GPIO_ID, HTCFG_UART_RTX_AFIO_PIN, AFIO_FUN_USART_UART);

  {
    /* UxART configured as follow:
          - BaudRate = 115200 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - None parity bit
          - Mode = Single-wire mode
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
    USART_InitStructure.USART_Mode = USART_MODE_SINGLE_WIRE;
    USART_Init(HTCFG_UART_PORT, &USART_InitStructure);
  }

  /* Enable UxART interrupt of NVIC                                                                         */
  NVIC_EnableIRQ(HTCFG_UART_IRQn);

  /* Enable UxART Rx interrupt                                                                              */
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_RXDR, ENABLE);

  /* Enable UxART Tx and Rx function                                                                        */
  USART_TxCmd(HTCFG_UART_PORT, ENABLE);
  USART_RxCmd(HTCFG_UART_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  UxART Master Tx.
  * @retval None
  ***********************************************************************************************************/
void UxART_Slave_Tx(void)
{
  /* Initialize Rx variables                                                                                */
  gRx_Match_Flag = FALSE;
  gURRx_Length = 0;

  /* Disable UxART Rx function                                                                              */
  USART_RxCmd(HTCFG_UART_PORT, DISABLE);

  /* Setting Tx variables and enable UxART Tx interrupt                                                     */
  gURTx_Ptr = (u8 *)gSlaveString;
  gURTx_Length = sizeof(gSlaveString) - 1;
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_TXDE | USART_INT_TXC, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Compares two buffers.
  * @retval None
  ***********************************************************************************************************/
u8 buffer_compare(uc8* pbuffer1 ,uc8* pbuffer2 ,vu32 buffer_length)
{
  while(buffer_length--)
  {
    if(*pbuffer1 != *pbuffer2)
    {
      return 0;
    }
    pbuffer1++;
    pbuffer2++;
  }
  return 1;
}

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
