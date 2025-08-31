/*********************************************************************************************************//**
 * @file    TM/PWM_Buzzer/ht32_board_config.h
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
/* !!! NOTICE !!!
   For the development board which uses "USE_HT32XXXXXX_DVB":
   1. The example requires external components on the expansion board but the development board can not use
      with it directly.
   2. The extra jumper/wired connections may be required to use this example.
*/

#if defined(USE_HT32F50030_SK)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     4
  #define  HTCFG_BUZZER_IPN                       SCTM2
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F0006_DVB)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     4
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F0008_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     8
  #define  HTCFG_BUZZER_IPN                       PWM1
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F50230_SK)
  #define _HTCFG_BUZZER_GPIOX                     B
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F50241_SK)
  #define _HTCFG_BUZZER_GPIOX                     B
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       MCTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F50343_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     7
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F52230_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     14
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F52241_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     8
  #define  HTCFG_BUZZER_IPN                       SCTM2
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F52253_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     10
  #define  HTCFG_BUZZER_IPN                       MCTM0
  #define  HTCFG_BUZZER_CHN                       1
#endif

#if defined(USE_HT32F52341_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     8
  #define  HTCFG_BUZZER_IPN                       SCTM2
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F52352_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     10
  #define  HTCFG_BUZZER_IPN                       MCTM0
  #define  HTCFG_BUZZER_CHN                       1
#endif

#if defined(USE_HT32F52354_SK)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     13
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F52367_SK)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     13
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_BM53A367A_DVB)
  #define _HTCFG_BUZZER_GPIOX                     A               // D29
  #define _HTCFG_BUZZER_GPION                     7
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_BM18B367A_DVB)
  #define _HTCFG_BUZZER_GPIOX                     A               // A2/D16
  #define _HTCFG_BUZZER_GPION                     3
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F57341_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     7
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F57352_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     7
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F61141_SK)  //PRELIMINARY_NOT_TEST
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     11
  #define  HTCFG_BUZZER_IPN                       SCTM1
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F65240_DVB)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     7
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       0
  #define  HTCFG_BUZZER_TM_REDEFINE               1
#endif

#if defined(USE_HT32F65240_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     8
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       0
  #define  HTCFG_BUZZER_TM_REDEFINE               1
#endif

#if defined(USE_HT32F65232_DVB)
  #define _HTCFG_BUZZER_GPIOX                     A               // PIN HallA
  #define _HTCFG_BUZZER_GPION                     8
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       0
  #define  HTCFG_BUZZER_TM_REDEFINE               1
#endif

#if defined(USE_HT32F61355_SK) || defined(USE_HT32F61356_SK) || defined(USE_HT32F61357_SK)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F61245_SK)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F54241_SK)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     5
  #define  HTCFG_BUZZER_IPN                       SCTM1
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F54253_SK)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     12
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       2
#endif

#if defined(USE_HT32F67051_SK)  //PRELIMINARY_NOT_TEST
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     11
  #define  HTCFG_BUZZER_IPN                       SCTM1
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F67233_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     14
  #define  HTCFG_BUZZER_IPN                       GPTM0
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F50452_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     10
  #define  HTCFG_BUZZER_IPN                       MCTM0
  #define  HTCFG_BUZZER_CHN                       1
#endif

#if defined(USE_HT32F53252_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     10
  #define  HTCFG_BUZZER_IPN                       MCTM0
  #define  HTCFG_BUZZER_CHN                       1
#endif

#if defined(USE_HT32F50441_SK)
  #define _HTCFG_BUZZER_GPIOX                     B
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       MCTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F53241_SK)
  #define _HTCFG_BUZZER_GPIOX                     B
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       MCTM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F52244_SK)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     8
  #define  HTCFG_BUZZER_IPN                       PWM0
  #define  HTCFG_BUZZER_CHN                       3
#endif

#if defined(USE_HT32F66242_DVB)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       SCTM1
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F66246_DVB)
  #define _HTCFG_BUZZER_GPIOX                     C
  #define _HTCFG_BUZZER_GPION                     9
  #define  HTCFG_BUZZER_IPN                       SCTM1
  #define  HTCFG_BUZZER_CHN                       0
#endif

#if defined(USE_HT32F65233_DVB)
  #define _HTCFG_BUZZER_GPIOX                     A
  #define _HTCFG_BUZZER_GPION                     3
  #define  HTCFG_BUZZER_IPN                       SCTM1
  #define  HTCFG_BUZZER_CHN                       0
#endif

#ifdef __cplusplus
}
#endif

#endif
