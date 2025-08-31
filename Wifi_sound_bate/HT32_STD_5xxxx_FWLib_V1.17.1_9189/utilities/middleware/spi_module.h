/*********************************************************************************************************//**
 * @file    spi_module.h
 * @version $Rev:: 1288         $
 * @date    $Date:: 2024-07-10 #$
 * @brief   The header file of spi api (interrupt mode with buffer).
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
#ifndef __SPI_MODULE_H
#define __SPI_MODULE_H

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SPI SPI
  * @{
  */

/** @addtogroup SPI_API SPI API
  * @{
  */

/* Includes ------------------------------------------------------------------------------------------------*/
/* If spi_module_config.h is missing, 
   1. please copy utilities/middleware/spi_module_config_templet.h to the folder of main program
   2. and change the file name to spi_module_config.h. */
#include "spi_module_config.h"
#include "ht32_board_config.h"

/* Exported types ------------------------------------------------------------------------------------------*/
/**
 * @brief SPI IAP TX/RX buffer
 */
typedef struct
{
  u32 uTxRxLength;
  u8 *puTxBuffer;
  u8 *puRxBuffer;
  bool uIsTxBufferFix;
  bool uIsRxBufferFix;
} SPIAPI_BufferTypeDef;

/**
 * @brief SPI API status
 */
typedef enum
{
  SPI_API_FINISH                       = 0,
  SPI_API_BUSBUSY                      = 1,
  SPI_API_SLAVE_ABORT                  = 2,
  SPI_API_SLAVE_RX_UNEXPECTED_DATA     = 4,
} SPIAPI_Status_Enum;

/* Exported constants --------------------------------------------------------------------------------------*/
#define   SPI_API_CH0    0
#define   SPI_API_CH1    1
#define   SPI_API_CH2    2
#define   SPI_API_CH3    3

#ifdef HTCFG_SPI_CH0
#define SPI_API_CH0_IRQ                   STRCAT2(HTCFG_SPI_CH0, _IRQn)
#define SPI_API_CH0_IRQHandler            STRCAT2(HTCFG_SPI_CH0, _IRQHandler)
#endif
#ifdef HTCFG_SPI_CH1
#define SPI_API_CH1_IRQ                   STRCAT2(HTCFG_SPI_CH1, _IRQn)
#define SPI_API_CH1_IRQHandler            STRCAT2(HTCFG_SPI_CH1, _IRQHandler)
#endif
#ifdef HTCFG_SPI_CH2
#define SPI_API_CH2_IRQ                   STRCAT2(HTCFG_SPI_CH2, _IRQn)
#define SPI_API_CH2_IRQHandler            STRCAT2(HTCFG_SPI_CH2, _IRQHandler)
#endif
#ifdef HTCFG_SPI_CH3
#define SPI_API_CH3_IRQ                   STRCAT2(HTCFG_SPI_CH3, _IRQn)
#define SPI_API_CH3_IRQHandler            STRCAT2(HTCFG_SPI_CH3, _IRQHandler)
#endif

#if SPICFG_PDMA_MODE
  #if SPICFG_CH0_PDMA_ENABLE
    #if SPICFG_CH0_PDMA
    #define SPI_API_CH0_RX_PDMA_CHANNEL                PDMA_SPI1_RX
    #define SPI_API_CH0_TX_PDMA_CHANNEL                PDMA_SPI1_TX
    #define SPI_API_CH0_RX_PDMA                        ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_RX * 6 * 4))
    #define SPI_API_CH0_TX_PDMA                        ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_TX * 6 * 4))
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH0_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT0                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT0                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT0                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT0                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT0                     PDMACH4_IRQn
      #define SPI_API_TX_PDMA_INT0                     PDMACH5_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH0_RX_PDMA
      #undef SPI_API_CH0_TX_PDMA
      #define SPI_API_CH0_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH4 * 6 * 4))
      #define SPI_API_CH0_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH5 * 6 * 4))
      #define SPI_API_RX_PDMA_INT0                     PDMA0_CH4_IRQn
      #define SPI_API_TX_PDMA_INT0                     PDMA0_CH5_IRQn
      #define PDMA_CH4_IRQHandler                      PDMA0_CH4_IRQHandler
      #define PDMA_CH5_IRQHandler                      PDMA0_CH5_IRQHandler
      #endif
    #else
      #define SPI_API_CH0_RX_PDMA_CHANNEL              PDMA_SPI0_RX
      #define SPI_API_CH0_TX_PDMA_CHANNEL              PDMA_SPI0_TX
      #define SPI_API_CH0_RX_PDMA                      (HT_PDMACH_TypeDef *)(HT_PDMA_BASE + PDMA_SPI0_RX * 6 * 4)
      #define SPI_API_CH0_TX_PDMA                      (HT_PDMACH_TypeDef *)(HT_PDMA_BASE + PDMA_SPI0_TX * 6 * 4)
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH0_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT0                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT0                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT0                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT0                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT0                     PDMACH0_IRQn
      #define SPI_API_TX_PDMA_INT0                     PDMACH1_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH0_RX_PDMA
      #undef SPI_API_CH0_TX_PDMA
      #define SPI_API_CH0_RX_PDMA                      (HT_PDMACH_TypeDef *)(HT_PDMA0_BASE + PDMA_CH2 * 6 * 4)
      #define SPI_API_CH0_TX_PDMA                      (HT_PDMACH_TypeDef *)(HT_PDMA0_BASE + PDMA_CH3 * 6 * 4)
      #define SPI_API_RX_PDMA_INT0                     PDMA0_CH2_IRQn
      #define SPI_API_TX_PDMA_INT0                     PDMA0_CH3_IRQn
      #define PDMA_CH2_IRQHandler                      PDMA0_CH2_IRQHandler
      #define PDMA_CH3_IRQHandler                      PDMA0_CH3_IRQHandler
      #endif
    #endif
  #endif
  #if SPICFG_CH1_PDMA_ENABLE
    #if SPICFG_CH1_PDMA
    #define SPI_API_CH1_RX_PDMA_CHANNEL                PDMA_SPI1_RX
    #define SPI_API_CH1_TX_PDMA_CHANNEL                PDMA_SPI1_TX
    #define SPI_API_CH1_RX_PDMA                        ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_RX * 6 * 4))
    #define SPI_API_CH1_TX_PDMA                        ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_TX * 6 * 4))
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH1_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT1                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT1                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT1                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT1                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT1                     PDMACH4_IRQn
      #define SPI_API_TX_PDMA_INT1                     PDMACH5_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH1_RX_PDMA
      #undef SPI_API_CH1_TX_PDMA
      #define SPI_API_CH1_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH4 * 6 * 4))
      #define SPI_API_CH1_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH5 * 6 * 4))
      #define SPI_API_RX_PDMA_INT1                     PDMA0_CH4_IRQn
      #define SPI_API_TX_PDMA_INT1                     PDMA0_CH5_IRQn
      #define PDMA_CH4_IRQHandler                      PDMA0_CH4_IRQHandler
      #define PDMA_CH5_IRQHandler                      PDMA0_CH5_IRQHandler
      #endif
    #else
      #define SPI_API_CH1_RX_PDMA_CHANNEL              PDMA_SPI0_RX
      #define SPI_API_CH1_TX_PDMA_CHANNEL              PDMA_SPI0_TX
      #define SPI_API_CH1_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI0_RX * 6 * 4))
      #define SPI_API_CH1_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI0_TX * 6 * 4))
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH1_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT1                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT1                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT1                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT1                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT1                     PDMACH0_IRQn
      #define SPI_API_TX_PDMA_INT1                     PDMACH1_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH1_RX_PDMA
      #undef SPI_API_CH1_TX_PDMA
      #define SPI_API_CH1_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH2 * 6 * 4))
      #define SPI_API_CH1_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH3 * 6 * 4))
      #define SPI_API_RX_PDMA_INT1                     PDMA0_CH2_IRQn
      #define SPI_API_TX_PDMA_INT1                     PDMA0_CH3_IRQn
      #define PDMA_CH2_IRQHandler                      PDMA0_CH2_IRQHandler
      #define PDMA_CH3_IRQHandler                      PDMA0_CH3_IRQHandler
      #endif
    #endif
  #endif
  #if SPICFG_CH2_PDMA_ENABLE
    #if SPICFG_CH2_PDMA
    #define SPI_API_CH2_RX_PDMA_CHANNEL                PDMA_SPI1_RX
    #define SPI_API_CH2_TX_PDMA_CHANNEL                PDMA_SPI1_TX
    #define SPI_API_CH2_RX_PDMA                        ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_RX * 6 * 4))
    #define SPI_API_CH2_TX_PDMA                        ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_TX * 6 * 4))
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH2_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT2                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT2                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT2                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT2                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT2                     PDMACH4_IRQn
      #define SPI_API_TX_PDMA_INT2                     PDMACH5_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH2_RX_PDMA
      #undef SPI_API_CH2_TX_PDMA
      #define SPI_API_CH2_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH4 * 6 * 4))
      #define SPI_API_CH2_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH5 * 6 * 4))
      #define SPI_API_RX_PDMA_INT2                     PDMA0_CH4_IRQn
      #define SPI_API_TX_PDMA_INT2                     PDMA0_CH5_IRQn
      #define PDMA_CH4_IRQHandler                      PDMA0_CH4_IRQHandler
      #define PDMA_CH5_IRQHandler                      PDMA0_CH5_IRQHandler
      #endif
    #else
      #define SPI_API_CH2_RX_PDMA_CHANNEL              PDMA_SPI0_RX
      #define SPI_API_CH2_TX_PDMA_CHANNEL              PDMA_SPI0_TX
      #define SPI_API_CH2_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI0_RX * 6 * 4))
      #define SPI_API_CH2_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI0_TX * 6 * 4))
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH2_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT2                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT2                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT2                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT2                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT2                     PDMACH0_IRQn
      #define SPI_API_TX_PDMA_INT2                     PDMACH1_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH2_RX_PDMA
      #undef SPI_API_CH2_TX_PDMA
      #define SPI_API_CH2_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH2 * 6 * 4))
      #define SPI_API_CH2_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH3 * 6 * 4))
      #define SPI_API_RX_PDMA_INT2                     PDMA0_CH2_IRQn
      #define SPI_API_TX_PDMA_INT2                     PDMA0_CH3_IRQn
      #define PDMA_CH2_IRQHandler                      PDMA0_CH2_IRQHandler
      #define PDMA_CH3_IRQHandler                      PDMA0_CH3_IRQHandler
      #endif
    #endif
  #endif
  #if SPICFG_CH3_PDMA_ENABLE
    #if SPICFG_CH3_PDMA
      #define SPI_API_CH3_RX_PDMA_CHANNEL              PDMA_SPI1_RX
      #define SPI_API_CH3_TX_PDMA_CHANNEL              PDMA_SPI1_TX
      #define SPI_API_CH3_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_RX * 6 * 4))
      #define SPI_API_CH3_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI1_TX * 6 * 4))
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH3_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT3                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT3                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT3                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT3                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT3                     PDMACH4_IRQn
      #define SPI_API_TX_PDMA_INT3                     PDMACH5_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH3_RX_PDMA
      #undef SPI_API_CH3_TX_PDMA
      #define SPI_API_CH3_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH4 * 6 * 4))
      #define SPI_API_CH3_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH5 * 6 * 4))
      #define SPI_API_RX_PDMA_INT3                     PDMA0_CH4_IRQn
      #define SPI_API_TX_PDMA_INT3                     PDMA0_CH5_IRQn
      #define PDMA_CH4_IRQHandler                      PDMA0_CH4_IRQHandler
      #define PDMA_CH5_IRQHandler                      PDMA0_CH5_IRQHandler
      #endif
    #else
      #define SPI_API_CH3_RX_PDMA_CHANNEL              PDMA_SPI0_RX
      #define SPI_API_CH3_TX_PDMA_CHANNEL              PDMA_SPI0_TX
      #define SPI_API_CH3_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI0_RX * 6 * 4))
      #define SPI_API_CH3_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA_BASE + PDMA_SPI0_TX * 6 * 4))
      #if (__CORTEX_M == 0)
        #if (SPI_API_CH3_RX_PDMA_CHANNEL < 2)
        #define SPI_API_RX_PDMA_INT3                   PDMACH0_1_IRQn
        #define SPI_API_TX_PDMA_INT3                   PDMACH0_1_IRQn
        #else
        #define SPI_API_RX_PDMA_INT3                   PDMACH2_5_IRQn
        #define SPI_API_TX_PDMA_INT3                   PDMACH2_5_IRQn
        #endif
      #endif
      #if (__CORTEX_M == 3)
      #define SPI_API_RX_PDMA_INT3                     PDMACH0_IRQn
      #define SPI_API_TX_PDMA_INT3                     PDMACH1_IRQn
      #endif
      #if (__CORTEX_M == 4)
      #undef SPI_API_CH3_RX_PDMA
      #undef SPI_API_CH3_TX_PDMA
      #define SPI_API_CH3_RX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH2 * 6 * 4))
      #define SPI_API_CH3_TX_PDMA                      ((HT_PDMACH_TypeDef*)(HT_PDMA0_BASE + PDMA_CH3 * 6 * 4))
      #define SPI_API_RX_PDMA_INT3                     PDMA0_CH2_IRQn
      #define SPI_API_TX_PDMA_INT3                     PDMA0_CH3_IRQn
      #define PDMA_CH2_IRQHandler                      PDMA0_CH2_IRQHandler
      #define PDMA_CH3_IRQHandler                      PDMA0_CH3_IRQHandler
      #endif
    #endif
  #endif
#endif

#if SPICFG_PDMA_MODE
  #if (__CORTEX_M == 4)
  #define SPI_MODULE_PDMA_CH0     HT_PDMA0, PDMA_CH0
  #define SPI_MODULE_PDMA_CH1     HT_PDMA0, PDMA_CH1
  #define SPI_MODULE_PDMA_CH2     HT_PDMA0, PDMA_CH2
  #define SPI_MODULE_PDMA_CH3     HT_PDMA0, PDMA_CH3
  #define SPI_MODULE_PDMA_CH4     HT_PDMA0, PDMA_CH4
  #define SPI_MODULE_PDMA_CH5     HT_PDMA0, PDMA_CH5
  #define SPI_MODULE_PDMA_RX_CH   HT_PDMA0, pSPIAPIState->uPDMARxCh
  #define SPI_MODULE_PDMA_TX_CH   HT_PDMA0, pSPIAPIState->uPDMATxCh
  #else
  #define SPI_MODULE_PDMA_CH0     PDMA_CH0
  #define SPI_MODULE_PDMA_CH1     PDMA_CH1
  #define SPI_MODULE_PDMA_CH2     PDMA_CH2
  #define SPI_MODULE_PDMA_CH3     PDMA_CH3
  #define SPI_MODULE_PDMA_CH4     PDMA_CH4
  #define SPI_MODULE_PDMA_CH5     PDMA_CH5
  #define SPI_MODULE_PDMA_RX_CH   pSPIAPIState->uPDMARxCh
  #define SPI_MODULE_PDMA_TX_CH   pSPIAPIState->uPDMATxCh
  #endif
#endif

/* Exported functions --------------------------------------------------------------------------------------*/
void SPIAPI_Init(u32 CH);
SPIAPI_Status_Enum SPIAPI_GetStatus(u32 CH);
bool SPIAPI_WriteRead(u32 CH, SPIAPI_BufferTypeDef *pSPIAPIBuffer);
u32 SPIAPI_GetReadBufferIndex(u32 CH);
u32 SPIAPI_GetWriteBufferIndex(u32 CH);
void SPIAPI_ClearStatus(u32 CH);

#if FREERTOS_SPI
#include "FreeRTOS.h"
#include "semphr.h"

void SPIAPI_Init_FreeRTOS(u32 CH);
u32 SPIAPI_WriteRead_FreeRTOS(u32 CH, SPIAPI_BufferTypeDef *pSPIAPIBuffer, u32 Timeout);
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif
