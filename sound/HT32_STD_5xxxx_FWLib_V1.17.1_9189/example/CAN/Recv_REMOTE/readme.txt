/**
 @page CAN_Recv_REMOTE

 @verbatim
 * @file    CAN/Recv_REMOTE/main.c
 * @version V1.00
 * @date    2024-08-13
 * @brief   This example describes how to receive CAN remote frames and prepare data for transmission.
 @endverbatim

@par Example Description:

This example describes how to configure and use the CAN interface to receive remote frames from a
CAN bus. The example returns data frames upon receiving remote frames from two specific CAN IDs.
The following CAN receive IDs are used in this example:
  - CAN ID    0x540 (Standard ID), FIFO depth 1 (1 * 8 = 8 byte).
  - CAN ID 0x540540 (Extended ID), FIFO depth 1 (1 * 8 = 8 byte).

Additionally, the system allows the user to input a character via PC serial port. The received
character is used to fill the CAN message data, demonstrating real-time CAN message updates.

@par Directory Contents:

- CAN/Recv_REMOTE/main.c               Main program
- CAN/Recv_REMOTE/ht32fxxxxx_nn_it.c   Interrupt handlers
- CAN/Recv_REMOTE/ht32_board_config.h  Board configuration file
- CAN/Recv_REMOTE/ht32_can_config.h    CAN configuration file

@par Hardware and Software Environment:

- Requires a CAN bus setup with nodes transmitting messages with the IDs specified above.
- This example shows the result via RS232.
- Connect a null-modem female/female RS232 cable between the COM1 DB9 connector and PC serial port.
  Hyperterminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - BaudRate = 115200 baud
  - flow control: None
- LED1 on the starter kit indicate successful reception and validation of CAN messages.
- CAN bit rate: 500K

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
