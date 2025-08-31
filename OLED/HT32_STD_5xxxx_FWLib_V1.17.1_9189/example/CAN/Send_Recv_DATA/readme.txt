/**
 @page CAN_Send_Recv_DATA

 @verbatim
 * @file    CAN/Send_Recv_DATA/readme.txt
 * @version V1.00
 * @date    2023-08-25
 * @brief   This example describes how to use CAN.
 @endverbatim

@par Example Description:

This example describes how to configure CAN and how to transmit/receive data.
The example continuously monitors two specific CAN IDs 0x540 and 0x542, and stores the received
data in RAM buffers. Then, these two specific CAN IDs 0x541 and 0x543, loops back the received
data.

The following CAN receive IDs are used in this example:
  - CAN ID 0x540 (Extended ID), FIFO depth 1 (1 * 8 = 8 byte).
  - CAN ID 0x542 (Extended ID), FIFO depth 20 (20 * 8 = 160 byte).
  
The following CAN transmit IDs are used in this example:
  - CAN ID 0x541 (Extended ID), 8 bytes, loop back the data received by ID 0x540.
  - CAN ID 0x543 (Extended ID), 8 bytes, loop back the data received by ID 0x542.

You can find the following table in the user interface of the CAN analyzer.
  <PRE>
  -----------------------------------------------------------------------------------
  | Direction      | Frame ID | Format     | Type   | DLC | Data                    |
  -----------------------------------------------------------------------------------
  | Analyzer->MCU  | 0x540    | Data Frame | Extern | 8   | 11 22 33 44 55 66 77 88 |
  -----------------------------------------------------------------------------------
  | MCU->Analyzer  | 0x541    | Data Frame | Extern | 8   | 11 22 33 44 55 66 77 88 | (Loop back)
  -----------------------------------------------------------------------------------
  | Analyzer->MCU  | 0x542    | Data Frame | Extern | 8   | AA BB CC DD EE FF 00 11 |
  ----------------------------------------------------------------------------------|
  | MCU->Analyzer  | 0x543    | Data Frame | Extern | 8   | AA BB CC DD EE FF 00 11 | (Loop back)
  ----------------------------------------------------------------------------------|
  </PRE>

@par Directory Contents:

- CAN/Send_Recv_DATA/main.c               Main program
- CAN/Send_Recv_DATA/ht32fxxxxx_nn_it.c   Interrupt handlers
- CAN/Send_Recv_DATA/ht32_board_config.h  Board configuration file
- CAN/Send_Recv_DATA/ht32_can_config.h    CAN configuration file

@par Hardware and Software Environment:

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
