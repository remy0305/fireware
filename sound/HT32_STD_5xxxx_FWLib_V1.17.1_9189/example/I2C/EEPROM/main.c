/*********************************************************************************************************//**
 * @file    I2C/EEPROM/main.c
 * @version $Rev:: 4444         $
 * @date    $Date:: 2019-12-25 #$
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
#include <stdlib.h>
#include "ht32.h"
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup I2C_Examples I2C
  * @{
  */

/** @addtogroup EEPROM
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void EEPROM_WriteReadTest(void);

/* Private constants ---------------------------------------------------------------------------------------*/
#define EEPROM_PAGE_CNT   (I2C_EEPROM_CAPACITY / I2C_EEPROM_PAGE_SIZE)

/* Global variables ----------------------------------------------------------------------------------------*/
__ALIGN4 u8 gWriteBuf[I2C_EEPROM_PAGE_SIZE];
__ALIGN4 u8 gReadBuf[I2C_EEPROM_PAGE_SIZE];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();           /* Retarget Related configuration                                     */

  /* print message                                                                                          */
  printf("\r\n*** HT32 I2C Example Code ***");
  printf("\r\n24LC02 EEPROM verifying : ");

  /* init EEPROM                                                                                            */
  I2C_EEPROM_Init();

  EEPROM_WriteReadTest();

  while (1);
}

/*********************************************************************************************************//**
  * @brief  Read and write EEPROM to check the entire data.
  * @retval None
  ***********************************************************************************************************/
void EEPROM_WriteReadTest(void)
{
  u32 i, j, *pBuf;

  for (j = 0; j < EEPROM_PAGE_CNT; j++)
  {
    /* generate test pattern                                                                                */
    pBuf = (u32 *)gWriteBuf;
    for (i = 0; i < (I2C_EEPROM_PAGE_SIZE / 4); i++)
    {
      *pBuf++ = rand();
    }

    /* Clean read buffer as 0xC3C3C3C3                                                                      */
    pBuf = (u32 *)gReadBuf;
    for (i = 0; i < (I2C_EEPROM_PAGE_SIZE / 4); i++)
    {
      *pBuf++ = 0xC3C3C3C3;
    }

    /* Write data                                                                                           */
    I2C_EEPROM_BufferWrite((u8 *)gWriteBuf, I2C_EEPROM_PAGE_SIZE * j, I2C_EEPROM_PAGE_SIZE);

    /* Read data                                                                                            */
    I2C_EEPROM_BufferRead((u8 *)gReadBuf, I2C_EEPROM_PAGE_SIZE * j, I2C_EEPROM_PAGE_SIZE);

    /* Compare Data                                                                                         */
    for (i = 0; i < (I2C_EEPROM_PAGE_SIZE); i++)
    {
      if (gReadBuf[i] != gWriteBuf[i])
      {
        printf(" [Failed]\n");
        while (1);
      }
    }

    printf("\r\t\t\t\t%d%%", (int)((j + 1) * 100)/EEPROM_PAGE_CNT);
  }

  printf(" [Pass]\n");
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
