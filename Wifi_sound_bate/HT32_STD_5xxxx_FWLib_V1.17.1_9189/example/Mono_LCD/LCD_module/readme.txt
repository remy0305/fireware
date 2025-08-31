/**
 @page Mono_LCD_LCD_module

 @verbatim
 * @file    Mono_LCD/LCD_module/readme.txt
 * @version V1.00
 * @date    2020-01-06
 * @brief   Description of the LCD example.
 @endverbatim

@par Example Description:

This example shows how to use the LCD function to communicate with an LCD module and display images on the screen.

@par ESK-A3A31 Pin Assignment:
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ESK32-A3A31 LCM_8x33_PinAssignment(Pin21~41)
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SK        | CN_S12  CN_S11  CN_S10  CN_S9   CN_S8   CN_S7   CN_S6   CN_C7   CN_C6   CN_C5   CN_C4   CN_C3   CN_C2   CN_C1   CN_C0   CN_S5   CN_S4   CN_S3   CN_S2   CN_S1   CN_S0
57341     | M_S9    M_S8    M_S7    M_S6    M_S5    M_S18   M_S17   M_C3    M_C2    M_C7    M_C6    M_C5    M_C4    M_C1    M_C0    M_S16   M_S4    M_S3    M_S2    M_S1    M_S0
57352     | M_S5    M_S23   M_S22   M_S21   M_S20   M_S19   M_S18   M_C3    M_C2    M_C7    M_C6    M_C5    M_C4    M_C1    M_C0    M_S17   M_S16   M_S4    M_S3    M_S2    M_S1
LCD       | SEG13   SEG12   SEG11   SEG10   SEG9    SEG8    SEG7    COM8    COM7    COM6    COM5    COM4    COM3    COM2    COM1    SEG6    SEG5    SEG4    SEG3    SEG2    SEG1
A3A31_PIN | 21      22      23      24      25      26      27      28      29      30      31      32      33      34      35      36      37      38      39      40      41
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ESK32-A3A31 LCM_8x33_PinAssignment(Pin1~20)
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SK        | CN_S13  CN_S15  CN_S17  CN_S19  CN_S21  CN_S23  CN_S25  CN_S27  CN_S29  CN_S31  CN_S32  CN_S30  CN_S28  CN_S26  CN_S24  CN_S22  CN_S20  CN_S18  CN_S16  CN_S14
57352     | M_S6    M_S13   M_S15   M_S0    M_S31   M_S28   M_S24   M_S26   M_S10   M_S8    M_S7    M_S9    M_S27   M_S25   M_S11   M_S30   M_S32   M_S29   M_S12   M_S14
57341     | M_S10   M_S10   M_S10   M_S10   M_S10   M_S14   M_S12   M_S11   M_S23   M_S21   M_S20   M_S22   M_S24   M_S15   M_S13   M_S19   M_S10   M_S10   M_S10   M_S10
LCD       | SEG33   SEG32   SEG31   SEG30   SEG29   SEG28   SEG27   SEG26   SEG25   SEG24   SEG23   SEG22   SEG21   SEG20   SEG19   SEG18   SEG17   SEG16   SEG15   SEG14
A3A31_PIN | 1       2       3       4       5       6       7       8       9       10      11      12      13      14      15      16      17      18      19      20

@par Directory Contents:

- Mono_LCD/LCD_module/main.c               Main program
- Mono_LCD/LCD_module/ht32fxxxxx_it.c      Interrupt handlers

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- The expansion board such as ESK32-2x001 is required, refer to the user manual for the jumper settings.
- The LCD module such as ESK32-A3A31 is required, refer to the user manual for the jumper settings.

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
