/*********************************************************************************************************//**
 * @file    EXTI/EXTI_Key_LED/ht32_board_config.h
 * @version $Rev:: 5805         $
 * @date    $Date:: 2022-04-12 #$
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
#if defined(USE_HT32F50030_SK)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       9
  #define  HTCFG_WAKE_EXTI_CHANNEL                EXTI_CHANNEL_1
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI1_IRQn
#elif defined(USE_HT32F65232_DVB)
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       15
  #define  HTCFG_WAKE_EXTI_CHANNEL                EXTI_CHANNEL_15
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI15_IRQn
#elif defined(USE_HT32F65233_DVB)
  #define _HTCFG_WAKE_GPIOX                       C
  #define  HTCFG_WAKE_GPION                       2
  #define  HTCFG_WAKE_EXTI_CHANNEL                EXTI_CHANNEL_2
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI2_IRQn
#else
  #define _HTCFG_WAKE_GPIOX                       B
  #define  HTCFG_WAKE_GPION                       12
  #define  HTCFG_WAKE_EXTI_CHANNEL                EXTI_CHANNEL_12
  #define  HTCFG_WAKE_EXTI_IRQn                   EXTI12_IRQn
#endif

#define HTCFG_WAKE_GPIO_CK                        STRCAT2(P,              _HTCFG_WAKE_GPIOX)
#define HTCFG_WAKE_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_WAKE_GPIOX)
#define HTCFG_WAKE_AFIO_PIN                       STRCAT2(AFIO_PIN_,      HTCFG_WAKE_GPION)
#define HTCFG_WAKE_GPIO_PORT                      STRCAT2(HT_GPIO,        _HTCFG_WAKE_GPIOX)
#define HTCFG_WAKE_GPIO_PIN                       STRCAT2(GPIO_PIN_,      HTCFG_WAKE_GPION)

#ifdef __cplusplus
}
#endif

#endif
