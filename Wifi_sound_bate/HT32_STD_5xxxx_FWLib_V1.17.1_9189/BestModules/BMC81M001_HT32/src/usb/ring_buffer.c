/*********************************************************************************************************//**
 * @file    ring_buffer.c
 * @version $Rev:: 7681         $
 * @date    $Date:: 2024-04-01 #$
 * @brief   Ring buffer related functions.
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
#include "ring_buffer.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup Common
  * @{
  */

/** @addtogroup RING_BUFFER RING_BUFFER
  * @brief The source file of ring buffer.
  * @{
  */

/* Private macro -------------------------------------------------------------------------------------------*/
#define IS_BUFFER_EMPTY(Read, Write)              (Write == Read)
#define IS_BUFFER_FULL(Read, Write, Size)         ((Write + 1) == Size ? (0 == Read) : ((Write + 1) == Read))

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup RING_BUFFER_Exported_Functions Ring Buffer exported functions
  * @{
  */
/*********************************************************************************************************//**
  * @brief  Buffer initialization.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @param  puMemory: Memory allocate by application
  * @param  uSize: Memory Size. !!!! The available size is (uSize - 1) !!!
  * @retval None
  ***********************************************************************************************************/
void Buffer_Init(Buffer_TypeDef *pBuffer, u8 *puMemory, u32 uSize)
{
  pBuffer->uRead = 0;
  pBuffer->uWrite = 0;
  pBuffer->uSize = uSize;
  pBuffer->puMemory = puMemory;

  return;
}

/*********************************************************************************************************//**
  * @brief  Read byte from buffer.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @param  puData: Pointer of returned data
  * @retval uResult: TRUE for read success, FALSE for no DATA
  ***********************************************************************************************************/
u32 Buffer_ReadByte(Buffer_TypeDef *pBuffer, u8 *puData)
{
  u32 uReadTemp = pBuffer->uRead;

  if (!IS_BUFFER_EMPTY(uReadTemp, pBuffer->uWrite))
  {
    *puData = pBuffer->puMemory[uReadTemp];
    uReadTemp++;

    if (uReadTemp == pBuffer->uSize)
    {
      uReadTemp = 0;
    }

    pBuffer->uRead = uReadTemp;

    return TRUE;
  }

  return FALSE;
}

/*********************************************************************************************************//**
  * @brief  Write byte to buffer.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @param  uData: Data to write
  * @retval uResult: TRUE for write success, FALSE for buffer full
  ***********************************************************************************************************/
u32 Buffer_WriteByte(Buffer_TypeDef *pBuffer, u8 uData)
{
  u32 uWriteTemp = pBuffer->uWrite;
  u32 uSize = pBuffer->uSize;

  if (!IS_BUFFER_FULL(pBuffer->uRead, uWriteTemp, uSize))
  {
    pBuffer->puMemory[uWriteTemp] = uData;
    uWriteTemp++;

    if (uWriteTemp == uSize)
    {
      uWriteTemp = 0;
    }

    pBuffer->uWrite = uWriteTemp;

    return TRUE;
  }

  return FALSE;
}

/*********************************************************************************************************//**
  * @brief  Read buffer.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @param  puData: Pointer of dada buffer for read
  * @param  uLength: Read length
  * @retval uCount: Data length of read operation
  ***********************************************************************************************************/
u32 Buffer_Read(Buffer_TypeDef *pBuffer, u8 *puData, u32 uLength)
{
  u32 uCount;
  u32 uResult;
  for (uCount = 0; uCount < uLength; uCount++)
  {
    uResult = Buffer_ReadByte(pBuffer, (u8 *)(puData + uCount));
    if (!uResult)
    {
      break;
    }
  }

  return uCount;
}

/*********************************************************************************************************//**
  * @brief  Write Buffer.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @param  puData: Pointer of dada buffer for write
  * @param  uLength: Write length
  * @retval uCount: Data length of write operation
  ***********************************************************************************************************/
u32 Buffer_Write(Buffer_TypeDef *pBuffer, u8 *puData, u32 uLength)
{
  u32 uCount = 0;
  u32 uResult;
  for (uCount = 0; uCount < uLength; uCount++)
  {
    uResult = Buffer_WriteByte(pBuffer, *(u8 *)(puData + uCount));
    if (!uResult)
    {
      break;
    }
  }

  return uCount;
}

/*********************************************************************************************************//**
  * @brief  Check if buffer is empty.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @retval TRUE for buffer is empty, FALSE for buffer is not empty
  ***********************************************************************************************************/
u32 Buffer_isEmpty(Buffer_TypeDef *pBuffer)
{
  return(IS_BUFFER_EMPTY(pBuffer->uRead, pBuffer->uWrite));
}

/*********************************************************************************************************//**
  * @brief  Check if buffer is full.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @retval TRUE for buffer is full, FALSE for buffer is not full
  ***********************************************************************************************************/
u32 Buffer_isFull(Buffer_TypeDef *pBuffer)
{
  return(IS_BUFFER_FULL(pBuffer->uRead, pBuffer->uWrite, pBuffer->uSize));
}

/*********************************************************************************************************//**
  * @brief  Get buffer length.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @retval length
  ***********************************************************************************************************/
u32 Buffer_GetLength(Buffer_TypeDef *pBuffer)
{
  u32 uRead = pBuffer->uRead;
  u32 uWrite = pBuffer->uWrite;

  if (uWrite >= uRead)
  {
    return (uWrite - uRead);
  }
  else
  {
    return (pBuffer->uSize - uRead + uWrite);
  }
}

/*********************************************************************************************************//**
  * @brief  Discard Buffer data.
  * @param  pBuffer: Pointer of Buffer_TypeDef
  * @retval None
  ***********************************************************************************************************/
void Buffer_Discard(Buffer_TypeDef *pBuffer)
{
  pBuffer->uRead = pBuffer->uWrite = 0;

  return;
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

/**
  * @}
  */
