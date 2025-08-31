/*********************************************************************************************************//**
 * @file    CAN/Send_DATA/main.c
 * @version $Rev:: 8489         $
 * @date    $Date:: 2025-03-19 #$
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

/** @addtogroup Send_DATA
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define CAN_SEND_ID1            (0x540)
#define CAN_SEND_ID2            (0x541)
#define CAN_SEND_ID3            (0x542)

/* Private function prototypes -----------------------------------------------------------------------------*/
void CAN_Configuration(void);
void CAN_MsgTx(void);
void CAN_MainRoutine(void);

/* Global variables ----------------------------------------------------------------------------------------*/
CAN_MSG_TypeDef gTx1Msg;
CAN_MSG_TypeDef gTx2Msg;
CAN_MSG_TypeDef gTx3Msg;

u8 gTxMsgData[8];

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
  CAN_MsgTx();

  HT32F_DVB_LEDOn(HT_LED1);

  while (1)
  {
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
  * @brief  CAN_MsgTx
  * @retval None
  ***********************************************************************************************************/
void CAN_MsgTx(void)
{
  u32 i, j;
  gTx1Msg.Id        = CAN_SEND_ID1;
  gTx1Msg.FrameType = CAN_DATA_FRAME;
  gTx1Msg.IdType    = CAN_EXT_ID;
  for (i = 0; i < 8; i++)
  {
    gTxMsgData[i] = i;
  }
  CAN_Transmit(HTCFG_CAN_PORT, &gTx1Msg, gTxMsgData, 8);
  while (CAN_TransmitStatus(HTCFG_CAN_PORT, &gTx1Msg) == 0);  /* Waiting tx Msg idle                        */


  gTx2Msg.Id        = CAN_SEND_ID2;
  gTx2Msg.FrameType = CAN_DATA_FRAME;
  gTx2Msg.IdType    = CAN_STD_ID;
  for (i = 0; i < 8; i++)
  {
    gTxMsgData[i] = i;
  }
  CAN_Transmit(HTCFG_CAN_PORT, &gTx2Msg, gTxMsgData, 8);
  while (CAN_TransmitStatus(HTCFG_CAN_PORT, &gTx2Msg) == 0);  /* Waiting tx Msg idle                        */


  for (i = 0; i < 20; i++)
  {
    for (j = 0; j < 8; j++)
    {
      gTxMsgData[j] = j + i * 8;
    }
    gTx3Msg.Id        = CAN_SEND_ID3;
    gTx3Msg.FrameType = CAN_DATA_FRAME;
    gTx3Msg.IdType    = CAN_STD_ID;
    CAN_Transmit(HTCFG_CAN_PORT, &gTx3Msg, gTxMsgData, 8);
    while (CAN_TransmitStatus(HTCFG_CAN_PORT, &gTx3Msg) == 0);  /* Waiting tx Msg idle                      */
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
