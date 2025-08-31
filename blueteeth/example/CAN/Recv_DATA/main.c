/*********************************************************************************************************//**
 * @file    CAN/Recv_DATA/main.c
 * @version $Rev:: 8550         $
 * @date    $Date:: 2025-04-14 #$
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
#include "ht32_board_config.h"
#include "ht32_can_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup CAN_Examples CAN
  * @{
  */

/** @addtogroup Recv_DATA
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define CAN_RECV_ID1            (0x540)
#define CAN_RECV_ID2            (0x541)
#define CAN_RECV_ID3            (0x542)

#define CAN_RECV1_FIFO_SIZE     (1)
#define CAN_RECV2_FIFO_SIZE     (1)
#define CAN_RECV3_FIFO_SIZE     (20)

#define CAN_RECV1_BUFFER_SIZE   (CAN_RECV1_FIFO_SIZE * 8)
#define CAN_RECV2_BUFFER_SIZE   (CAN_RECV2_FIFO_SIZE * 8)
#define CAN_RECV3_BUFFER_SIZE   (CAN_RECV3_FIFO_SIZE * 8)

/* Private function prototypes -----------------------------------------------------------------------------*/
void CAN_Configuration(void);
void CAN_MsgInit(void);
void CAN_MsgRx(void);
void CAN_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
CAN_MSG_TypeDef gRx1Msg;
CAN_MSG_TypeDef gRx2Msg;
CAN_MSG_TypeDef gRx3Msg;

u8 gRx1MsgBuffer[CAN_RECV1_BUFFER_SIZE];
u8 gRx2MsgBuffer[CAN_RECV2_BUFFER_SIZE];
u8 gRx3MsgBuffer[CAN_RECV3_BUFFER_SIZE];

bool gbRx1MsgCompareResult;
bool gbRx2MsgCompareResult;
bool gbRx3MsgCompareResult;

u32 gTxSerialNumber;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();
  HT32F_DVB_LEDInit(HT_LED1);

  #if (HTCFG_CAN_CONF_CHECK_ENABLE == 1)
  CAN_Config0_Check();
  #endif

  CAN_Configuration();
  CAN_MsgInit();

  while (1)
  {
    CAN_MsgRx();
    if ((gbRx1MsgCompareResult == TRUE) && (gbRx2MsgCompareResult == TRUE) && (gbRx3MsgCompareResult == TRUE))
    {
      HT32F_DVB_LEDOn(HT_LED1);
    }

    CAN_MainRoutine();
  }
}

/*********************************************************************************************************//**
  * @brief  CAN_MainRoutine
  * @retval None
  ***********************************************************************************************************/
void CAN_MainRoutine(void)
{
  if (CAN_GetFlagStatus(HTCFG_CAN_PORT, CAN_FLAG_BOFF))
  {
    /* Check if the CAN application is in bus-off state. If so, call the CAN_BusOffRecovery function to     */
    /* attempt recovery.                                                                                    */
    CAN_BusOffRecovery(HTCFG_CAN_PORT);
  }
}

/*********************************************************************************************************//**
  * @brief  CAN_Configuration
  * @retval None
  ***********************************************************************************************************/
void CAN_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.AFIO                          = 1;
    CKCUClock.Bit.HTCFG_CAN_IPN                 = 1;
    #if defined(HTCFG_CAN_STB_CONTROL)
    CKCUClock.Bit.HTCFG_CAN_STB_GPIO_CK         = 1;
    #endif
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO as CAN mode                                                                             */
  AFIO_GPxConfig(HTCFG_CAN_TX_GPIO_ID, HTCFG_CAN_TX_AFIO_PIN, AFIO_FUN_CAN);
  AFIO_GPxConfig(HTCFG_CAN_RX_GPIO_ID, HTCFG_CAN_RX_AFIO_PIN, AFIO_FUN_CAN);
  #if defined(HTCFG_CAN_STB_CONTROL)
  AFIO_GPxConfig(HTCFG_CAN_STB_GPIO_ID, HTCFG_CAN_STB_AFIO_PIN, AFIO_FUN_GPIO);
  GPIO_WriteOutBits(HTCFG_CAN_STB_GPIO_PORT, HTCFG_CAN_STB_AFIO_PIN, RESET);
  GPIO_DirectionConfig(HTCFG_CAN_STB_GPIO_PORT, HTCFG_CAN_STB_AFIO_PIN, GPIO_DIR_OUT);
  #endif

  CKCU_SetPeripPrescaler(HTCFG_CAN_CKCU_PCLK, (CKCU_APBCLKPRE_TypeDef)HTCFG_CAN_CF0_CLK_DIV);

  {
   /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    CAN_InitTypeDef CAN_InitStruct;
    CAN_InitStruct.CAN_Mode        = CAN_MODE_NORMAL;
    CAN_InitStruct.CAN_BRPrescaler = CAN_CONF0_PRESCALER;
    CAN_InitStruct.CAN_SJW         = CAN_CONF0_BIT_TIME_SJW;
    CAN_InitStruct.CAN_TSEG0       = CAN_CONF0_BIT_TIME_TSEG0;
    CAN_InitStruct.CAN_TSEG1       = CAN_CONF0_BIT_TIME_TSEG1;
    CAN_InitStruct.CAN_NART        = DISABLE;
    CAN_Init(HTCFG_CAN_PORT, &CAN_InitStruct);
  }
}

/*********************************************************************************************************//**
  * @brief  CAN_MsgInit
  * @retval None
  ***********************************************************************************************************/
void CAN_MsgInit(void)
{
  gRx1Msg.Id        = CAN_RECV_ID1;
  gRx1Msg.IdMask    = 0x1FFFFFFF;
  gRx1Msg.IdType    = CAN_EXT_ID;
  gRx1Msg.FrameType = CAN_DATA_FRAME;
  CAN_SetRxMsg(HTCFG_CAN_PORT, &gRx1Msg, CAN_RECV1_FIFO_SIZE);

  gRx2Msg.Id        = CAN_RECV_ID2;
  gRx2Msg.IdMask    = 0x7FF;
  gRx2Msg.IdType    = CAN_STD_ID;
  gRx2Msg.FrameType = CAN_DATA_FRAME;
  CAN_SetRxMsg(HTCFG_CAN_PORT, &gRx2Msg, CAN_RECV2_FIFO_SIZE);

  gRx3Msg.Id        = CAN_RECV_ID3;
  gRx3Msg.IdMask    = 0x7FF;
  gRx3Msg.IdType    = CAN_STD_ID;
  gRx3Msg.FrameType = CAN_DATA_FRAME;
  CAN_SetRxMsg(HTCFG_CAN_PORT, &gRx3Msg, CAN_RECV3_FIFO_SIZE);
}

/*********************************************************************************************************//**
  * @brief  CAN_MsgRx.
  * @retval None
  ***********************************************************************************************************/
void CAN_MsgRx(void)
{
  u32 i;
  u32 dataLength;
  CAN_RxStatus_TypeDef rx_status;

  /* Receive gRx1Msg Message                                                                                */
  rx_status = CAN_Receive(HTCFG_CAN_PORT, &gRx1Msg, gRx1MsgBuffer, &dataLength);
  if (rx_status == MSG_OVER_RUN)
  {
    printf("ID[%X] rx message over run\r\n", gRx1Msg.Id);
  }
  else if (rx_status == MSG_OBJ_NOT_SET)
  {
    printf("rx message not set  \r\n");
  }
  else if (rx_status == MSG_RX_FINISH)
  {
    printf("\r\nRx(==>), ID 0x%06X, ID Type %d, Frame Type %d, length: %d, Data: ", gRx1Msg.Id,
                                                                                    gRx1Msg.IdType,
                                                                                    gRx1Msg.FrameType,
                                                                                    dataLength);
    for (i = 0; i < dataLength; i++)
    {
      printf("%02X ", gRx1MsgBuffer[i]);
      if (gRx1MsgBuffer[i] != i)
      {
        printf("Comparison failed !!\r\n");
        while (1);
      }
    }
    gbRx1MsgCompareResult = TRUE;
    printf("Finish\r\n");
  }

  /* Receive gRx2Msg Message                                                                                */
  rx_status = CAN_Receive(HTCFG_CAN_PORT, &gRx2Msg, gRx2MsgBuffer, &dataLength);
  if (rx_status  == MSG_OVER_RUN)
  {
    printf("ID[%X] rx message over run\r\n", gRx2Msg.Id);
  }
  else if (rx_status == MSG_OBJ_NOT_SET)
  {
    printf("rx message not set  \r\n");
  }
  else if (rx_status == MSG_RX_FINISH)
  {
    printf("\r\nRx(==>), ID 0x%06X, ID Type %d, Frame Type %d, length: %d, Data: ", gRx2Msg.Id,
                                                                                    gRx2Msg.IdType,
                                                                                    gRx2Msg.FrameType,
                                                                                    dataLength);
    for (i = 0; i < dataLength; i++)
    {
      printf("%02X ", gRx2MsgBuffer[i]);
      if (gRx2MsgBuffer[i] != i)
      {
        printf("Comparison failed !!\r\n");
        while (1);
      }
    }
    gbRx2MsgCompareResult = TRUE;
    printf("Finish\r\n");
  }

  /* Receive gRx3Msg Message                                                                                */
  rx_status = CAN_Receive(HTCFG_CAN_PORT, &gRx3Msg, gRx3MsgBuffer, &dataLength);
  if (rx_status  == MSG_OVER_RUN)
  {
    printf("ID[%X] rx message over run\r\n", gRx3Msg.Id);
  }
  else if (rx_status == MSG_OBJ_NOT_SET)
  {
    printf("rx message not set  \r\n");
  }
  else if (rx_status == MSG_RX_FINISH)
  {
    printf("\r\nRx(==>), ID 0x%06X, ID Type %d, Frame Type %d, length: %d, Data: ", gRx3Msg.Id,
                                                                                    gRx3Msg.IdType,
                                                                                    gRx3Msg.FrameType,
                                                                                    dataLength);
    for (i = 0; i < dataLength; i++)
    {
      printf("%02X ", gRx3MsgBuffer[i]);
      if (gRx3MsgBuffer[i] != i)
      {
        printf("Comparison failed !!\r\n");
        while (1);
      }
    }
    gbRx3MsgCompareResult = TRUE;
    printf("Finish\r\n");
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
