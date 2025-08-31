/*********************************************************************************************************//**
 * @file    NVIC/Disable_Interrupt/main.c
 * @version $Rev:: 8753         $
 * @date    $Date:: 2025-05-12 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup NVIC_Examples NVIC
  * @{
  */

/** @addtogroup Disable_Interrupt
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void NVIC_Configuration(void);
void BFTM_Configuration(void);

/* Private variables ---------------------------------------------------------------------------------------*/
vu32 bftm_counter = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{

  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);
  BFTM_Configuration();

  while (1)
  {
    if (HT32F_DVB_PBGetState(BUTTON_KEY1) == RESET)
    {
      __disable_irq();
    }
    else
    {
      __enable_irq();
    }
  }
}

/*********************************************************************************************************//**
  * @brief  BFTM Configuration.
  * @retval None
  ***********************************************************************************************************/
void BFTM_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.BFTM0      = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  BFTM_SetCompare(HT_BFTM0, LIBCFG_MAX_SPEED/1000);
  BFTM_IntConfig(HT_BFTM0, ENABLE);
  BFTM_SetCounter(HT_BFTM0, 0);
  BFTM_EnaCmd(HT_BFTM0, ENABLE);

  NVIC_EnableIRQ(BFTM0_IRQn);
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
