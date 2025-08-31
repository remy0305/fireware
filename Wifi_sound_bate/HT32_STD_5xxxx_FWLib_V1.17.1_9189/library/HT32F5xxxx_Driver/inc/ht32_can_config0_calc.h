/*********************************************************************************************************//**
 * @file    ht32_can_config0_calc.h
 * @version $Rev:: 8766         $
 * @date    $Date:: 2025-05-14 #$
 * @brief   The CAN config calculation features.
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
#ifndef __HT32_CAN_CONFIG0_CALC_H
#define __HT32_CAN_CONFIG0_CALC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define CAN_CF0_CALC_DEBUG                        (0)

/*----------------------------------------------------------------------------------------------------------*/
/* CAN Parameter Calculation                                                                                */
/* !!! DO NOT MODIFY !!!                                                                                    */
/*----------------------------------------------------------------------------------------------------------*/
#if (HTCFG_CAN_CORECLKSEL == 0)
  #define _HTCFG_CAN_CORE_CLK                     (LIBCFG_MAX_SPEED)
#else
  #define _HTCFG_CAN_CORE_CLK                     (HTCFG_CAN_CORECLK_MANUAL)
#endif

#define _HTCFG_CF0_CK_CAN                         (_HTCFG_CAN_CORE_CLK / (1 << HTCFG_CAN_CF0_CLK_DIV))
#define HTCFG_CAN_CF0_ERROR_RATE_PERCENT          (HTCFG_CAN_CF0_ERROR_RATE / 100)

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (25UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 25
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (24UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 24
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (23UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 23
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (22UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 22
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (21UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 21
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (20UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 20
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (19UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 19
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (18UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 18
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (17UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 17
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (16UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 16
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (15UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 15
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (14UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 14
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (13UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 13
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (12UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 12
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (11UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 11
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (10UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 10
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (9UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 9
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #undef _TMP_CF0_NBT
  #undef _TMP_CF0_PRESCALER
  #define _TMP_CF0_NBT                            (8UL)

  /* Compute the prescaler using integer-based rounding:                                                    */
  /* Prescaler = round(CAN_CLK / (BAUD × NBT))                                                              */
  /* = ((2 × CAN_CLK / (BAUD × NBT)) + 1) / 2                                                               */
  /* This implements true 4-round-5-up rounding behavior entirely with integer math,                        */
  /* avoiding the use of floating-point arithmetic while still providing accurate results.                  */
  #define _TMP_CF0_PRESCALER     (((2 * _HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * _TMP_CF0_NBT)) + 1) / 2)

  #if (_TMP_CF0_PRESCALER > 0)
    #undef _TMP_CF0_ERR_PPM
    #undef _TMP_CF0_BAUD_ACT
    /* Calculate the actual baud rate based on the selected nominal bit time (_TMP_CF0_NBT) */ 
    #define _TMP_CF0_BAUD_ACT (_HTCFG_CF0_CK_CAN / _TMP_CF0_PRESCALER / _TMP_CF0_NBT)

    /* Calculate the error in ppm (parts per million) by comparing the actual baud rate with the target baud rate */
    /* If the actual baud rate is higher than the target, calculate the error as the difference */
    #if (_TMP_CF0_BAUD_ACT > HTCFG_CAN_CF0_BAUDRATE)
      #define _TMP_CF0_ERR_PPM (((_TMP_CF0_BAUD_ACT      - HTCFG_CAN_CF0_BAUDRATE) * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #else
      /* Otherwise, calculate the error as the difference in the opposite case */
      #define _TMP_CF0_ERR_PPM (((HTCFG_CAN_CF0_BAUDRATE - _TMP_CF0_BAUD_ACT)      * 10000) / HTCFG_CAN_CF0_BAUDRATE)
    #endif
 
    /* Check if the error is within the allowed error rate (HTCFG_CAN_CF0_ERROR_RATE)                       */
    /* If the error is within the range, set the nominal bit time to the current value (_TMP_CF0_NBT)       */
    #if (_TMP_CF0_ERR_PPM <= HTCFG_CAN_CF0_ERROR_RATE_PERCENT)
      #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME _TMP_CF0_NBT
      #if (CAN_CF0_CALC_DEBUG == 1)
        #warning Set HTCFG_CAN_CF0_NOMINAL_BIT_TIME as 8
      #endif
    #endif
  #endif
#endif

#ifndef HTCFG_CAN_CF0_NOMINAL_BIT_TIME
  #error Can not find the suitable Nominal Bit Time setting. \
    1. Try to increase CK_CAN or lower the CAN Baudrate (HTCFG_CAN_CF0_BAUDRATE). \
    2. The baudrate error might be too large with current HTCFG_CAN_CF0_ERROR_RATE setting.
#endif

/* define value for CAN_Init()                                                                              */
#define CAN_CONF0_PRESCALER                       _TMP_CF0_PRESCALER
#define CAN_CONF0_BIT_TIME_TSEG1                  (HTCFG_CAN_CF0_NOMINAL_BIT_TIME - (HTCFG_CAN_CF0_NOMINAL_BIT_TIME * HTCFG_CAN_CF0_SAMPLE_POINT) / 100)
#define CAN_CONF0_BIT_TIME_TSEG0                  (HTCFG_CAN_CF0_NOMINAL_BIT_TIME - 1 - CAN_CONF0_BIT_TIME_TSEG1)
#define CAN_CONF0_BIT_TIME_SJW                    (HTCFG_CAN_CF0_BIT_TIME_SJW)

/*----------------------------------------------------------------------------------------------------------*/
/* CAN Parameter Checking                                                                                   */
/* !!! DO NOT MODIFY !!!                                                                                    */
/*----------------------------------------------------------------------------------------------------------*/
#if (CAN_CONF0_PRESCALER < 1)
  #error CAN Config 0 "Prescaler" value out of spec (must >= 1)! Try to lower the Nominal Bit Time or CAN Baudrate.
#endif

#if (CAN_CONF0_PRESCALER > 1024)
  #error CAN Config 0 "Prescaler" value out of spec (must <= 1024)!
#endif

#if (CAN_CONF0_BIT_TIME_TSEG0 > 16)
  #error CAN Config 0 "TSEG0" value out of spec (must <= 16)!
#endif

#if (CAN_CONF0_BIT_TIME_TSEG1 > 8)
  #if (HTCFG_CAN_CF0_NOMINAL_BIT_TIME < 16)
  #error CAN Config 0 "TSEG1" value out of spec (must <= 8)! May try to larger the Sample Point.
  #else

  // Reduce HTCFG_CAN_CF0_NOMINAL_BIT_TIME and try again
  #undef CAN_CONF0_PRESCALER
  #undef CAN_CONF0_BIT_TIME_TSEG1
  #undef CAN_CONF0_BIT_TIME_TSEG0
  #define HTCFG_CAN_CF0_NOMINAL_BIT_TIME2         (HTCFG_CAN_CF0_NOMINAL_BIT_TIME/2)
  #define CAN_CONF0_PRESCALER                     (_HTCFG_CF0_CK_CAN / (HTCFG_CAN_CF0_BAUDRATE * HTCFG_CAN_CF0_NOMINAL_BIT_TIME2))
  #define CAN_CONF0_BIT_TIME_TSEG1                (HTCFG_CAN_CF0_NOMINAL_BIT_TIME2 - (HTCFG_CAN_CF0_NOMINAL_BIT_TIME2 * HTCFG_CAN_CF0_SAMPLE_POINT) / 100)
  #define CAN_CONF0_BIT_TIME_TSEG0                (HTCFG_CAN_CF0_NOMINAL_BIT_TIME2 - 1 - CAN_CONF0_BIT_TIME_TSEG1)

  #if (CAN_CONF0_BIT_TIME_TSEG1 > 8)
  #error CAN Config 0 "TSEG1" value out of spec (must <= 8)! May try to lager the Sample Point.
  #endif

  #endif
#endif

#if (CAN_CONF0_BIT_TIME_TSEG1 > 4)
  #define CAN_CONF0_BIT_TIME_SJW_MAX              (4)
#else
  #define CAN_CONF0_BIT_TIME_SJW_MAX              CAN_CONF0_BIT_TIME_TSEG1
#endif

#if (HTCFG_CAN_CF0_BIT_TIME_SJW > CAN_CONF0_BIT_TIME_SJW_MAX)
  #error CAN Config 0 "SJW" value out of spec (must <= 4 and TSEG1)!
#endif

/*----------------------------------------------------------------------------------------------------------*/
/* CAN Config Check function                                                                                */
/*----------------------------------------------------------------------------------------------------------*/
#if (HTCFG_CAN_CONF_CHECK_ENABLE == 1)
#include <stdlib.h>
__STATIC_INLINE void CAN_Config0_Check(void)
{
  u32 Core_Clock  = _HTCFG_CAN_CORE_CLK;
  u32 IPPrescaler = (1 << HTCFG_CAN_CF0_CLK_DIV);
  u32 CK_CAN      = Core_Clock / IPPrescaler;
  u32 BRP         = CAN_CONF0_PRESCALER;
  u32 ftq         = CK_CAN / BRP;
  u32 TSEG0       = CAN_CONF0_BIT_TIME_TSEG0;
  u32 TSEG1       = CAN_CONF0_BIT_TIME_TSEG1;
  u32 NBT         = (1 + TSEG0 + TSEG1);
  u32 SamplePoint = ((NBT - TSEG1) * 100) / NBT;
  u32 Baudrate    = ftq / (1 + TSEG0 + TSEG1) ;
  s64 ErrorPpm   =  ((s64)Baudrate - (s64)HTCFG_CAN_CF0_BAUDRATE)*100000 / (s64)HTCFG_CAN_CF0_BAUDRATE;

  RETARGET_Configuration();

  printf("HT32 CAN Config 0 Check\r\n");
  printf("---------------------------------------------\r\n");
  printf("  Core Clock (CK_AHB, Hz)                = %d\r\n", Core_Clock);
  printf("  CAN IP Prescaler                       = %d\r\n", IPPrescaler);
  printf("  CAN IP Clock (CK_CAN, Hz)              = %d\r\n", CK_CAN);
  printf("  CAN Prescaler (BRP)                    = %d\r\n", BRP);
  printf("  1 / time quantum (1/tq, Hz)            = %d\r\n", ftq);
  printf("  Prop_Seg + Phase_Seg0                  = %d\r\n", TSEG0);
  printf("  Phase_Seg1                             = %d\r\n", TSEG1);
  printf("  Nominal Bit Time(NBT, calc)            = %d tq\r\n", (u32)HTCFG_CAN_CF0_NOMINAL_BIT_TIME);
  printf("  Nominal Bit Time(NBT, real)            = %d tq\r\n", NBT);
  printf("  Sample Point (setting)                 = %d %%\r\n", HTCFG_CAN_CF0_SAMPLE_POINT);
  printf("  Sample Point (real)                    = %d %%\r\n", SamplePoint);
  printf("  CAN BAUDRATE (setting, Hz)             = %d\r\n", HTCFG_CAN_CF0_BAUDRATE);
  printf("  CAN BAUDRATE (real, Hz)                = %d\r\n", Baudrate);
  printf("  BAUDRATE Error (setting vs. real, %%)  = %c%d.%03d %%\r\n",
                                                              (ErrorPpm >= 0) ? '+' : '-',
                                                              abs((s32)ErrorPpm) / 1000,
                                                              abs((s32)ErrorPpm) % 1000);
  printf("\r\n");
  printf("Please check the above setting is as expected....\r\n\r\n");
}
#endif


#ifdef __cplusplus
}
#endif

#endif
