/**
 @page I2C_EEPROM

 @verbatim
 * @file    I2C/EEPROM/readme.txt
 * @version V1.01
 * @date    2019-12-25
 * @brief   Description of I2C EEPROM example.
 @endverbatim

@par Example Description:

This example describes how to use the I2C to communicate with the 24LC02 EEPROM.

The I2C is configured as the master mode to do the write/read operation with the 24LC02 EEPROM. This example
shows the result by the retarget function (print to UxART) to the terminal software.

More details about the behavior of 24LC02 EEPROM such as page write, acknowledge
polling and sequential read, please refer to the 24LC02 datasheet.

@par Directory Contents:

- I2C/EEPROM/main.c               Main program
- I2C/EEPROM/ht32fxxxx_it.c       Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The expansion board such as ESK32-2x001 is required, refer to the user manual for the jumper settings.
- This example requires external component on the expansion board but some development board (with the
  "USE_HT32XXXXXX_DVB" define) can not use with it directly. The extra jumper/wired connections may required
  to use this example.
- The device address of 24LC02 EEPROM is hard-wired as 0x51.

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
