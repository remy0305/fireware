/*********************************************************************************************************//**
 * @file    spi_module.c
 * @version $Rev:: 1288         $
 * @date    $Date:: 2024-07-10 #$
 * @brief   The SPI Master (interrupt mode with buffer).
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board_config.h"
#include "spi_module.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SPI SPI
  * @{
  */

/** @addtogroup SPI_API SPI API
  * @{
  */
/**
 * @brief SPI API state variables
 */
/* Private constants ---------------------------------------------------------------------------------------*/
#ifdef HTCFG_SPI_CH0
#define _SCK0_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH0_SCK_GPIO_PORT)
#define _SCK0_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH0_SCK_GPIO_PIN)
#define _SEL0_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH0_SEL_GPIO_PORT)
#define _SEL0_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH0_SEL_GPIO_PIN)
#define _MOSI0_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH0_MOSI_GPIO_PORT)
#define _MOSI0_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH0_MOSI_GPIO_PIN)
#define _MISO0_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH0_MISO_GPIO_PORT)
#define _MISO0_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH0_MISO_GPIO_PIN)
#define _SPI_CH0                 STRCAT2(HT_,       HTCFG_SPI_CH0)              /* SPI channel                         */
#define _SPI_INT0                STRCAT2(HTCFG_SPI_CH0, _IRQn)                  /* SPI interrupt channel of NVIC       */
#define _SPI_MISO0               STRCAT2(P,         HTCFG_CH0_MISO_GPIO_PORT)   /* MISO clock enable bit               */
#define _GPIO_MISO0              STRCAT2(HT_GPIO,    HTCFG_CH0_MISO_GPIO_PORT)
#endif

#ifdef HTCFG_SPI_CH1
#define _SCK1_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH1_SCK_GPIO_PORT)
#define _SCK1_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH1_SCK_GPIO_PIN)
#define _SEL1_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH1_SEL_GPIO_PORT)
#define _SEL1_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH1_SEL_GPIO_PIN)
#define _MOSI1_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH1_MOSI_GPIO_PORT)
#define _MOSI1_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH1_MOSI_GPIO_PIN)
#define _MISO1_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH1_MISO_GPIO_PORT)
#define _MISO1_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH1_MISO_GPIO_PIN)
#define _SPI_CH1                 STRCAT2(HT_,       HTCFG_SPI_CH1)              /* SPI channel                         */
#define _SPI_INT1                STRCAT2(HTCFG_SPI_CH1, _IRQn)                  /* SPI interrupt channel of NVIC       */
#define _SPI_MISO1               STRCAT2(P,         HTCFG_CH1_MISO_GPIO_PORT)   /* MISO clock enable bit               */
#define _GPIO_MISO1              STRCAT2(HT_GPIO,    HTCFG_CH1_MISO_GPIO_PORT)
#endif

#ifdef HTCFG_SPI_CH2
#define _SCK2_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH2_SCK_GPIO_PORT)
#define _SCK2_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH2_SCK_GPIO_PIN)
#define _SEL2_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH2_SEL_GPIO_PORT)
#define _SEL2_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH2_SEL_GPIO_PIN)
#define _MOSI2_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH2_MOSI_GPIO_PORT)
#define _MOSI2_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH2_MOSI_GPIO_PIN)
#define _MISO2_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH2_MISO_GPIO_PORT)
#define _MISO2_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH2_MISO_GPIO_PIN)
#define _SPI_CH2                 STRCAT2(HT_,       HTCFG_SPI_CH2)              /* SPI channel                         */
#define _SPI_INT2                STRCAT2(HTCFG_SPI_CH2, _IRQn)                  /* SPI interrupt channel of NVIC       */
#define _SPI_MISO2               STRCAT2(P,         HTCFG_CH2_MISO_GPIO_PORT)   /* MISO clock enable bit               */
#define _GPIO_MISO2              STRCAT2(HT_GPIO,    HTCFG_CH2_MISO_GPIO_PORT)
#endif

#ifdef HTCFG_SPI_CH3
#define _SCK3_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH3_SCK_GPIO_PORT)
#define _SCK3_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH3_SCK_GPIO_PIN)
#define _SEL3_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_CH3_SEL_GPIO_PORT)
#define _SEL3_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_CH3_SEL_GPIO_PIN)
#define _MOSI3_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH3_MOSI_GPIO_PORT)
#define _MOSI3_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH3_MOSI_GPIO_PIN)
#define _MISO3_GPIO_ID           STRCAT2(GPIO_P,    HTCFG_CH3_MISO_GPIO_PORT)
#define _MISO3_AFIO_PIN          STRCAT2(AFIO_PIN_, HTCFG_CH3_MISO_GPIO_PIN)
#define _SPI_CH3                 STRCAT2(HT_,       HTCFG_SPI_CH3)              /* SPI channel                         */
#define _SPI_INT3                STRCAT2(HTCFG_SPI_CH3, _IRQn)                  /* SPI interrupt channel of NVIC       */
#define _SPI_MISO3               STRCAT2(P,         HTCFG_CH3_MISO_GPIO_PORT)   /* MISO clock enable bit               */
#define _GPIO_MISO3              STRCAT2(HT_GPIO,    HTCFG_CH3_MISO_GPIO_PORT)
#endif

/* Private macro -------------------------------------------------------------------------------------------*/
#define __SPI_API_DBG_PRF(...)

#if (SPICFG_DEBUG_MODE)
  #undef __SPI_API_DBG_PRF
  #define __SPI_API_DBG_PRF printf
  #warning "================================ Debug Mode Warning ===================================="
  #warning " Debug mode has been enable which degrade the performance.                              "
  #warning " After all debug operation is finished, please remember to turn off debug mode.         "
  #warning "========================================================================================"
#endif

/* Private types -------------------------------------------------------------------------------------------*/
typedef struct
{
  HT_SPI_TypeDef *pSPIx;
  u8 *puTxBuffer;
  u8 *puRxBuffer;
  bool uIsTxBufferFix;
  bool uIsRxBufferFix;
  u32 uTxLength;
  u32 uRxLength;
  u32 uTxIndex;
  u32 uRxIndex;

  HT_GPIO_TypeDef *pGPIO_MISO;
  u32 uGPIO_MISOId;
  u32 uGPIO_MISOAfioPin;

  u32 uPDMARxCh;
  u32 uPDMATxCh;

  vu32 IsErrorSlaveAbort;
  vu32 IsErrorSlaveRxUnexpectedData;
  vu32 IsBusBusy;
} SPIAPI_StateTypeDef;

/* Private variables ---------------------------------------------------------------------------------------*/
SPIAPI_StateTypeDef gSPIAPIState[SPICFG_SUPPORT_CH];
#if SPICFG_PDMA_MODE
PDMACH_InitTypeDef PDMACH_RxStructure[SPICFG_SUPPORT_CH];
PDMACH_InitTypeDef PDMACH_TxStructure[SPICFG_SUPPORT_CH];
#endif

#if FREERTOS_SPI
SemaphoreHandle_t Semphr[SPICFG_SUPPORT_CH];
StaticSemaphore_t Semphr_Buffer[SPICFG_SUPPORT_CH];
SemaphoreHandle_t Mutex[SPICFG_SUPPORT_CH];
StaticSemaphore_t Mutex_Buffer[SPICFG_SUPPORT_CH];
u32 Transfer_Result[SPICFG_SUPPORT_CH];
void _SPIAPI_ISR_FreeRTOS(u32 CH);
#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
void _SPIAPI_InitAPIParameter(void);
void _SPIAPI_ResetPDMA(u32 CH);
u32  _SPIAPI_IsPDMARxEmpty(u32 CH);
void _SPIAPI_IRQHandler(u32 CH);
bool _SPIAPI_IsRxFinish(u32 CH);
bool _SPIAPI_IsTxFinish(u32 CH);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Initial SPI.
  * @param  CH: SPI Channel
  * @retval None
  ***********************************************************************************************************/
void SPIAPI_Init(u32 CH)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  SPI_InitTypeDef SPI_InitStructure;
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO       = 1;
  #if SPICFG_PDMA_MODE
  #if (__CORTEX_M == 4)
  CKCUClock.Bit.PDMA0      = 1;
  #else
  CKCUClock.Bit.PDMA       = 1;
  #endif
  #endif

  _SPIAPI_InitAPIParameter();

  SPI_InitStructure.SPI_FIFO = SPI_FIFO_ENABLE;
  SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
  SPI_InitStructure.SPI_SELMode = SPI_SEL_HARDWARE;
  SPI_InitStructure.SPI_RxFIFOTriggerLevel = 1;
  SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;

  #ifdef HTCFG_SPI_CH0
  if (CH == SPI_API_CH0)
  {
    /* Enable SPI & AFIO APB clock                                                                          */
    CKCUClock.Bit.HTCFG_SPI_CH0 = 1;
    CKCUClock.Bit._SPI_MISO0 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Configure AFIO as SPI mode                                                                           */
    #if SPICFG_MISOD_IDLE_VALUE
      GPIO_SetOutBits(_GPIO_MISO0, _MISO0_AFIO_PIN);
    #else
      GPIO_ClearOutBits(_GPIO_MISO0, _MISO0_AFIO_PIN);
    #endif
    GPIO_DirectionConfig(_GPIO_MISO0,_MISO0_AFIO_PIN,GPIO_DIR_OUT);
    AFIO_GPxConfig(_MISO0_GPIO_ID, _MISO0_AFIO_PIN, AFIO_FUN_GPIO);

    AFIO_GPxConfig(_SCK0_GPIO_ID,  _SCK0_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_SEL0_GPIO_ID,  _SEL0_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_MOSI0_GPIO_ID, _MOSI0_AFIO_PIN, AFIO_FUN_SPI);

    /* SPI configuration                                                                                      */
    SPI_InitStructure.SPI_Mode = SPICFG_CH0_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH0_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH0_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH0_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH0_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH0_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH0, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH0, ENABLE);
    /* Enable SPI                                                                                             */
    SPI_Cmd(_SPI_CH0, ENABLE);

    #if SPICFG_CH0_PDMA_ENABLE
      /* SPI Master Tx PDMA channel configuration                                                              */
      PDMACH_TxStructure[SPI_API_CH0].PDMACH_SrcAddr = NULL;
      PDMACH_TxStructure[SPI_API_CH0].PDMACH_DstAddr = (u32) &gSPIAPIState[SPI_API_CH0].pSPIx->DR;
      PDMACH_TxStructure[SPI_API_CH0].PDMACH_BlkCnt = 0;
      PDMACH_TxStructure[SPI_API_CH0].PDMACH_BlkLen = 1;
      PDMACH_TxStructure[SPI_API_CH0].PDMACH_DataSize = WIDTH_8BIT;
      PDMACH_TxStructure[SPI_API_CH0].PDMACH_Priority = M_PRIO;
      PDMACH_TxStructure[SPI_API_CH0].PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
      PDMA_Config(SPI_API_CH0_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH0]);

      /* SPI Master Rx PDMA channel configuration                                                              */
      PDMACH_RxStructure[SPI_API_CH0].PDMACH_SrcAddr = (u32) &gSPIAPIState[SPI_API_CH0].pSPIx->DR;
      PDMACH_RxStructure[SPI_API_CH0].PDMACH_DstAddr = NULL;
      PDMACH_RxStructure[SPI_API_CH0].PDMACH_BlkCnt = 0;
      PDMACH_RxStructure[SPI_API_CH0].PDMACH_BlkLen = 1;
      PDMACH_RxStructure[SPI_API_CH0].PDMACH_Priority = VH_PRIO;
      PDMACH_RxStructure[SPI_API_CH0].PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
      PDMA_Config(SPI_API_CH0_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH0]);
      /* Enable SPI Tx, Rx GE & TC interrupt                                                                   */
      PDMA_IntConfig(SPI_API_CH0_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TE| PDMA_INT_TC, ENABLE);
      PDMA_IntConfig(SPI_API_CH0_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TE| PDMA_INT_TC, ENABLE);
      NVIC_EnableIRQ(SPI_API_RX_PDMA_INT0);
      NVIC_EnableIRQ(SPI_API_TX_PDMA_INT0);
      SPI_IntConfig(_SPI_CH0,SPI_INT_WC|SPI_INT_RO|SPI_INT_SA, ENABLE);
      NVIC_EnableIRQ(_SPI_INT0);
    #else
      /* Enable SPI interrupts                                                                                  */
      SPI_IntConfig(_SPI_CH0,SPI_INT_RXBNE|SPI_INT_WC|SPI_INT_RO|SPI_INT_SA, ENABLE);
      NVIC_EnableIRQ(_SPI_INT0);
    #endif
  }
  #endif

  #ifdef HTCFG_SPI_CH1
  if (CH == SPI_API_CH1)
  {
    CKCUClock.Bit.HTCFG_SPI_CH1 = 1;
    CKCUClock.Bit._SPI_MISO1 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    #if SPICFG_MISOD_IDLE_VALUE
      GPIO_SetOutBits(_GPIO_MISO1, _MISO1_AFIO_PIN);
    #else
      GPIO_ClearOutBits(_GPIO_MISO1, _MISO1_AFIO_PIN);
    #endif
    GPIO_DirectionConfig(_GPIO_MISO1,_MISO1_AFIO_PIN,GPIO_DIR_OUT);
    AFIO_GPxConfig(_MISO1_GPIO_ID, _MISO1_AFIO_PIN, AFIO_FUN_GPIO);

    AFIO_GPxConfig(_SCK1_GPIO_ID,  _SCK1_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_SEL1_GPIO_ID,  _SEL1_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_MOSI1_GPIO_ID, _MOSI1_AFIO_PIN, AFIO_FUN_SPI);

    SPI_InitStructure.SPI_Mode = SPICFG_CH1_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH1_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH1_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH1_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH1_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH1_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH1, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH1, ENABLE);
    SPI_Cmd(_SPI_CH1, ENABLE);

    #if SPICFG_CH1_PDMA_ENABLE
      /* SPI Master Tx PDMA channel configuration                                                              */
      PDMACH_TxStructure[SPI_API_CH1].PDMACH_SrcAddr = NULL;
      PDMACH_TxStructure[SPI_API_CH1].PDMACH_DstAddr = (u32) &gSPIAPIState[SPI_API_CH1].pSPIx->DR;
      PDMACH_TxStructure[SPI_API_CH1].PDMACH_BlkCnt = 0;
      PDMACH_TxStructure[SPI_API_CH1].PDMACH_BlkLen = 1;
      PDMACH_TxStructure[SPI_API_CH1].PDMACH_DataSize = WIDTH_8BIT;
      PDMACH_TxStructure[SPI_API_CH1].PDMACH_Priority = M_PRIO;
      PDMACH_TxStructure[SPI_API_CH1].PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
      PDMA_Config(SPI_API_CH1_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH1]);

      /* SPI Master Rx PDMA channel configuration                                                              */
      PDMACH_RxStructure[SPI_API_CH1].PDMACH_SrcAddr = (u32) &gSPIAPIState[SPI_API_CH1].pSPIx->DR;
      PDMACH_RxStructure[SPI_API_CH1].PDMACH_DstAddr = NULL;
      PDMACH_RxStructure[SPI_API_CH1].PDMACH_BlkCnt = 0;
      PDMACH_RxStructure[SPI_API_CH1].PDMACH_BlkLen = 1;
      PDMACH_RxStructure[SPI_API_CH1].PDMACH_Priority = VH_PRIO;
      PDMACH_RxStructure[SPI_API_CH1].PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
      PDMA_Config(SPI_API_CH1_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH1]);
      /* Enable SPI Tx, Rx GE & TC interrupt                                                                   */
      PDMA_IntConfig(SPI_API_CH1_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
      PDMA_IntConfig(SPI_API_CH1_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
      NVIC_EnableIRQ(SPI_API_RX_PDMA_INT1);
      NVIC_EnableIRQ(SPI_API_TX_PDMA_INT1);
    #else
      /* Enable SPI interrupts                                                                                  */
      SPI_IntConfig(_SPI_CH1,SPI_INT_RXBNE|SPI_INT_WC|SPI_INT_RO|SPI_INT_MF|SPI_INT_SA, ENABLE);
      NVIC_EnableIRQ(_SPI_INT1);
    #endif
  }
  #endif

  #ifdef HTCFG_SPI_CH2
  if (CH == SPI_API_CH2)
  {
    CKCUClock.Bit.HTCFG_SPI_CH2 = 1;
    CKCUClock.Bit._SPI_MISO2 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    #if SPICFG_MISOD_IDLE_VALUE
      GPIO_SetOutBits(_GPIO_MISO2, _MISO2_AFIO_PIN);
    #else
      GPIO_ClearOutBits(_GPIO_MISO2, _MISO2_AFIO_PIN);
    #endif
    GPIO_DirectionConfig(_GPIO_MISO2,_MISO2_AFIO_PIN,GPIO_DIR_OUT);
    AFIO_GPxConfig(_MISO2_GPIO_ID, _MISO2_AFIO_PIN, AFIO_FUN_GPIO);

    AFIO_GPxConfig(_SCK2_GPIO_ID,  _SCK2_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_SEL2_GPIO_ID,  _SEL2_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_MOSI2_GPIO_ID, _MOSI2_AFIO_PIN, AFIO_FUN_SPI);

    SPI_InitStructure.SPI_Mode = SPICFG_CH2_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH2_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH2_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH2_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH2_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH1_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH2, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH2, ENABLE);
    SPI_Cmd(_SPI_CH2, ENABLE);

    #if SPICFG_CH2_PDMA_ENABLE
      /* SPI Master Tx PDMA channel configuration                                                              */
      PDMACH_TxStructure[SPI_API_CH2].PDMACH_SrcAddr = NULL;
      PDMACH_TxStructure[SPI_API_CH2].PDMACH_DstAddr = (u32) &gSPIAPIState[SPI_API_CH2].pSPIx->DR;
      PDMACH_TxStructure[SPI_API_CH2].PDMACH_BlkCnt = 0;
      PDMACH_TxStructure[SPI_API_CH2].PDMACH_BlkLen = 1;
      PDMACH_TxStructure[SPI_API_CH2].PDMACH_DataSize = WIDTH_8BIT;
      PDMACH_TxStructure[SPI_API_CH2].PDMACH_Priority = M_PRIO;
      PDMACH_TxStructure[SPI_API_CH2].PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
      PDMA_Config(SPI_API_CH2_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH2]);

      /* SPI Master Rx PDMA channel configuration                                                              */
      PDMACH_RxStructure[SPI_API_CH2].PDMACH_SrcAddr = (u32) &gSPIAPIState[SPI_API_CH2].pSPIx->DR;
      PDMACH_RxStructure[SPI_API_CH2].PDMACH_DstAddr = NULL;
      PDMACH_RxStructure[SPI_API_CH2].PDMACH_BlkCnt = 0;
      PDMACH_RxStructure[SPI_API_CH2].PDMACH_BlkLen = 1;
      PDMACH_RxStructure[SPI_API_CH2].PDMACH_Priority = VH_PRIO;
      PDMACH_RxStructure[SPI_API_CH2].PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
      PDMA_Config(SPI_API_CH2_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH2]);
      /* Enable SPI Tx, Rx GE & TC interrupt                                                                   */
      PDMA_IntConfig(SPI_API_CH2_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
      PDMA_IntConfig(SPI_API_CH2_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
      NVIC_EnableIRQ(SPI_API_RX_PDMA_INT2);
      NVIC_EnableIRQ(SPI_API_TX_PDMA_INT2);
    #else
      /* Enable SPI interrupts                                                                                  */
      SPI_IntConfig(_SPI_CH2,SPI_INT_RXBNE|SPI_INT_WC|SPI_INT_RO|SPI_INT_MF|SPI_INT_SA, ENABLE);
      NVIC_EnableIRQ(_SPI_INT2);
    #endif
  }
  #endif

  #ifdef HTCFG_SPI_CH3
  if (CH == SPI_API_CH3)
  {
    CKCUClock.Bit.HTCFG_SPI_CH3 = 1;
    CKCUClock.Bit._SPI_MISO3 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    #if SPICFG_MISOD_IDLE_VALUE
      GPIO_SetOutBits(_GPIO_MISO3, _MISO3_AFIO_PIN);
    #else
      GPIO_ClearOutBits(_GPIO_MISO3, _MISO3_AFIO_PIN);
    #endif
    GPIO_DirectionConfig(_GPIO_MISO3,_MISO3_AFIO_PIN,GPIO_DIR_OUT);
    AFIO_GPxConfig(_MISO3_GPIO_ID, _MISO3_AFIO_PIN, AFIO_FUN_GPIO);

    AFIO_GPxConfig(_SCK3_GPIO_ID,  _SCK3_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_SEL3_GPIO_ID,  _SEL3_AFIO_PIN,  AFIO_FUN_SPI);
    AFIO_GPxConfig(_MOSI3_GPIO_ID, _MOSI3_AFIO_PIN, AFIO_FUN_SPI);

    SPI_InitStructure.SPI_Mode = SPICFG_CH3_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH3_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH3_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH3_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH3_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH3_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH3, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH3, ENABLE);
    SPI_Cmd(_SPI_CH3, ENABLE);

    #if SPICFG_CH3_PDMA_ENABLE
      /* SPI Master Tx PDMA channel configuration                                                              */
      PDMACH_TxStructure[SPI_API_CH3].PDMACH_SrcAddr = NULL;
      PDMACH_TxStructure[SPI_API_CH3].PDMACH_DstAddr = (u32) &gSPIAPIState[SPI_API_CH3].pSPIx->DR;
      PDMACH_TxStructure[SPI_API_CH3].PDMACH_BlkCnt = 0;
      PDMACH_TxStructure[SPI_API_CH3].PDMACH_BlkLen = 1;
      PDMACH_TxStructure[SPI_API_CH3].PDMACH_DataSize = WIDTH_8BIT;
      PDMACH_TxStructure[SPI_API_CH3].PDMACH_Priority = M_PRIO;
      PDMACH_TxStructure[SPI_API_CH3].PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
      PDMA_Config(SPI_API_CH3_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH3]);

      /* SPI Master Rx PDMA channel configuration                                                              */
      PDMACH_RxStructure[SPI_API_CH3].PDMACH_SrcAddr = (u32) &gSPIAPIState[SPI_API_CH3].pSPIx->DR;
      PDMACH_RxStructure[SPI_API_CH3].PDMACH_DstAddr = NULL;
      PDMACH_RxStructure[SPI_API_CH3].PDMACH_BlkCnt = 0;
      PDMACH_RxStructure[SPI_API_CH3].PDMACH_BlkLen = 1;
      PDMACH_RxStructure[SPI_API_CH3].PDMACH_Priority = VH_PRIO;
      PDMACH_RxStructure[SPI_API_CH3].PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
      PDMA_Config(SPI_API_CH3_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH3]);
      /* Enable SPI Tx, Rx GE & TC interrupt                                                                   */
      PDMA_IntConfig(SPI_API_CH3_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
      PDMA_IntConfig(SPI_API_CH3_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
      NVIC_EnableIRQ(SPI_API_RX_PDMA_INT3);
      NVIC_EnableIRQ(SPI_API_TX_PDMA_INT3);
    #else
      /* Enable SPI interrupts                                                                                  */
      SPI_IntConfig(_SPI_CH3,SPI_INT_RXBNE|SPI_INT_WC|SPI_INT_RO|SPI_INT_MF|SPI_INT_SA, ENABLE);
      NVIC_EnableIRQ(_SPI_INT3);
    #endif
  }
  #endif
}

#if SPICFG_PDMA_MODE
/*********************************************************************************************************//**
  * @brief  Reset PDMA.
  * @retval None
  ***********************************************************************************************************/
void _SPIAPI_ResetPDMA(u32 CH)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  SPI_InitTypeDef SPI_InitStructure;

  /* Reset PDMA, SPI */
  RSTCU_PeripReset_TypeDef Reset = {0x00};
  #if (__CORTEX_M == 4)
  Reset.Bit.PDMA0  = 1;
  #else
  Reset.Bit.PDMA   = 1;
  #endif
  if(CH == SPI_API_CH0)
  {
    #ifdef HTCFG_SPI_CH0
    Reset.Bit.HTCFG_SPI_CH0 = 1;
    #endif
  }

  if (CH == SPI_API_CH1)
  {
    #ifdef HTCFG_SPI_CH1
    Reset.Bit.HTCFG_SPI_CH1 = 1;
    #endif
  }

  if (CH == SPI_API_CH2)
  {
    #ifdef HTCFG_SPI_CH2
    Reset.Bit.HTCFG_SPI_CH2 = 1;
    #endif
  }

  if (CH == SPI_API_CH3)
  {
    #ifdef HTCFG_SPI_CH3
    Reset.Bit.HTCFG_SPI_CH3 = 1;
    #endif
  }
  RSTCU_PeripReset(Reset, ENABLE);

  /* Re-Inital SPI,PDMA */
  SPI_InitStructure.SPI_FIFO = SPI_FIFO_ENABLE;
  SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
  SPI_InitStructure.SPI_SELMode = SPI_SEL_HARDWARE;
  SPI_InitStructure.SPI_RxFIFOTriggerLevel = 1;
  SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;

  #ifdef HTCFG_SPI_CH0
  if(CH == SPI_API_CH0)
  {
    SPI_InitStructure.SPI_Mode = SPICFG_CH0_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH0_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH0_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH0_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH0_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH0_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH0, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH0, ENABLE);
    SPI_Cmd(_SPI_CH0, ENABLE);
  }
  #if SPICFG_CH0_PDMA_ENABLE
  PDMA_Config(SPI_API_CH0_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH0]);
  PDMA_Config(SPI_API_CH0_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH0]);
  PDMA_IntConfig(SPI_API_CH0_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  PDMA_IntConfig(SPI_API_CH0_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  NVIC_EnableIRQ(SPI_API_RX_PDMA_INT0);
  NVIC_EnableIRQ(SPI_API_TX_PDMA_INT0);
  SPI_IntConfig(_SPI_CH0,SPI_INT_WC|SPI_INT_RO|SPI_INT_MF|SPI_INT_SA, ENABLE);
  NVIC_EnableIRQ(_SPI_INT0);
  #endif
  #endif

  #ifdef HTCFG_SPI_CH1
  if(CH == SPI_API_CH1)
  {
    SPI_InitStructure.SPI_Mode = SPICFG_CH1_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH1_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH1_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH1_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH1_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH1_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH1, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH1, ENABLE);
    SPI_Cmd(_SPI_CH1, ENABLE);
  }
  #if SPICFG_CH1_PDMA_ENABLE
  PDMA_Config(SPI_API_CH1_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH1]);
  PDMA_Config(SPI_API_CH1_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH1]);
  PDMA_IntConfig(SPI_API_CH1_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  PDMA_IntConfig(SPI_API_CH1_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  NVIC_EnableIRQ(SPI_API_RX_PDMA_INT1);
  NVIC_EnableIRQ(SPI_API_TX_PDMA_INT1);
  SPI_IntConfig(_SPI_CH1,SPI_INT_WC|SPI_INT_RO|SPI_INT_MF|SPI_INT_SA, ENABLE);
  NVIC_EnableIRQ(_SPI_INT1);
  #endif
  #endif

  #ifdef HTCFG_SPI_CH2
  if(CH == SPI_API_CH2)
  {
    SPI_InitStructure.SPI_Mode = SPICFG_CH2_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH2_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH2_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH2_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH2_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH2_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH2, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH2, ENABLE);
    SPI_Cmd(_SPI_CH2, ENABLE);
  }
  #if SPICFG_CH2_PDMA_ENABLE
  PDMA_Config(SPI_API_CH2_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH2]);
  PDMA_Config(SPI_API_CH2_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH2]);
  PDMA_IntConfig(SPI_API_CH2_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  PDMA_IntConfig(SPI_API_CH2_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  NVIC_EnableIRQ(SPI_API_RX_PDMA_INT2);
  NVIC_EnableIRQ(SPI_API_TX_PDMA_INT2);
  SPI_IntConfig(_SPI_CH2,SPI_INT_WC|SPI_INT_RO|SPI_INT_MF|SPI_INT_SA, ENABLE);
  NVIC_EnableIRQ(_SPI_INT2);
  #endif
  #endif

  #ifdef HTCFG_SPI_CH3
  if(CH == SPI_API_CH3)
  {
    SPI_InitStructure.SPI_Mode = SPICFG_CH3_MODE<<14;
    SPI_InitStructure.SPI_SELPolarity = SPICFG_CH3_SEL_POLARITY<<11;
    SPI_InitStructure.SPI_FirstBit = SPICFG_CH3_FIRST_BIT<<12;
    SPI_InitStructure.SPI_CPOL = SPICFG_CH3_CPOL<<10;
    SPI_InitStructure.SPI_CPHA = SPICFG_CH3_CPHA;
    SPI_InitStructure.SPI_ClockPrescaler = SPICFG_CH3_CLOCK_PRESCALER;
    SPI_Init(_SPI_CH3, &SPI_InitStructure);
    SPI_SELOutputCmd(_SPI_CH3, ENABLE);
    SPI_Cmd(_SPI_CH3, ENABLE);
  }
  #if SPICFG_CH3_PDMA_ENABLE
  PDMA_Config(SPI_API_CH3_TX_PDMA_CHANNEL, &PDMACH_TxStructure[SPI_API_CH3]);
  PDMA_Config(SPI_API_CH3_RX_PDMA_CHANNEL, &PDMACH_RxStructure[SPI_API_CH3]);
  PDMA_IntConfig(SPI_API_CH3_RX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  PDMA_IntConfig(SPI_API_CH3_TX_PDMA_CHANNEL, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
  NVIC_EnableIRQ(SPI_API_RX_PDMA_INT3);
  NVIC_EnableIRQ(SPI_API_TX_PDMA_INT3);
  SPI_IntConfig(_SPI_CH3,SPI_INT_WC|SPI_INT_RO|SPI_INT_MF|SPI_INT_SA, ENABLE);
  NVIC_EnableIRQ(_SPI_INT3);
  #endif
  #endif
}
#endif

/*********************************************************************************************************//**
  * @brief  SPI Write\Read.
  * @param  CH: SPI Channel
  * @param  pSPIAPI:
  * @retval None
  ***********************************************************************************************************/
bool SPIAPI_WriteRead(u32 CH, SPIAPI_BufferTypeDef *pSPIAPIBuffer)
{
  SPIAPI_StateTypeDef *pSPIAPIState   = &gSPIAPIState[CH];
  if((pSPIAPIState->IsErrorSlaveAbort == TRUE) || (pSPIAPIState->IsErrorSlaveRxUnexpectedData == TRUE))
  {
    return FALSE;
  }
  #if SPICFG_PDMA_MODE
  {
    PDMACH_InitTypeDef *pDMATxState   = &PDMACH_TxStructure[CH];
    PDMACH_InitTypeDef *pDMARxState   = &PDMACH_RxStructure[CH];

    AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_SPI);

    PDMA_EnaCmd(SPI_MODULE_PDMA_RX_CH, DISABLE);
    PDMA_EnaCmd(SPI_MODULE_PDMA_TX_CH, DISABLE);
    SPI_PDMACmd(pSPIAPIState->pSPIx, SPI_PDMAREQ_TX | SPI_PDMAREQ_RX, DISABLE);
    while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_RXBNE))
    {
      pSPIAPIState->IsErrorSlaveRxUnexpectedData =TRUE;
      return FALSE;
    }

    /* SPI Rx PDMA channel configuration                                                               */
    pDMARxState->PDMACH_DstAddr = (u32) pSPIAPIBuffer->puRxBuffer;
    pSPIAPIState->uRxLength = pSPIAPIBuffer->uTxRxLength;
    pDMARxState->PDMACH_BlkCnt = pSPIAPIBuffer->uTxRxLength;
    if (pSPIAPIBuffer->uIsRxBufferFix == TRUE)
    {
      pDMARxState->PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_FIX;
    }
    else
    {
      pDMARxState->PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
    }
    PDMA_Config(SPI_MODULE_PDMA_RX_CH, pDMARxState);
    /* Enable the corresponding PDMA channel                                                            */
    PDMA_EnaCmd(SPI_MODULE_PDMA_RX_CH, ENABLE);
    if(_SPIAPI_IsPDMARxEmpty(CH)==FALSE)
    {
      /* Rx buffer isn't empty.                                                                        */
      __SPI_API_DBG_PRF("Rx FIFO isn't empty.\r\n");
      #if 1
      /* An error occurred while transferring data.                                                    */
      while(1);
      #else
      /* Reset PDMA and SPI in slave mode.                                                             */
      _SPIAPI_ResetPDMA(CH);
      PDMA_Config(SPI_MODULE_PDMA_RX_CH, pDMARxState);
      PDMA_EnaCmd(SPI_MODULE_PDMA_RX_CH, ENABLE);
      #endif
    }

    /* SPI Tx PDMA channel configuration                                                               */
    pDMATxState->PDMACH_SrcAddr = (u32) pSPIAPIBuffer->puTxBuffer;
    pDMATxState->PDMACH_BlkCnt = pSPIAPIBuffer->uTxRxLength;
    pSPIAPIState->uTxLength = pSPIAPIBuffer->uTxRxLength;
    if (pSPIAPIBuffer->uIsTxBufferFix == TRUE)
    {
      pDMATxState->PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_FIX;
    }
    else
    {
      pDMATxState->PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
    }
    PDMA_Config(SPI_MODULE_PDMA_TX_CH, pDMATxState);

    /* Enable the corresponding PDMA channel                                                            */
    PDMA_EnaCmd(SPI_MODULE_PDMA_TX_CH, ENABLE);
    /* Enable master SPI0 PDMA requests later                                                           */
    SPI_PDMACmd(pSPIAPIState->pSPIx, SPI_PDMAREQ_TX | SPI_PDMAREQ_RX, ENABLE);
  }
  #else
    pSPIAPIState->puRxBuffer       = pSPIAPIBuffer->puRxBuffer;
    pSPIAPIState->puTxBuffer       = pSPIAPIBuffer->puTxBuffer;
    pSPIAPIState->uRxLength        = pSPIAPIBuffer->uTxRxLength;
    pSPIAPIState->uTxLength        = pSPIAPIBuffer->uTxRxLength;
    pSPIAPIState->uTxIndex              = 0;
    pSPIAPIState->uRxIndex              = 0;
    pSPIAPIState->IsErrorSlaveAbort     = FALSE;
    pSPIAPIState->IsErrorSlaveRxUnexpectedData    = FALSE;
    AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_SPI);
    SPI_IntConfig(pSPIAPIState->pSPIx, SPI_INT_TXBE, ENABLE);
  #endif
  return TRUE;
}

#if SPICFG_PDMA_MODE
/*********************************************************************************************************//**
  * @brief  Check if PDMA Rx is empty.
  * @param  CH: SPI Channel
  * @retval Result: TRUE or FALSE
  ***********************************************************************************************************/
u32 _SPIAPI_IsPDMARxEmpty(u32 CH)
{
  HT_PDMACH_TypeDef *PDMACH;
  switch(CH)
  {
    #ifdef HTCFG_SPI_CH0
    case SPI_API_CH0:
    {
      #if SPICFG_CH0_PDMA_ENABLE
      PDMACH = SPI_API_CH0_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH1
    case SPI_API_CH1:
    {
      #if SPICFG_CH1_PDMA_ENABLE
      PDMACH = SPI_API_CH1_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH2
    case SPI_API_CH2:
    {
      #if SPICFG_CH2_PDMA_ENABLE
      PDMACH = SPI_API_CH2_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH3
    case SPI_API_CH3:
    {
      #if SPICFG_CH3_PDMA_ENABLE
      PDMACH = SPI_API_CH3_RX_PDMA;
      #endif
      break;
    }
    #endif
  }
  if(PDMACH->TSR>>16!=PDMACH->CTSR>>16)
  {
    return FALSE;
  }
  else
  {
    return TRUE;
  }
}
#endif

/*********************************************************************************************************//**
  * @brief  Get write index.
  * @retval None
  ***********************************************************************************************************/
u32 SPIAPI_GetWriteBufferIndex(u32 CH)
{
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[CH];
  #if SPICFG_PDMA_MODE
  HT_PDMACH_TypeDef *PDMACH;
  switch(CH)
  {
    #ifdef HTCFG_SPI_CH0
    case SPI_API_CH0:
    {
      #if SPICFG_CH0_PDMA_ENABLE
      PDMACH = SPI_API_CH0_TX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH1
    case SPI_API_CH1:
    {
      #if SPICFG_CH1_PDMA_ENABLE
      PDMACH = SPI_API_CH1_TX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH2
    case SPI_API_CH2:
    {
      #if SPICFG_CH2_PDMA_ENABLE
      PDMACH = SPI_API_CH2_TX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH3
    case SPI_API_CH3:
    {
      #if SPICFG_CH3_PDMA_ENABLE
      PDMACH = SPI_API_CH3_TX_PDMA;
      #endif
      break;
    }
    #endif
  }
  return pSPIAPIState->uTxLength - (PDMACH->CTSR>>16);
  #else
  return pSPIAPIState->uTxIndex;
  #endif
}

/*********************************************************************************************************//**
  * @brief  Get read index.
  * @param  CH: SPI Channel
  * @retval None
  ***********************************************************************************************************/
u32 SPIAPI_GetReadBufferIndex(u32 CH)
{
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[CH];
  #if SPICFG_PDMA_MODE
  HT_PDMACH_TypeDef *PDMACH;
  switch(CH)
  {
    #ifdef HTCFG_SPI_CH0
    case SPI_API_CH0:
    {
      #if SPICFG_CH0_PDMA_ENABLE
      PDMACH = SPI_API_CH0_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH1
    case SPI_API_CH1:
    {
      #if SPICFG_CH1_PDMA_ENABLE
      PDMACH = SPI_API_CH1_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH2
    case SPI_API_CH2:
    {
      #if SPICFG_CH2_PDMA_ENABLE
      PDMACH = SPI_API_CH2_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH3
    case SPI_API_CH3:
    {
      #if SPICFG_CH3_PDMA_ENABLE
      PDMACH = SPI_API_CH3_RX_PDMA;
      #endif
      break;
    }
    #endif
  }
  return pSPIAPIState->uRxLength - (PDMACH->CTSR>>16);
  #else
  return pSPIAPIState->uRxIndex;
  #endif
}

/*********************************************************************************************************//**
  * @brief  Get SPI buffer statue.
  * @retval Result: SPI_API_FINISH or SPI_API_TIMEOUT
  ***********************************************************************************************************/
SPIAPI_Status_Enum SPIAPI_GetStatus(u32 CH)
{
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[CH];
  SPIAPI_Status_Enum Result =  SPI_API_BUSBUSY;

  if(_SPIAPI_IsRxFinish(CH) && _SPIAPI_IsTxFinish(CH))
  {
    Result = SPI_API_FINISH;
  }

  if(pSPIAPIState->IsErrorSlaveAbort == TRUE)
  {
    Result = SPI_API_SLAVE_ABORT;
    __SPI_API_DBG_PRF("SLAVE_ABORT\r\n");
  }

  if(pSPIAPIState->IsErrorSlaveRxUnexpectedData == TRUE)
  {
    Result = SPI_API_SLAVE_RX_UNEXPECTED_DATA;
    __SPI_API_DBG_PRF("SLAVE_RX_BUFFER_NOT_EMPTY\r\n");
  }
  return Result;
}

/*********************************************************************************************************//**
  * @brief  Clear SPI buffer statue.
  * @retval Result: None
  ***********************************************************************************************************/
void SPIAPI_ClearStatus(u32 CH)
{
  SPIAPI_StateTypeDef *pSPIAPIState   = &gSPIAPIState[CH];
  pSPIAPIState->IsErrorSlaveAbort     = FALSE;
  if(pSPIAPIState->IsErrorSlaveRxUnexpectedData == TRUE)
  {
    while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_RXBNE))
    {
      pSPIAPIState->pSPIx->DR;
    }
    pSPIAPIState->IsErrorSlaveRxUnexpectedData    = FALSE;
  }
}

#if defined(SPI0_IRQ_HANDLER) || defined(SPI1_IRQ_HANDLER) || defined(SPI2_IRQ_HANDLER) || defined(QSPI_IRQ_HANDLER)
#if defined(HT_SPI0) && defined(SPI0_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI0_IRQHandler(void)
{
  SPI0_IRQ_HANDLER();
}
#endif
#if defined(HT_SPI1) && defined(SPI1_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI1_IRQHandler(void)
{
  SPI1_IRQ_HANDLER();
}
#endif
#if defined(HT_SPI2) && defined(SPI2_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI2_IRQHandler(void)
{
  SPI2_IRQ_HANDLER();
}
#endif
#if defined(HT_QSPI) && defined(QSPI_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void QSPI_IRQHandler(void)
{
  QSPI_IRQ_HANDLER();
}
#endif
#else
#ifdef HTCFG_SPI_CH0
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI_API_CH0_IRQHandler(void)
{
  _SPIAPI_IRQHandler(SPI_API_CH0);
}
#endif

#ifdef HTCFG_SPI_CH1
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI_API_CH1_IRQHandler(void)
{
  _SPIAPI_IRQHandler(SPI_API_CH1);
}
#endif

#ifdef HTCFG_SPI_CH2
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI_API_CH2_IRQHandler(void)
{
  _SPIAPI_IRQHandler(SPI_API_CH2);
}
#endif

#ifdef HTCFG_SPI_CH3
/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void SPI_API_CH3_IRQHandler(void)
{
  _SPIAPI_IRQHandler(SPI_API_CH3);
}
#endif
#endif

/*********************************************************************************************************//**
 * @brief   This function handles SPI interrupt.
 * @retval  None
 ************************************************************************************************************/
void _SPIAPI_IRQHandler(u32 CH)
{
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[CH];
#if SPICFG_PDMA_MODE == 0
  /*----------------------------- SPI Transmitter ------------------------------------------------------*/
  if((SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_TXBE) == SET) && ((pSPIAPIState->pSPIx->IER&SPI_INT_TXBE)!=0))
  {
    if((pSPIAPIState->uTxLength <= 0)&&((pSPIAPIState->pSPIx->SR&0x03)==0x03))
    {
      SPI_IntConfig(pSPIAPIState->pSPIx, SPI_INT_TXBE, DISABLE);
      if((pSPIAPIState->pSPIx->CR1&SPI_MASTER) == 0)
      {
        /* Set MISO Idle value in slave mode */
        AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_GPIO);
        #if SPICFG_MISOD_IDLE_VALUE
        GPIO_SetOutBits(pSPIAPIState->pGPIO_MISO, pSPIAPIState->uGPIO_MISOAfioPin);
        #else
        GPIO_ClearOutBits(pSPIAPIState->pGPIO_MISO, pSPIAPIState->uGPIO_MISOAfioPin);
        #endif
        GPIO_DirectionConfig(pSPIAPIState->pGPIO_MISO,pSPIAPIState->uGPIO_MISOAfioPin,GPIO_DIR_OUT);
      }
    }
    else
    {
      int i;
      u32 uRemainTx=pSPIAPIState->uTxLength;
      if(uRemainTx>=8)
      {
        for(i=0;i<8;i++)
        {
          SPI_SendData(pSPIAPIState->pSPIx,pSPIAPIState->puTxBuffer[pSPIAPIState->uTxIndex++]);
        }
        pSPIAPIState->uTxLength-=8;
      }
      else
      {
        for(i=0;i<uRemainTx;i++)
        {
          SPI_SendData(pSPIAPIState->pSPIx, pSPIAPIState->puTxBuffer[pSPIAPIState->uTxIndex++]);
          pSPIAPIState->uTxLength--;
        }
      }
    }
  }

  /*-----------------------------SPI Receiver -----------------------------------------------------------*/
  if(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_RXBNE) == SET)
  {
    while(SPI_GetFIFOStatus(pSPIAPIState->pSPIx,SPI_FIFO_RX))
    {
      #if (SPICFG_DEBUG_MODE)
      if (Buffer_isFull(&gSPIRx[CH]))
      {
        /*------------------------------------------------------------------------------------------------*/
        /* Should not reach here! It means the buffer for SPI is full.                                    */
        /*------------------------------------------------------------------------------------------------*/
        __SPI_API_DBG_PRF("SPI Rx Buffer Full!\n\r");
        while (1);
      }
      #endif
      if(pSPIAPIState->uRxIndex < pSPIAPIState->uRxLength)
      {
        pSPIAPIState->puRxBuffer[pSPIAPIState->uRxIndex++]=SPI_ReceiveData(pSPIAPIState->pSPIx);
      }
      else
      {
        pSPIAPIState->IsErrorSlaveRxUnexpectedData = TRUE;
        SPI_ReceiveData(pSPIAPIState->pSPIx);
      }
    }
  }
#endif
  /*-----------------------------SPI Bus Error detection---------------------------------------------------*/
  if(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_RO) == SET)
  {
    SPI_ClearFlag(pSPIAPIState->pSPIx,SPI_FLAG_RO);
  }
  if(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_MF) == SET)
  {
    SPI_ClearFlag(pSPIAPIState->pSPIx,SPI_FLAG_MF);
  }
  if(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_SA) == SET)
  {
    pSPIAPIState->IsErrorSlaveAbort = TRUE;
    SPI_ClearFlag(pSPIAPIState->pSPIx,SPI_FLAG_SA);
  }

  #if FREERTOS_SPI
  _SPIAPI_ISR_FreeRTOS(CH);
  #endif
}

#if SPICFG_PDMA_MODE
/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH0 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH0_IRQHandler(void)
{
  #if SPICFG_CH0_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[0];
  #elif SPICFG_CH1_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[1];
  #elif SPICFG_CH2_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[2];
  #elif SPICFG_CH3_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[3];
  #else
  SPIAPI_StateTypeDef *pSPIAPIState ={0};
  #endif
  /*-----------------------------SPI Receiver -----------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH0,PDMA_FLAG_TC))
  {
    /* Channel 0 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH0, PDMA_FLAG_TC);
    /* Set MISO_IDLE_VALUE in slave mode */
    if((pSPIAPIState->pSPIx->CR1&SPI_MASTER) == 0)
    {
      /* Wait for Tx Complete, Clear this flags  */
      while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_TXE)!=SET);

      /* Set MISO Idle value in slave mode */
      AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_GPIO);
    }
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH0,PDMA_FLAG_TE))
  {
    /* Channel 0 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH0, PDMA_FLAG_TE);
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH1_IRQHandler(void)
{
  /*----------------------------- SPI Transmitter ------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH1,PDMA_FLAG_TC))
  {
    /* Channel 1 Transfer Complete, Clear this flags  */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH1, PDMA_FLAG_TC);
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH1,PDMA_FLAG_TE))
  {
    /* Channel 1 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH1, PDMA_FLAG_TE);
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH2 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH2_IRQHandler(void)
{
  #if SPICFG_CH0_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[0];
  #elif SPICFG_CH1_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[1];
  #elif SPICFG_CH2_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[2];
  #elif SPICFG_CH3_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[3];
  #else
  SPIAPI_StateTypeDef *pSPIAPIState ={0};
  #endif
  /*-----------------------------SPI Receiver -----------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH2,PDMA_FLAG_TC))
  {
    /* Channel 2 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH2, PDMA_FLAG_TC);
    /* Set MISO idle value in slave mode */
    if((pSPIAPIState->pSPIx->CR1&SPI_MASTER) == 0)
    {
      /* Wait for Tx Complete */
      while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_TXE)!=SET);

      /* Set MISO_IDLE_VALUE in slave mode */
      AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_GPIO);
    }
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH2,PDMA_FLAG_TE))
  {
    /* Channel 2 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH2, PDMA_FLAG_TE);
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH3 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH3_IRQHandler(void)
{
  /*----------------------------- SPI Transmitter ------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH3,PDMA_FLAG_TC))
  {
    /* Channel 3 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH3, PDMA_FLAG_TC);
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH3,PDMA_FLAG_TE))
  {
    /* Channel 3 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH3, PDMA_FLAG_TE);
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH4 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH4_IRQHandler(void)
{
  #if SPICFG_CH0_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[0];
  #elif SPICFG_CH1_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[1];
  #elif SPICFG_CH2_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[2];
  #elif SPICFG_CH3_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[3];
  #else
  SPIAPI_StateTypeDef *pSPIAPIState ={0};
  #endif
  /*-----------------------------SPI Receiver -----------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH4,PDMA_FLAG_TC))
  {
    /* Channel 4 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH4, PDMA_FLAG_TC);
    /* Set MISO idle value in slave mode */
    if((pSPIAPIState->pSPIx->CR1&SPI_MASTER) == 0)
    {
      /* Wait for Tx Complete */
      while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_TXE)!=SET);

      /* Set MISO_IDLE_VALUE in slave mode */
      AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_GPIO);
    }
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH4,PDMA_FLAG_TE))
  {
    /* Channel 4 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH4, PDMA_FLAG_TE);
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH5 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH5_IRQHandler(void)
{
  /*----------------------------- SPI Transmitter ------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH5,PDMA_FLAG_TC))
  {
    /* Channel 5 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH5, PDMA_FLAG_TC);
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH5,PDMA_FLAG_TE))
  {
    /* Channel 5 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH5, PDMA_FLAG_TE);
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH0~CH1 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH0_1_IRQHandler(void)
{
  #if SPICFG_CH0_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[0];
  #elif SPICFG_CH1_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[1];
  #elif SPICFG_CH2_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[2];
  #elif SPICFG_CH3_PDMA == 0
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[3];
  #else
  SPIAPI_StateTypeDef *pSPIAPIState ={0};
  #endif
  /*-----------------------------SPI Receiver -----------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH0,PDMA_FLAG_TC))
  {
    /* Channel 0 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH0, PDMA_FLAG_TC);
    /* Set MISO_IDLE_VALUE in slave mode */
    if((pSPIAPIState->pSPIx->CR1&SPI_MASTER) == 0)
    {
      /* Wait for Tx Complete, Clear this flags  */
      while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_TXE)!=SET);

      /* Set MISO Idle value in slave mode */
      AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_GPIO);
    }
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH0,PDMA_FLAG_TE))
  {
    /* Channel 0 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH0, PDMA_FLAG_TE);
  }

  /*----------------------------- SPI Transmitter ------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH1,PDMA_FLAG_TC))
  {
    /* Channel 1 Transfer Complete, Clear this flags  */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH1, PDMA_FLAG_TC);
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH1,PDMA_FLAG_TE))
  {
    /* Channel 1 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH1, PDMA_FLAG_TE);
  }
}

/*********************************************************************************************************//**
 * @brief   This function handles PDMA CH2~CH5 interrupt.
 * @retval  None
 ************************************************************************************************************/
void PDMA_CH2_5_IRQHandler(void)
{
  #if SPICFG_CH0_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[0];
  #elif SPICFG_CH1_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[1];
  #elif SPICFG_CH2_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[2];
  #elif SPICFG_CH3_PDMA == 1
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[3];
  #else
  SPIAPI_StateTypeDef *pSPIAPIState ={0};
  #endif
  /*-----------------------------SPI Receiver -----------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH2,PDMA_FLAG_TC))
  {
    /* Channel 4 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH2, PDMA_FLAG_TC);
    /* Set MISO idle value in slave mode */
    if((pSPIAPIState->pSPIx->CR1&SPI_MASTER) == 0)
    {
      /* Wait for Tx Complete */
      while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_TXE)!=SET);

      /* Set MISO_IDLE_VALUE in slave mode */
      AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_GPIO);
    }
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH2,PDMA_FLAG_TE))
  {
    /* Channel 4 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH2, PDMA_FLAG_TE);
  }

  /*----------------------------- SPI Transmitter ------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH3,PDMA_FLAG_TC))
  {
    /* Channel 5 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH3, PDMA_FLAG_TC);
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH3,PDMA_FLAG_TE))
  {
    /* Channel 5 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH3, PDMA_FLAG_TE);
  }

  /*-----------------------------SPI Receiver -----------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH4,PDMA_FLAG_TC))
  {
    /* Channel 4 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH4, PDMA_FLAG_TC);
    /* Set MISO idle value in slave mode */
    if((pSPIAPIState->pSPIx->CR1&SPI_MASTER) == 0)
    {
      /* Wait for Tx Complete */
      while(SPI_GetFlagStatus(pSPIAPIState->pSPIx,SPI_FLAG_TXE)!=SET);

      /* Set MISO_IDLE_VALUE in slave mode */
      AFIO_GPxConfig(pSPIAPIState->uGPIO_MISOId, pSPIAPIState->uGPIO_MISOAfioPin, AFIO_FUN_GPIO);
    }
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH4,PDMA_FLAG_TE))
  {
    /* Channel 4 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH4, PDMA_FLAG_TE);
  }

  /*----------------------------- SPI Transmitter ------------------------------------------------------*/
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH5,PDMA_FLAG_TC))
  {
    /* Channel 5 Transfer Complete, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH5, PDMA_FLAG_TC);
  }
  if(PDMA_GetFlagStatus(SPI_MODULE_PDMA_CH5,PDMA_FLAG_TE))
  {
    /* Channel 5 Transfer Error, Clear this flags */
    PDMA_ClearFlag(SPI_MODULE_PDMA_CH5, PDMA_FLAG_TE);
  }
}
#endif

/*********************************************************************************************************//**
  * @brief  Did SPI device receive data finish?
  * @retval Result: TRUE or False
  ***********************************************************************************************************/
bool _SPIAPI_IsRxFinish(u32 CH)
{
  #if SPICFG_PDMA_MODE
  HT_PDMACH_TypeDef *PDMACH;
  switch(CH)
  {
    #ifdef HTCFG_SPI_CH0
    case SPI_API_CH0:
    {
      #if SPICFG_CH0_PDMA_ENABLE
      PDMACH = SPI_API_CH0_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH1
    case SPI_API_CH1:
    {
      #if SPICFG_CH1_PDMA_ENABLE
      PDMACH = SPI_API_CH1_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH2
    case SPI_API_CH2:
    {
      #if SPICFG_CH2_PDMA_ENABLE
      PDMACH = SPI_API_CH2_RX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH3
    case SPI_API_CH3:
    {
      #if SPICFG_CH3_PDMA_ENABLE
      PDMACH = SPI_API_CH3_RX_PDMA;
      #endif
      break;
    }
    #endif
  }
  if((PDMACH->CTSR>>16) == 0)
  {
    return TRUE;
  }
  #else
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[CH];
  if(pSPIAPIState->uRxIndex == pSPIAPIState->uRxLength)
  {
    return TRUE;
  }
  #endif
  return FALSE;
}

/*********************************************************************************************************//**
  * @brief  Was SPI device transmit data finish?
  * @retval Result: TRUE or False
  ***********************************************************************************************************/
bool _SPIAPI_IsTxFinish(u32 CH)
{
  #if SPICFG_PDMA_MODE
  HT_PDMACH_TypeDef *PDMACH;
  switch(CH)
  {
    #ifdef HTCFG_SPI_CH0
    case SPI_API_CH0:
    {
      #if SPICFG_CH0_PDMA_ENABLE
      PDMACH = SPI_API_CH0_TX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH1
    case SPI_API_CH1:
    {
      #if SPICFG_CH1_PDMA_ENABLE
      PDMACH = SPI_API_CH1_TX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH2
    case SPI_API_CH2:
    {
      #if SPICFG_CH2_PDMA_ENABLE
      PDMACH = SPI_API_CH2_TX_PDMA;
      #endif
      break;
    }
    #endif
    #ifdef HTCFG_SPI_CH3
    case SPI_API_CH3:
    {
      #if SPICFG_CH3_PDMA_ENABLE
      PDMACH = SPI_API_CH3_TX_PDMA;
      #endif
      break;
    }
    #endif
  }
  if(0 == (PDMACH->CTSR>>16))
  {
    return TRUE;
  }
  #else
  SPIAPI_StateTypeDef *pSPIAPIState = &gSPIAPIState[CH];
  if(0 == pSPIAPIState->uTxLength)
  {
    return TRUE;
  }
  #endif
  return FALSE;
}

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief  Initial SPI_API Parameter.
 * @retval  None
 ************************************************************************************************************/
#if SPICFG_PDMA_MODE
#if (__CORTEX_M == 4)
void _SPIAPI_SetPDMAChannelPara(HT_PDMA_TypeDef* PDMAx, u32 PDMA_CHn , u32* Para)
{
  *Para = PDMA_CHn;
}
#else
void _SPIAPI_SetPDMAChannelPara(u32 PDMA_CHn , u32* Para)
{
  *Para = PDMA_CHn;
}
#endif
#endif

void _SPIAPI_InitAPIParameter(void)
{
  #ifdef HTCFG_SPI_CH0
  gSPIAPIState[SPI_API_CH0].pSPIx = _SPI_CH0;
  gSPIAPIState[SPI_API_CH0].pGPIO_MISO = _GPIO_MISO0;
  gSPIAPIState[SPI_API_CH0].uGPIO_MISOId =_MISO0_GPIO_ID;
  gSPIAPIState[SPI_API_CH0].uGPIO_MISOAfioPin =_MISO0_AFIO_PIN;
    #if SPICFG_PDMA_MODE
      #if SPICFG_CH0_PDMA_ENABLE
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH0_RX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH0].uPDMARxCh);
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH0_TX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH0].uPDMATxCh);
      #endif
    #endif
  #endif
  #ifdef HTCFG_SPI_CH1
  gSPIAPIState[SPI_API_CH1].pSPIx = _SPI_CH1;
  gSPIAPIState[SPI_API_CH1].pGPIO_MISO = _GPIO_MISO1;
  gSPIAPIState[SPI_API_CH1].uGPIO_MISOId =_MISO1_GPIO_ID;
  gSPIAPIState[SPI_API_CH1].uGPIO_MISOAfioPin =_MISO1_AFIO_PIN;
    #if SPICFG_PDMA_MODE
      #if SPICFG_CH1_PDMA_ENABLE
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH1_RX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH1].uPDMARxCh);
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH1_TX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH1].uPDMATxCh);
      #endif
    #endif
  #endif
  #ifdef HTCFG_SPI_CH2
  gSPIAPIState[SPI_API_CH2].pSPIx = _SPI_CH2;
  gSPIAPIState[SPI_API_CH2].pGPIO_MISO = _GPIO_MISO2;
  gSPIAPIState[SPI_API_CH2].uGPIO_MISOId =_MISO2_GPIO_ID;
  gSPIAPIState[SPI_API_CH2].uGPIO_MISOAfioPin =_MISO2_AFIO_PIN;
    #if SPICFG_PDMA_MODE
      #if SPICFG_CH2_PDMA_ENABLE
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH2_RX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH2].uPDMARxCh);
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH2_TX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH2].uPDMATxCh);
      #endif
    #endif
  #endif
  #ifdef HTCFG_SPI_CH3
  gSPIAPIState[SPI_API_CH3].pSPIx = _SPI_CH3;
  gSPIAPIState[SPI_API_CH3].pGPIO_MISO = _GPIO_MISO3;
  gSPIAPIState[SPI_API_CH3].uGPIO_MISOId =_MISO3_GPIO_ID;
  gSPIAPIState[SPI_API_CH3].uGPIO_MISOAfioPin =_MISO3_AFIO_PIN;
    #if SPICFG_PDMA_MODE
      #if SPICFG_CH3_PDMA_ENABLE
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH3_RX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH3].uPDMARxCh);
      _SPIAPI_SetPDMAChannelPara(SPI_API_CH3_TX_PDMA_CHANNEL, &gSPIAPIState[SPI_API_CH3].uPDMATxCh);
      #endif
    #endif
  #endif
}

#if FREERTOS_SPI
void SPIAPI_Init_FreeRTOS(u32 CH)
{
  taskENTER_CRITICAL();
  SPIAPI_Init(CH);
  Semphr[CH] = xSemaphoreCreateBinaryStatic(&Semphr_Buffer[CH]);
  Mutex[CH] = xSemaphoreCreateMutexStatic(&Mutex_Buffer[CH]);
  taskEXIT_CRITICAL();
}

u32 SPIAPI_WriteRead_FreeRTOS(u32 CH, SPIAPI_BufferTypeDef *pSPIAPIBuffer, u32 Timeout)
{
  TimeOut_t Tick_Base;

  vTaskSetTimeOutState(&Tick_Base);

  if(xSemaphoreTake(Mutex[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  taskENTER_CRITICAL();
  SPIAPI_ClearStatus(CH);
  SPIAPI_WriteRead(CH, pSPIAPIBuffer);
  xSemaphoreTake(Semphr[CH], 0);
  taskEXIT_CRITICAL();

  if(xTaskCheckForTimeOut(&Tick_Base, &Timeout) != pdFALSE)
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  if(xSemaphoreTake(Semphr[CH], Timeout) == pdFALSE)
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  xSemaphoreGive(Mutex[CH]);

  return Transfer_Result[CH];
}

void _SPIAPI_ISR_FreeRTOS(u32 CH)
{
  Transfer_Result[CH] = (SPIAPI_GetStatus(CH) == SPI_API_FINISH);
  if(SPIAPI_GetStatus(CH) == SPI_API_FINISH)
  {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}

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
