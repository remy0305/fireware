/*********************************************************************************************************//**
 * @file    TM/PWM_Buzzer/main.c
 * @version $Rev:: 5225         $
 * @date    $Date:: 2021-02-01 #$
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

#include "buzzer_pwm.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup TM_Examples TM
  * @{
  */

/** @addtogroup PWM_Buzzer
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void Buzzer_Fun1(void);
void Buzzer_Fun2(void);
void Buzzer_PlayTable(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u16 gBee_Scale[] =
{
    0,
  262,  294,  330,  349,  392,  440,  494,
  523,  587,  659,  698,  784,  880,  988,
 1046, 1175, 1318, 1397, 1568, 1760, 1976
};

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  Buzzer_Fun1();

  Buzzer_Fun2();

  Buzzer_Init(0);

  while (1)
  {
    Buzzer_PlayTable();
  }
}

/*********************************************************************************************************//**
  * @brief  Buzzer function 1.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Fun1(void)
{
  /* Bee 4 times, 3 kHz, active 50 ms, inactive 50 ms                                                       */
  Buzzer_Init(0);
  Buzzer_Start(4, 3000, 50, 50);
  while (Buzzer_IsFinish() == FALSE);
}

/*********************************************************************************************************//**
  * @brief  Buzzer function 2.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_Fun2(void)
{
  /* Bee 2 times, 800 Hz, active 1000 ms, inactive 500 ms                                                   */
  Buzzer_Init(0);
  Buzzer_Start(2, 800, 1000, 500);
  while (Buzzer_IsFinish() == FALSE);
}

/*********************************************************************************************************//**
  * @brief  Buzzer play table function.
  * @retval None
  ***********************************************************************************************************/
void Buzzer_PlayTable(void)
{
  static u32 i = 1;

  /* Bee 1 times, gBee_Scale[i] Hz, active 250 ms, inactive 250 ms                                          */
  if (Buzzer_IsFinish() == TRUE && i <= 21)
  {
    Buzzer_Start(1, gBee_Scale[i], 250, 250);
    i++;
  }
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
