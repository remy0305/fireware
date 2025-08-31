/*********************************************************************************************************//**
 * @file    ADC/OneShot_TMTrigger_PDMA/main.c
 * @version $Rev:: 5253         $
 * @date    $Date:: 2021-02-04 #$
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

/** @addtogroup OneShot_TMTrigger_PDMA
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void PDMA_Configuration(void);
void ADC_Configuration(void);
void TM_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  PDMA_Configuration();

  ADC_Configuration();

  TM_Configuration();

  /* !!! NOTICE !!!
     The trigger source must be kept inactive before ADC enable. Since the "TM_TimeBaseInit()" will
     generate an Update Event via the MTO pin, you shall configure the ADC trigger source after
     "TM_Configuration()" when the ADC trigger source is MTO.
  */
  /* Set TM MTO as ADC trigger source                                                                       */
  ADC_RegularTrigConfig(HTCFG_ADC_PORT, HTCFG_ADC_TRIG_TM);

  ADC_Cmd(HTCFG_ADC_PORT, ENABLE);

  /* Enable TM which will trigger ADC start of conversion periodically                                      */
  TM_Cmd(HTCFG_LED_TM_PORT, ENABLE);

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  PDMA configuration.
  * @retval None
  ***********************************************************************************************************/
void PDMA_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.PDMA = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Configure PDMA channel to move ADC result from ADC->DR[0] to TM CHnCCR                               */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;

    PDMACH_InitStructure.PDMACH_SrcAddr = (u32)&HTCFG_ADC_PORT->DR[0];
    PDMACH_InitStructure.PDMACH_DstAddr = (u32)((&HTCFG_LED_TM_PORT->CH0CCR) + HTCFG_LED_TM_CHN);
    PDMACH_InitStructure.PDMACH_BlkCnt = 1;
    PDMACH_InitStructure.PDMACH_BlkLen = 1;
    PDMACH_InitStructure.PDMACH_DataSize = WIDTH_32BIT;
    PDMACH_InitStructure.PDMACH_Priority = VH_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_FIX | AUTO_RELOAD;
    PDMA_Config(HTCFG_DMA_PORT, &PDMACH_InitStructure);
    PDMA_EnaCmd(HTCFG_DMA_PORT, ENABLE);
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
  AFIO_GPxConfig(HTCFG_VR_GPIO_ID, HTCFG_VR_AFIO_PIN, HTCFG_VR_AFIO_MODE);

  { /* ADC related settings                                                                                 */
    /* CK_ADC frequency is set to (CK_AHB / 64)                                                             */
    CKCU_SetADCnPrescaler(HTCFG_ADC_CKCU_ADCPRE, CKCU_ADCPRE_DIV64);

    /* One Shot mode, sequence length = 1                                                                   */
    ADC_RegularGroupConfig(HTCFG_ADC_PORT, ONE_SHOT_MODE, 1, 0);

    /* ADC conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC              */
    /* Set ADST = 0, sampling time = 1.5 + ADST                                                             */
    #if (LIBCFG_ADC_SAMPLE_TIME_BY_CH)
      // The sampling time is set by the last parameter of the function "ADC_RegularChannelConfig()".
    #else
    ADC_SamplingTimeConfig(HTCFG_ADC_PORT, 0);
    #endif

    /* Set ADC conversion sequence as channel n                                                             */
    ADC_RegularChannelConfig(HTCFG_ADC_PORT, HTCFG_VR_ADC_CH, 0, 0);

    #if 0
    /* Set TM MTO as ADC trigger source                                                                     */
    ADC_RegularTrigConfig(HTCFG_ADC_PORT, HTCFG_ADC_TRIG_TM);
    #endif
  }

  /* Issue ADC DMA request when cycle end of conversion occur                                               */
  ADC_PDMAConfig(HTCFG_ADC_PORT, ADC_PDMA_REGULAR_CYCLE, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  TM configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  /* Configure timer channel n as PWM output mode used to represent potentiometer's level                   */

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_LED_TM_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure LED AFIO mode as timer function                                                              */
  AFIO_GPxConfig(HTCFG_LED_GPIO_ID, HTCFG_LED_AFIO_PIN, HTCFG_LED_AFIO_FUN);

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = 100 - 1;
    TimeBaseInit.CounterReload = 4096 - 1;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    /* !!! NOTICE !!!
       "PSCReloadTime = TM_PSC_RLD_IMMEDIATE" writes the TM EVRG UEV1G bit and generates a Update Event via
       the MTO pin (MTO default is in Reset mode).
    */
    TM_TimeBaseInit(HTCFG_LED_TM_PORT, &TimeBaseInit);
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;
    OutInit.Channel = HTCFG_LED_TM_CH;
    OutInit.OutputMode = TM_OM_PWM2;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = 0;
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HTCFG_LED_TM_PORT, &OutInit);

    #if (IS_IPN_MCTM(HTCFG_LED_TM_IPN))
    /* MCTM Channel Main Output Enable                                                                      */
    MCTM_CHMOECmd(HTCFG_LED_TM_PORT, ENABLE);
    #endif
  }

  /* Update event 1 is used as MTO trigger output.                                                          */
  TM_MMSELConfig(HTCFG_LED_TM_PORT, TM_MMSEL_UPDATE);
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
