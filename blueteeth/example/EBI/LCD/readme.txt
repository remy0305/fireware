/**
 @page EBI_LCD

 @verbatim
 * @file    EBI/LCD/readme.txt
 * @version V1.00
 * @date    2014-06-30
 * @brief   Description of the EBI LCD example.
 @endverbatim

@par Example Description:

This example shows how to use the LCD functions to communicate with LCD by EBI Interface. For more information
, please refer to the "ebi_lcd.c" file and check the document of LCD driver. This example will show the text
as below and followed by a holtek whale logo picture on LCD.

<PRE>
"       Holtek       "
"     HT32 Series    "
"     LCD Example    "
</PRE>

@par Directory Contents:

- EBI/LCD/main.c               Main program
- EBI/LCD/ht32fxxxx_it.c       Interrupt handlers
- EBI/LCD/picture.h            picture data

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The expansion board such as ESK32-2x001 is required, refer to the user manual for the jumper settings.
- The LCD module such as ESK32-A2A31 is required, refer to the user manual for the jumper settings.
- This example requires external component on the expansion board but some development board (with the
  "USE_HT32XXXXXX_DVB" define) can not use with it directly. The extra jumper/wired connections may required
  to use this example.

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
