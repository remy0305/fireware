/*********************************************************************************************************//**
 * @file    DAC/Sync_12bit_2CH/main.c
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

/** @addtogroup Sync_12bit_2CH
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
#define CHANNEL0_OUT_MILLI_V        (1650)       /* 1.65V                                                   */
#define CHANNEL1_OUT_MILLI_V        (1650)       /* 1.65V                                                   */

/* Private constants ---------------------------------------------------------------------------------------*/
/* DAC use Synchronous mode 12-bit resolution,
   DAC1 data is located at DAC0DHR[27:16], DAC0 data is located at DAC0DHR[11:0]
   if DAC use Synchronous mode 8-bit resolution,
   DAC1 data is located at DAC0DHR[15:8], DAC0 data is located at DAC0DHR[7:0]                              */
#define CHANNEL0_CONV_DATA          (CHANNEL0_OUT_MILLI_V * 4095 / 3300)
#define CHANNEL1_CONV_DATA          (CHANNEL1_OUT_MILLI_V * 4095 / 3300)
#define CH_CONV_DATA_ALL            ((CHANNEL1_CONV_DATA << 16) | (CHANNEL0_CONV_DATA))

/* Private function prototypes -----------------------------------------------------------------------------*/
void DAC_Configuration(void);

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

  /* Set the DAC0 channel 0 holding value                                                                   */
  DAC_SetData(HT_DAC0, DAC_CH0, CH_CONV_DATA_ALL);

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

  /* Configure the DAC Synchronous conversion mode                                                          */
  DAC_ModeConfig(HT_DAC0, SYNC_MODE);

  /* Configure DAC0 channel 0                                                                               */
  /* Configure the VDDA to DAC channel reference voltage                                                    */
  DAC_ReferenceConfig(HT_DAC0, DAC_CH0, DAC_REFERENCE_VDDA);

  /* Configure the 12-bit resolution to DAC channel                                                         */
  DAC_ResolutionConfig(HT_DAC0, DAC_CH0, DAC_RESOLUTION_12BIT);

  /* Provide DAC channel output with driver                                                                 */
  DAC_OutBufCmd(HT_DAC0, DAC_CH0, ENABLE);


  /* Configure DAC0 channel 1                                                                               */
  /* Configure the VDDA to DAC channel reference voltage                                                    */
  DAC_ReferenceConfig(HT_DAC0, DAC_CH1, DAC_REFERENCE_VDDA);

  /* Provide DAC channel output with driver                                                                 */
  DAC_OutBufCmd(HT_DAC0, DAC_CH1, ENABLE);
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
