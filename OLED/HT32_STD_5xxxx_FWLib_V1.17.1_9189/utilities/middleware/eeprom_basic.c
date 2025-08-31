/*********************************************************************************************************//**
 * @file    eeprom_basic.c
 * @version $Rev:: 508          $
 * @date    $Date:: 2022-03-10 #$
 * @brief   The source file of EEPROM emulation APIs.
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
#include "eeprom_basic.h"

/** @addtogroup EEPROM_Basic_Examples EEPROM_Basic
  * @{
  */

/** @addtogroup EEPROM_Basic
  * @{
  */

/* Private constants ---------------------------------------------------------------------------------------*/
#if (EEPROM_BASIC_LENGTH <= 0)
  #error "EEPROM_BASIC_LENGTH is not correct (must >= 1)!"
#endif

#if (EEPROM_BASIC_LENGTH > LIBCFG_FLASH_PAGESIZE)
  #error "EEPROM_BASIC_LENGTH is not correct (must <= Page Size)!"
#endif

#if (EEPROM_BASIC_START_NUM <= 0)
  #error "EEPROM_BASIC_START_NUM is not correct (must >= 1)!"
#endif

#if (EEPROM_BASIC_START_NUM > LIBCFG_FLASH_SIZE / LIBCFG_FLASH_PAGESIZE)
  #error "EEPROM_BASIC_START_NUM is not correct (must < (Flash Size / Page Size) )!"
#endif

/* Private function prototypes -----------------------------------------------------------------------------*/
#ifndef _ERROR_HANDLER_
#define SetErrId(...)
#endif

/* Private variables ---------------------------------------------------------------------------------------*/
extern __ALIGN4 u8 EEPROM_Buffer[EEPROM_BASIC_LENGTH];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Function init emulated eeprom (flash)
  * @retval none
  ***********************************************************************************************************/
u8 EEPROM_Init(void)
{
  u16 i;
  u16 uLength = EEPROM_BASIC_LENGTH >> 2;
  u32 *pBufferAddr = (u32*) EEPROM_Buffer;

  for (i = 0; i < uLength; i++)
  {
    *pBufferAddr++ = rw(EEPROM_BASIC_START_ADDR + (i << 2));
  }
  return 0;
}

/*********************************************************************************************************//**
  * @brief  Function reads a byte from emulated eeprom (flash)
  * @param  Address : Address to read
  * @retval Data : Data read from eeprom
  ***********************************************************************************************************/
u8 EEPROM_Read(const u32 Address)
{
  u8 Data = 0;
  if (Address < EEPROM_BASIC_LENGTH)
  {
    Data = EEPROM_Buffer[Address];
  }
  else
  {
    SetErrId(API_ERROR_PARAMETER_ERROR);
  }
  return Data;
}

/*********************************************************************************************************//**
  * @brief  Function writes a byte to emulated eeprom (flash)
  * @param  Address : Address to write
  * @param  Data : value to write
  * @retval none
  ***********************************************************************************************************/
void EEPROM_Write(u32 Address, u8 Data)
{
  u16 i;
  u16 uCurrentLength = Address >> 2;
  u16 uLength = EEPROM_BASIC_LENGTH >> 2;
  u8  uBufferData = EEPROM_Buffer[Address];
  u32 *pBufferAddr = (u32*) EEPROM_Buffer;
  FLASH_State FLASHState;

  if (Address < EEPROM_BASIC_LENGTH)
  {
    if (uBufferData == Data)
    {
      return;
    }

    //Update SRAM Buffer Data
    EEPROM_Buffer[Address] = Data;

    if (uBufferData == 0xFF)
    {
      //Write 4 Byte
      u32 *pData = (u32*)((u32)pBufferAddr + (uCurrentLength << 2));
      FLASHState = FLASH_ProgramWordData((u32)(EEPROM_BASIC_START_ADDR + (uCurrentLength << 2)), *pData);

      if (FLASHState != FLASH_COMPLETE)
      {
        SetErrId(API_ERROR_ACCESS_FAILED);
      #if 0  // For Debug
        while(1);
      #endif
      }
    }
    else
    {
      //Clear Flash Page
      FLASHState = FLASH_ErasePage(EEPROM_BASIC_START_ADDR);

      //Write Page Flash
      for (i = 0; i < uLength; i++)
      {
        u32 *pData = (u32*)((u32)pBufferAddr + (i << 2));
        FLASHState = FLASH_ProgramWordData((u32)(EEPROM_BASIC_START_ADDR + (i << 2)), *pData);

        if (FLASHState != FLASH_COMPLETE)
        {
          SetErrId(API_ERROR_ACCESS_FAILED);
        #if 0  // For Debug
          while(1);
        #endif
        }
      }
    }
  }
  else
  {
    SetErrId(API_ERROR_PARAMETER_ERROR);
  }
}

/**
  * @}
  */

/**
  * @}
  */
