/**
 @page QSPI_Flash_Quad_Mode

 @verbatim
 * @file    QSPI/Flash_Quad_Mode/readme.txt
 * @version V2.00
 * @date    2020-07-27
 * @brief   Description of the QSPI_Flash example.
 @endverbatim

@par Example Description:

This example describes how to use the utilities SPI driver to communicate with MX25L6436F SPI flash by the
Quad mode.

The SPI is configured as master mode. The SPI clock is set to HCLK/2 MHz.

The test address of SPI flash is defined by the "FLASH_TEST_ADDR". If all the test are passed, LED1 ~ LED3
will be turned on.

Test Steps
  - Read the Flash ID from the SPI flash.
  - Set Quad Enable bit (QE = 1) and clear Block Protection bit by write the status register.
  - Read the Quad Enable bit and confirm it qual to 1.
  - Turn on the LED1 if tha above operations are OK.
  - Erase sector on the address "FLASH_TEST_ADDR".
  - Program the data of "gWrite_Buffer[]" into the address "FLASH_TEST_ADDR" of the flash by qual mode.
  - Read the Flash data to the variable, "gRead_Buffer[]" by qual read function.
  - Do the flash verification by compare the "gWrite_Buffer[]" and "gRead_Buffer[]", turn on the LED2 if
    verification is passed.
  - Erase sector again on the address "FLASH_TEST_ADDR".
  - Do the flash blank check (by qual read function), turn on the LED3 if the blank check is passed.

@par Directory Contents:

- QSPI/Flash_Quad_Mode/main.c                               Main program
- QSPI/Flash_Quad_Mode/ht32fxxxx_nn_it.c                    Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The expansion board such as ESK32-2x001A is required, refer to the user manual for the jumper settings.
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
