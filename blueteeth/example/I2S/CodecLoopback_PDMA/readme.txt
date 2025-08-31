/**
 @page I2S_CodecLoopback_PDMA

 @verbatim
 * @file    I2S/CodecLoopback_PDMA/readme.txt
 * @version V1.00
 * @date    2014-06-30
 * @brief   Description of I2S CODEC Loopback PDMA example.
 @endverbatim

@par Example Description:

This example describes how to use I2S cooperating with PDMA to drive CODEC reading and playing voice.

@par Directory Contents:

- I2S/CodecLoopback_PDMA/main.c               Main program
- I2S/CodecLoopback_PDMA/ht32fxxxxx_nn_it.c   Interrupt handlers
- I2S/CodecLoopback_PDMA/i2cm.h               Header file of the I2C master driver.
- I2S/CodecLoopback_PDMA/wm8978.h             Header file of the WM8978 driver.

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The expansion board such as ESK32-21001 is required, refer to the user manual for the jumper settings.
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
