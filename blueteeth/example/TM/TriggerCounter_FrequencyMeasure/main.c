/*********************************************************************************************************//**
 * @file    TM/TriggerCounter_FrequencyMeasure/main.c
 * @version $Rev:: 8389         $
 * @date    $Date:: 2025-02-13 #$
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

/** @addtogroup TriggerCounter_FrequencyMeasure
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define HTCFG_SYSTICK_TIME_BASE           (LIBCFG_MAX_SPEED * 0.1)     /* 100 ms                            */

/* Private function prototypes -----------------------------------------------------------------------------*/
void TM_Configuration(void);
void TM_MainRoutine(void);
void SysTick_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();           /* Retarget Related configuration                                     */

  TM_Configuration();

  SysTick_Configuration();

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

    TimeBaseInit.Prescaler = 1 - 1;
    TimeBaseInit.CounterReload = 0xFFFF;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_CAP_PORT, &TimeBaseInit);
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

  /* Slave Trigger Input selection                                                                          */
  TM_StiConfig(HTCFG_CAP_PORT, TM_TRSEL_TI0S0);

  /* Slave Mode selection: Trigger Mode                                                                     */
  TM_SlaveModeConfig(HTCFG_CAP_PORT, TM_SMSEL_STIED);

  /* Enable TM Channel Trigger Event and Update Event interrupts                                            */
  TM_IntConfig(HTCFG_CAP_PORT, TM_INT_TEV | TM_INT_UEV, ENABLE);
  NVIC_EnableIRQ(HTCFG_CAP_IRQn);

  TM_Cmd(HTCFG_CAP_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure SysTick.
  * @retval None
  ***********************************************************************************************************/
void SysTick_Configuration(void)
{
  SYSTICK_ClockSourceConfig(SYSTICK_SRC_FCLK);
  SYSTICK_SetReloadValue(HTCFG_SYSTICK_TIME_BASE);
  SYSTICK_IntConfig(ENABLE);
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
