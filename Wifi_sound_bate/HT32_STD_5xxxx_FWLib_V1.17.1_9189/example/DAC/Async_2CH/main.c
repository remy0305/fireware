/*********************************************************************************************************//**
 * @file    DAC/Async_2CH/main.c
 * @version $Rev:: 7081         $
 * @date    $Date:: 2023-08-01 #$
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

/** @addtogroup DAC_example DAC
  * @{
  */

/** @addtogroup Async_2CH
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
#define CHANNEL0_OUT_MILLI_V        (1650)       /* 1.65V                                                   */
#define CHANNEL1_OUT_MILLI_V        (1650)       /* 1.65V                                                   */

/* Private constants ---------------------------------------------------------------------------------------*/
#define CHANNEL0_CONV_DATA          ((CHANNEL0_OUT_MILLI_V * 4095)/3300)    /* CH0 use 12-bit scaler        */
#define CHANNEL1_CONV_DATA          ((CHANNEL1_OUT_MILLI_V * 255)/3300)     /* CH1 use 8-bit scaler         */

/* Private function prototypes -----------------------------------------------------------------------------*/
void DAC_Configuration(void);
void DAC0_CH0_Config(void);
void DAC0_CH1_Config(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  DAC_Configuration();

  /* DAC0 channel 0, 1 conversion start                                                                     */
  DAC_Cmd(HT_DAC0, DAC_CH0, ENABLE);
  DAC_Cmd(HT_DAC0, DAC_CH1, ENABLE);

  while (1);
}
/*********************************************************************************************************//**
  * @brief  DAC Configuration.
  * @retval None
  ***********************************************************************************************************/
void DAC_Configuration(void)
{
  {
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  /* Enable peripherals clocks of DAC, AFIO                                                                 */
  CKCUClock.Bit.AFIO       = 1;
  CKCUClock.Bit.DAC0       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Config DAC pins function                                                                               */
  AFIO_GPxConfig(HTCFG_DAC0_CH0_AFIO_PORT, HTCFG_DAC0_CH0_AFIO_PIN, AFIO_FUN_DAC0);
  AFIO_GPxConfig(HTCFG_DAC0_CH1_AFIO_PORT, HTCFG_DAC0_CH1_AFIO_PIN, AFIO_FUN_DAC0);

  /* Configure the DAC Asynchronous conversion mode                                                         */
  DAC_ModeConfig(HT_DAC0, ASYNC_MODE);

  /* Configure the DAC0 channel 0 as a 12-bit scaler                                                        */
  DAC0_CH0_Config();

  /* Configure the DAC0 channel 1 as a 8-bit scaler                                                         */
  DAC0_CH1_Config();
}

/*********************************************************************************************************//**
  * @brief  Configure the DAC as a 12-bit scaler.
  * @retval None
  ***********************************************************************************************************/
void DAC0_CH0_Config(void)
{
  /* Configure the VDDA to DAC channel reference voltage                                                    */
  DAC_ReferenceConfig(HT_DAC0, DAC_CH0, DAC_REFERENCE_VDDA);

  /* Configure the 12-bit resolution to DAC channel                                                         */
  DAC_ResolutionConfig(HT_DAC0, DAC_CH0, DAC_RESOLUTION_12BIT);

  /* Provide DAC channel output with driver                                                                 */
  DAC_OutBufCmd(HT_DAC0, DAC_CH0, ENABLE);

  /* Set the data holding register value                                                                    */
  DAC_SetData(HT_DAC0, DAC_CH0, CHANNEL0_CONV_DATA);
}

/*********************************************************************************************************//**
  * @brief  Configure the DAC as a 8-bit scaler.
  * @retval None
  ***********************************************************************************************************/
void DAC0_CH1_Config(void)
{
  /* Configure the VDDA to DAC channel reference voltage                                                    */
  DAC_ReferenceConfig(HT_DAC0, DAC_CH1, DAC_REFERENCE_VDDA);

  /* Configure the 8-bit resolution to DAC channel                                                          */
  DAC_ResolutionConfig(HT_DAC0, DAC_CH1, DAC_RESOLUTION_8BIT);

  /* Provide DAC channel output with driver                                                                 */
  DAC_OutBufCmd(HT_DAC0, DAC_CH1, ENABLE);

  /* Set the data holding register value                                                                    */
  DAC_SetData(HT_DAC0, DAC_CH1, CHANNEL1_CONV_DATA);
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
