/**
 @page TM_UpdateEvent

 @verbatim
 * @file    TM/UpdateEvent/readme.txt
 * @version V2.00
 * @date    2020-07-24
 * @brief   Description of TM update event with interrupt example.
 @endverbatim

@par Example Description:

This example describes how to use TM to generate update event interrupt, for the time count or
delay purpose.

  TM configuration:
  - TM_PCLK = CK_AHB / 1 (Prescaler = 1)
  - Update Event frequency = TM_FREQ_HZ Hz (counter reload = TM_PCLK/TM_FREQ_HZ)
  - Enable Update Event interrupt

@par Directory Contents:

- TM/UpdateEvent/main.c                                     Main program
- TM/UpdateEvent/ht32fxxxx_it.c                             Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The LED 1 will be toggled every (TM_TIME_DELAY / TM_FREQ_HZ) second.

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
