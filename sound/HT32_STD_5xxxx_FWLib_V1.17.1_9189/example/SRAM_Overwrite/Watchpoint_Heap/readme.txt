/**
 @page SRAM_Overwrite_Watchpoint_Heap

 @verbatim
 * @file    SRAM_Overwrite/Watchpoint_Heap/readme.txt
 * @version V1.00
 * @date    2023-01-09
 * @brief   Description of heap overwrite example.
 @endverbatim

@par Example Description:

This example describes how to debug the condition of SRAM overwrite by setting the __HT_check_heap
watchpoint ("BS Write __HT_check_heap, 2" in "HT32FXxxxx_01_DebugSupport.ini").

@par Directory Contents:

- SRAM_Overwrite/Watchpoint_Heap/main.c               Main program
- SRAM_Overwrite/Watchpoint_Heap/ht32fxxxx_it.c       Interrupt handlers

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
