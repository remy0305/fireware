/*********************************************************************************************************//**
 * @file    CAN_Legacy/FIFO/can_api.c
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   This file provides multiple can's APIs.
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
#include "can_api.h"
#include "string.h"

/* Global variables ----------------------------------------------------------------------------------------*/
can_msgfifoTypeDef rmsgfifo;
can_msgfifoTypeDef tmsgfifo;
can_queueTypeDef recvQ;
can_queueTypeDef sendQ;

/* fsys=8MHz, sample-potint 75% */
const u8 sBR_8mhz_sp75pa[10][4] = /*  bitrate     time quanta     SamplePoint */
{
  {0x23, 0x3a, 0x01, 0x00},       /*  S0 : 5K         16              75 */
  {0x31, 0x3a, 0x00, 0x00},       /*  S1 : 10K        16              75 */
  {0x18, 0x3a, 0x00, 0x00},       /*  S2 : 20K        16              75 */
  {0x09, 0x3a, 0x00, 0x00},       /*  S3 : 50K        16              75 */
  {0x04, 0x3a, 0x00, 0x00},       /*  S4 : 100K       16              75 */
  {0x03, 0x3a, 0x00, 0x00},       /*  S5 : 125K       16              75 */
  {0x01, 0x3a, 0x00, 0x00},       /*  S6 : 250K       16              75 */
  {0x00, 0x3a, 0x00, 0x00},       /*  S7 : 500K       16              75 */
  {0x00, 0x16, 0x00, 0x00},       /*  S8 : 800K       16              75 */
  {0x00, 0x14, 0x00, 0x00},       /*  S9 : 1000K      16              75 */
};

/* fsys=16MHz, sample-potint 75% */
const u8 sBR_16mhz_sp75pa[10][4] =/*  bitrate     time quanta     SamplePoint */
{
  {0x07, 0x3a, 0x03, 0x00},       /*  S0 : 5K         16              75 */
  {0x23, 0x3a, 0x01, 0x00},       /*  S1 : 10K        16              75 */
  {0x31, 0x3a, 0x00, 0x00},       /*  S2 : 20K        16              75 */
  {0x13, 0x3a, 0x00, 0x00},       /*  S3 : 50K        16              75 */
  {0x09, 0x3a, 0x00, 0x00},       /*  S4 : 100K       16              75 */
  {0x07, 0x3a, 0x00, 0x00},       /*  S5 : 125K       16              75 */
  {0x03, 0x3a, 0x00, 0x00},       /*  S6 : 250K       16              75 */
  {0x01, 0x3a, 0x00, 0x00},       /*  S7 : 500K       16              75 */
  {0x00, 0x4d, 0x00, 0x00},       /*  S8 : 800K       16              75 */
  {0x00, 0x3a, 0x00, 0x00},       /*  S9 : 1000K      16              75 */
};

/* fsys=48MHz, sample-potint 75% */
const u8 sBR_48mhz_sp75pa[10][4] =/*  bitrate     time quanta     SamplePoint */
{
  {0x17, 0x3a, 0x09, 0x00},       /*  S0 : 5K         16              75 */
  {0x2b, 0x3a, 0x04, 0x00},       /*  S1 : 10K        16              75 */
  {0x15, 0x3a, 0x02, 0x00},       /*  S2 : 20K        16              75 */
  {0x3b, 0x3a, 0x00, 0x00},       /*  S3 : 50K        16              75 */
  {0x1d, 0x3a, 0x00, 0x00},       /*  S4 : 100K       16              75 */
  {0x17, 0x3a, 0x00, 0x00},       /*  S5 : 125K       16              75 */
  {0x0b, 0x3a, 0x00, 0x00},       /*  S6 : 250K       16              75 */
  {0x05, 0x3a, 0x00, 0x00},       /*  S7 : 500K       16              75 */
  {0x02, 0x4d, 0x00, 0x00},       /*  S8 : 800K       20              75 */
  {0x02, 0x3a, 0x00, 0x00},       /*  S9 : 1000K      16              75 */
};

/* fsys=60MHz, sample-potint 75% */
const u8 sBR_60mhz_sp75pa[10][4] =/*  bitrate     time quanta     SamplePoint */
{
  {0x2d, 0x3a, 0x0b, 0x00},       /*  S0 : 5K         16              75 */
  {0x36, 0x3a, 0x05, 0x00},       /*  S1 : 10K        16              75 */
  {0x15, 0x4d, 0x02, 0x00},       /*  S2 : 20K        20              75 */
  {0x0a, 0x3a, 0x01, 0x00},       /*  S3 : 50K        16              75 */
  {0x1d, 0x4d, 0x00, 0x00},       /*  S4 : 100K       20              75 */
  {0x1d, 0x3a, 0x00, 0x00},       /*  S5 : 125K       16              75 */
  {0x0e, 0x3a, 0x00, 0x00},       /*  S6 : 250K       16              75 */
  {0x05, 0x4d, 0x00, 0x00},       /*  S7 : 500K       20              75 */
  {0x04, 0x39, 0x00, 0x00},       /*  S8 : 800K       15              75 */
  {0x02, 0x4d, 0x00, 0x00},       /*  S9 : 1000K      20              75 */
};

/* fsys=80MHz, sample-potint 75% */
const u8 sBR_80mhz_sp75pa[10][4] =/*  bitrate     time quanta     SamplePoint */
{
  {0x27, 0x3a, 0x0F, 0x00},       /*  S0 : 5K         16              75 */
  {0x33, 0x3a, 0x07, 0x00},       /*  S1 : 10K        16              75 */
  {0x0F, 0x4d, 0x1F, 0x00},       /*  S2 : 20K        20              75 */
  {0x23, 0x3a, 0x01, 0x00},       /*  S3 : 50K        16              75 */
  {0x27, 0x4d, 0x00, 0x00},       /*  S4 : 100K       20              75 */
  {0x27, 0x3a, 0x00, 0x00},       /*  S5 : 125K       16              75 */
  {0x13, 0x3a, 0x00, 0x00},       /*  S6 : 250K       16              75 */
  {0x07, 0x4d, 0x00, 0x00},       /*  S7 : 500K       20              75 */
  {0x04, 0x4d, 0x00, 0x00},       /*  S8 : 800K       20              75 */
  {0x03, 0x4d, 0x00, 0x00},       /*  S9 : 1000K      20              75 */
};



/* Private function prototypes -----------------------------------------------------------------------------*/
static u32 conv_msk(u8 EXTx, u32 MSKx);
static u32 conv_id(u8 RTRx, u8 EXTx, u32 IDx, u8 IFx);
static void updateIFn_to_msgobj(u8 num, u32 field, u8 IFx, HT_CAN_TypeDef *CANx);
static u32 reverse_conv_id(u8 IFx, u8 *pEXTn, u8 *pRTRn, volatile uint32_t *src);
static void can_set_unused_msg(u8 first, u8 last, HT_CAN_TypeDef *CANx);
static void recv_datamove(u8 *dst, volatile uint32_t *src, u8 len);
static void send_datamove(volatile uint32_t *dst, u8 *src, u8 len);
static u8 check_has_newData(u32 ndata);

/* Global functions ----------------------------------------------------------------------------------------*/
/**********************************************************************************************************//**
  * @brief  Get CAN status.
  * @param  CANx: The pointer to CAN module base address.
  * @retval status : CAN_RET_TXOK         = 64
  *                  CAN_RET_RXOK         = 1~32
  *                  CAN_RET_IDLE         = 0
  *                  CAN_RET_BUSOFF_RCY   = -1
  *                  CAN_RET_EWARN        = -2
  *                  CAN_RET_RX_EMPTY     = -3
  ***********************************************************************************************************/
s8 CANAPI_Receive(HT_CAN_TypeDef *CANx)
{
  u32 intID;
  u32 newDATA;
  u8 num;

  /* read interrupt pointer and status register */
  intID = CANx->IR;

  /** error interrupt.(triggered by BOFF or EWARN bit) **/
  if(intID == 0x8000)
  {
    /* CANbus at Bus-Off state. */
    if(CANx->SR & CAN_FLAG_BOFF)
    {
      return CAN_RET_BUSOFF_RCY;
    }

    /* CANbus at error warning status state. */
    if(CANx->SR & CAN_FLAG_EWARN)
    {
      return CAN_RET_EWARN;
    }
  }
  else
  {
    /** Transmitted or Received Message Successfully. **/
    if(intID >= 0x01 && intID <= 0x20)
    {
      /* Transmitted a Message Successfully. */
      if(CANx->SR & CAN_FLAG_TXOK)
      {
        /* clear TxOK status. */
        CANx->SR &= ~CAN_FLAG_TXOK;

        /* clear interrupt pending. */
        CANx->IF0.CMASK = (CAN_IF_CMASK_CLRINTPND | CAN_IF_CMASK_TXRQSTNEWDAT);
        CANx->IF0.CREQ = intID;
        return CAN_RET_TXOK;
      }
      else
      {
        /* Received a Message Successfully. */
        if(CANx->SR & CAN_FLAG_RXOK)
        {
          /* clear RxOK status. */
          CANx->SR &= ~CAN_FLAG_RXOK;

          newDATA = CANx->NDR1;
          newDATA <<= 16;
          newDATA = newDATA + CANx->NDR0;
          num = check_has_newData(newDATA);

          if(num)
          {
            return CAN_RET_RXOK + (num - 1);
          }
          else
            return CAN_RET_RX_EMPTY;
        }
      }
    }
  }
  return CAN_RET_IDLE;
}

/**********************************************************************************************************//**
  * @brief  Recevie NewData via RX_IFn.---IF1
  * @param  M: Pointer to the message structure.
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
void CANAPI_RecvMewData(can_msgTypeDef *M, HT_CAN_TypeDef *CANx)
{
  u8 n;
  u32 newDATA;

  newDATA = CANx->NDR1;
  newDATA <<= 16;
  newDATA = newDATA + CANx->NDR0;

  for(n = 0; n < 32; n++)
  {
    if(newDATA & 0x00000001)
    {
      /* clear interrupt pending & read message to IF1 registers */
      CANx->IF1.CMASK = (CAN_IF_CMASK_MASK | CAN_IF_CMASK_ARB | CAN_IF_CMASK_CONTROL | 
                         CAN_IF_CMASK_DATAA | CAN_IF_CMASK_DATAB)
                        | (CAN_IF_CMASK_CLRINTPND | CAN_IF_CMASK_TXRQSTNEWDAT);
      CANx->IF1.CREQ = n + 1;

      M->FMT.DLC._u16 = LONIBBLE(CANx->IF1.MCR);
      recv_datamove(M->data, &CANx->IF1.DA0R, M->FMT.DLC._u16);
      M->arb_id._u32 = reverse_conv_id(IFn_RX, &(M->FMT.EXT), &(M->FMT.RTR), &CANx->IF1.ARB0);
      break;
    }
    newDATA >>= 1;
  }
}

/**********************************************************************************************************//**
  * @brief  Send Data via TX_IFn.---IF0
  * @param  msgnum: Specifies the Message object number, from 0 to 31.
  * @param  payload: data.
  * @param  dlc: data length.(0~8 Bytes)
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
void CANAPI_SendOut(u8 msgnum, u8 *payload, u8 dlc, HT_CAN_TypeDef *CANx)
{
  send_datamove(&CANx->IF0.DA0R, payload, CAN_DLC);
  CANx->IF0.MCR = (CAN_IF_MCR_TXIE | CAN_IF_MCR_TXRQST) + dlc;
  CANx->IF0.ARB1 |= CAN_IF_ARB1_MSGVAL;
  CANx->IF0.CMASK = (CAN_IF_CMASK_CONTROL | CAN_IF_CMASK_DATAA | CAN_IF_CMASK_DATAB) |
                     CAN_IF_CMASK_WRRD;
  CANx->IF0.CREQ = msgnum;
}

/**********************************************************************************************************//**
  * @brief  Setting TX Message MASK/ARB/CTRL/DATA Field via TX_IFn(IF0) access.
  * @param  msgnum
  * @param  type_frame
  *         @arg  0, Data frame.
  *         @arg  1, Remote frame.
  * @param  type_id
  *         @arg  0, Standard ID.
  *         @arg  1, Extanded ID.
  * @param  id
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
void CANAPI_InitTxMsg(u8 msgnum, u8 type_frame, u8 type_id, u32 id, HT_CAN_TypeDef *CANx)
{
  dwformat_uWord arb;

  arb._u32 = conv_id(type_frame, type_id, id, DIRn_TRANSMIT);

  CANx->IF0.ARB0 = arb._u16.L;
  CANx->IF0.ARB1 = arb._u16.H;
  updateIFn_to_msgobj(msgnum, CAN_IF_CMASK_ARB, IFn_TX, CANx);
}

/**********************************************************************************************************//**
  * @brief  Setting RX Message MASK/ARB/CTRL/DATA Field via IF1 access.
  * @param  msgnum: Specifies the Message object number, from 0 to 31.
  * @param  type_frame
  *         @arg  0, Data frame.
  *         @arg  1, Remote frame.
  * @param  type_id
  *         @arg  0, Standard ID.
  *         @arg  1, Extanded ID.
  * @param  id
  * @param  mask
  * @param  fifo_dup : rx fifo depth
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
void CANAPI_InitRxMsg(u8 msgnum, u8 type_frame, u8 type_id, u32 id, u32 mask, u8 fifo_dup, HT_CAN_TypeDef *CANx)
{
  u8 n;
  dwformat_uWord msk;
  dwformat_uWord arb;

  msk._u32 = conv_msk(type_id, mask);
  CANx->IF1.MASK0 = msk._u16.L;
  CANx->IF1.MASK1 = msk._u16.H;
  arb._u32 = conv_id(type_frame, type_id, id, DIRn_RECEIVE);

  CANx->IF1.ARB0 = arb._u16.L;
  CANx->IF1.ARB1 = arb._u16.H;

  for(n = 0; n < fifo_dup; n++)
  {
    if(n == fifo_dup - 1)
    {
      CANx->IF1.MCR = CAN_IF_MCR_UMASK | CAN_IF_MCR_RXIE | CAN_IF_MCR_EOB;
    }
    else
      CANx->IF1.MCR = CAN_IF_MCR_UMASK | CAN_IF_MCR_RXIE;

    updateIFn_to_msgobj(msgnum + n, CAN_IF_CMASK_MASK | CAN_IF_CMASK_ARB | CAN_IF_CMASK_CONTROL, IFn_RX, CANx);
  }
}

/**********************************************************************************************************//**
  * @brief  Setting Mode & BitRate.
  * @param  mode
  *         @arg  0x00, NORMAL
  *         @arg  0x10, LBACK
  *         @arg  0x08, SILENT
  *         @arg  0x04, BASIC
  * @param  br
  *         @arg  0, BR_5K
  *         @arg  1, BR_10K
  *         @arg  2, BR_20K
  *         @arg  3, BR_50K
  *         @arg  4, BR_100K
  *         @arg  5, BR_125K
  *         @arg  6, BR_250K
  *         @arg  7, BR_500K
  *         @arg  8, BR_800K
  *         @arg  9, BR_1000K
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
void CANAPI_SetModeBitrate(u8 mode, u8 br, HT_CAN_TypeDef *CANx)
{
  /** Set Mode. **/
  if(mode == CAN_MODE_LBACK
          || mode == CAN_MODE_SILENT
          || mode == CAN_MODE_BASIC)
  {
    /* Enter TEST Mode. */
    CANx->CR |= CAN_CR_TEST;
    CANx->TR = (CANx->TR & (CAN_TEST_RX | CAN_MODE_TX_RECESSIVE)) | mode;
  }
  else
  {
    /* Exit TEST Mode. */
    CANx->TR &= (CAN_TEST_RX | CAN_MODE_TX_RECESSIVE);
    CANx->CR &= ~CAN_CR_TEST;
  }

  /** Set BitRate. **/
  if(br <= 10)
  {
    /* Enter Initial Mode. */
    CANx->CR |= (CAN_CR_CCE | CAN_CR_INIT);

    #if (LIBCFG_MAX_SPEED == 60000000)
    {
      CANx->BTR = sBR_60mhz_sp75pa[br][1];
      CANx->BTR = CANx->BTR << 8;
      CANx->BTR += sBR_60mhz_sp75pa[br][0];
      CANx->BRPER = sBR_60mhz_sp75pa[br][2];
    }
    #elif (LIBCFG_MAX_SPEED == 80000000)
    {
      CANx->BTR = sBR_80mhz_sp75pa[br][1];
      CANx->BTR = CANx->BTR << 8;
      CANx->BTR += sBR_80mhz_sp75pa[br][0];
      CANx->BRPER = sBR_80mhz_sp75pa[br][2];
    }
    #endif

    /** All Message Object Set Not Valid. **/
    can_set_unused_msg(1, MSGOBJ_NUMBER, CANx);

    /* Exit Initial Mode. */
    CANx->CR &= ~(CAN_CR_CCE | CAN_CR_INIT);
  }
}

/**********************************************************************************************************//**
  * @brief  Setting CAN interrupt.
  * @param  int_en
  *         This parameter can be one of the following values:
  *         @arg CAN_CR_IE : Module interrupt enable.
  *         @arg CAN_CR_SIE: Status change interrupt enable.
  *         @arg CAN_CR_EIE: Error interrupt enable.
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
void CANAPI_SetInterrupt(u32 int_en, HT_CAN_TypeDef *CANx)
{
  /* Set Error/Status Change/Module Interrupt. */
  CANx->CR = (CANx->CR & (CAN_CR_TEST | CAN_CR_CCE | CAN_CR_DAR)) | int_en;
}

/**********************************************************************************************************//**
  * @brief  push data to ring fifo.
  * @param  dst : destination
  * @param  src : source
  * @param  q   : ring fifo pointer
  * @param  dup : fifo depth
  * @retval ring fifo pointer.
  ***********************************************************************************************************/
u8 CANAPI_PushToRingFIFO(u8 *dst, u8 *src, u8 q, u8 dup)
{
  memcpy(dst + q * MSG_SIZEn, src, MSG_SIZEn);
  q++;

  if(q == dup)
  {
    q = 0x00;
  }
  return q;
}

/**********************************************************************************************************//**
  * @brief  pop data from ring fifo.
  * @param  dst : destination
  * @param  src : source
  * @param  q   : ring fifo pointer
  * @param  dup : fifo depth
  * @retval ring fifo pointer.
  ***********************************************************************************************************/
u8 CANAPI_PopFromRingFIFO(u8 *dst, u8 *src, u8 q, u8 dup)
{
  memcpy(dst, src + q * MSG_SIZEn, MSG_SIZEn);
  q++;

  if(q == dup)
  {
    q = 0x00;
  }
  return q;
}

/**********************************************************************************************************//**
  * @brief  check ring buffer delta
  * @param  a
  * @param  b
  * @param  dup
  * @retval delta : number of delta.
  ***********************************************************************************************************/
u8 CANAPI_Rmemdelta(u8 a, u8 b, u8 dup)
{
  u8 delta;

  delta = a - b;

  if(delta & 0x80)
  {
    delta = delta + dup;
  }
  return delta;
}


/* Private functions ---------------------------------------------------------------------------------------*/
/**********************************************************************************************************//**
  * @brief  Convert Mask.
  * @param  EXTx
  *         @arg 0, Standard ID.
  *         @arg 1, Extanded ID.
  * @param  MSKx
  * @retval msk
  ***********************************************************************************************************/
static u32 conv_msk(u8 EXTx, u32 MSKx)
{
  dwformat_uWord msk;
  msk._u32 = MSKx;

  if(EXTx)
  {
    /* Extended Mask.(bit28..bit18). */
    msk._u32 &= 0x1FFFFFFF;
    msk.arr[3] |= (MDIRn | MXTDn);
  }
  else
  {
    /* Standard Mask.(bit28..bit18). */
    msk._u32 = (msk._u32 & 0x000007FF) << 18;
    msk.arr[3] |= MDIRn;
  }
  return msk._u32;
}

/**********************************************************************************************************//**
  * @brief  Convert ID.
  * @param  RTRx
  *         @arg 0, Data frame.
  *         @arg 1, Remote frame.
  * @param  EXTx
  *         @arg 0, Standard ID.
  *         @arg 1, Extanded ID.
  * @param  IDx
  * @param  IFx
  *         @arg 0, Receive.
  *         @arg 1, Transmit.
  * @retval arb
  ***********************************************************************************************************/
static u32 conv_id(u8 RTRx, u8 EXTx, u32 IDx, u8 IFx)
{
  dwformat_uWord arb;
  arb._u32 = IDx;

  if(EXTx)
  {
    /** Extended Mask.(bit28..bit18). **/
    arb._u32 &= 0x1FFFFFFF;

    /* XTDn = 1, Extended ID. */
    arb.arr[3] |= XTDn;
  }
  else
  {
    /** Standard Mask.(bit28..bit18). **/
    arb._u32 = (arb._u32 & 0x000007FF) << 18;

    /* XTDn = 0, Standard ID. */
    arb.arr[3] &= ~(DIRn | XTDn);
  }

  if(IFx)
  {
    if(!RTRx)
    {
      /* DIRn = 1, Direction = transmit data frame. */
      arb.arr[3] |= DIRn;
    }
    /* DIRn = 0, Direction = transmit remote frame. */

  }
  else
  {
    if(RTRx)
    {
      /* DIRn = 1, Direction = remote. */
      arb.arr[3] |= DIRn;
    }
  }
  return arb._u32;
}

/**********************************************************************************************************//**
  * @brief  Update Message field via IF0/IF1 access.
  * @param  num :  message number.
  * @param  field : ARB/CONTROL/DATAA/DATAB field.
  * @param  IFx
  *         @arg 0, TX_IFn. ---(IF1)
  *         @arg 1, RX_IFn. ---(IF2)
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
static void updateIFn_to_msgobj(u8 num, u32 field, u8 IFx, HT_CAN_TypeDef *CANx)
{
  if(IFx)
  {
    CANx->IF1.ARB1 |= CAN_IF_ARB1_MSGVAL;
    CANx->IF1.CMASK = (field | CAN_IF_CMASK_WRRD);
    CANx->IF1.CREQ = num;
  }
  else
  {
    CANx->IF0.ARB1 |= CAN_IF_ARB1_MSGVAL;
    CANx->IF0.CMASK = (field | CAN_IF_CMASK_WRRD);
    CANx->IF0.CREQ = num;
  }
}

/**********************************************************************************************************//**
  * @brief  Reverse Convert ID.
  * @param  IFx
  *         @arg 0, TX_IFn. ---(IF1)
  *         @arg 1, RX_IFn. ---(IF2)
  * @param  pEXTn
  * @param  pRTRn
  * @param  src : id pointer.
  * @retval arb
  ***********************************************************************************************************/
static u32 reverse_conv_id(u8 IFx, u8 *pEXTn, u8 *pRTRn, volatile uint32_t *src)
{
  dwformat_uWord arb;

  arb._u32 = *(src + 1);
  arb._u32 = (arb._u32 << 16) + *(src);

  if(IFx)
  {
    if(arb.arr[3] & DIRn)
    {
      *(pRTRn) = CAN_RMT_MSG;
    }
    else
      *(pRTRn) = CAN_DAT_MSG;
  }

  if(arb.arr[3] & XTDn)
  {
    /** Extended Mask.(bit28..bit18). **/
    arb._u32 &= 0x1FFFFFFF;
    *(pEXTn) = CAN_EXT_ID;
  }
  else
  {
    /** Standard Mask.(bit28..bit18). **/
    arb._u32 = (arb._u32 & 0x1FFFFFFF) >> 18;
    *(pEXTn) = CAN_STD_ID;
  }
  return arb._u32;
}

/**********************************************************************************************************//**
  * @brief  Set Message Object is ignored by the Message Handler.
  * @param  first
  *         @arg Start Message Object number.(value= 1..32).
  * @param  last
  *         @arg End Message Object number.(value= 1..32,must >= Start Message Object number).
  * @param  CANx: The pointer to CAN module base address.
  * @retval None
  ***********************************************************************************************************/
static void can_set_unused_msg(u8 first, u8 last, HT_CAN_TypeDef *CANx)
{
  u8 n;

  for(n = first; n <= last; n++)
  {
    CANx->IF0.ARB1 &= (~CAN_IF_ARB1_MSGVAL);
    CANx->IF0.CREQ = n;
    while((CANx->IF0.CREQ) & CAN_FLAG_IF_BUSY);
  }
}

/**********************************************************************************************************//**
  * @brief  Read receive data from RX_IFn(IF1) register.
  * @param  dst : destination
  * @param  src : source
  * @param  len : length
  * @retval None
  ***********************************************************************************************************/
static void recv_datamove(u8 *dst, volatile uint32_t *src, u8 len)
{
  u8 i;

  for(i = 0; i < len; i++)
  {
    if(i & 0x01)
    {
      *(dst + i) = DWBYTE1(*(src + (i / 2)));
    }
    else
      *(dst + i) = DWBYTE0(*(src + (i / 2)));
  }
}

/**********************************************************************************************************//**
  * @brief  Write send data to TX_IFn(IF0) register.
  * @param  dst : destination
  * @param  src : source
  * @param  len : length
  * @retval None
  ***********************************************************************************************************/
static void send_datamove(volatile uint32_t *dst, u8 *src, u8 len)
{
  u8 i;

  for(i = 0; i < len; i++)
  {
    if(i & 0x01)
    {
      *(dst + i / 2) += (*(src + i)) << 8;
    }
    else
      *(dst + i / 2) = *(src + i);
  }
}

/**********************************************************************************************************//**
  * @brief  Check has newdata in message RAM ?
  * @param  ndata : NewData Registers value.
  * @retval m : number of newdata
  ***********************************************************************************************************/
static u8 check_has_newData(u32 ndata)
{
  u8 n, m;
  m = 0;

  for(n = 0; n < 32; n++)
  {
    if(ndata & 0x00000001)
    {
      m++;
    }
    ndata >>= 1;
  }
  return m;
}
