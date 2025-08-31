/**
 @page SPI_Slave SPI_Slave

 @verbatim
 * @file    SPI/Slave/readme.txt
 * @version V1.01
 * @date    2019-12-24
 * @brief   Description of SPI Slave example.
 @endverbatim

@par Example Description:

This example shows how to configure SPI as Slave mode. When Key1 is pressed, Slave prepares the data to be
transmitted, then set specify GPIO as low to inform the master to start the transmission. After the 8 or 4
data are received, the example shows the data by RS232.

Note: Ensure the Host and Slave have the same SPI FIFO depth to allow proper data transmission.

@par Directory Contents:

- SPI/Slave/main.c               Main program
- SPI/Slave/ht32fxxxxx_nn_it.c   Interrupt handlers

@par Hardware and Software Environment:

- Remember to connect SPI Master. Refer "ht32_board_config.h" for pin assignment.
- This example can be run on the HT32 Series development board.
- This example shows the result by RS232.
- Connect a null-modem female/female RS232 cable between the COM1 DB9 connector and PC serial port.
  Hyperterminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - BaudRate = 115200 baud
  - flow control: None
  
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
