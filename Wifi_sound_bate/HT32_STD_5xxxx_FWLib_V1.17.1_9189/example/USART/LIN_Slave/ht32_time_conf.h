/*********************************************************************************************************//**
 * @file    USART/LIN_Slave/ht32_time_conf.h
 * @version $Rev:: 8755         $
 * @date    $Date:: 2025-05-12 #$
 * @brief   The configuration of HT32 Time function.
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
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_TIME_CONF_H
#define __HT32_TIME_CONF_H

#include "ht32_board_config.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
/*
//<e0> Enable HT32 Time Function
//  <i> Provide "Time_GetTick()" and "Time_Dealy()" functions.

//  <o1> Timer Selection
//      <0=> BFTM0
//      <1=> BFTM1
//      <2=> SCTM0
//      <3=> SCTM1
//      <4=> SCTM2
//      <5=> SCTM3
//      <6=> PWM0
//      <7=> PWM1
//      <8=> PWM2
//      <9=> GPTM0
//      <10=> GPTM1
//      <11=> MCTM0

//  <h> Timer Clock Setting
//  </h>
//    <i> Timer Clock = (Core Clock) / (APB Peripheral Clock Prescaler)
//    <i> HTCFG_TIME_CLKSRC = _HTCFG_TIME_CORECLK / (2^HTCFG_TIME_PCLK_DIV)
//    <i> _HTCFG_TIME_CORECLK = LIBCFG_MAX_SPEED or HTCFG_TIME_CLK_MANUAL (selected by HTCFG_TIME_CLKSEL)

//  <o2> -- Core Clock Setting (CK_AHB)
//    <i> HTCFG_TIME_CLKSEL
//    <i> 0 = Default Maximum (LIBCFG_MAX_SPEED)
//    <i> 1 = Manual Input (HTCFG_TIME_CLK_MANUAL)
//       <0=> Default Maximum (LIBCFG_MAX_SPEED)
//       <1=> Manual Input (HTCFG_TIME_CLK_MANUAL)

//  <o3> -- Core Clock Manual Input (Hz)
//    <i> HTCFG_TIME_CLK_MANUAL
//    <i> Only meaningful when Core Clock Setting (HTCFG_TIME_CLKSEL) = Manual Input (1)

//  <o4> -- APB Peripheral Clock Prescaler
//    <i> HTCFG_TIME_PCLK_DIV
//       <0=> /1
//       <1=> /2
//       <2=> /4
//       <3=> /8

//  <o5> Time Tick (Hz, not applicable for BFTM) <1-1000000:100>
//    <i> Not applicable for BFTM, fixed TICKHZ to HTCFG_TIME_CLKSRC for BFTM.
*/
#if (1) // Enable HT32 Time Function
#define HTCFG_TIME_IPSEL                          (HTCFG_IPSEL)
#define HTCFG_TIME_CLKSEL                         (0)         // 0 = Default Maximum (LIBCFG_MAX_SPEED), 1 = Manual Input (HTCFG_TIME_CLKSRC)
#define HTCFG_TIME_CLK_MANUAL                     (20000000)  // Only meaningful when HTCFG_TIME_CLKSEL = 1 (Manual Input)
#define HTCFG_TIME_PCLK_DIV                       (0)         // 0 ~ 3. (/1, /2, /4, /8)
#define HTCFG_TIME_TICKHZ                         (1000)      // Hz, not applicable for BFTM, fixed TICKHZ to HTCFG_TIME_CLKSRC for BFTM
#define HTCFG_TIME_MULTIPLE                       (1)         // MUST be 1, 2, 4, 8. TICK = COUNT / MULTIPLE. Not applicable for BFTM.
/*

  Timer Clock = (Core Clock) / (APB Peripheral Clock Prescaler)
  HTCFG_TIME_CLKSRC = (_HTCFG_TIME_CORECLK) / (2^HTCFG_TIME_PCLK_DIV)
  where _HTCFG_TIME_CORECLK can be LIBCFG_MAX_SPEED or HTCFG_TIME_CLK_MANUAL (selected by HTCFG_TIME_CLKSEL)

  Tick Range: 0 ~ 2^32 / HTCFG_TIME_TICKHZ (maximum tick time)
  Interrupt Time: _HTCFG_TIME_OVERFLOW_VALUE / (HTCFG_TIME_TICKHZ * HTCFG_TIME_MULTIPLE) Second
  (Interrupt Time is not applicable for BFTM)

  Example: 32-bit BFTM with 48 MHz Timer Clock
    HTCFG_TIME_TICKHZ = HTCFG_TIME_CLKSRC = 48000000
    Tick Range: 0 ~ 2^32 / 48000000 = 0 ~ 89.478485 Second (maximum tick time, return to 0 every 89.478485 Second)
    BFTM do not use interrupt

  Example: 16-bit GPTM with 1 ms tick
    HTCFG_TIME_TICKHZ = 1000 (Hz)
    HTCFG_TIME_MULTIPLE = 1 (1 Timer Count = 1 Tick)
    Tick Range: 0 ~ 2^32 / 1000 = 0 ~ 4294967 Second = 0 ~ 49.7 Day (maximum tick time, return to 0 every 49.7 Day)
    Interrupt Time: 65536 / (1000 * 1) = 65.536 Second (Trigger interrupt every 65.536 Second)
*/
#endif
/*
//</e>
*/

#ifdef __cplusplus
}
#endif

#endif

