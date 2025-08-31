/*********************************************************************************************************//**
 * @file    SLED/ARGB_GetLEDNum/main.c
 * @version $Rev:: 8158         $
 * @date    $Date:: 2024-09-20 #$
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SLED_Examples SLED
  * @{
  */

/** @addtogroup ARGB_GetLEDNum
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define BFTM_MODE                      (1)   /* 0: Timer by GPTM, 1: Timer by BFTM                          */

#define LED_GRB_DATA_LEN               (3)     /* 3 bytes                                                   */
#define LED_NUMBER_OF_COLOR_TYPES      (3)     /* 3 color type                                              */

/* Private constants ---------------------------------------------------------------------------------------*/
#define DELAY_5US                      (300)   /* DELAY_5US / SystemCoreClock = 5us                         */
#define DELAY_10US                     (600)   /* DELAY_10US / SystemCoreClock = 10us                       */
#define DELAY_20US                     (1200)  /* DELAY_20US / SystemCoreClock = 20us                       */
#define DELAY_50US                     (3000)  /* DELAY_50US / SystemCoreClock = 50us                       */

/* Private function prototypes -----------------------------------------------------------------------------*/
void CKCU_Configuration(void);
void TM_Configuration(void);
u32 ARGB_Feedback(void);
void SLED_Configuration(void);
void SLED_MainRoutine(void);
static void __Delay(u32 count);

/* Global variables ----------------------------------------------------------------------------------------*/
u8 __ALIGN4 gGRBTable[LED_NUMBER_OF_COLOR_TYPES][LED_GRB_DATA_LEN] = {
  { 0x00, 0xFF, 0x00 },     /* Red                                                                          */
  { 0xFF, 0x00, 0x00 },     /* Green                                                                        */
  { 0x00, 0x00, 0xFF },     /* Blue                                                                         */
};

u32 i, j, k;
u32 gLampBead;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  printf ("ARGB Feedback Mode Test\r\n");

  CKCU_Configuration();               /* System Related Configuration                                       */

  TM_Configuration();

  gLampBead = ARGB_Feedback();

  SLED_Configuration();

  while (1)
  {
    SLED_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
#if 1
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO            = 1;
  CKCUClock.Bit.HTCFG_SLED_CK   = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
#endif
}

#if (BFTM_MODE == ENABLE)
/*********************************************************************************************************//**
  * @brief  Configure the Timer.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.BFTM0      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  BFTM_SetCompare(HT_BFTM0, SystemCoreClock / 1000000 * 160); /* CompareTime = 160us                        */
  BFTM_ClearFlag(HT_BFTM0);
  BFTM_SetCounter(HT_BFTM0, 0);

  BFTM_EnaCmd(HT_BFTM0, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  ARGB Feedback Mode, returns number of lamp beads.
  * @retval None
  ***********************************************************************************************************/
u32 ARGB_Feedback(void)
{
  u32 uLampbead = 0;
  u32 uCount;
  /* Configure SLED to GPIO mode                                                                            */
  AFIO_GPxConfig(HTCFG_SLED_GPIO_ID, HTCFG_SLED_AFIO_PIN, AFIO_FUN_GPIO);

  /* Configure GPIO direction of output pins                                                                */
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, RESET);
  GPIO_DirectionConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_DIR_OUT);

  /* Generate feedback mode waveform.                                                                       */
  BFTM_SetCounter(HT_BFTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, SET);
  while (BFTM_GetCounter(HT_BFTM0) < DELAY_20US);

  BFTM_SetCounter(HT_BFTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, RESET);
  while (BFTM_GetCounter(HT_BFTM0) < DELAY_10US);

  BFTM_SetCounter(HT_BFTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, SET);
  while (BFTM_GetCounter(HT_BFTM0) < DELAY_50US);

  BFTM_SetCounter(HT_BFTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, RESET);
  while (BFTM_GetCounter(HT_BFTM0) < DELAY_5US);

  /* Configure GPIO direction of input pins                                                                 */
  GPIO_DirectionConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_DIR_IN);

  /* Configure GPIO pull resistor of input pins                                                             */
  GPIO_PullResistorConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_PR_DOWN);

  GPIO_InputConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, ENABLE);

  /* Get reply information                                                                                  */
  while (BFTM_GetFlagStatus(HT_BFTM0) == RESET)
  {
    while (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 0 && BFTM_GetFlagStatus(HT_BFTM0) == RESET){};
    if (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 1 && BFTM_GetFlagStatus(HT_BFTM0) == RESET)
    {
      BFTM_SetCounter(HT_BFTM0, 0);
      uLampbead++;
    }
    while (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 1 && BFTM_GetFlagStatus(HT_BFTM0) == RESET){};
    if (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 0 && BFTM_GetFlagStatus(HT_BFTM0) == RESET)
    {
      uCount = BFTM_GetCounter(HT_BFTM0);
    }
  }

  /* Configure GPIO direction of output pins                                                                */
  GPIO_DirectionConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_DIR_OUT);

  printf ("Drive Current Time= %d us    LampBead= %d\r\n" ,uCount * 1000000 / SystemCoreClock ,uLampbead);

  return uLampbead;
}

#else
/*********************************************************************************************************//**
  * @brief  Configure the Timer.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  TM_TimeBaseInitTypeDef TimeBaseInit;
  TM_OutputInitTypeDef OutInit;

  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.GPTM0      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure xxTM Channel 0 to count time.                                                                */
  TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
  TimeBaseInit.CounterReload = 65535;
  TimeBaseInit.Prescaler = 0;
  TimeBaseInit.RepetitionCounter = 0;
  TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
  TM_TimeBaseInit(HT_GPTM0, &TimeBaseInit);

  TM_ClearFlag(HT_GPTM0, TM_FLAG_UEV);

  /* Init GPTM0 input mode configuration                                                                    */
  OutInit.Channel = TM_CH_0;
  OutInit.OutputMode = TM_OM_PWM1;
  OutInit.Control = TM_CHCTL_ENABLE;
  OutInit.ControlN = TM_CHCTL_DISABLE;
  OutInit.Polarity = TM_CHP_NONINVERTED;
  OutInit.PolarityN = TM_CHP_NONINVERTED;
  OutInit.IdleState = MCTM_OIS_LOW;
  OutInit.IdleStateN = MCTM_OIS_HIGH;
  OutInit.Compare = SystemCoreClock / 1000000 * 160;      /* CompareTime = 160us                            */
  OutInit.AsymmetricCompare = 0;
  TM_OutputInit(HT_GPTM0, &OutInit);

  TM_Cmd(HT_GPTM0, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  ARGB Feedback Mode, returns number of lamp beads.
  * @retval None
  ***********************************************************************************************************/
u32 ARGB_Feedback(void)
{
  u32 uLampbead = 0;
  u32 uCount = 0;

  /* Configure SLED to GPIO mode                                                                            */
  AFIO_GPxConfig(HTCFG_SLED_GPIO_ID, HTCFG_SLED_AFIO_PIN, AFIO_FUN_GPIO);

  /* Configure GPIO direction of output pins                                                                */
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, RESET);
  GPIO_DirectionConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_DIR_OUT);

  /* Generate feedback mode waveform.                                                                       */
  TM_SetCounter(HT_GPTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, SET);
  while (TM_GetCounter(HT_GPTM0) < DELAY_20US);

  TM_SetCounter(HT_GPTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, RESET);
  while (TM_GetCounter(HT_GPTM0) < DELAY_10US);

  TM_SetCounter(HT_GPTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, SET);
  while (TM_GetCounter(HT_GPTM0) < DELAY_50US);

  TM_SetCounter(HT_GPTM0, 0);
  GPIO_WriteOutBits(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, RESET);
  while (TM_GetCounter(HT_GPTM0) < DELAY_5US);

  /* Configure GPIO direction of input pins                                                                 */
  GPIO_DirectionConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_DIR_IN);

  /* Configure GPIO pull resistor of input pins                                                             */
  GPIO_PullResistorConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_PR_DOWN);

  GPIO_InputConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, ENABLE);

  /* Get reply information                                                                                  */
  while (TM_GetFlagStatus(HT_GPTM0, TM_FLAG_UEV) == RESET)
  {
    while (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 0 && TM_GetFlagStatus(HT_GPTM0, TM_FLAG_UEV) == RESET){};
    if (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 1 && TM_GetFlagStatus(HT_GPTM0, TM_FLAG_UEV) == RESET)
    {
      TM_SetCounter(HT_GPTM0, 0);
      uLampbead++;
    }
    while (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 1 && TM_GetFlagStatus(HT_GPTM0, TM_FLAG_UEV) == RESET){};
    if (GPIO_ReadInBit(HTCFG_SLED, HTCFG_SLED_GPIO_PIN) == 0 && TM_GetFlagStatus(HT_GPTM0, TM_FLAG_UEV) == RESET)
    {
      uCount = TM_GetCounter(HT_GPTM0);
    }
  }

  /* Configure GPIO direction of output pins                                                                */
  GPIO_DirectionConfig(HTCFG_SLED, HTCFG_SLED_GPIO_PIN, GPIO_DIR_OUT);

  printf ("Drive Current Time= %d us    LampBead= %d\r\n", (u32) (uCount * 1000000 / SystemCoreClock), uLampbead);

  return uLampbead;
}
#endif

/*********************************************************************************************************//**
  * @brief  Configure the SLED.
  * @retval None
  ***********************************************************************************************************/
void SLED_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below this function.
  */
  SLED_InitTypeDef SLED_InitStruct;
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};

  /* Enable SLED & AFIO APB clock                                                                           */
  CKCUClock.Bit.AFIO             = 1;
  CKCUClock.Bit.HTCFG_SLED_IPN   = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure GPIO to SLED mode                                                                            */
  AFIO_GPxConfig(HTCFG_SLED_GPIO_ID, HTCFG_SLED_AFIO_PIN, AFIO_FUN_SLED);

  /* Configure SLED                                                                                         */
  SLED_InitStruct.ClockPrescaler = HTCFG_SLED_CK_PRESCALER;   /* F_PCLK / HTCFG_SLED_CK_PRESCALER= 20 MHz   */
  SLED_InitStruct.BaudRate       = HTCFG_SLED_BAUDRATE - 1;   /* F_SCLK / HTCFG_SLED_BAUDRATE    = 833 kHz  */
  SLED_InitStruct.TRST           = HTCFG_SLED_RESET - 1;      /* HTCFG_SLED_RESET * 1.2us        = 250us    */
  SLED_InitStruct.T0H            = HTCFG_SLED_T0H - 1;        /* 6/24 = 25% Duty. 1.2us * (25/100)= 0.3us   */
  SLED_InitStruct.T1H            = HTCFG_SLED_T1H - 1;        /* 18/24 = 75% Duty. 1.2us * (75/100)= 0.9us  */
  SLED_InitStruct.SyncState      = SLED_SYNC_STATE_T0;
  SLED_InitStruct.IdleState      = SLED_IDLE_STATE_LOW;
  SLED_InitStruct.ResetState     = SLED_RESET_STATE_LOW;
  SLED_InitStruct.SyncMode       = SLED_SYNC_MODE_DISABLE;
  SLED_InitStruct.OutputPolarity = SLED_OUTPUT_NONINVERTING;
  SLED_Init(HTCFG_SLED_PORT, &SLED_InitStruct);

  /* Enable SLED                                                                                            */
  SLED_OutputCmd(HTCFG_SLED_PORT, ENABLE);
  SLED_FIFOTrigLevelConfig(HTCFG_SLED_PORT, SLED_FIFO_LEVEL_0);
  SLED_Cmd(HTCFG_SLED_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  SLED Main Routine.
  * @retval None
  ***********************************************************************************************************/
void SLED_MainRoutine(void)
{
  /* Select color type                                                                                      */
  for (i = 0; i < LED_NUMBER_OF_COLOR_TYPES; i++)
  {
    /* Select LED                                                                                           */
    for (j = 0; j < gLampBead; j++)
    {
      /* Select RGB                                                                                         */
      for (k = 0; k < LED_GRB_DATA_LEN; k++)
      {
        /* Send data                                                                                        */
        HTCFG_SLED_PORT->DR_8BIT = gGRBTable[i][k]; /* RGB Data. 8-bit access, duplicate 4 times into 32-bit*/
      }
      /* Waiting for transfer to complete                                                                   */
      while (SLED_GetFIFOStatus(HTCFG_SLED_PORT) != 0);
    }
   /* Delay                                                                                                 */
    __Delay(SystemCoreClock/30);
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

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  delay function
  * @param  count: delay count for loop
  * @retval None
  ***********************************************************************************************************/
static void __Delay(u32 count)
{
  while (count--)
  {
    __NOP(); // Prevent delay loop be optimized
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
