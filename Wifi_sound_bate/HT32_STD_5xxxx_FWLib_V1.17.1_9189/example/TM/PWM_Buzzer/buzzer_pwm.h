/*********************************************************************************************************//**
 * @file    buzzer_pwm.h
 * @version $Rev:: 5260         $
 * @date    $Date:: 2021-02-05 #$
 * @brief   The header file of buzzer function.
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
#ifndef __BUZZER_PWM_H
#define __BUZZER_PWM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#define BEE_TM_PRE                      (4)
#define BEE_SYS_CLK                     (LIBCFG_MAX_SPEED)      // Calculate with fix value (#define)
#define BEE_DUTY                        (40) // % duty

/*
#if 0 // Pin define example

  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     10
  #define  HTCFG_BUZZER_IPN                       MCTM1
  #define  HTCFG_BUZZER_CHN                       1
  #define  HTCFG_BUZZER_TM_REDEFINE               1  // Option, 1 for different X_IRQn/X__IRQHandler naming

#endif
*/

/* Exported functions --------------------------------------------------------------------------------------*/
void Buzzer_Init(u32 uFrequency);
void Buzzer_Start(u8 uBeeTimes, u16 uFrequency, u16 uActive_ms, u16 uInActive_ms);
u32 Buzzer_IsFinish(void);

#ifdef __cplusplus
}
#endif

#endif
