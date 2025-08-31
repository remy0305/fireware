/**
 @page TM_PWMOut_PDMA_4CH

 @verbatim
 * @file    TM/PWMOut_PDMA_4CH/readme.txt
 * @version V2.00
 * @date    2021-06-10
 * @brief   Description of the MCTM/GPTM 4 Channels PWM Output with PDMA example.
 @endverbatim

@par Example Description:

This example describes how to use the MCTM/GPTM Update Event 1 PDMA request to change the channel 0 ~ 3
Capture/Compare Register (CHnCCR).

The PDMA moves 4 block (32-bit) each time when it triggered by timer, after 4 x 3 block have been moved,
it auto reload the address.

  <PRE>

   Reload     <800 kHz>
   100 %      /|    /|    /|    /|        /|    /|    /|    /|
    80 %     / |   / |   / |   / |       / |   / |   / |   / |          Timer
    60 %    /  |  /  |  /  |  /  |      /  |  /  |  /  |  /  |  /       Counter
    40 %   /   | /   | /   | /   |  ...    | /   | /   | /   | /   ...  Value
    20 %  /____|/____|/____|/____|_________|/____|/____|/____|/__       (CNTR)
                __    ___   ___             __    ___   ___
 TM CH0 _______|  |__|   |_|   |_         _|  |__|   |_|   |_      ...
                ___   __    ___             ___   __    ___
 TM CH1 _______|   |_|  |__|   |_         _|   |_|  |__|   |_      ...
                __    ___   __              __    ___   __
 TM CH2 _______|  |__|   |_|  |__         _|  |__|   |_|  |__      ...
                ___   __    __              ___   __    __
 TM CH3 _______|   |_|  |__|  |__         _|   |_|  |__|  |__      ...
          T    x     x     x               x     x     x
               D0    D1    D2      ...    D0    D1    D2           ...

        T: Timer Start, CHnCCH = 0
        x: Update Event trigger PDMA
        D0: CH0CCR = CCR_Buffer[0] = 60%
            CH1CCR = CCR_Buffer[1]
            CH2CCR = CCR_Buffer[2]
            CH3CCR = CCR_Buffer[3]
        D1: CH0CCR = CCR_Buffer[4]
            CH1CCR = CCR_Buffer[5]
            CH2CCR = CCR_Buffer[6]
            CH3CCR = CCR_Buffer[7]
        D2: CH0CCR = CCR_Buffer[8]
            CH1CCR = CCR_Buffer[9]
            CH2CCR = CCR_Buffer[10]
            CH3CCR = CCR_Buffer[11]

  </PRE>

MCTM/GPTM configuration:
  - TM_PCLK = CK_AHB / 1 (Prescaler = 1)
  - PWM frequency = 800 kHz (counter reload = TM_PCLK/800000)
  - Set channel 0 ~ 3 output as PWM mode 1
  - Enable compare register preload function
  - Enable trigger PDMA by update event function

PDMA configuration:
  - Source = "CCR_buffer[]"
  - Destination = MCTM/GPTM channel 0 Capture/Compare Register (HT_xxTM->CHnCCR)
  - Data width = 32-bit
  - Block length = 4
  - Block count = 3
  - Address modes: Source linear increment, destination circular increment, auto reload

@par Directory Contents:

- TM/PWMOut_PDMA_4CH/main.c                                 Main program
- TM/PWMOut_PDMA_4CH/ht32fxxxx_it.c                         Interrupt handlers
- TM/PWMOut_PDMA_4CH/ht32_board_config.h                    Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Connect the TM channel 0 ~ 3 to an oscilloscope or LA to monitor the waveform.

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
