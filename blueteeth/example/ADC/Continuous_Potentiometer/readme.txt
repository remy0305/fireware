/**
 @page ADC_Continuous_Potentiometer

 @verbatim
 * @file    ADC/Continuous_Potentiometer/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of ADC Continuous mode example.
 @endverbatim

@par Example Description:

This example shows how to use the ADC Continuous mode to measure the potentiometer level.

ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - Continuous mode, sequence length = 1
  - Set ADST = 0, sampling time = 1.5 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC
  - Set ADC conversion sequence 0 as channel n.
  - Set software trigger as ADC trigger source.
  - Enable ADC single-end of conversion interrupt.

The ADC result is copied to the "gPotentiometerLevel" by the ADC single-end interrupt. The ADC main routine
shows the "gPotentiometerLevel" value by printf(). If the UxART is connected to PC, the ADC result will be
printed on the terminal.

@par Directory Contents:

- ADC/Continuous_Potentiometer/main.c                       Main program
- ADC/Continuous_Potentiometer/ht32fxxxxx_nn_it.c           Interrupt handlers
- ADC/Continuous_Potentiometer/ht32_board_config.h          Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
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
