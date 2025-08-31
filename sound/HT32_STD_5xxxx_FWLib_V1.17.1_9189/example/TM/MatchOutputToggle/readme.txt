/**
 @page TM_MatchOutputToggle

 @verbatim
 * @file    TM/MatchOutputToggle/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of TM output toggle on match mode example.
 @endverbatim

@par Example Description:

This example shows how to use the TM output toggle on match mode to output 4 different frequency.

The TM_PCLK frequency is set to CH_AHB / 2000 (Prescaler = 2000).

The counter reload is configured to max value 0xFFFF;

The channels delta compare match value as following:
- Channel 0 output frequency =  100 Hz, the "CH_DeltaValue[0]" = TM_PCLK /  100 / 2
- Channel 1 output frequency =  500 Hz, the "CH_DeltaValue[1]" = TM_PCLK /  500 / 2
- Channel 2 output frequency = 1000 Hz, the "CH_DeltaValue[2]" = TM_PCLK / 1000 / 2
- Channel 3 output frequency = 2000 Hz, the "CH_DeltaValue[3]" = TM_PCLK / 2000 / 2

The channel 0 ~ 3 are configured as Match Output Toggle mode and the compare match interrupts are enabled.
The CHnCCR value of each channel (for the next compare match) will be updated in the compare matched interrupt
service routine. The next CHnCCR = Current CHnCCR + "CH_DeltaValue[n]" (where n = 0 ~ 3).

@par Directory Contents:

- TM/MatchOutputToggle/main.c                               Main program
- TM/MatchOutputToggle/ht32fxxxx_it.c                       Interrupt handlers
- TM/MatchOutputToggle/ht32_board_config.h                  Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- Connect the TM CH0 ~ CH3 to an oscilloscope or LA to monitor the waveform.

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
