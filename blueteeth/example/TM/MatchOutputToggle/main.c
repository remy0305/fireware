/*********************************************************************************************************//**
 * @file    TM/MatchOutputToggle/main.c
 * @version $Rev:: 6403         $
 * @date    $Date:: 2022-10-28 #$
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

/** @addtogroup MatchOutputToggle
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void TM_Configuration(void);

/* Private variables ---------------------------------------------------------------------------------------*/
u32 CH_Frequency[4];
u32 CH_DeltaCCR[4];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  TM_Configuration();

  while (1);
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
    CKCUClock.Bit.HTCFG_COMP_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  AFIO_GPxConfig(HTCFG_COMP_CH0_GPIO_ID, HTCFG_COMP_CH0_AFIO_PIN, HTCFG_COMP_AFIO_FUN);
  AFIO_GPxConfig(HTCFG_COMP_CH1_GPIO_ID, HTCFG_COMP_CH1_AFIO_PIN, HTCFG_COMP_AFIO_FUN);
  #if (LIBCFG_TM_SCTM_2CHANNEL == 0)
  AFIO_GPxConfig(HTCFG_COMP_CH2_GPIO_ID, HTCFG_COMP_CH2_AFIO_PIN, HTCFG_COMP_AFIO_FUN);
  AFIO_GPxConfig(HTCFG_COMP_CH3_GPIO_ID, HTCFG_COMP_CH3_AFIO_PIN, HTCFG_COMP_AFIO_FUN);
  #endif
  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = HTCFG_TM_PRESCALER - 1;                      // Timer clock = CK_AHB / 2000
    TimeBaseInit.CounterReload = 65535;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_COMP_PORT, &TimeBaseInit);
  }

  /* Compute the channels compare match delta value.
     Channel 0 frequency = 100 Hz
     Channel 1 frequency = 500 Hz
     Channel 2 frequency = 1000 Hz
     Channel 3 frequency = 2000 Hz
  */
  CH_Frequency[0] = 100;
  CH_DeltaCCR[0] = (SystemCoreClock / HTCFG_TM_PRESCALER) / CH_Frequency[0] / 2;
  CH_Frequency[1] = 500;
  CH_DeltaCCR[1] = (SystemCoreClock / HTCFG_TM_PRESCALER) / CH_Frequency[1] / 2;
  #if (LIBCFG_TM_SCTM_2CHANNEL == 0)
  CH_Frequency[2] = 1000;
  CH_DeltaCCR[2] = (SystemCoreClock / HTCFG_TM_PRESCALER) / CH_Frequency[2] / 2;
  CH_Frequency[3] = 2000;
  CH_DeltaCCR[3] = (SystemCoreClock / HTCFG_TM_PRESCALER) / CH_Frequency[3] / 2;
  #endif

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;

    OutInit.OutputMode = TM_OM_MATCH_TOGGLE;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.AsymmetricCompare = 0;

    OutInit.Channel = TM_CH_0;
    OutInit.Compare = CH_DeltaCCR[0];
    TM_OutputInit(HTCFG_COMP_PORT, &OutInit);

    OutInit.Channel = TM_CH_1;
    OutInit.Compare = CH_DeltaCCR[1];
    TM_OutputInit(HTCFG_COMP_PORT, &OutInit);
    #if (LIBCFG_TM_SCTM_2CHANNEL == 0)
    OutInit.Channel = TM_CH_2;
    OutInit.Compare = CH_DeltaCCR[2];
    TM_OutputInit(HTCFG_COMP_PORT, &OutInit);

    OutInit.Channel = TM_CH_3;
    OutInit.Compare = CH_DeltaCCR[3];
    TM_OutputInit(HTCFG_COMP_PORT, &OutInit);
    #endif
  }

  #if (LIBCFG_TM_SCTM_2CHANNEL)
  /* Enable TM channel 0 ~ 1 compare match interrupts                                                       */
  TM_IntConfig(HTCFG_COMP_PORT, TM_INT_CH0CC | TM_INT_CH1CC, ENABLE);
  #else
  /* Enable TM channel 0 ~ 3 compare match interrupts                                                       */
  TM_IntConfig(HTCFG_COMP_PORT, TM_INT_CH0CC | TM_INT_CH1CC | TM_INT_CH2CC | TM_INT_CH3CC, ENABLE);
  #endif
  NVIC_EnableIRQ(HTCFG_COMP_IRQn);

  /* Enable TM                                                                                              */
  TM_Cmd(HTCFG_COMP_PORT, ENABLE);
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
