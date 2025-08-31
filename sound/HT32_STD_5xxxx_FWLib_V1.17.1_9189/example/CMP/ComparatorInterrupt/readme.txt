/**
 @page CMP_ComparatorInterrupt

 @verbatim
 * @file    CMP/ComparatorInterrupt/readme.txt
 * @version V2.00
 * @date    2020-08-20
 * @brief   Description of CMP example.
 @endverbatim

@par Example Description:

This example describes how to configure the CMP CP input to compare with internal reference voltage.

CMP Configuration:
- The comparator voltage reference power source come from the VDDA pin (with 6-bit or 8-bit scaler).
- CN0 = 31 * (VDDA - VSSA) / ((2 ^ n) - 1), n represent the bits of the scaler.

The CMP output rising / falling edge detect interrupt are turned on. In the CMP interrupt service routine:
- Turn on LED1 when CMPRF is set (rising edge).
- Turn off LED1 when CMPFF is set (falling edge).

@par Directory Contents:

- CMP/ComparatorInterrupt/main.c                            Main program
- CMP/ComparatorInterrupt/ht32fxxxx_it.c                    Interrupt handlers
- CMP/ComparatorInterrupt/ht32_board_config.h               Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Connect a signal to CP0 pin. Refer "ht32_board_config.h" for pin assignment.

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
