/*********************************************************************************************************//**
 * @file    BMD31M090_HT32/src/BMD31M090.c
 * @version V1.0.1
 * @date    2024-08-01
 * @brief   This file provides all BMD31M090 Lib functions.
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

/* Private macro -------------------------------------------------------------------------------------------*/
#if (CHECK_WIREn(BMD31M090_WIRE) == -1)
  #error "Error: BMD31M090_WIRE doesn't support the current WIRE number. Check ht32_board_config.h."
#endif

/* Global variables ----------------------------------------------------------------------------------------*/
uint32_t gBMD31M090_WIRE = BMD31M090_WIRE;

/* Private constants ---------------------------------------------------------------------------------------*/
static const unsigned char* _font;

/* Private function prototypes -----------------------------------------------------------------------------*/
static void _initI2CMaster(uint32_t i2c_clock);
static void setCommand(uint8_t command);
static void setData(uint8_t data);
static uint32_t setPow(uint8_t baseValue, uint8_t indexValue);

/* Private macro -------------------------------------------------------------------------------------------*/
#ifndef _swapValue_uint8_t
#define _swapValue_uint8_t(a, b)                                               \
  {                                                                            \
    uint8_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif

#define ssd1306_swap(a, b)                                                     \
  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))) ///< No-temp-var swap operation

/* Private variables ---------------------------------------------------------------------------------------*/
static uint8_t _deviceAddress ;    // device address initialized when begin method is called
static uint32_t _clkFrequency ;
static uint8_t _displayWidth  = BMD31M090_WIDTH;
static uint8_t _displayHeight = BMD31M090_HEIGHT;

static uint8_t _fontOffset = 2;
static uint8_t _fontWidth;
static uint8_t _fontHeight;
static uint8_t buffer[1024];


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  BMD31M090 module wire number select.
  * @param  wire_number: select wire number.
  * @retval BMD31M090_SUCCESS/BMD31M090_FAILURE
 ************************************************************************************************************/
BMD31M090_selStatus BMD31M090_selWire(uint32_t wire_number)
{
  if(CHECK_WIREn(wire_number) == -1)
  {
    return BMD31M090_FAILURE;
  }

  gBMD31M090_WIRE = wire_number;
  return BMD31M090_SUCCESS;
}

/*********************************************************************************************************//**
  * @brief  BMD31M090 Module Initial
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_Init(uint8_t i2c_addr, uint32_t i2c_clock)
{

  _deviceAddress = i2c_addr;
  _clkFrequency = i2c_clock;
  _initI2CMaster(_clkFrequency);

  setCommand(BMD31M090_SET_DISPLAYOFF);                       // 0xAE

  setCommand(BMD31M090_SET_DISPLAYCLOCKDIV);                  // 0xD5
  setCommand(0x80);                                 // The Suggested Ratio 0x80

  setCommand(BMD31M090_SET_MULTIPLEX);                        // 0xA8
  setCommand(_displayHeight - 1);                   // 0x3F - (64 -1)dec -> (0x3F)hex

  setCommand(BMD31M090_SET_DISPLAYOFFSET);                    // 0xD3
  setCommand(0x00);                                 // No Offset
  setCommand(BMD31M090_SET_STARTLINE | 0x0);                  // 0x40
  setCommand(BMD31M090_SET_CHARGEPUMP);                       // 0x8D
  setCommand(0x14);                                 // 0x14, Enable Charge Pump

  setCommand(BMD31M090_SET_ADDRESSINGMODE);                   // 0x20
  setCommand(0x00);                                 // Horizontal Address Mode
  setCommand(BMD31M090_SEGMENT_REMAP);                        // 0xA1
  setCommand(BMD31M090_COMSCAN_DIRECTION);                    // 0xC8

  setCommand(BMD31M090_SET_COMPINS);                          // 0xDA
  setCommand(0x12);                                 // COM Pins Hardware Configuration
  setCommand(BMD31M090_SET_CONTRAST);                         // 0x81
  setCommand(BMD31M090_NORMAL_CONTRAST);                      // 0xCF

  setCommand(BMD31M090_SET_VCOMDETECT);                       // 0xDB
  setCommand(0x40);

  setCommand(BMD31M090_SET_PRECHARGE);                        // 0xD9
  setCommand(0xF1);
  setCommand(BMD31M090_DISPLAYALLON_RESUME);                  // 0xA4
  setCommand(BMD31M090_SET_NORMALDISPLAY);                    // 0xA6
  setCommand(BMD31M090_DEACTIVATE_SCROLL);                    // 0x2E

  setCommand(BMD31M090_SET_DISPLAYON);                        // 0xAF

  BMD31M090_clearDisplay();
  BMD31M090_display();

  BMD31M090_setFont(FontTable_8X16);                // Default Font Type : 8 * 16

}

/*********************************************************************************************************//**
  * @brief  Clear contents of display buffer.
  *         set all pixels to off.
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_clearDisplay(void)
{
  unsigned char *p = buffer;
  uint16_t count = _displayWidth * ((_displayHeight + 7) / 8);
  while (count--) {
        *p++ = (unsigned char)0x00;
  }
}

/*********************************************************************************************************//**
  * @brief  Push data currently in RAM to Display.
  *         Drawing operations are not visible until this function is called. 
  *         Call after each graphics command, or after a whole set of graphics commands, 
  *         as best needed by one's own application.
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_display(void)
{
  unsigned char *ptr = buffer;
  uint16_t count = _displayWidth * ((_displayHeight + 7) / 8);
  
  setCommand(BMD31M090_SET_PAGEADDRESS);                    // Set Page Address
  setCommand(BMD31M090_SET_LOWCOLUMN);                      // Set Column Lower Address
  setCommand(BMD31M090_SET_HIGHCOLUMN);                     // Set Column Higher Address


  while (count--)
  {
    setData(*ptr++);
  }
}

/*********************************************************************************************************//**
  * @brief  Set/Clear/Invert a single pixel.
  * @param  x: Column of display, 0 at left to (_displayWidth - 1) at right.
  *         y: Row of display, 0 at left to (_displayHeight - 1) at right.
  *         pixelColor: set pixel color.
  *         @arg BMD31M090_pixelColor_BLACK
  *         @arg BMD31M090_pixelColor_WHITE
  *         @arg BMD31M090_pixelColor_INVERSE
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawPixel(uint8_t x, uint8_t y, uint8_t pixelColor)
{
  switch (pixelColor)
  {
    case BMD31M090_pixelColor_BLACK:
      buffer[x + (y / 8) * _displayWidth] &= ~(1 << (y & 7));
      break;

    case BMD31M090_pixelColor_WHITE:
      buffer[x + (y / 8) * _displayWidth] |= (1 << (y & 7));
      break;

    case BMD31M090_pixelColor_INVERSE:
      buffer[x + (y / 8) * _displayWidth] ^= (1 << (y & 7));
      break;

    default:
      /* BMD31M090 doesn't support colors other than black and white. */
      break;
  }
}

/*********************************************************************************************************//**
  * @brief  draw Line.
  * @param  x_Start : Start point x coordinate.
  *         y_Start : Start point y coordinate.
  *         x_End : End point x coordinate.
  *         y_End : End point y coordinate.
  *         pixelColor: set pixel color.
  *         @arg BMD31M090_pixelColor_BLACK
  *         @arg BMD31M090_pixelColor_WHITE
  *         @arg BMD31M090_pixelColor_INVERSE
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawLine(uint8_t x_Start, uint8_t y_Start, uint8_t x_End, uint8_t y_End, uint8_t pixelColor)
{
  uint8_t Steep = abs(y_End - y_Start) > abs(x_End - x_Start),i;
  int8_t yStep;
  int16_t errValue;
  uint8_t dx, dy;

  if (Steep)
  {
    _swapValue_uint8_t(x_Start, y_Start);
    _swapValue_uint8_t(x_End, y_End);
  }

  if (x_Start > x_End)
  {
    _swapValue_uint8_t(x_Start, x_End);
    _swapValue_uint8_t(y_Start, y_End);
  }

  dx = abs(x_End - x_Start);
  dy = abs(y_End - y_Start);

  errValue = dx / 2;

  if (y_Start < y_End)
  {
    yStep = 1;
  }
  else
  {
    yStep = -1;
  }

  for (i=x_Start; i <= x_End; i++)
  {
    if (Steep) 
    {
      BMD31M090_drawPixel(y_Start, i, pixelColor);
    }
    else
    {
      BMD31M090_drawPixel(i, y_Start, pixelColor);
    }
    errValue -= dy;
    if (errValue < 0)
    {
      y_Start += yStep;
      errValue += dx;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  draw a Horizontal Line.
  * @param  x: Column of display, 0 at left to (_display_width - 1) at right.
  *         y: Row of display, 0 at left to (_displayHeight - 1) at right.
  *         width : Width of Line, in pixels.
  *         pixelColor: set pixel color.
  *         @arg BMD31M090_pixelColor_BLACK
  *         @arg BMD31M090_pixelColor_WHITE
  *         @arg BMD31M090_pixelColor_INVERSE
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawFastHLine(uint8_t x, uint8_t y, uint8_t width, uint8_t pixelColor)
{
  BMD31M090_drawLine(x, y, (x + width - 1), y, pixelColor);
}

/*********************************************************************************************************//**
  * @brief  draw a Vertical Line.
  * @param  x: Column of display, 0 at left to (_display_width - 1) at right.
  *         y: Row of display, 0 at left to (_displayHeight - 1) at right.
  *         height : Height of Line, in pixels.
  *         pixelColor: set pixel color.
  *         @arg pixelColor_BLACK
  *         @arg pixelColor_WHITE
  *         @arg pixelColor_INVERSE
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawFastVLine(uint8_t x, uint8_t y, uint8_t height, uint8_t pixelColor)
{
  BMD31M090_drawLine(x, y, x, (y + height - 1), pixelColor);
}

/*********************************************************************************************************//**
  * @brief  draw Char.
  * @param  x: Column of display, 0 at left to (_display_width - 1) at right.
  *         page: Row page of display, 0 at top page to 7 at bottom page..
  *         chr : The char on FontTable.
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawChar(uint8_t x, uint8_t row, uint8_t chr)
{
  uint8_t  i, j, charPageNum;
  uint8_t pageAddr = 0;

  if(x > (_displayWidth-1))
  {
    x = 0;
    row = row + (_fontHeight/8);
  }

  if(chr < 32 || chr > 127)
  {
    chr = ' ';
  }

  /* Calculate how many pages a char need. The height is not a multiple of 8 (1 page), set page + 1. */
  charPageNum = (_fontHeight % 8) ? ((_fontHeight / 8) + 1) : (_fontHeight / 8);

  for (j = charPageNum; j>0; j--)
  {
    BMD31M090_setPixelRow(x, row + pageAddr);
    for(i=0; i<_fontWidth; i++)
    {
      setData(*(const unsigned char *)(&_font[(chr - 32) * (_fontWidth * ((_fontHeight % 8) ? ((_fontHeight / 8) + 1) : (_fontHeight / 8))) +
                                    _fontOffset + i + (_fontWidth * pageAddr)]));
    }
    pageAddr++;
  }
}

/*********************************************************************************************************//**
  * @brief  draw String.
  * @param  x: Column of display, 0 at left to (_display_width - 1) at right.
  *         page: Row page of display, 0 at top page to 7 at bottom page..
  *         str : The string on FontTable.
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawString(uint8_t x, uint8_t row, uint8_t *str)
{
  unsigned char j=0;
  while (str[j] != '\0')
  {
    BMD31M090_drawChar(x, row, str[j]);

    /* If it is judged that it exceeds the width of the display, set x = 0 and skip to the next display page */
    x += _fontWidth;
    if(x > (128 - _fontWidth))
    {
      x = 0;
      row += (_fontHeight % 8) ? ((_fontHeight / 8) + 1) : (_fontHeight / 8);
    }
    j++;
  }
}

/*********************************************************************************************************//**
  * @brief  draw Num.
  * @param  x: Column of display, 0 at left to (_display_width - 1) at right.
  *         page: Row page of display, 0 at top page to 7 at bottom page..
  *         num : The num on FontTable.
  *         numLen : The num Length.
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawNum(uint8_t x, uint8_t row, uint32_t num, uint8_t numLen)
{
  uint8_t t,temp;
  uint8_t enShow=0;
  for(t=0; t<numLen; t++)
  {
    /* One-digit, one-digit display                                                            */
    temp=(num / setPow(10, (numLen - t - 1))) % 10;

    if(enShow == 0 && t < (numLen - 1))
    {
      /* According the value of 'numLen',
         If the Highest digit number is 0 (or Highest and the second of topest, etc.), then show "space". */
      if(temp == 0)
      {
        BMD31M090_drawChar(x + (_fontWidth * t), row, ' ');
        continue;
      }
      else
      {
        enShow = 1; 
      }
    }
    /* Show the num                                                                            */
    BMD31M090_drawChar(x + (_fontWidth * t), row, (temp + '0'));
  }
}

/*********************************************************************************************************//**
  * @brief  draw BMP.
  * @param  x: Column of display, 0 at left to (_display_width - 1) at right.
  *         y: Row of display, 0 at left to (_displayHeight - 1) at right.
  *         Bitmap[]: Bitmap Name.
  *         w: Width of Bitmap in pixels
  *         h: Height of Bitmap in pixels
  *         pixelColor: set pixel color.
  *         @arg BMD31M090_pixelColor_BLACK
  *         @arg BMD31M090_pixelColor_WHITE
  *         @arg BMD31M090_pixelColor_INVERSE
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_drawBitmap(int8_t x, int8_t y, const uint8_t *Bitmap, uint8_t w, uint8_t h, uint8_t pixelColor)
{
  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t b = 0;
  int16_t j,i;

  for (j = 0; j < h; j++, y++)
  {
    for (i = 0; i < w; i++)
    {
      if (i & 7)
      {
        b <<= 1;
      }
      else
      {
        #if 1
        /* RAM-resident 1-bit image at the specified */
        b = Bitmap[(j * byteWidth) + (i / 8)];
        #else
        /* PROGMEM-resident 1-bit image at the specified */
        b = *(const unsigned char *)(&Bitmap[(j * byteWidth) + (i / 8)]);
        #endif
      }
      if (b & 0x80)
      {
        if (((x + i) >= 0) && ((x + i) < _displayWidth) && (y >= 0) && (y < _displayHeight))
        {
          BMD31M090_drawPixel(x + i, y, (pixelColor == BMD31M090_pixelColor_WHITE) ? BMD31M090_pixelColor_WHITE : 
                                                                (pixelColor == BMD31M090_pixelColor_BLACK) ? BMD31M090_pixelColor_BLACK : BMD31M090_pixelColor_INVERSE);
        }
      }
      else
      {
        if (((x + i) >= 0) && ((x + i) < _displayWidth) && (y >= 0) && (y < _displayHeight))
        {
          BMD31M090_drawPixel(x + i, y, (pixelColor == BMD31M090_pixelColor_WHITE) ? BMD31M090_pixelColor_BLACK : 
                                                                (pixelColor == BMD31M090_pixelColor_BLACK) ? BMD31M090_pixelColor_WHITE : BMD31M090_pixelColor_INVERSE);
        }
      }
    }
  }
}

/*********************************************************************************************************//**
  * @brief  start Right-handed Scroll.
  * @param  startPage: start scroll Page, 0 at top page to 7 at bottom page.
  *         endPage: end scroll Page, 0 at top page to 7 at bottom page.
  *         scrollSpeed: set scroll speed.
  *         @arg BMD31M090_SCROLL_2FRAMES
  *         @arg BMD31M090_SCROLL_3FRAMES
  *         @arg BMD31M090_SCROLL_4FRAMES
  *         @arg BMD31M090_SCROLL_5FRAMES
  *         @arg BMD31M090_SCROLL_25FRAMES
  *         @arg BMD31M090_SCROLL_64FRAMES
  *         @arg BMD31M090_SCROLL_128FRAMES
  *         @arg BMD31M090_SCROLL_256FRAMES
  *         scrollVDirection: set scroll vertical direction 
  *         @arg BMD31M090_SCROLLV_NONE
  *         @arg BMD31M090_SCROLLV_TOP
  *         @arg BMD31M090_SCROLLV_BOTTOM
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_startScrollRight(uint8_t startRow, uint8_t endRow, uint8_t scrollSpeed, uint8_t scrollVDirection)
{
  setCommand(BMD31M090_DEACTIVATE_SCROLL);                   // Must be deactivated before issuing this command (0x2E).

  switch (scrollVDirection)
  {
    case BMD31M090_SCROLLV_NONE:
      setCommand(BMD31M090_RIGHT_SCROLL);                    // 0x26, Right Horizontal Scroll
      setCommand(0x00);                            // A[7:0] Dummy Byte (Set as 00h)

      setCommand(startRow);                        // B[2:0] Define start page address
      setCommand(scrollSpeed);                     // C[2:0] Set time interval between each scroll step in terms of the frame frequency
      setCommand(endRow);                          // D[2:0] Define end page address

      setCommand(0x00);                            // E[7:0] Dummy Byte (Set as 00h)
      setCommand(0xFF);                            // F[7:0] Dummy Byte (Set as FFh)
      setCommand(BMD31M090_ACTIVATE_SCROLL);                 // 0x2F
      break;

    case BMD31M090_SCROLLV_TOP:
    case BMD31M090_SCROLLV_BOTTOM:
      setCommand(BMD31M090_SET_SCROLLAREA);                  // 0xA3, Set Vertical Scroll Area
      setCommand(0x00);                            // Set No. of rows in top fixed area
      setCommand(_displayHeight);                  // Set No. of rows in scroll area (0-63)

      setCommand(BMD31M090_RIGHTDIAGONAL_SCROLL);            // 0x29, Vertical and Right Horizontal Scroll
      setCommand(0x00);                            // A[7:0] Dummy Byte (Set as 00h)

      setCommand(startRow);                        // B[2:0] Define start page address
      setCommand(scrollSpeed);                     // C[2:0] Set time interval between each scroll step in terms of the frame frequency
      setCommand(endRow);                          // D[2:0] Define end page address

      setCommand(scrollVDirection);                // Vertical Scrolling offset
      setCommand(BMD31M090_ACTIVATE_SCROLL);                 // 0x2F
      break;

    default:
      break;
  }
}

/*********************************************************************************************************//**
  * @brief  start Left-handed Scroll.
  * @param  startPage: start scroll Page, 0 at top page to 7 at bottom page.
  *         endPage: end scroll Page, 0 at top page to 7 at bottom page.
  *         scrollSpeed: set scroll speed.
  *         @arg BMD31M090_SCROLL_2FRAMES
  *         @arg BMD31M090_SCROLL_3FRAMES
  *         @arg BMD31M090_SCROLL_4FRAMES
  *         @arg BMD31M090_SCROLL_5FRAMES
  *         @arg BMD31M090_SCROLL_25FRAMES
  *         @arg BMD31M090_SCROLL_64FRAMES
  *         @arg BMD31M090_SCROLL_128FRAMES
  *         @arg BMD31M090_SCROLL_256FRAMES
  *         scrollVDirection: set scroll vertical direction 
  *         @arg BMD31M090_SCROLLV_NONE
  *         @arg BMD31M090_SCROLLV_TOP
  *         @arg BMD31M090_SCROLLV_BOTTOM
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_startScrollLeft(uint8_t startRow, uint8_t endRow, uint8_t scrollSpeed, uint8_t scrollVDirection)
{
  setCommand(BMD31M090_DEACTIVATE_SCROLL);                    // Must be deactivated before issuing this command (0x2E).

  switch (scrollVDirection)
  {
    case BMD31M090_SCROLLV_NONE:
      setCommand(BMD31M090_LEFT_SCROLL);                      // 0x27, Left Horizontal Scroll
      setCommand(0x00);                             // A[7:0] Dummy Byte (Set as 00h)

      setCommand(startRow);                         // B[2:0] Define start page address
      setCommand(scrollSpeed);                      // C[2:0] Set time interval between each scroll step in terms of the frame frequency
      setCommand(endRow);                           // D[2:0] Define end page address

      setCommand(0x00);                             // E[7:0] Dummy Byte (Set as 00h)
      setCommand(0xFF);                             // F[7:0] Dummy Byte (Set as FFh)
      setCommand(BMD31M090_ACTIVATE_SCROLL);                  // 0x2F
      break;

    case BMD31M090_SCROLLV_TOP:
    case BMD31M090_SCROLLV_BOTTOM:
      setCommand(BMD31M090_SET_SCROLLAREA);                   // 0xA3, Set Vertical Scroll Area
      setCommand(0x00);                             // Set No. of rows in top fixed area
      setCommand(_displayHeight);                   // Set No. of rows in scroll area (0-63)

      setCommand(BMD31M090_LEFTDIAGONAL_SCROLL);              // 0x2A, Vertical and Left Horizontal Scroll
      setCommand(0x00);                             // A[7:0] Dummy Byte (Set as 00h)

      setCommand(startRow);                         // B[2:0] Define start page address
      setCommand(scrollSpeed);                      // C[2:0] Set time interval between each scroll step in terms of the frame frequency
      setCommand(endRow);                           // D[2:0] Define end page address

      setCommand(scrollVDirection);                 // Vertical Scrolling offset
      setCommand(BMD31M090_ACTIVATE_SCROLL);                  // 0x2F
      break;

    default:
      break;
  }
}

/*********************************************************************************************************//**
  * @brief  stop a previously-begun scrolling action.
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_stopScroll(void)
{
  setCommand(BMD31M090_DEACTIVATE_SCROLL);                    // 0x2E
}

/*********************************************************************************************************//**
  * @brief  set Font.
  *         Currently support FontTable_8X16 and FontTable_6X8.
  *         After begin() is executed, FontTable_8X16 is used by default.
  *         (set __fontWidth and _fontHeight by _font[0]&[1])
  * @param  None
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_setFont(const unsigned char* font)
{
  _font = font;
  _fontWidth = *(const unsigned char *)(&_font[0]);
  _fontHeight = *(const unsigned char *)(&_font[1]);
}

/*********************************************************************************************************//**
  * @brief  set Pixel Page.
  * @param  x: Column of display, 0 at left to (_display_width - 1) at right.
  *         row: Row page of display, 0 at top page to 7 at bottom page.
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_setPixelRow(uint8_t x, uint8_t row)
{
  setCommand(BMD31M090_SET_PAGEADDRESS + row);                // Set Page Address
  setCommand(((x & 0xF0) >> 4) | BMD31M090_SET_HIGHCOLUMN);   // Set Column Higher Address
  setCommand((x & 0x0F));                           // Set Column Lower Address
}

/*********************************************************************************************************//**
  * @brief  set Dim to display.
  *         Contrast ranges from 00h to FFh, the range is too small to be really useful.
  *         This function is only set for the lowest contrast and normal contrast.
  * @param  dim : True for enable dim mode (contrast value : 0x00),
  *               False for Normal brightness mode (contrast value : 0xCF).
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_dim(bool dim)
{
  setCommand(BMD31M090_SET_CONTRAST);
  setCommand(dim ? 0 : BMD31M090_NORMAL_CONTRAST);            // if True - set contrast 0 , False - set normal contrast 0xCF
}

/*********************************************************************************************************//**
  * @brief  invert Display mode.
  * @param  i: True to set invert Display mode (black-on-white).
  *            False to set normal Display mode (white-on-black).
  * @retval None
  ***********************************************************************************************************/
void BMD31M090_invertDisplay(bool i)
{
  setCommand(i ? BMD31M090_SET_INVERTDISPLAY : BMD31M090_SET_NORMALDISPLAY);
}

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief  Initial I2C Master.
 * @param  i2c_clock: I2C communication rate.
 * @retval None
 ************************************************************************************************************/
static void _initI2CMaster(uint32_t i2c_clock)
{
  /*
    !!! PORTING !!!
    Implement I2C Master Initial.
  */
  I2CMaster_Init(gBMD31M090_WIRE, BMD31M090_DEVICEADDR0, i2c_clock);
}

/*********************************************************************************************************//**
  * @brief  set Command to display.
  * @param  Commmand: The Command character to send to the display.
  * @retval None
  ***********************************************************************************************************/
static void setCommand(uint8_t command)
{
  uint8_t uTxData[2] = {0};
  uTxData[0] = 0x00;
  uTxData[1] = command;

  /*
    !!! PORTING !!!
    Decalered related I2C structures and write function...
  */
  {
    I2CMaster_Status_Enum I2CResult = I2C_MASTER_GOING;
    I2CMaster_Typedef gI2CMaster = {0x00};

    gI2CMaster.uSlaveAddress = _deviceAddress;
    gI2CMaster.Tx.puBuffer = (uint8_t *)&uTxData;
    gI2CMaster.Tx.uLength = 2;
    gI2CMaster.uTimeout_us = 30000;
    gI2CMaster.isDynamicOnOff_I2C = FALSE;

    I2CResult = I2C_MASTER_GOING;
    I2CMaster_Write(gBMD31M090_WIRE,&gI2CMaster);
    do {
      I2CResult = I2CMaster_GetStatus(gBMD31M090_WIRE);
    } while (I2CResult == I2C_MASTER_GOING);
  }

}

/*********************************************************************************************************//**
  * @brief  set Data to display.
  * @param  Data: The Data character to send to the display.
  * @retval None
  ***********************************************************************************************************/
static void setData(uint8_t data)
{
  uint8_t uTxData[2] = {0};
  uTxData[0] = 0x40;
  uTxData[1] = data;

  /*
    !!! PORTING !!!
    Decalered related I2C structures and write function...
  */
  {
    I2CMaster_Status_Enum I2CResult = I2C_MASTER_GOING;
    I2CMaster_Typedef gI2CMaster = {0x00};

    gI2CMaster.uSlaveAddress = _deviceAddress;
    gI2CMaster.Tx.puBuffer = (uint8_t *)&uTxData;
    gI2CMaster.Tx.uLength = 2;
    gI2CMaster.uTimeout_us = 30000;
    gI2CMaster.isDynamicOnOff_I2C = FALSE;

    I2CResult = I2C_MASTER_GOING;
    I2CMaster_Write(gBMD31M090_WIRE,&gI2CMaster);
    do {
      I2CResult = I2CMaster_GetStatus(gBMD31M090_WIRE);
    } while (I2CResult == I2C_MASTER_GOING);
  }

}

/*********************************************************************************************************//**
  * @brief  set Pow.
  * @param  baseValue : Base Value.
  *         indexValue : Index Value.
  * @retval The value of baseValue^indexValue.
  ***********************************************************************************************************/
static uint32_t setPow(uint8_t baseValue, uint8_t indexValue)
{
  uint32_t result = 1;
  while(indexValue--)
  {
    result *= baseValue;                            // result = baseValue^indexValue
  }

  return result;
}
