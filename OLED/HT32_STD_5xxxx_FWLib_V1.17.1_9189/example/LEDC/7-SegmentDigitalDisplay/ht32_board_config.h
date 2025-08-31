/*********************************************************************************************************//**
 * @file    LEDC/7-SegmentDigitalDisplay/ht32_board_config.h
 * @version $Rev:: 7265         $
 * @date    $Date:: 2023-10-02 #$
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
#if defined(USE_HT32F54241_SK)
  #define HTCFG_LEDC_COM_D1                        3
  #define HTCFG_LEDC_COM_D2                        4
  #define HTCFG_LEDC_COM_D3                        5
  #define HTCFG_LEDC_COM_D4                        6

  #define _HTCFG_LEDC_COM0_GPIO_PORT               B
  #define _HTCFG_LEDC_COM0_GPIO_PIN                5
  #define _HTCFG_LEDC_COM1_GPIO_PORT               C
  #define _HTCFG_LEDC_COM1_GPIO_PIN                1
  #define _HTCFG_LEDC_COM2_GPIO_PORT               C
  #define _HTCFG_LEDC_COM2_GPIO_PIN                2
  #define _HTCFG_LEDC_COM3_GPIO_PORT               C
  #define _HTCFG_LEDC_COM3_GPIO_PIN                3

  #define _HTCFG_LEDC_SEG0_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG0_GPIO_PIN                0
  #define _HTCFG_LEDC_SEG1_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG1_GPIO_PIN                1
  #define _HTCFG_LEDC_SEG2_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG2_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG3_GPIO_PORT               B
  #define _HTCFG_LEDC_SEG3_GPIO_PIN                3
  #define _HTCFG_LEDC_SEG4_GPIO_PORT               B
  #define _HTCFG_LEDC_SEG4_GPIO_PIN                7
  #define _HTCFG_LEDC_SEG5_GPIO_PORT               B
  #define _HTCFG_LEDC_SEG5_GPIO_PIN                8
  #define _HTCFG_LEDC_SEG6_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG6_GPIO_PIN                6
  #define _HTCFG_LEDC_SEG7_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG7_GPIO_PIN                7
#endif

#if defined(USE_HT32F54253_SK)
  #define HTCFG_LEDC_COM_D1                        4
  #define HTCFG_LEDC_COM_D2                        5
  #define HTCFG_LEDC_COM_D3                        6
  #define HTCFG_LEDC_COM_D4                        7

  #define _HTCFG_LEDC_COM0_GPIO_PORT               C
  #define _HTCFG_LEDC_COM0_GPIO_PIN                4
  #define _HTCFG_LEDC_COM1_GPIO_PORT               C
  #define _HTCFG_LEDC_COM1_GPIO_PIN                5
  #define _HTCFG_LEDC_COM2_GPIO_PORT               C
  #define _HTCFG_LEDC_COM2_GPIO_PIN                6
  #define _HTCFG_LEDC_COM3_GPIO_PORT               C
  #define _HTCFG_LEDC_COM3_GPIO_PIN                7

  #define _HTCFG_LEDC_SEG0_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG0_GPIO_PIN                0
  #define _HTCFG_LEDC_SEG1_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG1_GPIO_PIN                1
  #define _HTCFG_LEDC_SEG2_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG2_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG3_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG3_GPIO_PIN                3
  #define _HTCFG_LEDC_SEG4_GPIO_PORT               D
  #define _HTCFG_LEDC_SEG4_GPIO_PIN                4
  #define _HTCFG_LEDC_SEG5_GPIO_PORT               D
  #define _HTCFG_LEDC_SEG5_GPIO_PIN                5
  #define _HTCFG_LEDC_SEG6_GPIO_PORT               D
  #define _HTCFG_LEDC_SEG6_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG7_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG7_GPIO_PIN                7
#endif

#if defined(USE_HT32F50030_SK)
  #define HTCFG_LEDC_COM_D1                        0
  #define HTCFG_LEDC_COM_D2                        1
  #define HTCFG_LEDC_COM_D3                        2
  #define HTCFG_LEDC_COM_D4                        3

  #define _HTCFG_LEDC_COM0_GPIO_PORT               C
  #define _HTCFG_LEDC_COM0_GPIO_PIN                0
  #define _HTCFG_LEDC_COM1_GPIO_PORT               A
  #define _HTCFG_LEDC_COM1_GPIO_PIN                8
  #define _HTCFG_LEDC_COM2_GPIO_PORT               A
  #define _HTCFG_LEDC_COM2_GPIO_PIN                10
  #define _HTCFG_LEDC_COM3_GPIO_PORT               A
  #define _HTCFG_LEDC_COM3_GPIO_PIN                11

  #define _HTCFG_LEDC_SEG0_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG0_GPIO_PIN                0
  #define _HTCFG_LEDC_SEG1_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG1_GPIO_PIN                1
  #define _HTCFG_LEDC_SEG2_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG2_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG3_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG3_GPIO_PIN                3
  #define _HTCFG_LEDC_SEG4_GPIO_PORT               B
  #define _HTCFG_LEDC_SEG4_GPIO_PIN                7
  #define _HTCFG_LEDC_SEG5_GPIO_PORT               B
  #define _HTCFG_LEDC_SEG5_GPIO_PIN                8
  #define _HTCFG_LEDC_SEG6_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG6_GPIO_PIN                6
  #define _HTCFG_LEDC_SEG7_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG7_GPIO_PIN                7
#endif

#if defined(USE_HT32F50452_SK)
  #define HTCFG_LEDC_COM_D1                        0
  #define HTCFG_LEDC_COM_D2                        1
  #define HTCFG_LEDC_COM_D3                        2
  #define HTCFG_LEDC_COM_D4                        3

  #define _HTCFG_LEDC_COM0_GPIO_PORT               A
  #define _HTCFG_LEDC_COM0_GPIO_PIN                14
  #define _HTCFG_LEDC_COM1_GPIO_PORT               A
  #define _HTCFG_LEDC_COM1_GPIO_PIN                15
  #define _HTCFG_LEDC_COM2_GPIO_PORT               A
  #define _HTCFG_LEDC_COM2_GPIO_PIN                10
  #define _HTCFG_LEDC_COM3_GPIO_PORT               A
  #define _HTCFG_LEDC_COM3_GPIO_PIN                11

  #define _HTCFG_LEDC_SEG0_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG0_GPIO_PIN                0
  #define _HTCFG_LEDC_SEG1_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG1_GPIO_PIN                1
  #define _HTCFG_LEDC_SEG2_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG2_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG3_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG3_GPIO_PIN                3
  #define _HTCFG_LEDC_SEG4_GPIO_PORT               D
  #define _HTCFG_LEDC_SEG4_GPIO_PIN                4
  #define _HTCFG_LEDC_SEG5_GPIO_PORT               D
  #define _HTCFG_LEDC_SEG5_GPIO_PIN                5
  #define _HTCFG_LEDC_SEG6_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG6_GPIO_PIN                6
  #define _HTCFG_LEDC_SEG7_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG7_GPIO_PIN                7
#endif

#if defined(USE_HT32F53252_SK)
  #define HTCFG_LEDC_COM_D1                        0
  #define HTCFG_LEDC_COM_D2                        1
  #define HTCFG_LEDC_COM_D3                        2
  #define HTCFG_LEDC_COM_D4                        3

  #define _HTCFG_LEDC_COM0_GPIO_PORT               A
  #define _HTCFG_LEDC_COM0_GPIO_PIN                14
  #define _HTCFG_LEDC_COM1_GPIO_PORT               A
  #define _HTCFG_LEDC_COM1_GPIO_PIN                15
  #define _HTCFG_LEDC_COM2_GPIO_PORT               A
  #define _HTCFG_LEDC_COM2_GPIO_PIN                10
  #define _HTCFG_LEDC_COM3_GPIO_PORT               A
  #define _HTCFG_LEDC_COM3_GPIO_PIN                11

  #define _HTCFG_LEDC_SEG0_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG0_GPIO_PIN                0
  #define _HTCFG_LEDC_SEG1_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG1_GPIO_PIN                1
  #define _HTCFG_LEDC_SEG2_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG2_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG3_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG3_GPIO_PIN                3
  #define _HTCFG_LEDC_SEG4_GPIO_PORT               D
  #define _HTCFG_LEDC_SEG4_GPIO_PIN                4
  #define _HTCFG_LEDC_SEG5_GPIO_PORT               D
  #define _HTCFG_LEDC_SEG5_GPIO_PIN                5
  #define _HTCFG_LEDC_SEG6_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG6_GPIO_PIN                6
  #define _HTCFG_LEDC_SEG7_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG7_GPIO_PIN                7
#endif

#if defined(USE_HT32F50441_SK)
  #define HTCFG_LEDC_COM_D1                        0
  #define HTCFG_LEDC_COM_D2                        1
  #define HTCFG_LEDC_COM_D3                        2
  #define HTCFG_LEDC_COM_D4                        3

  #define _HTCFG_LEDC_COM0_GPIO_PORT               A
  #define _HTCFG_LEDC_COM0_GPIO_PIN                14
  #define _HTCFG_LEDC_COM1_GPIO_PORT               A
  #define _HTCFG_LEDC_COM1_GPIO_PIN                15
  #define _HTCFG_LEDC_COM2_GPIO_PORT               A
  #define _HTCFG_LEDC_COM2_GPIO_PIN                10
  #define _HTCFG_LEDC_COM3_GPIO_PORT               A
  #define _HTCFG_LEDC_COM3_GPIO_PIN                11

  #define _HTCFG_LEDC_SEG0_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG0_GPIO_PIN                0
  #define _HTCFG_LEDC_SEG1_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG1_GPIO_PIN                1
  #define _HTCFG_LEDC_SEG2_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG2_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG3_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG3_GPIO_PIN                3
  #define _HTCFG_LEDC_SEG4_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG4_GPIO_PIN                4
  #define _HTCFG_LEDC_SEG5_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG5_GPIO_PIN                5
  #define _HTCFG_LEDC_SEG6_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG6_GPIO_PIN                6
  #define _HTCFG_LEDC_SEG7_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG7_GPIO_PIN                7
#endif

#if defined(USE_HT32F53241_SK)
  #define HTCFG_LEDC_COM_D1                        0
  #define HTCFG_LEDC_COM_D2                        1
  #define HTCFG_LEDC_COM_D3                        2
  #define HTCFG_LEDC_COM_D4                        3

  #define _HTCFG_LEDC_COM0_GPIO_PORT               A
  #define _HTCFG_LEDC_COM0_GPIO_PIN                14
  #define _HTCFG_LEDC_COM1_GPIO_PORT               A
  #define _HTCFG_LEDC_COM1_GPIO_PIN                15
  #define _HTCFG_LEDC_COM2_GPIO_PORT               A
  #define _HTCFG_LEDC_COM2_GPIO_PIN                10
  #define _HTCFG_LEDC_COM3_GPIO_PORT               A
  #define _HTCFG_LEDC_COM3_GPIO_PIN                11

  #define _HTCFG_LEDC_SEG0_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG0_GPIO_PIN                0
  #define _HTCFG_LEDC_SEG1_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG1_GPIO_PIN                1
  #define _HTCFG_LEDC_SEG2_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG2_GPIO_PIN                2
  #define _HTCFG_LEDC_SEG3_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG3_GPIO_PIN                3
  #define _HTCFG_LEDC_SEG4_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG4_GPIO_PIN                4
  #define _HTCFG_LEDC_SEG5_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG5_GPIO_PIN                5
  #define _HTCFG_LEDC_SEG6_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG6_GPIO_PIN                6
  #define _HTCFG_LEDC_SEG7_GPIO_PORT               A
  #define _HTCFG_LEDC_SEG7_GPIO_PIN                7
#endif

/* fCK_LED = 32Khz / 20 = 1600Hz */
/* Frame = 1600Hz / [8 * 4] = 50 Hz */
#define HTCFG_LEDC_CLOCK_PRESCAL                   (20)
#define _HTCFG_LEDC_CLOCK_NUMBER                   8

#define HTCFG_LEDC_COM1EN                          STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D1, EN)
#define HTCFG_LEDC_COM2EN                          STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D2, EN)
#define HTCFG_LEDC_COM3EN                          STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D3, EN)
#define HTCFG_LEDC_COM4EN                          STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D4, EN)

#define HTCFG_LEDC_COM1POL                         STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D1, POL)
#define HTCFG_LEDC_COM2POL                         STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D2, POL)
#define HTCFG_LEDC_COM3POL                         STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D3, POL)
#define HTCFG_LEDC_COM4POL                         STRCAT3(LEDC_COM, HTCFG_LEDC_COM_D4, POL)

#define HTCFG_LEDC_COM0_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_COM0_GPIO_PORT)
#define HTCFG_LEDC_COM0_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_COM0_GPIO_PIN)
#define HTCFG_LEDC_COM1_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_COM1_GPIO_PORT)
#define HTCFG_LEDC_COM1_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_COM1_GPIO_PIN)
#define HTCFG_LEDC_COM2_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_COM2_GPIO_PORT)
#define HTCFG_LEDC_COM2_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_COM2_GPIO_PIN)
#define HTCFG_LEDC_COM3_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_COM3_GPIO_PORT)
#define HTCFG_LEDC_COM3_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_COM3_GPIO_PIN)

#define HTCFG_LEDC_SEG0_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG0_GPIO_PORT)
#define HTCFG_LEDC_SEG0_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG0_GPIO_PIN)
#define HTCFG_LEDC_SEG1_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG1_GPIO_PORT)
#define HTCFG_LEDC_SEG1_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG1_GPIO_PIN)
#define HTCFG_LEDC_SEG2_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG2_GPIO_PORT)
#define HTCFG_LEDC_SEG2_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG2_GPIO_PIN)
#define HTCFG_LEDC_SEG3_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG3_GPIO_PORT)
#define HTCFG_LEDC_SEG3_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG3_GPIO_PIN)
#define HTCFG_LEDC_SEG4_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG4_GPIO_PORT)
#define HTCFG_LEDC_SEG4_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG4_GPIO_PIN)
#define HTCFG_LEDC_SEG5_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG5_GPIO_PORT)
#define HTCFG_LEDC_SEG5_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG5_GPIO_PIN)
#define HTCFG_LEDC_SEG6_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG6_GPIO_PORT)
#define HTCFG_LEDC_SEG6_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG6_GPIO_PIN)
#define HTCFG_LEDC_SEG7_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_LEDC_SEG7_GPIO_PORT)
#define HTCFG_LEDC_SEG7_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_LEDC_SEG7_GPIO_PIN)

#define HTCFG_LEDC_DUTY_CLOCK_NUMBER               STRCAT2(LEDC_DTYNUM_,   _HTCFG_LEDC_CLOCK_NUMBER)

#ifdef __cplusplus
}
#endif

#endif
