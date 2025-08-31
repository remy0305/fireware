/**
 @page SLED_ARGB_GetLEDNum

 @verbatim
 * @file    SLED/ARGB_GetLEDNum/readme.txt
 * @version V1.00
 * @date    2020-02-04
 * @brief   Description of Addressable LEDs get the number of LEDs.
 @endverbatim

@par Example Description:

This example describes how to get an addressable LED number of lamp beads and drive Specify the number of lights.

The example supports to change feedback mode timer method. You can configure

BFTM_MODE                      (1)   // 0: Timer by GPTM, 1: Timer by BFTM

@par Directory Contents:

- SLED/ARGB_GetLEDNum/main.c                          Main program
- SLED/ARGB_GetLEDNum/ht32f5xxxx_01_it.c              Interrupt handlers
- SLED/ARGB_GetLEDNum/ht32_board_config.h             Board configuration file

@par Hardware and Software Environment:

- Refer "ht32_board_config.h" for pin assignment.
- This example must prepare an ARGB LED(LG-3535FRGB-T12), and connect the data line to Starter Kit.

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
