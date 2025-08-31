/**
 @page TM_PWM

 @verbatim
 * @file    TM/PWM/readme.txt
 * @version V2.00
 * @date    2020-08-05
 * @brief   Description of TM PWM example.
 @endverbatim

@par Example Description:

This example describes how to use TM to generate 1 ~ 4 channel PWM.

  TM configuration:
  - TM_PCLK = CK_AHB / HTCFG_PWM_TM_PRESCALER (pwm.h)
  - Counter reload = HTCFG_PWM_TM_PCLK / HTCFG_PWM_TM_PRESCALER / HTCFG_PWM_FREQ_HZ (ht32_board_config.h, pwm.h)
  - PWM frequency = HTCFG_PWM_FREQ_HZ (pwm.h)

@par Directory Contents:

- TM/PWM/main.c                                             Main program
- TM/PWM/ht32fxxxx_it.c                                     Interrupt handlers
- TM/PWM/pwm.c                                              The PWM function
- TM/PWM/pwm.h                                              The header file of PWM function

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The PWM will be output on the specify pins (refer to the ht32_board_config.h)

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
