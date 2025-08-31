/*********************************************************************************************************//**
 * @file    ADC/BandgapVoltage/ht32_board_config.h
 * @version $Rev:: 8660         $
 * @date    $Date:: 2025-04-29 #$
 * @brief   The header file of board configuration.
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
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_HT32F50030_SK)
  #define _HTCFG_VR_GPIOX                         B
  #define _HTCFG_VR_GPION                         7
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_0)

  #define _HTCFG_VBG_GPIOX                        A
  #define _HTCFG_VBG_GPION                        0
#endif

#if defined(USE_HT32F65233_DVB)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         0
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_7)

  #define _HTCFG_VBG_GPIOX                        A
  #define _HTCFG_VBG_GPION                        7
#endif

#if defined(USE_HT32F66242_DVB)
  #define _HTCFG_VR_GPIOX                         C
  #define _HTCFG_VR_GPION                         7
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_0)

  // VBG and VR have the same I/O, so always don't enable the VBG output function.
  #if 0
  #define _HTCFG_VBG_GPIOX                        C
  #define _HTCFG_VBG_GPION                        7
  #endif
#endif

#if defined(USE_HT32F66246_DVB)
  #define _HTCFG_VR_GPIOX                         C
  #define _HTCFG_VR_GPION                         7
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_0)

  // VBG and VR have the same I/O, so always don't enable the VBG output function.
  #if 0
  #define _HTCFG_VBG_GPIOX                        C
  #define _HTCFG_VBG_GPION                        7
  #endif
#endif

#define HTCFG_VR_GPIO_ID                          STRCAT2(GPIO_P,         _HTCFG_VR_GPIOX)
#define HTCFG_VR_AFIO_PIN                         STRCAT2(AFIO_PIN_,      _HTCFG_VR_GPION)
#define HTCFG_VBG_GPIO_ID                         STRCAT2(GPIO_P,         _HTCFG_VBG_GPIOX)
#define HTCFG_VBG_AFIO_PIN                        STRCAT2(AFIO_PIN_,      _HTCFG_VBG_GPION)



#ifdef __cplusplus
}
#endif

#endif
