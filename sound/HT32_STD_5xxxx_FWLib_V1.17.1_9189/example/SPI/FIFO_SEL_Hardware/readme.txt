/**
 @page SPI_FIFO_SEL_Hardware

 @verbatim
 * @file    SPI/FIFO_SEL_Hardware/readme.txt
 * @version V1.01
 * @date    2020-08-21
 * @brief   Description of the SPI FIFO & SEL hardware control example.
 @endverbatim

@par Example Description:

This example describes how to configure SPI transmission by FIFO & SEL hardware control.

Transmission behavior implies as following:

This example configures SPI0 as master and SPI1 as slave, remember to set SEL as output mode
for slave select. Both SPIs are configured with 8 bits mode, FIFO mode with Tx & Rx FIFO depths
4, (PCLK_SPI/4) MHz transmission speed, TimeOut (PCLK_SPI * maximum).

Transmission by polling, Receiving by interrupt.
Transmission starts from SPI1 that data comes from SPI1_Buffer_Tx and the SPI0 FIFO receives the data.
When the RX FIFO trigger level (RXFTLS) reached 4 data, the SPI0_IRQHandler will be triggered interrupt
to move the data from RX FIFO to SPI0_Buffer_Rx.

In addition, the TimeOut(TOUT) interrupt is enabled after the SPI is initialized. The TOUT interrupt will be
triggered when the Rx FIFO level is not empty and the trigger level 4 is not reached within the timeout period.

This example jumps to ISR 3 times for each and totally 6 times after 12 data are sent and received,
the program will compare the received data to the transferred data to check on data validation.

@par Directory Contents:

- SPI/FIFO_SEL_Hardware/main.c                 Main program
- SPI/FIFO_SEL_Hardware/ht32fxxxxx_nn_it.c     Interrupt handlers

@par Hardware and Software Environment:

- Remember to connect SPI0 to SPI1 respectively. Refer "ht32_board_config.h" for pin assignment.
- This example shows the result by LED1 and LED2.
- This example can be run on HT32 Series development board.

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
