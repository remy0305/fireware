/*********************************************************************************************************//**
 * @file    TM/SinglePulseMode/main.c
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

/** @addtogroup SinglePulseMode
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void TM_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  /* Configure KEY1 used to start TM                                                                        */
  HT32F_DVB_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

  TM_Configuration();

  /* Waiting for KEY1 pressed to start the TM                                                               */
  while (HT32F_DVB_PBGetState(BUTTON_KEY1));
  TM_Cmd(HTCFG_PULSE_PORT, ENABLE);

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the Timer.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_PULSE_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  AFIO_GPxConfig(HTCFG_PULSE_GPIO_ID, HTCFG_PULSE_AFIO_PIN, HTCFG_PULSE_AFIO_FUN);

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = HTCFG_TIMER_PRESCALER - 1;        // Timer clock = CK_AHB / HTCFG_TIMER_PRESCALER

    // Counter-Reload value = (Timer clock / TM_FREQ_HZ - 1), must less than 0xFFFF.
    TimeBaseInit.CounterReload = ((HTCFG_PULSE_SYS_CLK / HTCFG_TIMER_PRESCALER) / HTCFG_PULSE_FREQ_HZ) - 1;

    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_PULSE_PORT, &TimeBaseInit);
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;

    OutInit.Channel = HTCFG_PULSE_CH;
    OutInit.OutputMode = TM_OM_PWM2;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = ((HTCFG_PULSE_SYS_CLK / HTCFG_TIMER_PRESCALER) / HTCFG_PULSE_FREQ_HZ) * 0.75;
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HTCFG_PULSE_PORT, &OutInit);
  }

  /* Enable TM single pulse mode                                                                            */
  TM_SinglePulseModeCmd(HTCFG_PULSE_PORT, ENABLE);
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
