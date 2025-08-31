/*********************************************************************************************************//**
 * @file    PGA/Comparator/ht32_board_config.h
 * @version $Rev:: 8167         $
 * @date    $Date:: 2024-09-23 #$
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
#if defined(USE_HT32F65233_DVB)
  #define HTCFG_PGA_PORT                          HT_PGA1
  #define _HTCFG_PGA_POS_GPIOX                    C
  #define _HTCFG_PGA_POS_GPION                    11
  #define _HTCFG_PGA_NEG_GPIOX                    C
  #define _HTCFG_PGA_NEG_GPION                    10
  #define _HTCFG_PGA_OUT_GPIOX                    B
  #define _HTCFG_PGA_OUT_GPION                    8
#endif

#if defined(USE_HT32F66242_DVB)
  #define HTCFG_PGA_PORT                          HT_PGA2
  #define _HTCFG_PGA_POS_GPIOX                    A
  #define _HTCFG_PGA_POS_GPION                    5
  #define _HTCFG_PGA_NEG_GPIOX                    A
  #define _HTCFG_PGA_NEG_GPION                    4
  #define _HTCFG_PGA_OUT_GPIOX                    A
  #define _HTCFG_PGA_OUT_GPION                    3
#endif

#if defined(USE_HT32F66246_DVB)
  #define HTCFG_PGA_PORT                          HT_PGA2
  #define _HTCFG_PGA_POS_GPIOX                    A
  #define _HTCFG_PGA_POS_GPION                    5
  #define _HTCFG_PGA_NEG_GPIOX                    A
  #define _HTCFG_PGA_NEG_GPION                    4
  #define _HTCFG_PGA_OUT_GPIOX                    A
  #define _HTCFG_PGA_OUT_GPION                    3
#endif

#define HTCFG_PGA_POS_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_PGA_POS_GPIOX)
#define HTCFG_PGA_POS_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_PGA_POS_GPION)

#define HTCFG_PGA_NEG_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_PGA_NEG_GPIOX)
#define HTCFG_PGA_NEG_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_PGA_NEG_GPION)

#define HTCFG_PGA_OUT_GPIO_ID                     STRCAT2(GPIO_P,         _HTCFG_PGA_OUT_GPIOX)
#define HTCFG_PGA_OUT_AFIO_PIN                    STRCAT2(AFIO_PIN_,      _HTCFG_PGA_OUT_GPION)

#ifdef __cplusplus
}
#endif

#endif
