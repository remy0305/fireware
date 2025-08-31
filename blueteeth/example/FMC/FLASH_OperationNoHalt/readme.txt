/**
 @page FLASH_OperationNoHalt

 @verbatim
 * @file    FMC/FLASH_OperationNoHalt/readme.txt
 * @version V1.00
 * @date    2022-02-22
 * @brief   Description of FLASH OperationNoHalt example.
 @endverbatim

@par Example Description:

This example describes how to operation HT32 FLASH no halt.

When HT32 Flash doing erase or program, the CPU will be halted and cannot execute F/W.

Therefore, by placing the necessary function and vector in RAM (0x2000_0000),
the HT32 can still execute a small part of F/W during HT32 Flash doing erase or program,
and reduce the possibility of the halt to a limited extent.

@par Directory Contents:

- FMC/FLASH_OperationNoHalt/main.c               Main program
- FMC/FLASH_OperationNoHalt/ht32fxxxxx_nn_it.c   Interrupt handlers
- FMC/FLASH_OperationNoHalt/ram_fun.c            The RAM functions

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
