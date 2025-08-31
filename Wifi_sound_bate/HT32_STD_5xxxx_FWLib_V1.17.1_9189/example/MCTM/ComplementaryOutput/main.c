/*********************************************************************************************************//**
 * @file    MCTM/ComplementaryOutput/main.c
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup MCTM_Examples MCTM
  * @{
  */

/** @addtogroup ComplementaryOutput
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void MCTM_Configuration(void);

/* Private variables ---------------------------------------------------------------------------------------*/

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  MCTM_Configuration();

  while (1);
}

/*********************************************************************************************************//**
  * @brief  Configures MCTM to output PWM.
  * @retval None
  ***********************************************************************************************************/
void MCTM_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  TM_TimeBaseInitTypeDef MCTM_TimeBaseInitStructure;
  TM_OutputInitTypeDef MCTM_OutputInitStructure;
  MCTM_CHBRKCTRInitTypeDef MCTM_CHBRKCTRInitStructure;

  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO                                = 1;
  CKCUClock.Bit.HTCFG_MCTM_BREAK_GPIO_CLOCK_ID      = 1;
  CKCUClock.Bit.MCTM0                               = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure MCTM Channel 0 output pin                                                                    */
  AFIO_GPxConfig(HTCFG_MCTM_CH0_GPIO_ID, HTCFG_MCTM_CH0_AFIO_PIN, AFIO_FUN_MCTM_GPTM);
  AFIO_GPxConfig(HTCFG_MCTM_CH0N_GPIO_ID, HTCFG_MCTM_CH0N_AFIO_PIN, AFIO_FUN_MCTM_GPTM);
  /* Configure MCTM Channel 1 output pin                                                                    */
  AFIO_GPxConfig(HTCFG_MCTM_CH1_GPIO_ID, HTCFG_MCTM_CH1_AFIO_PIN, AFIO_FUN_MCTM_GPTM);
  AFIO_GPxConfig(HTCFG_MCTM_CH1N_GPIO_ID, HTCFG_MCTM_CH1N_AFIO_PIN, AFIO_FUN_MCTM_GPTM);
  /* Configure MCTM Channel 2 output pin                                                                    */
  AFIO_GPxConfig(HTCFG_MCTM_CH2_GPIO_ID, HTCFG_MCTM_CH2_AFIO_PIN, AFIO_FUN_MCTM_GPTM);
  AFIO_GPxConfig(HTCFG_MCTM_CH2N_GPIO_ID, HTCFG_MCTM_CH2N_AFIO_PIN, AFIO_FUN_MCTM_GPTM);
  /* Configure MCTM Break pin                                                                               */
  AFIO_GPxConfig(HTCFG_MCTM_BREAK_GPIO_ID, HTCFG_MCTM_BREAK_AFIO_PIN, AFIO_FUN_MCTM_GPTM);

  /* Configure MCTM Break pin pull resistor to avoid floating input                                         */
  GPIO_PullResistorConfig(HTCFG_MCTM_BREAK_GPIO_PORT, HTCFG_MCTM_BREAK_AFIO_PIN, GPIO_PR_UP);

  /* MCTM Time Base configuration                                                                           */
  MCTM_TimeBaseInitStructure.CounterReload = HTCFG_MCTM_RELOAD - 1;
  MCTM_TimeBaseInitStructure.Prescaler = 0;
  MCTM_TimeBaseInitStructure.RepetitionCounter = 0;
  MCTM_TimeBaseInitStructure.CounterMode = TM_CNT_MODE_UP;
  MCTM_TimeBaseInitStructure.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
  TM_TimeBaseInit(HT_MCTM0, &MCTM_TimeBaseInitStructure);

  /* MCTM Channel 0, 1, 2 output configuration                                                              */
  MCTM_OutputInitStructure.Channel = TM_CH_0;
  MCTM_OutputInitStructure.OutputMode = TM_OM_PWM1;
  MCTM_OutputInitStructure.Control = TM_CHCTL_ENABLE;
  MCTM_OutputInitStructure.ControlN = TM_CHCTL_ENABLE;
  MCTM_OutputInitStructure.Polarity = TM_CHP_NONINVERTED;
  MCTM_OutputInitStructure.PolarityN = TM_CHP_NONINVERTED;
  MCTM_OutputInitStructure.IdleState = MCTM_OIS_LOW;
  MCTM_OutputInitStructure.IdleStateN = MCTM_OIS_HIGH;
  MCTM_OutputInitStructure.Compare = HTCFG_MCTM_RELOAD * 3 / 4;
  MCTM_OutputInitStructure.AsymmetricCompare = 0;
  TM_OutputInit(HT_MCTM0, &MCTM_OutputInitStructure);

  MCTM_OutputInitStructure.Channel = TM_CH_1;
  MCTM_OutputInitStructure.Compare = HTCFG_MCTM_RELOAD * 1 / 2;
  TM_OutputInit(HT_MCTM0, &MCTM_OutputInitStructure);

  MCTM_OutputInitStructure.Channel = TM_CH_2;
  MCTM_OutputInitStructure.Compare = HTCFG_MCTM_RELOAD * 1 / 4;
  TM_OutputInit(HT_MCTM0, &MCTM_OutputInitStructure);

  /* MCTM Off State, lock, Break, Automatic Output enable, dead time configuration                          */
  MCTM_CHBRKCTRInitStructure.OSSRState = MCTM_OSSR_STATE_ENABLE;
  MCTM_CHBRKCTRInitStructure.OSSIState = MCTM_OSSI_STATE_ENABLE;
  MCTM_CHBRKCTRInitStructure.LockLevel = MCTM_LOCK_LEVEL_2;
  MCTM_CHBRKCTRInitStructure.Break0 = MCTM_BREAK_ENABLE;
  MCTM_CHBRKCTRInitStructure.Break0Polarity = MCTM_BREAK_POLARITY_LOW;
  MCTM_CHBRKCTRInitStructure.AutomaticOutput = MCTM_CHAOE_ENABLE;
  MCTM_CHBRKCTRInitStructure.DeadTime = HTCFG_MCTM_DEAD_TIME;
  MCTM_CHBRKCTRInitStructure.BreakFilter = 0;
  MCTM_CHBRKCTRConfig(HT_MCTM0, &MCTM_CHBRKCTRInitStructure);

  /* MCTM counter enable                                                                                    */
  TM_Cmd(HT_MCTM0, ENABLE);

  /* MCTM Channel Main Output enable                                                                        */
  MCTM_CHMOECmd(HT_MCTM0, ENABLE);
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
