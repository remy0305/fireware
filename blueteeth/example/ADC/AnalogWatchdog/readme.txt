/**
 @page ADC_AnalogWatchdog

 @verbatim
 * @file    ADC/AnalogWatchdog/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of ADC Analog Watchdog example.
 @endverbatim

@par Example Description:

This example shows how to use the ADC Analog Watchdog to monitor the input voltage level of the ADC channel.

ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - Continuous mode, sequence length = 1
  - Set ADST = 0, sampling time = 1.5 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC
  - Set ADC conversion sequence 0 as channel n.
  - Set software trigger as ADC trigger source.
  - Enable Analog Watchdog function. Upper threshold = 3000, lower threshold = 1000.

The ADC interrupt will occur when the ADC channel's level is above 3000 or below 1000. The ADC interrupt
service routine will turn on/off LED1 or LED2 depending on the input voltage level of the ADC channel.

@par Directory Contents:

- ADC/AnalogWatchdog/main.c                                 Main program
- ADC/AnalogWatchdog/ht32fxxxxx_nn_it.c                     Interrupt handlers
- ADC/AnalogWatchdog/ht32_board_config.h                    Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- Adjust the potentiometer on the expansion board to change the input level and observe the LEDs.

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
