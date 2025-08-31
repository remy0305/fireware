/*********************************************************************************************************//**
 * @file    bmduino_check.h
 * @version $Rev:: 7842         $
 * @date    $Date:: 2024-07-10 #$
 * @brief   WIRE/SPI/SERIAL select check of BMduino.
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
#ifndef __BMDUINO_CHECK_H
#define __BMDUINO_CHECK_H

/* SERIAL CHECK --------------------------------------------------------------------------------------------*/
#ifdef HTCFG_UARTM_CH0
  #define SERIAL_CHECK                     1
#else
  #define SERIAL_CHECK                     0
#endif

#ifdef HTCFG_UARTM_CH1
  #define SERIAL1_CHECK                    1
#else
  #define SERIAL1_CHECK                    0
#endif

#ifdef HTCFG_UARTM_CH2
  #define SERIAL2_CHECK                    1
#else
  #define SERIAL2_CHECK                    0
#endif

#ifdef HTCFG_UARTM_CH3
  #define SERIAL3_CHECK                    1
#else
  #define SERIAL3_CHECK                    0
#endif

#ifdef HTCFG_UARTM_CH4
  #define SERIAL4_CHECK                    1
#else
  #define SERIAL4_CHECK                    0
#endif

#define CHECK_SERIALn(SERIAL_NUMBER) \
        ((SERIAL_NUMBER) == 0 ? (SERIAL_CHECK  ? 0 : -1) : \
        ((SERIAL_NUMBER) == 1 ? (SERIAL1_CHECK ? 1 : -1) : \
        ((SERIAL_NUMBER) == 2 ? (SERIAL2_CHECK ? 2 : -1) : \
        ((SERIAL_NUMBER) == 3 ? (SERIAL3_CHECK ? 3 : -1) : \
        ((SERIAL_NUMBER) == 4 ? (SERIAL4_CHECK ? 4 : -1) :-1)))))


/* SPI CHECK --------------------------------------------------------------------------------------------*/
#ifdef HTCFG_SPI_CH0
  #define SPI_CHECK                     1
#else
  #define SPI_CHECK                     0
#endif

#ifdef HTCFG_SPI_CH1
  #define SPI1_CHECK                    1
#else
  #define SPI1_CHECK                    0
#endif

#ifdef HTCFG_SPI_CH2
  #define SPI2_CHECK                    1
#else
  #define SPI2_CHECK                    0
#endif

#ifdef HTCFG_SPI_CH3
  #define SPI3_CHECK                    1
#else
  #define SPI3_CHECK                    0
#endif

#define CHECK_SPIn(SPI_NUMBER) \
        ((SPI_NUMBER) == 0 ? (SPI_CHECK  ? 0 : -1) : \
        ((SPI_NUMBER) == 1 ? (SPI1_CHECK ? 1 : -1) : \
        ((SPI_NUMBER) == 2 ? (SPI2_CHECK ? 2 : -1) : \
        ((SPI_NUMBER) == 3 ? (SPI3_CHECK ? 3 : -1) : -1))))


/* WIRE CHECK --------------------------------------------------------------------------------------------*/
#ifdef HTCFG_I2CM_CH0
  #define WIRE_CHECK                     1
#else
  #define WIRE_CHECK                     0
#endif

#ifdef HTCFG_I2CM_CH1
  #define WIRE1_CHECK                    1
#else
  #define WIRE1_CHECK                    0
#endif

#ifdef HTCFG_I2CM_CH2
  #define WIRE2_CHECK                    1
#else
  #define WIRE2_CHECK                    0
#endif

#ifdef HTCFG_I2CM_CH3
  #define WIRE3_CHECK                    1
#else
  #define WIRE3_CHECK                    0
#endif

#define CHECK_WIREn(WIRE_NUMBER) \
        ((WIRE_NUMBER) == 0 ? (WIRE_CHECK  ? 0 : -1) : \
        ((WIRE_NUMBER) == 1 ? (WIRE1_CHECK ? 1 : -1) : \
        ((WIRE_NUMBER) == 2 ? (WIRE2_CHECK ? 2 : -1) : \
        ((WIRE_NUMBER) == 3 ? (WIRE3_CHECK ? 3 : -1) : -1))))


#endif
