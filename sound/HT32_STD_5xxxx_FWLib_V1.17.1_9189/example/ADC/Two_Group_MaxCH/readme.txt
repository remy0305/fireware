/**
 @page ADC_Two_Group_MaxCH

 @verbatim
 * @file    ADC/Two_Group_MaxCH/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of ADC two group example.
 @endverbatim

@par Example Description:

This example shows how to use a software "two groups" concept to convert more than 8 channels of ADC at a
time. The HT32F5 series has only 8 conversion channel sequence which means the maximum conversion channel
number in each trigger is 8 channels. The example shows how to change the conversion list from group1 to
group2 and trigger the ADC to start again by the software when the conversion end interrupt occurred.

The example supports the following trigger and data moving mode. You can configure
them in the "adc_group.h" file.

    ADC_GROUP_TRIGGER_MODE        (0)   // 0: Trigger by software,  1: Trigger by Timer
    ADC_GROUP_DATA_MODE           (0)   // 0: Move ADC data by CPU, 1: Move ADC data by PDMA

@par Directory Contents:

- ADC/Two_Group_MaxCH/main.c                                Main program
- ADC/Two_Group_MaxCH/ht32fxxxx_it.c                        Interrupt handlers
- ADC/Two_Group_MaxCH/adc_group.h                           The header file of ADC Group
- ADC/Two_Group_MaxCH/ht32_board_config.h                   Board configuration file

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
