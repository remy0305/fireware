/*********************************************************************************************************//**
 * @file    ADC/OneShot_PWMTrigger_with_Delay/main.c
 * @version $Rev:: 7265         $
 * @date    $Date:: 2023-10-02 #$
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

/** @addtogroup OneShot_PWMTrigger_with_Delay
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void ADC_Configuration(void);
void TM_Configuration(void);

void ADC_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 gADC_Result[3];
vu32 gADC_CycleEndOfConversion;

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

  ADC_Configuration();

  TM_Configuration();

  ADC_Cmd(HTCFG_ADC_PORT, ENABLE);

  TM_SetCaptureCompare3(HTCFG_PWM_TM_PORT, 20000 - 1 + 20); // CH3O ADC trigger delay 20 GPTM clock after CH2

  /* Enable TM which will trigger ADC start of conversion periodically                                      */
  TM_Cmd(HTCFG_PWM_TM_PORT, ENABLE);

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
  if (gADC_CycleEndOfConversion)
  {
    printf("ADC Result Seq0:%4u Seq1:%4u Seq2:%4u\r\n", gADC_Result[0], gADC_Result[1], gADC_Result[2]);
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

    /* One Shot mode, sequence length = 3                                                                   */
    ADC_RegularGroupConfig(HTCFG_ADC_PORT, ONE_SHOT_MODE, 3, 0);

    /* ADC conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC              */
    /* Set ADST = 36, sampling time = 1.5 + ADST                                                            */
    #if (LIBCFG_ADC_SAMPLE_TIME_BY_CH)
      // The sampling time is set by the last parameter of the function "ADC_RegularChannelConfig()".
    #else
    ADC_SamplingTimeConfig(HTCFG_ADC_PORT, 36);
    #endif

    /* Set ADC conversion sequence as channel n                                                             */
    ADC_RegularChannelConfig(HTCFG_ADC_PORT, HTCFG_VR_ADC_CH, 0, 36);
    ADC_RegularChannelConfig(HTCFG_ADC_PORT, HTCFG_AD2_ADC_CH, 1, 36);
    ADC_RegularChannelConfig(HTCFG_ADC_PORT, HTCFG_AD3_ADC_CH, 2, 36);

    /* Set GPTM0 CH3O as ADC trigger source                                                                 */
    ADC_RegularTrigConfig(HTCFG_ADC_PORT, HTCFG_ADC_TRIG_TM_CH3O);
  }

  /* Enable ADC single/cycle end of conversion interrupt                                                    */
  ADC_IntConfig(HTCFG_ADC_PORT, ADC_INT_SINGLE_EOC | ADC_INT_CYCLE_EOC, ENABLE);

  /* Enable the ADC interrupts                                                                              */
  NVIC_EnableIRQ(HTCFG_ADC_IRQn);
}

/*********************************************************************************************************//**
  * @brief  TM configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  /* Configure GPTM0 channel 2 as PWM output mode, channel 3 used to trigger ADC start of conversion        */

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.HTCFG_PWM_TM_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  AFIO_GPxConfig(HTCFG_PWM_GPIO_ID, HTCFG_PWM_AFIO_PIN, HTCFG_PWM_AFIO_FUN);

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
    TM_TimeBaseInit(HTCFG_PWM_TM_PORT, &TimeBaseInit);
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;
    OutInit.Channel = HTCFG_PWM_TM_CH;
    OutInit.OutputMode = TM_OM_PWM2;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = 20000 - 1;
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HTCFG_PWM_TM_PORT, &OutInit);

    OutInit.Channel = TM_CH_3;
    TM_OutputInit(HTCFG_PWM_TM_PORT, &OutInit);
  }

  TM_IntConfig(HTCFG_PWM_TM_PORT, TM_INT_CH3CC, ENABLE);
  NVIC_EnableIRQ(HTCFG_PWM_IRQn);
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
