/**
 @page PGA_NonInverting

 @verbatim
 * @file    PGA/NonInverting/readme.txt
 * @version V2.00
 * @date    2020-08-20
 * @brief   Description of PGA NonInverting example.
 @endverbatim

@par Example Description:

This example shows how to configure the AFIO PGA, enable PGA function and demonstrate the non-inverting amplifier.

@par Directory Contents:

- PGA/NonInverting/main.c                            Main program
- PGA/NonInverting/ht32fxxxx_it.c                    Interrupt handlers
- PGA/NonInverting/ht32_board_config.h               Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- Connect the negative input to ground and wait for the calibration to complete, which is indicated by LED1 turning off.
- Connect the negative input of PGA to ground, and connect the positive input of PGA to the voltage source that needs to be amplified.

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
