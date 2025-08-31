/*********************************************************************************************************//**
 * @file    SYSTICK/DelayMicrosecond/main.c
 * @version $Rev:: 6735         $
 * @date    $Date:: 2023-02-15 #$
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

/** @addtogroup SYSTICK_Examples SYSTICK
  * @{
  */

/** @addtogroup DelayMicrosecond
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/* !!! NOTICE !!!
   Notice that the value of the preprocessor depends on the device.
*/
#define TICK_OFFSET                               (13) // HT32F50231/50241
//#define TICK_OFFSET                               (15) // HT32F52342/52352 (Branch Cache)

#define TICK_US                                   (LIBCFG_MAX_SPEED / 1000000)

/* Private macro -------------------------------------------------------------------------------------------*/
#define US2TICK(us)                               (us * TICK_US - TICK_OFFSET)

#define delayMicroseconds(cnt)                    {SysTick->LOAD = cnt;\
                                                   SysTick->VAL = 0;\
                                                   while (SysTick->CTRL == 5);}

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.PA = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  GPIO_DirectionConfig(HTCFG_GPIO_ID, HTCFG_GPIO_PIN, GPIO_DIR_OUT);

  SYSTICK_ClockSourceConfig(SYSTICK_SRC_FCLK);
  SYSTICK_SetReloadValue(0x5);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
  SysTick->CTRL; // Fix the timing issue when using delayMicroseconds() for the first time

  HT_GPIOA->SRR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(1));
  HT_GPIOA->RR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(2));
  HT_GPIOA->SRR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(3));
  HT_GPIOA->RR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(4));
  HT_GPIOA->SRR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(5));
  HT_GPIOA->RR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(6));
  HT_GPIOA->SRR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(7));
  HT_GPIOA->RR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(8));
  HT_GPIOA->SRR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(9));
  HT_GPIOA->RR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(10));
  HT_GPIOA->SRR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(11));
  HT_GPIOA->RR = HTCFG_GPIO_PIN;
  delayMicroseconds(US2TICK(12));
  HT_GPIOA->SRR = HTCFG_GPIO_PIN;

  while (1)
  {
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
