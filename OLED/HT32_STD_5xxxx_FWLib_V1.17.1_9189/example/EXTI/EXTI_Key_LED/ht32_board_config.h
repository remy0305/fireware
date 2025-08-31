/*********************************************************************************************************//**
 * @file    EXTI/EXTI_Key_LED/ht32_board_config.h
 * @version $Rev:: 8632         $
 * @date    $Date:: 2025-04-25 #$
 * @brief   The header file of board configuration.
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
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_HT32F52230_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F52241_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       7
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI7_IRQn
#endif

#if defined(USE_HT32F52253_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       D
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI1_IRQn
#endif

#if defined(USE_HT32F52341_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       0
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI0_IRQn
#endif

#if defined(USE_HT32F52352_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       D
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI1_IRQn
#endif

#if defined(USE_HT32F0008_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F50030_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       9
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI1_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       3
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI3_IRQn
#endif

#if defined(USE_HT32F50230_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F50241_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F52354_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       14
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI14_IRQn
#endif

#if defined(USE_HT32F0006_DVB)
  #define _HTCFG_WAKE_GPIOX                       A
  #define  HTCFG_WAKE_GPION                       0
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI0_IRQn

  #define _HTCFG_KEY1_GPIOX                       A
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI1_IRQn
#endif

#if defined(USE_HT32F57341_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       A
  #define  HTCFG_KEY1_GPION                       9
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI9_IRQn
#endif

#if defined(USE_HT32F57352_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       A
  #define  HTCFG_KEY1_GPION                       9
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI9_IRQn
#endif

#if defined(USE_HT32F52367_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       15
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI15_IRQn
#endif

#if defined(USE_BM53A367A_DVB)
  #define _HTCFG_WAKE_GPIOX                       B               // D22
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B               // D2
  #define  HTCFG_KEY1_GPION                       0
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI0_IRQn
#endif

#if defined(USE_BM18B367A_DVB)
  #define _HTCFG_WAKE_GPIOX                       A               // D17
  #define  HTCFG_WAKE_GPION                       4
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI4_IRQn

  #define _HTCFG_KEY1_GPIOX                       A               // D31
  #define  HTCFG_KEY1_GPION                       5
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI5_IRQn
#endif

#if defined(USE_HT32F50343_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       7
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI7_IRQn
#endif

#if defined(USE_HT32F54241_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B   // Conncet to the external trigger pin. If use the expansion board, please connect PA14 and PB8 to an outer line.
  #define  HTCFG_KEY1_GPION                       8
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI8_IRQn
#endif

#if defined(USE_HT32F54253_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F61141_SK)  //PRELIMINARY_NOT_TEST
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       A
  #define  HTCFG_KEY1_GPION                       15
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI15_IRQn
#endif

#if defined(USE_HT32F61245_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       14
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI14_IRQn
#endif

#if defined(USE_HT32F61355_SK) || defined(USE_HT32F61356_SK) || defined(USE_HT32F61357_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       14
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI14_IRQn
#endif

#if defined(USE_HT32F65240_DVB)
  #define _HTCFG_WAKE_GPIOX                       A
  #define  HTCFG_WAKE_GPION                       6
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI6_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       9
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI9_IRQn
#endif

#if defined(USE_HT32F65240_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI1_IRQn
#endif

#if defined(USE_HT32F65232_DVB)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       15
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI15_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       8
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI8_IRQn
#endif

#if defined(USE_HT32F67051_SK)  //PRELIMINARY_NOT_TEST
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI0_IRQn
#endif

#if defined(USE_HT32F67233_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       A
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F50452_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       D
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI1_IRQn
#endif

#if defined(USE_HT32F53252_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       D
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI1_IRQn
#endif

#if defined(USE_HT32F50441_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F53241_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       2
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI2_IRQn
#endif

#if defined(USE_HT32F52244_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn

  #define _HTCFG_KEY1_GPIOX                       B
  #define  HTCFG_KEY1_GPION                       7
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI7_IRQn
#endif

#if defined(USE_HT32F66242_DVB)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       2
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI2_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       0
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI0_IRQn
#endif

#if defined(USE_HT32F66246_DVB)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       2
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI2_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       0
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI0_IRQn
#endif

#if defined(USE_HT32F65233_DVB)
  #define _HTCFG_WAKE_GPIOX                       C
  #define  HTCFG_WAKE_GPION                       2
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI2_IRQn

  #define _HTCFG_KEY1_GPIOX                       C
  #define  HTCFG_KEY1_GPION                       1
  #define  HTCFG_KEY1_EXTI_IRQn                   EXTI1_IRQn
#endif

#define HTCFG_WAKE_GPIO_CK                        STRCAT2(P,              _HTCFG_WAKE_GPIOX)
#define HTCFG_WAKE_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_WAKE_GPIOX)
#define HTCFG_WAKE_AFIO_PIN                       STRCAT2(AFIO_PIN_,      HTCFG_WAKE_GPION)
#define HTCFG_WAKE_GPIO_PORT                      STRCAT2(HT_GPIO,        _HTCFG_WAKE_GPIOX)
#define HTCFG_WAKE_GPIO_PIN                       STRCAT2(GPIO_PIN_,      HTCFG_WAKE_GPION)


#define HTCFG_KEY1_GPIO_CK                        STRCAT2(P,              _HTCFG_KEY1_GPIOX)
#define HTCFG_KEY1_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_KEY1_GPIOX)
#define HTCFG_KEY1_AFIO_PIN                       STRCAT2(AFIO_PIN_,      HTCFG_KEY1_GPION)
#define HTCFG_KEY1_GPIO_PORT                      STRCAT2(HT_GPIO,        _HTCFG_KEY1_GPIOX)
#define HTCFG_KEY1_GPIO_PIN                       STRCAT2(GPIO_PIN_,      HTCFG_KEY1_GPION)

#ifdef __cplusplus
}
#endif

#endif
