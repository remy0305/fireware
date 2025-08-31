/*********************************************************************************************************//**
 * @file    HWDIV/DIV32/main.c
 * @version $Rev:: 1524         $
 * @date    $Date:: 2017-07-03 #$
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup HWDIV_Examples HWDIV
  * @{
  */

/** @addtogroup DIV32
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void DIV_TestFun1(void);
void DIV_TestFun2(void);
void DIV_TestFun3(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 ua, ub, uc, uRemainder;
s32 sa, sb, sc, sRemainder;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  printf("\r\n\r\n");

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.DIV = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  DIV_TestFun1();
  DIV_TestFun2();

  while (1)
  {
    DIV_TestFun3();
  }
}


/*********************************************************************************************************//**
  * @brief  Div Test function.
  * @retval None
  ***********************************************************************************************************/
void DIV_TestFun1(void)
{
  /* 31-bit Unsigned division, maximum input value is 0x7FFFFFFF (2147483647, 31-bit)                       */
  ua = 52352;
  ub = 3;
  uc = DIV_Div32(ua, ub);
  uRemainder = DIV_GetLastRemainder();
  printf("Unsigned 31-bit %u / %u = %u, Remainder = %u\r\n\r\n", ua, ub, uc, uRemainder);

  ua = 2147483647;
  ub = 2147483640;
  uc = DIV_Div32(ua, ub);
  uRemainder = DIV_GetLastRemainder();
  printf("Unsigned 31-bit %u / %u = %u, Remainder = %u\r\n\r\n", ua, ub, uc, uRemainder);

  /* 32-bit Unsigned division                                                                               */
  ua = 52352;
  ub = 3;
  uc = DIV_uDiv32(ua, ub);
  uRemainder = DIV_uGetLastRemainder();
  printf("Unsigned 32-bit %u / %u = %u, Remainder = %u\r\n\r\n", ua, ub, uc, uRemainder);

  ua = 0x84663548;           // 2221290824
  ub = 0x1ACF;               // 6863
  uc = DIV_uDiv32(ua, ub);   // ua / ub = (x / ub) + (0x7FFFFFFF / ub), where ua = x + 0x7FFFFFFF
  uRemainder = DIV_uGetLastRemainder();
  printf("Unsigned 32-bit %u / %u = %u, Remainder = %u\r\n\r\n", ua, ub, uc, uRemainder);

  ua = 0x80000002;           // 2147483650
  ub = 0x80000001;           // 2147483649
  uc = DIV_uDiv32(ua, ub);   // ua / ub = 1...(ua - ub), where ua and ub > 0x7FFFFFFF
  uRemainder = DIV_uGetLastRemainder();
  printf("Unsigned %u / %u = %u, Remainder = %u\r\n\r\n", ua, ub, uc, uRemainder);

  /* Signed division                                                                                        */
  sa = 52241;
  sb = -4;
  sc = DIV_Div32(sa, sb);
  sRemainder = DIV_GetLastRemainder();
  printf("Signed %d / %d = %d, Remainder = %d\r\n\r\n", sa, sb, sc, sRemainder);

  sa = -52241;
  sb = 9;
  sc = DIV_Div32(sa, sb);
  sRemainder = DIV_GetLastRemainder();
  printf("Signed %d / %d = %d, Remainder = %d\r\n\r\n", sa, sb, sc, sRemainder);

  /* Mod operation                                                                                          */
  sa = 52241;
  sb = -6;
  sc = DIV_Mod(sa, sb);
  printf("Signed %d mod %d = %d\r\n\r\n", sa, sb, sc);
}

/*********************************************************************************************************//**
  * @brief  Div Test function.
  * @retval None
  ***********************************************************************************************************/
void DIV_TestFun2(void)
{
  /* You cna also set the "DIV_ENABLE_DIVIDE_BY_ZERO_CHECK = 1" to check the divide by zero case            */
  /* (stop at foreverloop)                                                                                  */
  sc = DIV_Div32(100, 0);
  sRemainder = DIV_GetLastRemainder();
  printf("Signed 100 / 0 = %d, Remainder = %d\r\n", sc, sRemainder);
  if (DIV_IsDivByZero() == TRUE)
  {
    printf("Divide by zero occurred! The quotient is not meaningful!\r\n");
  }
}

/*********************************************************************************************************//**
  * @brief  Div Test function.
  * @retval None
  ***********************************************************************************************************/
void DIV_TestFun3(void)
{
  printf ("\r\nPlease input integer....\r\n");

  printf("Dividend=");
  scanf("%d", &sa);
  printf("%d", sa);

  printf("\r\nDivisor=");
  scanf("%d", &sb);
  printf("%d", sb);

  sc = DIV_Div32(sa, sb);

  printf("\r\n%d / %d = %d\r\n\r\n", sa, sb, sc);
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
