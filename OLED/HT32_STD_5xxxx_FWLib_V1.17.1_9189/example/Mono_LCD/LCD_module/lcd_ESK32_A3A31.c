/*********************************************************************************************************//**
 * @file    Mono_LCD/LCD_module/lcd_ESK32_A3A31.c
 * @version $Rev:: 4463      $
 * @date    $Date:: 2020-01-06 #$
 * @brief   The file provides firmware functions to LCD.
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32_lcd_board.h"
#include "lcd_ESK32_A3A31.h"

/* Private constants ---------------------------------------------------------------------------------------*/
#define _a 0x01  //    aaaaaa
#define _b 0x02  //    f    b
#define _c 0x04  //    f    b
#define _d 0x08  //    gggggg
#define _e 0x10  //    e    c
#define _f 0x20  //    e    c
#define _g 0x40  //    dddddd

const u8 TAB_7SEG[_7SEG_CodeEnd + 1] =
{
  /* 0 */ (_a | _b | _c | _d | _e | _f),
  /* 1 */ (_b | _c),
  /* 2 */ (_a | _b | _d | _e | _g),
  /* 3 */ (_a | _b | _c | _d | _g),
  /* 4 */ (_b | _c | _f | _g),
  /* 5 */ (_a | _c | _d | _f | _g),
  /* 6 */ (_a | _c | _d | _e | _f | _g),
  /* 7 */ (_a | _b | _c | _f),
  /* 8 */ (_a | _b | _c | _d | _e | _f | _g),
  /* 9 */ (_a | _b | _c | _d | _f | _g),
  /* A */ (_a | _b | _c | _e | _f | _g),
  /* b */ (_c | _d | _e | _f | _g),
  /* C */ (_a | _d | _e | _f),
  /* d */ (_b | _c | _d | _e | _g),
  /* E */ (_a | _d | _e | _f | _g),
  /* F */ (_a | _e | _f | _g),
  /* H */ (_b | _c | _e | _f | _g),
  /* - */ (_g)
};

const COM_SEG_Type TAB_G1_DIGIT[4][7] =
{
  {_4A,_4B,_4C,_4D,_4E,_4F,_4G},
  {_3A,_3B,_3C,_3D,_3E,_3F,_3G},
  {_2A,_2B,_2C,_2D,_2E,_2F,_2G},
  {_1A,_1B,_1C,_1D,_1E,_1F,_1G}
};
const COM_SEG_Type TAB_G1_Unit[3] = {_DEGREE_1, _PM, _AM};
const COM_SEG_Type TAB_G1_Dot[3] = {_S5_G1_Dot1, _S4_G1_Dot2, _S3_G1_Dot3};
const COM_SEG_Type COM_SEG_G1_TimeDot = _S1_G1_TIME_Dot;

const COM_SEG_Type TAB_G2_DIGIT[5][7] =
{
  {_9A,_9B,_9C,_9D,_9E,_9F,_9G},
  {_8A,_8B,_8C,_8D,_8E,_8F,_8G},
  {_7A,_7B,_7C,_7D,_7E,_7F,_7G},
  {_6A,_6B,_6C,_6D,_6E,_6F,_6G},
  {_5A,_5B,_5C,_5D,_5E,_5F,_5G}
};
const COM_SEG_Type TAB_G2_Unit[4] = {_DEGREE_2, _uA, _mA, _mV};
const COM_SEG_Type TAB_G2_Dot[4] = {_S11_G2_Dot1, _S10_G2_Dot2, _S9_G2_Dot3, _S8_G2_Dot4};
const COM_SEG_Type COM_SEG_G2_TimeDot = _S2_G2_TIME_Dot;

const COM_SEG_Type TAB_Voice_Level[6] = {_V_OFF, _V_ON, _V_L1, _V_L2, _V_L3, _V_L4};

const COM_SEG_Type COM_SEG_BT             = _BT;
const COM_SEG_Type COM_SEG_BT_UpStream    = _BT_U;
const COM_SEG_Type COM_SEG_BT_DownStream  = _BT_D;

const COM_SEG_Type TAB_RF_Level[3]        = {_RF_L1, _RF_L2, _RF_L3};
const COM_SEG_Type COM_SEG_RF_UpStream    = _RF_U;
const COM_SEG_Type COM_SEG_RF_DownStream  = _RF_D;

const COM_SEG_Type COM_SEG_BAT_Frame  = _BAT;
const COM_SEG_Type TAB_BAT_Level[3]   = {_BAT3, _BAT2, _BAT1};

const COM_SEG_Type COM_SEG_HOLTEK = _S6_HOLTEK;
const COM_SEG_Type COM_SEG_Minus  = _S7_MINUS;

const u8 LCD_Matrix_X_Size = _MATRIX_X_SIZE;
const u8 LCD_Matrix_Y_Size = _MATRIX_Y_SIZE;

const u8 TAB_MATRIX_X_BIT_INDEX[_MATRIX_X_SIZE] = _MATRIX_X_BIT_INDEX;
const u8 TAB_MATRIX_Y_RAM_INDEX[_MATRIX_Y_SIZE] = _MATRIX_Y_RAM_INDEX;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief Initialize LCD.
  * @retval None
  ***********************************************************************************************************/
void LCD_Init_ESK32_A3A31(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  LCD_InitTypeDef LCD_InitStructure;
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.LCDC          = 1;
  CKCUClock.Bit.LCDR          = 1;
  CKCUClock.Bit.AFIO          = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* For ESK32-A3A31 8 COM x 33 SEG, Please refer to ESK32_A3A31_HW_INFO_57xxxSK for pin assigment          */
  AFIO_GPxConfig(HTCFG_LCD_COM0_GPIO_ID, HTCFG_LCD_COM0_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM1_GPIO_ID, HTCFG_LCD_COM1_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM2_GPIO_ID, HTCFG_LCD_COM2_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM3_GPIO_ID, HTCFG_LCD_COM3_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM4_GPIO_ID, HTCFG_LCD_COM4_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM5_GPIO_ID, HTCFG_LCD_COM5_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM6_GPIO_ID, HTCFG_LCD_COM6_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM7_GPIO_ID, HTCFG_LCD_COM7_AFIO_PIN,   AFIO_FUN_LCD);

  AFIO_GPxConfig(HTCFG_LCD_SEG0_GPIO_ID,  HTCFG_LCD_SEG0_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG1_GPIO_ID,  HTCFG_LCD_SEG1_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG2_GPIO_ID,  HTCFG_LCD_SEG2_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG3_GPIO_ID,  HTCFG_LCD_SEG3_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG4_GPIO_ID,  HTCFG_LCD_SEG4_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG5_GPIO_ID,  HTCFG_LCD_SEG5_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG6_GPIO_ID,  HTCFG_LCD_SEG6_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG7_GPIO_ID,  HTCFG_LCD_SEG7_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG8_GPIO_ID,  HTCFG_LCD_SEG8_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG9_GPIO_ID,  HTCFG_LCD_SEG9_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG10_GPIO_ID, HTCFG_LCD_SEG10_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG11_GPIO_ID, HTCFG_LCD_SEG11_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG12_GPIO_ID, HTCFG_LCD_SEG12_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG13_GPIO_ID, HTCFG_LCD_SEG13_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG14_GPIO_ID, HTCFG_LCD_SEG14_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG15_GPIO_ID, HTCFG_LCD_SEG15_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG16_GPIO_ID, HTCFG_LCD_SEG16_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG17_GPIO_ID, HTCFG_LCD_SEG17_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG18_GPIO_ID, HTCFG_LCD_SEG18_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG19_GPIO_ID, HTCFG_LCD_SEG19_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG20_GPIO_ID, HTCFG_LCD_SEG20_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG21_GPIO_ID, HTCFG_LCD_SEG21_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG22_GPIO_ID, HTCFG_LCD_SEG22_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG23_GPIO_ID, HTCFG_LCD_SEG23_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG24_GPIO_ID, HTCFG_LCD_SEG24_AFIO_PIN, AFIO_FUN_LCD);
 #if (_MATRIX_X_SIZE == 20)
  AFIO_GPxConfig(HTCFG_LCD_SEG25_GPIO_ID, HTCFG_LCD_SEG25_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG26_GPIO_ID, HTCFG_LCD_SEG26_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG27_GPIO_ID, HTCFG_LCD_SEG27_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG28_GPIO_ID, HTCFG_LCD_SEG28_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG29_GPIO_ID, HTCFG_LCD_SEG29_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG30_GPIO_ID, HTCFG_LCD_SEG30_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG31_GPIO_ID, HTCFG_LCD_SEG31_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG32_GPIO_ID, HTCFG_LCD_SEG32_AFIO_PIN, AFIO_FUN_LCD);
  #endif

  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD control register.
  */
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);

  /* LCDCLK config                                                                                          */
  CKCU_LCDClockConfig(CKCU_LCDSRC_LSI);     /* Using internal 32 kHz RC oscillator clock. LCDCLK = 32 kHz.  */

  /* LCD initialization                                                                                     */
  /* Frame rate = LCDCLK / (LCD_Divider_25 * LCD_Prescaler_4) * duty                                        */
  /*            =  32000 / (25 * 4) * 1/8                                                                   */
  /*            =  40 Hz                                                                                    */
  LCD_InitStructure.LCD_Divider = LCD_Divider_25;
  LCD_InitStructure.LCD_Prescaler = LCD_Prescaler_4;
  LCD_InitStructure.LCD_Duty = LCD_Duty_1_8;
  LCD_InitStructure.LCD_Bias = LCD_Bias_1_4;
  LCD_InitStructure.LCD_VoltageSource = LCD_VoltageSource_Internal;
  LCD_InitStructure.LCD_Waveform = LCD_Type_B_Waveform;
  LCD_DriverInit(&LCD_InitStructure);

  /* Enable High Drive Mode                                                                                 */
  LCD_HighDriveConfig(LCD_HighDrive_Static);

  /* Increase LCD drive capability.                                                                         */
  LCD_HalfRLCmd(ENABLE);  /* Enable half of the RL(low value resistor).                                     */

  /* LCD Internal Charge Pump 3.25V                                                                         */
  LCD_ChargePumpConfig(LCD_ChargePump_3V25);

  /* Wait for charge pump ready                                                                             */
  while (LCD_GetFlagStatus(LCD_FLAG_RDY) == RESET);

  /* LCD Interrupt                                                                                          */
  LCD_ClearFlag(LCD_CLR_UDD | LCD_CLR_SOF);
  LCD_IntConfig(LCD_INT_UDD | LCD_INT_SOF, ENABLE);
  NVIC_EnableIRQ(LCD_IRQn);

  /* Enable LCD                                                                                             */
  LCD_Cmd(ENABLE);
}

/*********************************************************************************************************//**
  * @brief Pixel ON or OFF.
  * @param pixel  : defined by COM_SEG_Type structure
  * @param on_off : LCD_PIXEL_OFF, LCD_PIXEL_ON
  * @retval None
  ***********************************************************************************************************/
void LCD_PixelConfig(COM_SEG_Type pixel, LCD_PIXEL_CONTROL_Enum on_off)
{
  if (on_off)
    HT_LCD->RAM[pixel.RAM_Index] |= (u32)0x1 << pixel.BIT_Index;
  else
    HT_LCD->RAM[pixel.RAM_Index] &= ~((u32)0x1 << pixel.BIT_Index);
}

/*********************************************************************************************************//**
  * @brief Show char on specific digit in digits group 1.
  * @param digit_n : LCD_DIGIT_0, LCD_DIGIT_1, LCD_DIGIT_2, LCD_DIGIT_3
  * @param char_id : _7SEG_0 ~ _7SEG_9,
  *                  _7SEG_A, _7SEG_b, _7SEG_C, _7SEG_d, _7SEG_E, _7SEG_F, _7SEG_H, _7SEG_Minus
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Group1_number(LCD_DIGIT_ID_Enum digit_n, _7SEG_ID_Enum char_id)
{
  u8 code = TAB_7SEG[char_id];
  u8 i, mask = 0x1;

  if (digit_n <= LCD_DIGIT_3)
  {
    for (i = 0; i < 7; i++)
    {
      LCD_PixelConfig(TAB_G1_DIGIT[digit_n][i], (LCD_PIXEL_CONTROL_Enum)(code & mask));
      mask <<= 1;
    }
  }
}

/*********************************************************************************************************//**
  * @brief Show char on specific digit in digits group 2.
  * @param digit_n : LCD_DIGIT_0, LCD_DIGIT_1, LCD_DIGIT_2, LCD_DIGIT_3, LCD_DIGIT_4
  * @param char_id : _7SEG_0 ~ _7SEG_9,
  *                  _7SEG_A, _7SEG_b, _7SEG_C, _7SEG_d, _7SEG_E, _7SEG_F, _7SEG_H, _7SEG_Minus
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Group2_number(LCD_DIGIT_ID_Enum digit_n, _7SEG_ID_Enum char_id)
{
  u8 code = TAB_7SEG[char_id];
  u8 i, mask = 0x1;

  if (digit_n <= LCD_DIGIT_4)
  {
    for (i = 0; i < 7; i++)
    {
      LCD_PixelConfig(TAB_G2_DIGIT[digit_n][i], (LCD_PIXEL_CONTROL_Enum)(code & mask));
      mask <<= 1;
    }
  }
}

/*********************************************************************************************************//**
  * @brief Show Voice configuration.
  * @param level : LCD_VOICE_LEVEL_OFF, LCD_VOICE_LEVEL_1, LCD_VOICE_LEVEL_2, LCD_VOICE_LEVEL_3
  *                LCD_VOICE_LEVEL_4, LCD_VOICE_LEVEL_5
  * @retval None
  ***********************************************************************************************************/
void LCD_show_VoiceConfig(LCD_VOICE_LEVEL_Enum level)
{
  u32 i;

  if (level == 0)
  {
    LCD_PixelConfig(TAB_Voice_Level[0], LCD_PIXEL_ON);

    for (i = 1; i < 6; i++)
      LCD_PixelConfig(TAB_Voice_Level[i], LCD_PIXEL_OFF);
  }
  else
  {
    LCD_PixelConfig(TAB_Voice_Level[0], LCD_PIXEL_OFF);

    for (i = 1; i < 6; i++)
      LCD_PixelConfig(TAB_Voice_Level[i], (LCD_PIXEL_CONTROL_Enum)(i <= level));
  }
}

/*********************************************************************************************************//**
  * @brief Show RF signal level.
  * @param level : LCD_RF_LEVEL_OFF, LCD_RF_LEVEL_1, LCD_RF_LEVEL_2, LCD_RF_LEVEL_3
  * @retval None
  ***********************************************************************************************************/
void LCD_show_RF_Level(LCD_RF_LEVEL_Enum level)
{
  int i;
  for (i = 0; i < 3; i++)
    LCD_PixelConfig(TAB_RF_Level[i], (LCD_PIXEL_CONTROL_Enum)(i < level));
}

/*********************************************************************************************************//**
  * @brief Show Battery Volumn level.
  * @param level : LCD_BAT_LEVEL_OFF, LCD_BAT_LEVEL_1, LCD_BAT_LEVEL_2, LCD_BAT_LEVEL_3
  * @retval None
  ***********************************************************************************************************/
void LCD_show_BAT_Level(LCD_BAT_LEVEL_Enum level)
{
  int i;
  for (i = 0; i < 3; i++)
    LCD_PixelConfig(TAB_BAT_Level[i], (LCD_PIXEL_CONTROL_Enum)(i < level));
}

/*********************************************************************************************************//**
  * @brief Show the Unit of digits group 1.
  * @param unit_id : LCD_UNIT_DEGREE, LCD_UNIT_PM, LCD_UNIT_AM
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Group1_Unit(LCD_UNIT_Enum unit_id)
{
  int i;
  for (i = 0; i < 3; i++)
    LCD_PixelConfig(TAB_G1_Unit[i], (LCD_PIXEL_CONTROL_Enum)(i == unit_id));
}

/*********************************************************************************************************//**
  * @brief Show the Unit of digits group 2.
  * @param unit_id : LCD_UNIT_DEGREE, LCD_UNIT_uA, LCD_UNIT_mA, LCD_UNIT_mV
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Group2_Unit(LCD_UNIT_Enum unit_id)
{
  int i;
  for (i = 0; i < 4; i++)
    LCD_PixelConfig(TAB_G2_Unit[i], (LCD_PIXEL_CONTROL_Enum)(i == unit_id));
}

/*********************************************************************************************************//**
  * @brief Show the Dot of digits group 1.
  * @param digit_n : LCD_DIGIT_0, LCD_DIGIT_1, LCD_DIGIT_2
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Group1_Dot(LCD_DIGIT_ID_Enum digit_n)
{
  int i;
  for (i = 0; i < 3; i++)
    LCD_PixelConfig(TAB_G1_Dot[i], (LCD_PIXEL_CONTROL_Enum)(i == digit_n));
}

/*********************************************************************************************************//**
  * @brief Show the Dot of digits group 2.
  * @param digit_n : LCD_DIGIT_0, LCD_DIGIT_1, LCD_DIGIT_2, LCD_DIGIT_3
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Group2_Dot(LCD_DIGIT_ID_Enum digit_n)
{
  int i;
  for (i = 0; i < 4; i++)
    LCD_PixelConfig(TAB_G2_Dot[i], (LCD_PIXEL_CONTROL_Enum)(i == digit_n));
}

/*********************************************************************************************************//**
  * @brief Turn ON or turn OFF the point of Dot Matrix.
  * @param StartX : X position
  * @param StartY : Y position
  * @param on_off :
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Matrix(u8 StartX, u8 StartY, LCD_PIXEL_CONTROL_Enum on_off)
{
  u8 bit_index, ram_index;

  if (StartX >= _MATRIX_X_SIZE)
    StartX = _MATRIX_X_SIZE-1;

  if (StartY >= _MATRIX_Y_SIZE)
    StartY = _MATRIX_Y_SIZE-1;

  bit_index = TAB_MATRIX_X_BIT_INDEX[StartX];
  ram_index = TAB_MATRIX_Y_RAM_INDEX[StartY] + (bit_index >> 5);
  bit_index =  bit_index & 0x1F;

  if (on_off)
    HT_LCD->RAM[ram_index] |= (u32)0x1 << bit_index;
  else
    HT_LCD->RAM[ram_index] &= ~((u32)0x1 << bit_index);
}

/*********************************************************************************************************//**
  * @brief Turn ON or turn OFF the point of Dot Matrix.
  * @param StartX : X position
  * @param StartY : Y position
  * @param W : Width
  * @param H : Height
  * @param on_off :
  * @retval None
  ***********************************************************************************************************/
void LCD_MatrixClear(u8 StartX, u8 StartY, u8 W, u8 H, LCD_PIXEL_CONTROL_Enum on_off)
{
  u32 i;
  u8 x, y;

  x = StartX;
  y = StartY;
  i = (u32)W * H;

  while (i--)
  {
    LCD_show_Matrix(x, y++, on_off);

    if (y >= (StartY + H))
    {
      y = StartY;
      x++;
    }
  }
}

/*********************************************************************************************************//**
  * @brief Turn ON or turn OFF the point of Dot Matrix.
  * @param StartX : X position
  * @param StartY : Y position
  * @param pPicture : Picture
  * @retval None
  ***********************************************************************************************************/
void LCD_show_Picture(u8 StartX, u8 StartY, uc8 pPicture[])
{
  u8 W = pPicture[0];
  u8 H = pPicture[1];
  u8* pData = (u8*)&pPicture[2];
  u32 i;
  u8 d, x, y;

  x = StartX;
  y = StartY;
  i = (u32)W * H;
  d = *pData;
  while (i--)
  {
    LCD_show_Matrix(x, y++, (LCD_PIXEL_CONTROL_Enum)(d&0x1));
    LCD_SetUpdateDisplayRequest();
    d >>= 1;

    if (y >= (StartY + H))
    {
      pData++;
      d = *pData;
      y = StartY;
      x++;
    }
  }
}
