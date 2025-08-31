/*********************************************************************************************************//**
 * @file    BMD31M090_HT32/display/main.c
 * @version V1.0.1
 * @date    2024-08-01
 * @brief   Main program.
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
#include "BMD31M090.h"
#include "Bitmap.h"

/* Private function prototypes -----------------------------------------------------------------------------*/
void test_drawString_6x8(void);
void test_drawString_8x16(void);
void test_drawString_drawChar_drawNum(void);
void test_drawPixel(void);
void test_drawFastHLine_drawFastVLine(void);
void test_drawBitmap(void);
void test_variousScroll(void);
void test_invertDisplay(void);
void test_dim(void);
static void __Delay_ms(vu32 count);

/* Global variables ----------------------------------------------------------------------------------------*/
uint8_t t = ' ';

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  /*
    !!! NOTICE !!!
    BMD31M090 Module I2C slave address should be one of the following values (7-bit Addressing Mode):
    (Please check the jumper on the back of the module, and set the corresponding I2C slave address)
    - BMD31M090_DEVICEADDR0       : 0x3C (Factory Default)
    - BMD31M090_DEVICEADDR1       : 0x3D
    - BMD31M090_CLKFREQ           : 400000
  */
  BMD31M090_Init(BMD31M090_DEVICEADDR0, BMD31M090_CLOCK_SPEED);

  /* Test Function: drawString to draw font(6x8) Hello World! */
  test_drawString_6x8();

  /* Test Function: drawString to draw font(8x16) Hello World! */
  test_drawString_8x16();

  /* Test Function: drawString, drawChar and drawNum */
  test_drawString_drawChar_drawNum();

  /* Test Function: drawPixel */
  test_drawPixel();

  /* Test Function: drawFastHLine and drawFastVLine */
  test_drawFastHLine_drawFastVLine();

  /* Test Function: drawBitMap to show BestModule_LOGO and NameBestModule_LOGO */
  test_drawBitmap();

  /* Test Function: Scroll function to scroll various directions */
  test_variousScroll();

  /* Test Function: invertDisplay to invert and restore display */
  test_invertDisplay();

  /* Test Function: dim to display */
  test_dim();

  while (1);
}

/*********************************************************************************************************//**
  * @brief  Test Function: drawString to draw font(6x8) Hello World!
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_drawString_6x8()
{
  uint8_t col, row;
  BMD31M090_clearDisplay();
  BMD31M090_display();

  BMD31M090_setFont(FontTable_6X8); // Set Font Type - 6X8 (Default Font Type : 8X16)

  col = (128 - (6 * sizeof("Hello World!"))) / 2;
  for (row=0; row<8; row++)
  {
    BMD31M090_drawString(col, row, (u8*)"Hello World!");
  }
  __Delay_ms(500);
}

/*********************************************************************************************************//**
  * @brief  Test Function: drawString to draw font(8x16) Hello World!
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_drawString_8x16()
{
  uint8_t col, row;
  BMD31M090_clearDisplay();
  BMD31M090_display();

  BMD31M090_setFont(FontTable_8X16); // Set Font Type : 8X16

  col = (128 - (8 * sizeof("Hello World!"))) / 2;
  for (row=0; row<8; row+=2)
  {
    BMD31M090_drawString(col, row, (u8*)"Hello World!");
  }
  __Delay_ms(500);
}

/*********************************************************************************************************//**
  * @brief  Test Function: drawString, drawChar and drawNum
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_drawString_drawChar_drawNum()
{
  BMD31M090_clearDisplay();
  BMD31M090_display();

  BMD31M090_drawString(16, BMD31M090_displayROW0, (u8*)"Best Modules");
  BMD31M090_drawString(8, BMD31M090_displayROW2, (u8*)"BMD31M090 TEST");
  /* Sequentially display ASCII ' ' (0x20/32) to ' ~' (0x7E/126) values for Font 6x8 & 8x16 */
  do
  {
    BMD31M090_setFont(FontTable_6X8);
    BMD31M090_drawString(0, BMD31M090_displayROW5, (u8*)"ASCII:");
    BMD31M090_drawString(63, BMD31M090_displayROW5, (u8*)"CODE:");
    BMD31M090_drawChar(48, BMD31M090_displayROW5, t);
    BMD31M090_drawNum(103, BMD31M090_displayROW5, t, 3);

    BMD31M090_setFont(FontTable_8X16);
    BMD31M090_drawString(0, BMD31M090_displayROW6, (u8*)"ASCII:");
    BMD31M090_drawString(63, BMD31M090_displayROW6, (u8*)"CODE:");
    BMD31M090_drawChar(48, BMD31M090_displayROW6, t);
    BMD31M090_drawNum(103, BMD31M090_displayROW6, t, 3);
    __Delay_ms(10);
  } while(++t < '~');
  t=' ';
}

/*********************************************************************************************************//**
  * @brief  Test Function: drawPixel
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_drawPixel()
{
  uint8_t col,row;
  BMD31M090_clearDisplay();
  for (col=0; col<128; col++)
  {
    for(row=0; row<64; row++)
    {
      BMD31M090_drawPixel(col, row, BMD31M090_pixelColor_WHITE);
    }
  }
  BMD31M090_display();
  __Delay_ms(500);

  for (col=0; col<128; col++)
  {
    for(row=0; row<32; row++)
    {
      BMD31M090_drawPixel(col, row, BMD31M090_pixelColor_BLACK);
    }
  }
  BMD31M090_display();
  __Delay_ms(500);

  for (col=0; col<128; col++)
  {
    for(row=0; row<64; row++)
    {
      BMD31M090_drawPixel(col, row, BMD31M090_pixelColor_INVERSE);
    }
  }
  BMD31M090_display();
  __Delay_ms(500);
}

/*********************************************************************************************************//**
  * @brief  Test Function: drawFastHLine and drawFastVLine
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_drawFastHLine_drawFastVLine()
{
  int8_t col, row;

  BMD31M090_clearDisplay();
  col = 112;
  for (row=0; row<64; row+=8)
  {
    BMD31M090_drawFastHLine(0, row, col, BMD31M090_pixelColor_WHITE);
    BMD31M090_drawFastVLine(col, row, 64 - row, BMD31M090_pixelColor_WHITE);
    col -= 14;
  }
  BMD31M090_display();
  __Delay_ms(500);

  BMD31M090_clearDisplay();
  col = 112;
  for (row=56; row>=0; row-=8)
  {
    BMD31M090_drawFastHLine(col, row, 128 - col, BMD31M090_pixelColor_WHITE);
    BMD31M090_drawFastVLine(col, row, 64 - row, BMD31M090_pixelColor_WHITE);
    col -= 14;
  }
  BMD31M090_display();
  __Delay_ms(500);
}

/*********************************************************************************************************//**
  * @brief  Test Function: drawBitMap to show BestModule_LOGO and NameBestModule_LOGO
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_drawBitmap()
{
  /*==========================================================
   |Using Image2LCD Software conversion, setting as bellow    |
   |1. Output file type: C array (*.c)                        |
   |2. Scan mode: Horizon Scan                                |
   |3. Bits Pixel: monochrome                                 |
   |4. Max Width and Height: 128 (Width) / 64 (Height)        |
   |5. Select "MSB First"                                     |
    ----------------------------------------------------------
   |Using LCD Assistant Software conversion, setting as bellow|
   |1. Byte orientation: Horizontal                           |
   |2. Size: According your image size                        |
   |3. Size endianness: Little                                |
   |4. Pixels/byte: 8                                         |
    ==========================================================*/

  BMD31M090_clearDisplay();
  BMD31M090_drawBitmap(0, 0, BestModule_LOGO, 128, 64, BMD31M090_pixelColor_WHITE);
  BMD31M090_display();
  __Delay_ms(300);
  BMD31M090_drawBitmap(0, 0, BestModule_LOGO, 128, 64, BMD31M090_pixelColor_BLACK);
  BMD31M090_display();
  __Delay_ms(300);
  BMD31M090_drawBitmap(0, 0, BestModule_LOGO, 128, 64, BMD31M090_pixelColor_INVERSE);
  BMD31M090_display();
  __Delay_ms(300);

  BMD31M090_clearDisplay();
  BMD31M090_drawBitmap(0, 0, BestModule_LOGOandName, 128, 64, BMD31M090_pixelColor_WHITE);
  BMD31M090_display();
  __Delay_ms(300);
  BMD31M090_drawBitmap(0, 0, BestModule_LOGOandName, 128, 64, BMD31M090_pixelColor_BLACK);
  BMD31M090_display();
  __Delay_ms(300);
  BMD31M090_drawBitmap(0, 0, BestModule_LOGOandName, 128, 64, BMD31M090_pixelColor_INVERSE);
  BMD31M090_display();
  __Delay_ms(300);
}

/*********************************************************************************************************//**
  * @brief  Test Function: Scroll function to scroll various directions
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_variousScroll()
{
  /* Scroll Function Test */
  uint8_t startrow = BMD31M090_displayROW0;
  uint8_t endrow = BMD31M090_displayROW7;

  BMD31M090_startScrollRight(startrow, endrow, BMD31M090_SCROLL_2FRAMES, BMD31M090_SCROLLV_NONE);
  __Delay_ms(500);
  BMD31M090_startScrollRight(startrow, endrow, BMD31M090_SCROLL_2FRAMES, BMD31M090_SCROLLV_TOP);
  __Delay_ms(500);
  BMD31M090_startScrollRight(startrow, endrow, BMD31M090_SCROLL_2FRAMES, BMD31M090_SCROLLV_BOTTOM);
  __Delay_ms(500);

  BMD31M090_startScrollLeft(startrow, endrow, BMD31M090_SCROLL_2FRAMES, BMD31M090_SCROLLV_NONE);
  __Delay_ms(500);
  BMD31M090_startScrollLeft(startrow, endrow, BMD31M090_SCROLL_2FRAMES, BMD31M090_SCROLLV_TOP);
  __Delay_ms(500);
  BMD31M090_startScrollLeft(startrow, endrow, BMD31M090_SCROLL_2FRAMES, BMD31M090_SCROLLV_BOTTOM);
  __Delay_ms(500);

  BMD31M090_stopScroll();

}

/*********************************************************************************************************//**
  * @brief  Test Function: invertDisplay to invert and restore display
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_invertDisplay()
{
  BMD31M090_invertDisplay(TRUE); // invert Display Mode:black-on-white
  __Delay_ms(500);
  BMD31M090_invertDisplay(FALSE); // normal Display Mode:white-on-black
  __Delay_ms(500);
  BMD31M090_invertDisplay(TRUE); // invert Display Mode:black-on-white
  __Delay_ms(500);
  BMD31M090_invertDisplay(FALSE); // normal Display Mode:white-on-black
  __Delay_ms(500);
}

/*********************************************************************************************************//**
  * @brief  Test Function: dim to display
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void test_dim()
{
  BMD31M090_dim(TRUE); // dim Mode:contrast-0x00
  __Delay_ms(500);
  BMD31M090_dim(FALSE); // normal Brightness Mode:contrast-0xCF
  __Delay_ms(500);
  BMD31M090_dim(TRUE); // dim Mode:contrast-0x00
  __Delay_ms(500);
  BMD31M090_dim(FALSE); // normal Brightness Mode:contrast-0xCF
  __Delay_ms(500);
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  delay millisecond function 
  * @param  count: delay count for loop
  * @retval None
  ***********************************************************************************************************/
static void __Delay_ms(vu32 count)
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}
