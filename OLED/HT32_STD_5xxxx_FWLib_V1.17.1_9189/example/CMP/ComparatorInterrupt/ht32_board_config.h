/*********************************************************************************************************//**
 * @file    CMP/ComparatorInterrupt/ht32_board_config.h
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
#if defined(USE_HT32F52352_SK)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         2
  #define HTCFG_CMP_IRQn                          COMP_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_IRQHandler
#endif

#if defined(USE_HT32F52354_SK)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         2
  #define HTCFG_CMP_IRQn                          COMP_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_IRQHandler
#endif

#if defined(USE_HT32F57352_SK)
  #define HTCFG_CP_PORT                           HT_CMP1
  #define _HTCFG_CP_GPIOX                         B
  #define _HTCFG_CP_GPION                         7
  #define HTCFG_CMP_IRQn                          COMP_DAC_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_DAC_IRQHandler
#endif

#if defined(USE_HT32F52367_SK)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         2
  #define HTCFG_CMP_IRQn                          COMP_DAC_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_DAC_IRQHandler
#endif

#if defined(USE_BM53A367A_DVB)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C               // A3/D17
  #define _HTCFG_CP_GPION                         2
  #define HTCFG_CMP_IRQn                          COMP_DAC_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_DAC_IRQHandler
#endif

#if defined(USE_HT32F54253_SK)
  #define HTCFG_CP_PORT                           HT_CMP1
  #define _HTCFG_CP_GPIOX                         B
  #define _HTCFG_CP_GPION                         7
  #define HTCFG_CMP_IRQn                          COMP_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_IRQHandler
#endif

#if defined(USE_HT32F65240_DVB)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         A
  #define _HTCFG_CP_GPION                         6
  #define HTCFG_CMP_IRQn                          CMP0_IRQn
  #define HTCFG_CMP_IRQHandler                    CMP0_IRQHandler
#endif

#if defined(USE_HT32F65240_SK)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         A
  #define _HTCFG_CP_GPION                         6
  #define HTCFG_CMP_IRQn                          CMP0_IRQn
  #define HTCFG_CMP_IRQHandler                    CMP0_IRQHandler
#endif

#if defined(USE_HT32F65232_DVB)
  #define HTCFG_CP_PORT                           HT_CMP1
  #define _HTCFG_CP_GPIOX                         B
  #define _HTCFG_CP_GPION                         7
  #define HTCFG_CMP_IRQn                          CMP1_IRQn
  #define HTCFG_CMP_IRQHandler                    CMP1_IRQHandler
#endif

#if defined(USE_HT32F65233_DVB)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         2
  #define HTCFG_CMP_IRQn                          CMP0_IRQn
  #define HTCFG_CMP_IRQHandler                    CMP0_IRQHandler
#endif

#if defined(USE_HT32F50452_SK)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         2
  #define HTCFG_CMP_IRQn                          COMP_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_IRQHandler
#endif

#if defined(USE_HT32F53252_SK)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         2
  #define HTCFG_CMP_IRQn                          COMP_IRQn
  #define HTCFG_CMP_IRQHandler                    COMP_IRQHandler
#endif

#if defined(USE_HT32F66242_DVB)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         11
  #define HTCFG_CMP_IRQn                          CMP0_IRQn
  #define HTCFG_CMP_IRQHandler                    CMP0_IRQHandler
#endif

#if defined(USE_HT32F66246_DVB)
  #define HTCFG_CP_PORT                           HT_CMP0
  #define _HTCFG_CP_GPIOX                         C
  #define _HTCFG_CP_GPION                         11
  #define HTCFG_CMP_IRQn                          CMP0_IRQn
  #define HTCFG_CMP_IRQHandler                    CMP0_IRQHandler
#endif

#define HTCFG_CP_GPIO_ID                          STRCAT2(GPIO_P,         _HTCFG_CP_GPIOX)
#define HTCFG_CP_AFIO_PIN                         STRCAT2(AFIO_PIN_,      _HTCFG_CP_GPION)

#ifdef __cplusplus
}
#endif

#endif
