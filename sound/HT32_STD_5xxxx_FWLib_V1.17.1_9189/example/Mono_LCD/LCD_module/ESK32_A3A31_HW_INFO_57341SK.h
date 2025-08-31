/*********************************************************************************************************//**
 * @file    Mono_LCD/LCD_module/ESK32_A3A31_HW_INFO_57341SK.h
 * @version $Rev:: 4461      $
 * @date    $Date:: 2020-01-06 #$
 * @brief   LCD parameters of 573xx.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __ESK32_A3A31_HW_INFO_57341SK_H
#define __ESK32_A3A31_HW_INFO_57341SK_H

#ifdef __cplusplus
 extern "C" {
#endif
/*
ESK32-A3A31 LCM_8x33_PinAssignment
SK        | CN_S12  CN_S11  CN_S10  CN_S9   CN_S8   CN_S7   CN_S6   CN_C7   CN_C6   CN_C5   CN_C4   CN_C3   CN_C2   CN_C1   CN_C0   CN_S5   CN_S4   CN_S3   CN_S2   CN_S1   CN_S0
57341     | M_S9    M_S8    M_S7    M_S6    M_S5    M_S18   M_S17   M_C3    M_C2    M_C7    M_C6    M_C5    M_C4    M_C1    M_C0    M_S16   M_S4    M_S3    M_S2    M_S1    M_S0
LCD       | SEG13   SEG12   SEG11   SEG10   SEG9    SEG8    SEG7    COM8    COM7    COM6    COM5    COM4    COM3    COM2    COM1    SEG6    SEG5    SEG4    SEG3    SEG2    SEG1
A3A31_PIN | 21      22      23      24      25      26      27      28      29      30      31      32      33      34      35      36      37      38      39      40      41

SK        | CN_S13  CN_S15  CN_S17  CN_S19  CN_S21  CN_S23  CN_S25  CN_S27  CN_S29  CN_S31  CN_S32  CN_S30  CN_S28  CN_S26  CN_S24  CN_S22  CN_S20  CN_S18  CN_S16  CN_S14
57341     | M_S10   M_S10   M_S10   M_S10   M_S10   M_S14   M_S12   M_S11   M_S23   M_S21   M_S20   M_S22   M_S24   M_S15   M_S13   M_S19   M_S10   M_S10   M_S10   M_S10
LCD       | SEG33   SEG32   SEG31   SEG30   SEG29   SEG28   SEG27   SEG26   SEG25   SEG24   SEG23   SEG22   SEG21   SEG20   SEG19   SEG18   SEG17   SEG16   SEG15   SEG14
A3A31_PIN | 1       2       3       4       5       6       7       8       9       10      11      12      13      14      15      16      17      18      19      20
*/

/* Settings ------------------------------------------------------------------------------------------------*/
#define _MATRIX_X_SIZE    11
#define _MATRIX_Y_SIZE    8

/* Exported macro ------------------------------------------------------------------------------------------*/
#define LCD_RAM_BIT(com,seg)    {((com*2)+(seg/32)),(seg%32)}

#define _1A             LCD_RAM_BIT(0,1)
#define _1B             LCD_RAM_BIT(1,1)
#define _1C             LCD_RAM_BIT(4,1)
#define _1D             LCD_RAM_BIT(3,1)
#define _1E             LCD_RAM_BIT(3,2)
#define _1F             LCD_RAM_BIT(1,2)
#define _1G             LCD_RAM_BIT(4,2)

#define _2A             LCD_RAM_BIT(0,0)
#define _2B             LCD_RAM_BIT(0,17)
#define _2C             LCD_RAM_BIT(4,17)
#define _2D             LCD_RAM_BIT(3,17)
#define _2E             LCD_RAM_BIT(4,0)
#define _2F             LCD_RAM_BIT(1,0)
#define _2G             LCD_RAM_BIT(1,17)

#define _3A             LCD_RAM_BIT(0,5)
#define _3B             LCD_RAM_BIT(1,6)
#define _3C             LCD_RAM_BIT(4,5)
#define _3D             LCD_RAM_BIT(3,5)
#define _3E             LCD_RAM_BIT(4,18)
#define _3F             LCD_RAM_BIT(0,18)
#define _3G             LCD_RAM_BIT(1,5)

#define _4A             LCD_RAM_BIT(0,7)
#define _4B             LCD_RAM_BIT(1,8)
#define _4C             LCD_RAM_BIT(4,7)
#define _4D             LCD_RAM_BIT(3,7)
#define _4E             LCD_RAM_BIT(4,6)
#define _4F             LCD_RAM_BIT(0,6)
#define _4G             LCD_RAM_BIT(1,7)

#define _5A             LCD_RAM_BIT(2,3)
#define _5B             LCD_RAM_BIT(7,2)
#define _5C             LCD_RAM_BIT(6,2)
#define _5D             LCD_RAM_BIT(5,2)
#define _5E             LCD_RAM_BIT(6,4)
#define _5F             LCD_RAM_BIT(7,3)
#define _5G             LCD_RAM_BIT(6,3)

#define _6A             LCD_RAM_BIT(2,2)
#define _6B             LCD_RAM_BIT(2,1)
#define _6C             LCD_RAM_BIT(6,0)
#define _6D             LCD_RAM_BIT(5,0)
#define _6E             LCD_RAM_BIT(6,1)
#define _6F             LCD_RAM_BIT(7,1)
#define _6G             LCD_RAM_BIT(7,0)

#define _7A             LCD_RAM_BIT(2,0)
#define _7B             LCD_RAM_BIT(2,17)
#define _7C             LCD_RAM_BIT(6,18)
#define _7D             LCD_RAM_BIT(5,18)
#define _7E             LCD_RAM_BIT(6,17)
#define _7F             LCD_RAM_BIT(7,17)
#define _7G             LCD_RAM_BIT(7,18)

#define _8A             LCD_RAM_BIT(2,5)
#define _8B             LCD_RAM_BIT(2,6)
#define _8C             LCD_RAM_BIT(6,6)
#define _8D             LCD_RAM_BIT(5,6)
#define _8E             LCD_RAM_BIT(6,5)
#define _8F             LCD_RAM_BIT(2,18)
#define _8G             LCD_RAM_BIT(7,6)

#define _9A             LCD_RAM_BIT(2,8)
#define _9B             LCD_RAM_BIT(7,8)
#define _9C             LCD_RAM_BIT(6,8)
#define _9D             LCD_RAM_BIT(5,8)
#define _9E             LCD_RAM_BIT(6,7)
#define _9F             LCD_RAM_BIT(2,7)
#define _9G             LCD_RAM_BIT(7,7)

#define _V_OFF          LCD_RAM_BIT(5,4)
#define _V_ON           LCD_RAM_BIT(6,16)
#define _V_L1           LCD_RAM_BIT(7,4)
#define _V_L2           LCD_RAM_BIT(2,16)
#define _V_L3           LCD_RAM_BIT(7,16)
#define _V_L4           LCD_RAM_BIT(5,16)

#define _BT             LCD_RAM_BIT(1,3)
#define _BT_D           LCD_RAM_BIT(1,4)
#define _BT_U           LCD_RAM_BIT(4,3)

#define _RF_L1          LCD_RAM_BIT(0,3)
#define _RF_L2          LCD_RAM_BIT(0,4)
#define _RF_L3          LCD_RAM_BIT(0,16)
#define _RF_D           LCD_RAM_BIT(0,2)
#define _RF_U           LCD_RAM_BIT(1,16)

#define _BAT            LCD_RAM_BIT(0,9)
#define _BAT3           LCD_RAM_BIT(3,9)
#define _BAT2           LCD_RAM_BIT(4,9)
#define _BAT1           LCD_RAM_BIT(1,9)

#define _DEGREE_1       LCD_RAM_BIT(0,8)
#define _PM             LCD_RAM_BIT(4,8)
#define _AM             LCD_RAM_BIT(3,8)

#define _DEGREE_2       LCD_RAM_BIT(2,9)
#define _uA             LCD_RAM_BIT(7,9)
#define _mA             LCD_RAM_BIT(6,9)
#define _mV             LCD_RAM_BIT(5,9)

#define _S6_HOLTEK      LCD_RAM_BIT(2,4)
#define _S7_MINUS       LCD_RAM_BIT(5,3)
#define _S1_G1_TIME_Dot LCD_RAM_BIT(1,18)
#define _S2_G2_TIME_Dot LCD_RAM_BIT(7,5)

#define _S5_G1_Dot1     LCD_RAM_BIT(3,6)
#define _S4_G1_Dot2     LCD_RAM_BIT(3,18)
#define _S3_G1_Dot3     LCD_RAM_BIT(3,0)

#define _S11_G2_Dot1    LCD_RAM_BIT(5,7)
#define _S10_G2_Dot2    LCD_RAM_BIT(5,5)
#define _S9_G2_Dot3     LCD_RAM_BIT(5,17)
#define _S8_G2_Dot4     LCD_RAM_BIT(5,1)

#define _MATRIX_X_BIT_INDEX   {19,13,15,24,22,20,21,23,11,12,14} // LCD SEG
#define _MATRIX_Y_RAM_INDEX   {10,12,14,4,6,8,2,0} // LCD RAM index

#ifdef __cplusplus
}
#endif

#endif
