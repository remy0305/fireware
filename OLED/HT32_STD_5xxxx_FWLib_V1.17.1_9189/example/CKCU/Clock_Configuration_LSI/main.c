/*********************************************************************************************************//**
 * @file    CKCU/Clock_Configuration_LSI/main.c
 * @version $Rev:: 1396         $
 * @date    $Date:: 2017-06-21 #$
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

/** @addtogroup Clock_Configuration_LSI
  * @{
  */

/* Private constants ---------------------------------------------------------------------------------------*/
#define DELAY_TIME          (32000)
#define DELAY_TIME_LSI      (100)

/* Private function prototypes -----------------------------------------------------------------------------*/
void SysClockConfig_LSI(void);

static void __Delay(vu32 count);

void Clock_TestFun(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  /* Initialize LEDs                                                                                        */
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);

  Clock_TestFun();

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Clock sourse switch test
  * @retval None
  ***********************************************************************************************************/
void Clock_TestFun(void){
  int i;
  for (i = 0; i < 300; i++)
  {
    /* Toggle LED1                                                                                        */
    HT32F_DVB_LEDToggle(HT_LED1);
    __Delay(DELAY_TIME);
  }
  HT32F_DVB_LEDOff(HT_LED1);

  SysClockConfig_LSI();

  for (i = 0; i < 100; i++)
  {
    /* Toggle LED2                                                                                        */
    HT32F_DVB_LEDToggle(HT_LED2);
    __Delay(DELAY_TIME_LSI);
  }
  HT32F_DVB_LEDOff(HT_LED2);

}

/*********************************************************************************************************//**
  * @brief Configure system clock as LSI.
  * @retval None
  ***********************************************************************************************************/
void SysClockConfig_LSI(void)
{
  while (CKCU_GetClockReadyStatus(CKCU_FLAG_LSIRDY) != SET);      /* wait LSI ready                         */
  CKCU_SysClockConfig(CKCU_SW_LSI);                               /* select CK_SYS source                   */
  CKCU_SetHCLKPrescaler(CKCU_SYSCLK_DIV1);                        /* set CK_AHB prescaler                   */

  #if (LIBCFG_FMC_PREFETCH)
  FLASH_SetWaitState(FLASH_WAITSTATE_0);
  #endif

  CKCU_HSICmd(DISABLE);                                           /* Disable HSI                            */
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

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  delay function
  * @param  count: delay count for loop
  * @retval None
  ***********************************************************************************************************/
static void __Delay(vu32 count)
{
  while (count--);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
