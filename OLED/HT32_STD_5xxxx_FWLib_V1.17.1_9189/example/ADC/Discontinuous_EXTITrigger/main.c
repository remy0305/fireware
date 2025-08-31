/*********************************************************************************************************//**
 * @file    ADC/Discontinuous_EXTITrigger/main.c
 * @version $Rev:: 4826         $
 * @date    $Date:: 2020-07-21 #$
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

/** @addtogroup ADC_Examples ADC
  * @{
  */

/** @addtogroup Discontinuous_EXTITrigger
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void ADC_Configuration(void);
void EXTI_Configuration(void);

void ADC_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 gADC_Result[3];
volatile bool gADC_CycleEndOfConversion;
volatile bool gADC_SubGroupEndOfConversion;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  ADC_Configuration();

  EXTI_Configuration();

  /* Enable ADC                                                                                             */
  ADC_Cmd(HTCFG_ADC_PORT, ENABLE);

  /* Enable EXTI channel                                                                                    */
  EXTI_IntConfig(HTCFG_KEY1_EXTI_CH, ENABLE);

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
  /* Subgroup 0                                                                                             */
  if (gADC_SubGroupEndOfConversion)
  {
    printf("Sequence0:%4u Sequence1:%4u\r\n", (int)gADC_Result[0], (int)gADC_Result[1]);
    gADC_SubGroupEndOfConversion = FALSE;
  }

  /* Subgroup 1                                                                                             */
  if (gADC_CycleEndOfConversion)
  {
    printf("Sequence2:%4u\r\n", (int)gADC_Result[2]);
    gADC_CycleEndOfConversion = FALSE;
  }
}

/*********************************************************************************************************//**
  * @brief  ADC configuration.
  * @retval None
  ***********************************************************************************************************/
void ADC_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_ADC_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as ADC function                                                                    */
  AFIO_GPxConfig(HTCFG_VR_GPIO_ID, HTCFG_VR_AFIO_PIN, HTCFG_ADC_AFIO_MODE);
  AFIO_GPxConfig(HTCFG_AD2_GPIO_ID, HTCFG_AD2_AFIO_PIN, HTCFG_ADC_AFIO_MODE);
  AFIO_GPxConfig(HTCFG_AD3_GPIO_ID, HTCFG_AD3_AFIO_PIN, HTCFG_ADC_AFIO_MODE);

  { /* ADC related settings                                                                                 */
    /* CK_ADC frequency is set to (CK_AHB / 64)                                                             */
    CKCU_SetADCnPrescaler(HTCFG_ADC_CKCU_ADCPRE, CKCU_ADCPRE_DIV64);

    /* Discontinuous mode, sequence length = 3, subgroup length = 2                                         */
    ADC_RegularGroupConfig(HTCFG_ADC_PORT, DISCONTINUOUS_MODE, 3, 2);

    /* ADC conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC              */
    /* Set ADST = 0, sampling time = 1.5 + ADST                                                             */
    #if (LIBCFG_ADC_SAMPLE_TIME_BY_CH)
      // The sampling time is set by the last parameter of the function "ADC_RegularChannelConfig()".
    #else
    ADC_SamplingTimeConfig(HTCFG_ADC_PORT, 0);
    #endif

    /* Set ADC conversion sequence as channel n                                                             */
    ADC_RegularChannelConfig(HTCFG_ADC_PORT, HTCFG_VR_ADC_CH, 0, 0);
    ADC_RegularChannelConfig(HTCFG_ADC_PORT, HTCFG_AD2_ADC_CH, 1, 0);
    ADC_RegularChannelConfig(HTCFG_ADC_PORT, HTCFG_AD3_ADC_CH, 2, 0);

    /* Set EXTI channel n as ADC trigger source                                                             */
    ADC_RegularTrigConfig(HTCFG_ADC_PORT, HTCFG_ADC_TRIG_EXTI);
  }

  /* Enable ADC cycle and subgroup end of conversion interrupt                                              */
  ADC_IntConfig(HTCFG_ADC_PORT, ADC_INT_CYCLE_EOC | ADC_INT_SUB_GROUP_EOC, ENABLE);

  /* Enable the ADC interrupts                                                                              */
  NVIC_EnableIRQ(HTCFG_ADC_IRQn);
}

/*********************************************************************************************************//**
  * @brief  EXTI configuration.
  * @retval None
  ***********************************************************************************************************/
void EXTI_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_KEY1_GPIO_CK = 1;
    CKCUClock.Bit.EXTI = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode of input pins                                                                      */
  AFIO_GPxConfig(HTCFG_KEY1_GPIO_ID, HTCFG_KEY1_AFIO_PIN, AFIO_FUN_GPIO);

  /* Enable GPIO input                                                                                      */
  GPIO_InputConfig(HTCFG_KEY1_GPIO_PORT, HTCFG_KEY1_GPIO_PIN, ENABLE);

  /* Configure GPIO pull resistor of input pins                                                             */
  GPIO_PullResistorConfig(HTCFG_KEY1_GPIO_PORT, HTCFG_KEY1_GPIO_PIN, GPIO_PR_DISABLE);

  /* Connect EXTI channel to GPIO Pin                                                                       */
  AFIO_EXTISourceConfig(HTCFG_KEY1_AFIO_EXTI_CH, HTCFG_KEY1_AFIO_ESS);

  { /* Configure EXTI channel n as falling edge trigger                                                     */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    EXTI_InitTypeDef EXTI_InitStruct;

    EXTI_InitStruct.EXTI_Channel = HTCFG_KEY1_EXTI_CH;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_NEGATIVE_EDGE;
    EXTI_Init(&EXTI_InitStruct);
  }
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
