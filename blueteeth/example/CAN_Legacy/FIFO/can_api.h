/*********************************************************************************************************//**
 * @file    CAN_Legacy/FIFO/can_api.h
 * @version $Rev:: 8184         $
 * @date    $Date:: 2024-09-24 #$
 * @brief   The header file of can's API.
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
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __CAN_API_H
#define __CAN_API_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include    "usertypedef.h"

/* Settings ------------------------------------------------------------------------------------------------*/
#define CAN_CR_INIT_Msk     CAN_CR_INIT
#define CAN_SR_TXOK_Msk     CAN_FLAG_TXOK
#define CAN_CR_EIE_Msk      CAN_INT_EIE
#define CAN_CR_IE_Msk       CAN_INT_IE
#define CAN_NORMAL_MODE     CAN_MODE_NORMAL

#define MSGOBJ_NUMBER       32
#define CAN_DLC             8
#define CAN_DAT_MSG         0
#define CAN_RMT_MSG         1

#define FIFO_DEPTH          16  /* rx fifo-depth. */
#define DIRn_RECEIVE        0
#define DIRn_TRANSMIT       1
#define IFn_RX              1
#define IFn_TX              0

#define MXTDn               0x80
#define MDIRn               0x40
#define XTDn                0x40
#define DIRn                0x20

/**************************************************************
 * internal used defines
 *************************************************************/
#define CAN_RET_TXOK         64
#define CAN_RET_RXOK_MAX     32
#define CAN_RET_RXOK         1  // 1~32
#define CAN_RET_IDLE         0
#define CAN_RET_BUSOFF_RCY  -1
#define CAN_RET_EWARN       -2
#define CAN_RET_RX_EMPTY    -3

/**************************************************************
 * can bitrate used defines
 *************************************************************/
#define BR_5K                0
#define BR_10K               1
#define BR_20K               2
#define BR_50K               3
#define BR_100K              4
#define BR_125K              5
#define BR_250K              6
#define BR_500K              7
#define BR_800K              8
#define BR_1000K             9

/**************************************************************
 * can message number used defines
 *************************************************************/
#define MSG_NUM1             1
#define MSG_NUM2             2
#define MSG_NUM3             3
#define MSG_NUM4             4
#define MSG_NUM5             5
#define MSG_NUM6             6
#define MSG_NUM7             7
#define MSG_NUM8             8
#define MSG_NUM9             9
#define MSG_NUM10            10
#define MSG_NUM11            11
#define MSG_NUM12            12
#define MSG_NUM13            13
#define MSG_NUM14            14
#define MSG_NUM15            15
#define MSG_NUM16            16
#define MSG_NUM17            17
#define MSG_NUM18            18
#define MSG_NUM19            19
#define MSG_NUM20            20
#define MSG_NUM21            21
#define MSG_NUM22            22
#define MSG_NUM23            23
#define MSG_NUM24            24
#define MSG_NUM25            25
#define MSG_NUM26            26
#define MSG_NUM27            27
#define MSG_NUM28            28
#define MSG_NUM29            29
#define MSG_NUM30            30
#define MSG_NUM31            31
#define MSG_NUM32            32

#define MSG_SIZEn            16

/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef struct
{
  dwformat_uWord arb_id;
  struct
  {
    u8  RTR;
    u8  EXT;
    wformat_uWord   DLC;
  } FMT;
  u8 data[CAN_DLC];
} can_msgTypeDef;

typedef union
{
  /* message fifo paramters */
  u8 arr[FIFO_DEPTH][MSG_SIZEn];
  can_msgTypeDef  msg[FIFO_DEPTH];
} can_msgfifoTypeDef;

typedef struct
{
  /* paramters */
  u8 rptr;
  u8 sptr;
  /* message buffer */
  u8 *buf;
} can_queueTypeDef;

/* Exported variables --------------------------------------------------------------------------------------*/
extern can_msgfifoTypeDef rmsgfifo;
extern can_msgfifoTypeDef tmsgfifo;
extern can_queueTypeDef recvQ;
extern can_queueTypeDef sendQ;

/* Exported functions --------------------------------------------------------------------------------------*/
s8 CANAPI_Receive(HT_CAN_TypeDef *CANx);
void CANAPI_RecvMewData(can_msgTypeDef *M, HT_CAN_TypeDef *CANx);
void CANAPI_SendOut(u8 msgnum, u8 *payload, u8 dlc, HT_CAN_TypeDef *CANx);
void CANAPI_InitTxMsg(u8 msgnum, u8 type_frame, u8 type_id, u32 id, HT_CAN_TypeDef *CANx);
void CANAPI_InitRxMsg(u8 msgnum, u8 type_frame, u8 type_id, u32 id, u32 mask, u8 fifo_dup, HT_CAN_TypeDef *CANx);
void CANAPI_SetModeBitrate(u8 mode, u8 br, HT_CAN_TypeDef *CANx);
void CANAPI_SetInterrupt(u32 int_en, HT_CAN_TypeDef *CANx);
u8 CANAPI_PushToRingFIFO(u8 *dst, u8 *src, u8 q, u8 dup);
u8 CANAPI_PopFromRingFIFO(u8 *dst, u8 *src, u8 q, u8 dup);
u8 CANAPI_Rmemdelta(u8 a, u8 b, u8 dup);

#ifdef __cplusplus
}
#endif

#endif /* __CAN_API_H -------------------------------------------------------------------------------*/
