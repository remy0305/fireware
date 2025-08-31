/*********************************************************************************************************//**
 * @file    SCI/ATR/ht32_board_config.h
 * @version $Rev:: 7355         $
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
#if (LIBCFG_SCI0)
#else
  #error "This example code does not apply to the chip you selected."
#endif

#if defined(USE_HT32F52341_SK)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI0)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI0)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PC)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PC)
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_2)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_2)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_3)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_3)

  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_7)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_8)
#endif

#if defined(USE_HT32F52352_SK)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI1)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI1)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PD)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PD)
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_3)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_3)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_15)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_15)


  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_7)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_8)
#endif

#if defined(USE_HT32F57341_SK)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI0)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI0)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PC)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PC)
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_2)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_2)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_3)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_3)


  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_7)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_8)
#endif

#if defined(USE_HT32F57352_SK)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI1)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI1)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PC)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PC)
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_4)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_4)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_3)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_3)

  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_7)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_8)
#endif

#if defined(USE_HT32F52367_SK)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI1)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI1)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PA)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PA)
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_3)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_3)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PA)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PA)
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_2)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_2)

  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_7)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_8)
#endif

#if defined(USE_BM53A367A_DVB)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI1)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI1)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PD)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PD)               // A2/D16
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_4)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_4)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PC)               // A3/D17
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_2)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_2)

  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PA)               // D27
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_4)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PA)               // D26
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PA)               // D28
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_5)
#endif

#if defined(USE_BM18B367A_DVB)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI1)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI1)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PC)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PC)               // A4/D18
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_5)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_5)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PC)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PC)               // A5/D19
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_4)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_4)

  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PA)               // A3/D17
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_4)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PA)               // A7/D32
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PA)               // A6/D31
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_5)
#endif

#if defined(USE_HT32F61141_SK)
  #define HTCFG_SMARTCARD_SCI                 (HT_SCI1)
  #define HTCFG_SMARTCARD_CLK(CK)             (CK.Bit.SCI1)
  #define HTCFG_SMARTCARD_IRQn                (SCI_IRQn)

  #define HTCFG_SMARTCARD_CMD_CLK(CK)         (CK.Bit.PB)
  #define HTCFG_SMARTCARD_CMD_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_CMD_GPIO_PIN        (GPIO_PIN_5)
  #define HTCFG_SMARTCARD_CMD_AFIO_PIN        (AFIO_PIN_5)

  #define HTCFG_SMARTCARD_RSTN_CLK(CK)        (CK.Bit.PB)
  #define HTCFG_SMARTCARD_RSTN_GPIO_ID        (GPIO_PB)
  #define HTCFG_SMARTCARD_RSTN_GPIO_PIN       (GPIO_PIN_4)
  #define HTCFG_SMARTCARD_RSTN_AFIO_PIN       (AFIO_PIN_4)

  #define HTCFG_SMARTCARD_CLK_GPIO_ID         (GPIO_PC)
  #define HTCFG_SMARTCARD_CLK_AFIO_PIN        (AFIO_PIN_2)

  #define HTCFG_SMARTCARD_DET_GPIO_ID         (GPIO_PB)
  #define HTCFG_SMARTCARD_DET_AFIO_PIN        (AFIO_PIN_6)

  #define HTCFG_SMARTCARD_DIO_GPIO_ID         (GPIO_PC)
  #define HTCFG_SMARTCARD_DIO_AFIO_PIN        (AFIO_PIN_3)
#endif

#ifdef __cplusplus
}
#endif

#endif
