/**
 @page TM_PWMInput

 @verbatim
 * @file    TM/PWMInput/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of GPTM PWM Input example.
 @endverbatim

@par Example Description:

This example shows how to use the GPTM peripheral to measure the frequency and duty cycle of an external signal.

  <PRE>
                             |<          2 kHz            >|
                                                  | <33%>  |
                     ________                      ________
                    |        |                    |        |
   ... _____________|        |____________________|        |_____ ...
                    ^        v                    ^
           TI1S1->STI        Falling Capture      Rising Capture
   Trigger TM Restart        CH0CCR               CH1CCR
           (CNTR = 0)                             > Channel 1 Capture interrupt:
                                                    Calculate the frequency and duty
  </PRE>

  - The GPTM_PCLK frequency is set to CK_AHB / TM_CAP_PRESCAELER.
  - The minimum frequency value to measure is (GPTM_PCLK / 65536) Hz.
  - GPTM is configured as PWM Input Mode: the external signal is connected to the GPTM Channel 1.
  - Calculate the frequency and the duty cycle by the TM CH1CC interrupt request (GPTMn_IRQHandler).
  - Frequency = GPTM_PCLK / (CH1CCR + 1)       (in Hz).
  - Duty Cycle = (CH0CCR + 1) / (CH1CCR + 1)   (in % used fix point 16.16 format)

Another TM Channel n is configured as PWM output with the 2 kHz / 33 % duty cycle, for the TM PWM Input
measurement. If the UxART is connected to PC serial port, the "wFrequency" and "wDutyCycle" will be printed
on terminal.

@par Directory Contents:

- TM/PWMInput/main.c                                        Main program
- TM/PWMInput/ht32fxxxx_it.c                                Interrupt handlers
- TM/PWMInput/ht32_board_config.h                           Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- Connect the external signal to the GPTM channel 1 (_HTCFG_CAP_GPIOX, _HTCFG_CAP_GPION).
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word length = 8 Bits
  - One stop bit
  - No parity
  - BaudRate = 115200 baud
  - Flow control: None

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
