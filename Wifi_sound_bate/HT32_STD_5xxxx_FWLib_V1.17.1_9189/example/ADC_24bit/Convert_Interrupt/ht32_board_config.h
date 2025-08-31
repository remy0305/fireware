/*********************************************************************************************************//**
 * @file    ADC_24bit/Convert_Interrupt/ht32_board_config.h
 * @version $Rev:: 5193         $
 * @date    $Date:: 2021-01-25 #$
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
#if defined(USE_HT32F59041_SK)
  #define _HTCFG_DRDYB_GPIOX                      B
  #define _HTCFG_DRDYB_GPION                      2

  #define HTCFG_I2CM_CH0                          I2C0
  #define HTCFG_M0_SCL_GPIO_PORT                  B
  #define HTCFG_M0_SCL_GPIO_PIN                   0
  #define HTCFG_M0_SDA_GPIO_PORT                  B
  #define HTCFG_M0_SDA_GPIO_PIN                   1
#endif

#if defined(USE_HT32F59741_SK)
  #define _HTCFG_DRDYB_GPIOX                      A
  #define _HTCFG_DRDYB_GPION                      14

  #define HTCFG_I2CM_CH0                          I2C0
  #define HTCFG_M0_SCL_GPIO_PORT                  B
  #define HTCFG_M0_SCL_GPIO_PIN                   0
  #define HTCFG_M0_SDA_GPIO_PORT                  B
  #define HTCFG_M0_SDA_GPIO_PIN                   1
#endif

#define HTCFG_DRDYB_GPIO_CK                       STRCAT2(P,              _HTCFG_DRDYB_GPIOX)
#define HTCFG_DRDYB_GPIO_ID                       STRCAT2(GPIO_P,         _HTCFG_DRDYB_GPIOX)
#define HTCFG_DRDYB_AFIO_PIN                      STRCAT2(AFIO_PIN_,      _HTCFG_DRDYB_GPION)
#define HTCFG_DRDYB_GPIO_PORT                     STRCAT2(HT_GPIO,        _HTCFG_DRDYB_GPIOX)
#define HTCFG_DRDYB_GPIO_PIN                      STRCAT2(GPIO_PIN_,      _HTCFG_DRDYB_GPION)
#define HTCFG_DRDYB_AFIO_EXTI_CH                  STRCAT2(AFIO_EXTI_CH_,  _HTCFG_DRDYB_GPION)
#define HTCFG_DRDYB_AFIO_ESS                      STRCAT2(AFIO_ESS_P,     _HTCFG_DRDYB_GPIOX)
#define HTCFG_DRDYB_EXTI_CHANNEL                  STRCAT2(EXTI_CHANNEL_,  _HTCFG_DRDYB_GPION)

#if _HTCFG_DRDYB_GPION < 2
#define HTCFG_DRDYB_EXTI_IRQn                     EXTI0_1_IRQn
#define DRDYB_EXTI_IRQHandler                     EXTI0_1_IRQHandler
#elif _HTCFG_DRDYB_GPION < 4
#define HTCFG_DRDYB_EXTI_IRQn                     EXTI2_3_IRQn
#define DRDYB_EXTI_IRQHandler                     EXTI2_3_IRQHandler
#else
#define HTCFG_DRDYB_EXTI_IRQn                     EXTI4_15_IRQn
#define DRDYB_EXTI_IRQHandler                     EXTI4_15_IRQHandler
#endif


#ifdef __cplusplus
}
#endif

#endif
