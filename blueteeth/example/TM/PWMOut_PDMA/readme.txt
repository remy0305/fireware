/**
 @page TM_PWMOut_PDMA

 @verbatim
 * @file    TM/PWMOut_PDMA/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of the MCTM/GPTM PWM Output with PDMA example.
 @endverbatim

@par Example Description:

This example describes how to use the MCTM/GPTM Update Event 1 PDMA request to change the channel n
Capture/Compare Register (CHnCCR).

The PDMA moves one block (32-bit) each time when it triggered by timer, after 3 block have been moved,
it auto reload the address.

  <PRE>

   Reload     <2 kHz>
   100 %     /|   /|   /|   /|       /|   /|   /|   /|          Timer
    75 %    / |  / |  / |  / |      / |  / |  / |  / |          Counter
    50 %   /  | /  | /  | /  |  ...   | /  | /  | /  | /   ...  Value
    25 %  /___|/___|/___|/___|________|/___|/___|/___|/__       (CNTR)
               _    __   ___           _    __   ___
    TM        | |  |  | |   |   ...   | |  |  | |   |      ...
    CHn ______| |__|  |_|   |_       _| |__|  |_|   |_
          T   x    x    x    x        x    x    x    x
              D0   D1   D2   D0 ...   D0   D1   D2   D0

        T: Timer Start, CHnCCH = 0
        x: Update Event trigger PDMA
        D0: CHnCCR = CCR_Buffer[0]
        D1: CHnCCR = CCR_Buffer[1]
        D2: CHnCCR = CCR_Buffer[2]

  </PRE>

MCTM/GPTM configuration:
  - TM_PCLK = CK_AHB / 1 (Prescaler = 1)
  - PWM frequency = 2 kHz (counter reload = TM_PCLK/2000)
  - Set channel n output as PWM mode 1
  - Enable trigger PDMA by update event function

PDMA configuration:
  - Source = "CCR_buffer[]"
  - Destination = MCTM/GPTM channel n Capture/Compare Register (HT_xxTM->CHnCCR)
  - Data width = 32-bit
  - Block length = 1
  - Block count = 3
  - Address modes: Source linear increment, destination fixed, auto reload

@par Directory Contents:

- TM/PWMOut_PDMA/main.c                                     Main program
- TM/PWMOut_PDMA/ht32fxxxx_it.c                             Interrupt handlers
- TM/PWMOut_PDMA/ht32_board_config.h                        Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Connect the TM channel n to an oscilloscope or LA to monitor the waveform.

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
