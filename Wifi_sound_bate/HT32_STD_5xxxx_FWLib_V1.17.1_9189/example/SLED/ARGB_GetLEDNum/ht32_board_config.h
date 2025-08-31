/*********************************************************************************************************//**
 * @file    SLED/ARGB_GetLEDNum/ht32_board_config.h
 * @version $Rev:: 4515         $
 * @date    $Date:: 2020-02-05 #$
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
#if defined(USE_HT32F50343_SK)
  #define HTCFG_SLED_IPN                          SLED1
  #define _HTCFG_SLED_GPIOX                       A
  #define _HTCFG_SLED_GPION                       0

  #define HTCFG_SLED_CK_PRESCALER                 (3)            /* 60M / HTCFG_SLED_CK_PRESCALER  = 20M Hz */
  #define HTCFG_SLED_BAUDRATE                     (24)           /* HTCFG_SLED_BAUDRATE / 20M      = 1.2us  */
  #define HTCFG_SLED_RESET                        (208)          /* HTCFG_SLED_RESET * 1.2us       = 250us  */
  #define HTCFG_SLED_T0H                          (6)            /* 6/24 = 25% Duty. 1.2us*(25/100)= 0.3us  */
  #define HTCFG_SLED_T1H                          (18)           /* 18/24 = 75% Duty. 1.2us*(75/100)= 0.9us */
#endif

#define HTCFG_SLED                                STRCAT2(HT_GPIO,        _HTCFG_SLED_GPIOX)
#define HTCFG_SLED_CK                             STRCAT2(P,              _HTCFG_SLED_GPIOX)
#define HTCFG_SLED_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_SLED_GPIOX)
#define HTCFG_SLED_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_SLED_GPION)
#define HTCFG_SLED_PORT                           STRCAT2(HT_,            HTCFG_SLED_IPN)
#define HTCFG_SLED_GPIO_PIN                       STRCAT2(GPIO_PIN_,      _HTCFG_SLED_GPION)

#ifdef __cplusplus
}
#endif

#endif
