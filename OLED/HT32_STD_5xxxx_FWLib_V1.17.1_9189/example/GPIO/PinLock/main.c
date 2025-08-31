/*********************************************************************************************************//**
 * @file    GPIO/PinLock/main.c
 * @version $Rev:: 7314         $
 * @date    $Date:: 2023-10-24 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup GPIO_Examples GPIO
  * @{
  */

/** @addtogroup PinLock
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void GPIO_Configuration(void);
void GPIO_LockStatus(void);
void GPIO_LockPinTest(void);
void GPIO_OtherPinTest(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  GPIO_Configuration();

  GPIO_PinLock(HT_GPIOA, GPIO_PIN_1);

  GPIO_LockStatus();

  GPIO_LockPinTest();

  GPIO_OtherPinTest();

  while (1);
}

/*********************************************************************************************************//**
  * @brief  Configure the GPIO as below.
            AFIO Mode             : GPIO Mode
            Default Value         : RESET
            Pull Resistor         : Pull-DISABLE
            Output Driving Current: 8mA
            Direction             : Output
  * @retval None
  ***********************************************************************************************************/
void GPIO_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.PA = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Configure GPIO as output mode                                                                        */

    /* Configure AFIO mode as GPIO                                                                          */
    AFIO_GPxConfig(GPIO_PA, AFIO_PIN_1, AFIO_FUN_GPIO);
    AFIO_GPxConfig(GPIO_PA, AFIO_PIN_2, AFIO_FUN_GPIO);

    /* Default value RESET/SET                                                                              */
    GPIO_WriteOutBits(HT_GPIOA, GPIO_PIN_1, RESET);
    GPIO_WriteOutBits(HT_GPIOA, GPIO_PIN_2, RESET);

    /* Configure GPIO pull resistor                                                                         */
    GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_1, GPIO_PR_DISABLE);
    GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_2, GPIO_PR_DISABLE);

    /* Configure GPIO Output Driving Current                                                                */
    GPIO_DriveConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DV_8MA);
    GPIO_DriveConfig(HT_GPIOA, GPIO_PIN_2, GPIO_DV_8MA);

    /* Configure GPIO direction as output                                                                   */
    GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_OUT);
    GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_2, GPIO_DIR_OUT);
  }
}

/*********************************************************************************************************//**
  * @brief  Determine the lock state of specified GPIO port and Pin.
            GPIO Port A is Locked.
            GPIO Port A Pin 1 is Locked.
            GPIO Port A Pin 2 is unLocked.
  * @retval None
  ***********************************************************************************************************/
void GPIO_LockStatus(void)
{
  /* Port A Lock Status                                                                                     */
  if (GPIO_IsPortLocked(HT_GPIOA) == TRUE)
  {
    printf("GPIO Port A is Locked. \r\n");
  }
  else
  {
    printf("GPIO Port A is unLocked. \r\n");
  }

  printf("===============================\r\n");

  /* Port A Pin 1 & 2 Lock Status                                                                           */
  if (GPIO_IsPinLocked(HT_GPIOA, GPIO_PIN_1) == TRUE)
  {
    printf("GPIO Port A Pin 1 is Locked. \r\n");
  }
  else
  {
    printf("GPIO Port A Pin 1 is unLocked. \r\n");
  }
  if (GPIO_IsPinLocked(HT_GPIOA, GPIO_PIN_2) == TRUE)
  {
    printf("GPIO Port A Pin 2 is Locked. \r\n");
  }
  else
  {
    printf("GPIO Port A Pin 2 is unLocked. \r\n");
  }
}

/*********************************************************************************************************//**
  * @brief  Lock Pin Test. (Port A Pin 1)
            PA1 is Locked, so changing PA1 GPIO Configuration is invalid.
            After changing  GPIO Configuration, PA1 GPIO Configuration as below:
            AFIO Mode: GPIO Mode
            Default Value         : RESET
            Pull Resistor         : Pull-DISABLE
            Output Driving Current: 8mA
            Direction             : Output
            Result => PA1 Toggle Ten Times, because PA1 is Locked (Change Configuration is invalid)
                      PA1: (Output -> Output) Mode, (Pull-Disable -> Pull-Disable)
  * @retval None
  ***********************************************************************************************************/
void GPIO_LockPinTest(void)
{
  vu32 i, j;

  /* Change PA1 GPIO Configuration is invalid, because PA1 is locked                                        */
  /* PA1: (Output -> Output) Mode, (Pull-Disable -> Pull-Disable)                                           */
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_1, GPIO_PR_UP);
  GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_IN);

  /* Toggle PA1 ten times                                                                                   */
  for (j = 0; j < 10; j++)
  {
    HT_GPIOA->DOUTR ^= 1 << 1; /* PA1 Pin Lock in Output Mode, so toggle valid.                             */
    for (i = 0; i < 1000000; i++);
  }
}

/*********************************************************************************************************//**
  * @brief  Other Pin Test. (Port A Pin 2)
            PA2 is UnLocked, so changing PA2 GPIO Configuration is valid.
            After changing  GPIO Configuration, PA2 GPIO Configuration as below:
            AFIO Mode             : GPIO Mode
            Default Value         : RESET
            Pull Resistor         : "Pull-Up"
            Output Driving Current: 8mA
            Direction             : "Input"
            Result => PA2 keeps the high level, because PA2 is unlocked (Change Configuration is valid)
                      PA2: (Output -> Input) Mode, (Pull-Disable -> Pull-Up)
  * @retval None
  ***********************************************************************************************************/
void GPIO_OtherPinTest(void)
{
  vu32 i, j;

  /* Change PA2 GPIO Configuration is valid, because PA2 is unlocked                                        */
  /* PA2: (Output -> Input) Mode, (Pull-Disable -> Pull-Up)                                                 */
  GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_2, GPIO_PR_UP);
  GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_2, GPIO_DIR_IN);

  /* PA2 keeps the high level                                                                               */
  for (j = 0; j < 10; j++)
  {
    HT_GPIOA->DOUTR ^= 1 << 2; /* PA2 Input Mode , so toggle invalid.                                       */
    for (i = 0; i < 1000000; i++);
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
