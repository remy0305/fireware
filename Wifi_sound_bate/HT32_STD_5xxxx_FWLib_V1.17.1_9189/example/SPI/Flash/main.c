/*********************************************************************************************************//**
 * @file    SPI/Flash/main.c
 * @version $Rev:: 6386         $
 * @date    $Date:: 2022-10-27 #$
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

/** @addtogroup SPI_Examples SPI
  * @{
  */

/** @addtogroup Flash
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define FLASH_ID                                  (0xC22000)  // MX25L1606E = 0xC22015, MX25L6406E = 0xC22017
#define FLASH_ID_MASK                             (0xFFFF00)

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
  u32 i;

  /* Prepare test pattern                                                                                   */
  for (i = 0; i < FLASH_TEST_SIZE; i++)
  {
    gWrite_Buffer[i] = i;
  }

  /* Init and check Flash ID, turn on LED1 if success                                                       */
  SPI_FLASH_Init();                           /* Initialize the SPI_FLASH driver                            */
  gFLASH_ID = SPI_FLASH_ReadJEDECID();        /* Read and check SPI Flash ID                                */
  if ((gFLASH_ID & FLASH_ID_MASK) == FLASH_ID)
  {
    HT32F_DVB_LEDOn(HT_LED1);
  }

  /* Must clear the Block Protection bit before write or erase operation                                    */
  SPI_FLASH_WriteStatus(0x00);

  /* Sector Erase                                                                                           */
  SPI_FLASH_SectorErase(FLASH_TEST_ADDR);

  /* Write and Dual Read (for verify)                                                                       */
  SPI_FLASH_BufferWrite(gWrite_Buffer, FLASH_TEST_ADDR, FLASH_TEST_SIZE);
  #if (LIBCFG_SPI_NO_DUAL)
  SPI_FLASH_BufferRead(gRead_Buffer, FLASH_TEST_ADDR, FLASH_TEST_SIZE);
  #else
  SPI_FLASH_BufferDualRead((u16*)gRead_Buffer, FLASH_TEST_ADDR, FLASH_TEST_SIZE/2);
  #endif
  Flash_Verify();

  /* Sector Erase                                                                                           */
  SPI_FLASH_SectorErase(FLASH_TEST_ADDR);

  /* Read and Blank check                                                                                   */
  SPI_FLASH_BufferRead(gRead_Buffer, FLASH_TEST_ADDR, FLASH_TEST_SIZE);
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
