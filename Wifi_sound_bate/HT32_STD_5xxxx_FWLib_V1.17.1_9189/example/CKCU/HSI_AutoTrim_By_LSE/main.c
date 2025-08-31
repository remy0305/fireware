/*********************************************************************************************************//**
 * @file    CKCU/HSI_AutoTrim_By_LSE/main.c
 * @version $Rev:: 7524         $
 * @date    $Date:: 2024-01-17 #$
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

/** @addtogroup CKCU_Examples CKCU
  * @{
  */

/** @addtogroup HSI_AutoTrim_By_LSE
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void CKOUTConfig(void);
void AutoTrim_Configuration(void);
void AutoTrim_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 guIsAutoTrimReady = FALSE;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  HT32F_DVB_LEDInit(HT_LED1);

  #if 0
  CKOUTConfig();
  #endif

  AutoTrim_Configuration();

  while (1)
  {
    AutoTrim_MainRoutine();

    if (guIsAutoTrimReady == TRUE)
    {
      // Do the things which shall wait the HSI Auto Trim Ready.
      // ...
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Auto Trim by LSE configuration.
  * @retval None
  ***********************************************************************************************************/
void AutoTrim_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.BKP = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  RTC_LSESMConfig(RTC_LSESM_FAST);
  RTC_LSECmd(ENABLE);
  while (CKCU_GetClockReadyStatus(CKCU_FLAG_LSERDY) == RESET); // Take long time (xxx ms) when first time power-on

  CKCU_HSIAutoTrimClkConfig(CKCU_ATC_LSE);
  CKCU_HSIAutoTrimCmd(ENABLE);

  #if 0 // Wait Auto Trim Ready
  while (CKCU_HSIAutoTrimIsReady() == FALSE);
  #endif
}

/*********************************************************************************************************//**
  * @brief  Auto Trim main routine.
  * @retval None
  ***********************************************************************************************************/
void AutoTrim_MainRoutine(void)
{
  if (guIsAutoTrimReady == FALSE)
  {
    guIsAutoTrimReady = CKCU_HSIAutoTrimIsReady();
    if (guIsAutoTrimReady == TRUE)
    {
      #if 1
      HT32F_DVB_LEDToggle(HT_LED1);
      printf("HSI Auto Trim Ready!\r\n");
      #endif
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the debug output clock.
  * @retval None
  ***********************************************************************************************************/
void CKOUTConfig(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* Configure CKOUT                                                                                      */
    CKCU_CKOUTInitTypeDef CKOUTInit;
    CKOUTInit.CKOUTSRC = CKCU_CKOUTSRC_HSICK_DIV16;
    CKCU_CKOUTConfig(&CKOUTInit);
  }

  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_9, AFIO_MODE_15);
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
