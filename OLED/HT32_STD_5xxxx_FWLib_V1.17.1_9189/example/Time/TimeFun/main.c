/*********************************************************************************************************//**
 * @file    Time/TimeFun/main.c
 * @version $Rev:: 5543         $
 * @date    $Date:: 2021-07-23 #$
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

/** @addtogroup Time_Examples Time
  * @{
  */

/** @addtogroup TimeFun
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void Test_Time_Delay(void);

void Test_Time_Measure(void);
void Test_Fun(void);

void Test_Time_Out(void);
bool IsTimeOut(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 guTimeOutStart = 0;
u32 guTimeOut_ms = 100;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);
  RETARGET_Configuration();

  Time_Init();

  Test_Time_Delay();

  Test_Time_Measure();

  HT32F_DVB_LEDToggle(HT_LED1);

  while (1)
  {
    Test_Time_Out();
  }
}

/*********************************************************************************************************//**
  * @brief  Test "Time_Delay()" function.
  * @retval None
  ***********************************************************************************************************/
void Test_Time_Delay(void)
{
  HT32F_DVB_LEDOn(HT_LED1);
  Time_Delay(TIME_MS2TICK(500));
  HT32F_DVB_LEDOff(HT_LED1);
  Time_Delay(TIME_MS2TICK(500));

  HT32F_DVB_LEDOn(HT_LED1);
  Time_Delay(TIME_MS2TICK(100));
  HT32F_DVB_LEDOff(HT_LED1);
  Time_Delay(TIME_MS2TICK(100));
}

/*********************************************************************************************************//**
  * @brief  Test Time Measure by "Time_GetTick()" function.
  * @retval None
  ***********************************************************************************************************/
void Test_Time_Measure(void)
{
  u32 uStart;
  u32 uEnd;
  u32 uDiff;

  uStart = Time_GetTick();

  HT32F_DVB_LEDOn(HT_LED1);
  Test_Fun();
  HT32F_DVB_LEDOff(HT_LED1);

  uEnd = Time_GetTick();

  uDiff = TIME_TICKDIFF(uStart, uEnd);

  printf("Test_Fun() take %d tick, about %d us\r\n", uDiff, (u32)TIME_TICK2US(uDiff));
}

/*********************************************************************************************************//**
  * @brief  Test function
  * @retval None
  ***********************************************************************************************************/
void Test_Fun(void)
{
  #if 1
  u32 i;
  for (i = 1000; i != 0; i--)
  {
  }
  #else
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
  #endif
}

/*********************************************************************************************************//**
  * @brief  Test timeout function.
  * @retval None
  ***********************************************************************************************************/
void Test_Time_Out(void)
{
  HT32F_DVB_LEDToggle(HT_LED2);

  if (IsTimeOut() == TRUE)
  {
    guTimeOut_ms += 10;
    HT32F_DVB_LEDToggle(HT_LED1);
  }
}

/*********************************************************************************************************//**
  * @brief  Check timeout by "Time_GetTick()" function.
  * @retval None
  ***********************************************************************************************************/
bool IsTimeOut(void)
{
  bool Result;
  if (guTimeOutStart == 0)
  {
    guTimeOutStart = Time_GetTick();
  }

  if (TIME_TICKDIFF(guTimeOutStart, Time_GetTick()) < TIME_MS2TICK(guTimeOut_ms))
  {
    Result = FALSE;
  }
  else
  {
    guTimeOutStart = 0;
    Result = TRUE;
  }

  return Result;
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
