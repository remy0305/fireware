/*********************************************************************************************************//**
 * @file    SLED/PDMA/main.c
 * @version $Rev:: 8392         $
 * @date    $Date:: 2025-02-17 #$
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SLED_Examples SLED
  * @{
  */

/** @addtogroup SLED_PDMA
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define LED_STRIP_DISP_LEN            (44)    /* LED strip count                                            */
#define LED_GRB_DATA_LEN              (3)     /* GRB 3 bytes                                                */
#define LED_STRIP_PATN_LEN            (8)

/* Private function prototypes -----------------------------------------------------------------------------*/
void CKCU_Configuration(void);
void SLED_Configuration(void);
void PDMA_Configuration(void);
void SLED_MainRoutine(void);
static void __Delay(u32 count);


/* Global variables ----------------------------------------------------------------------------------------*/
u8 gColorTable[LED_STRIP_PATN_LEN][LED_GRB_DATA_LEN] =
{
  { 0xFF, 0x66, 0x66 }, // HSL(120, 100%,  70%)
  { 0xFF, 0x38, 0x38 }, // HSL(120, 100%,  61%)
  { 0xFF, 0x0A, 0x0A }, // HSL(120, 100%,  52%)
  { 0xDB, 0x00, 0x00 }, // HSL(120, 100%,  43%)
  { 0xAD, 0x00, 0x00 }, // HSL(120, 100%,  34%)
  { 0x80, 0x00, 0x00 }, // HSL(120, 100%,  25%)
  { 0x52, 0x00, 0x00 }, // HSL(120, 100%,  16%)
  { 0x24, 0x00, 0x00 }, // HSL(120, 100%,   7%)
};

u32 new_pix_cnt = 0;
u8 gDispBuf[LED_STRIP_DISP_LEN][LED_GRB_DATA_LEN];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  CKCU_Configuration();

  SLED_Configuration();

  PDMA_Configuration();

  while (1)
  {
    SLED_MainRoutine();
    __Delay(SystemCoreClock/200);
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the SLED.
  * @retval None
  ***********************************************************************************************************/
void SLED_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below this function.
  */
  SLED_InitTypeDef SLED_InitStruct;

  /* Configure GPIO to SLED mode                                                                            */
  AFIO_GPxConfig(HTCFG_SLED_GPIO_ID, HTCFG_SLED_AFIO_PIN, AFIO_FUN_SLED);

  /* Configure SLED                                                                                         */
  SLED_InitStruct.ClockPrescaler = HTCFG_SLED_CK_PRESCALER; /* F_PCLK / HTCFG_SLED_CK_PRESCALER    = 20M Hz */
  SLED_InitStruct.BaudRate       = HTCFG_SLED_BAUDRATE - 1; /* F_SCLK / HTCFG_SLED_BAUDRATE        = 800K Hz*/
  SLED_InitStruct.T0H            = HTCFG_SLED_T0H - 1;      /* 5/25 = 20% Duty. 1/800K * (20/100)  = 0.25u s*/
  SLED_InitStruct.T1H            = HTCFG_SLED_T1H - 1;      /* 20/25 = 80% Duty. 1/800K * (80/100) = 1.00u s*/
  SLED_InitStruct.TRST           = HTCFG_SLED_TRST - 1;     /* HTCFG_SLED_TRST * 1/800K            = 280u s */
  SLED_InitStruct.SyncState      = SLED_SYNC_STATE_T0;
  SLED_InitStruct.IdleState      = SLED_IDLE_STATE_LOW;
  SLED_InitStruct.ResetState     = SLED_RESET_STATE_LOW;
  SLED_InitStruct.SyncMode       = SLED_SYNC_MODE_DISABLE;
  SLED_InitStruct.OutputPolarity = SLED_OUTPUT_NONINVERTING;
  SLED_Init(HTCFG_SLED, &SLED_InitStruct);

  /* Enable SLED                                                                                            */
  SLED_OutputCmd(HTCFG_SLED, ENABLE);
  SLED_FIFOTrigLevelConfig(HTCFG_SLED, SLED_FIFO_LEVEL_1);
  SLED_Cmd(HTCFG_SLED, ENABLE);

  /* Enable PDMA                                                                                            */
  SLED_PDMACmd(HTCFG_SLED, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure the PDMA.
  * @retval None
  ***********************************************************************************************************/
void PDMA_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below this function.
  */
  PDMACH_InitTypeDef PDMACH_InitStruct;

  /*--------------------------------------------------------------------------------------------------------*/
  /* Start lighting the LED strip by SLED                                                                   */
  /* PDMA Configuration : gDispBuf to HTCFG_SLED->DR, linear increment to fix, 8-bit.                       */
  /*--------------------------------------------------------------------------------------------------------*/
  PDMACH_InitStruct.PDMACH_AdrMod   = AUTO_RELOAD | SRC_ADR_LIN_INC | DST_ADR_FIX;
  PDMACH_InitStruct.PDMACH_SrcAddr  = (u32)&gDispBuf[0][0];
  PDMACH_InitStruct.PDMACH_DstAddr  = (u32)&HTCFG_SLED->DR_8BIT;
  PDMACH_InitStruct.PDMACH_DataSize = WIDTH_8BIT;
  PDMACH_InitStruct.PDMACH_BlkLen   = LED_GRB_DATA_LEN;
  PDMACH_InitStruct.PDMACH_BlkCnt   = LED_STRIP_DISP_LEN;
  PDMACH_InitStruct.PDMACH_Priority = H_PRIO;
  PDMA_Config(HTCFG_SLED_PDMA_RAM_TO_DR_CH, &PDMACH_InitStruct);

  /* HTCFG_SLED_PDMA_RAM_TO_DR_CH is used to move the RAM data to the  DR of SLED.                          */
  PDMA_IntConfig(HTCFG_SLED_PDMA_RAM_TO_DR_CH, PDMA_INT_TC, ENABLE);


  /*--------------------------------------------------------------------------------------------------------*/
  /* Shift the pixel data.                                                                                  */
  /* PDMA Configuration : gDispBuf to gDispBuf, linear decrement to linear decrement, 8-bit.                */
  /*--------------------------------------------------------------------------------------------------------*/
  PDMACH_InitStruct.PDMACH_AdrMod   = AUTO_RELOAD | SRC_ADR_LIN_DEC | DST_ADR_LIN_DEC;
  PDMACH_InitStruct.PDMACH_SrcAddr  = (u32)&(gDispBuf[LED_STRIP_DISP_LEN - 2][2]);
  PDMACH_InitStruct.PDMACH_DstAddr  = (u32)&(gDispBuf[LED_STRIP_DISP_LEN - 1][2]);
  PDMACH_InitStruct.PDMACH_DataSize = WIDTH_8BIT;
  PDMACH_InitStruct.PDMACH_BlkLen   = LED_GRB_DATA_LEN;
  PDMACH_InitStruct.PDMACH_BlkCnt   = LED_STRIP_DISP_LEN - 1;
  PDMACH_InitStruct.PDMACH_Priority = M_PRIO;
  PDMA_Config(HTCFG_SLED_PDMA_RAM_TO_RAM_CH, &PDMACH_InitStruct);

  /* HTCFG_SLED_PDMA_RAM_TO_RAM_CH is used to data shift.                                                   */
  PDMA_IntConfig(HTCFG_SLED_PDMA_RAM_TO_RAM_CH, PDMA_INT_TC, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  SLED Main Routine.
  * @retval None
  ***********************************************************************************************************/
void SLED_MainRoutine(void)
{
  u32 i;

  /* Waiting for Reset Code to complete                                                                     */
  while (SLED_GetResetCodeStatus(HTCFG_SLED) != 0);

  /* Enable RESET Code                                                                                      */
  SLED_InsertResetCode(HTCFG_SLED);

  /*--------------------------------------------------------------------------------------------------------*/
  /* Start lighting the LED strip by SLED                                                                   */
  /* PDMA Configuration : gDispBuf to HTCFG_SLED->DR, linear increment to fix, 8-bit.                       */
  /*--------------------------------------------------------------------------------------------------------*/
  PDMA_EnaCmd(HTCFG_SLED_PDMA_RAM_TO_DR_CH, ENABLE);

  /* Check transfer finish                                                                                  */
  while (PDMA_GetFlagStatus(HTCFG_SLED_PDMA_RAM_TO_DR_CH, PDMA_FLAG_TC) == RESET);
  PDMA_EnaCmd(HTCFG_SLED_PDMA_RAM_TO_DR_CH, DISABLE);
  PDMA_ClearFlag(HTCFG_SLED_PDMA_RAM_TO_DR_CH, PDMA_FLAG_TC);

  /*--------------------------------------------------------------------------------------------------------*/
  /* Shift the pixel data.                                                                                  */
  /* PDMA Configuration : gDispBuf to gDispBuf, linear decrement to linear decrement, 8-bit.                */
  /*--------------------------------------------------------------------------------------------------------*/
  PDMA_EnaCmd(HTCFG_SLED_PDMA_RAM_TO_RAM_CH, ENABLE);
  PDMA_SwTrigCmd(HTCFG_SLED_PDMA_RAM_TO_RAM_CH, ENABLE);

  /* Check transfer finish                                                                                  */
  while (PDMA_GetFlagStatus(HTCFG_SLED_PDMA_RAM_TO_RAM_CH, PDMA_FLAG_TC) == RESET);
  PDMA_EnaCmd(HTCFG_SLED_PDMA_RAM_TO_RAM_CH, DISABLE);
  PDMA_ClearFlag(HTCFG_SLED_PDMA_RAM_TO_RAM_CH, PDMA_FLAG_TC);

  /*--------------------------------------------------------------------------------------------------------*/
  /* 1. Add new one pixel.                                                                                  */
  /* 2. Shift Color Table.                                                                                  */
  /*--------------------------------------------------------------------------------------------------------*/
  /* Add new one pixel                                                                                      */
  if (new_pix_cnt < LED_STRIP_PATN_LEN)
  {
    /* Turn on the LED                                                                                      */
    gDispBuf[0][0] = gColorTable[new_pix_cnt][0];
    gDispBuf[0][1] = gColorTable[new_pix_cnt][1];
    gDispBuf[0][2] = gColorTable[new_pix_cnt][2];
  }
  else
  {
    /* Turn off the LED                                                                                     */
    gDispBuf[0][0] = 0;
    gDispBuf[0][1] = 0;
    gDispBuf[0][2] = 0;
  }

  /* Shift Color Table                                                                                      */
  if (++new_pix_cnt > (LED_STRIP_DISP_LEN - 1))
  {
    /* Change color                                                                                         */
    for (i = 0; i < LED_STRIP_PATN_LEN; i++)
    {
      u8 tmp;
      tmp = gColorTable[i][0];
      gColorTable[i][0] = gColorTable[i][1];
      gColorTable[i][1] = gColorTable[i][2];
      gColorTable[i][2] = tmp;
    }
    new_pix_cnt = 0;
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  /* Enable SLED & AFIO APB clock                                                                           */
  CKCUClock.Bit.AFIO             = 1;
  CKCUClock.Bit.PDMA             = 1;
  HTCFG_SLED_CLK(CKCUClock)      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
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

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  delay function
  * @param  count: delay count for loop
  * @retval None
  ***********************************************************************************************************/
static void __Delay(u32 count)
{
  while (count--)
  {
    __NOP(); // Prevent delay loop be optimized
  }
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
