/*********************************************************************************************************//**
 * @file    OPA/OPA_Enable/ht32_board_config.h
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

#if defined(USE_HT32F65232_DVB)
  #define HTCFG_OPA_IPN                            OPA0

  #define _HTCFG_OPAO_GPIOX                        C
  #define _HTCFG_OPAN_GPIOX                        A
  #define _HTCFG_OPAP_GPIOX                        A

  #define _HTCFG_OPAO_GPION                        4
  #define _HTCFG_OPAN_GPION                        7
  #define _HTCFG_OPAP_GPION                        6
#endif

#if defined(USE_HT32F65233_DVB)
  #define HTCFG_OPA_IPN                            OPA0

  #define _HTCFG_OPAO_GPIOX                        C
  #define _HTCFG_OPAN_GPIOX                        B
  #define _HTCFG_OPAP_GPIOX                        B

  #define _HTCFG_OPAO_GPION                        3
  #define _HTCFG_OPAN_GPION                        6
  #define _HTCFG_OPAP_GPION                        7
#endif

#if defined(USE_HT32F65240_SK)
  #define HTCFG_OPA_IPN                            OPA1

  #define _HTCFG_OPAO_GPIOX                        C
  #define _HTCFG_OPAN_GPIOX                        B
  #define _HTCFG_OPAP_GPIOX                        B

  #define _HTCFG_OPAO_GPION                        3
  #define _HTCFG_OPAN_GPION                        6
  #define _HTCFG_OPAP_GPION                        7
#endif

#define HTCFG_OPA_PORT                             STRCAT2(HT_,            HTCFG_OPA_IPN)

#define HTCFG_OPAO_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_OPAO_GPIOX)
#define HTCFG_OPAO_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_OPAO_GPION)

#define HTCFG_OPAN_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_OPAN_GPIOX)
#define HTCFG_OPAN_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_OPAN_GPION)

#define HTCFG_OPAP_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_OPAP_GPIOX)
#define HTCFG_OPAP_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_OPAP_GPION)

#ifdef __cplusplus
}
#endif

#endif
