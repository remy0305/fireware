/*********************************************************************************************************//**
 * @file    TM/PWMOut_PDMA_4CH/main.c
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

/** @addtogroup TM_Examples TM
  * @{
  */

/** @addtogroup PWMOut_PDMA_4CH
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define PWM_FREQU   (800000)
#define LOW_PERIOD  (0.4)
#define HIGH_PERIOD (0.6)

/* Private function prototypes -----------------------------------------------------------------------------*/
void TM_InitPWMData(void);

void PDMA_Configuration(void);
void TM_Configuration(void);

/* Private variables ---------------------------------------------------------------------------------------*/
u32 CCR_Buffer[4 * 3];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  TM_InitPWMData();

  PDMA_Configuration();

  TM_Configuration();

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Init data PWM data for compare match register.
  * @retval None
  ***********************************************************************************************************/
void TM_InitPWMData(void)
{
  u32 uCounterReload;

  uCounterReload = SystemCoreClock / PWM_FREQU;

  CCR_Buffer[0] = (u32)(uCounterReload * LOW_PERIOD);
  CCR_Buffer[1] = (u32)(uCounterReload * HIGH_PERIOD);
  CCR_Buffer[2] = (u32)(uCounterReload * LOW_PERIOD);
  CCR_Buffer[3] = (u32)(uCounterReload * HIGH_PERIOD);

  CCR_Buffer[4] = (u32)(uCounterReload * HIGH_PERIOD);
  CCR_Buffer[5] = (u32)(uCounterReload * LOW_PERIOD);
  CCR_Buffer[6] = (u32)(uCounterReload * HIGH_PERIOD);
  CCR_Buffer[7] = (u32)(uCounterReload * LOW_PERIOD);

  CCR_Buffer[8]  = (u32)(uCounterReload * HIGH_PERIOD);
  CCR_Buffer[9]  = (u32)(uCounterReload * HIGH_PERIOD);
  CCR_Buffer[10] = (u32)(uCounterReload * LOW_PERIOD);
  CCR_Buffer[11] = (u32)(uCounterReload * LOW_PERIOD);
}

/*********************************************************************************************************//**
  * @brief  Configure the PDMA.
  * @retval None
  ***********************************************************************************************************/
void PDMA_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.PDMA = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  {
    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;

    /* PDMA configuration                                                                                   */
    PDMACH_InitStructure.PDMACH_SrcAddr = (u32)CCR_Buffer;
    PDMACH_InitStructure.PDMACH_DstAddr = (u32)&(HTCFG_PWM_PORT->CH0CCR);
    PDMACH_InitStructure.PDMACH_BlkCnt = 3;
    PDMACH_InitStructure.PDMACH_BlkLen = 4;
    PDMACH_InitStructure.PDMACH_DataSize = WIDTH_32BIT;
    PDMACH_InitStructure.PDMACH_Priority = VH_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_CIR_INC | AUTO_RELOAD;
    PDMA_Config(HTCFG_PDMA_CH, &PDMACH_InitStructure);
  }

  PDMA_EnaCmd(HTCFG_PDMA_CH, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Timer configuration.
  * @retval None
  ***********************************************************************************************************/
void TM_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.HTCFG_PWM_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as TM function                                                                     */
  AFIO_GPxConfig(HTCFG_PWM0_GPIO_ID, HTCFG_PWM0_AFIO_PIN, HTCFG_PWM0_AFIO_FUN);
  AFIO_GPxConfig(HTCFG_PWM1_GPIO_ID, HTCFG_PWM1_AFIO_PIN, HTCFG_PWM1_AFIO_FUN);
  AFIO_GPxConfig(HTCFG_PWM2_GPIO_ID, HTCFG_PWM2_AFIO_PIN, HTCFG_PWM2_AFIO_FUN);
  AFIO_GPxConfig(HTCFG_PWM3_GPIO_ID, HTCFG_PWM3_AFIO_PIN, HTCFG_PWM3_AFIO_FUN);

  { /* Time base configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_TimeBaseInitTypeDef TimeBaseInit;

    TimeBaseInit.Prescaler = 1 - 1;                               // Timer clock = CK_AHB / 1
    TimeBaseInit.CounterReload = (SystemCoreClock / PWM_FREQU) - 1;
    TimeBaseInit.RepetitionCounter = 0;
    TimeBaseInit.CounterMode = TM_CNT_MODE_UP;
    TimeBaseInit.PSCReloadTime = TM_PSC_RLD_IMMEDIATE;
    TM_TimeBaseInit(HTCFG_PWM_PORT, &TimeBaseInit);

    /* Clear Update Event Interrupt flag since the "TM_TimeBaseInit()" writes the UEV1G bit                 */
    TM_ClearFlag(HTCFG_PWM_PORT, TM_FLAG_UEV);
  }

  { /* Channel n output configuration                                                                       */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    TM_OutputInitTypeDef OutInit;

    OutInit.Channel = HTCFG_PWM0_CH;
    OutInit.OutputMode = TM_OM_PWM1;
    OutInit.Control = TM_CHCTL_ENABLE;
    OutInit.ControlN = TM_CHCTL_DISABLE;
    OutInit.Polarity = TM_CHP_NONINVERTED;
    OutInit.PolarityN = TM_CHP_NONINVERTED;
    OutInit.IdleState = MCTM_OIS_LOW;
    OutInit.IdleStateN = MCTM_OIS_HIGH;
    OutInit.Compare = 0x0;                                    // PWM duty = 0 %
    OutInit.AsymmetricCompare = 0;
    TM_OutputInit(HTCFG_PWM_PORT, &OutInit);

    OutInit.Channel = HTCFG_PWM1_CH;
    TM_OutputInit(HTCFG_PWM_PORT, &OutInit);

    OutInit.Channel = HTCFG_PWM2_CH;
    TM_OutputInit(HTCFG_PWM_PORT, &OutInit);

    OutInit.Channel = HTCFG_PWM3_CH;
    TM_OutputInit(HTCFG_PWM_PORT, &OutInit);

    TM_CHCCRPreloadConfig(HTCFG_PWM_PORT, TM_CH_0, ENABLE);
    TM_CHCCRPreloadConfig(HTCFG_PWM_PORT, TM_CH_1, ENABLE);
    TM_CHCCRPreloadConfig(HTCFG_PWM_PORT, TM_CH_2, ENABLE);
    TM_CHCCRPreloadConfig(HTCFG_PWM_PORT, TM_CH_3, ENABLE);
  }

  #if (IS_IPN_MCTM(HTCFG_PWM_IPN))
  /* MCTM channel Main Output Enable                                                                        */
  MCTM_CHMOECmd(HTCFG_PWM_PORT, ENABLE);
  #endif

  /* MCTM/GPTM Update Event PDMA request enable                                                             */
  TM_PDMAConfig(HTCFG_PWM_PORT, TM_PDMA_UEV, ENABLE);

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
