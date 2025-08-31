/*********************************************************************************************************//**
 * @file    Mono_LCD/LCD_module/lcd_ESK32_A3A31.h
 * @version $Rev:: 4461      $
 * @date    $Date:: 2020-01-06 #$
 * @brief   The header file of LCD_module.c.
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
#ifndef __LCD_ESK32_A3A31_H
#define __LCD_ESK32_A3A31_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef struct
{
  u8 RAM_Index;
  u8 BIT_Index;
} COM_SEG_Type;

typedef enum
{
  LCD_DIGIT_0 = 0,
  LCD_DIGIT_1,
  LCD_DIGIT_2,
  LCD_DIGIT_3,
  LCD_DIGIT_4,
  LCD_DIGIT_NONE
} LCD_DIGIT_ID_Enum;

typedef enum
{
  LCD_VOICE_LEVEL_OFF = 0,
  LCD_VOICE_LEVEL_1,
  LCD_VOICE_LEVEL_2,
  LCD_VOICE_LEVEL_3,
  LCD_VOICE_LEVEL_4,
  LCD_VOICE_LEVEL_5
} LCD_VOICE_LEVEL_Enum;

typedef enum
{
  LCD_RF_LEVEL_OFF = 0,
  LCD_RF_LEVEL_1,
  LCD_RF_LEVEL_2,
  LCD_RF_LEVEL_3
} LCD_RF_LEVEL_Enum;

typedef enum
{
  LCD_BAT_LEVEL_OFF = 0,
  LCD_BAT_LEVEL_1,
  LCD_BAT_LEVEL_2,
  LCD_BAT_LEVEL_3
} LCD_BAT_LEVEL_Enum;

typedef enum
{
  LCD_UNIT_DEGREE = 0,
  LCD_UNIT_PM = 1,
  LCD_UNIT_AM = 2,
  LCD_UNIT_uA = 1,
  LCD_UNIT_mA = 2,
  LCD_UNIT_mV = 3,
} LCD_UNIT_Enum;

typedef enum
{
  LCD_PIXEL_OFF = 0,
  LCD_PIXEL_ON = !LCD_PIXEL_OFF
} LCD_PIXEL_CONTROL_Enum;

typedef enum
{
  _7SEG_0 = 0,
  _7SEG_1,
  _7SEG_2,
  _7SEG_3,
  _7SEG_4,
  _7SEG_5,
  _7SEG_6,
  _7SEG_7,
  _7SEG_8,
  _7SEG_9,
  _7SEG_A,
  _7SEG_b,
  _7SEG_C,
  _7SEG_d,
  _7SEG_E,
  _7SEG_F,
  _7SEG_H,
  _7SEG_Minus,
  _7SEG_CodeEnd
} _7SEG_ID_Enum;

/* Exported constants --------------------------------------------------------------------------------------*/
extern const u8 TAB_7SEG[_7SEG_CodeEnd+1];

extern const COM_SEG_Type TAB_G1_DIGIT[4][7];
extern const COM_SEG_Type TAB_G1_Unit[3];
extern const COM_SEG_Type TAB_G1_Dot[3];
extern const COM_SEG_Type COM_SEG_G1_TimeDot;

extern const COM_SEG_Type TAB_G2_DIGIT[5][7];
extern const COM_SEG_Type TAB_G2_Unit[4];
extern const COM_SEG_Type TAB_G2_Dot[4];
extern const COM_SEG_Type COM_SEG_G2_TimeDot;

extern const COM_SEG_Type TAB_Voice_Level[6];

extern const COM_SEG_Type COM_SEG_BT;
extern const COM_SEG_Type COM_SEG_BT_UpStream;
extern const COM_SEG_Type COM_SEG_BT_DownStream;

extern const COM_SEG_Type TAB_RF_Level[3];
extern const COM_SEG_Type COM_SEG_RF_UpStream;
extern const COM_SEG_Type COM_SEG_RF_DownStream;

extern const COM_SEG_Type COM_SEG_BAT_Frame;
extern const COM_SEG_Type TAB_BAT_Level[3];

extern const COM_SEG_Type COM_SEG_HOLTEK;
extern const COM_SEG_Type COM_SEG_Minus;

extern const u8 LCD_Matrix_X_Size;
extern const u8 LCD_Matrix_Y_Size;

/* Exported macro ------------------------------------------------------------------------------------------*/
#define LCD_show_HoltekLogo(on_off)     LCD_PixelConfig(COM_SEG_HOLTEK, on_off)
#define LCD_show_BT(on_off)             LCD_PixelConfig(COM_SEG_BT, on_off)
#define LCD_show_BT_UpStream(on_off)    LCD_PixelConfig(COM_SEG_BT_UpStream, on_off)
#define LCD_show_BT_DownStream(on_off)  LCD_PixelConfig(COM_SEG_BT_DownStream, on_off)
#define LCD_show_RF_UpStream(on_off)    LCD_PixelConfig(COM_SEG_RF_UpStream, on_off)
#define LCD_show_RF_DownStream(on_off)  LCD_PixelConfig(COM_SEG_RF_DownStream, on_off)
#define LCD_show_BAT_Frame(on_off)      LCD_PixelConfig(COM_SEG_BAT_Frame, on_off)
#define LCD_show_Group1_TimeDot(on_off) LCD_PixelConfig(COM_SEG_G1_TimeDot, on_off)
#define LCD_show_Group2_TimeDot(on_off) LCD_PixelConfig(COM_SEG_G2_TimeDot, on_off)

/* Exported functions --------------------------------------------------------------------------------------*/
void LCD_Init_ESK32_A3A31(void);

void LCD_PixelConfig(COM_SEG_Type pixel, LCD_PIXEL_CONTROL_Enum on_off);
void LCD_show_Group1_number(LCD_DIGIT_ID_Enum digit_n, _7SEG_ID_Enum char_id);
void LCD_show_Group2_number(LCD_DIGIT_ID_Enum digit_n, _7SEG_ID_Enum char_id);
void LCD_show_VoiceConfig(LCD_VOICE_LEVEL_Enum level);
void LCD_show_RF_Level(LCD_RF_LEVEL_Enum level);
void LCD_show_BAT_Level(LCD_BAT_LEVEL_Enum level);
void LCD_show_Group1_Unit(LCD_UNIT_Enum unit_id);
void LCD_show_Group2_Unit(LCD_UNIT_Enum unit_id);
void LCD_show_Group1_Dot(LCD_DIGIT_ID_Enum digit_n);
void LCD_show_Group2_Dot(LCD_DIGIT_ID_Enum digit_n);
void LCD_show_Matrix(u8 X, u8 Y, LCD_PIXEL_CONTROL_Enum on_off);
void LCD_MatrixClear(u8 StartX, u8 StartY, u8 W, u8 H, LCD_PIXEL_CONTROL_Enum on_off);
void LCD_show_Picture(u8 StartX, u8 StartY, uc8 pPicture[]);
#ifdef __cplusplus
}
#endif

#endif
