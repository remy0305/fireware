/*********************************************************************************************************//**
 * @file    BFTM/OneShot/main.c
 * @version $Rev:: 6400         $
 * @date    $Date:: 2022-10-28 #$
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

/** @addtogroup OneShot
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
#define HTCFG_ONESHOT_IPN                         BFTM0
#define HTCFG_ONESHOT_PORT                        STRCAT2(HT_, HTCFG_ONESHOT_IPN)
#define HTCFG_ONESHOT_CLKPRE                      STRCAT2(CKCU_PCLK_, HTCFG_ONESHOT_IPN)
#define COMPARE_MATCH_COUNTER                     (245)

/* Private macro -------------------------------------------------------------------------------------------*/

/* !!! NOTICE !!!
   The actually delay will be large then the calculation result since the code execution overhead.
*/
#if 1
// Direct register access to reduce time overhead error
#define OneShot_Delay(cnt)                        {HTCFG_ONESHOT_PORT->SR = 0;\
                                                   HTCFG_ONESHOT_PORT->CMP = cnt;\
                                                   HTCFG_ONESHOT_PORT->CR |= (1 << 2);\
                                                   while (HTCFG_ONESHOT_PORT->SR == 0){};}
#else
#define OneShot_Delay(cnt)                        {BFTM_ClearFlag(HTCFG_ONESHOT_PORT);\
                                                   BFTM_SetCompare(HTCFG_ONESHOT_PORT, cnt);\
                                                   BFTM_EnaCmd(HTCFG_ONESHOT_PORT, ENABLE);\
                                                   while (BFTM_GetFlagStatus(HTCFG_ONESHOT_PORT) != SET){};}
#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
void BFTM_Configuration(void);
void OneShotFun1(void);
void OneShotFun2(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);

  BFTM_Configuration();

  OneShotFun1();

  while (1)
  {
    OneShotFun2();
  }
}

/*********************************************************************************************************//**
  * @brief  BFTM Configuration.
  * @retval None
  ***********************************************************************************************************/
void BFTM_Configuration(void)
{
  #if 0 // Use following function to configure the IP clock speed.
  CKCU_SetPeripPrescaler(HTCFG_ONESHOT_CLKPRE, CKCU_APBCLKPRE_DIV2);
  #endif

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.HTCFG_ONESHOT_IPN = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* BFTM as one shot mode                                                                                  */
  BFTM_SetCounter(HTCFG_ONESHOT_PORT, 0);
  BFTM_OneShotModeCmd(HTCFG_ONESHOT_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  One Shot test example.
  * @retval None
  ***********************************************************************************************************/
void OneShotFun1(void)
{
  HT32F_DVB_LEDOn(HT_LED1);

  /* !!! NOTICE !!!
     The actually delay will be large then the (SystemCoreClock / n) calculation result
     since the code execution overhead.
  */
  OneShot_Delay(48000);         // T = (cnt + 1) * (1 / BFTM PCLK)
  HT32F_DVB_LEDOff(HT_LED1);

  OneShot_Delay(720);
  HT32F_DVB_LEDOn(HT_LED1);

  OneShot_Delay(48);
  HT32F_DVB_LEDOff(HT_LED1);
}


/*********************************************************************************************************//**
  * @brief  One Shot test example 2.
  * @retval None
  ***********************************************************************************************************/
#if (LIBCFG_BFTM_16BIT_COUNTER)
void OneShotFun2(void)
{
  u32 i;

  for (i = COMPARE_MATCH_COUNTER; i != 0; i--)
  {
    OneShot_Delay(0xFFFF);
  }

  HT32F_DVB_LEDToggle(HT_LED1);
}
#else
void OneShotFun2(void)
{
  OneShot_Delay(SystemCoreClock);
  HT32F_DVB_LEDToggle(HT_LED1);
}
#endif

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
