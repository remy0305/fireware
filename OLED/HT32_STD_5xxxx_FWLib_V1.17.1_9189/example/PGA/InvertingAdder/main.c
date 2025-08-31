/*********************************************************************************************************//**
 * @file    PGA/InvertingAdder/main.c
 * @version $Rev:: 8167         $
 * @date    $Date:: 2024-09-23 #$
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

/** @addtogroup PGA_Examples PGA
  * @{
  */

/** @addtogroup InvertingAdder
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void PGA_Configuration(void);
ErrStatus PGA_InputCalibration(HT_PGA0_X_TypeDef* HT_PGAn, PGA_CALIBRATION_INPUT_Enum PGA_INPUT_x);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);

  Time_Init();

  PGA_SetUnProtectKey(PGA_UNPROTECT_KEY);

  PGA_Configuration();

  PGA_SetUnProtectKey(0x0);

  PGA_Cmd(HTCFG_PGA_PORT, DISABLE); // Not work since the PGA is protected after "PGA_SetUnProtectKey(0x0)".

  while(1){};
}

/*********************************************************************************************************//**
  * @brief  PGA configuration.
  * @retval None
  ***********************************************************************************************************/
void PGA_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    #if defined(USE_HT32F65233)
    CKCUClock.Bit.OPA_PGA = 1;
    #else
    CKCUClock.Bit.PGA = 1;
    #endif
    CKCUClock.Bit.AFIO = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as PGA function                                                                    */
  AFIO_GPxConfig(HTCFG_PGA_POS_GPIO_ID, HTCFG_PGA_POS_AFIO_PIN, AFIO_FUN_PGA);
  AFIO_GPxConfig(HTCFG_PGA_NEG_GPIO_ID, HTCFG_PGA_NEG_AFIO_PIN, AFIO_FUN_PGA);
  AFIO_GPxConfig(HTCFG_PGA_OUT_GPIO_ID, HTCFG_PGA_OUT_AFIO_PIN, AFIO_FUN_PGA);

  HT32F_DVB_LEDOn(HT_LED1); // Before calibration, turn on LED1

  if(!PGA_InputCalibration(HTCFG_PGA_PORT, PGA_CALIBRATION_INPUT_POSITIVE))
  {
    while(1){};
  }

  HT32F_DVB_LEDOff(HT_LED1); //Calibration complete, turn off LED1

  /* Set the Inverting Adder Mode                                                                           */
  PGA_SetModeInvertingAdder(HTCFG_PGA_PORT, PGA_GAIN_LEVEL_0);
  /* Enable PGA                                                                                             */
  PGA_Cmd(HTCFG_PGA_PORT, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Execute the input offset calibration of the specified HT_PGAn.
 * @param HT_PGAn: where HT_PGAn is the selected PGA from the PGA peripherals.
 * @param PGA_INPUT_x: where PGA_INPUT_x is the calibration reference.
 *   This parameter can be one of the following values:
 *     @arg PGA_INPUT_NEGATIVE
 *     @arg PGA_INPUT_POSITIVE
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus PGA_InputCalibration(HT_PGA0_X_TypeDef* HT_PGAn, PGA_CALIBRATION_INPUT_Enum PGA_INPUT_x)
{
  u8  PGAnO_Buffer;
  u32 PGA_VOS1;
  u32 PGA_VOS2;

  PGA_CalibrationCmd(HT_PGAn,ENABLE);
  PGA_SetCalibrationInput(HT_PGAn,PGA_INPUT_x);
  PGA_Cmd(HT_PGAn,ENABLE);

  PGA_SetCalibrationValue(HT_PGAn,0);
  while(PGA_ReadOutputBit(HT_PGAn) != 0){}
  Time_Delay(TIME_US2TICK(500));
  PGAnO_Buffer = PGA_ReadOutputBit(HT_PGAn);

  PGA_VOS1 = 0;
  while(PGA_ReadOutputBit(HT_PGAn) == PGAnO_Buffer)
  {
    PGA_VOS1 += 1;
    if(PGA_VOS1 == 0x20)
    {
      return ERROR;
    }

    PGA_SetCalibrationValue(HT_PGAn,PGA_VOS1);
    Time_Delay(TIME_US2TICK(100));
  }

  PGA_SetCalibrationValue(HT_PGAn,0x1F);
  Time_Delay(TIME_US2TICK(500));
  PGAnO_Buffer = PGA_ReadOutputBit(HT_PGAn);;

  PGA_VOS2 = 0x1F;
  while(PGA_ReadOutputBit(HT_PGAn) == PGAnO_Buffer)
  {
    if(PGA_VOS2 == 0)
    {
      return ERROR;
    }
    PGA_VOS2 -= 1;

    PGA_SetCalibrationValue(HT_PGAn,PGA_VOS2);
    Time_Delay(TIME_US2TICK(100));
  }

  PGA_SetCalibrationValue(HT_PGAn,(PGA_VOS1 + PGA_VOS2) >> 1);
  PGA_CalibrationCmd(HT_PGAn,DISABLE);
  return SUCCESS;
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
