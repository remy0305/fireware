/*********************************************************************************************************//**
 * @file    SLED/RGB/main.c
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

/** @addtogroup RGB
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define LED_STRIP_DISP_LEN            (44)    /* 44 LEDs on the LED Strip                                   */
#define LED_GRB_DATA_LEN              (3)     /* 3 bytes                                                    */
#define LED_NUMBER_OF_COLOR_TYPES     (8)     /* 8 color type                                               */

/* Private function prototypes -----------------------------------------------------------------------------*/
void SLED_Configuration(void);
void SLED_MainRoutine(void);
void SLED_Output(u32 sled_beads, u32 colornum);
static void __Delay(u32 count);

/* Global variables ----------------------------------------------------------------------------------------*/
u8 __ALIGN4 gGRBTable[LED_NUMBER_OF_COLOR_TYPES][LED_GRB_DATA_LEN] = {
  { 0x00, 0xFF, 0x00 },     /* Red                                                                          */
  { 0xA5, 0xFF, 0x00 },     /* Orange                                                                       */
  { 0xFF, 0xFF, 0x00 },     /* Yellow                                                                       */
  { 0x80, 0x00, 0x00 },     /* Green                                                                        */
  { 0xFF, 0x00, 0xFF },     /* Cyan                                                                         */
  { 0x00, 0x00, 0xFF },     /* Blue                                                                         */
  { 0x00, 0x4B, 0x82 },     /* Indigo                                                                       */
  { 0x08, 0x80, 0x80 },     /* Violet                                                                       */
};

u32 i, j, k;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  SLED_Configuration();

  while (1)
  {
    SLED_MainRoutine();
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
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};

  /* Enable SLED & AFIO APB clock                                                                           */
  CKCUClock.Bit.AFIO             = 1;
  HTCFG_SLED_CLK(CKCUClock)      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

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
}

/*********************************************************************************************************//**
  * @brief  SLED Main Routine.
  * @retval None
  ***********************************************************************************************************/
void SLED_MainRoutine(void)
{
  /* Select color type                                                                                      */
  for (i = 0; i < LED_NUMBER_OF_COLOR_TYPES; i++)
  {
    /* Transmit SLED signal                                                                                 */
    SLED_Output(LED_STRIP_DISP_LEN, i);
    /* Delay                                                                                                */
    __Delay(SystemCoreClock/30);
  }
}

/*********************************************************************************************************//**
  * @brief  SLED Output.
  * @retval None
  ***********************************************************************************************************/
void SLED_Output(u32 sled_beads, u32 colornum)
{
  /* Waiting for SLED to enter the ready-to-transmit state                                                  */
  while (SLED_GetResetCodeStatus(HTCFG_SLED) != 0);
  /* Select LED                                                                                             */
  for(j = 0; j < sled_beads; j++)
  {
    /* Select RGB                                                                                           */
    for(k = 0; k < LED_GRB_DATA_LEN; k++)
    {
      /* Waiting for FIFO space to prevent write overflow                                                   */
      while (SLED_GetFIFOStatus(HTCFG_SLED) >= 4);
      /* Send data                                                                                          */
      HTCFG_SLED->DR_8BIT = gGRBTable[colornum][k];/* RGB Data. 8-bit access, duplicate 4 times into 32-bit */
    }
  }
  /* Enable Reset Code                                                                                      */
  SLED_InsertResetCode(HTCFG_SLED);
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
