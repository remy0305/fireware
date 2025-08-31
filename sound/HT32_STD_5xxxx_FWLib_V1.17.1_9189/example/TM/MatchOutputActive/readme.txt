/**
 @page TM_MatchOutputActive

 @verbatim
 * @file    TM/MatchOutputActive/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of TM output active on match mode example.
 @endverbatim

@par Example Description:

This example shows how to use the TM output active on match mode after timer start.

  <PRE>
              ___________________                     ____________________
   KEY1                          |___________________|
          ...                           __________________________________  ...
   TM CHn     _________________________|
                                 ^     ^
                      Timer Start|     |
                                 |<1ms>|
  </PRE>

The TM_PCLK frequency is set to the CK_AHB / 10 (the Prescaler = 10).

The compare value (CHnCCR) is TM_PCLK / 1000, so the TM channel n will output active level when the TM
is enabled and the time passed 1 ms.

@par Directory Contents:

- TM/MatchOutputActive/main.c                               Main program
- TM/MatchOutputActive/ht32fxxxx_it.c                       Interrupt handlers
- TM/MatchOutputActive/ht32_board_config.h                  Board configuration file

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
