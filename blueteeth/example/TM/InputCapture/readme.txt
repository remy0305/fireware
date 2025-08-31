/**
 @page TM_InputCapture

 @verbatim
 * @file    TM/InputCapture/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of TM Input Capture example.
 @endverbatim

@par Example Description:

This example shows how to use the TM peripheral to measure the pulse width of an external signal.

  <PRE>
       |<          1 Hz            >|
                           |<2500us>|
                            ________                      ________
                           |        |                    |        |
   ... ____________________|        |____________________|        |_____ ...
         x    x    x    x    x    x    x    x    x  ...
                           ^        v
              Rising Capture        Falling Capture
              "StartValue"          "cap_value"

   Note: x is update event of the TM.
  </PRE>

The SCTM/PWM is set to output 2500 us (10/4000) high pulse every 1 second for test purpose.

The TM_PCLK frequency is set to the maximum CK_AHB (the Prescaler = 1).
TM is configured as Input Capture Mode: the external signals are connected to TM Channel n as an input pin.
The TM Channel Capture and Update Event interrupts are enabled.

In the TMn_IRQHandler routine:
- The TM update interrupt is used to deal with the counter overflow condition.
- The TM rising capture interrupt will store the capture value to global variable "StartValue".
- The TM falling capture interrupt will compute the measured pulse width count by the following formula.
  Pulse Width Count = (OverflowCounter * (CounterReload + 1)) - StartValue + Capture_value

If the UxART is connected to PC serial port and the channels capture pulse value are valid, the pulse width
timing will be printed on the terminal.

@par Directory Contents:

- TM/InputCapture/main.c                                    Main program
- TM/InputCapture/ht32fxxxx_it.c                            Interrupt handlers
- TM/InputCapture/ht32_board_config.h                       Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- Connect the PWM output to the TM Input Capture pins.
   - TM Input Capture: _HTCFG_CAP_GPIOX, _HTCFG_CAP_GPION
   - PWM Output: _HTCFG_PWM_GPIOX, _HTCFG_PWM_GPION
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word length = 8 Bits
  - One stop bit
  - No parity
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
