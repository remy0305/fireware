/**
 @page TM_InternalTrigger

 @verbatim
 * @file    TM/InternalTrigger/readme.txt
 * @version V1.00
 * @date    2021-01-21
 * @brief   Describe how to internal trigger timer.
 @endverbatim

@par Example Description:

Master timer:
  Trigger the slave timer every 100 ms and toggle CHnO at the same time.

Slave timer:
  Output PWM 5 times.
  - PWM period = 10 ms
  - PWM duty = 10/3 ms = 3.33 ms

  <PRE>
                  <-          100ms       -><-        100ms           ->
                  _________________________                             _____________________
   Master TM  ___|                         |___________________________|
                 ^                         ^                           ^
                 Master timer Start.       Update event occurs, then   Update event occurs, then
                                           trigger slave timer.        trigger slave timer.
                                              _   _   _   _   _            _   _   _   _   _
   Slave TM   _______________________________| |_| |_| |_| |_| |__________| |_| |_| |_| |_| |____
                                           ^                                ^   ^
                                   Slave timer Start, Output 5 PWM,       Period: 10 ms
                                   it is triggered by master timer.       Duty Cycle: 3.33 ms
  </PRE>

@par Directory Contents:

- TM/InternalTrigger/main.c                                 Main program
- TM/InternalTrigger/ht32fxxxx_it.c                         Interrupt handlers
- TM/InternalTrigger/ht32_board_config.h                    Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.

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
