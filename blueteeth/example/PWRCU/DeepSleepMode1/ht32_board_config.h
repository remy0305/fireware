/*********************************************************************************************************//**
 * @file    PWRCU/DeepSleepMode1/ht32_board_config.h
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

#include "ht32.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#if (LIBCFG_LSE)
  // Device have LSE.
  #define EXAMPLE_RTC_LSE                         (1)
#endif

#if defined(USE_HT32F65240_DVB) || defined(USE_HT32F61245_SK) || defined(USE_HT32F65232_DVB) || defined(USE_HT32F65233_DVB) || defined(USE_HT32F66242_DVB) || defined(USE_HT32F66246_DVB)
  // 62540, 61245, 65232, 65233, 66242, 66246 SK/DVB did not have LSE.
  #undef EXAMPLE_RTC_LSE
  #define EXAMPLE_RTC_LSE                         (0)
#else
#endif


#ifdef __cplusplus
}
#endif

#endif
