/**
 @page TM_SinglePulseMode

 @verbatim
 * @file    TM/SinglePulseMode/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of TM single pulse mode example.
 @endverbatim

@par Example Description:

This example shows how to use the TM peripheral single pulse mode to generate output pulse after a edge of an
external signal (press the button).

  <PRE>
              ___________________
   KEY1                          |_________________________________________
          ...                                 ___                           ...
   TM CHn     _______________________________|   |_________________________
                                 ^           ^   ^
                                 s           |   |
                                 |<-   a   ->|   |
                                 |<-     b     ->|

        s: Press KEY1, Timer started by software
        a: 1.5 ms (2 ms * 0.75)
        b: 2 ms (500 Hz)

  </PRE>

Timer configuration:
  - TM_PCLK = (CK_AHB / 2)
  - PWM reload = TM_PCLK / 500, where 500 is defined by HTCFG_PLUSE_FREQ_HZ
  - PWM frequency = 500 Hz
  - TM CHnO (HTCFG_PULSE_CH) is configured as PWM2 mode, compare match value = (PWM reload * 0.75).
  - Enable Single Pulse Mode (set SMPSET field of the MDCFR register)

@par Directory Contents:

- TM/SinglePulseMode/main.c                                 Main program
- TM/SinglePulseMode/ht32fxxxx_it.c                         Interrupt handlers
- TM/SinglePulseMode/ht32_board_config.h                    Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- Connect the TM channel n and KEY1 pins to an oscilloscope or LA to check the waveform.
- Press KEY1 to start the TM.

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
