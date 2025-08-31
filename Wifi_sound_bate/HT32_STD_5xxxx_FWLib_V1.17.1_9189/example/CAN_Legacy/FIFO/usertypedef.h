/*********************************************************************************************************//**
 * @file    usertypedef.h
 * @version $Rev:: 7114         $
 * @date    $Date:: 2023-08-10 #$
 * @brief   The header file of user's typedef.
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
#ifndef __USERTYPEDEF_H
#define __USERTYPEDEF_H

/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef struct
{
  u8  L;
  u8  H;
} wformat_u8;

typedef struct
{
  u16 L;
  u16 H;
} dwformat_u16;

typedef union
{
  wformat_u8          _u8;
  u16                 _u16;
  u8                  arr[2];
} wformat_uWord;

typedef union
{
  dwformat_u16        _u16;
  u32                 _u32;
  u8                  arr[4];
} dwformat_uWord;

typedef union
{
  s32                 _s32;
  s8                  arr[4];
} sdwformat_uWord;

/* Exported macro ------------------------------------------------------------------------------------------*/
#define LONIBBLE(val)   (val & 0x0f)
#define HINIBBLE(val)   (val & 0xf0)>>4
#define LOBYTE(val)     (val & 0x00ff)
#define HIBYTE(val)     (val & 0xff00)>>8
#define DWBYTE0(val)    (val & 0x000000ff)
#define DWBYTE1(val)    (val & 0x0000ff00)>>8
#define DWBYTE2(val)    (val & 0x00ff0000)>>16
#define DWBYTE3(val)    (val & 0xff000000)>>24
#define LOINT(val)      (val & 0x0000ffff)
#define HIINT(val)      (val & 0xffff0000)>>16

#endif /* __USERTYPEDEF_H -------------------------------------------------------------------------------*/
