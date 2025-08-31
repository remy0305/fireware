/*********************************************************************************************************//**
 * @file    ADC/Two_Group_MaxCH/main.c
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

#include "adc_group.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup ADC_Examples ADC
  * @{
  */

/** @addtogroup Two_Group_MaxCH
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void PDMA_Configuration(void);
void ADC_Configuration(void);
void TM_Configuration(void);

void ADC_TriggerConfig_Software(void);
void ADC_TriggerConfig_TM(void);

void ADC_Test_MainRoutine(void);
void ADC_Test_MainRoutine_Softwre(void);
void ADC_Test_MainRoutine_TM(void);
void ADC_Test_ShowResult(void);

void ADC_Group_SoftwareStart(void);
void ADC_Group1Config(void);
void ADC_Group2Config(void);

void SysTick_Configuration(void);

/* Global variables ----------------------------------------------------------------------------------------*/
vu32 uADCGroupState = 1;    // 0: Stop, 1: Group 1, 2: Group 2.
vu32 uADCGroupFinish = 0;   // 0: Not finish, 2: Finished.

u32 uADCData[16];

u32 uTimeTick500ms = 4;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  SysTick_Configuration();

  #if (ENABLE_DEBUG_IO == 1)
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);
  #endif

  #if (ADC_GROUP_DATA_MODE == ADC_GROUP_DATA_MODE_DMA)
  PDMA_Configuration();
  #endif

  ADC_Configuration();

  #if (ENABLE_DEBUG_PRINTF == 1)
  // Configure Retarget UxART after the "ADC_Configuration()" since "ADC_Configuration()" changes the
  // Retarget AFIO as ADC.
  RETARGET_Configuration();
  #endif

  #if (ADC_GROUP_TRIGGER_MODE == ADC_GROUP_TRIGGER_MODE_SW)
  ADC_TriggerConfig_Software();
  #endif

  #if (ADC_GROUP_TRIGGER_MODE == ADC_GROUP_TRIGGER_MODE_TM)
  TM_Configuration();
  ADC_TriggerConfig_TM();
  #endif

  while (1)
  {
    ADC_Test_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  ADC group main routine
  * @retval None
  ***********************************************************************************************************/
void ADC_Test_MainRoutine(void)
{
  #if (ADC_GROUP_TRIGGER_MODE == ADC_GROUP_TRIGGER_MODE_SW)
  ADC_Test_MainRoutine_Softwre();
  #endif

  #if (ADC_GROUP_TRIGGER_MODE == ADC_GROUP_TRIGGER_MODE_TM)
  ADC_Test_MainRoutine_TM();
  #endif
}

/*********************************************************************************************************//**
  * @brief  ADC Group main routine - Software trigger every 2 second and show the result.
  * @retval None
  ***********************************************************************************************************/
void ADC_Test_MainRoutine_Softwre(void)
{
  if (uTimeTick500ms >= 4)
  {
    uTimeTick500ms = 0;

    ADC_Group_SoftwareStart();
  }

  if (uADCGroupFinish == ADC_GROUP_FINISH)
  {
    uADCGroupFinish = 0;
    ADC_Test_ShowResult();
  }
}

/*********************************************************************************************************//**
  * @brief  ADC Group main routine - Timer trigger every 2 second and show the result.
  * @retval None
  ***********************************************************************************************************/
void ADC_Test_MainRoutine_TM(void)
{
  if (uADCGroupFinish == ADC_GROUP_FINISH)
  {
    uADCGroupFinish = 0;
    ADC_Test_ShowResult();
  }
}

/*********************************************************************************************************//**
  * @brief  Show ADC Result.
  * @retval None
  ***********************************************************************************************************/
void ADC_Test_ShowResult(void)
{
  u32 i;

  uADCData[0] &= 0x00000FFF;
  uADCData[1] &= 0x00000FFF;
  uADCData[2] &= 0x00000FFF;
  uADCData[3] &= 0x00000FFF;
  uADCData[4] &= 0x00000FFF;
  uADCData[5] &= 0x00000FFF;
  uADCData[6] &= 0x00000FFF;
  uADCData[7] &= 0x00000FFF;
  uADCData[8] &= 0x00000FFF;
  uADCData[9] &= 0x00000FFF;
  uADCData[10] &= 0x00000FFF;
  uADCData[11] &= 0x00000FFF;
  uADCData[12] &= 0x00000FFF;
  uADCData[13] &= 0x00000FFF;
  uADCData[14] &= 0x00000FFF;
  uADCData[15] &= 0x00000FFF;

  #if (ENABLE_DEBUG_PRINTF == 1)
  printf("\r\nADC Result\r\n");
  printf("ADC Group 1\r\n");
  for (i = 0; i < ADC_GROUP_LIST_LENGTH; i++)
  {
    printf("ADC Sequence %d = %d\r\n", i, uADCData[i]);
  }
  printf("ADC Group 2\r\n");
  for (i = 0; i < ADC_GROUP_LIST_LENGTH; i++)
  {
    printf("ADC Sequence %d = %d\r\n", i, uADCData[ADC_GROUP_LIST_LENGTH + i]);
  }
  #endif
}

#if (LIBCFG_PDMA)
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

  { /* Configure PDMA channel to move ADC result from ADC->DR[0] to SRAM                                    */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;

    PDMACH_InitStructure.PDMACH_SrcAddr = (u32)&HT_ADC0->DR[0];
    PDMACH_InitStructure.PDMACH_DstAddr = (u32)uADCData;
    PDMACH_InitStructure.PDMACH_BlkCnt = 2;
    PDMACH_InitStructure.PDMACH_BlkLen = ADC_GROUP_LIST_LENGTH;
    PDMACH_InitStructure.PDMACH_DataSize = WIDTH_32BIT;
    PDMACH_InitStructure.PDMACH_Priority = VH_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_CIR_INC | DST_ADR_LIN_INC | AUTO_RELOAD;
    PDMA_Config(PDMA_ADC0, &PDMACH_InitStructure);
    PDMA_EnaCmd(PDMA_ADC0, ENABLE);
  }

  PDMA_IntConfig(PDMA_CH0, (PDMA_INT_GE | PDMA_INT_TC), ENABLE);

  NVIC_EnableIRQ(PDMACH0_1_IRQn);
}
#endif

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
  AFIO_GPxConfig(HTCFG_ADCCH0_GPIO_ID, HTCFG_ADCCH0_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH1_GPIO_ID, HTCFG_ADCCH1_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH2_GPIO_ID, HTCFG_ADCCH2_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH3_GPIO_ID, HTCFG_ADCCH3_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH4_GPIO_ID, HTCFG_ADCCH4_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH5_GPIO_ID, HTCFG_ADCCH5_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH6_GPIO_ID, HTCFG_ADCCH6_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH7_GPIO_ID, HTCFG_ADCCH7_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH8_GPIO_ID, HTCFG_ADCCH8_AFIO_PIN, AFIO_FUN_ADC0);
  AFIO_GPxConfig(HTCFG_ADCCH9_GPIO_ID, HTCFG_ADCCH9_AFIO_PIN, AFIO_FUN_ADC0);
  //AFIO_GPxConfig(HTCFG_ADCCH10_GPIO_ID, HTCFG_ADCCH10_AFIO_PIN, AFIO_FUN_ADC0);
  //AFIO_GPxConfig(HTCFG_ADCCH11_GPIO_ID, HTCFG_ADCCH11_AFIO_PIN, AFIO_FUN_ADC0);
  //AFIO_GPxConfig(HTCFG_ADCCH12_GPIO_ID, HTCFG_ADCCH12_AFIO_PIN, AFIO_FUN_ADC0);
  //AFIO_GPxConfig(HTCFG_ADCCH13_GPIO_ID, HTCFG_ADCCH13_AFIO_PIN, AFIO_FUN_ADC0);
  //AFIO_GPxConfig(HTCFG_ADCCH14_GPIO_ID, HTCFG_ADCCH14_AFIO_PIN, AFIO_FUN_ADC0);
  //AFIO_GPxConfig(HTCFG_ADCCH15_GPIO_ID, HTCFG_ADCCH15_AFIO_PIN, AFIO_FUN_ADC0);

  { /* ADC related settings                                                                                 */
    /* CK_ADC frequency is set to (CK_AHB / n)                                                              */
    #if (ENABLE_DEBUG_IO == 1)
    CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0, CKCU_ADCPRE_DIV64);
    #else
    CKCU_SetADCnPrescaler(CKCU_ADCPRE_ADC0, CKCU_ADCPRE_DIV3);
    #endif

    /* One Shot mode, sequence length = ADC_GROUP_LIST_LENGTH                                               */
    ADC_RegularGroupConfig(HT_ADC0, ONE_SHOT_MODE, ADC_GROUP_LIST_LENGTH, 0);

    /* ADC conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC              */
    /* Set ADST = 36, sampling time = 1.5 + ADST                                                            */
    #if (LIBCFG_ADC_SAMPLE_TIME_BY_CH)
      // The sampling time is set by the last parameter of the function "ADC_RegularChannelConfig()".
    #else
    ADC_SamplingTimeConfig(HT_ADC0, 36);
    #endif

    /* Set ADC conversion sequence as channel n                                                             */
    ADC_Group1Config();
  }

  /* Enable ADC cycle end of conversion interrupt                                                           */
  ADC_IntConfig(HT_ADC0, ADC_INT_CYCLE_EOC, ENABLE);

  #if (ENABLE_DEBUG_IO == 1)
  ADC_IntConfig(HT_ADC0, ADC_INT_SINGLE_EOC, ENABLE);
  #endif

  NVIC_EnableIRQ(ADC0_IRQn);

  #if (ADC_GROUP_DATA_MODE == ADC_GROUP_DATA_MODE_DMA)
  /* Issue ADC DMA request when cycle end of conversion occur                                               */
  ADC_PDMAConfig(HT_ADC0, ADC_PDMA_REGULAR_CYCLE, ENABLE);
  #endif

  ADC_Cmd(HT_ADC0, ENABLE);
}

#if !defined(USE_HT32F50020_30) && !defined(USE_HT32F52234_44)
/*********************************************************************************************************//**
  * @brief  TM configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  /* Configure xxTM Channel 0 to trigger ADC start of conversion every 2 second                             */

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.GPTM0      = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = (SystemCoreClock / 20000) - 1; // GPTM Clock is 20K
    TimeBaseInit.CounterReload = 40000 - 1;                 // 40000/20000 = 2 S;
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
    OutInit.Channel = TM_CH_0;
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

  TM_IntConfig(HT_GPTM0, TM_INT_CH0CC, ENABLE);
}
#endif

/*********************************************************************************************************//**
  * @brief  Configure ADC trigger source as software.
  * @retval None
  ***********************************************************************************************************/
void ADC_TriggerConfig_Software(void)
{
  ADC_RegularTrigConfig(HT_ADC0, ADC_TRIG_SOFTWARE);
}

#if !defined(USE_HT32F50020_30) && !defined(USE_HT32F52234_44)
/*********************************************************************************************************//**
  * @brief  Configure ADC trigger source as Timer.
  * @retval None
  ***********************************************************************************************************/
void ADC_TriggerConfig_TM(void)
{
  ADC_RegularTrigConfig(HT_ADC0, ADC_TRIGGER_TM_SOURCE);
  TM_Cmd(HT_GPTM0, ENABLE);
}
#endif

/*********************************************************************************************************//**
  * @brief  Software trigger of ADC Group
  * @retval None
  ***********************************************************************************************************/
void ADC_Group_SoftwareStart(void)
{
  uADCGroupFinish = 0;
  ADC_SoftwareStartConvCmd(HT_ADC0, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure ADC conversion list as group 1.
  * @retval None
  ***********************************************************************************************************/
void ADC_Group1Config(void)
{
  HT_ADC0->LST[0] = (ADC_GROUP1_LIST0 << 0)  | \
                    (ADC_GROUP1_LIST1 << 8)  | \
                    (ADC_GROUP1_LIST2 << 16) | \
                    (ADC_GROUP1_LIST3 << 24);

  #if !defined(USE_HT32F50020_30)
  HT_ADC0->LST[1] = (ADC_GROUP1_LIST4 << 0)  | \
                    (ADC_GROUP1_LIST5 << 8)  | \
                    (ADC_GROUP1_LIST6 << 16) | \
                    (ADC_GROUP1_LIST7 << 24);
  #endif

  HT_ADC0->CR &= ~(0x00070700);
  HT_ADC0->CR |= ((u32)(0 - 1) << 16) | ((u32)(ADC_GROUP_LIST_LENGTH - 1) << 8);

  #if 0
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST0, 0);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST1, 1);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST2, 2);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST3, 3);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST4, 4);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST5, 5);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST6, 6);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP1_LIST7, 7);
  ADC_RegularGroupConfig(HT_ADC0, ONE_SHOT_MODE, ADC_GROUP_LIST_LENGTH, 0);
  #endif
}

/*********************************************************************************************************//**
  * @brief  Configure ADC conversion list as group 2.
  * @retval None
  ***********************************************************************************************************/
void ADC_Group2Config(void)
{
  HT_ADC0->LST[0] = (ADC_GROUP2_LIST0 << 0)  | \
                    (ADC_GROUP2_LIST1 << 8)  | \
                    (ADC_GROUP2_LIST2 << 16) | \
                    (ADC_GROUP2_LIST3 << 24);

  #if !defined(USE_HT32F50020_30)
  HT_ADC0->LST[1] = (ADC_GROUP2_LIST4 << 0)  | \
                    (ADC_GROUP2_LIST5 << 8)  | \
                    (ADC_GROUP2_LIST6 << 16) | \
                    (ADC_GROUP2_LIST7 << 24);

  HT_ADC0->CR &= ~(0x00070700);
  HT_ADC0->CR |= ((u32)(0 - 1) << 16) | ((u32)(ADC_GROUP_LIST_LENGTH - 1) << 8);
  #endif

  #if 0
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST0, 0);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST1, 1);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST2, 2);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST3, 3);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST4, 4);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST5, 5);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST6, 6);
  ADC_RegularChannelConfig(HT_ADC0, ADC_GROUP2_LIST7, 7);
  ADC_RegularGroupConfig(HT_ADC0, ONE_SHOT_MODE, ADC_GROUP_LIST_LENGTH, 0);
  #endif
}

/*********************************************************************************************************//**
  * @brief  ADC group process of Interrupt Handler (CPU reads ADC result).
  * @retval None
  ***********************************************************************************************************/
void ADC_GroupProcess(void)
{
  #if (ADC_GROUP_DATA_MODE == ADC_GROUP_DATA_MODE_CPU)
  static u32 guDataIndex = 0;
  u32 i;
  #endif

  #if (ENABLE_DEBUG_IO == 1)
  if (ADC_GetFlagStatus(HT_ADC0, ADC_FLAG_SINGLE_EOC))
  {
    ADC_ClearIntPendingBit(HT_ADC0, ADC_FLAG_SINGLE_EOC);
    HT32F_DVB_LEDToggle(HT_LED2);
    //HT_GPIOA->DOUTR ^= (1 << 14);
  }
  #endif

  if (ADC_GetFlagStatus(HT_ADC0, ADC_FLAG_CYCLE_EOC))
  {
    ADC_ClearIntPendingBit(HT_ADC0, ADC_FLAG_CYCLE_EOC);
    if (uADCGroupState == 1)
    {
      uADCGroupState = 2;

      #if (ADC_GROUP_DATA_MODE == ADC_GROUP_DATA_MODE_CPU)
      guDataIndex = 0;
      for (i = 0; i < ADC_GROUP_LIST_LENGTH; i++)
      {
        uADCData[guDataIndex + i] = HT_ADC0->DR[i];
      }
      guDataIndex = ADC_GROUP_LIST_LENGTH;
      #endif

      ADC_Group2Config();

      // Trigger ADC by Software when group 1 conversion is finished
      ADC_RegularTrigConfig(HT_ADC0, ADC_TRIG_SOFTWARE);
      ADC_SoftwareStartConvCmd(HT_ADC0, ENABLE);
    }
    else
    {
      uADCGroupState = 1;

      #if (ADC_GROUP_DATA_MODE == ADC_GROUP_DATA_MODE_CPU)
      for (i = 0; i < ADC_GROUP_LIST_LENGTH; i++)
      {
        uADCData[guDataIndex + i] = HT_ADC0->DR[i];
      }

      uADCGroupFinish = ADC_GROUP_FINISH;
      #endif

      ADC_Group1Config();

      // Restore the trigger source when group 2 conversion is finished
      #if (ADC_GROUP_TRIGGER_MODE == ADC_GROUP_TRIGGER_MODE_TM)
      ADC_RegularTrigConfig(HT_ADC0, ADC_TRIGGER_TM_SOURCE);
      #endif

      #if (ENABLE_DEBUG_IO == 1)
      HT32F_DVB_LEDToggle(HT_LED1);
      #endif
    }
  }
}

/*********************************************************************************************************//**
  * @brief  SysTick configuration.
  * @retval None
  ***********************************************************************************************************/
void SysTick_Configuration(void)
{
  SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);         /* Default : CK_AHB/8                               */
  SYSTICK_SetReloadValue(SystemCoreClock / 8 / 2);      /* (CK_AHB/8/2) = 500ms                             */
  SYSTICK_IntConfig(ENABLE);                            /* Enable SYSTICK Interrupt                         */
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
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
