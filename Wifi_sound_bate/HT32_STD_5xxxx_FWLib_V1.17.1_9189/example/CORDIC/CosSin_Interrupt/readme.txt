/**
 @page CORDIC_CosSin_Interrupt

 @verbatim
 * @file    CORDIC/CosSin_Interrupt/readme.txt
 * @version V2.00
 * @date    2024-09-23
 * @brief   Description of CORDIC Interrupt CosSin example.
 @endverbatim

@par Example Description:

This example shows how to configure CORDIC as interrupt mode to calculate cosine and sine.

In this example, the CORDIC peripheral is configured as below.
- cosine function, q1.31 format for both input and output data, and with 6 cycles of precision.
The input data provided to CORDIC processor are angles in radians divided by PI, in q1.31 format.
The output data are cosine and sine in q1.31 format.

For 6 cycles of precision, the maximal expected residual error of the calculated sines is 2^-19.

The calculated cosine and sine are stored in cosOutput and sinOutput variables.
The residual error of calculation results is verified, by comparing to reference values.

LED1 and LED2 is used to monitor the example status:
  - LED1 is ON when correct CORDIC cosine and sine results are calculated.
  - LED2 is ON when exceeding residual error on CORDIC results is detected or when there is an initialization error.

This example will display relevant information through printf().
If UxART is connected to a PC, relevant information results will be printed on the terminal.

@par Directory Contents:

- CORDIC/CosSin_Interrupt/main.c                          Main program
- CORDIC/CosSin_Interrupt/ht32fxxxxx_nn_it.c              Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
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
