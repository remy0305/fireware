/**
 @page TM_PWM_Buzzer

 @verbatim
 * @file    TM/PWM_Buzzer/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of TM PWM output for buzzer example.
 @endverbatim

@par Example Description:

This example shows how to use the TM to drive the buzzer by PWM output.

Timer configuration:
  - TM_PCLK = CK_AHB / 4 (Prescaler = 4, defined by BEE_TM_PRE)
  - PWM reload    = TM_PCLK / uFrequency
  - PWM frequency = uFrequency (Example: 48 MHz / 4 / reload)
  - TM CHnO (HTCFG_BUZZER_CHN) is configured as PWM2 mode, compare match value = 33 % duty (BEE_DUTY).

  <PRE>

   Reload     < f  >
             /|   /|   /|   /|         /|   /|   /|         Timer
            / |  / |  / |  / |        / |  / |  / |         Counter
           /  | /  | /  | /  |  ...  /  | /  | /  | /  ...  Value
          /___|/___|/___|/___|______/___|/___|/___|/__      (CNTR)
             _    _    _    _                               _
    TM      | |  | |  | |  | |  ...                    ... | |  ...
    CHn   __|d|__|d|__|d|__|d|_     _______________________|d|__
              u    u    u    u          u    u    u
          <       uActive_ms       ><   uInActive_ms     >
          <------ Waveform of one single bee sound ------>

        f: uFrequency
        d: Fixed duty (setting by BEE_DUTY)
        u: Update Event ISR to process related count

  </PRE>

@par Directory Contents:

- TM/PWM_Buzzer/main.c                                      Main program
- TM/PWM_Buzzer/buzzer_pwm.c                                Buzzer function
- TM/PWM_Buzzer/buzzer_pwm.h                                Header file of buzzer function
- TM/PWM_Buzzer/ht32fxxxx_it.c                              Interrupt handlers
- TM/PWM_Buzzer/ht32_board_config.h                         Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Timer Channel is used as PWM output to drive the buzzer.

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
