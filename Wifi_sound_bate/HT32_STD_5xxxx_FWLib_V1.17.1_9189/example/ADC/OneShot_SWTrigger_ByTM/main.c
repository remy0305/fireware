/*********************************************************************************************************//**
 * @file    ADC/OneShot_SWTrigger_ByTM/main.c
 * @version $Rev:: 6365         $
 * @date    $Date:: 2022-10-21 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup ADC_Examples ADC
  * @{
  */

/** @addtogroup OneShot_SWTrigger_ByTM
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define ADC_TRIGGER_TIME_COUNT                    (2)

#if defined(USE_HT32F50020_30)
#define HTCFG_BFTM0_TIME_BASE                     (LIBCFG_MAX_SPEED / 1000 * 4)   /* 4 mS                   */
#else
#define HTCFG_BFTM0_TIME_BASE                     (LIBCFG_MAX_SPEED * 1)   /* 1 S                           */
#endif

/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
void ADC_Configuration(void);
void ADC_MainRoutine(void);

void BFTM_Configuration(void);

/* Private macro -------------------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------------------*/
u8 gADC_TimeCount = ADC_TRIGGER_TIME_COUNT;

u16 gADC_Result[2];
vu8 gADC_CycleEndOfConversion = FALSE;

/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  ADC_Configuration();
  ADC_Cmd(HT_ADC0, ENABLE);

  BFTM_Configuration();

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
  if (gADC_TimeCount == 0)
  {
    gADC_TimeCount = ADC_TRIGGER_TIME_COUNT;
    ADC_SoftwareStartConvCmd(HT_ADC0, ENABLE); // Software trigger ADC start of conversion
  }

  if (gADC_CycleEndOfConversion)
  {
    #if 1 // For test purpose
    printf("ADC Result = %4u %4u\r\n", gADC_Result[0], gADC_Result[1]);
    #endif

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
    CKCUClock.Bit.ADC0 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as ADC function                                                                    */
  /* !!! NOTICE !!!
     The "GPIO_Px" and "AFIO_PIN_n" shall be modified according to the MCU part number.
  */
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_0, AFIO_FUN_ADC0);
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_1, AFIO_FUN_ADC0);

  { /* ADC related settings                                                                                 */
    /* CK_ADC frequency is set to (CK_AHB / 64)                                                             */
    #if defined(USE_HT32F50020_30)
    #else
    CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0, CKCU_ADCPRE_DIV64);
    #endif

    /* One Shot mode, sequence length = 2                                                                   */
    ADC_RegularGroupConfig(HT_ADC0, ONE_SHOT_MODE, 2, 0);

    /* ADC conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC              */
    /* Set ADST = 36, sampling time = 1.5 + ADST                                                            */
    ADC_SamplingTimeConfig(HT_ADC0, 36);

    /* Set ADC conversion sequence as channel n                                                             */
    /* !!! NOTICE !!!
       The "ADC_CH_n" shall be modified according to the MCU part number.
    */
    ADC_RegularChannelConfig(HT_ADC0, ADC_CH_2, 0);
    ADC_RegularChannelConfig(HT_ADC0, ADC_CH_3, 1);

    /* Set ADC trigger source                                                                               */
    ADC_RegularTrigConfig(HT_ADC0, ADC_TRIG_SOFTWARE);
  }

  /* Enable ADC end of conversion interrupt                                                                 */
  #if 0
  ADC_IntConfig(HT_ADC0, ADC_INT_SINGLE_EOC | ADC_INT_CYCLE_EOC, ENABLE);
  #else
  ADC_IntConfig(HT_ADC0, ADC_INT_CYCLE_EOC, ENABLE);
  #endif

  /* Enable the ADC interrupts                                                                              */
  NVIC_EnableIRQ(ADC0_IRQn);
}

/*********************************************************************************************************//**
  * @brief  BFTM Configuration.
  * @retval None
  ***********************************************************************************************************/
void BFTM_Configuration(void)
{
  #if 0 // Use following function to configure the IP clock speed.
  CKCU_SetPeripPrescaler(CKCU_PCLK_BFTM0, CKCU_APBCLKPRE_DIV2);
  #endif

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.BFTM0 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* BFTM as Repetitive mode, every n second to trigger the match interrupt                                 */
  BFTM_SetCompare(HT_BFTM0, HTCFG_BFTM0_TIME_BASE);
  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_IntConfig(HT_BFTM0, ENABLE);
  BFTM_EnaCmd(HT_BFTM0, ENABLE);

  NVIC_EnableIRQ(BFTM0_IRQn);
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
