/**
 @page Time_TimeFun

 @verbatim
 * @file    Time/TimeFun/readme.txt
 * @version V1.00
 * @date    2021-05-27
 * @brief   Description of Time function.
 @endverbatim

@par Example Description:

This example shows how to use the HT32 Time function to achieve delay, time measure, and timeout functions.

The HT32 Time provides three major functions, "Time_Init()", "Time_GetTick()", and "Time_Delay()". It uses
BFTM/SCTM/GPTM/PWM/MCTM to work as an up counter, with a global variable to take care 16-bit overflow
interrupt (except the 32-bit BFTM, it doesn't need variable and interrupt) to save the time tick value. The
time tick value can be read by the "Time_GetTick()" function, it also uses to do the delay mechanism.

<PRE>
  Configuration:
    The following setting in the file, "ht32fxxxxx_conf.h" (It also has an alternately one in user space,
    named "ht32_time_conf.h") shall be set by user.

    HTCFG_TIME_IPSEL      : Timer Selection (BFTM/SCTM/GPTM/PWM/MCTM), refer to the conf file for detailed.
    HTCFG_TIME_CLKSEL     : 0 for Default Maximum (LIBCFG_MAX_SPEED), 1 for Manual Input (HTCFG_TIME_CLKSRC).
    HTCFG_TIME_CLK_MANUAL : Manual Input of core clock, only meaningful when HTCFG_TIME_CLKSEL = 1.
    HTCFG_TIME_PCLK_DIV   : APB Peripheral Clock Prescaler 0, 1, 2, 3 (/1, /2, /4, /8).
                            The Timer Clock = Core Clock / (2^HTCFG_TIME_PCLK_DIV).
    HTCFG_TIME_TICKHZ     : Time Tick based on Hz. It is not applied to BFTM. The HTCFG_TIME_TICKHZ is fixed
                            to HTCFG_TIME_CLKSRC for BFTM.
    HTCFG_TIME_MULTIPLE   : Multiples of tick and timer count. Default = 1. Must be 1, 2, 4, 8.
                            TICK = COUNT / MULTIPLE

  Tick Range:
    0 ~ 2^32 / HTCFG_TIME_TICKHZ (maximum tick time)

  Interrupt Time:
    _HTCFG_TIME_OVERFLOW_VALUE / (HTCFG_TIME_TICKHZ * HTCFG_TIME_MULTIPLE) Second (not apply for BFTM)

  Example: 32-bit BFTM with 48 MHz Timer Clock
    HTCFG_TIME_TICKHZ = HTCFG_TIME_CLKSRC = 48000000
    Tick Range: 0 ~ 2^32 / 48000000 = 0 ~ 89.478485 Second (maximum tick time, return to 0 every 89.478485 Second)
    BFTM do not use interrupt

  Example: 16-bit GPTM with 1 ms tick
    HTCFG_TIME_TICKHZ = 1000 (Hz)
    HTCFG_TIME_MULTIPLE = 1 (1 Timer Count = 1 Tick)
    Tick Range: 0 ~ 2^32 / 1000 = 0 ~ 4294967 Second = 0 ~ 49.7 Day (maximum tick time, return to 0 every 49.7 Day)
    Interrupt Time: 65536 / (1000 * 4) = 16.384 Second (Trigger interrupt every 16.384 Second)
</PRE>

@par Directory Contents:

- Time/TimeFun/main.c                                       Main program
- Time/TimeFun/ht32fxxxxx_nn_it.c                           Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- It uses the LED1 to shows the related timing. You can use a logic analyzer to check the timing of each
  function.

@par Firmware Disclaimer Information

1. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
   proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
   other intellectual property laws.

2. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
   other than HOLTEK and the customer.

3. The program technical documentation, including the code, is provided "as is" and for customer reference
   only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
   the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
   the warranties of merchantability, satisfactory quality and fitness for a particular purpose.

 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 */
