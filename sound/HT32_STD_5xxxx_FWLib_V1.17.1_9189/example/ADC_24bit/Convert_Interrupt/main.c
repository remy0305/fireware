/*********************************************************************************************************//**
 * @file    ADC_24bit/Convert_Interrupt/main.c
 * @version $Rev:: 5502         $
 * @date    $Date:: 2021-07-20 #$
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

#include "delta_sigma_adc.h"


/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup ADC_24bit_Examples ADC_24bit
  * @{
  */

/** @addtogroup Convert_Interrupt
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void DRDYB_EXTI_Configuration(void);
void ADC_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
s32 sADCValue;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{

  DRDYB_EXTI_Configuration();

  ADC24_Init();
  ADC24_Start();

  while (1)
  {
    ADC_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  ADC main routine.
  * @retval None
  ***********************************************************************************************************/
void ADC_MainRoutine(void)
{
  /* !!! NOTICE !!!
     The "ADC24_ReadData_MainRoutine()" function shall be called regularly.
  */
  if (ADC24_ReadData_MainRoutine(&sADCValue))
  {
    // ADC data is ready, process data here
    // ...

    // printf("ADC = %d", sADCValue);
    __NOP();
  }
}

/*********************************************************************************************************//**
  * @brief  EXTI configuration for DRDYB.
  * @retval None
  ***********************************************************************************************************/
void DRDYB_EXTI_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO       = 1;
    CKCUClock.Bit.EXTI       = 1;
    CKCUClock.Bit.HTCFG_DRDYB_GPIO_CK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode of input pins                                                                      */
  AFIO_GPxConfig(HTCFG_DRDYB_GPIO_ID, HTCFG_DRDYB_AFIO_PIN, AFIO_FUN_GPIO);

  /* Enable GPIO Input Function                                                                             */
  GPIO_InputConfig(HTCFG_DRDYB_GPIO_PORT, HTCFG_DRDYB_GPIO_PIN, ENABLE);

  /* Configure GPIO pull resistor of input pins                                                             */
  GPIO_PullResistorConfig(HTCFG_DRDYB_GPIO_PORT, HTCFG_DRDYB_GPIO_PIN, GPIO_PR_DISABLE);

  /* Select Port as EXTI Trigger Source                                                                     */
  AFIO_EXTISourceConfig(HTCFG_DRDYB_AFIO_EXTI_CH, HTCFG_DRDYB_AFIO_ESS);

  { /* Configure EXTI Channel n as falling edge trigger                                                     */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    EXTI_InitTypeDef EXTI_InitStruct;

    EXTI_InitStruct.EXTI_Channel = HTCFG_DRDYB_EXTI_CHANNEL;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
    EXTI_Init(&EXTI_InitStruct);
  }

  /* Enable EXTI & NVIC line Interrupt                                                                      */
  EXTI_IntConfig(HTCFG_DRDYB_EXTI_CHANNEL, ENABLE);
  NVIC_EnableIRQ(HTCFG_DRDYB_EXTI_IRQn);
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
