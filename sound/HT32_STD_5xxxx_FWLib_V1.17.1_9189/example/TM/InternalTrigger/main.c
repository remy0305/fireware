/*********************************************************************************************************//**
 * @file    TM/InternalTrigger/main.c
 * @version $Rev:: 5262         $
 * @date    $Date:: 2021-02-05 #$
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
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup TM_Examples TM
  * @{
  */

/** @addtogroup InternalTrigger
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void MasterTimer_Configuration(void);
void SlaveTimer_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  MasterTimer_Configuration();
  SlaveTimer_Configuration();

  #if (IS_IPN_MCTM(HTCFG_TM_MASTER_IPN))
  /* MCTM channel Main Output Enable                                                                        */
  MCTM_CHMOECmd(HTCFG_MASTER_PORT, ENABLE);
  #endif

  TM_Cmd(HTCFG_MASTER_PORT, ENABLE);

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  GPTM Configuration.
  * @retval None
  ***********************************************************************************************************/
void MasterTimer_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  TM_TimeBaseInitTypeDef MasterTM_TimeBase;
  TM_OutputInitTypeDef MasterTM_OutInit;

  /* Enable peripheral's clock of AFIO and GPTM                                                             */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO                    = 1;
  CKCUClock.Bit.HTCFG_TM_MASTER_IPN     = 1;
  CKCUClock.Bit.PDMA                    = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure AFIO mode as Master Timer function.                                                          */
  AFIO_GPxConfig(HTCFG_MASTER_GPIO_ID, HTCFG_MASTER_AFIO_PIN, HTCFG_MASTER_AFIO_FUN);

  /* Master Timer Configuration                                                                             */
  MasterTM_TimeBase.CounterMode = TM_CNT_MODE_UP;
  MasterTM_TimeBase.Prescaler = SystemCoreClock/10000;       /* Timer clock = CK_AHB / Prescaler = 10 kHz   */
  MasterTM_TimeBase.CounterReload = HTCFG_MASTER_PERIOD - 1; /* Reload counter every 10 Hz (10 kHz / 1000 = 10 Hz) */
  MasterTM_TimeBase.RepetitionCounter = 0;
  MasterTM_TimeBase.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
  TM_TimeBaseInit(HTCFG_MASTER_PORT, &MasterTM_TimeBase);

  /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                   */
  TM_ClearFlag(HTCFG_MASTER_PORT, TM_FLAG_UEV);

  /* Channel n capture configuration                                                                        */
  MasterTM_OutInit.Channel = HTCFG_MASTER_CH;
  MasterTM_OutInit.OutputMode = TM_OM_MATCH_TOGGLE;        /* Toggle Mode                                   */
  MasterTM_OutInit.Control = TM_CHCTL_ENABLE;
  MasterTM_OutInit.ControlN = TM_CHCTL_DISABLE;
  MasterTM_OutInit.Polarity = TM_CHP_INVERTED;
  MasterTM_OutInit.PolarityN = TM_CHP_NONINVERTED;
  MasterTM_OutInit.IdleState = MCTM_OIS_LOW;
  MasterTM_OutInit.IdleStateN = MCTM_OIS_LOW;
  MasterTM_OutInit.AsymmetricCompare = 0;
  MasterTM_OutInit.Compare = HTCFG_MASTER_PERIOD;          /* Toggle IO once every 10 Hz (10 kHz / 1000 = 10 Hz)*/
  TM_OutputInit(HTCFG_MASTER_PORT, &MasterTM_OutInit);

  /* Enable TM Channel Update Event interrupt                                                               */
  TM_IntConfig(HTCFG_MASTER_PORT, TM_INT_UEV, ENABLE);

  NVIC_EnableIRQ(HTCFG_MASTER_IRQ);

  TM_MMSELConfig(HTCFG_MASTER_PORT, TM_MMSEL_UPDATE);
  TM_TimSyncCmd(HTCFG_MASTER_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  MCTM Configuration.This timer is used to trigger another timer.
  * @retval None
  ***********************************************************************************************************/
void SlaveTimer_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  TM_TimeBaseInitTypeDef SlaveTM_TimeBase;
  TM_OutputInitTypeDef SlaveTM_OutInit;

  /* Enable peripheral's clock of AFIO and TM                                                               */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO                   = 1;
  CKCUClock.Bit.HTCFG_TM_SLAVE_IPN     = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Configure AFIO mode as MCTM function.                                                                  */
  AFIO_GPxConfig(HTCFG_SLAVE_GPIO_ID, HTCFG_SLAVE_AFIO_PIN, HTCFG_SLAVE_AFIO_FUN);

  /* Time base configuration                                                                                */
  SlaveTM_TimeBase.CounterMode = TM_CNT_MODE_UP;
  SlaveTM_TimeBase.Prescaler = SystemCoreClock/100000;         /* Timer clock = CK_AHB / Prescaler = 100 kHz*/
  SlaveTM_TimeBase.CounterReload = HTCFG_SLAVE_PERIOD - 1;     /* Period = 100 kHz / 1000 = 100 Hz = 10 ms  */
  SlaveTM_TimeBase.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
  SlaveTM_TimeBase.RepetitionCounter = 0;
  TM_TimeBaseInit(HTCFG_SLAVE_PORT, &SlaveTM_TimeBase);

  /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                   */
  TM_ClearFlag(HTCFG_SLAVE_PORT, TM_FLAG_UEV);

  /* Channel n capture configuration                                                                        */
  SlaveTM_OutInit.Channel = HTCFG_SLAVE_CH;
  SlaveTM_OutInit.OutputMode = TM_OM_PWM2;            /* PWM2 Mode                                          */
  SlaveTM_OutInit.Control = TM_CHCTL_ENABLE;
  SlaveTM_OutInit.ControlN = TM_CHCTL_DISABLE;
  SlaveTM_OutInit.Polarity = TM_CHP_NONINVERTED;
  SlaveTM_OutInit.PolarityN = TM_CHP_NONINVERTED;
  SlaveTM_OutInit.Compare = HTCFG_SLAVE_PERIOD/3;     /* Duty cycle = 10ms/3 = 3.3ms                        */
  SlaveTM_OutInit.IdleState = MCTM_OIS_LOW;
  SlaveTM_OutInit.IdleStateN = MCTM_OIS_LOW;
  SlaveTM_OutInit.AsymmetricCompare = 0;
  TM_OutputInit(HTCFG_SLAVE_PORT, &SlaveTM_OutInit);

  /* Enable TM Channel Update Event interrupt                                                               */
  TM_IntConfig(HTCFG_SLAVE_PORT, TM_INT_UEV, ENABLE);
  NVIC_EnableIRQ(HTCFG_SLAVE_IRQ);

  /* Setting Internal Trigger                                                                               */
  TM_StiConfig(HTCFG_SLAVE_PORT, HTCFG_TM_SLAVE_TRSEL_ITI);
  TM_SlaveModeConfig(HTCFG_SLAVE_PORT, TM_SMSEL_TRIGGER);

  #if (IS_IPN_MCTM(HTCFG_TM_SLAVE_IPN))
  /* MCTM channel Main Output Enable                                                                        */
  MCTM_CHMOECmd(HTCFG_SLAVE_PORT, ENABLE);
  #endif
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
