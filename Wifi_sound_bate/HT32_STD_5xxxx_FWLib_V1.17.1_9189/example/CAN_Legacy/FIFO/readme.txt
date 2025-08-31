/**
 @page CAN_Legacy_FIFO

 @verbatim
 * @file    CAN_Legacy/FIFO/readme.txt
 * @version V1.00
 * @date    2023-08-25
 * @brief   This example describes how to use CAN.
 @endverbatim

@par Example Description:

This example describes how to configure CAN and how to transmit/receive data.

The program flow will send a standard frame, ID 0x451, Data Field 0xD9 0x04. Using a CAN 
analyzer, transmit 8 ID 0x540 and 8 byte Data Field to MCU. The MCU will then modify the received 
frames into extended frames and send message back.

You can find the following table in the user interface of the CAN analyzer.
  <PRE>
  -------------------------------------------------------------------------------
  | Direction      | Frame ID | Format     | Type     | DLC | Data              |
  -------------------------------------------------------------------------------
  | MCU->Analyzer  | 0x541    | Data Frame | Standard | 2   | D9 04             |
  -------------------------------------------------------------------------------
  | Analyzer->MCU  | 0x540    | Data Frame | Standard | 3   | 11 22 33          |
  -------------------------------------------------------------------------------
  | MCU->Analyzer  | 0x541    | Data Frame | Extern   | 3   | 11 22 33          | (Loop back)
  -------------------------------------------------------------------------------
  | Analyzer->MCU  | 0x540    | Data Frame | Standard | 3   | AA BB CC DD EE FF |
  -------------------------------------------------------------------------------
  | MCU->Analyzer  | 0x541    | Data Frame | Extern   | 3   | AA BB CC DD EE FF | (Loop back)
  -------------------------------------------------------------------------------
  </PRE>

@par Directory Contents:

- CAN_Legacy/FIFO/main.c               Main program
- CAN_Legacy/FIFO/ht32fxxxxx_nn_it.c   Interrupt handlers
- CAN_Legacy/FIFO/can_api.c            CAN API
- CAN_Legacy/FIFO/can_api.h            CAN API handlers
- CAN_Legacy/FIFO/usertypedef.h        User typedef

@par Hardware and Software Environment:

- This example can be run on HT32 Series development board.
- This example requires the preparation of CAN analyzer equipment. For example: USBCANII.
- bitrate : 500K
- Receive ID  : 0x540, FIFO depth 16.
- Transmit ID : 0x541.

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
