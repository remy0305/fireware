/*********************************************************************************************************//**
 * @file    i2c_master.c
 * @version $Rev:: 1478         $
 * @date    $Date:: 2025-04-01 #$
 * @brief   The I2C Master (interrupt mode with buffer).
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
#include "i2c_master.h"


/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup I2C I2C
  * @{
  */

/** @addtogroup I2C_Master I2C Master
  * @{
  */


/* Private types -------------------------------------------------------------------------------------------*/
/**
 * @brief I2C Master state variables
 */
typedef struct
{
  HT_I2C_TypeDef *pI2Cx;
  u32 uTxIndex;
  u32 uTxLength;
  u8 *puTxBuffer;

  u32 uRxIndex;
  u32 uRxLength;
  u8 *puRxBuffer;

  u32 uSlaveAddress;
  I2CMaster_CMD_Enum Command;
  u32 uI2CReadWrite;
  vu32 IsBusy;
  vu32 uIsNACK;
  vu32 uIsBusError;
  vu32 uIsHardwareTimeout;
  vu32 uStart;
  vs32 sTimerCount;
  vs32 sDynamicOnOffI2C;
} I2CMaster_StateTypeDef;

/* Private constants ---------------------------------------------------------------------------------------*/
#ifdef HTCFG_I2CM_CH0
#define _SCL0_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M0_SCL_GPIO_PORT)
#define _SCL0_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M0_SCL_GPIO_PIN)
#define _SDA0_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M0_SDA_GPIO_PORT)
#define _SDA0_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M0_SDA_GPIO_PIN)
#define _I2C_CH0                 STRCAT2(HT_,       HTCFG_I2CM_CH0)  /* I2C channel                         */
#define _I2C_INT0                STRCAT2(HTCFG_I2CM_CH0, _IRQn)      /* I2C interrupt channel of NVIC       */
  #if I2C_MASTER_INITIAL_BUS
  #define _SCL0_GPIO_CLK         STRCAT2(P,          HTCFG_M0_SCL_GPIO_PORT)
  #define _SCL0_GPIO             STRCAT2(HT_GPIO,    HTCFG_M0_SCL_GPIO_PORT)
  #endif
#endif

#ifdef HTCFG_I2CM_CH1
#define _SCL1_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M1_SCL_GPIO_PORT)
#define _SCL1_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M1_SCL_GPIO_PIN)
#define _SDA1_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M1_SDA_GPIO_PORT)
#define _SDA1_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M1_SDA_GPIO_PIN)
#define _I2C_CH1                 STRCAT2(HT_, HTCFG_I2CM_CH1)       /* I2C channel                          */
#define _I2C_INT1                STRCAT2(HTCFG_I2CM_CH1, _IRQn)     /* I2C interrupt channel of NVIC        */
  #if I2C_MASTER_INITIAL_BUS
  #define _SCL1_GPIO_CLK         STRCAT2(P,          HTCFG_M1_SCL_GPIO_PORT)
  #define _SCL1_GPIO             STRCAT2(HT_GPIO,    HTCFG_M1_SCL_GPIO_PORT)
  #endif
#endif

#ifdef HTCFG_I2CM_CH2
#define _SCL2_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M2_SCL_GPIO_PORT)
#define _SCL2_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M2_SCL_GPIO_PIN)
#define _SDA2_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M2_SDA_GPIO_PORT)
#define _SDA2_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M2_SDA_GPIO_PIN)
#define _I2C_CH2                 STRCAT2(HT_, HTCFG_I2CM_CH2)       /* I2C channel                          */
#define _I2C_INT2                STRCAT2(HTCFG_I2CM_CH2, _IRQn)     /* I2C interrupt channel of NVIC        */
  #if I2C_MASTER_INITIAL_BUS
  #define _SCL2_GPIO_CLK         STRCAT2(P,          HTCFG_M2_SCL_GPIO_PORT)
  #define _SCL2_GPIO             STRCAT2(HT_GPIO,    HTCFG_M2_SCL_GPIO_PORT)
  #endif
#endif

#ifdef HTCFG_I2CM_CH3
#define _SCL3_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M3_SCL_GPIO_PORT)
#define _SCL3_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M3_SCL_GPIO_PIN)
#define _SDA3_GPIO_ID            STRCAT2(GPIO_P,    HTCFG_M3_SDA_GPIO_PORT)
#define _SDA3_AFIO_PIN           STRCAT2(AFIO_PIN_, HTCFG_M3_SDA_GPIO_PIN)
#define _I2C_CH3                 STRCAT2(HT_, HTCFG_I2CM_CH3)       /* I2C channel                          */
#define _I2C_INT3                STRCAT2(HTCFG_I2CM_CH3, _IRQn)     /* I2C interrupt channel of NVIC        */
  #if I2C_MASTER_INITIAL_BUS
  #define _SCL3_GPIO_CLK         STRCAT2(P,          HTCFG_M3_SCL_GPIO_PORT)
  #define _SCL3_GPIO             STRCAT2(HT_GPIO,    HTCFG_M3_SCL_GPIO_PORT)
  #endif
#endif

#define I2C_MASTER_RECEIVED_TXNACK    ((u32)0x003A0200)
#define I2C_MASTER_RECEIVED_RXNACK    ((u32)0x00180200)

/* Private function prototypes -----------------------------------------------------------------------------*/
I2CMaster_Status_Enum _I2CMaster_DynamicTimeout(u32 CH);

/* Private macro -------------------------------------------------------------------------------------------*/
#define __DBG_Printf(...)

#if (I2C_MASTER_DEBUG_MODE == 1)
  #undef __DBG_Printf
  #define __DBG_Printf printf
  #warning "================================ Debug Mode Warning ===================================="
  #warning " Debug mode has been enable which degrade the performance.                              "
  #warning " After all debug operation is finished, please remember to turn off debug mode.         "
  #warning "========================================================================================"
#endif

/* Private variables ---------------------------------------------------------------------------------------*/
static I2CMaster_StateTypeDef gI2CMasterState[I2C_MASTER_SUPPORT_CH];

#if FREERTOS_I2C
SemaphoreHandle_t Semphr[I2C_MASTER_SUPPORT_CH];
StaticSemaphore_t Semphr_Buffer[I2C_MASTER_SUPPORT_CH];
SemaphoreHandle_t Mutex[I2C_MASTER_SUPPORT_CH];
StaticSemaphore_t Mutex_Buffer[I2C_MASTER_SUPPORT_CH];
u32 Transfer_Result[I2C_MASTER_SUPPORT_CH];
#endif

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief Initial I2C Master.
 * @param CH: I2C Channel
 * @param uMasterAddress
 * @param uClockSpeed
 * @retval None
 ************************************************************************************************************/
void I2CMaster_Init(u32 CH, u32 uMasterAddress, u32 uClockSpeed)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  I2C_InitTypeDef  I2C_InitStructure;
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  I2CMaster_StateTypeDef *pI2CMasterState = &gI2CMasterState[CH];
  CKCUClock.Bit.AFIO       = 1;

  #ifdef HTCFG_I2CM_CH0
  if (CH == I2C_MASTER_CH0)
  {
    gI2CMasterState[I2C_MASTER_CH0].pI2Cx = _I2C_CH0;
    /* Enable I2C & AFIO APB clock                                                                          */
    CKCUClock.Bit.HTCFG_I2CM_CH0 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Send eight clocks                                                                                    */
    #if I2C_MASTER_INITIAL_BUS
    {
      volatile int i = 0;
      volatile int tm = 0;
      CKCUClock.Bit._SCL0_GPIO_CLK = 1;
      CKCU_PeripClockConfig(CKCUClock, ENABLE);
      AFIO_GPxConfig(_SCL0_GPIO_ID, _SCL0_AFIO_PIN, AFIO_FUN_GPIO);
      GPIO_SetOutBits(_SCL0_GPIO, _SCL0_AFIO_PIN);
      GPIO_DirectionConfig(_SCL0_GPIO, _SCL0_AFIO_PIN, GPIO_DIR_OUT);
      for (; i < 8; i++)
      {
        GPIO_ClearOutBits(_SCL0_GPIO, _SCL0_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
        GPIO_SetOutBits(_SCL0_GPIO, _SCL0_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
      }
    }
    #endif

    /* Configure AFIO as I2C mode                                                                           */
    AFIO_GPxConfig(_SCL0_GPIO_ID, _SCL0_AFIO_PIN, AFIO_FUN_I2C);
    AFIO_GPxConfig(_SDA0_GPIO_ID, _SDA0_AFIO_PIN, AFIO_FUN_I2C);

    NVIC_EnableIRQ(_I2C_INT0);
  }
  #endif

  #ifdef HTCFG_I2CM_CH1
  if (CH == I2C_MASTER_CH1)
  {
    gI2CMasterState[I2C_MASTER_CH1].pI2Cx = _I2C_CH1;
    CKCUClock.Bit.HTCFG_I2CM_CH1 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    #if I2C_MASTER_INITIAL_BUS
    {
      volatile int i = 0;
      volatile int tm = 0;
      CKCUClock.Bit._SCL1_GPIO_CLK = 1;
      CKCU_PeripClockConfig(CKCUClock, ENABLE);
      AFIO_GPxConfig(_SCL1_GPIO_ID, _SCL1_AFIO_PIN, AFIO_FUN_GPIO);
      GPIO_SetOutBits(_SCL1_GPIO, _SCL1_AFIO_PIN);
      GPIO_DirectionConfig(_SCL1_GPIO, _SCL1_AFIO_PIN, GPIO_DIR_OUT);
      for (; i < 8; i++)
      {
        GPIO_ClearOutBits(_SCL1_GPIO, _SCL1_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
        GPIO_SetOutBits(_SCL1_GPIO, _SCL1_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
      }
    }
    #endif

    AFIO_GPxConfig(_SCL1_GPIO_ID, _SCL1_AFIO_PIN, AFIO_FUN_I2C);
    AFIO_GPxConfig(_SDA1_GPIO_ID, _SDA1_AFIO_PIN, AFIO_FUN_I2C);

    NVIC_EnableIRQ(_I2C_INT1);
  }
  #endif

  #ifdef HTCFG_I2CM_CH2
  if (CH == I2C_MASTER_CH2)
  {
    gI2CMasterState[I2C_MASTER_CH2].pI2Cx = _I2C_CH2;
    CKCUClock.Bit.HTCFG_I2CM_CH2 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    #if I2C_MASTER_INITIAL_BUS
    {
      volatile int i = 0;
      volatile int tm = 0;
      CKCUClock.Bit._SCL2_GPIO_CLK = 1;
      CKCU_PeripClockConfig(CKCUClock, ENABLE);
      AFIO_GPxConfig(_SCL2_GPIO_ID, _SCL2_AFIO_PIN, AFIO_FUN_GPIO);
      GPIO_SetOutBits(_SCL2_GPIO, _SCL2_AFIO_PIN);
      GPIO_DirectionConfig(_SCL2_GPIO, _SCL2_AFIO_PIN, GPIO_DIR_OUT);
      for (; i < 8; i++)
      {
        GPIO_ClearOutBits(_SCL2_GPIO, _SCL2_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
        GPIO_SetOutBits(_SCL2_GPIO, _SCL2_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
      }
    }
    #endif

    AFIO_GPxConfig(_SCL2_GPIO_ID, _SCL2_AFIO_PIN, AFIO_FUN_I2C);
    AFIO_GPxConfig(_SDA2_GPIO_ID, _SDA2_AFIO_PIN, AFIO_FUN_I2C);

    NVIC_EnableIRQ(_I2C_INT2);
  }
  #endif

  #ifdef HTCFG_I2CM_CH3
  if (CH == I2C_MASTER_CH3)
  {
    gI2CMasterState[I2C_MASTER_CH3].pI2Cx = _I2C_CH3;
    CKCUClock.Bit.HTCFG_I2CM_CH3 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    #if I2C_MASTER_INITIAL_BUS
    {
      volatile int i = 0;
      volatile int tm = 0;
      CKCUClock.Bit._SCL3_GPIO_CLK = 1;
      CKCU_PeripClockConfig(CKCUClock, ENABLE);
      AFIO_GPxConfig(_SCL3_GPIO_ID, _SCL3_AFIO_PIN, AFIO_FUN_GPIO);
      GPIO_SetOutBits(_SCL3_GPIO, _SCL3_AFIO_PIN);
      GPIO_DirectionConfig(_SCL3_GPIO, _SCL3_AFIO_PIN, GPIO_DIR_OUT);
      for (; i < 8; i++)
      {
        GPIO_ClearOutBits(_SCL3_GPIO, _SCL3_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
        GPIO_SetOutBits(_SCL3_GPIO, _SCL3_AFIO_PIN);
        for (tm = 0; tm < 2000; tm++)
        __NOP();
      }
    }
    #endif


    AFIO_GPxConfig(_SCL3_GPIO_ID, _SCL3_AFIO_PIN, AFIO_FUN_I2C);
    AFIO_GPxConfig(_SDA3_GPIO_ID, _SDA3_AFIO_PIN, AFIO_FUN_I2C);

    NVIC_EnableIRQ(_I2C_INT3);
  }
  #endif

  /* I2C configuration                                                                                      */
  I2C_InitStructure.I2C_GeneralCall = DISABLE;
  I2C_InitStructure.I2C_AddressingMode = I2C_ADDRESSING_7BIT;
  I2C_InitStructure.I2C_Acknowledge = DISABLE;
  I2C_InitStructure.I2C_OwnAddress = uMasterAddress;
  I2C_InitStructure.I2C_Speed = uClockSpeed;
  I2C_InitStructure.I2C_SpeedOffset = SystemCoreClock / 8000000;
  I2C_Init(pI2CMasterState->pI2Cx, &I2C_InitStructure);

  #if I2C_MASTER_HW_TIMEOUT_MODE
  /*Seting TimeOut Counter                                                                                  */
  I2C_SetTimeOutPrescaler(pI2CMasterState->pI2Cx, I2C_MASTER_HW_TIMEOUT_DIV << 16);
  I2C_SetTimeOutValue(pI2CMasterState->pI2Cx, I2C_MASTER_HW_TIMEOUT_BASE);

  /* Enable I2C                                                                                             */
  I2C_TimeOutCmd(pI2CMasterState->pI2Cx, ENABLE);
  I2C_IntConfig(pI2CMasterState->pI2Cx, I2C_INT_TOUT, ENABLE);
  #endif

  #if (LIBCFG_I2C_NO_ARBLOS == 0)
  /* Enable I2C interrupts                                                                                  */
  I2C_IntConfig(pI2CMasterState->pI2Cx, I2C_INT_ARBLOS | I2C_INT_BUSERR | I2C_INT_STA | I2C_INT_ADRS | I2C_INT_RXNACK | I2C_INT_RXDNE, ENABLE);
  #else
  /* Enable I2C interrupts                                                                                  */
  I2C_IntConfig(pI2CMasterState->pI2Cx, I2C_INT_BUSERR | I2C_INT_STA | I2C_INT_ADRS | I2C_INT_RXNACK | I2C_INT_RXDNE, ENABLE);
  #endif

  I2C_CombFilterCmd(pI2CMasterState->pI2Cx, ENABLE);
  I2C_SequentialFilterConfig(pI2CMasterState->pI2Cx, SEQ_FILTER_2_PCLK);
}

/*********************************************************************************************************//**
 * @brief I2C Write.
 * @param CH: I2C Channel
 * @param pI2CMaster:
 * @retval None
 ************************************************************************************************************/
void I2CMaster_Write(u32 CH, I2CMaster_Typedef *pI2CMaster)
{
  pI2CMaster->Command = I2C_MASTER_CMD_WRITE;
  I2CMaster_Start(CH, pI2CMaster);
}

/*********************************************************************************************************//**
 * @brief I2C Read.
 * @param CH: I2C Channel
 * @param pI2CMaster:
 * @retval None
 ************************************************************************************************************/
void I2CMaster_Read(u32 CH, I2CMaster_Typedef *pI2CMaster)
{
  pI2CMaster->Command = I2C_MASTER_CMD_READ;
  I2CMaster_Start(CH, pI2CMaster);
}

/*********************************************************************************************************//**
 * @brief I2C Write Read.
 * @param CH: I2C Channel
 * @param pI2CMaster:
 * @retval None
 ************************************************************************************************************/
void I2CMaster_WriteRead(u32 CH, I2CMaster_Typedef *pI2CMaster)
{
  pI2CMaster->Command = I2C_MASTER_CMD_WRITEREAD;
  I2CMaster_Start(CH, pI2CMaster);
}

/*********************************************************************************************************//**
 * @brief I2C Write Stop Read.
 * @param CH: I2C Channel
 * @param pI2CMaster:
 * @retval None
 ************************************************************************************************************/
void I2CMaster_WriteStopRead(u32 CH, I2CMaster_Typedef *pI2CMaster)
{
  pI2CMaster->Command = I2C_MASTER_CMD_WRITESTOPREAD;
  I2CMaster_Start(CH, pI2CMaster);
}

/*********************************************************************************************************//**
 * @brief Start Read or Write of I2C buffer.
 * @param CH: I2C Channel
 * @param pI2CMaster: Pointer of I2CMaster_InitTypedef
 * @retval None
  ***********************************************************************************************************/
void I2CMaster_Start(u32 CH, I2CMaster_Typedef *pI2CMaster)
{
  I2CMaster_StateTypeDef *pI2CMasterState = &gI2CMasterState[CH];

  pI2CMasterState->uTxIndex = 0;
  pI2CMasterState->uTxLength = pI2CMaster->Tx.uLength;
  pI2CMasterState->puTxBuffer = pI2CMaster->Tx.puBuffer;

  pI2CMasterState->uRxIndex = 0;
  pI2CMasterState->uRxLength = pI2CMaster->Rx.uLength;
  pI2CMasterState->puRxBuffer = pI2CMaster->Rx.puBuffer;

  pI2CMasterState->uSlaveAddress = pI2CMaster->uSlaveAddress;
  pI2CMasterState->Command = pI2CMaster->Command;

  pI2CMasterState->IsBusy = TRUE;
  pI2CMasterState->uIsNACK = FALSE;
  pI2CMasterState->uIsBusError = FALSE;
  pI2CMasterState->uIsHardwareTimeout = FALSE;

  #if (I2C_MASTER_SW_TIMEOUT_MODE != 0)
  pI2CMasterState->sTimerCount = TRANSFER_TIMER(pI2CMaster->uTimeout_us);
  if (pI2CMasterState->sTimerCount <= 0)
  {
    while(1);   //Please check uTimeout_us need more than I2C_MASTER_SW_TIMEOUT_BASE.
  }
  #endif

  /* this flag avoided I2C busbusy when Pull-up was disabled.                                               */
  pI2CMasterState->sDynamicOnOffI2C = (u32)pI2CMaster->isDynamicOnOff_I2C;

  I2C_Cmd(pI2CMasterState->pI2Cx, ENABLE);

  #if (I2C_MASTER_SW_TIMEOUT_MODE == 2)
  pI2CMasterState->uStart = I2CMASTER_GETTICK();
  #endif

  while (I2C_GetFlagStatus(pI2CMasterState->pI2Cx, I2C_FLAG_BUSBUSY) == SET)
  {
    #if (I2C_MASTER_SW_TIMEOUT_MODE == 2)
    u32 uCurrent = I2CMASTER_GETTICK();
    pI2CMasterState->sTimerCount -= DIFF_TICK(pI2CMasterState->uStart,uCurrent);
    pI2CMasterState->uStart = uCurrent;
    #endif

    #if (I2C_MASTER_SW_TIMEOUT_MODE != 0)
    if (pI2CMasterState->sTimerCount <= 0)
    {
      return;
    }
    #endif
  }

  I2C_ClearFlag(pI2CMasterState->pI2Cx, I2C_FLAG_RXNACK);
  I2C_IntConfig(pI2CMasterState->pI2Cx, I2C_INT_RXNACK, ENABLE);

  if (pI2CMaster->Command == I2C_MASTER_CMD_WRITE ||
      pI2CMaster->Command == I2C_MASTER_CMD_WRITEREAD ||
      pI2CMaster->Command == I2C_MASTER_CMD_WRITESTOPREAD)
  {
    I2C_IntConfig(pI2CMasterState->pI2Cx, I2C_INT_TXDE, ENABLE);
    pI2CMasterState->uI2CReadWrite = I2C_MASTER_WRITE;
  }
  else
  {
    pI2CMasterState->uI2CReadWrite = I2C_MASTER_READ;
  }

  I2C_TargetAddressConfig(pI2CMasterState->pI2Cx, pI2CMasterState->uSlaveAddress, pI2CMasterState->uI2CReadWrite);

  return;
}

/*********************************************************************************************************//**
 * @brief Get I2C buffer status.
 * @param CH: I2C Channel
 * @retval Result: I2C_MASTER_FINISH, I2C_MASTER_HW_TIMEOUT or I2C_MASTER_SW_TIMEOUT
 ************************************************************************************************************/
I2CMaster_Status_Enum I2CMaster_GetStatus(u32 CH)
{
  I2CMaster_StateTypeDef *pI2CMasterState = &gI2CMasterState[CH];
  I2CMaster_Status_Enum Result = I2C_MASTER_GOING;
  #if (I2C_MASTER_NACK_AUTO_RETRY == 1)
  vu32 i;
  #endif

  #if (I2C_MASTER_SW_TIMEOUT_MODE == 2)
  u32 uCurrent;
  uCurrent = I2CMASTER_GETTICK();
  pI2CMasterState->sTimerCount -= DIFF_TICK(pI2CMasterState->uStart,uCurrent);
  pI2CMasterState->uStart = uCurrent;
  #endif

  if (pI2CMasterState->uIsBusError == TRUE)
  {
    return I2C_MASTER_BUSERR;
  }

  if (pI2CMasterState->uIsHardwareTimeout == TRUE)
  {
    return I2C_MASTER_HW_TIMEOUT;
  }

  if (pI2CMasterState->IsBusy == FALSE)
  {
    Result = I2C_MASTER_FINISH;
  }
  #if (I2C_MASTER_SW_TIMEOUT_MODE != 0)
  else if (pI2CMasterState->sTimerCount <= 0)
  {
    pI2CMasterState->IsBusy = FALSE;
    Result = I2C_MASTER_SW_TIMEOUT;

    I2C_IntConfig(pI2CMasterState->pI2Cx, I2C_INT_RXNACK, DISABLE);
    I2C_ClearFlag(pI2CMasterState->pI2Cx, I2C_FLAG_RXNACK);

    I2C_GenerateSTOP(pI2CMasterState->pI2Cx);
  }
  #endif
  else if (pI2CMasterState->uIsNACK == TRUE)
  {
    pI2CMasterState->uIsNACK = FALSE;

    #if (I2C_MASTER_NACK_AUTO_RETRY == 0)
    Result = I2C_MASTER_NACK;
    #else
    /* Release I2C bus for other master by adding a delay                                                   */
    for (i = 0; i < 500; i++);

    /* Re-Write Slave address for start Tx or Rx (re-try when Slave not ack)                                */
    I2C_TargetAddressConfig(pI2CMasterState->pI2Cx, pI2CMasterState->uSlaveAddress, pI2CMasterState->uI2CReadWrite);
    #endif
  }

  return Result;
}

/*********************************************************************************************************//**
 * @brief Get I2C Rx index.
 * @param CH: I2C Channel
 * @retval None
 ************************************************************************************************************/
u32 I2CMaster_GetRxIndex(u32 CH)
{
  I2CMaster_StateTypeDef *pI2CMasterState = &gI2CMasterState[CH];
  return pI2CMasterState->uRxIndex;
}

/*********************************************************************************************************//**
 * @brief Update I2C Rx length.
 * @param CH: I2C Channel
 * @retval None
 ************************************************************************************************************/
void I2CMaster_UpdateRxLength(u32 CH, u32 uLength)
{
  I2CMaster_StateTypeDef *pI2CMasterState = &gI2CMasterState[CH];
  pI2CMasterState->uRxLength = uLength;
  return;
}

#if defined(I2C0_IRQ_HANDLER) || defined(I2C1_IRQ_HANDLER) || defined(I2C2_IRQ_HANDLER) || defined(I2C3_IRQ_HANDLER)
#if defined(HT_I2C0) && defined(I2C0_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief This function handles I2C interrupt.
 * @retval None
 ************************************************************************************************************/
void I2C0_IRQHandler(void)
{
  I2C0_IRQ_HANDLER();
}
#endif
#if defined(HT_I2C1) && defined(I2C1_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief This function handles I2C interrupt.
 * @retval None
 ************************************************************************************************************/
void I2C1_IRQHandler(void)
{
  I2C1_IRQ_HANDLER();
}
#endif
#if defined(HT_I2C2) && defined(I2C2_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief This function handles I2C interrupt.
 * @retval None
 ************************************************************************************************************/
void I2C2_IRQHandler(void)
{
  I2C2_IRQ_HANDLER();
}
#endif
#if defined(HT_I2C3) && defined(I2C3_IRQ_HANDLER)
/*********************************************************************************************************//**
 * @brief This function handles I2C interrupt.
 * @retval None
 ************************************************************************************************************/
void I2C3_IRQHandler(void)
{
  I2C3_IRQ_HANDLER();
}
#endif
#else
#ifdef HTCFG_I2CM_CH0
/*********************************************************************************************************//**
 * @brief This function handles I2C interrupt.
 * @retval None
 ************************************************************************************************************/
void I2CM_CH0_IRQHandler(void)
{
  I2CMaster_IRQHandler(I2C_MASTER_CH0);
}
#endif

#ifdef HTCFG_I2CM_CH1
/*********************************************************************************************************//**
 * @brief This function handles I2C interrupt.
 * @retval None
 ************************************************************************************************************/
void I2CM_CH1_IRQHandler(void)
{
  I2CMaster_IRQHandler(I2C_MASTER_CH1);
}
#endif

#ifdef HTCFG_I2CM_CH2
/*********************************************************************************************************//**
 * @brief   This function handles I2C interrupt.
 * @retval  None
 ************************************************************************************************************/
void I2CM_CH2_IRQHandler(void)
{
  I2CMaster_IRQHandler(I2C_MASTER_CH2);
}
#endif
#endif

#ifdef HTCFG_I2CM_CH3
/*********************************************************************************************************//**
 * @brief   This function handles I2C interrupt.
 * @retval  None
 ************************************************************************************************************/
void I2CM_CH3_IRQHandler(void)
{
  I2CMaster_IRQHandler(I2C_MASTER_CH3);
}
#endif

/*********************************************************************************************************//**
 * @brief   This function handles I2C interrupt.
 * @param  CH: I2C Channel
 * @retval  None
 ************************************************************************************************************/
void I2CMaster_IRQHandler(u32 CH)
{
  I2CMaster_StateTypeDef *pI2CMasterState = &gI2CMasterState[CH];
  u32 uResult;

  if (pI2CMasterState->pI2Cx == 0)
  {
    return;
  }

  uResult = I2C_ReadRegister(pI2CMasterState->pI2Cx, I2C_REGISTER_SR);

  /*----------------------------- Error Process ----------------------------------------------------------  */
  if (uResult & I2C_FLAG_BUSERR)
  {
    pI2CMasterState->uIsBusError = TRUE;
    I2C_ClearFlag(pI2CMasterState->pI2Cx, I2C_FLAG_BUSERR);
    
    #if FREERTOS_I2C
    Transfer_Result[CH] = FALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    #endif
    return ;
  }

  #if (LIBCFG_I2C_NO_ARBLOS == 0)
  if (uResult & I2C_FLAG_ARBLOS)
  {
    pI2CMasterState->uIsBusError = TRUE;
    I2C_ClearFlag(pI2CMasterState->pI2Cx, I2C_FLAG_ARBLOS);
    I2C_ReceiveData(pI2CMasterState->pI2Cx); // Clear Rx Interrupt
    I2C_ReceiveData(pI2CMasterState->pI2Cx);
    
    #if FREERTOS_I2C
    Transfer_Result[CH] = FALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    #endif
    
    return;
  }
  #endif

  if(uResult & I2C_FLAG_TOUTF)
  {
    pI2CMasterState->uIsHardwareTimeout = TRUE;
    I2C_ClearFlag(pI2CMasterState->pI2Cx, I2C_FLAG_TOUTF);

    #if FREERTOS_I2C
    Transfer_Result[CH] = FALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    #endif
    return;
  }

  if (uResult == I2C_FLAG_RXNACK)
  {
    pI2CMasterState->uIsNACK = TRUE;
    I2C_ClearFlag(pI2CMasterState->pI2Cx, I2C_FLAG_RXNACK);

    #if FREERTOS_I2C
    Transfer_Result[CH] = FALSE;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    #endif
    return;
  }


  switch (uResult)
  {
    case I2C_MASTER_SEND_START:
    {
      break;
    }
    /*-----------------------------Master Receiver ---------------------------------------------------------*/
    case I2C_MASTER_RECEIVER_MODE:
    {
      /* Enable I2C ACK for receiving data                                                                  */
      if (pI2CMasterState->uRxLength > 1)
      {
        I2C_AckCmd(pI2CMasterState->pI2Cx, ENABLE);
      }
      break;
    }
    case I2C_MASTER_RX_NOT_EMPTY_NOBUSY:
    {
      if (pI2CMasterState->uRxIndex == pI2CMasterState->uRxLength - 2)
      {
        I2C_AckCmd(pI2CMasterState->pI2Cx, DISABLE);
      }
      *(pI2CMasterState->puRxBuffer + pI2CMasterState->uRxIndex) = I2C_ReceiveData(pI2CMasterState->pI2Cx);
      pI2CMasterState->uRxIndex++;
      break;
    }
    case I2C_MASTER_RX_BUFFER_FULL:
    case I2C_MASTER_RX_NOT_EMPTY:
    {
      if (pI2CMasterState->uRxIndex == pI2CMasterState->uRxLength - 2)
      {
        I2C_AckCmd(pI2CMasterState->pI2Cx, DISABLE);
      }
      /* Receive data sent from I2C                                                                         */
      *(pI2CMasterState->puRxBuffer + pI2CMasterState->uRxIndex) = I2C_ReceiveData(pI2CMasterState->pI2Cx);
      pI2CMasterState->uRxIndex++;

      if (pI2CMasterState->uRxIndex == pI2CMasterState->uRxLength)
      {
        I2C_GenerateSTOP(pI2CMasterState->pI2Cx);

        /* Clear IsBusy flag to terminate polling of I2CMaster_GetStatus                                    */
        pI2CMasterState->IsBusy = FALSE;

        if (pI2CMasterState->sDynamicOnOffI2C)
        {
          if (_I2CMaster_DynamicTimeout(CH) == I2C_MASTER_SW_TIMEOUT)
          {
            return;
          }
          I2C_Cmd(pI2CMasterState->pI2Cx, DISABLE);
        }

        #if FREERTOS_I2C
        Transfer_Result[CH] = TRUE;
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        #endif
      }
      break;
    }

    /*-----------------------------Master Transmitter ------------------------------------------------------*/
    case I2C_MASTER_TRANSMITTER_MODE:
    case I2C_MASTER_TX_EMPTY:
    {
      if (pI2CMasterState->uTxLength != 0)
      {
        I2C_SendData(pI2CMasterState->pI2Cx, *(pI2CMasterState->puTxBuffer + pI2CMasterState->uTxIndex));
        pI2CMasterState->uTxIndex++;
        pI2CMasterState->uTxLength--;
      }
      else
      {
        I2C_IntConfig(pI2CMasterState->pI2Cx, I2C_INT_TXDE, DISABLE);
        if (pI2CMasterState->Command == I2C_MASTER_CMD_WRITE)
        {
          I2C_GenerateSTOP(pI2CMasterState->pI2Cx);
          /* Clear IsBusy flag to terminate polling of I2CMaster_GetStatus                                  */
          pI2CMasterState->IsBusy = FALSE;

          if (pI2CMasterState->sDynamicOnOffI2C)
          {
            if (_I2CMaster_DynamicTimeout(CH) == I2C_MASTER_SW_TIMEOUT)
            {
              return;
            }
            I2C_Cmd(pI2CMasterState->pI2Cx, DISABLE);
          }

          #if FREERTOS_I2C
          Transfer_Result[CH] = TRUE;
          BaseType_t xHigherPriorityTaskWoken = pdFALSE;
          xSemaphoreGiveFromISR(Semphr[CH], &xHigherPriorityTaskWoken);
          portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
          #endif
        }
        else if (pI2CMasterState->Command == I2C_MASTER_CMD_WRITEREAD)
        {
          pI2CMasterState->uI2CReadWrite = I2C_MASTER_READ;
          I2C_TargetAddressConfig(pI2CMasterState->pI2Cx, pI2CMasterState->uSlaveAddress, pI2CMasterState->uI2CReadWrite);
        }
        else if (pI2CMasterState->Command == I2C_MASTER_CMD_WRITESTOPREAD)
        {
          I2C_GenerateSTOP(pI2CMasterState->pI2Cx);
          pI2CMasterState->uI2CReadWrite = I2C_MASTER_READ;
          I2C_TargetAddressConfig(pI2CMasterState->pI2Cx, pI2CMasterState->uSlaveAddress, pI2CMasterState->uI2CReadWrite);
        }
      }
      break;
    }

    /* Received NACK when Read or Write mode                                                                */
    case I2C_MASTER_RECEIVED_RXNACK:
    case I2C_MASTER_RECEIVED_TXNACK:
    {
      I2C_ClearFlag(pI2CMasterState->pI2Cx, I2C_FLAG_RXNACK);
      I2C_GenerateSTOP(pI2CMasterState->pI2Cx);

      if (pI2CMasterState->sDynamicOnOffI2C)
      {
        if (_I2CMaster_DynamicTimeout(CH) == I2C_MASTER_SW_TIMEOUT)
        {
          return;
        }
        I2C_Cmd(pI2CMasterState->pI2Cx, DISABLE);
      }
      /* Set uIsNACK flag for I2CMaster_GetStatus                                                           */
      pI2CMasterState->uIsNACK = TRUE;
      break;
    }
  }
}

/*********************************************************************************************************//**
 * @brief I2C timeout handler.
 * @retval None
 ************************************************************************************************************/
void I2CMaster_TimeoutHandler(void)
{
  #ifdef HTCFG_I2CM_CH0
  if (gI2CMasterState[I2C_MASTER_CH0].sTimerCount > 0)
  {
    gI2CMasterState[I2C_MASTER_CH0].sTimerCount--;
  }
  #endif
  #ifdef HTCFG_I2CM_CH1
  if (gI2CMasterState[I2C_MASTER_CH1].sTimerCount > 0)
  {
    gI2CMasterState[I2C_MASTER_CH1].sTimerCount--;
  }
  #endif
  #ifdef HTCFG_I2CM_CH2
  if (gI2CMasterState[I2C_MASTER_CH2].sTimerCount > 0)
  {
    gI2CMasterState[I2C_MASTER_CH2].sTimerCount--;
  }
  #endif
  #ifdef HTCFG_I2CM_CH3
  if (gI2CMasterState[I2C_MASTER_CH3].sTimerCount > 0)
  {
    gI2CMasterState[I2C_MASTER_CH3].sTimerCount--;
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief I2C Dynamic Timeout Process.
 * @retval None
 ************************************************************************************************************/
I2CMaster_Status_Enum _I2CMaster_DynamicTimeout(u32 CH)
{
  I2CMaster_StateTypeDef *pI2CMasterState = &gI2CMasterState[CH];

  while (I2C_GetFlagStatus(pI2CMasterState->pI2Cx, I2C_FLAG_BUSBUSY) == SET)
  {
    #if (I2C_MASTER_SW_TIMEOUT_MODE == 2)
    u32 uCurrent;
    uCurrent = I2CMASTER_GETTICK();
    pI2CMasterState->sTimerCount -= DIFF_TICK(pI2CMasterState->uStart,uCurrent);
    pI2CMasterState->uStart = uCurrent;
    #endif
    
    if (pI2CMasterState->sTimerCount <= 0) // May not work if timer's interrupt priority is lower than I2C
    {
      return I2C_MASTER_SW_TIMEOUT;
    }
  }
  return I2C_MASTER_GOING;
}

#if FREERTOS_I2C

void I2CMaster_Init_FreeRTOS(u32 CH, u32 uMasterAddress, u32 uClockSpeed)
{
  taskENTER_CRITICAL();
  I2CMaster_Init(CH, uMasterAddress, uClockSpeed);
  Semphr[CH] = xSemaphoreCreateBinaryStatic(&Semphr_Buffer[CH]);
  Mutex[CH] = xSemaphoreCreateMutexStatic(&Mutex_Buffer[CH]);
  taskEXIT_CRITICAL();
}

u32 I2CMaster_Write_FreeRTOS(u32 CH, I2CMaster_Typedef *pI2CMaster, u32 Timeout)
{
  TimeOut_t Tick_Base;

  vTaskSetTimeOutState(&Tick_Base);

  if(xSemaphoreTake(Mutex[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  taskENTER_CRITICAL();
  I2CMaster_Write(CH, pI2CMaster);
  xSemaphoreTake(Semphr[CH], 0);
  taskEXIT_CRITICAL();

  if(xTaskCheckForTimeOut(&Tick_Base, &Timeout) != pdFALSE)
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  if(xSemaphoreTake(Semphr[CH], Timeout) == pdFALSE)
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  xSemaphoreGive(Mutex[CH]);

  return Transfer_Result[CH];
}

u32 I2CMaster_Read_FreeRTOS(u32 CH, I2CMaster_Typedef *pI2CMaster, u32 Timeout)
{
  TimeOut_t Tick_Base;

  vTaskSetTimeOutState(&Tick_Base);

  if(xSemaphoreTake(Mutex[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  taskENTER_CRITICAL();
  I2CMaster_Read(CH, pI2CMaster);
  xSemaphoreTake(Semphr[CH], 0);
  taskEXIT_CRITICAL();

  if(xTaskCheckForTimeOut(&Tick_Base, &Timeout) != pdFALSE )
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  if(xSemaphoreTake(Semphr[CH], Timeout) == pdFALSE)
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  xSemaphoreGive(Mutex[CH]);

  return Transfer_Result[CH];
}

u32 I2CMaster_WriteRead_FreeRTOS(u32 CH, I2CMaster_Typedef *pI2CMaster, u32 Timeout)
{
  TimeOut_t Tick_Base;

  vTaskSetTimeOutState(&Tick_Base);

  if(xSemaphoreTake(Mutex[CH], Timeout) == pdFALSE)
  {
    return FALSE;
  }

  taskENTER_CRITICAL();
  I2CMaster_WriteRead(CH, pI2CMaster);
  xSemaphoreTake(Semphr[CH], 0);
  taskEXIT_CRITICAL();

  if(xTaskCheckForTimeOut(&Tick_Base, &Timeout) != pdFALSE )
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  if(xSemaphoreTake(Semphr[CH], Timeout) == pdFALSE)
  {
    xSemaphoreGive(Mutex[CH]);
    return FALSE;
  }

  xSemaphoreGive(Mutex[CH]);

  return Transfer_Result[CH];
}
#endif

/* Private functions ---------------------------------------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
