/*********************************************************************************************************//**
 * @file    BFTM/TimeMeasure/main.c
 * @version $Rev:: 8666         $
 * @date    $Date:: 2025-04-29 #$
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

/** @addtogroup BFTM_Examples BFTM
  * @{
  */

/** @addtogroup TimeMeasure
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define HTCFG_MEASURE_IPN                         BFTM0
#define HTCFG_MEASURE_PORT                        STRCAT2(HT_, HTCFG_MEASURE_IPN)

#if (LIBCFG_BFTM_16BIT_COUNTER)
#define BFTM_COMPARE_VALUE   (0xFFFF) // Maximum value of 16-bit counter
#else
#define BFTM_COMPARE_VALUE   (0xFFFFFFFF) // Maximum value of 32-bit counter
#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
void BFTM_Configuration(void);
void TimeMeasureFun(void);

static void TestFun1(void);
void TestFun2(void);

/* Private macro -------------------------------------------------------------------------------------------*/
#define MeasureStart()                            {HTCFG_MEASURE_PORT->SR = 0; HTCFG_MEASURE_PORT->CNTR = 0;}
#define MeasureEnd(cnt)                           (cnt = HTCFG_MEASURE_PORT->CNTR)
#define IsMeasureOverflow()                       (BFTM_GetFlagStatus(HTCFG_MEASURE_PORT))

/* Global variables ----------------------------------------------------------------------------------------*/
s32 num;  /* Numerator    */
s32 den;  /* Denominator  */
s32 quo;  /* Quotient     */

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);
  RETARGET_Configuration();

  BFTM_Configuration();
  TimeMeasureFun();

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  BFTM Configuration.
  * @retval None
  ***********************************************************************************************************/
void BFTM_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.HTCFG_MEASURE_IPN      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  BFTM_SetCompare(HTCFG_MEASURE_PORT, BFTM_COMPARE_VALUE);  // Set to maximum value to detect the timer overflow
  BFTM_SetCounter(HTCFG_MEASURE_PORT, 0);
  BFTM_EnaCmd(HTCFG_MEASURE_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Time measure function example.
  * @retval None
  ***********************************************************************************************************/
void TimeMeasureFun(void)
{
  u32 uCount;

  /*--------------------------------------------------------------------------------------------------------*/
  /* Measure the UART 1 bytes                                                                               */
  /*--------------------------------------------------------------------------------------------------------*/
  MeasureStart();
  {
    RETARGET_USART_PORT->DR = 'a';
    while ((RETARGET_USART_PORT->SR & USART_FLAG_TXC) == 0);
  }
  MeasureEnd(uCount); // Time count based on the system clock, t = uCount/SystemCoreClock
  #if 1
  if (IsMeasureOverflow()) // Shall check the timer overflow, close to the "MeasureEnd()"
  {
    printf("\r\nTimer overflow, the uCount is invalid!\r\n"); // Timer overflow, the uCount is invalid
  }
  #endif
  printf("\r\nMeasure 1 Count=%4u, T=%2.9f mS\r\n", uCount, ((float)uCount)/((float)SystemCoreClock/1000));


  /*--------------------------------------------------------------------------------------------------------*/
  /* Measure the LED API execution timing                                                                   */
  /*--------------------------------------------------------------------------------------------------------*/
  MeasureStart();
  {
    HT32F_DVB_LEDOn(HT_LED1);
  }
  MeasureEnd(uCount); // Time count based on the system clock, t = uCount/SystemCoreClock

  printf("Measure 2 Count=%4u, T=%2.9f uS\r\n", uCount, ((float)uCount)/((float)SystemCoreClock/1000000));


  /*--------------------------------------------------------------------------------------------------------*/
  /* Measure the division execution timing                                                                  */
  /*--------------------------------------------------------------------------------------------------------*/
  num = 978520;
  den = 48;
  MeasureStart();
  {
    quo = num/den;
  }
  MeasureEnd(uCount); // Time count based on the system clock, t = uCount/SystemCoreClock

  printf("Measure 3 Count=%4u, T=%2.9f S, Quotient=%d\r\n", uCount, ((float)uCount)/SystemCoreClock, quo);


  /*--------------------------------------------------------------------------------------------------------*/
  /* Measure the instruction/function execution timing (may have the Flash Wait effect)                     */
  /*--------------------------------------------------------------------------------------------------------*/
  MeasureStart();
  {
    TestFun1();
  }
  MeasureEnd(uCount); // Time count based on the system clock, t = uCount/SystemCoreClock

  printf("Measure 4 Count=%4u, T=%2.9f S\r\n", uCount, ((float)uCount)/SystemCoreClock);


  /*--------------------------------------------------------------------------------------------------------*/
  /* Measure the instruction/function execution timing (may have the Flash Wait effect)                     */
  /*--------------------------------------------------------------------------------------------------------*/
  MeasureStart();
  {
    TestFun2();
  }
  MeasureEnd(uCount); // Time count based on the system clock, t = uCount/SystemCoreClock

  printf("Measure 5 Count=%4u, T=%2.9f S\r\n", uCount, ((float)uCount)/SystemCoreClock);

}

/*********************************************************************************************************//**
  * @brief  Test function 1 (with "static", shall be inline).
  * @retval None
  ***********************************************************************************************************/
static void TestFun1(void)
{
  {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
}

/*********************************************************************************************************//**
  * @brief  Test function 2 (without "static", may needs function jump overhead).
  * @retval None
  ***********************************************************************************************************/
void TestFun2(void)
{
  {__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
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
