/*********************************************************************************************************//**
 * @file    SPI/PDMA/main.c
 * @version $Rev:: 6679         $
 * @date    $Date:: 2023-01-17 #$
 * @brief   Main program.
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
#include "ht32_board.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SPI_Examples SPI
  * @{
  */

/** @addtogroup SPI_PDMA
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define BUF_SIZE                                  (16)

/* Private function prototypes -----------------------------------------------------------------------------*/
void SPI_Slave_Configuration(void);
void SPI_Master_Configuration(void);

void SPI_Loopback_Test(void);

ErrStatus CmpBuffer(u8* Buffer1, u8* Buffer2, u32 BufferLength);

/* Private variables ---------------------------------------------------------------------------------------*/
u8 SPI0_Buffer_Tx[BUF_SIZE] = {
  0x00, 0x11, 0x22, 0x33,
  0x44, 0x55, 0x66, 0x77,
  0x88, 0x99, 0xAA, 0xBB,
  0xCC, 0xDD, 0xEE, 0xFF
};

u8 SPI0_Buffer_Rx[BUF_SIZE] = {0};

u8 SPI1_Buffer_Tx[BUF_SIZE] = {
  0xFF, 0xEE, 0xDD, 0xCC,
  0xBB, 0xAA, 0x99, 0x88,
  0x77, 0x66, 0x55, 0x44,
  0x33, 0x22, 0x11, 0x00
};

u8 SPI1_Buffer_Rx[BUF_SIZE] = {0};

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);

  SPI_Slave_Configuration();
  SPI_Master_Configuration();

  SPI_Loopback_Test();

  while (1);
}

/*********************************************************************************************************//**
  * @brief  Configure the SPI Slave.
  * @retval None
  ***********************************************************************************************************/
void SPI_Slave_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO                    = 1;
    CKCUClock.Bit.HTCFG_SPIS_SEL_GPIO_CLK = 1;
    CKCUClock.Bit.HTCFG_SPIS_IPN          = 1;
    CKCUClock.Bit.PDMA                    = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* PDMA related settings for SPI Slave                                                                  */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;

    /* Slave Slave Tx PDMA channel configuration                                                            */
    PDMACH_InitStructure.PDMACH_SrcAddr = (u32) &SPI1_Buffer_Tx;
    PDMACH_InitStructure.PDMACH_DstAddr = (u32) &HTCFG_SPIS_PORT->DR;
    PDMACH_InitStructure.PDMACH_BlkCnt = BUF_SIZE;
    PDMACH_InitStructure.PDMACH_BlkLen = 1;
    PDMACH_InitStructure.PDMACH_DataSize = WIDTH_8BIT;
    PDMACH_InitStructure.PDMACH_Priority = H_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
    PDMA_Config(HTCFG_SPIS_PDMA_TX, &PDMACH_InitStructure);

    /* Slave Slave Rx PDMA channel configuration                                                            */
    PDMACH_InitStructure.PDMACH_SrcAddr = (u32) &HTCFG_SPIS_PORT->DR;
    PDMACH_InitStructure.PDMACH_DstAddr = (u32) &SPI1_Buffer_Rx;
    PDMACH_InitStructure.PDMACH_Priority = VH_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
    PDMA_Config(HTCFG_SPIS_PDMA_RX, &PDMACH_InitStructure);

    /* Enable Slave Tx, Rx GE & TC interrupt                                                                */
    PDMA_IntConfig(HTCFG_SPIS_PDMA_TX, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
    PDMA_IntConfig(HTCFG_SPIS_PDMA_RX, PDMA_INT_GE | PDMA_INT_TC, ENABLE);

    /* Enable the corresponding PDMA channel                                                                */
    PDMA_EnaCmd(HTCFG_SPIS_PDMA_TX, ENABLE);
    PDMA_EnaCmd(HTCFG_SPIS_PDMA_RX, ENABLE);
  }

  /* Enable Slave SEL pull up (idle high)                                                                   */
  GPIO_PullResistorConfig(HTCFG_SPIS_SEL_GPIO_PORT, HTCFG_SPIS_SEL_AFIO_PIN, GPIO_PR_UP);

  /* Configure AFIO mode as SPI function                                                                    */
  AFIO_GPxConfig(HTCFG_SPIS_SEL_GPIO_ID,  HTCFG_SPIS_SEL_AFIO_PIN, AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_SPIS_SCK_GPIO_ID,  HTCFG_SPIS_SCK_AFIO_PIN, AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_SPIS_MOSI_GPIO_ID, HTCFG_SPIS_MOSI_AFIO_PIN, AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_SPIS_MISO_GPIO_ID, HTCFG_SPIS_MISO_AFIO_PIN, AFIO_FUN_SPI);

  { /* SPI related settings                                                                                 */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    SPI_InitTypeDef SPI_InitStructure;

    SPI_InitStructure.SPI_Mode = SPI_SLAVE;
    SPI_InitStructure.SPI_FIFO = SPI_FIFO_DISABLE;
    SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
    SPI_InitStructure.SPI_SELMode = SPI_SEL_HARDWARE;
    SPI_InitStructure.SPI_SELPolarity = SPI_SELPOLARITY_LOW;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_LOW;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_FIRST;
    SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
    SPI_InitStructure.SPI_RxFIFOTriggerLevel = 0;
    SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;
    SPI_InitStructure.SPI_ClockPrescaler = 4;
    SPI_Init(HTCFG_SPIS_PORT, &SPI_InitStructure);
  }

  SPI_Cmd(HTCFG_SPIS_PORT, ENABLE);
  SPI_PDMACmd(HTCFG_SPIS_PORT, SPI_PDMAREQ_TX | SPI_PDMAREQ_RX, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure the SPI Master.
  * @retval None
  ***********************************************************************************************************/
void SPI_Master_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO           = 1;
    CKCUClock.Bit.HTCFG_SPIM_IPN = 1;
    CKCUClock.Bit.PDMA           = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* PDMA related settings for SPI Master                                                                 */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;

    /* Master Master Tx PDMA channel configuration                                                          */
    PDMACH_InitStructure.PDMACH_SrcAddr = (u32) &SPI0_Buffer_Tx;
    PDMACH_InitStructure.PDMACH_DstAddr = (u32) &HTCFG_SPIM_PORT->DR;
    PDMACH_InitStructure.PDMACH_BlkCnt = BUF_SIZE;
    PDMACH_InitStructure.PDMACH_BlkLen = 1;
    PDMACH_InitStructure.PDMACH_DataSize = WIDTH_8BIT;
    PDMACH_InitStructure.PDMACH_Priority = M_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_LIN_INC | DST_ADR_FIX;
    PDMA_Config(HTCFG_SPIM_PDMA_TX, &PDMACH_InitStructure);

    /* Master Master Rx PDMA channel configuration                                                          */
    PDMACH_InitStructure.PDMACH_SrcAddr = (u32) &HTCFG_SPIM_PORT->DR;
    PDMACH_InitStructure.PDMACH_DstAddr = (u32) &SPI0_Buffer_Rx;
    PDMACH_InitStructure.PDMACH_Priority = VH_PRIO;
    PDMACH_InitStructure.PDMACH_AdrMod = SRC_ADR_FIX | DST_ADR_LIN_INC;
    PDMA_Config(HTCFG_SPIM_PDMA_RX, &PDMACH_InitStructure);

    /* Enable Master Tx, Rx GE & TC interrupt                                                               */
    PDMA_IntConfig(HTCFG_SPIM_PDMA_TX, PDMA_INT_GE | PDMA_INT_TC, ENABLE);
    PDMA_IntConfig(HTCFG_SPIM_PDMA_RX, PDMA_INT_GE | PDMA_INT_TC, ENABLE);

    /* Enable the corresponding PDMA channel                                                                */
    PDMA_EnaCmd(HTCFG_SPIM_PDMA_TX, ENABLE);
    PDMA_EnaCmd(HTCFG_SPIM_PDMA_RX, ENABLE);
  }

  /* Configure AFIO mode as SPI function                                                                    */
  AFIO_GPxConfig(HTCFG_SPIM_SEL_GPIO_ID,  HTCFG_SPIM_SEL_AFIO_PIN,   AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_SPIM_SCK_GPIO_ID,  HTCFG_SPIM_SCK_AFIO_PIN,   AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_SPIM_MOSI_GPIO_ID, HTCFG_SPIM_MOSI_AFIO_PIN , AFIO_FUN_SPI);
  AFIO_GPxConfig(HTCFG_SPIM_MISO_GPIO_ID, HTCFG_SPIM_MISO_AFIO_PIN , AFIO_FUN_SPI);

  { /* SPI related settings                                                                                 */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    SPI_InitTypeDef SPI_InitStructure;

    SPI_InitStructure.SPI_Mode = SPI_MASTER;
    SPI_InitStructure.SPI_FIFO = SPI_FIFO_DISABLE;
    SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
    SPI_InitStructure.SPI_SELMode = SPI_SEL_HARDWARE;
    SPI_InitStructure.SPI_SELPolarity = SPI_SELPOLARITY_LOW;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_LOW;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_FIRST;
    SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
    SPI_InitStructure.SPI_RxFIFOTriggerLevel = 0;
    SPI_InitStructure.SPI_TxFIFOTriggerLevel = 0;
    SPI_InitStructure.SPI_ClockPrescaler = 4;
    SPI_Init(HTCFG_SPIM_PORT, &SPI_InitStructure);
  }

  /* Set SS as output mode for slave select                                                                 */
  SPI_SELOutputCmd(HTCFG_SPIM_PORT, ENABLE);
  SPI_Cmd(HTCFG_SPIM_PORT, ENABLE);
  SPI_PDMACmd(HTCFG_SPIM_PORT, SPI_PDMAREQ_TX | SPI_PDMAREQ_RX, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  The SPI send data.
  * @retval None
  ***********************************************************************************************************/
void SPI_Loopback_Test(void)
{
  /* Wait for transmission finished                                                                         */
  while (!PDMA_GetFlagStatus(HTCFG_SPIS_PDMA_RX, PDMA_FLAG_TC))
  {
    HT32F_DVB_LEDToggle(HT_LED2);
  }
  HT32F_DVB_LEDOff(HT_LED2);

  /* Check on validity of received data on Master & Slave                                                   */
  if (CmpBuffer(SPI0_Buffer_Tx, SPI1_Buffer_Rx, BUF_SIZE) == SUCCESS &&
      CmpBuffer(SPI1_Buffer_Tx, SPI0_Buffer_Rx, BUF_SIZE) == SUCCESS)
  {
    /* Turn on LED1 if the transmitted and received data are equal                                          */
    HT32F_DVB_LEDOn(HT_LED1);
  }
  else
  {
    /* Turn on LED2 if the transmitted and received data are different                                      */
    HT32F_DVB_LEDOn(HT_LED2);
  }
}

/*********************************************************************************************************//**
  * @brief  Compare two buffers.
  * @param  Buffer1, Buffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CmpBuffer(u8* Buffer1, u8* Buffer2, u32 BufferLength)
{
  while (BufferLength--)
  {
    if (*Buffer1 != *Buffer2)
    {
      return ERROR;
    }

    Buffer1++;
    Buffer2++;
  }

  return SUCCESS;
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
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
