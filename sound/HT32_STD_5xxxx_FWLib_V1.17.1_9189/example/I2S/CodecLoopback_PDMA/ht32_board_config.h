/*********************************************************************************************************//**
 * @file    I2S/CodecLoopback_PDMA/ht32_board_config.h
 * @version $Rev:: 8284         $
 * @date    $Date:: 2024-11-22 #$
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
#if (LIBCFG_I2S)
#else
  #error "This example code does not apply to the chip you selected."
#endif

/* !!! NOTICE !!!
   For the development board which uses "USE_HT32XXXXXX_DVB":
   1. The example requires external components on the expansion board but the development board can not use
      with it directly.
   2. The extra jumper/wired connections may be required to use this example.
*/

#if defined(USE_HT32F52352_SK)
  #define HTCFG_I2C_IPN                           I2C1
  #define HTCFG_I2C_SDA_GPIOX                     A
  #define HTCFG_I2C_SDA_GPION                     1
  #define HTCFG_I2C_SCL_GPIOX                     A
  #define HTCFG_I2C_SCL_GPION                     0

  #define HTCFG_I2S_SDO_GPIOX                     C
  #define HTCFG_I2S_SDO_GPION                     12
  #define HTCFG_I2S_SDI_GPIOX                     C
  #define HTCFG_I2S_SDI_GPION                     13
  #define HTCFG_I2S_MCLK_GPIOX                    A
  #define HTCFG_I2S_MCLK_GPION                    8
  #define HTCFG_I2S_BCLK_GPIOX                    C
  #define HTCFG_I2S_BCLK_GPION                    11
  #define HTCFG_I2S_WS_GPIOX                      C
  #define HTCFG_I2S_WS_GPION                      10

  #define HTCFG_I2S_VOICE_X_DIV                   (18)
  #define HTCFG_I2S_VOICE_Y_DIV                   (211)

  #define HTCFG_I2S_MUSIC_X_DIV                   (64)
  #define HTCFG_I2S_MUSIC_Y_DIV                   (125)
#endif

#if defined(USE_HT32F57352_SK)
  #define HTCFG_I2C_IPN                           I2C1
  #define HTCFG_I2C_SDA_GPIOX                     A
  #define HTCFG_I2C_SDA_GPION                     1
  #define HTCFG_I2C_SCL_GPIOX                     A
  #define HTCFG_I2C_SCL_GPION                     0

  #define HTCFG_I2S_SDO_GPIOX                     D
  #define HTCFG_I2S_SDO_GPION                     9
  #define HTCFG_I2S_SDI_GPIOX                     D
  #define HTCFG_I2S_SDI_GPION                     10
  #define HTCFG_I2S_MCLK_GPIOX                    A
  #define HTCFG_I2S_MCLK_GPION                    11
  #define HTCFG_I2S_BCLK_GPIOX                    D
  #define HTCFG_I2S_BCLK_GPION                    8
  #define HTCFG_I2S_WS_GPIOX                      A
  #define HTCFG_I2S_WS_GPION                      9

  #define HTCFG_I2S_VOICE_X_DIV                   (14)
  #define HTCFG_I2S_VOICE_Y_DIV                   (205)

  #define HTCFG_I2S_MUSIC_X_DIV                   (34)
  #define HTCFG_I2S_MUSIC_Y_DIV                   (83)
#endif

#if defined(USE_HT32F52367_SK)
  #define HTCFG_I2C_IPN                           I2C1
  #define HTCFG_I2C_SDA_GPIOX                     C
  #define HTCFG_I2C_SDA_GPION                     0
  #define HTCFG_I2C_SCL_GPIOX                     B
  #define HTCFG_I2C_SCL_GPION                     15

  #define HTCFG_I2S_SDO_GPIOX                     D
  #define HTCFG_I2S_SDO_GPION                     9
  #define HTCFG_I2S_SDI_GPIOX                     D
  #define HTCFG_I2S_SDI_GPION                     10
  #define HTCFG_I2S_MCLK_GPIOX                    A
  #define HTCFG_I2S_MCLK_GPION                    8
  #define HTCFG_I2S_BCLK_GPIOX                    D
  #define HTCFG_I2S_BCLK_GPION                    8
  #define HTCFG_I2S_WS_GPIOX                      A
  #define HTCFG_I2S_WS_GPION                      9

  #define HTCFG_I2S_VOICE_X_DIV                   (14)
  #define HTCFG_I2S_VOICE_Y_DIV                   (205)

  #define HTCFG_I2S_MUSIC_X_DIV                   (34)
  #define HTCFG_I2S_MUSIC_Y_DIV                   (83)
#endif

#if defined(USE_BM53A367A_DVB)
  #define HTCFG_I2C_IPN                           I2C1
  #define HTCFG_I2C_SDA_GPIOX                     C               // A4/D18
  #define HTCFG_I2C_SDA_GPION                     5
  #define HTCFG_I2C_SCL_GPIOX                     C               // A5/D19
  #define HTCFG_I2C_SCL_GPION                     4

  #define HTCFG_I2S_SDO_GPIOX                     C               // D21
  #define HTCFG_I2S_SDO_GPION                     12
  #define HTCFG_I2S_SDI_GPIOX                     C               // D20
  #define HTCFG_I2S_SDI_GPION                     13
  #define HTCFG_I2S_MCLK_GPIOX                    C               // A0/D14
  #define HTCFG_I2S_MCLK_GPION                    1
  #define HTCFG_I2S_BCLK_GPIOX                    C               // D13
  #define HTCFG_I2S_BCLK_GPION                    11
  #define HTCFG_I2S_WS_GPIOX                      A               // A6/D30
  #define HTCFG_I2S_WS_GPION                      0

  #define HTCFG_I2S_VOICE_X_DIV                   (14)
  #define HTCFG_I2S_VOICE_Y_DIV                   (205)

  #define HTCFG_I2S_MUSIC_X_DIV                   (34)
  #define HTCFG_I2S_MUSIC_Y_DIV                   (83)
#endif

#if defined(USE_BM18B367A_DVB)
  #define HTCFG_I2C_IPN                           I2C1
  #define HTCFG_I2C_SDA_GPIOX                     C               // A4/D18
  #define HTCFG_I2C_SDA_GPION                     5
  #define HTCFG_I2C_SCL_GPIOX                     C               // A5/D19
  #define HTCFG_I2C_SCL_GPION                     4

  #define HTCFG_I2S_SDO_GPIOX                     A               // A1/D15
  #define HTCFG_I2S_SDO_GPION                     2
  #define HTCFG_I2S_SDI_GPIOX                     A               // A2/D16
  #define HTCFG_I2S_SDI_GPION                     3
  #define HTCFG_I2S_MCLK_GPIOX                    A               // D2
  #define HTCFG_I2S_MCLK_GPION                    11
  #define HTCFG_I2S_BCLK_GPIOX                    A               // A0/D14
  #define HTCFG_I2S_BCLK_GPION                    1
  #define HTCFG_I2S_WS_GPIOX                      A               // A8/D30
  #define HTCFG_I2S_WS_GPION                      0

  #define HTCFG_I2S_VOICE_X_DIV                   (14)
  #define HTCFG_I2S_VOICE_Y_DIV                   (205)

  #define HTCFG_I2S_MUSIC_X_DIV                   (34)
  #define HTCFG_I2S_MUSIC_Y_DIV                   (83)
#endif

#if defined(USE_HT32F61355_SK) || defined(USE_HT32F61356_SK) || defined(USE_HT32F61357_SK)
  #define HTCFG_I2C_IPN                           I2C0
  #define HTCFG_I2C_SDA_GPIOX                     A
  #define HTCFG_I2C_SDA_GPION                     5
  #define HTCFG_I2C_SCL_GPIOX                     A
  #define HTCFG_I2C_SCL_GPION                     4

  #define HTCFG_I2S_SDO_GPIOX                     A
  #define HTCFG_I2S_SDO_GPION                     2
  #define HTCFG_I2S_SDI_GPIOX                     A
  #define HTCFG_I2S_SDI_GPION                     3
  #define HTCFG_I2S_MCLK_GPIOX                    A
  #define HTCFG_I2S_MCLK_GPION                    7
  #define HTCFG_I2S_BCLK_GPIOX                    A
  #define HTCFG_I2S_BCLK_GPION                    1
  #define HTCFG_I2S_WS_GPIOX                      A
  #define HTCFG_I2S_WS_GPION                      0

  #define HTCFG_I2S_VOICE_X_DIV                   (18)
  #define HTCFG_I2S_VOICE_Y_DIV                   (211)

  #define HTCFG_I2S_MUSIC_X_DIV                   (64)
  #define HTCFG_I2S_MUSIC_Y_DIV                   (125)
#endif

#define HTCFG_I2C_PORT                            STRCAT2(HT_, HTCFG_I2C_IPN)
#define HTCFG_I2C_IRQn                            STRCAT2(HTCFG_I2C_IPN, _IRQn)
#define HTCFG_I2C_IRQHandler                      STRCAT2(HTCFG_I2C_IPN, _IRQHandler)

#define HTCFG_I2C_SDA_GPIO_ID                     STRCAT2(GPIO_P,    HTCFG_I2C_SDA_GPIOX)
#define HTCFG_I2C_SDA_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_I2C_SDA_GPION)
#define HTCFG_I2C_SCL_GPIO_ID                     STRCAT2(GPIO_P,    HTCFG_I2C_SCL_GPIOX)
#define HTCFG_I2C_SCL_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_I2C_SCL_GPION)

#define HTCFG_I2S_SDO_GPIO_ID                     STRCAT2(GPIO_P,    HTCFG_I2S_SDO_GPIOX)
#define HTCFG_I2S_SDO_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_I2S_SDO_GPION)
#define HTCFG_I2S_SDI_GPIO_ID                     STRCAT2(GPIO_P,    HTCFG_I2S_SDI_GPIOX)
#define HTCFG_I2S_SDI_AFIO_PIN                    STRCAT2(AFIO_PIN_, HTCFG_I2S_SDI_GPION)
#define HTCFG_I2S_MCLK_GPIO_ID                    STRCAT2(GPIO_P,    HTCFG_I2S_MCLK_GPIOX)
#define HTCFG_I2S_MCLK_AFIO_PIN                   STRCAT2(AFIO_PIN_, HTCFG_I2S_MCLK_GPION)
#define HTCFG_I2S_BCLK_GPIO_ID                    STRCAT2(GPIO_P,    HTCFG_I2S_BCLK_GPIOX)
#define HTCFG_I2S_BCLK_AFIO_PIN                   STRCAT2(AFIO_PIN_, HTCFG_I2S_BCLK_GPION)
#define HTCFG_I2S_WS_GPIO_ID                      STRCAT2(GPIO_P,    HTCFG_I2S_WS_GPIOX)
#define HTCFG_I2S_WS_AFIO_PIN                     STRCAT2(AFIO_PIN_, HTCFG_I2S_WS_GPION)

#ifdef __cplusplus
}
#endif

#endif
