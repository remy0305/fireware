/**
 @page CAN_Silent_Mode

 @verbatim
 * @file    CAN/Silent_Mode/main.c
 * @version V1.00
 * @date    2025-02-04
 * @brief   This example describes how to receive CAN messages in silent mode.
 @endverbatim

@par Example Description:

This example demonstrates how to configure and use the CAN interface to receive messages from a CAN bus.
The example continuously monitors a specific CAN ID and displays the received data when a valid message
is detected. The following CAN receive settings are used in this example:

CAN ID 0x540 (Extended ID), FIFO depth 1 (1 * 8 = 8 bytes).

@par Directory Contents:

- CAN/Silent_Mode/main.c               Main program
- CAN/Silent_Mode/ht32fxxxxx_nn_it.c   Interrupt handlers
- CAN/Silent_Mode/ht32_board_config.h  Board configuration file
- CAN/Silent_Mode/ht32_can_config.h    CAN configuration file

@par Hardware and Software Environment:

- Requires a CAN bus setup with nodes transmitting messages with ID 0x540.
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
