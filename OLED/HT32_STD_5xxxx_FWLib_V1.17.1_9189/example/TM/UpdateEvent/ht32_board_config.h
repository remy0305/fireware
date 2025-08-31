/*********************************************************************************************************//**
 * @file    TM/UpdateEvent/ht32_board_config.h
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
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
#if defined(USE_HT32F50030_SK) || defined(USE_HT32F52244_SK)
  #define  HTCFG_TM_IPN                           SCTM0
#else
  #define  HTCFG_TM_IPN                           GPTM0
#endif

#if (LIBCFG_MAX_SPEED > 60000000)
  #define  HTCFG_TIMER_PRESCALER                  (2)
#else
  #define  HTCFG_TIMER_PRESCALER                  (1)
#endif

#define HTCFG_PULSE_SYS_CLK                       (LIBCFG_MAX_SPEED)

#define HTCFG_TM_IRQn                             STRCAT2(HTCFG_TM_IPN,  _IRQn)
#define HTCFG_TM_IRQHandler                       STRCAT2(HTCFG_TM_IPN,  _IRQHandler)

#define HTCFG_TM_PORT                             STRCAT2(HT_,           HTCFG_TM_IPN)

#ifdef __cplusplus
}
#endif

#endif
