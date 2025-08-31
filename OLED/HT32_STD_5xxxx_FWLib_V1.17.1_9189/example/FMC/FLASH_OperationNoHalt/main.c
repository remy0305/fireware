/*********************************************************************************************************//**
 * @file    FMC/FLASH_OperationNoHalt/main.c
 * @version $Rev:: 5928         $
 * @date    $Date:: 2022-06-01 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup FMC_Examples FMC
  * @{
  */

/** @addtogroup FLASH_OperationNoHalt
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define HTCFG_SYSTICK_TIME_BASE           (LIBCFG_MAX_SPEED * 0.0001)     /* 0.1 ms                         */

#define TEST_START_ADDR    (1024 * 4)
#define TEST_END_ADDR      (1024 * 5)

/* Private constants ---------------------------------------------------------------------------------------*/
#define TEST_DATA          (0x12345678)
#define TEST_LEN           (TEST_END_ADDR - TEST_START_ADDR)

/* Private function prototypes -----------------------------------------------------------------------------*/
void InitVector(u32 uSource, u32 uRAMAddress);
void GPIO_Configuration(void);
void SysTick_Configuration(void);

void FLASH_Erase(void);
void FLASH_Program(void);
void FLASH_Check(void);

void Flash_Test(void);

/* Global variables ----------------------------------------------------------------------------------------*/
u32 uData[TEST_LEN/4];
u32 err;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  #if 1
  InitVector(0x00000000, 0x20000000);
  NVIC_SetVectorTable(NVIC_VECTTABLE_RAM, 0);
  #endif

  GPIO_Configuration();

  SysTick_Configuration();

  Flash_Test();

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Flash Test.
  * @retval None
  ***********************************************************************************************************/
void Flash_Test(void)
{
  {
    u32 i;
    for (i = 0; i < TEST_LEN/4 ; i++)
    {
      uData[i] = TEST_DATA;
    }
  }

  /* Erase Flash pages before program data                                                                  */
  HT_GPIOB->DOUTR ^= 1 << 2;
  FLASH_Erase();
  /* Program Word data                                                                                      */
  HT_GPIOB->DOUTR ^= 1 << 2;
  FLASH_Program();
  HT_GPIOB->DOUTR ^= 1 << 2;

  /* Check Flash data                                                                                       */
  FLASH_Check();
  if (err != 0)
  {
    while (1); /* Test Failed                                                                               */
  }

  while (1); /* Test Passed                                                                                 */
}

/*********************************************************************************************************//**
  * @brief  Init RAM Vector.
  * @retval None
  ***********************************************************************************************************/
void InitVector(u32 uSource, u32 uRAMAddress)
{
  u32 i;
  u32 *VectorTable = (u32 *)uRAMAddress;
  vu32 *Source = (u32 *)uSource; /* Fix the issue of Arm Compiler Version V6.18 (u32 -> vu32)               */

  for (i = 0; i < 16 + 32; i++)
  {
    VectorTable[i] = Source[i];
  }
}

/*********************************************************************************************************//**
  * @brief  Configure GPIO.
  * @retval None
  ***********************************************************************************************************/
void GPIO_Configuration(void)
{
  {
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PB       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_0, GPIO_DIR_OUT);
  GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_2, GPIO_DIR_OUT);
}

/*********************************************************************************************************//**
  * @brief  Configure SysTick.
  * @retval None
  ***********************************************************************************************************/
void SysTick_Configuration(void)
{
  SYSTICK_ClockSourceConfig(SYSTICK_SRC_FCLK);
  SYSTICK_SetReloadValue(HTCFG_SYSTICK_TIME_BASE);
  SYSTICK_IntConfig(ENABLE);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
}

/*********************************************************************************************************//**
  * @brief Erase FLASH Byte page.
  * @retval None
 ************************************************************************************************************/
void FLASH_Erase(void)
{
  u32 Addr;
  FLASH_State FLASHState;

  for (Addr = TEST_START_ADDR; Addr < TEST_END_ADDR; Addr += FLASH_PAGE_SIZE)
  {
    FLASHState = FLASH_ErasePage(Addr);

    if (FLASHState != FLASH_COMPLETE)
    {
      err++;
    }
  }
}

/*********************************************************************************************************//**
  * @brief Program FLASH Byte page.
  * @retval None
 ************************************************************************************************************/
void FLASH_Program(void)
{
  u32 Addr;
  u32 i = 0;
  FLASH_State FLASHState;

  for (Addr = TEST_START_ADDR; Addr < TEST_END_ADDR; Addr += 4)
  {
    FLASHState = FLASH_ProgramWordData(Addr, uData[i++]);

    if (FLASHState != FLASH_COMPLETE)
    {
      err++;
    }
  }
}

/*********************************************************************************************************//**
  * @brief Check FLASH Byte page.
  * @retval None
 ************************************************************************************************************/
void FLASH_Check(void)
{
  u32 Addr;

  for (Addr = TEST_START_ADDR; Addr < TEST_END_ADDR; Addr += 4)
  {
    if (rw(Addr) != TEST_DATA)
    {
      err++;
    }
  }
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
