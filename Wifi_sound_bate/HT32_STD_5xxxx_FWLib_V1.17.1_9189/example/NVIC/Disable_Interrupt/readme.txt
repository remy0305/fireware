/**
 @page NVIC_Disable_Interrupt

 @verbatim
 * @file    NVIC/Disable_Interrupt/readme.txt
 * @version V1.00
 * @date    2021-01-19
 * @brief   Description of NVIC Disable Interrupt example.
 @endverbatim

@par Example Description:

This example shows how to use "__disable_irq()" and "__enable_irq()" to disable/enable interrupts.
It uses "CPSID I" and "CPSIE I" to set/clear PRIMASK.
  PRIMASK = 1: Disable all interrupts except NMI
  PRIMASK = 0: Enable interrupts

- Configure the LED1 of Starter Kit as output function.
- Configure the KEY1 of Starter Kit as input function.
- Configure the BFTM0 to trigger interrupt every 1 second. In the ISR, toggle the LED1.
- In the while loop of main() function, check the KEY1 and call the "__disable_irq()" or "__enable_irq()".
- When KEY1 is pressed and held, the LED1 stops toggling.

@par Directory Contents:

- NVIC/Disable_Interrupt/main.c                             Main program
- NVIC/Disable_Interrupt/ht32fxxxx_it.c                     Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- This example shows the result by LEDs.

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
