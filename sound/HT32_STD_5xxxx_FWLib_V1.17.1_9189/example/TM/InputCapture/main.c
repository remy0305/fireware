/*********************************************************************************************************//**
 * @file    TM/InputCapture/main.c
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
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

/** @addtogroup TM_Examples TM
  * @{
  */

/** @addtogroup InputCapture
  * @{
  */


/* Private types -------------------------------------------------------------------------------------------*/
typedef struct
{
  u32 OverflowCounter;
  u32 StartValue;
  u32 CapturePulse;
  TM_CHP_Enum ChannelPolarity;
  bool DataValid;
  bool DataOverwrite;
} sPulseCaptureStructure;

/* Private function prototypes -----------------------------------------------------------------------------*/
void Capture_Configuration(void);
void Capture_MainRoutine(void);
void Capture_IRQHandler(void);
void Capture_Process(sPulseCaptureStructure* cap, u16 capture_value, bool isCapBeforeUpdate);

void PWM_OUT_Configuration(void);

/* Private variables ---------------------------------------------------------------------------------------*/
sPulseCaptureStructure CaptureCHx;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  Capture_Configuration();

  PWM_OUT_Configuration();

  while (1)
  {
    Capture_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  Capture Main Routine.
  * @retval None
  ***********************************************************************************************************/
void Capture_MainRoutine(void)
{
  if (CaptureCHx.DataValid)
  {
    printf("Capture: %d %8.2f uS\r\n", CaptureCHx.CapturePulse, ((float)CaptureCHx.CapturePulse / (SystemCoreClock / 1000000ul)));
    CaptureCHx.DataValid = FALSE;
  }
}

/*********************************************************************************************************//**
  * @brief  Configures TM to capture waveform.
  * @retval None
  ***********************************************************************************************************/
void Capture_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_CAP_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  AFIO_GPxConfig(HTCFG_CAP_GPIO_ID, HTCFG_CAP_AFIO_PIN, HTCFG_CAP_AFIO_FUN);

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = 1 - 1;                         // Timer clock = CK_AHB / 1
    TimeBaseInit.CounterReload = 0xFFFF;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_CAP_PORT, &TimeBaseInit);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    TM_ClearFlag(HTCFG_CAP_PORT, TM_FLAG_UEV);
  }

  { /* Channel n capture configuration                                                                      */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_CaptureInitTypeDef CapInit;

    TM_CaptureStructInit(&CapInit);
    CapInit.Channel = HTCFG_CAP_CH;
    CapInit.Polarity = TM_CHP_NONINVERTED;
    CapInit.Selection = TM_CHCCS_DIRECT;
    CapInit.Prescaler = TM_CHPSC_OFF;
    #if (LIBCFG_TM_65X_66X_V1)
    CapInit.Fsampling = TM_CHFDIV_1;
    CapInit.Event = TM_CHFEV_OFF;
    #else
    CapInit.Filter = 0x0;
    #endif
    TM_CaptureInit(HTCFG_CAP_PORT, &CapInit);
  }

  /* Enable TM Channel Capture and Update Event interrupts                                                  */
  TM_IntConfig(HTCFG_CAP_PORT, HTCFG_CAP_CCR | TM_INT_UEV, ENABLE);
  NVIC_EnableIRQ(HTCFG_CAP_IRQn);

  TM_Cmd(HTCFG_CAP_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  This function handles GPTM interrupt.
  * @retval None
  ***********************************************************************************************************/
void HTCFG_CAP_IRQHandler(void)
{
  bool update_flag = FALSE;

  /* store and clear all interrupt flags                                                                    */
  u32 status = HTCFG_CAP_PORT->INTSR;
  u32 cnt = HTCFG_CAP_PORT->CNTR;
  #if 0
  if ((status & TM_INT_UEV) != (HTCFG_CAP_PORT->INTSR & TM_INT_UEV))
  {
    status = HTCFG_CAP_PORT->INTSR;
    cnt = HTCFG_CAP_PORT->CNTR;
  }
  #endif
  HTCFG_CAP_PORT->INTSR = ~status;

  if (status & TM_INT_UEV)
  {
    update_flag = TRUE;
    /* The OverflowCounter will stop at max value 0xFFFF                                                    */
    if (CaptureCHx.OverflowCounter != 0xFFFF)
      CaptureCHx.OverflowCounter++;
  }

  if (status & HTCFG_CAP_CCR)
  {
    u32 cap_value = TM_GetCaptureCompare(HTCFG_CAP_PORT, HTCFG_CAP_CH);
    bool isCapBeforeUpdate = (update_flag && (cap_value > cnt))? TRUE : FALSE;
    Capture_Process(&CaptureCHx, cap_value, isCapBeforeUpdate);
    TM_ChPolarityConfig(HTCFG_CAP_PORT, HTCFG_CAP_CH, CaptureCHx.ChannelPolarity);
  }
}

/*********************************************************************************************************//**
 * @brief   Capture Process function.
 * @retval  None
 ************************************************************************************************************/
void Capture_Process(sPulseCaptureStructure* cap, u16 capture_value, bool isCapBeforeUpdate)
{
  if (cap->ChannelPolarity == TM_CHP_NONINVERTED)
  {
    /* Reset OverflowCounter and store capture value when rising edge occurred                              */
    if (isCapBeforeUpdate)
    {
      cap->OverflowCounter = 1;
    }
    else
    {
      cap->OverflowCounter = 0;
    }

    cap->StartValue = capture_value;

    /* Change channel polarity to capture when falling edge occur                                           */
    cap->ChannelPolarity = TM_CHP_INVERTED;
  }
  else
  {
    /* Compute pulse width in PCLK unit when falling edge occurred                                          */
    if (isCapBeforeUpdate)
      cap->OverflowCounter--;

    /* Pulse width clock cycles = (overflow counter * (CounterReload + 1)) - rising capture + falling capture */
    cap->CapturePulse = (cap->OverflowCounter << 16) - cap->StartValue + capture_value;

    if (cap->DataValid)
      cap->DataOverwrite = TRUE;
    else
      cap->DataValid = TRUE;

    /* Change channel polarity to capture when rising edge occur                                            */
    cap->ChannelPolarity = TM_CHP_NONINVERTED;
  }
}

/*********************************************************************************************************//**
  * @brief   Configures TM to output PWM waveform.
  * @retval  None
  * @details Configuration as frequency 1 Hz and duty 2500 uS (10/4000).
  ***********************************************************************************************************/
void PWM_OUT_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_PWM_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  AFIO_GPxConfig(HTCFG_PWM_GPIO_ID, HTCFG_PWM_AFIO_PIN, HTCFG_PWM_AFIO_FUN);

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = (SystemCoreClock / HTCFG_PWM_TM_PCLK) - 1;
    TimeBaseInit.CounterReload = HTCFG_PWM_TM_PCLK - 1;                  // PWM frequency = 1 Hz
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_PWM_PORT, &TimeBaseInit);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    #if 0
    TM_ClearFlag(HTCFG_PWM_PORT, TM_FLAG_UEV);
    #endif
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;

    OutInit.Channel = HTCFG_PWM_CH;
    OutInit.OutputMode = TM_OM_PWM2;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare =  HTCFG_PWM_TM_PCLK - (HTCFG_PWM_TM_PCLK * 0.0025);      // PWM CCR = PWM clock * 2500 us
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HTCFG_PWM_PORT, &OutInit);
  }

  TM_Cmd(HTCFG_PWM_PORT, ENABLE);
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
