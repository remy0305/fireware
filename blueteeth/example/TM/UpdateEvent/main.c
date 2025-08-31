/*********************************************************************************************************//**
 * @file    TM/UpdateEvent/main.c
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

/** @addtogroup UpdateEvent
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define TM_FREQ_HZ           (1000)
#define TM_TIME_DELAY        (500)

/* Private function prototypes -----------------------------------------------------------------------------*/
void TM_Configuration(void);
void TM_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
vu32 gIsUpdateEvent = FALSE;
s32 gTimeCount;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);

  TM_Configuration();

  gTimeCount = TM_TIME_DELAY;

  while (1)
  {
    TM_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  Timer Main Routine.
  * @retval None
  ***********************************************************************************************************/
void TM_MainRoutine(void)
{
  if (gIsUpdateEvent == TRUE)
  {
    gIsUpdateEvent = FALSE;
    if (gTimeCount != 0)
    {
      gTimeCount--;
      if (gTimeCount == 0)
      {
        HT32F_DVB_LEDToggle(HT_LED1);
        gTimeCount = TM_TIME_DELAY;
      }
    }
  }
}

/*********************************************************************************************************//**
  * @brief   Configures TM for delay function.
  * @retval  None
  * @details Configuration as "TM_FREQ_HZ" Hz.
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  #if 0 // Use following function to configure the IP clock speed.
  CKCU_SetPeripPrescaler(CKCU_PCLK_GPTM0, CKCU_APBCLKPRE_DIV2);
  #endif

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.HTCFG_TM_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;
    TimeBaseInit.Prescaler = HTCFG_TIMER_PRESCALER - 1;         // Timer clock = CK_AHB / HTCFG_TIMER_PRESCALER

    // Counter-Reload value = (Timer clock / TM_FREQ_HZ - 1), must less than 0xFFFF.
    TimeBaseInit.CounterReload = (HTCFG_PULSE_SYS_CLK/HTCFG_TIMER_PRESCALER) / TM_FREQ_HZ - 1;

    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_TM_PORT, &TimeBaseInit);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    TM_ClearFlag(HTCFG_TM_PORT, TM_FLAG_UEV);
  }

  /* Enable Update Event interrupt                                                                          */
  NVIC_EnableIRQ(HTCFG_TM_IRQn);
  TM_IntConfig(HTCFG_TM_PORT, TM_INT_UEV, ENABLE);

  TM_Cmd(HTCFG_TM_PORT, ENABLE);
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
