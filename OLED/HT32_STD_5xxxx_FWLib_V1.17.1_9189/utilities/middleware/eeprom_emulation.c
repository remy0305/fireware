/*********************************************************************************************************//**
 * @file    eeprom_emulation.c
 * @version $Rev:: 1064         $
 * @date    $Date:: 2024-01-19 #$
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
#include "eeprom_emulation.h"

/** @addtogroup EEPROM_Emulation_Examples EEPROM_Emulation
  * @{
  */

/** @addtogroup EEPROM_Emulation
  * @{
  */

/* Private constants ---------------------------------------------------------------------------------------*/
#define EEPROM_EMU_ERASED             (0xFFFF)
#define EEPROM_EMU_TRANSFER           (0xCCCC)
#define EEPROM_EMU_ACTIVE             (0x0000)

#define EEPROM_EMU_READ_PAGE          (0)
#define EEPROM_EMU_WRITE_PAGE         (1)

#if (EEPROM_EMU_LENGTH <= 0)
  #error "EEPROM_EMU_LENGTH is not correct (must >= 1)!"
#endif

#if (EEPROM_EMU_LENGTH > (LIBCFG_FLASH_PAGESIZE / 4 - 2))
  #error "EEPROM_EMU_LENGTH is not correct (must < (Page Size / 4 -2) )!"
#endif

#if (EEPROM_EMU_START_NUM <= 1)
  #error "EEPROM_EMU_START_NUM is not correct (must >= 2)!"
#endif

#if (EEPROM_EMU_START_NUM > (LIBCFG_FLASH_SIZE / LIBCFG_FLASH_PAGESIZE))
  #error "EEPROM_EMU_START_NUM is not correct (must < (Flash Size / Page Size) )!"
#endif

/* Global variables ----------------------------------------------------------------------------------------*/
#if (EEPROM_EMU_SEQUENTIAL_ADDR == 0)
extern u16 EEPROM_VarAddrTab[EEPROM_EMU_LENGTH];
#endif

/* Private variables ---------------------------------------------------------------------------------------*/
u32 guActiveAddress;
u8 guActivePage;

/* Private function prototypes -----------------------------------------------------------------------------*/
static EEPROM_EMU_State EEPROM_Format(void);
static EEPROM_EMU_State EEPROM_FindActivePage(u8 Operation);
static EEPROM_EMU_State EEPROM_FindActiveAddr(void);
static EEPROM_EMU_State EEPROM_WriteActivePage(u16 DataAddr, u16 Data);
static EEPROM_EMU_State EEPROM_TransferPage(void);

/* Private macro -------------------------------------------------------------------------------------------*/
#if (EEPROM_EMU_SEQUENTIAL_ADDR == 0)
#define ADDR_MAP(i)    (EEPROM_VarAddrTab[i])
#else
#define ADDR_MAP(i)    (i)
#endif

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  EEPROM init
  * @retval EEPROM_EMU_OPERATION_OK, EEPROM_EMU_OPERATION_FAIL, EEPROM_EMU_FLASH_ERROR
  ***********************************************************************************************************/
EEPROM_EMU_State EEPROM_Init(void)
{
  FLASH_State FlashStatus;
  EEPROM_EMU_State EepromStatus;
  u16 Page0Status = rhw(EEPROM_EMU_PAGE0_BASE_ADDR);
  u16 Page1Status = rhw(EEPROM_EMU_PAGE1_BASE_ADDR);

  switch (Page0Status)
  {
    case EEPROM_EMU_ERASED:
      if (Page1Status == EEPROM_EMU_ACTIVE)
      {
        /* erase page0                                                                                      */
        FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE0_BASE_ADDR);

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }
      }
      else if (Page1Status == EEPROM_EMU_TRANSFER)
      {
        /* erase page0                                                                                      */
        FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE0_BASE_ADDR);

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }

        /* set page1 active                                                                                 */
        FlashStatus = FLASH_ProgramWordData(EEPROM_EMU_PAGE1_BASE_ADDR, EEPROM_EMU_ACTIVE);

        #if defined(USE_HT32F42366_76_86)
        /* Disable and Enable Cache to insure the Flash read is corrct                                      */
        FLASH_CacheCmd(DISABLE);
        FLASH_CacheCmd(ENABLE);
        #endif

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }
      }
      else
      {
        /* format EEPROM                                                                                    */
        EepromStatus = EEPROM_Format();

        if (EepromStatus != EEPROM_EMU_OPERATION_OK)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }
      }
      break;

    case EEPROM_EMU_TRANSFER:
      if (Page1Status == EEPROM_EMU_ERASED)
      {
        /* erase page1                                                                                      */
        FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE1_BASE_ADDR);

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }

        /* set page0 active                                                                                 */
        FlashStatus = FLASH_ProgramWordData(EEPROM_EMU_PAGE0_BASE_ADDR, EEPROM_EMU_ACTIVE);

        #if defined(USE_HT32F42366_76_86)
        /* Disable and Enable Cache to insure the Flash read is corrct                                      */
        FLASH_CacheCmd(DISABLE);
        FLASH_CacheCmd(ENABLE);
        #endif

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }
      }
      else if (Page1Status == EEPROM_EMU_ACTIVE)
      {
        /* erase page0                                                                                      */
        FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE0_BASE_ADDR);

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }

        /* redo the transfer                                                                                */
        EepromStatus = EEPROM_TransferPage();

        if (EepromStatus != EEPROM_EMU_OPERATION_OK)
        {
          return EepromStatus;
        }
      }
      else
      {
        /* format EEPROM                                                                                    */
        EepromStatus = EEPROM_Format();

        if (EepromStatus != EEPROM_EMU_OPERATION_OK)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }
      }
      break;

    case EEPROM_EMU_ACTIVE:
      if (Page1Status == EEPROM_EMU_ERASED)
      {
        /* erase page1                                                                                      */
        FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE1_BASE_ADDR);

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }
      }
      else if (Page1Status == EEPROM_EMU_TRANSFER)
      {
        /* erase page1                                                                                      */
        FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE1_BASE_ADDR);

        if (FlashStatus != FLASH_COMPLETE)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }

        /* redo the transfer                                                                                */
        EepromStatus = EEPROM_TransferPage();

        if (EepromStatus != EEPROM_EMU_OPERATION_OK)
        {
          return EepromStatus;
        }
      }
      else
      {
        /* format EEPROM                                                                                    */
        EepromStatus = EEPROM_Format();

        if (EepromStatus != EEPROM_EMU_OPERATION_OK)
        {
          return EEPROM_EMU_FLASH_ERROR;
        }
      }
      break;

    default:
      /* format EEPROM                                                                                      */
      EepromStatus = EEPROM_Format();

      if (EepromStatus != EEPROM_EMU_OPERATION_OK)
      {
        return EEPROM_EMU_FLASH_ERROR;
      }
      break;
  }

  guActivePage = EEPROM_FindActivePage(EEPROM_EMU_WRITE_PAGE);
  EepromStatus = EEPROM_FindActiveAddr();

  return EepromStatus;
}

/*********************************************************************************************************//**
  * @brief  Read data from EEPROM
  * @para   DataAddr: data address
  * @para   Data: pointer of data buffer
  * @retval EEPROM_EMU_OPERATION_OK, EEPROM_EMU_NO_ACTIVE_PAGE, EEPROM_EMU_DATA_NOT_FOUND
  ***********************************************************************************************************/
EEPROM_EMU_State EEPROM_Read(u16 DataAddr, u16 *Data)
{
  EEPROM_EMU_State ActivePage;
  u32 StopAddr, CompareAddr;

  /* get active page                                                                                        */
  ActivePage = EEPROM_FindActivePage(EEPROM_EMU_READ_PAGE);

  if (ActivePage == EEPROM_EMU_NO_ACTIVE_PAGE)
  {
    return EEPROM_EMU_NO_ACTIVE_PAGE;
  }

  /* search for latest data                                                                                 */
  StopAddr = EEPROM_EMU_START_ADDR + ((u32)ActivePage * EEPROM_EMU_PAGE_SIZE + 4);           // skip page status field
  CompareAddr = EEPROM_EMU_START_ADDR + ((u32)(1 + ActivePage) * EEPROM_EMU_PAGE_SIZE - 2);  // start from page end

  while (CompareAddr > StopAddr)
  {
    if (rhw(CompareAddr) == DataAddr)
    {
      *Data = rhw(CompareAddr - 2);

      return EEPROM_EMU_OPERATION_OK;
    }
    else
    {
      CompareAddr -= 4;
    }
  }

  return EEPROM_EMU_DATA_NOT_FOUND;
}

/*********************************************************************************************************//**
  * @brief Write data to EEPROM
  * @retval EEPROM_EMU_OPERATION_OK, EEPROM_EMU_NO_ACTIVE_PAGE, EEPROM_EMU_FLASH_ERROR
  ***********************************************************************************************************/
EEPROM_EMU_State EEPROM_Write(u16 DataAddr, u16 Data)
{
  EEPROM_EMU_State EepromStatus;

  EepromStatus = EEPROM_WriteActivePage(DataAddr, Data);

  /* check page full                                                                                        */
  if (EepromStatus == EEPROM_EMU_PAGE_FULL)
  {
    EepromStatus = EEPROM_TransferPage();
  }
  else if (EepromStatus == EEPROM_EMU_OPERATION_FAIL)
  {
    EepromStatus = EEPROM_TransferPage();

    if (EepromStatus != EEPROM_EMU_OPERATION_OK)
    {
      return EepromStatus;
    }

    EepromStatus = EEPROM_WriteActivePage(DataAddr, Data);
  }

  return EepromStatus;
}

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Erase page0, page1 and set page0 active
  * @retval EEPROM_EMU_OPERATION_OK, EEPROM_EMU_FLASH_ERROR
  ***********************************************************************************************************/
static EEPROM_EMU_State EEPROM_Format(void)
{
  FLASH_State FlashStatus;

  /* erase page0                                                                                            */
  FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE0_BASE_ADDR);

  if (FlashStatus != FLASH_COMPLETE)
  {
    return EEPROM_EMU_FLASH_ERROR;
  }

  /* erase page1                                                                                            */
  FlashStatus = FLASH_ErasePage(EEPROM_EMU_PAGE1_BASE_ADDR);

  if (FlashStatus != FLASH_COMPLETE)
  {
    return EEPROM_EMU_FLASH_ERROR;
  }

  /* set page0 active                                                                                       */
  FlashStatus = FLASH_ProgramWordData(EEPROM_EMU_PAGE0_BASE_ADDR, EEPROM_EMU_ACTIVE);

  #if defined(USE_HT32F42366_76_86)
  /* Disable and Enable Cache to insure the Flash read is corrct                                            */
  FLASH_CacheCmd(DISABLE);
  FLASH_CacheCmd(ENABLE);
  #endif

  if (FlashStatus != FLASH_COMPLETE)
  {
    return EEPROM_EMU_FLASH_ERROR;
  }

  return EEPROM_EMU_OPERATION_OK;
}

/*********************************************************************************************************//**
  * @brief Find active page
  * @retval EEPROM_EMU_PAGE0_ACTIVE, EEPROM_EMU_PAGE1_ACTIVE, EEPROM_EMU_NO_ACTIVE_PAGE
  ***********************************************************************************************************/
static EEPROM_EMU_State EEPROM_FindActivePage(u8 Operation)
{
  u16 Page0Status = rhw(EEPROM_EMU_PAGE0_BASE_ADDR);
  u16 Page1Status = rhw(EEPROM_EMU_PAGE1_BASE_ADDR);

  switch (Operation)
  {
    case EEPROM_EMU_WRITE_PAGE:
      if (Page1Status == EEPROM_EMU_ACTIVE)
      {
        if (Page0Status == EEPROM_EMU_TRANSFER)
        {
          return EEPROM_EMU_PAGE0_ACTIVE;
        }
        else
        {
          return EEPROM_EMU_PAGE1_ACTIVE;
        }
      }
      else if (Page0Status == EEPROM_EMU_ACTIVE)
      {
        if (Page1Status == EEPROM_EMU_TRANSFER)
        {
          return EEPROM_EMU_PAGE1_ACTIVE;
        }
        else
        {
          return EEPROM_EMU_PAGE0_ACTIVE;
        }
      }
      else
      {
        return EEPROM_EMU_NO_ACTIVE_PAGE;
      }

    case EEPROM_EMU_READ_PAGE:
      if (Page0Status == EEPROM_EMU_ACTIVE)
      {
        return EEPROM_EMU_PAGE0_ACTIVE;
      }
      else if (Page1Status == EEPROM_EMU_ACTIVE)
      {
        return EEPROM_EMU_PAGE1_ACTIVE;
      }
      else
      {
        return EEPROM_EMU_NO_ACTIVE_PAGE;
      }

    default:
      return EEPROM_EMU_PAGE0_ACTIVE;
  }
}

/*********************************************************************************************************//**
  * @brief Find active write address
  * @retval EEPROM_EMU_OPERATION_OK, EEPROM_EMU_OPERATION_FAIL
  ***********************************************************************************************************/
static EEPROM_EMU_State EEPROM_FindActiveAddr(void)
{
  u32 StopAddr, CompareAddr;

  if (guActivePage == EEPROM_EMU_NO_ACTIVE_PAGE)
  {
    return EEPROM_EMU_NO_ACTIVE_PAGE;
  }

  /* search for lst empty location                                                                          */
  StopAddr = EEPROM_EMU_START_ADDR + ((u32)(1 + guActivePage) * EEPROM_EMU_PAGE_SIZE);   // page end address
  CompareAddr = EEPROM_EMU_START_ADDR + ((u32)guActivePage * EEPROM_EMU_PAGE_SIZE + 4);  // start from page head

  while (CompareAddr < StopAddr)
  {
    if (rw(CompareAddr) == 0xFFFFFFFF)
    {
      guActiveAddress = CompareAddr;

      return EEPROM_EMU_OPERATION_OK;
    }
    else
    {
      CompareAddr += 4;
    }
  }

  return EEPROM_EMU_OPERATION_FAIL;
}

/*********************************************************************************************************//**
  * @brief Write data into active page
  * @retval EEPROM_EMU_OPERATION_OK, 
            EEPROM_EMU_NO_ACTIVE_PAGE, EEPROM_EMU_FLASH_ERROR, EEPROM_EMU_PAGE_FULL
  ***********************************************************************************************************/
static EEPROM_EMU_State EEPROM_WriteActivePage(u16 DataAddr, u16 Data)
{
  FLASH_State FlashStatus;
  u32 StopAddr;

  if (guActivePage == EEPROM_EMU_NO_ACTIVE_PAGE)
  {
    return EEPROM_EMU_NO_ACTIVE_PAGE;
  }

  /* search for lst empty location                                                                          */
  StopAddr = EEPROM_EMU_START_ADDR + ((u32)(1 + guActivePage) * EEPROM_EMU_PAGE_SIZE);   // page end address

  FlashStatus = FLASH_ProgramWordData(guActiveAddress, ((u32)(DataAddr << 16) | Data));

  #if defined(USE_HT32F42366_76_86)
  /* Disable and Enable Cache to insure the Flash read is corrct                                            */
  FLASH_CacheCmd(DISABLE);
  FLASH_CacheCmd(ENABLE);
  #endif

  if (FlashStatus != FLASH_COMPLETE)
  {
    return EEPROM_EMU_FLASH_ERROR;
  }

  if (guActiveAddress == (StopAddr - 4))
  {
    return EEPROM_EMU_PAGE_FULL;
  }

  guActiveAddress += 4;

  return EEPROM_EMU_OPERATION_OK;
}

/*********************************************************************************************************//**
  * @brief
  * @retval EEPROM_EMU_OPERATION_OK, EEPROM_EMU_NO_ACTIVE_PAGE, EEPROM_EMU_FLASH_ERROR
  ***********************************************************************************************************/
static EEPROM_EMU_State EEPROM_TransferPage(void)
{
  FLASH_State FlashStatus;
  EEPROM_EMU_State EepromStatus;
  u32 NewPage, OldPage, i;
  u16 VarData;

  /* get NewPage & OldPage                                                                                  */
  EepromStatus = EEPROM_FindActivePage(EEPROM_EMU_READ_PAGE);

  if (EepromStatus == EEPROM_EMU_PAGE1_ACTIVE)
  {
    NewPage = EEPROM_EMU_PAGE0_BASE_ADDR;
    OldPage = EEPROM_EMU_PAGE1_BASE_ADDR;
    guActivePage = EEPROM_EMU_PAGE0_ACTIVE;
  }
  else if (EepromStatus == EEPROM_EMU_PAGE0_ACTIVE)
  {
    NewPage = EEPROM_EMU_PAGE1_BASE_ADDR;
    OldPage = EEPROM_EMU_PAGE0_BASE_ADDR;
    guActivePage = EEPROM_EMU_PAGE1_ACTIVE;
  }
  else
  {
    return EEPROM_EMU_NO_ACTIVE_PAGE;
  }

  /* set NewPage state as EEPROM_EMU_TRANSFER                                                               */
  FlashStatus = FLASH_ProgramWordData(NewPage, EEPROM_EMU_TRANSFER);

  #if defined(USE_HT32F42366_76_86)
  /* Disable and Enable Cache to insure the Flash read is corrct                                            */
  FLASH_CacheCmd(DISABLE);
  FLASH_CacheCmd(ENABLE);
  #endif

  if (FlashStatus != FLASH_COMPLETE)
  {
    return EEPROM_EMU_FLASH_ERROR;
  }

  guActiveAddress = EEPROM_EMU_START_ADDR + ((u32)guActivePage * EEPROM_EMU_PAGE_SIZE + 4);  // start from page head

  /* transfer data                                                                                          */
  for (i = 0; i < EEPROM_EMU_LENGTH; i++)
  {
    /* write other variables                                                                                */
    EepromStatus = EEPROM_Read(ADDR_MAP(i), &VarData);

    if (EepromStatus != EEPROM_EMU_DATA_NOT_FOUND)
    {
      EepromStatus = EEPROM_WriteActivePage(ADDR_MAP(i), VarData);

      if (EepromStatus != EEPROM_EMU_OPERATION_OK)
      {
        return EepromStatus;
      }
    }
  }

  /* erase OldPage                                                                                          */
  FlashStatus = FLASH_ErasePage(OldPage);

  if (FlashStatus != FLASH_COMPLETE)
  {
    return EEPROM_EMU_FLASH_ERROR;
  }

  /* set NewPage state as EEPROM_EMU_ACTIVE                                                                 */
  FlashStatus = FLASH_ProgramWordData(NewPage, EEPROM_EMU_ACTIVE);

  #if defined(USE_HT32F42366_76_86)
  /* Disable and Enable Cache to insure the Flash read is corrct                                            */
  FLASH_CacheCmd(DISABLE);
  FLASH_CacheCmd(ENABLE);
  #endif

  if (FlashStatus != FLASH_COMPLETE)
  {
    return EEPROM_EMU_FLASH_ERROR;
  }

  return EEPROM_EMU_OPERATION_OK;
}

/**
  * @}
  */

/**
  * @}
  */
