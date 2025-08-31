/*********************************************************************************************************//**
 * @file    BMD31M090_HT32/src/BMD31M090.h
 * @version V1.0.1
 * @date    2024-08-01
 * @brief   The header file of the BMD31M090 libray.
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
#ifndef __BMD31M090_H
#define __BMD31M090_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "fontTable.h"

/*
  !!! PORTING !!!
  Include related header files.
*/
#include "ht32.h"
#include "i2c_master_config.h"
#include "ht32_board_config.h"
#include "bmduino_check.h"

#include "middleware/i2c_master.h"

/* Exported macro ------------------------------------------------------------------------------------------*/
#define abs(x) ((x)>0?(x):-(x))

/*----------------------------------------------------------------------------------------------------------*
 *  Slave Address (Default) :                                                                               *
 *       7-bit: 0x3C                                                                                        *
 *       8-bit: 0x78 or 0x79                                                                                *
 *          S | A6 | A5 | A4 | A3 | A2 | A1 | A0 | 0r/1w | A                                                *
 *            |  0 |  1 |  1 |  1 |  1 |  0 |  0 | 0(w)  |                                                  *
 *----------------------------------------------------------------------------------------------------------*/
#define BMD31M090_DEVICEADDR0    0x3C     // See Schematic "I2C Addr SEL" for address setting,
#define BMD31M090_DEVICEADDR1    0x3D     // The I2C address can configure: Addr0:0x3C ; Addr1:0x3D
#define BMD31M090_CLOCK_SPEED    400000
#define BMD31M090_WIDTH          128      // BMD31M090 Module display width, in pixels
#define BMD31M090_HEIGHT         64       // BMD31M090 Module display height, in pixels

#define BMD31M090_displayROW0          0
#define BMD31M090_displayROW1          1
#define BMD31M090_displayROW2          2
#define BMD31M090_displayROW3          3
#define BMD31M090_displayROW4          4
#define BMD31M090_displayROW5          5
#define BMD31M090_displayROW6          6
#define BMD31M090_displayROW7          7

/* Pixel Color                                                */
#define BMD31M090_pixelColor_BLACK 0                 // Pixel Color is 'OFF'
#define BMD31M090_pixelColor_WHITE 1                 // Pixel Color is 'ON'
#define BMD31M090_pixelColor_INVERSE 2               // Pixel Color is last color flip

/* Datasheet Relation Setup                                   */
#define BMD31M090_SET_LOWCOLUMN        0x00
#define BMD31M090_SET_HIGHCOLUMN       0x10
#define BMD31M090_SET_ADDRESSINGMODE   0x20
#define BMD31M090_SET_COLUMNADDR       0x21
#define BMD31M090_SET_PAGEADDR         0x22
#define BMD31M090_SET_STARTLINE        0x40
#define BMD31M090_SET_CONTRAST         0x81
#define BMD31M090_SET_CHARGEPUMP       0x8D
#define BMD31M090_SEGMENT_REMAP        0xA1
#define BMD31M090_DISPLAYALLON_RESUME  0xA4
#define BMD31M090_SET_NORMALDISPLAY    0xA6
#define BMD31M090_SET_INVERTDISPLAY    0xA7
#define BMD31M090_SET_MULTIPLEX        0xA8
#define BMD31M090_SET_DISPLAYOFF       0xAE
#define BMD31M090_SET_DISPLAYON        0xAF
#define BMD31M090_SET_PAGEADDRESS      0xB0
#define BMD31M090_COMSCAN_DIRECTION    0xC8
#define BMD31M090_NORMAL_CONTRAST      0xCF
#define BMD31M090_SET_DISPLAYOFFSET    0xD3
#define BMD31M090_SET_DISPLAYCLOCKDIV  0xD5
#define BMD31M090_SET_PRECHARGE        0xD9
#define BMD31M090_SET_COMPINS          0xDA
#define BMD31M090_SET_VCOMDETECT       0xDB

/* Display Scroll Relation Setup                              */
#define BMD31M090_RIGHT_SCROLL         0x26
#define BMD31M090_LEFT_SCROLL          0x27
#define BMD31M090_RIGHTDIAGONAL_SCROLL 0x29
#define BMD31M090_LEFTDIAGONAL_SCROLL  0x2A
#define BMD31M090_DEACTIVATE_SCROLL    0x2E
#define BMD31M090_ACTIVATE_SCROLL      0x2F
#define BMD31M090_SET_SCROLLAREA       0xA3

#define BMD31M090_SCROLL_2FRAMES       0x07
#define BMD31M090_SCROLL_3FRAMES       0x04
#define BMD31M090_SCROLL_4FRAMES       0x05
#define BMD31M090_SCROLL_5FRAMES       0x00
#define BMD31M090_SCROLL_25FRAMES      0x06
#define BMD31M090_SCROLL_64FRAMES      0x01
#define BMD31M090_SCROLL_128FRAMES     0x02
#define BMD31M090_SCROLL_256FRAMES     0x03

#define BMD31M090_SCROLLV_NONE         0x00       // Scroll Vertical Direction : N/A
#define BMD31M090_SCROLLV_TOP          0x01       // Scroll Vertical Direction : Top
#define BMD31M090_SCROLLV_BOTTOM       0x3F       // Scroll Vertical Direction : Bottom

/* Exported variables --------------------------------------------------------------------------------------*/
extern uint32_t gBMD31M090_WIRE;

/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef enum {
  BMD31M090_SUCCESS,
  BMD31M090_FAILURE
} BMD31M090_selStatus;

/* Exported functions --------------------------------------------------------------------------------------*/
BMD31M090_selStatus BMD31M090_selWire(uint32_t BMD31M090_CH);
void BMD31M090_Init(uint8_t i2c_addr, uint32_t i2c_clock);
void BMD31M090_clearDisplay(void);
void BMD31M090_display(void);
void BMD31M090_drawPixel(uint8_t x, uint8_t y, uint8_t pixelColor);
void BMD31M090_drawLine(uint8_t x_Start, uint8_t y_Start, uint8_t x_End, uint8_t y_End, uint8_t pixelColor);
void BMD31M090_drawFastHLine(uint8_t x, uint8_t y, uint8_t width, uint8_t pixelColor);
void BMD31M090_drawFastVLine(uint8_t x, uint8_t y, uint8_t height, uint8_t pixelColor);
void BMD31M090_drawChar(uint8_t x, uint8_t row, uint8_t chr);
void BMD31M090_drawString(uint8_t x, uint8_t row, uint8_t *str);
void BMD31M090_drawNum(uint8_t x, uint8_t row, uint32_t num, uint8_t numLen);
void BMD31M090_drawBitmap(int8_t x, int8_t y, const uint8_t *Bitmap, uint8_t w, uint8_t h, uint8_t pixelColor);
void BMD31M090_startScrollRight(uint8_t startRow, uint8_t endRow, uint8_t scrollSpeed, uint8_t scrollVDirection);
void BMD31M090_startScrollLeft(uint8_t startRow, uint8_t endRow, uint8_t scrollSpeed, uint8_t scrollVDirection);
void BMD31M090_stopScroll(void);
void BMD31M090_setFont(const unsigned char* font);
void BMD31M090_setPixelRow(uint8_t x, uint8_t row);
void BMD31M090_dim(bool dim);
void BMD31M090_invertDisplay(bool i);

#ifdef __cplusplus
}
#endif

#endif

