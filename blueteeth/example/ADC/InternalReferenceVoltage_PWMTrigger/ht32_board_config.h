/*********************************************************************************************************//**
 * @file    ADC/InternalReferenceVoltage_PWMTrigger/ht32_board_config.h
 * @version $Rev:: 7348         $
 * @date    $Date:: 2023-12-05 #$
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

#if (LIBCFG_ADC_IVREF)
#else
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32F52354_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_6)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F57341_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         3
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_3)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F57352_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         2
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_2)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F52367_SK)
  #define _HTCFG_VR_GPIOX                         D
  #define _HTCFG_VR_GPION                         4
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_8)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_BM53A367A_DVB)
  #define _HTCFG_VR_GPIOX                         D               // A2/D16
  #define _HTCFG_VR_GPION                         4
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_8)

  #define _HTCFG_VREF_GPIOX                       A               // A6/D30
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_BM18B367A_DVB)
  #define _HTCFG_VR_GPIOX                         A               // A2/D16
  #define _HTCFG_VR_GPION                         3
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_3)

  #define _HTCFG_VREF_GPIOX                       A               // A8/D30
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F54241_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         3
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_5)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F54253_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_8)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F50452_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_6)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F53252_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_6)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F50441_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_6)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F53241_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_6)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0
#endif

#if defined(USE_HT32F52244_SK)
  #define _HTCFG_VR_GPIOX                         A
  #define _HTCFG_VR_GPION                         6
  #define  HTCFG_VR_ADC_CH                        (ADC_CH_6)

  #define _HTCFG_VREF_GPIOX                       A
  #define _HTCFG_VREF_GPION                       0

  #define HTCFG_PWM_IPN                           PWM0
  #define HTCFG_ADC_TRIG_TM_CH3O                  ADC_TRIG_PWM0_CH3O
#endif

#if !defined(HTCFG_PWM_IPN)
  #define HTCFG_PWM_IPN                           GPTM0
  #define HTCFG_ADC_TRIG_TM_CH3O                  ADC_TRIG_GPTM0_CH3O
#endif

#define HTCFG_PWM_TM_PORT                         STRCAT2(HT_,            HTCFG_PWM_IPN)
#define HTCFG_PWM_IRQn                            STRCAT2(HTCFG_PWM_IPN, _IRQn)
#define HTCFG_PWM_IRQHandler                      STRCAT2(HTCFG_PWM_IPN, _IRQHandler)

#define HTCFG_VR_GPIO_ID                          STRCAT2(GPIO_P,         _HTCFG_VR_GPIOX)
#define HTCFG_VR_AFIO_PIN                         STRCAT2(AFIO_PIN_,      _HTCFG_VR_GPION)
#define HTCFG_VREF_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_VREF_GPIOX)
#define HTCFG_VREF_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_VREF_GPION)


#ifdef __cplusplus
}
#endif

#endif
