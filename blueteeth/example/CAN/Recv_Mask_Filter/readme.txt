/**
 @page CAN_Recv_Mask_Filter

 @verbatim
 * @file    CAN/Recv_Mask_Filter/main.c
 * @version V1.00
 * @date    2024-08-13
 * @brief   This example describes how to receive CAN messages using specific mask filtering.
 @endverbatim

@par Example Description:

This example describes how to configure and use the CAN interface to receive messages from a CAN bus.
It continuously monitors three specific CAN IDs, applying a mask filter to specific bits, and displays the
received data when valid messages are detected.
The following CAN receive IDs are configured in this example:
  - CAN ID 0x540 (Extended ID), FIFO depth: 1 (1 * 8 = 8 byte)
    This ID uses an extended frame format and has a filtering mask that ignores bits 2 and 3 of the ID.
    Therefore, it can receive messages with IDs 0x540, 0x544, 0x548, and 0x54C.
  - CAN ID 0x541 (Standard ID), FIFO depth: 1 (1 * 8 = 8 byte)
    This ID uses a standard frame format and also ignores bits 2 and 3 of the ID.
    Therefore, it can receive messages with IDs 0x541, 0x545, 0x549, and 0x54D.
  - CAN ID 0x542 (Standard ID), FIFO depth: 20 (20 * 8 = 160 byte)
    Similar to the above, this ID uses a standard frame format and ignores bits 2 and 3 of the ID.
    Therefore, it can receive messages with IDs 0x542, 0x546, 0x54A, and 0x54E.

@par Directory Contents:

- CAN/Recv_Mask_Filter/main.c               Main program
- CAN/Recv_Mask_Filter/ht32fxxxxx_nn_it.c   Interrupt handlers
- CAN/Recv_Mask_Filter/ht32_board_config.h  Board configuration file
- CAN/Recv_Mask_Filter/ht32_can_config.h    CAN configuration file

@par Hardware and Software Environment:

- Requires a CAN bus setup with nodes transmitting messages with the IDs specified above.
- This example shows the result RS232.
- Connect a null-modem female/female RS232 cable between the COM1 DB9 connector and PC serial port.
  Hyperterminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - BaudRate = 115200 baud
  - flow control: None
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
