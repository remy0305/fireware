/*********************************************************************************************************//**
 * @file    TM/InternalTrigger/ht32_board_config.h
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
#define HTCFG_SLAVE_PERIOD                        (1000)
#define HTCFG_MASTER_PERIOD                       (1000)

#if defined(USE_HT32F52241_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F52253_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F52341_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F52352_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   B
  #define _HTCFG_TM_SLAVE_GPION                   0
  #define  HTCFG_TM_SLAVE_IPN                     MCTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI2

  #define _HTCFG_TM_MASTER_GPIOX                  C
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    GPTM1
  #define _HTCFG_TM_MASTER_CHN                    0
#endif

#if defined(USE_HT32F0008_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  C
  #define _HTCFG_TM_MASTER_GPION                  4
  #define  HTCFG_TM_MASTER_IPN                    PWM1
  #define _HTCFG_TM_MASTER_CHN                    0
#endif

#if defined(USE_HT32F50230_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI2

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  8
  #define  HTCFG_TM_MASTER_IPN                    PWM1
  #define _HTCFG_TM_MASTER_CHN                    3
#endif

#if defined(USE_HT32F50241_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI2

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  8
  #define  HTCFG_TM_MASTER_IPN                    PWM1
  #define _HTCFG_TM_MASTER_CHN                    3
#endif

#if defined(USE_HT32F52354_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   C
  #define _HTCFG_TM_SLAVE_GPION                   5
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F57341_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI2

  #define _HTCFG_TM_MASTER_GPIOX                  D
  #define _HTCFG_TM_MASTER_GPION                  4
  #define  HTCFG_TM_MASTER_IPN                    PWM1
  #define _HTCFG_TM_MASTER_CHN                    0
#endif

#if defined(USE_HT32F57352_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI2

  #define _HTCFG_TM_MASTER_GPIOX                  D
  #define _HTCFG_TM_MASTER_GPION                  6
  #define  HTCFG_TM_MASTER_IPN                    PWM1
  #define _HTCFG_TM_MASTER_CHN                    2
#endif

#if defined(USE_HT32F50343_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI2

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  3
  #define  HTCFG_TM_MASTER_IPN                    PWM1
  #define _HTCFG_TM_MASTER_CHN                    3
#endif

#if defined(USE_HT32F52367_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   B
  #define _HTCFG_TM_SLAVE_GPION                   0
  #define  HTCFG_TM_SLAVE_IPN                     MCTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  C
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    GPTM0
  #define _HTCFG_TM_MASTER_CHN                    0
#endif

#if defined(USE_BM53A367A_DVB)
  #define _HTCFG_TM_SLAVE_GPIOX                   B               // D2
  #define _HTCFG_TM_SLAVE_GPION                   0
  #define  HTCFG_TM_SLAVE_IPN                     MCTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A               // D27
  #define _HTCFG_TM_MASTER_GPION                  4
  #define  HTCFG_TM_MASTER_IPN                    GPTM0
  #define _HTCFG_TM_MASTER_CHN                    0
#endif

#if defined(USE_BM18B367A_DVB)
  #define _HTCFG_TM_SLAVE_GPIOX                   B               // D5
  #define _HTCFG_TM_SLAVE_GPION                   0
  #define  HTCFG_TM_SLAVE_IPN                     MCTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A               // A3/D17
  #define _HTCFG_TM_MASTER_GPION                  4
  #define  HTCFG_TM_MASTER_IPN                    GPTM0
  #define _HTCFG_TM_MASTER_CHN                    0
#endif

#if defined(USE_HT32F65240_DVB)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   9
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     3
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  B
  #define _HTCFG_TM_MASTER_GPION                  8
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    3

  #define _HTCFG_TM_REDEFINE                      1
#endif

#if defined(USE_HT32F65240_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   9
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     3
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  B
  #define _HTCFG_TM_MASTER_GPION                  8
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    3

  #define _HTCFG_TM_REDEFINE                      1
#endif

#if defined(USE_HT32F65232_DVB)
  #define _HTCFG_TM_SLAVE_GPIOX                   B               // PIN V
  #define _HTCFG_TM_SLAVE_GPION                   7
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  C
  #define _HTCFG_TM_MASTER_GPION                  2
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    3

  #define _HTCFG_TM_REDEFINE                      1
#endif

#if defined(USE_HT32F54241_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F54253_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F50452_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F53252_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F50441_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F53241_SK)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   1
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  A
  #define _HTCFG_TM_MASTER_GPION                  10
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    1
#endif

#if defined(USE_HT32F66242_DVB)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   6
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  C
  #define _HTCFG_TM_MASTER_GPION                  9
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    0

  #define _HTCFG_TM_REDEFINE                      1
#endif

#if defined(USE_HT32F66246_DVB)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   6
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     1
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  C
  #define _HTCFG_TM_MASTER_GPION                  9
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    0

  #define _HTCFG_TM_REDEFINE                      1
#endif

#if defined(USE_HT32F65233_DVB)
  #define _HTCFG_TM_SLAVE_GPIOX                   A
  #define _HTCFG_TM_SLAVE_GPION                   3
  #define  HTCFG_TM_SLAVE_IPN                     GPTM0
  #define _HTCFG_TM_SLAVE_CHN                     0
  #define  HTCFG_TM_SLAVE_TRSEL_ITI               TM_TRSEL_ITI1

  #define _HTCFG_TM_MASTER_GPIOX                  B
  #define _HTCFG_TM_MASTER_GPION                  3
  #define  HTCFG_TM_MASTER_IPN                    MCTM0
  #define _HTCFG_TM_MASTER_CHN                    0

  #define _HTCFG_TM_REDEFINE                      1
#endif

#define HTCFG_SLAVE_GPIO_ID                       STRCAT2(GPIO_P,    _HTCFG_TM_SLAVE_GPIOX)
#define HTCFG_SLAVE_AFIO_PIN                      STRCAT2(AFIO_PIN_, _HTCFG_TM_SLAVE_GPION)
#define HTCFG_SLAVE_AFIO_FUN                      STRCAT2(AFIO_FUN_,  HTCFG_TM_SLAVE_IPN)
#define HTCFG_SLAVE_PORT                          STRCAT2(HT_,        HTCFG_TM_SLAVE_IPN)
#define HTCFG_SLAVE_CH                            STRCAT2(TM_CH_,    _HTCFG_TM_SLAVE_CHN)
#define HTCFG_SLAVE_IRQ                           STRCAT2(HTCFG_TM_SLAVE_IPN, _IRQn)
#define HTCFG_SLAVE_IRQHandler                    STRCAT2(HTCFG_TM_SLAVE_IPN, _IRQHandler)

#define HTCFG_MASTER_GPIO_ID                      STRCAT2(GPIO_P,    _HTCFG_TM_MASTER_GPIOX)
#define HTCFG_MASTER_AFIO_PIN                     STRCAT2(AFIO_PIN_, _HTCFG_TM_MASTER_GPION)
#define HTCFG_MASTER_AFIO_FUN                     STRCAT2(AFIO_FUN_,  HTCFG_TM_MASTER_IPN)
#define HTCFG_MASTER_PORT                         STRCAT2(HT_,        HTCFG_TM_MASTER_IPN)
#define HTCFG_MASTER_CH                           STRCAT2(TM_CH_,    _HTCFG_TM_MASTER_CHN)
#define HTCFG_MASTER_IRQ                          STRCAT2(HTCFG_TM_MASTER_IPN, _IRQn)
#define HTCFG_MASTER_IRQHandler                   STRCAT2(HTCFG_TM_MASTER_IPN, _IRQHandler)

#if (_HTCFG_TM_REDEFINE == 1)
  /*
    Do the following re-define
      GPTMn_IRQn          ->    GPTMn_G_IRQn
      GPTMn_IRQHandler    ->    GPTMn_G_IRQHandler
      MCTMn_IRQn          ->    MCTMn_UP_IRQn
      MCTMn_IRQHandler    ->    MCTMn_UP_IRQHandler
  */
  #undef HTCFG_SLAVE_IRQ
  #undef HTCFG_SLAVE_IRQHandler

  #if IS_IPN_GPTM(HTCFG_TM_SLAVE_IPN)
  #define HTCFG_SLAVE_IRQ                         STRCAT2(HTCFG_TM_SLAVE_IPN,  _G_IRQn)
  #define HTCFG_SLAVE_IRQHandler                  STRCAT2(HTCFG_TM_SLAVE_IPN,  _G_IRQHandler)
  #endif

  #if IS_IPN_MCTM(HTCFG_TM_SLAVE_IPN)
  #define HTCFG_SLAVE_IRQ                         STRCAT2(HTCFG_TM_SLAVE_IPN,  _UP_IRQn)
  #define HTCFG_SLAVE_IRQHandler                  STRCAT2(HTCFG_TM_SLAVE_IPN,  _UP_IRQHandler)
  #endif

  #undef HTCFG_MASTER_IRQ
  #undef HTCFG_MASTER_IRQHandler

  #if IS_IPN_GPTM(HTCFG_TM_MASTER_IPN)
  #define HTCFG_MASTER_IRQ                        STRCAT2(HTCFG_TM_MASTER_IPN,  _G_IRQn)
  #define HTCFG_MASTER_IRQHandler                 STRCAT2(HTCFG_TM_MASTER_IPN,  _G_IRQHandler)
  #endif

  #if IS_IPN_MCTM(HTCFG_TM_MASTER_IPN)
  #define HTCFG_MASTER_IRQ                        STRCAT2(HTCFG_TM_MASTER_IPN,  _UP_IRQn)
  #define HTCFG_MASTER_IRQHandler                 STRCAT2(HTCFG_TM_MASTER_IPN,  _UP_IRQHandler)
  #endif
#endif


#ifdef __cplusplus
}
#endif

#endif
