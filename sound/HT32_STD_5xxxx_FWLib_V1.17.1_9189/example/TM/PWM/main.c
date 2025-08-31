/*********************************************************************************************************//**
 * @file    TM/PWM/main.c
 * @version $Rev:: 6712         $
 * @date    $Date:: 2023-02-03 #$
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
#include "pwm.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup TM_Examples TM
  * @{
  */

/** @addtogroup PWM
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void Delay(u32 uLoop);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  PWM_Init();

  PWM_UpdateDuty(PWM_CH0, PWM_DUTY_50);
  PWM_UpdateDuty(PWM_CH1, PWM_DUTY_25);
  PWM_Cmd(ENABLE);

  Delay(5000);

  PWM_UpdateDuty(PWM_CH0, PWM_DUTY_0);
  PWM_UpdateDuty(PWM_CH1, PWM_DUTY_75);

  Delay(5000);

  PWM_Cmd(DISABLE);

  Delay(5000);

  PWM_SetFreq(PWM_FREQ_12K);
  PWM_UpdateDuty(PWM_CH0, PWM_FREQ_12K * 0.25);
  PWM_UpdateDuty(PWM_CH1, PWM_FREQ_12K * 0.75);
  PWM_Cmd(ENABLE);

  while (1);
}

/*********************************************************************************************************//**
  * @brief  Dealy loop.
  * @param  uLoop: Delay loop count
  * @retval None
  ***********************************************************************************************************/
void Delay(u32 uLoop)
{
  vu32 i;
  for (i = 0; i < uLoop; i++);
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
