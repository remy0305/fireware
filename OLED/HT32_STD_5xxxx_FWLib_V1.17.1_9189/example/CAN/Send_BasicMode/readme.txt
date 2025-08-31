/**
 @page CAN_Send_BasicMode

 @verbatim
 * @file    CAN/Send_BasicMode/main.c
 * @version V1.00
 * @date    2025-02-04
 * @brief   This example describes how to send CAN messages in basic mode.
 @endverbatim

@par Example Description:

This example describes how to configure and use the CAN interface for transmitting messages to a CAN bus by basic mode.
The example sends messages for a specific CAN ID and lights up an LED when the message is successfully transmitted.
The following CAN receive IDs is used in this example:
  - CAN ID 0x540 (Standard ID), FIFO depth 1 (1 * 8 = 8 byte).

@par Directory Contents:

- CAN/Send_BasicMode/main.c               Main program
- CAN/Send_BasicMode/ht32fxxxxx_nn_it.c   Interrupt handlers
- CAN/Send_BasicMode/ht32_board_config.h  Board configuration file
- CAN/Send_BasicMode/ht32_can_config.h    CAN configuration file

@par Hardware and Software Environment:

- Requires a CAN bus setup with nodes transmitting messages with the IDs specified above.
- LED1 on the starter kit indicates successful transmission of CAN messages.
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
