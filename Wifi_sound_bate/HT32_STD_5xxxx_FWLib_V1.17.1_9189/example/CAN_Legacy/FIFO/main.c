/*********************************************************************************************************//**
 * @file    CAN_Legacy/FIFO/main.c
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
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
#include "can_api.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup CAN_Legacy_Examples CAN_Legacy
  * @{
  */

/** @addtogroup FIFO
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
#define CAN_SEND_ID         0x541
#define CAN_RECV_ID         0x540

/* Global variables ----------------------------------------------------------------------------------------*/
u32 gCanTimeout;

/* Private variables ---------------------------------------------------------------------------------------*/
u8 flag;

/* Private function prototypes -----------------------------------------------------------------------------*/
void CKCU_Configuration(void);
void GPIO_Configuration(void);
void CAN_Configuration(void);
void SysTick_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  CKCU_Configuration();               /* System Related configuration                                       */
  GPIO_Configuration();               /* GPIO Related configuration                                         */
  HT32F_DVB_LEDInit(HT_LED1);         /* LED1 configuration                                                 */
  RETARGET_Configuration();           /* Retarget Related configuration                                     */
  printf("\r\n CAN FIFO Demo. System Core Clock %u \r\n", (unsigned int)SystemCoreClock);

  SysTick_Configuration();            /* Timebase 1ms                                                       */

  CAN_Configuration();                /* CAN Related configuration                                          */

  flag = 1;

  HT32F_DVB_LEDOff(HT_LED1);

  while(1)
  {
    can_msgTypeDef rmsg;
    can_msgTypeDef tmsg;
    s32 ret;

    ret = CANAPI_Receive(HT_CAN0);  /* Get CAN Status */

    if(ret == CAN_RET_BUSOFF_RCY)
    {
      /* CANbus at Bus-Off state */
      HT_CAN0->CR &= ~CAN_CR_INIT_Msk;

      /* Bus-Off recovery sequence.128 * 11 consecutive recessive bits.                     `                     */
      /* This example waits for the longest time, BitRate = 5K ==> (1/5K) * 128/11 = 0.282s .     */
      gCanTimeout=282; /* Delay 282ms */
      while(gCanTimeout){}
    }

    if((ret >= CAN_RET_RXOK) && (ret <= CAN_RET_RXOK_MAX))
    {
      /* Received Data */
      u8 n;

      for(n = 0; n < ret; n++)
      {
        int i;
        CANAPI_RecvMewData(&rmsg, HT_CAN0);

        printf("\r\nRx(==>), ID %06d, DLC %02d, EXT %d, RTR %d, Data: ", rmsg.arb_id._u32, rmsg.FMT.DLC._u16, rmsg.FMT.EXT, rmsg.FMT.RTR);
        for(i = 0; i<rmsg.FMT.DLC._u16; i++)
        {
          printf("%02X ", rmsg.data[i]);
        }
        printf("Finish\r\n");
        recvQ.rptr = CANAPI_PushToRingFIFO(recvQ.buf, &rmsg.arb_id.arr[0], recvQ.rptr, FIFO_DEPTH);
      }

      /*  Parsing massage. */
      while(CANAPI_Rmemdelta(recvQ.rptr, recvQ.sptr, FIFO_DEPTH))
      {
        recvQ.sptr = CANAPI_PopFromRingFIFO(&rmsg.arb_id.arr[0], recvQ.buf, recvQ.sptr, FIFO_DEPTH);

        if(rmsg.arb_id._u32 == CAN_RECV_ID)
        {
          sendQ.rptr = CANAPI_PushToRingFIFO(sendQ.buf, &rmsg.arb_id.arr[0], sendQ.rptr, FIFO_DEPTH);
        }
      }
    }

    if(ret == CAN_RET_IDLE)
    {
      /* BUS idle */
      if(flag)
      {
        /* Send a standard frame transmission after power-on, data 0xD0 0x04. */
        int i;
        flag = 0;
        /* Prepare data. */
        tmsg.data[0] = 0xd9;
        tmsg.data[1] = 0x04;
        tmsg.FMT.DLC._u16 = 2;
        CANAPI_SendOut(MSG_NUM17, &tmsg.data[0], tmsg.FMT.DLC._u16, HT_CAN0);
        tmsg.FMT.EXT = 0;
        printf("\r\nTx(<==), ID %06d, DLC %02d, EXT %d, RTR %d, Data: ", tmsg.arb_id._u32, tmsg.FMT.DLC._u16, tmsg.FMT.EXT, tmsg.FMT.RTR);
        for(i = 0; i<tmsg.FMT.DLC._u16; i++)
        {
          printf("%02X ", tmsg.data[i]);
        }

        /* Send message. */
        HT32F_DVB_LEDOn(HT_LED1);
        while(!(HT_CAN0->SR & CAN_SR_TXOK_Msk));

        printf("Finish\r\n");
        /* clear TXOK flag. */
        HT_CAN0->SR &= ~CAN_SR_TXOK_Msk;
        /* Send message OK. */
        HT32F_DVB_LEDOff(HT_LED1);

      }

      if(CANAPI_Rmemdelta(sendQ.rptr, sendQ.sptr, FIFO_DEPTH))
      {
        /* the messages will be transferred because "Send FIFO" is not empty. */
        int i;
        sendQ.sptr = CANAPI_PopFromRingFIFO(&tmsg.arb_id.arr[0], sendQ.buf, sendQ.sptr, FIFO_DEPTH);
        CANAPI_InitTxMsg(MSG_NUM17, CAN_DAT_MSG, CAN_EXT_ID, CAN_SEND_ID, HT_CAN0);
        CANAPI_SendOut(MSG_NUM17, &tmsg.data[0], tmsg.FMT.DLC._u16, HT_CAN0);
        tmsg.FMT.EXT = 1;
        printf("\r\nTx(<==), ID %06d, DLC %02d, EXT %d, RTR %d, Data: ", tmsg.arb_id._u32, tmsg.FMT.DLC._u16, tmsg.FMT.EXT, tmsg.FMT.RTR);
        for(i = 0; i<tmsg.FMT.DLC._u16; i++)
        {
          printf("%02X ", tmsg.data[i]);
        }

        /* Send message. */
        HT32F_DVB_LEDOn(HT_LED1);
        while(!(HT_CAN0->SR & CAN_SR_TXOK_Msk));
        printf("Finish\r\n");
        /* Clear TXOK flag. */
        HT_CAN0->SR &= ~CAN_SR_TXOK_Msk;
        /* Send message OK */
        HT32F_DVB_LEDOff(HT_LED1);
      }
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the CAN.
  * @retval None
  ***********************************************************************************************************/
void CAN_Configuration(void)
{
  CANAPI_SetModeBitrate(CAN_NORMAL_MODE, BR_500K, HT_CAN0);
  CANAPI_SetInterrupt(CAN_CR_EIE_Msk | CAN_CR_IE_Msk, HT_CAN0);

  CANAPI_InitRxMsg(MSG_NUM1,
                  CAN_DAT_MSG,
                  CAN_STD_ID,
                  CAN_RECV_ID,
                  0x1fffffff,
                  FIFO_DEPTH,    /* fifo depth = 16.(MSG_NUM1~MSG_NUM16) */
                  HT_CAN0);

  CANAPI_InitTxMsg(MSG_NUM17,
                  CAN_DAT_MSG,
                  CAN_STD_ID,
                  CAN_SEND_ID,
                  HT_CAN0);

  recvQ.rptr = 0;
  recvQ.sptr = 0;
  recvQ.buf = &rmsgfifo.arr[0][0];

  sendQ.rptr = 0;
  sendQ.sptr = 0;
  sendQ.buf = &tmsgfifo.arr[0][0];
}

/*********************************************************************************************************//**
  * @brief  BFTM Configuration.
  * @retval None
  ***********************************************************************************************************/
void SysTick_Configuration(void)
{
  SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);       /* Default : CK_AHB/8                                 */
  SYSTICK_SetReloadValue(SystemCoreClock / 8 / 1000); /* (CK_AHB/8/1000) = 1ms on chip                      */
  SYSTICK_IntConfig(ENABLE);                          /* Enable SYSTICK Interrupt                           */
  SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
  SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AFIO             = 1;
  CKCUClock.Bit.HTCFG_CAN_IPN    = 1;
  #if defined(HTCFG_CAN_STB_CONTROL)
  CKCUClock.Bit.HTCFG_CAN_STB_GPIO_CK         = 1;
  #endif
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure the GPIO ports.
  * @retval None
  ***********************************************************************************************************/
void GPIO_Configuration(void)
{
  AFIO_GPxConfig(HTCFG_CAN_TX_GPIO_ID, HTCFG_CAN_TX_AFIO_PIN, AFIO_FUN_CAN);
  AFIO_GPxConfig(HTCFG_CAN_RX_GPIO_ID, HTCFG_CAN_RX_AFIO_PIN, AFIO_FUN_CAN);

  #if defined(HTCFG_CAN_STB_CONTROL)
  AFIO_GPxConfig(HTCFG_CAN_STB_GPIO_ID, HTCFG_CAN_STB_AFIO_PIN, AFIO_FUN_GPIO);
  GPIO_WriteOutBits(HTCFG_CAN_STB_GPIO_PORT, HTCFG_CAN_STB_AFIO_PIN, RESET);
  GPIO_DirectionConfig(HTCFG_CAN_STB_GPIO_PORT, HTCFG_CAN_STB_AFIO_PIN, GPIO_DIR_OUT);
  #endif
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
