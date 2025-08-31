/*********************************************************************************************************//**
 * @file    BMC81M001_HT32/example_TCP/ht32_board_config.h
 * @version V1.0.1
 * @date    2024-10-10
 * @brief   The configuration file.
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H
/* Includes ------------------------------------------------------------------------------------------------*/
#include "bmduino_board.h"

/*----------------------------------------------------------------------------------------------------------*/
/* USE_BM53A367A_DVB                                                                                        */
/*----------------------------------------------------------------------------------------------------------*/
#if defined(USE_BM53A367A_DVB)
/* communication interface----------------------------------------------------------------------------------*/
#define BMC81M001_SERIAL                            (1)


#endif
/*----------------------------------------------------------------------------------------------------------*/
/* USE_HT32F52352_SK                                                                                        */
/*----------------------------------------------------------------------------------------------------------*/
#if defined(USE_HT32F52352_SK)
/* communication interface----------------------------------------------------------------------------------*/
#define BMC81M001_SERIAL                            (0)
/* UART Module Setting--------------------------------------------------------------------------------------*/
  #define HTCFG_UARTM_CH0                         USART0
  #define HTCFG_UARTM0_TX_GPIO_PORT               A
  #define HTCFG_UARTM0_TX_GPIO_PIN                2
  #define HTCFG_UARTM0_RX_GPIO_PORT               A
  #define HTCFG_UARTM0_RX_GPIO_PIN                3
  #define HTCFG_UARTM0_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM0_RX_BUFFER_SIZE             128
/* SPI Module Setting --------------------------------------------------------------------------------------*/
  #define HTCFG_SPI_CH0                           SPI0
  #define HTCFG_CH0_SCK_GPIO_PORT                 B
  #define HTCFG_CH0_SCK_GPIO_PIN                  3
  #define HTCFG_CH0_SEL_GPIO_PORT                 B
  #define HTCFG_CH0_SEL_GPIO_PIN                  2
  #define HTCFG_CH0_MOSI_GPIO_PORT                B
  #define HTCFG_CH0_MOSI_GPIO_PIN                 4
  #define HTCFG_CH0_MISO_GPIO_PORT                B
  #define HTCFG_CH0_MISO_GPIO_PIN                 5
/* I2C Master Setting --------------------------------------------------------------------------------------*/
  #define HTCFG_I2CM_CH0                          I2C1
  #define HTCFG_M0_SCL_GPIO_PORT                  A
  #define HTCFG_M0_SCL_GPIO_PIN                   0
  #define HTCFG_M0_SDA_GPIO_PORT                  A
  #define HTCFG_M0_SDA_GPIO_PIN                   1
#endif

#endif
