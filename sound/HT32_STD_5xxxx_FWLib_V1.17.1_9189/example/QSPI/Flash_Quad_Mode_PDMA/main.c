/*********************************************************************************************************//**
 * @file    QSPI/Flash_Quad_Mode_PDMA/main.c
 * @version $Rev:: 4907         $
 * @date    $Date:: 2020-08-11 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup QSPI_Examples QSPI
  * @{
  */

/** @addtogroup Flash_Quad_Mode_PDMA
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define FLASH_TEST_SIZE                           (256)       // Shall be less or equal to the sector size
                                                              // (erase size in one time)
#define FLASH_TEST_ADDR                           (0x100000)

/* Private function prototypes -----------------------------------------------------------------------------*/
void Flash_Test(void);
void Flash_Verify(void);
void Flash_BlankCheck(void);

/* Global variables ----------------------------------------------------------------------------------------*/
vu32 gFLASH_ID = 0;
u8 gWrite_Buffer[FLASH_TEST_SIZE];
__ALIGN4 u8 gRead_Buffer[FLASH_TEST_SIZE];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);
  HT32F_DVB_LEDInit(HT_LED3);

  Flash_Test();

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  SPI Flash Test Function.
  * @retval None
  ***********************************************************************************************************/
void Flash_Test(void)
{
  u8 status;
  u32 i;

  /* Prepare test pattern                                                                                   */
  for (i = 0; i < FLASH_TEST_SIZE; i++)
  {
    gWrite_Buffer[i] = i;
  }

  /* Initialize the QSPI flash driver                                                                       */
  SPI_FLASH_Init();

  /* Read SPI Flash ID                                                                                      */
  gFLASH_ID = SPI_FLASH_ReadJEDECID();

  /* Set Status Reg and Configuration Reg                                                                   */
  /*  Status Reg       : 0x40, Quad Enable, clear the Block Protection bit                                  */
  /*  Configuration Reg: 0x00                                                                               */
  /* !!! NOTICE !!!
     The output driver strength (ODS) can be adjusted in the Configuration Register depending on the
     Flash model.
  */
  status = SPI_FLASH_WriteStatus2(0x40, 0x00);
  if ((status & 0x40) == 0) // Check the Quad Enable success
  {
    while (1); /* Should not reach here, which means the Serial Flash does not support Quad Enable (QE) bit */
  }

  HT32F_DVB_LEDOn(HT_LED1);

  /* Sector Erase                                                                                           */
  SPI_FLASH_SectorErase(FLASH_TEST_ADDR);

  /* Quad Write and Read by DMA (for verify)                                                                */
  QSPI_FLASH_BufferWriteByDMA(gWrite_Buffer, FLASH_TEST_ADDR, FLASH_TEST_SIZE);
  QSPI_FLASH_BufferQuadReadByDMA((u16*)gRead_Buffer, FLASH_TEST_ADDR, FLASH_TEST_SIZE/2);
  Flash_Verify();

  /* Sector Erase                                                                                           */
  SPI_FLASH_SectorErase(FLASH_TEST_ADDR);

  /* Read by DMA and Blank check                                                                            */
  QSPI_FLASH_BufferQuadReadByDMA((u16*)gRead_Buffer, FLASH_TEST_ADDR, FLASH_TEST_SIZE/2);
  Flash_BlankCheck();
}

/*********************************************************************************************************//**
  * @brief  Verify by compare the read buffer with write buffer, turn on LED2 if success.
  * @retval None
  ***********************************************************************************************************/
void Flash_Verify(void)
{
  u32 i;
  u32 err = 0;

  /* Check the data of read/write buffer are the same                                                       */
  for (i = 0; i < FLASH_TEST_SIZE; i++)
  {
    if (gRead_Buffer[i] != gWrite_Buffer[i])
    {
      err++;
    }
  }

  if (err == 0)
  {
    HT32F_DVB_LEDOn(HT_LED2);
  }
}

/*********************************************************************************************************//**
  * @brief  Blank check by confirm the read buffer, turn on LED3 if success.
  * @retval None
  ***********************************************************************************************************/
void Flash_BlankCheck(void)
{
  u32 i;
  u32 err = 0;

  /* Confirm the data of read buffer are all 0xFF                                                           */
  for (i = 0; i < FLASH_TEST_SIZE; i++)
  {
    if (gRead_Buffer[i] != 0xFF)
    {
      err++;
    }
  }

  if (err == 0)
  {
    HT32F_DVB_LEDOn(HT_LED3);
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
