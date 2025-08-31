/*********************************************************************************************************//**
 * @file    buzzer_pwm.c
 * @version $Rev:: 7566         $
 * @date    $Date:: 2024-01-31 #$
 * @brief   The buzzer function.
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
#include "ht32_board_config.h"

#include "buzzer_pwm.h"

/* Private constants ---------------------------------------------------------------------------------------*/
#define HTCFG_BUZZER_GPIO_ID                      STRCAT2(GPIO_P,         _HTCFG_BUZZER_GPIOX)
#define HTCFG_BUZZER_AFIO_PIN                     STRCAT2(AFIO_PIN_,      _HTCFG_BUZZER_GPION)
#define HTCFG_BUZZER_AFIO_FUN                     STRCAT2(AFIO_FUN_,       HTCFG_BUZZER_IPN)
#define HTCFG_BUZZER_PORT                         STRCAT2(HT_,             HTCFG_BUZZER_IPN)
#define HTCFG_BUZZER_CH                           STRCAT2(TM_CH_,          HTCFG_BUZZER_CHN)
#define HTCFG_BUZZER_IRQn                         STRCAT2(HTCFG_BUZZER_IPN, _IRQn)
#define HTCFG_BUZZER_IRQHandler                   STRCAT2(HTCFG_BUZZER_IPN, _IRQHandler)

#if (HTCFG_BUZZER_TM_REDEFINE == 1)
  /*
    Do the following re-define
      GPTMn_IRQn          ->    GPTMn_G_IRQn
      GPTMn_IRQHandler    ->    GPTMn_G_IRQHandler
      MCTMn_IRQn          ->    MCTMn_UP_IRQn
      MCTMn_IRQHandler    ->    MCTMn_UP_IRQHandler
  */
  #undef HTCFG_BUZZER_IRQn
  #undef HTCFG_BUZZER_IRQHandler

  #if IS_IPN_GPTM(HTCFG_BUZZER_IPN)
  #define HTCFG_BUZZER_IRQn                       STRCAT2(HTCFG_BUZZER_IPN, _G_IRQn)
  #define HTCFG_BUZZER_IRQHandler                 STRCAT2(HTCFG_BUZZER_IPN, _G_IRQHandler)
  #endif

  #if IS_IPN_MCTM(HTCFG_BUZZER_IPN)
  #define HTCFG_BUZZER_IRQn                       STRCAT2(HTCFG_BUZZER_IPN, _UP_IRQn)
  #define HTCFG_BUZZER_IRQHandler                 STRCAT2(HTCFG_BUZZER_IPN, _UP_IRQHandler)
  #endif
#endif

/* Private macro -------------------------------------------------------------------------------------------*/
#define BEE_TIME_MS(t, f)               (f * t / 1000)

#define IPN_NULL                        (0)
#define IPN_MCTM0                       (0x4002C000)
#define IPN_MCTM1                       (0x4002D000)
#define IPN_CHECK(IP)                   STRCAT2(IPN_, IP)
#define IS_IPN_MCTM(IP)                 (IPN_CHECK(IP) == IPN_MCTM0) || (IPN_CHECK(IP) == IPN_MCTM1)

/* Private variables ---------------------------------------------------------------------------------------*/
static u8 gBee_Time;
static u16 gBee_Active;
static u16 gBee_InActive;
static vu32 gBee_Count;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Configure the timer for buzzer.
  * @param  uFrequency: Frequency of Buzzer (Hz).
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Init(u32 uFrequency)
{
  u32 uReload;

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_BUZZER_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  AFIO_GPxConfig(HTCFG_BUZZER_GPIO_ID, HTCFG_BUZZER_AFIO_PIN, HTCFG_BUZZER_AFIO_FUN);

  uReload = (BEE_SYS_CLK / BEE_TM_PRE / uFrequency) - 1;

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler =  BEE_TM_PRE - 1;
    TimeBaseInit.CounterReload = uReload;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_BUZZER_PORT, &TimeBaseInit);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    TM_ClearFlag(HTCFG_BUZZER_PORT, TM_FLAG_UEV);
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;

    OutInit.Channel = HTCFG_BUZZER_CH;
    OutInit.OutputMode = TM_OM_PWM2;
    OutInit.Control = TM_CHCTL_DISABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = ((uReload + 1) * (100 - BEE_DUTY)) / 100;
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HTCFG_BUZZER_PORT, &OutInit);
  }

  #if (IS_IPN_MCTM(HTCFG_BUZZER_IPN))
  /* MCTM channel Main Output Enable                                                                        */
  MCTM_CHMOECmd(HTCFG_BUZZER_PORT, ENABLE);
  #endif

  /* Enable TM interrupt                                                                                    */
  NVIC_EnableIRQ(HTCFG_BUZZER_IRQn);
}

/*********************************************************************************************************//**
  * @brief  Start the Buzzer.
  * @param  uBeeTimes: Bee times.
  * @param  uFrequency: Frequency of Buzzer (Hz).
  * @param  uActive_ms: Bee active time based on ms.
  * @param  uInActive_ms: Bee inactive time based ms.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Start(u8 uBeeTimes, u16 uFrequency, u16 uActive_ms, u16 uInActive_ms)
{
  u32 uReload  =  (BEE_SYS_CLK / BEE_TM_PRE / uFrequency) - 1;
  u32 uCompare =  ((uReload + 1) * (100 - BEE_DUTY)) / 100;

  gBee_Time = uBeeTimes;
  gBee_Active = BEE_TIME_MS(uActive_ms, uFrequency);
  gBee_InActive = BEE_TIME_MS(uInActive_ms, uFrequency);
  gBee_Count = gBee_Active + gBee_InActive;

  TM_SetCounterReload(HTCFG_BUZZER_PORT, uReload);
  TM_SetCaptureCompare(HTCFG_BUZZER_PORT, HTCFG_BUZZER_CH, uCompare);

  TM_IntConfig(HTCFG_BUZZER_PORT, TM_INT_UEV, ENABLE);
  TM_ChannelConfig(HTCFG_BUZZER_PORT, HTCFG_BUZZER_CH, TM_CHCTL_ENABLE);
  TM_Cmd(HTCFG_BUZZER_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Is Buzzer finished.
  * @retval TRUE or FALSE
  ***********************************************************************************************************/
u32 Buzzer_IsFinish(void)
{
  return (gBee_Time ? FALSE : TRUE);
}

/*********************************************************************************************************//**
 * @brief   This function handles TM interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_BUZZER_IRQHandler(void)
{
  TM_ClearFlag(HTCFG_BUZZER_PORT, TM_INT_UEV);

  if (gBee_Count)
  {
    gBee_Count--;
    if (gBee_Count == gBee_InActive)
    {
      TM_ChannelConfig(HTCFG_BUZZER_PORT, HTCFG_BUZZER_CH, TM_CHCTL_DISABLE);
    }

    if (gBee_Count == 0)
    {
      gBee_Count = gBee_Active + gBee_InActive;
      TM_ChannelConfig(HTCFG_BUZZER_PORT, HTCFG_BUZZER_CH, TM_CHCTL_ENABLE);

      if (gBee_Time)
        gBee_Time--;

      if (gBee_Time == 0)
      {
        TM_Cmd(HTCFG_BUZZER_PORT, DISABLE);
      }
    }
  }
}
