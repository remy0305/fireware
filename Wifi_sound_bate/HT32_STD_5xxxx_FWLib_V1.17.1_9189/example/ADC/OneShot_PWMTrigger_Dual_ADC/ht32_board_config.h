/*********************************************************************************************************//**
 * @file    ADC/OneShot_PWMTrigger_Dual_ADC/ht32_board_config.h
 * @version $Rev:: 5068         $
 * @date    $Date:: 2020-11-07 #$
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
#if (LIBCFG_NO_ADC)
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32F65240_SK)
  #define _HTCFG_ADC0_5_GPIOX                     A
  #define _HTCFG_ADC0_5_GPION                     0
  #define _HTCFG_ADC0_5_ADC_CHN                   5

  #define _HTCFG_ADC0_6_GPIOX                     A
  #define _HTCFG_ADC0_6_GPION                     1
  #define _HTCFG_ADC0_6_ADC_CHN                   6

  #define _HTCFG_ADC1_7_GPIOX                     A
  #define _HTCFG_ADC1_7_GPION                     6
  #define _HTCFG_ADC1_7_ADC_CHN                   7
#endif

#define HTCFG_ADC0_5_GPIO_ID                      STRCAT2(GPIO_P,         _HTCFG_ADC0_5_GPIOX)
#define HTCFG_ADC0_5_AFIO_PIN                     STRCAT2(AFIO_PIN_,      _HTCFG_ADC0_5_GPION)
#define HTCFG_ADC0_5_ADC_CH                       STRCAT2(ADC_CH_,        _HTCFG_ADC0_5_ADC_CHN)

#define HTCFG_ADC0_6_GPIO_ID                      STRCAT2(GPIO_P,         _HTCFG_ADC0_6_GPIOX)
#define HTCFG_ADC0_6_AFIO_PIN                     STRCAT2(AFIO_PIN_,      _HTCFG_ADC0_6_GPION)
#define HTCFG_ADC0_6_ADC_CH                       STRCAT2(ADC_CH_,        _HTCFG_ADC0_6_ADC_CHN)

#define HTCFG_ADC1_7_GPIO_ID                      STRCAT2(GPIO_P,         _HTCFG_ADC1_7_GPIOX)
#define HTCFG_ADC1_7_AFIO_PIN                     STRCAT2(AFIO_PIN_,      _HTCFG_ADC1_7_GPION)
#define HTCFG_ADC1_7_ADC_CH                       STRCAT2(ADC_CH_,        _HTCFG_ADC1_7_ADC_CHN)


#ifdef __cplusplus
}
#endif

#endif
