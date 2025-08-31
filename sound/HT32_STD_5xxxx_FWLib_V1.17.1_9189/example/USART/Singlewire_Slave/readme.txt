/**
 @page USART_Singlewire_Slave

 @verbatim
 * @file    USART/Singlewire_Slave/readme.txt
 * @version V2.00
 * @date    2025-02-03
 * @brief   Description of USART/UART Single-wire example.
 @endverbatim

@par Example Description:

This example shows how to configure USART/UART in single-wire mode as slave.

The example flow is as follows:

After the reset and initialization, the process will wait to receive data and validate whether it matches
"0123456789". If the validation is successful, LED1, LED2, and LED3 will turn on; otherwise, they will turn
off. The Rx function will then be disabled, and "ABCDEFGHIJ" will be transmitted through the RTx pin. Once
the transmission is complete, the Rx function will be re-enabled, and the process of waiting for data will
be repeated.

@par Directory Contents:

- USART/Singlewire_Slave/main.c                          Main program
- USART/Singlewire_Slave/ht32fxxxxx_nn_it.c              Interrupt handlers
- USART/Singlewire_Slave/ht32_board_config.h             Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- This example uses open-drain mode, which requires an external pull-up resistor.

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
