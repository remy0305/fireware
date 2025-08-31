/*********************************************************************************************************//**
 * @file    TM/PWMOut_PDMA_4CH/ht32_board_config.h
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
#if (LIBCFG_PDMA == 0)
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32F52253_SK)
  #define  HTCFG_PWM_IPN                          MCTM0

  #define _HTCFG_PWM0_GPIOX                       B
  #define _HTCFG_PWM0_GPION                       15
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       B
  #define _HTCFG_PWM1_GPION                       0
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       D
  #define _HTCFG_PWM2_GPION                       1
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       D
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_MCTM0_UEV1)
#endif

#if defined(USE_HT32F52352_SK)
  #define  HTCFG_PWM_IPN                          MCTM0

  #define _HTCFG_PWM0_GPIOX                       B
  #define _HTCFG_PWM0_GPION                       15
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       B
  #define _HTCFG_PWM1_GPION                       0
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       D
  #define _HTCFG_PWM2_GPION                       1
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       D
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_MCTM0_UEV1)
#endif

#if defined(USE_HT32F0008_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       0
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       1
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A
  #define _HTCFG_PWM2_GPION                       2
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F52354_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       0
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       1
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A
  #define _HTCFG_PWM2_GPION                       2
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F0006_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       C
  #define _HTCFG_PWM0_GPION                       4
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       C
  #define _HTCFG_PWM1_GPION                       5
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       8
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       C
  #define _HTCFG_PWM3_GPION                       9
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F57352_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       C
  #define _HTCFG_PWM0_GPION                       10
  #define _HTCFG_PWM0_CHN                         0
  
  #define _HTCFG_PWM1_GPIOX                       C
  #define _HTCFG_PWM1_GPION                       11
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       12
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       C
  #define _HTCFG_PWM3_GPION                       13
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F50343_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       0
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       1
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A
  #define _HTCFG_PWM2_GPION                       2
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F52367_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       0
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       1
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A
  #define _HTCFG_PWM2_GPION                       2
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_BM53A367A_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A               // D27
  #define _HTCFG_PWM0_GPION                       4
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A               // D28
  #define _HTCFG_PWM1_GPION                       5
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A               // D26
  #define _HTCFG_PWM2_GPION                       6
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A               // D29
  #define _HTCFG_PWM3_GPION                       7
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_BM18B367A_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A               // A8/D30
  #define _HTCFG_PWM0_GPION                       0
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A               // A0/D14
  #define _HTCFG_PWM1_GPION                       1
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A               // A1/D15
  #define _HTCFG_PWM2_GPION                       2
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A               // A2/D16
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F65240_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       7
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       C
  #define _HTCFG_PWM1_GPION                       4
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       5
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       C
  #define _HTCFG_PWM3_GPION                       6
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F65240_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       7
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       C
  #define _HTCFG_PWM1_GPION                       4
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       5
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       C
  #define _HTCFG_PWM3_GPION                       6
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F65232_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       B               // PIN W
  #define _HTCFG_PWM0_GPION                       8
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       B               // PIN V
  #define _HTCFG_PWM1_GPION                       7
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       B               // PIN U
  #define _HTCFG_PWM2_GPION                       6
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       C               // PIN NP
  #define _HTCFG_PWM3_GPION                       3
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F61355_SK) || defined(USE_HT32F61356_SK) || defined(USE_HT32F61357_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       4
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       5
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A
  #define _HTCFG_PWM2_GPION                       6
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       7
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F61245_SK)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       4
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       5
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A
  #define _HTCFG_PWM2_GPION                       6
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       7
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F54253_SK)
  #define  HTCFG_PWM_IPN                          MCTM0

  #define _HTCFG_PWM0_GPIOX                       B
  #define _HTCFG_PWM0_GPION                       15
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       B
  #define _HTCFG_PWM1_GPION                       0
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       6
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       B
  #define _HTCFG_PWM3_GPION                       9
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_MCTM0_UEV1)
#endif

#if defined(USE_HT32F50452_SK)
  #define  HTCFG_PWM_IPN                          MCTM0

  #define _HTCFG_PWM0_GPIOX                       B
  #define _HTCFG_PWM0_GPION                       15
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       10
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       8
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       B
  #define _HTCFG_PWM3_GPION                       9
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_MCTM0_UEV1)
#endif

#if defined(USE_HT32F53252_SK)
  #define  HTCFG_PWM_IPN                          MCTM0

  #define _HTCFG_PWM0_GPIOX                       B
  #define _HTCFG_PWM0_GPION                       15
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       10
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       8
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       B
  #define _HTCFG_PWM3_GPION                       9
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_MCTM0_UEV1)
#endif

#if defined(USE_HT32F50441_SK)
  #define  HTCFG_PWM_IPN                          MCTM0

  #define _HTCFG_PWM0_GPIOX                       B
  #define _HTCFG_PWM0_GPION                       15
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       10
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       B
  #define _HTCFG_PWM2_GPION                       2
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       B
  #define _HTCFG_PWM3_GPION                       9
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_MCTM0_UEV1)
#endif

#if defined(USE_HT32F53241_SK)
  #define  HTCFG_PWM_IPN                          MCTM0

  #define _HTCFG_PWM0_GPIOX                       B
  #define _HTCFG_PWM0_GPION                       15
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       10
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       B
  #define _HTCFG_PWM2_GPION                       2
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       B
  #define _HTCFG_PWM3_GPION                       9
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_MCTM0_UEV1)
#endif

#if defined(USE_HT32F52244_SK)
  #define  HTCFG_PWM_IPN                          PWM0

  #define _HTCFG_PWM0_GPIOX                       C
  #define _HTCFG_PWM0_GPION                       4
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       C
  #define _HTCFG_PWM1_GPION                       5
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       6
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       C
  #define _HTCFG_PWM3_GPION                       7
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_PWM0_UEV)
#endif

#if defined(USE_HT32F66242_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       C
  #define _HTCFG_PWM0_GPION                       5
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       6
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       3
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       5
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F66246_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       C
  #define _HTCFG_PWM0_GPION                       5
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       6
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       C
  #define _HTCFG_PWM2_GPION                       3
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       5
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#if defined(USE_HT32F65233_DVB)
  #define  HTCFG_PWM_IPN                          GPTM0

  #define _HTCFG_PWM0_GPIOX                       A
  #define _HTCFG_PWM0_GPION                       3
  #define _HTCFG_PWM0_CHN                         0

  #define _HTCFG_PWM1_GPIOX                       A
  #define _HTCFG_PWM1_GPION                       4
  #define _HTCFG_PWM1_CHN                         1

  #define _HTCFG_PWM2_GPIOX                       A
  #define _HTCFG_PWM2_GPION                       5
  #define _HTCFG_PWM2_CHN                         2

  #define _HTCFG_PWM3_GPIOX                       A
  #define _HTCFG_PWM3_GPION                       6
  #define _HTCFG_PWM3_CHN                         3

  #define HTCFG_PDMA_CH                           (PDMA_GPTM0_UEV)
#endif

#define HTCFG_PWM_PORT                            STRCAT2(HT_,             HTCFG_PWM_IPN)

#define HTCFG_PWM0_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_PWM0_GPIOX)
#define HTCFG_PWM0_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_PWM0_GPION)
#define HTCFG_PWM0_AFIO_FUN                       STRCAT2(AFIO_FUN_,       HTCFG_PWM_IPN)
#define HTCFG_PWM0_CH                             STRCAT2(TM_CH_,         _HTCFG_PWM0_CHN)

#define HTCFG_PWM1_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_PWM1_GPIOX)
#define HTCFG_PWM1_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_PWM1_GPION)
#define HTCFG_PWM1_AFIO_FUN                       STRCAT2(AFIO_FUN_,       HTCFG_PWM_IPN)
#define HTCFG_PWM1_CH                             STRCAT2(TM_CH_,         _HTCFG_PWM1_CHN)

#define HTCFG_PWM2_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_PWM2_GPIOX)
#define HTCFG_PWM2_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_PWM2_GPION)
#define HTCFG_PWM2_AFIO_FUN                       STRCAT2(AFIO_FUN_,       HTCFG_PWM_IPN)
#define HTCFG_PWM2_CH                             STRCAT2(TM_CH_,         _HTCFG_PWM2_CHN)

#define HTCFG_PWM3_GPIO_ID                        STRCAT2(GPIO_P,         _HTCFG_PWM3_GPIOX)
#define HTCFG_PWM3_AFIO_PIN                       STRCAT2(AFIO_PIN_,      _HTCFG_PWM3_GPION)
#define HTCFG_PWM3_AFIO_FUN                       STRCAT2(AFIO_FUN_,       HTCFG_PWM_IPN)
#define HTCFG_PWM3_CH                             STRCAT2(TM_CH_,         _HTCFG_PWM3_CHN)


#ifdef __cplusplus
}
#endif

#endif
