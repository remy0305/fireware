/**
 @page LEDC_7-SegmentDigitalDisplay

 @verbatim
 * @file    LEDC/7-SegmentDigitalDisplay/readme.txt
 * @version V1.00
 * @date    2021-07-14
 * @brief   Description of 7-Segment Digital Display.
 @endverbatim

@par Example Description:

This example describes how to use the LEDC to drive the 7-Segment Digital Display.The seven-segment
display will cycle through the numbers.

@par Directory Contents:

- LEDC/7-SegmentDigitalDisplay/main.c                       Main program
- LEDC/7-SegmentDigitalDisplay/ht32fxxxxx_nn_it.c           Interrupt handlers
- LEDC/7-SegmentDigitalDisplay/ht32_board_config.h          Board configuration file

@par Hardware and Software Environment:

- Refer "ht32_board_config.h" for pin assignment.
- Schematic diagram of 7-segment display:
                 a
              -------
              |     |
             f|     |b
              |  g  |
              -------
              |     |
             e|     |c
              |     |
              ------- .dp
                 d
- SEGx and 7-segment display:
   a:  Seg 4(0x10)
   b:  Seg 7(0x80)
   c:  Seg 2(0x04)
   d:  Seg 5(0x20)
   e:  Seg 3(0x08)
   f:  Seg 0(0x01)
   g:  Seg 6(0x40)
   dp: Seg 1(0x02)
- There are 4 7-segment displays on the SK, which be scanned by COM0~COM4.
- Each frame is 40Hz, and characters will be replaced after displaying for 1 second.
- Frame = (LSI/Prescaler) / (LEDC_DutyClockNumber * COM Number)
        = (32K/20) / (8*4)
        = 50 Hz

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
