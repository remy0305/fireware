/**
 @page PDMA_SoftwareTrigger

 @verbatim
 * @file    PDMA/SoftwareTrigger/readme.txt
 * @version V2.00
 * @date    2022-10-20
 * @brief   Description of PDMA software trigger example.
 @endverbatim

@par Example Description:

This example shows how to use HT32 PDMA software trigger.

Different source/destination address mode is present. Notice that PDMA_FLAG_BE and PDMA_FLAG_HT
is not available during software trigger transfer. Only PDMA_FLAG_TC is used.

         Data Width   Source       Destination  Source/Destination Address Mode
         ===========  ===========  ===========  ===========
Test 1:   8-bit       Flash        SRAM         Linear increment / Linear decrement
Test 2:  16-bit       IP Register  SRAM         Fixed / Linear decrement
Test 3:  32-bit       SRAM         SRAM         Circular increment / Linear decrement

@par Directory Contents:

- PDMA/SoftwareTrigger/main.c              Main program
- PDMA/SoftwareTrigger/ht32fxxxxx_nn_it.c  Interrupt handlers

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
