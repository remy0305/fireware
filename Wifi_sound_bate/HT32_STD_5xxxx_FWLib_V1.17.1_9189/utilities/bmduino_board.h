/*********************************************************************************************************//**
 * @file    bmduino_board.h
 * @version $Rev:: 7842         $
 * @date    $Date:: 2024-07-10 #$
 * @brief   Pin assignment of BMduino.
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
#ifndef __BMDUINO_BOARD_H
#define __BMDUINO_BOARD_H

/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_BM53A367A_DVB)

/*----------------------------------------------------------------------------------------------------------*/
/* UART Module Setting                                                                                      */
/*----------------------------------------------------------------------------------------------------------*/
  // Serial
  #define HTCFG_UARTM_CH0                         USART0
  #define HTCFG_UARTM0_TX_GPIO_PORT               A
  #define HTCFG_UARTM0_TX_GPIO_PIN                8
  #define HTCFG_UARTM0_RX_GPIO_PORT               A
  #define HTCFG_UARTM0_RX_GPIO_PIN                10
  #define HTCFG_UARTM0_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM0_RX_BUFFER_SIZE             128

  // Serial1
  #define HTCFG_UARTM_CH1                         UART1
  #define HTCFG_UARTM1_TX_GPIO_PORT               C
  #define HTCFG_UARTM1_TX_GPIO_PIN                12
  #define HTCFG_UARTM1_RX_GPIO_PORT               C
  #define HTCFG_UARTM1_RX_GPIO_PIN                13
  #define HTCFG_UARTM1_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM1_RX_BUFFER_SIZE             128

  // Serial2
  #define HTCFG_UARTM_CH2                         UART3
  #define HTCFG_UARTM2_TX_GPIO_PORT               C
  #define HTCFG_UARTM2_TX_GPIO_PIN                14
  #define HTCFG_UARTM2_RX_GPIO_PORT               C
  #define HTCFG_UARTM2_RX_GPIO_PIN                15
  #define HTCFG_UARTM2_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM2_RX_BUFFER_SIZE             128

  // Serial3
  #define HTCFG_UARTM_CH3                         USART1
  #define HTCFG_UARTM3_TX_GPIO_PORT               A
  #define HTCFG_UARTM3_TX_GPIO_PIN                4
  #define HTCFG_UARTM3_RX_GPIO_PORT               A
  #define HTCFG_UARTM3_RX_GPIO_PIN                5
  #define HTCFG_UARTM3_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM3_RX_BUFFER_SIZE             128

  // Serial4
  #define HTCFG_UARTM_CH4                         UART2
  #define HTCFG_UARTM4_TX_GPIO_PORT               B
  #define HTCFG_UARTM4_TX_GPIO_PIN                2
  #define HTCFG_UARTM4_RX_GPIO_PORT               B
  #define HTCFG_UARTM4_RX_GPIO_PIN                3
  #define HTCFG_UARTM4_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM4_RX_BUFFER_SIZE             128

  #define USART0_IRQ_HANDLER()                    _UARTM_IRQHandler(UARTM_CH0);
  #define UART1_IRQ_HANDLER()                     _UARTM_IRQHandler(UARTM_CH1);
  #define UART3_IRQ_HANDLER()                     _UARTM_IRQHandler(UARTM_CH2);
  #define USART1_IRQ_HANDLER()                    _UARTM_IRQHandler(UARTM_CH3);
  #define UART2_IRQ_HANDLER()                     _UARTM_IRQHandler(UARTM_CH4);

/*----------------------------------------------------------------------------------------------------------*/
/* SPI Module Setting                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
  // SPI
  #define HTCFG_CH0_SCK_GPIO_PORT                 C
  #define HTCFG_CH0_SCK_GPIO_PIN                  11
  #define HTCFG_CH0_SEL_GPIO_PORT                 C
  #define HTCFG_CH0_SEL_GPIO_PIN                  10
  #define HTCFG_CH0_MOSI_GPIO_PORT                C
  #define HTCFG_CH0_MOSI_GPIO_PIN                 8
  #define HTCFG_CH0_MISO_GPIO_PORT                C
  #define HTCFG_CH0_MISO_GPIO_PIN                 9
  #define HTCFG_SPI_CH0                           SPI1

  // SPI1
  #define HTCFG_CH1_SCK_GPIO_PORT                 A
  #define HTCFG_CH1_SCK_GPIO_PIN                  4
  #define HTCFG_CH1_SEL_GPIO_PORT                 A
  #define HTCFG_CH1_SEL_GPIO_PIN                  7
  #define HTCFG_CH1_MOSI_GPIO_PORT                A
  #define HTCFG_CH1_MOSI_GPIO_PIN                 5
  #define HTCFG_CH1_MISO_GPIO_PORT                A
  #define HTCFG_CH1_MISO_GPIO_PIN                 11
  #define HTCFG_SPI_CH1                           SPI0

  // SPI2
  #define HTCFG_CH2_SCK_GPIO_PORT                 B
  #define HTCFG_CH2_SCK_GPIO_PIN                  3
  #define HTCFG_CH2_SEL_GPIO_PORT                 B
  #define HTCFG_CH2_SEL_GPIO_PIN                  2
  #define HTCFG_CH2_MOSI_GPIO_PORT                B
  #define HTCFG_CH2_MOSI_GPIO_PIN                 4
  #define HTCFG_CH2_MISO_GPIO_PORT                B
  #define HTCFG_CH2_MISO_GPIO_PIN                 5
  #define HTCFG_SPI_CH2                           QSPI

  #define SPI0_IRQ_HANDLER()                      _SPIAPI_IRQHandler(SPI_API_CH1);
  #define SPI1_IRQ_HANDLER()                      _SPIAPI_IRQHandler(SPI_API_CH0);
  #define QSPI_IRQ_HANDLER()                      _SPIAPI_IRQHandler(SPI_API_CH2);

  #if defined(SPICFG_SUPPORT_CH) && (SPICFG_SUPPORT_CH < 3)
    #error "SPICFG_SUPPORT_CH setting in spi_module_config.h is not correct!!"
  #endif

/*----------------------------------------------------------------------------------------------------------*/
/* I2C Master Setting                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
  // Wire
  #define HTCFG_I2CM_CH0                          I2C1
  #define HTCFG_M0_SCL_GPIO_PORT                  C
  #define HTCFG_M0_SCL_GPIO_PIN                   4
  #define HTCFG_M0_SDA_GPIO_PORT                  C
  #define HTCFG_M0_SDA_GPIO_PIN                   5

  // Wire1
  #define HTCFG_I2CM_CH1                          I2C0
  #define HTCFG_M1_SCL_GPIO_PORT                  C
  #define HTCFG_M1_SCL_GPIO_PIN                   12
  #define HTCFG_M1_SDA_GPIO_PORT                  C
  #define HTCFG_M1_SDA_GPIO_PIN                   13

  // Wire2
  #define HTCFG_I2CM_CH2                          I2C0
  #define HTCFG_M2_SCL_GPIO_PORT                  C
  #define HTCFG_M2_SCL_GPIO_PIN                   14
  #define HTCFG_M2_SDA_GPIO_PORT                  C
  #define HTCFG_M2_SDA_GPIO_PIN                   15

  #define I2C0_IRQ_HANDLER()                      I2CMaster_IRQHandler(I2C_MASTER_CH1); \
                                                  I2CMaster_IRQHandler(I2C_MASTER_CH2);
  #define I2C1_IRQ_HANDLER()                      I2CMaster_IRQHandler(I2C_MASTER_CH0);

  #if defined(I2C_MASTER_SUPPORT_CH) && (I2C_MASTER_SUPPORT_CH < 3)
    #error "I2C_MASTER_SUPPORT_CH setting in i2c_master_config.h is not correct!!"
  #endif

#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_BM18B367A_DVB)

/*----------------------------------------------------------------------------------------------------------*/
/* UART Module Setting                                                                                      */
/*----------------------------------------------------------------------------------------------------------*/
  // Serial
  #define HTCFG_UARTM_CH0                         USART0
  #define HTCFG_UARTM0_TX_GPIO_PORT               A
  #define HTCFG_UARTM0_TX_GPIO_PIN                8
  #define HTCFG_UARTM0_RX_GPIO_PORT               A
  #define HTCFG_UARTM0_RX_GPIO_PIN                10
  #define HTCFG_UARTM0_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM0_RX_BUFFER_SIZE             128

  // Serial2
  #define HTCFG_UARTM_CH2                         UART1
  #define HTCFG_UARTM2_TX_GPIO_PORT               C
  #define HTCFG_UARTM2_TX_GPIO_PIN                12
  #define HTCFG_UARTM2_RX_GPIO_PORT               C
  #define HTCFG_UARTM2_RX_GPIO_PIN                13
  #define HTCFG_UARTM2_TX_BUFFER_SIZE             128
  #define HTCFG_UARTM2_RX_BUFFER_SIZE             128

  #define USART0_IRQ_HANDLER()                    _UARTM_IRQHandler(UARTM_CH0);
  #define UART1_IRQ_HANDLER()                     _UARTM_IRQHandler(UARTM_CH2);

/*----------------------------------------------------------------------------------------------------------*/
/* SPI Module Setting                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
  // SPI
  #define HTCFG_CH0_SCK_GPIO_PORT                 C
  #define HTCFG_CH0_SCK_GPIO_PIN                  2
  #define HTCFG_CH0_SEL_GPIO_PORT                 C
  #define HTCFG_CH0_SEL_GPIO_PIN                  1
  #define HTCFG_CH0_MOSI_GPIO_PORT                C
  #define HTCFG_CH0_MOSI_GPIO_PIN                 3
  #define HTCFG_CH0_MISO_GPIO_PORT                B
  #define HTCFG_CH0_MISO_GPIO_PIN                 6
  #define HTCFG_SPI_CH0                           SPI1

  // SPI1
  #define HTCFG_CH1_SCK_GPIO_PORT                 A
  #define HTCFG_CH1_SCK_GPIO_PIN                  15
  #define HTCFG_CH1_SEL_GPIO_PORT                 A
  #define HTCFG_CH1_SEL_GPIO_PIN                  14
  #define HTCFG_CH1_MOSI_GPIO_PORT                B
  #define HTCFG_CH1_MOSI_GPIO_PIN                 0
  #define HTCFG_CH1_MISO_GPIO_PORT                B
  #define HTCFG_CH1_MISO_GPIO_PIN                 1
  #define HTCFG_SPI_CH1                           QSPI

  #define SPI1_IRQ_HANDLER()                      _SPIAPI_IRQHandler(SPI_API_CH0);
  #define QSPI_IRQ_HANDLER()                      _SPIAPI_IRQHandler(SPI_API_CH1);

  #if defined(SPICFG_SUPPORT_CH) && (SPICFG_SUPPORT_CH < 2)
    #error "SPICFG_SUPPORT_CH setting in spi_module_config.h is not correct!!"
  #endif

/*----------------------------------------------------------------------------------------------------------*/
/* I2C Master Setting                                                                                       */
/*----------------------------------------------------------------------------------------------------------*/
  // Wire
  #define HTCFG_I2CM_CH0                          I2C1
  #define HTCFG_M0_SCL_GPIO_PORT                  C
  #define HTCFG_M0_SCL_GPIO_PIN                   4
  #define HTCFG_M0_SDA_GPIO_PORT                  C
  #define HTCFG_M0_SDA_GPIO_PIN                   5

  // Wire2
  #define HTCFG_I2CM_CH2                          I2C0
  #define HTCFG_M2_SCL_GPIO_PORT                  C
  #define HTCFG_M2_SCL_GPIO_PIN                   12
  #define HTCFG_M2_SDA_GPIO_PORT                  C
  #define HTCFG_M2_SDA_GPIO_PIN                   13

  #define I2C0_IRQ_HANDLER()                      I2CMaster_IRQHandler(I2C_MASTER_CH2);
  #define I2C1_IRQ_HANDLER()                      I2CMaster_IRQHandler(I2C_MASTER_CH0);

  #if defined(I2C_MASTER_SUPPORT_CH) && (I2C_MASTER_SUPPORT_CH < 3)
    #error "I2C_MASTER_SUPPORT_CH setting in i2c_master_config.h is not correct!!"
  #endif

#endif

#endif
