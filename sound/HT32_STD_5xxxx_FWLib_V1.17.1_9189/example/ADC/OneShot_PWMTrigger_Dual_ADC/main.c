/*********************************************************************************************************//**
 * @file    ADC/OneShot_PWMTrigger_Dual_ADC/main.c
 * @version $Rev:: 5032         $
 * @date    $Date:: 2020-11-03 #$
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

/** @addtogroup OneShot_PWMTrigger_Dual_ADC
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void Dual_ADC_Configuration(void);
void TM_Configuration(void);

void ADC_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 gADC0_Result[2];
u32 gADC1_Result[2];
vu32 gADC0_CycleEndOfConversion;
vu32 gADC1_CycleEndOfConversion;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);
  HT32F_DVB_LEDInit(HT_LED3);

  Dual_ADC_Configuration();

  TM_Configuration();

  ADC_Cmd(HT_ADC0, ENABLE);
  ADC_Cmd(HT_ADC1, ENABLE);

  /* Enable TM which will trigger ADC start of conversion periodically                                      */
  TM_Cmd(HT_GPTM0, ENABLE);

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
  if (gADC0_CycleEndOfConversion && gADC1_CycleEndOfConversion)
  {
    printf("ADC Result Seq0:%4u Seq1:%4u Seq2:%4u Seq3:%4u\r\n", gADC0_Result[0], gADC0_Result[1], gADC1_Result[0], gADC1_Result[1]);
    gADC0_CycleEndOfConversion = FALSE;
    gADC1_CycleEndOfConversion = FALSE;
  }
}

/*********************************************************************************************************//**
  * @brief  Dual ADC configuration.
  * @retval None
  ***********************************************************************************************************/
void Dual_ADC_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.ADC0 = 1;
    CKCUClock.Bit.ADC1 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as ADC0 function                                                                   */
  AFIO_GPxConfig(HTCFG_ADC0_5_GPIO_ID, HTCFG_ADC0_5_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADC0_6_GPIO_ID, HTCFG_ADC0_6_AFIO_PIN, AFIO_FUN_ADC0);

  /* Configure AFIO mode as ADC1 function                                                                   */
  AFIO_GPxConfig(HTCFG_ADC1_7_GPIO_ID, HTCFG_ADC1_7_AFIO_PIN, AFIO_FUN_ADC1);

  { /* ADC related settings                                                                                 */
    /* CK_ADC frequency is set to (CK_AHB / 64)                                                             */
    CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0, CKCU_ADCPRE_DIV64);
    CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC1, CKCU_ADCPRE_DIV64);

    /* Dual Cascade Regular mode, delayTime = 0 (Synchronous)                                               */
    ADC_DualModeConfig(HT_ADC1, DUAL_CASCADE_REGULAR, 0, 0);

    /* One Shot mode, sequence length = 2                                                                   */
    ADC_RegularGroupConfig(HT_ADC0, ONE_SHOT_MODE, 2, 0);
    ADC_RegularGroupConfig(HT_ADC1, ONE_SHOT_MODE, 2, 0);

    /* ADC conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC              */
    /* Set ADST = 36, sampling time = 1.5 + ADST                                                            */
    /* Set ADC0 conversion sequence as channel n                                                            */
    ADC_RegularChannelConfig(HT_ADC0, HTCFG_ADC0_5_ADC_CH, 0, 36);
    ADC_RegularChannelConfig(HT_ADC0, HTCFG_ADC0_6_ADC_CH, 1, 36);

    /* Set ADC1 conversion sequence as channel n                                                            */
    ADC_RegularChannelConfig(HT_ADC1, HTCFG_ADC1_7_ADC_CH, 0, 36);
    ADC_RegularChannelConfig(HT_ADC1, ADC_CH_VDD_VREF, 1, 36);

    /* Set GPTM0 CH3O as ADC trigger source                                                                 */
    ADC_RegularTrigConfig(HT_ADC0, ADC_TRIG_GPTM0_CH3O);
  }

  /* Enable ADC cycle end of conversion interrupt                                                           */
  ADC_IntConfig(HT_ADC0, ADC_INT_CYCLE_EOC, ENABLE);
  ADC_IntConfig(HT_ADC1, ADC_INT_CYCLE_EOC, ENABLE);

  /* Enable the ADC interrupts                                                                              */
  NVIC_EnableIRQ(ADC0_IRQn);
  NVIC_EnableIRQ(ADC1_IRQn);
}

/*********************************************************************************************************//**
  * @brief  TM configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  /* Configure GPTM0 channel 3 as PWM output mode used to trigger ADC start of conversion every 1 second    */

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.GPTM0 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = (SystemCoreClock / 40000) - 1; // GPTM Clock is 40K
    TimeBaseInit.CounterReload = 40000 - 1;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HT_GPTM0, &TimeBaseInit);
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;
    OutInit.Channel = TM_CH_3;
    OutInit.OutputMode = TM_OM_PWM2;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = 20000 - 1;
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HT_GPTM0, &OutInit);
  }

  TM_IntConfig(HT_GPTM0, TM_INT_CH3CC, ENABLE);
  NVIC_EnableIRQ(GPTM0_IRQn);
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
