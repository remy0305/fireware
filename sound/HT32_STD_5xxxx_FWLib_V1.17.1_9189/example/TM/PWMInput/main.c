/*********************************************************************************************************//**
 * @file    TM/PWMInput/main.c
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

/** @addtogroup PWMInput
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define TM_CAP_PRESCAELER           (20)
#if 0
#define SLAVE_RESTART_LATENCY       (2)
#endif

#define TM_PWMOUT_FREQ_HZ           (2000)

/* Private function prototypes -----------------------------------------------------------------------------*/
void TM_Capture_Configuration(void);
void TM_Capture_MainRoutine(void);

void TM_PWMOut_Configuration(void);

/* Private variables ---------------------------------------------------------------------------------------*/
u32 CaptureValue[2];
vu32 wDutyCycle;       /* Duty Cycle in 16.16 fix point format                                              */
vu32 wFrequency;       /* Frequency in 32.0 fix point format                                                */

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  TM_Capture_Configuration();

  TM_PWMOut_Configuration();

  while (1)
  {
    TM_Capture_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  Timer Main Routine.
  * @retval None
  ***********************************************************************************************************/
void TM_Capture_MainRoutine(void)
{
  u32 wFrequencyInteger = wFrequency / 1000;
  u32 wFrequencyFraction = wFrequency % 1000;
  u32 wDutyCycleInteger = wDutyCycle >> 16;
  u32 wDutyCycleFraction = ((wDutyCycle & 0xFFFF) * 10000) >> 16;
  printf("CH0CCR = %d, CH1CCR = %d, ", CaptureValue[0], CaptureValue[1]);
  printf("Frequency = %u.%03u Hz, ", wFrequencyInteger, wFrequencyFraction);
  printf("Duty Cycle = %u.%04u %%\r", wDutyCycleInteger, wDutyCycleFraction);
}

/*********************************************************************************************************//**
  * @brief  Configures TM to capture waveform.
  * @retval None
  ***********************************************************************************************************/
void TM_Capture_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_CAP_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  AFIO_GPxConfig(HTCFG_CAP_GPIO_ID, HTCFG_CAP_AFIO_PIN, AFIO_FUN_MCTM_GPTM);

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TM_TimeBaseInitStructure;

    TM_TimeBaseInitStructure.Prescaler = TM_CAP_PRESCAELER - 1;  // Timer clock = CK_AHB / TM_CAP_PRESCAELER
    TM_TimeBaseInitStructure.CounterReload = 0xFFFF;
    TM_TimeBaseInitStructure.RepetitionCounter = 0;
    TM_TimeBaseInitStructure.CounterMode = TM_CNT_MODE_UP;
    TM_TimeBaseInitStructure.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_CAP_PORT, &TM_TimeBaseInitStructure);
  }

  /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                   */
  TM_ClearFlag(HTCFG_CAP_PORT, TM_FLAG_UEV);

  { /* Channel n PWM input configuration                                                                    */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_CaptureInitTypeDef CapInit;

    TM_CaptureStructInit(&CapInit);
    CapInit.Channel = TM_CH_1;
    CapInit.Polarity = TM_CHP_NONINVERTED;
    CapInit.Selection = TM_CHCCS_DIRECT;
    CapInit.Prescaler = TM_CHPSC_OFF;
    #if (LIBCFG_TM_65X_66X_V1)
    CapInit.Fsampling = TM_CHFDIV_1;
    CapInit.Event = TM_CHFEV_OFF;
    #else
    CapInit.Filter = 0x00;
    #endif
    TM_PwmInputInit(HTCFG_CAP_PORT, &CapInit);
  }

  /* Set the STI trigger souece from the TI1S1, TM is configured as slave restart mode. The TM will be      */
  /* restarted on the rising edge of the TM channel 1.                                                      */
  TM_StiConfig(HTCFG_CAP_PORT, TM_TRSEL_TI1S1);
  TM_SlaveModeConfig(HTCFG_CAP_PORT, TM_SMSEL_RESTART);

  /* Set UGDIS = 1, disable the update event interrupt of the UEVG and slave mode, only counter             */
  /* overflow/underflow generations an update event interrupt function.                                     */
  TM_UEVG_IntConfig(HTCFG_CAP_PORT, DISABLE);

  /* Enable TM Channel 1 Capture and Update Event interrupts                                                */
  TM_IntConfig(HTCFG_CAP_PORT, TM_INT_CH1CC | TM_INT_UEV, ENABLE);
  NVIC_EnableIRQ(HTCFG_CAP_IRQn);

  TM_Cmd(HTCFG_CAP_PORT, ENABLE);
}

/*********************************************************************************************************//**
 * @brief   This function handles GPTM0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void HTCFG_CAP_IRQHandler(void)
{
  if (TM_GetIntStatus(HTCFG_CAP_PORT, TM_INT_UEV) != RESET)
  {
    /* Reset wFrequency and wDutyCycle                                                                      */
    TM_ClearIntPendingBit(HTCFG_CAP_PORT, TM_INT_UEV);
    wDutyCycle = 0;
    wFrequency = 0;
  }

  if (TM_GetIntStatus(HTCFG_CAP_PORT, TM_INT_CH1CC) != RESET)
  {
    /* Clear GPTM1 Capture compare interrupt pending bit                                                    */
    TM_ClearIntPendingBit(HTCFG_CAP_PORT, TM_INT_CH1CC);

    /* Get the Input Capture value                                                                          */
    CaptureValue[1] = TM_GetCaptureCompare1(HTCFG_CAP_PORT);

    if (CaptureValue[1] != 0)
    {
      CaptureValue[0] = TM_GetCaptureCompare0(HTCFG_CAP_PORT);

      /* Compute wDutyCycle and wFrequency                                                                  */
      wDutyCycle = (((u64)(CaptureValue[0] + 1) << 16) * 100) / (u64)(CaptureValue[1] + 1);
      /* We want to get achieve three decimal places, so a magnification of 1000                            */
      wFrequency = ((u64)SystemCoreClock * 1000) / ((CaptureValue[1] + 1) * TM_CAP_PRESCAELER);
    }
    else
    {
      wDutyCycle = 0;
      wFrequency = 0;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Configures TM to output PWM waveform.
  * @retval None
  ***********************************************************************************************************/
void TM_PWMOut_Configuration(void)
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

    TimeBaseInit.Prescaler = 1 - 1;                         // Timer clock = CK_AHB / 1
    TimeBaseInit.CounterReload = SystemCoreClock / TM_PWMOUT_FREQ_HZ - 1;
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
    OutInit.Compare = ((SystemCoreClock / TM_PWMOUT_FREQ_HZ) * (100 - 33)) / 100; // Duty cycle = 33 %
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
