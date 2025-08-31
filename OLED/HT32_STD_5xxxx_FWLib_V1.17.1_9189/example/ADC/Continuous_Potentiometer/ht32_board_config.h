/*********************************************************************************************************//**
 * @file    ADC/Continuous_Potentiometer/ht32_board_config.h
 * @version $Rev:: 8632         $
 * @date    $Date:: 2025-04-25 #$
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

  #define HTCFG_ADC_IPN                           ADC0
  #define HTCFG_ADC_IRQHandler                    ADC_IRQHandler

#if defined(USE_HT32F52230_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         7
  #define _HTCFG_VR_ADC_CHN                       7
#endif

#if defined(USE_HT32F52241_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       8
#endif

#if defined(USE_HT32F52253_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F52341_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       8
#endif

#if defined(USE_HT32F52352_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F50030_SK)
  #define _HTCFG_VR_GPIOX                         B
  #define _HTCFG_VR_GPION                         7
  #define _HTCFG_VR_ADC_CHN                       0
#endif

#if defined(USE_HT32F50230_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         2
  #define _HTCFG_VR_ADC_CHN                       4
#endif

#if defined(USE_HT32F50241_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       8
#endif

#if defined(USE_HT32F52354_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F0006_DVB)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       10
#endif

#if defined(USE_HT32F57341_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         3
  #define _HTCFG_VR_ADC_CHN                       3
#endif

#if defined(USE_HT32F57352_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         2
  #define _HTCFG_VR_ADC_CHN                       2
#endif

#if defined(USE_HT32F52367_SK)
  #define _HTCFG_VR_GPIOX                         D
  #define _HTCFG_VR_GPION                         4
  #define _HTCFG_VR_ADC_CHN                       8
#endif

#if defined(USE_BM53A367A_DVB)
  #define _HTCFG_VR_GPIOX                         D               // A2/D16
  #define _HTCFG_VR_GPION                         4
  #define _HTCFG_VR_ADC_CHN                       8
#endif

#if defined(USE_BM18B367A_DVB)
  #define _HTCFG_VR_GPIOX                         A               // A2/D16
  #define _HTCFG_VR_GPION                         3
  #define _HTCFG_VR_ADC_CHN                       3
#endif

#if defined(USE_HT32F50343_SK)
  #define _HTCFG_VR_GPIOX                         D
  #define _HTCFG_VR_GPION                         5
  #define _HTCFG_VR_ADC_CHN                       11
#endif

#if defined(USE_HT32F54241_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         3
  #define _HTCFG_VR_ADC_CHN                       5
#endif

#if defined(USE_HT32F54253_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       8
#endif

#if defined(USE_HT32F65240_DVB)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         4
  #define _HTCFG_VR_ADC_CHN                       5

  #undef  HTCFG_ADC_IPN
  #define HTCFG_ADC_IPN                           ADC1

  #undef  HTCFG_ADC_IRQHandler
  #define HTCFG_ADC_IRQHandler                    STRCAT2(HTCFG_ADC_IPN, _IRQHandler)
#endif

#if defined(USE_HT32F65240_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       7

  #undef  HTCFG_ADC_IPN
  #define HTCFG_ADC_IPN                           ADC1

  #undef  HTCFG_ADC_IRQHandler
  #define HTCFG_ADC_IRQHandler                    STRCAT2(HTCFG_ADC_IPN, _IRQHandler)
#endif

#if defined(USE_HT32F65232_DVB)
  #define _HTCFG_VR_GPIOX                         C
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       10

  #undef  HTCFG_ADC_IPN
  #define HTCFG_ADC_IPN                           ADC0

  #undef  HTCFG_ADC_IRQHandler
  #define HTCFG_ADC_IRQHandler                    STRCAT2(HTCFG_ADC_IPN, _IRQHandler)
#endif

#if defined(USE_HT32F65233_DVB)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         0
  #define _HTCFG_VR_ADC_CHN                       7

  #undef  HTCFG_ADC_IPN
  #define HTCFG_ADC_IPN                           ADC0

  #undef  HTCFG_ADC_IRQHandler
  #define HTCFG_ADC_IRQHandler                    STRCAT2(HTCFG_ADC_IPN, _IRQHandler)
#endif

#if defined(USE_HT32F61355_SK) || defined(USE_HT32F61356_SK) || defined(USE_HT32F61357_SK)
  #define _HTCFG_VR_GPIOX                         C
  #define _HTCFG_VR_GPION                         8
  #define _HTCFG_VR_ADC_CHN                       14
#endif

#if defined(USE_HT32F61245_SK)
  #define _HTCFG_VR_GPIOX                         C
  #define _HTCFG_VR_GPION                         8
  #define _HTCFG_VR_ADC_CHN                       14
#endif

#if defined(USE_HT32F67233_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         7
  #define _HTCFG_VR_ADC_CHN                       7
#endif

#if defined(USE_HT32F50452_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F53252_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F50441_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F53241_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F52244_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define _HTCFG_VR_ADC_CHN                       6
#endif

#if defined(USE_HT32F66242_DVB)
  #define _HTCFG_VR_GPIOX                         C
  #define _HTCFG_VR_GPION                         7
  #define _HTCFG_VR_ADC_CHN                       0
#endif

#if defined(USE_HT32F66246_DVB)
  #define _HTCFG_VR_GPIOX                         C
  #define _HTCFG_VR_GPION                         7
  #define _HTCFG_VR_ADC_CHN                       0
#endif

#define HTCFG_VR_GPIO_ID                          STRCAT2(GPIO_P,         _HTCFG_VR_GPIOX)
#define HTCFG_VR_AFIO_PIN                         STRCAT2(AFIO_PIN_,      _HTCFG_VR_GPION)
#define HTCFG_VR_ADC_CH                           STRCAT2(ADC_CH_,        _HTCFG_VR_ADC_CHN)

#define HTCFG_ADC_PORT                            STRCAT2(HT_,            HTCFG_ADC_IPN)
#define HTCFG_ADC_AFIO_MODE                       STRCAT2(AFIO_FUN_,      HTCFG_ADC_IPN)
#define HTCFG_ADC_CKCU_ADCPRE                     STRCAT2(CKCU_ADCPRE_,   HTCFG_ADC_IPN)
#define HTCFG_ADC_IRQn                            STRCAT2(HTCFG_ADC_IPN, _IRQn)


#ifdef __cplusplus
}
#endif

#endif
