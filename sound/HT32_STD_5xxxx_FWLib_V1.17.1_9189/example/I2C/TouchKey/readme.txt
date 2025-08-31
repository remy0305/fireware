/**
 @page I2C_TouchKey

 @verbatim
 * @file    I2C/TouchKey/readme.txt
 * @version V1.00
 * @date    2014-06-30
 * @brief   Description of I2C TouchKey example.
 @endverbatim

@par Example Description:

This example describes how to use the I2C to communicate with the BS8112A touch key IC.
The I2C is configured as the master mode to do the write/read operation with the touch key IC.
This example shows the result by the retarget function (print to UxART) to the terminal software.

@par Directory Contents:

- I2C/TouchKey/main.c               Main program
- I2C/TouchKey/ht32fxxxx_it.c       Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The expansion board such as ESK32-2x001 is required, refer to the user manual for the jumper settings.
- This example requires external component on the expansion board but some development board (with the
  "USE_HT32XXXXXX_DVB" define) can not use with it directly. The extra jumper/wired connections may required
  to use this example.
- The device address of BS8112A is 0x50.
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word length = 8 Bits
  - One stop bit
  - No parity
  - BaudRate = 115200 baud
  - Flow control: None

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
