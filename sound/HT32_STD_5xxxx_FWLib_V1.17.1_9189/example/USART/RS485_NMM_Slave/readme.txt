/**
 @page USART_RS485_NMM_Slave

 @verbatim
 * @file    USART/RS485_NMM_Slave/readme.txt
 * @version V1.00
 * @date    2021-05-26
 * @brief   Description of USART RS485 NMM mode with interrupt example.
 @endverbatim

@par Example Description:

This example shows how to configure USART as RS485 NMM mode with interrupt to send and receive data.

<PRE>
  How to test:

  ======================                        ======================
  =    RS485 Master    =                        =     RS485 Slave    =
  = (PC terminal tool) =                        =     (HT32 MCU)     =
  ======================                        ======================
      ADDR[0] 0x32 (P=1)        ---->>>>                                guSlaveState = RS485_STATE_ADDRESSED
                                <<<<----        ADDR[0] 0x31 (P=1)      (Option, ENABLE_ADDRESS_RESPONSE = 1)
                                <<<<----        HELLO[n]     (P=0)      (Option, ENABLE_HELLO_STR = 1)
      DATA[5]      (P=0)        ---->>>>
                                <<<<----        ADDR[0] 0x31 (P=1)      (Option, ENABLE_TX_ADDRESS = 1)
                                <<<<----        DATA[5]      (P=1)      (Loopback data for test)

      ADDR[0] 0x35 (P=1)        ---->>>>                                guSlaveState = RS485_STATE_IDLE
      DATA[n]      (P=0)        ---->>>>                                Note1

            ...                   ...                   ...

      ADDR[0] 0x32 (P=1)        ---->>>>                                guSlaveState = RS485_STATE_ADDRESSED

            ...                   ...                   ...

    P=n: Parity Mark/Space (1/0)
    Note1: Required to receive the next address packet. Otherwise, you need reset the UART IP after received
           a unmatch address packet (Example: ADDR[0] 0x35).

    1. Send address packet from terminal with Parity Mark (high), Data=HTCFG_RS485_SLAVE_ADDR (default 0x32).
    2. If ENABLE_ADDRESS_RESPONSE = 1, MCU will send back the address packet with Parity Mark (high),
       Data =  HTCFG_RS485_MASTER_ADDR (default 0x31).
    3. If ENABLE_HELLO_STR = 1, MCU sends hello string as below.
       "RS485 Slave is addressed! Please change to Parity Space and enter 5 characters..."
    4. Send 5 byte data packet from terminal with the Parity Space (low).
    5. If ENABLE_TX_ADDRESS = 1, MCU sends the address packet first with Parity Mark (high).
    6. MCU loop back the data packet (received in step 4) to master with the Parity Space (low).
</PRE>

@par Directory Contents:

- USART/RS485_NMM_Slave/main.c                    Main program
- USART/RS485_NMM_Slave/ht32fxxxxx_nn_it.c        Interrupt handlers
- USART/RS485_NMM_Slave/ht32_board_config.h       Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word Length = 8 Bits
  - One Stop Bit
  - Parity Mark for address package, Parity Space for data packet
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
