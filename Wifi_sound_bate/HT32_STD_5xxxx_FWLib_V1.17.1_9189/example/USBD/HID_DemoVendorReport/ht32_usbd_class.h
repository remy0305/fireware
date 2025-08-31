/*********************************************************************************************************//**
 * @file    USBD/HID_DemoVendorReport/ht32_usbd_class.h
 * @version $Rev:: 4519         $
 * @date    $Date:: 2020-02-06 #$
 * @brief   The header file of USB Device Class.
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
#ifndef __HT32_USBD_CLASS_H
#define __HT32_USBD_CLASS_H

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USBD_Examples USBD
  * @{
  */

/** @addtogroup HID_DemoVendorReport
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define USAGE_PAGE_L                      (0x00)

#define RPT_EN_1                          (1)
#define RPT_EN_2                          (1)
#define RPT_EN_3                          (1)
#define RPT_EN_4                          (1)
#define RPT_EN_5                          (1)
#define RPT_EN_6                          (1)

#define RPT_ID_1                          (0x1)
#define RPT_ID_2                          (0x2)
#define RPT_ID_3                          (0x3)
#define RPT_ID_4                          (0x4)
#define RPT_ID_5                          (0x5)
#define RPT_ID_6                          (0x6)

#define RPT_LEN_1                         (768)
#define RPT_LEN_2                         (32)
#define RPT_LEN_3                         (768)
#define RPT_LEN_4                         (32)
#define RPT_LEN_5                         (63)
#define RPT_LEN_6                         (32)

                                          // 0x81 INPUT
                                          // 0x91 OUTPUT
                                          // 0xb1 FEATURE
                                          // Modify the "USBDClass_GetReport()", "USBDClass_SetReport()" if you change the type.
#define RPT_TYPE_1                        (0x81)
#define RPT_TYPE_2                        (0x81)
#define RPT_TYPE_3                        (0x91)
#define RPT_TYPE_4                        (0x91)
#define RPT_TYPE_5                        (0xb1)
#define RPT_TYPE_6                        (0xb1)


/* Exported constants --------------------------------------------------------------------------------------*/

/* For ht32_usbd_descriptor.c                                                                               */
#define CLASS_INF_CLASS                   (DESC_CLASS_03_HID)
#define CLASS_INF_SUBCLASS                (HID_SUBCLASS_00_NONE)
#define CLASS_INF_PTCO                    (HID_PROTOCOL_00_NONE)

/* HID related definition                                                                                   */
#define DESC_LEN_RPT_1                    (0)
#define DESC_LEN_RPT_2                    (0)
#define DESC_LEN_RPT_3                    (0)
#define DESC_LEN_RPT_4                    (0)
#define DESC_LEN_RPT_5                    (0)
#define DESC_LEN_RPT_6                    (0)

#if (RPT_EN_1)
#undef DESC_LEN_RPT_1
#define DESC_LEN_RPT_1                    (16)
#endif

#if (RPT_EN_2)
#undef DESC_LEN_RPT_2
#define DESC_LEN_RPT_2                    (16)
#endif

#if (RPT_EN_3)
#undef DESC_LEN_RPT_3
#define DESC_LEN_RPT_3                    (16)
#endif

#if (RPT_EN_4)
#undef DESC_LEN_RPT_4
#define DESC_LEN_RPT_4                    (16)
#endif

#if (RPT_EN_5)
#undef DESC_LEN_RPT_5
#define DESC_LEN_RPT_5                    (16)
#endif

#if (RPT_EN_6)
#undef DESC_LEN_RPT_6
#define DESC_LEN_RPT_6                    (16)
#endif

#define DESC_LEN_HID                      ((u32)(9))
#define DESC_LEN_RPOT                     ((u16)(7 + DESC_LEN_RPT_1 + \
                                                     DESC_LEN_RPT_2 + \
                                                     DESC_LEN_RPT_3 + \
                                                     DESC_LEN_RPT_4 + \
                                                     DESC_LEN_RPT_5 + \
                                                     DESC_LEN_RPT_6 + \
                                                     + 1))

#define DESC_TYPE_21_HID                  (0x21)
#define DESC_TYPE_22_RPOT                 (0x22)
#define DESC_TYPE_23_PHY                  (0x23)

#define HID_SUBCLASS_00_NONE              (0x00)
#define HID_SUBCLASS_01_BOOT              (0x01)

#define HID_PROTOCOL_00_NONE              (0x00)
#define HID_PROTOCOL_01_KEYBOARD          (0x01)
#define HID_PROTOCOL_02_MOUSE             (0x02)

/* Exported functions --------------------------------------------------------------------------------------*/
void USBDClass_Init(USBDCore_Class_TypeDef *pClass);


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __HT32_USBD_CLASS_H ------------------------------------------------------------------------------*/
