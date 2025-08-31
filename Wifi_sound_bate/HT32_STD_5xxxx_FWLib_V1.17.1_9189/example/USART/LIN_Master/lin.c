/*********************************************************************************************************//**
 * @file    USART/LIN_Master/lin.c
 * @version $Rev:: 9183         $
 * @date    $Date:: 2025-06-23 #$
 * @brief   The LIN bus related function.
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
#include "ht32_board_config.h"
#include "lin.h"
#include "ht32_time.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup LIN_Master
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
typedef union
{
  struct
  {
    unsigned long B0 :1;
    unsigned long B1 :1;
    unsigned long B2 :1;
    unsigned long B3 :1;
    unsigned long B4 :1;
    unsigned long B5 :1;
    unsigned long B6 :1;
    unsigned long B7 :1;
  } Bit;
  u8 Byte;
} USART_LIN_PID_Byte;

/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
u8 _LIN_CalculatePIDParity(u8 uPID);
ErrStatus _LIN_CheckPID(u8 uPID);
u8 _LIN_GetChecksum(u8 uPID, u8 *pBuffer, u8 uLength, u8 uMode);

/* Private macro -------------------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------------------------------------*/
s8 gLINState = LIN_IDLE;
u8 gLIN_SYNC;
u8 gLIN_PID;

u32 gLINResponse_StartTime;
u32 gLINResponse_Timeout;

uc8  *gLINTx_Ptr;
vu8 gLINTx_Length = 0;

u8  *gLINRx_Ptr;
vu8  gLINRx_Length = 0;

u8  *gLINRx_PtrDefault;
u8   gLINRx_ExpectLength = 0;
u8   gLINRx_CheckSumMode;

LIN_PIDHandler_CallBack_TypeDef gpUserPIDHandler = NULL;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  LIN init.
  * @param pRxBuffer: Default buffer for receive the response.
  * @param pUserPIDHandlerCallBack: User handler of Rx
  * @retval None
  ***********************************************************************************************************/
void LIN_Init(u8 *pRxBuffer, LIN_PIDHandler_CallBack_TypeDef pUserPIDHandlerCallBack)
{
  gLINRx_PtrDefault = pRxBuffer;
  gpUserPIDHandler = pUserPIDHandlerCallBack;
  LIN_ResetState();
}

/*********************************************************************************************************//**
  * @brief  Reset LIN state.
  * @retval None
  ***********************************************************************************************************/
void LIN_ResetState(void)
{
  gLINState = LIN_IDLE;
  gLIN_SYNC = 0;
  gLIN_PID = 0;
  gLINResponse_Timeout = 0;
}

/*********************************************************************************************************//**
 * @brief LIN start frame.
 * @param uPID: Protected Identifier.
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus LIN_StartFrame(u8 uPID)
{
  if (gLINState == LIN_IDLE)
  {
    gLINState = LIN_SEND_BREAK;

    uPID = _LIN_CalculatePIDParity(uPID);

    gLINResponse_StartTime = GET_CNT();
    gLINResponse_Timeout = LIN_MAX_HEADER_TIME;

    #if (LIBCFG_USART_LIN == 1 && LIN_FORCR_UART_MODE == 0)
    HTCFG_UART_PORT->CR |= USART_LINSENDBREAK;
    while ((HTCFG_UART_PORT->CR & USART_LINSENDBREAK) != 0);
    #else
    // To Do, send te break without UxART HW LIN mode
    #endif
    HTCFG_UART_PORT->DR = 0x55;
    #if 1 // UART must turn on since it did not have FIFO
    while ((HTCFG_UART_PORT->SR & USART_FLAG_TXC) == 0){};
    #endif
    HTCFG_UART_PORT->DR = uPID;

    return SUCCESS;
  }

  return ERROR;
}

/*********************************************************************************************************//**
  * @brief  LIN Send Response.
  * @param  uPID:
  * @param  pBuffer: Buffer pointer for Tx data
  * @param  uLength: Length of Tx data
  * @param  uCheckSumMode: LIN_CHECKSUM_CLASSIC, LIN_CHECKSUM_ENHANCED
  * @retval None
  ***********************************************************************************************************/
void LIN_SendResponse(u8 uPID, u8 *pBuffer, u8 uLength, u8 uCheckSumMode)
{
  *(pBuffer + uLength) = _LIN_GetChecksum(_LIN_CalculatePIDParity(uPID), pBuffer, uLength, uCheckSumMode);
  gLINTx_Ptr = pBuffer;
  gLINTx_Length = uLength + 1; // Add 1 for checksum
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_TXDE | USART_INT_TXC, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Set Tx/Rx attributes.
  * @param  uNextState: LIN_TX or LIN_RX
  * @param  pBuffer: Buffer for receive the response. Set as NULL when Tx to skip the data.
  * @param  uExpectRxLength: Expect Rx length
  * @param  uCheckSumMode: LIN_CHECKSUM_CLASSIC, LIN_CHECKSUM_ENHANCED
  * @retval None
  ***********************************************************************************************************/
void LIN_SetTxRxAttributes(u8 uNextState, u8 *pBuffer, u8 uExpectRxLength, u8 uCheckSumMode)
{
  gLINState = uNextState;
  gLINRx_Ptr = pBuffer;
  gLINRx_ExpectLength = uExpectRxLength;
  gLINRx_CheckSumMode = uCheckSumMode;
  gLINRx_Length = 0;
  gLINResponse_Timeout = (u32)LIN_MAX_RESPONSE_TIME(uExpectRxLength);
}

/*********************************************************************************************************//**
  * @brief  Is PID ready.
  * @retval TRUE or FALSE
  ***********************************************************************************************************/
bool LIN_IsPIDReady(void)
{
  return (gLINState == LIN_PID) ? TRUE : FALSE;
}

/*********************************************************************************************************//**
  * @brief  Get PID.
  * @retval gLIN_PID
  ***********************************************************************************************************/
u8 LIN_GetPID(void)
{
  return LIN_GETID(gLIN_PID);
}

/*********************************************************************************************************//**
  * @brief  Check if LIN Frame is finish.
  * @param  pRxInfo: Rx information.
  * @retval LIN_NOTUSE, LIN_PROCESS, LIN_FINISH, LIN_TIMEOUT, LIN_ERROR, LIN_CHECKSUMERROR
  **********************************************************************************************************/
s32 LIN_GetStatus(LIN_RxInfoTypeDef *pRxInfo)
{
  s32 sResult;

  switch (gLINState)
  {
    case LIN_IDLE:
    {
      sResult = LIN_NOTUSE;
      break;
    }
    case LIN_RX_READY:
    {
      pRxInfo->uPID = gLIN_PID;
      pRxInfo->pBuffer = gLINRx_Ptr;
      pRxInfo->uLnegth = gLINRx_Length;
      gLINState = LIN_IDLE;
      gLINResponse_Timeout = 0;
      sResult = LIN_FINISH;
      break;
    }
    case LIN_RX_CHECKSUMERROR:
    {
      pRxInfo->uPID = gLIN_PID;
      pRxInfo->pBuffer = gLINRx_Ptr;
      pRxInfo->uLnegth = gLINRx_Length;
      sResult = LIN_CHECKSUMERROR;
      break;
    }
    case LIN_SYNC_ERROR:
    case LIN_PID_ERROR:
    case LIN_RX_OVERWRITE:
    {
      pRxInfo->uLINState = gLINState;
      sResult = LIN_ERROR;
      break;
    }
    default:
    {
      sResult = LIN_PROCESS;
      break;
    }
  }

  if (gLINResponse_Timeout != 0 && sResult == LIN_PROCESS)
  {
    u32 uDiff = TIME_TICKDIFF(gLINResponse_StartTime, GET_TICK());
    if (TIME_TICK2US(uDiff) > gLINResponse_Timeout)
    {
      return LIN_TIMEOUT;
    }
  }

  return sResult;
}

/*********************************************************************************************************//**
  * @brief  Handler for Break detect.
  * @retval None
  ***********************************************************************************************************/
void LIN_BreakHandler(void)
{
  #if 0
  if (gLINState == LIN_IDLE)
  {
    // Slave mode, detect break but gLINState is not LIN_SEND_BREAK
  }
  #endif

  if (gLINState == LIN_IDLE || gLINState == LIN_SEND_BREAK)
  {
    gLINState = LIN_BREAK_DETECTED;
    gLIN_SYNC = 0;
    gLIN_PID = 0;

    #if 0
    gLINRx_Ptr = gLINRx_PtrDefault;
    #endif
    gLINRx_Length = 0;
    gLINRx_ExpectLength = 0;

    gLINResponse_StartTime = GET_CNT();
    gLINResponse_Timeout = LIN_MAX_HEADER_TIME;
  }
}

/*********************************************************************************************************//**
  * @brief  Handler for Rx.
  * @retval None
  ***********************************************************************************************************/
void LIN_RxHandler(u8 uData)
{
  switch (gLINState)
  {
    case LIN_PID:
    {
      // Received Rx data but LIN_SetTxRxAttributes() is not called (device not care current PID or F/W is too slow), skip all the following rx data
      gLINState = LIN_RX_READY;
      break;
    }
    case LIN_TX_END:
    case LIN_TX:
    case LIN_RX:
    {
      if (gLINRx_Ptr != NULL)
      {
        gLINRx_Ptr[gLINRx_Length] = uData;
      }
      if (gLINRx_Length == gLINRx_ExpectLength)
      {
        gLINState = LIN_RX_READY;
        if (gLINRx_Ptr != NULL)
        {
          u8 Checksum = _LIN_GetChecksum(gLIN_PID, gLINRx_Ptr, gLINRx_Length, gLINRx_CheckSumMode);
          if (gLINRx_Ptr[gLINRx_Length] != Checksum)
          {
            gLINState = LIN_RX_CHECKSUMERROR;
          }
        }
      }
      gLINRx_Length++;
      break;
    }
    case LIN_BREAK_DETECTED:
    {
      gLIN_SYNC = uData;
      if (gLIN_SYNC == 0x55)
      {
        gLINState = LIN_SYNCED;
      }
      else
      {
        gLINState = LIN_SYNC_ERROR;
        // Error handling here or by main super loop
        // ...
      }
      break;
    }
    case LIN_SYNCED:
    {
      gLIN_PID = uData;
      if (_LIN_CheckPID(gLIN_PID) == SUCCESS)
      {
        extern void LIN_PIDHandler(u8 uPID);
        gLINState = LIN_PID;
        gLINResponse_StartTime = GET_TICK();

        if (gpUserPIDHandler != NULL)
        {
          gpUserPIDHandler(LIN_GETID(gLIN_PID));
        }
      }
      else
      {
        #if 0 // Does any process need when PID parity error?
        gLINState = LIN_PID_ERROR;
        // Error handling here or by main super loop
        // ...
        #endif
      }
      break;
    }
    case LIN_IDLE:
    case LIN_SEND_BREAK:
    {
      #if (LIBCFG_USART_LIN == 0 || LIN_FORCR_UART_MODE == 1)
      // UxART mode (SW LIN), received 0x00 means break
      if (uData == 0)
      {
        LIN_BreakHandler();
      }
      #endif
      break;
    }
    case LIN_RX_READY:
    {
      break;
    }
    case LIN_RX_CHECKSUMERROR:
    default:
    {
      gLINState = LIN_RX_OVERWRITE;
      break;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Handler for Tx.
  * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus LIN_TxHandler(void)
{
  if (gLINState == LIN_TX)
  {
    if (gLINTx_Length > 0)
    {
      USART_SendData(HTCFG_UART_PORT, *gLINTx_Ptr++);
      gLINTx_Length--;
      if (gLINTx_Length == 0)
      {
        USART_IntConfig(HTCFG_UART_PORT, USART_INT_TXDE, DISABLE);
        gLINState = LIN_TX_END;
      }
    }
    return SUCCESS;
  }

  return ERROR;
}

/*********************************************************************************************************//**
  * @brief  Handler for Tx finish (TXC).
  * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus LIN_TxFinishHandler(void)
{
  if (gLINState == LIN_TX_END)
  {
    //gLINState = LIN_IDLE;
    return SUCCESS;
  }

  return ERROR;
}

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Calculate PID.
  * @param  uPID: Protected Identifier.
  * @retval Protected Identifier with parity
  ***********************************************************************************************************/
u8 _LIN_CalculatePIDParity(u8 uPID)
{
  USART_LIN_PID_Byte _ID;

  _ID.Byte = uPID;
  _ID.Bit.B6 =  (_ID.Bit.B0 ^ _ID.Bit.B1 ^ _ID.Bit.B2 ^ _ID.Bit.B4);
  _ID.Bit.B7 = !(_ID.Bit.B1 ^ _ID.Bit.B3 ^ _ID.Bit.B4 ^ _ID.Bit.B5);

  return _ID.Byte;
}

/*********************************************************************************************************//**
  * @brief  Check PID.
  * @param  uPID: Protected Identifier.
  * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus _LIN_CheckPID(u8 uPID)
{
  USART_LIN_PID_Byte _ID;
  _ID.Byte = uPID;

  if (_ID.Bit.B6 != (_ID.Bit.B0 ^ _ID.Bit.B1 ^ _ID.Bit.B2 ^ _ID.Bit.B4))
  {
    return ERROR;
  }
  if (_ID.Bit.B7 != (!(_ID.Bit.B1 ^ _ID.Bit.B3 ^ _ID.Bit.B4 ^ _ID.Bit.B5)))
  {
    return ERROR;
  }

  return SUCCESS;
}

/*********************************************************************************************************//**
  * @brief  Get Checksum.
  * @param  uPID:
  * @param  pBuffer: Buffer pointer for data
  * @param  uLength: Length of data
  * @param  uCheckSumMode: LIN_CHECKSUM_CLASSIC, LIN_CHECKSUM_ENHANCED
  * @retval checksum
  ***********************************************************************************************************/
u8 _LIN_GetChecksum(u8 uPID, u8 *pBuffer, u8 uLength, u8 uCheckSumMode)
{
  u16 checksum = 0;
  u32 i;

  if (uCheckSumMode == LIN_CHECKSUM_ENHANCED)
  {
    checksum = uPID;
  }

  for (i = 0; i < uLength; i++)
  {
    checksum += *pBuffer++;
    if (checksum >= 256)
    {
      checksum -= 255;
    }
  }

  return ~checksum;
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
