/**
 @page GPIO_PinLock

 @verbatim
 * @file    GPIO/PinLock/readme.txt
 * @version V1.00
 * @date    2023-03-02
 * @brief   Description of GPIO output example.
 @endverbatim

@par Example Description:

This example describes how to set GPIO Pin Lock.

In this example, the result is as follows:
PA1 is Locked,
PA1 GPIO Configuration Change invalid. ==> (Output -> Output) Mode, (Pull-Disable -> Pull-Disable)
: Toggle PA1 ten times

PA2 is unlocked,
PA2 GPIO Configuration Change valid.   ==> (Output -> Input) Mode, (Pull-Disable -> Pull-Up)
: PA2 keeps High Level

@par Directory Contents:

- GPIO/PinLock/main.c                                        Main program
- GPIO/PinLock/ht32fxxxx_it.c                                Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on HT32 Series development board.

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
