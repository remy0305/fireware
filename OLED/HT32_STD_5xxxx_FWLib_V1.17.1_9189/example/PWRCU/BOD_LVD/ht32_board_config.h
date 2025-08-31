/*********************************************************************************************************//**
 * @file    PWRCU/BOD_LVD/ht32_board_config.h
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
#if defined(USE_HT32F0006)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F0008)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_2V95)
#endif

#if defined(USE_HT32F50020_30)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F50220_30)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F50231_41)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F50343)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F52220_30)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F52231_41)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F52243_53)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F52331_41)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F52342_52)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F52344_54)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_2V95)
#endif

#if defined(USE_HT32F52357_67)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_2V95)
#endif

#if defined(USE_HT32F54231_41)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F54243_53)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F57331_41)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_2V95)
#endif

#if defined(USE_HT32F57342_52)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_2V95)
#endif

#if defined(USE_HT32F61141)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F61244_45)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F65230_40)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F65232)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F65233)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F50442_52)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F53242_52)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F50431_41)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F53231_41)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F52234_44)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_2V95)
#endif

#if defined(USE_HT32F61355_56_57)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V)
#endif

#if defined(USE_HT32F66242)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#if defined(USE_HT32F66246)
  #define HTCFG_PWRCU_LVDS    (PWRCU_LVDS_3V05)
#endif

#ifdef __cplusplus
}
#endif

#endif
