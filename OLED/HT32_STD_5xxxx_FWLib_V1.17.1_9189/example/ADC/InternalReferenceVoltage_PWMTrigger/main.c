/*********************************************************************************************************//**
 * @file    ADC/InternalReferenceVoltage_PWMTrigger/main.c
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

/** @addtogroup InternalReferenceVoltage_PWMTrigger
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/* Internal VREF output level setting                                                                       */
#if (LIBCFG_ADC_IVREF_LEVEL_TYPE2)

  #define ADC_VREF_LEVEL                ADC_VREF_2V5
  #define VREF_VALUE_mV                 (2500)

  //#define ADC_VREF_LEVEL                ADC_VREF_3V0
  //#define VREF_VALUE_mV                 (3000)

  //#define ADC_VREF_LEVEL                ADC_VREF_4V0
  //#define VREF_VALUE_mV                 (4000)

  //#define ADC_VREF_LEVEL                ADC_VREF_4V5
  //#define VREF_VALUE_mV                 (4500)

#elif (LIBCFG_ADC_IVREF)
  #if (LIBCFG_ADC_IVREF_DEFAULT_08V)
  #define ADC_VREF_LEVEL                ADC_VREF_0V8
  #define VREF_VALUE_mV                 (800)
  #else
  #define ADC_VREF_LEVEL                ADC_VREF_1V215
  #define VREF_VALUE_mV                 (1215)
  #endif

  //#define ADC_VREF_LEVEL                ADC_VREF_2V0
  //#define VREF_VALUE_mV                 (2000)

  //#define ADC_VREF_LEVEL                ADC_VREF_2V5
  //#define VREF_VALUE_mV                 (2500)

  //#define ADC_VREF_LEVEL                ADC_VREF_2V7
  //#define VREF_VALUE_mV                 (2700)

#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
void ADC_Configuration(void);
void TM_Configuration(void);

void ADC_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 gADC_Result[3];
volatile bool gADC_CycleEndOfConversion;

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

  ADC_Cmd(HT_ADC0, ENABLE);

  /* Enable GPTM which will trigger ADC start                                                               */
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
    gADC_CycleEndOfConversion = FALSE;

    /* Show internal VREF voltage and ADC result                                                            */
    printf("VREF=   %4dmV  Value= %4d\n\r", VREF_VALUE_mV, gADC_Result[1]);

    /* Show VDDA, MVDDA, and ADC input (potentiometer) voltage and ADC result                               */
    printf("VDDA=   %4dmV  \n\r", (VREF_VALUE_mV * 4095) / gADC_Result[1]);
    printf("MVDDA=  %4dmV  Value= %4d\n\r", (VREF_VALUE_mV * gADC_Result[0]) / gADC_Result[1], gADC_Result[0]);
    printf("VR=     %4dmV  Value= %4d\n\n\r", (VREF_VALUE_mV * gADC_Result[2]) / gADC_Result[1], gADC_Result[2]);
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
    CKCUClock.Bit.ADC0 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as ADC and VREF function                                                           */
  AFIO_GPxConfig(HTCFG_VR_GPIO_ID, HTCFG_VR_AFIO_PIN, AFIO_FUN_ADC0);

  /* !!! NOTICE !!!
     The VREF output to IO is for test purposes only, it is not recommended to use the VREF output with an
     external circuit.
  */
  #if 0
  AFIO_GPxConfig(HTCFG_VREF_GPIO_ID, HTCFG_VREF_AFIO_PIN, AFIO_FUN_SYSTEM);
  #endif

  { /* ADC related settings                                                                                 */
    /* CK_ADC frequency is set to (CK_AHB / 64)                                                             */
    CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0, CKCU_ADCPRE_DIV64);

    /* One Shot mode, sequence length = 3                                                                   */
    ADC_RegularGroupConfig(HT_ADC0, ONE_SHOT_MODE, 3, 0);

    /* ADC conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC              */
    /* Set ADST = 36, sampling time = 1.5 + ADST                                                            */
    #if (LIBCFG_ADC_SAMPLE_TIME_BY_CH)
      // The sampling time is set by the last parameter of the function "ADC_RegularChannelConfig()".
    #else
    ADC_SamplingTimeConfig(HT_ADC0, 36);
    #endif

    /* Set ADC conversion sequence as channel n                                                             */
    ADC_RegularChannelConfig(HT_ADC0, ADC_CH_MVDDA, 0, 36);
    ADC_RegularChannelConfig(HT_ADC0, ADC_CH_IVREF, 1, 36);
    ADC_RegularChannelConfig(HT_ADC0, HTCFG_VR_ADC_CH, 2, 36);

    /* Set GPTM0 CH3O as ADC trigger source                                                                 */
    ADC_RegularTrigConfig(HT_ADC0, HTCFG_ADC_TRIG_TM_CH3O);
  }

  /* Select the internal VREF output level and enable it                                                    */
  ADC_VREFConfig(HT_ADC0, ADC_VREF_LEVEL);

  /* !!! NOTICE !!!
     VREF needs a minimum of 100 ms stable time (tSTABLE) after enable, please check the datasheet for the
     actual timing. You shall take care of a delay for the stable time according to the application.
  */
  ADC_VREFCmd(HT_ADC0, ENABLE);

  /* Enable MVDDA function                                                                                  */
  ADC_MVDDACmd(HT_ADC0, ENABLE);

  /* Enable ADC single/cycle end of conversion interrupt                                                    */
  ADC_IntConfig(HT_ADC0, ADC_INT_SINGLE_EOC | ADC_INT_CYCLE_EOC, ENABLE);

  /* Enable the ADC interrupts                                                                              */
  NVIC_EnableIRQ(ADC0_IRQn);
}

/*********************************************************************************************************//**
  * @brief  TM Configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  /* Configure GPTM0 channel 3 as PWM output mode used to trigger ADC start of conversion every 1 second    */

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO  = 1;
    CKCUClock.Bit.HTCFG_PWM_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = (SystemCoreClock / 40000) - 1; // GPTM Clock is 40K
    TimeBaseInit.CounterReload = 40000 - 1 ;
    TimeBaseInit.RepetitionCounter  = 0;
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
