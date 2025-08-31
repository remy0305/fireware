/*********************************************************************************************************//**
 * @file    PDMA/SoftwareTrigger/main.c
 * @version $Rev:: 7504         $
 * @date    $Date:: 2024-01-16 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup PDMA_Examples PDMA
  * @{
  */

/** @addtogroup SoftwareTrigger
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void PDMA_TestFun1(void);
void PDMA_TestFun2(void);
void PDMA_TestFun3(void);

/* Private variables ---------------------------------------------------------------------------------------*/
uc8 PdmaCh0SrcBuf[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
u8 PdmaCh0DstBuf[8];

u16 PdmaCh1DstBuf[4];

u32 PdmaCh2SrcBuf[2] = {0x01234567, 0x89ABCDEF};
u32 PdmaCh2DstBuf[6];

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  PDMA_TestFun1();

  PDMA_TestFun2();

  PDMA_TestFun3();

  while (1)
  {
    /* All tests are passed!                                                                                */
  }
}

/*********************************************************************************************************//**
  * @brief  PDMA Test Function 1.
  * @retval None
  ***********************************************************************************************************/
void PDMA_TestFun1(void)
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Configure the PDMA from Flash to SRAM, linear increment to linear decrement, 8-bit.                    */
  /*--------------------------------------------------------------------------------------------------------*/

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PDMA       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  {
    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;

    PDMACH_InitStructure.PDMACH_SrcAddr   = (u32)(&PdmaCh0SrcBuf[0]);
    PDMACH_InitStructure.PDMACH_DstAddr   = (u32)(&PdmaCh0DstBuf[7]);
    PDMACH_InitStructure.PDMACH_AdrMod    = SRC_ADR_LIN_INC | DST_ADR_LIN_DEC;
    PDMACH_InitStructure.PDMACH_Priority  = M_PRIO;
    PDMACH_InitStructure.PDMACH_BlkCnt    = 2;
    PDMACH_InitStructure.PDMACH_BlkLen    = 4;
    PDMACH_InitStructure.PDMACH_DataSize  = WIDTH_8BIT;
    PDMA_Config(PDMA_CH0, &PDMACH_InitStructure);

    PDMA_IntConfig(PDMA_CH0, (PDMA_INT_GE | PDMA_INT_TC), ENABLE);
    PDMA_EnaCmd(PDMA_CH0, ENABLE);
  }

  PDMA_SwTrigCmd(PDMA_CH0, ENABLE);    /* Software trigger PDMA                                             */
  while (PDMA_GetFlagStatus(PDMA_CH0, PDMA_FLAG_TC) != SET){};  /* Wait until  Transfer Complete            */
  PDMA_ClearFlag(PDMA_CH0, PDMA_INT_TC);

  /* Check the source and destination data of are the same                                                  */
  {
    u32 i;
    u32 err = 0;

    for (i = 0; i < 8; i++)
    {
      if (PdmaCh0DstBuf[7 - i] != PdmaCh0SrcBuf[i])
      {
        err++;
      }
    }

    /* Verify error                                                                                         */
    while (err != 0){};
  }
}
PDMACH_InitTypeDef PDMACH_InitStructure;
/*********************************************************************************************************//**
  * @brief  PDMA Test Function 2.
  * @retval None
  ***********************************************************************************************************/
void PDMA_TestFun2(void)
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Configure the PDMA from IP Register to SRAM, fixed address to linear increment, 16-bit.                */
  /*--------------------------------------------------------------------------------------------------------*/

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PDMA       = 1;
    CKCUClock.Bit.BFTM0      = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  HT_BFTM0->CNTR = 0xAA55;

  {
    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    //PDMACH_InitTypeDef PDMACH_InitStructure;

    PDMACH_InitStructure.PDMACH_SrcAddr   = (u32)(&HT_BFTM0->CNTR);
    PDMACH_InitStructure.PDMACH_DstAddr   = (u32)(&PdmaCh1DstBuf[0]);
    PDMACH_InitStructure.PDMACH_AdrMod    = SRC_ADR_FIX | DST_ADR_LIN_INC;
    PDMACH_InitStructure.PDMACH_Priority  = H_PRIO;
    PDMACH_InitStructure.PDMACH_BlkCnt    = 4;
    PDMACH_InitStructure.PDMACH_BlkLen    = 1;
    PDMACH_InitStructure.PDMACH_DataSize  = WIDTH_16BIT;
    PDMA_Config(PDMA_CH1, &PDMACH_InitStructure);

    PDMA_IntConfig(PDMA_CH1, (PDMA_INT_GE | PDMA_INT_TC), ENABLE);
    PDMA_EnaCmd(PDMA_CH1, ENABLE);
  }

  PDMA_SwTrigCmd(PDMA_CH1, ENABLE);    /* Software trigger PDMA                                             */
  while (PDMA_GetFlagStatus(PDMA_CH1, PDMA_FLAG_TC) != SET){};  /* Wait until  Transfer Complete            */
  PDMA_ClearFlag(PDMA_CH1, PDMA_INT_TC);

  /* Check the source and destination data of are the same                                                  */
  {
    u32 i;
    u32 err = 0;

    for (i = 0; i < 4; i++)
    {
      if (PdmaCh1DstBuf[i] != HT_BFTM0->CNTR)
      {
        err++;
      }
    }

    /* Verify error                                                                                         */
    while (err != 0){};
  }
}

/*********************************************************************************************************//**
  * @brief  PDMA Test Function 3.
  * @retval None
  ***********************************************************************************************************/
void PDMA_TestFun3(void)
{
  /*--------------------------------------------------------------------------------------------------------*/
  /* Configure the from PDMA SRAM to SRAM, circular increment to linear increment, 32-bit.                  */
  /*--------------------------------------------------------------------------------------------------------*/

  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PDMA       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  {
    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    PDMACH_InitTypeDef PDMACH_InitStructure;

    PDMACH_InitStructure.PDMACH_SrcAddr   = (u32)(&PdmaCh2SrcBuf[0]);
    PDMACH_InitStructure.PDMACH_DstAddr   = (u32)(&PdmaCh2DstBuf[0]);
    PDMACH_InitStructure.PDMACH_AdrMod    = SRC_ADR_CIR_INC | DST_ADR_LIN_INC;
    PDMACH_InitStructure.PDMACH_Priority  = L_PRIO;
    PDMACH_InitStructure.PDMACH_BlkCnt    = 3;
    PDMACH_InitStructure.PDMACH_BlkLen    = 2;
    PDMACH_InitStructure.PDMACH_DataSize  = WIDTH_32BIT;
    PDMA_Config(PDMA_CH2, &PDMACH_InitStructure);

    PDMA_IntConfig(PDMA_CH2, (PDMA_INT_GE | PDMA_INT_TC), ENABLE);
    PDMA_EnaCmd(PDMA_CH2, ENABLE);
  }

  PDMA_SwTrigCmd(PDMA_CH2, ENABLE);    /* Software trigger PDMA                                             */
  while (PDMA_GetFlagStatus(PDMA_CH2, PDMA_FLAG_TC) != SET){};  /* Wait until  Transfer Complete            */
  PDMA_ClearFlag(PDMA_CH2, PDMA_INT_TC);

  /* Check the source and destination data of are the same                                                  */
  {
    u32 i;
    u32 j;
    u32 err = 0;

    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 2; j++)
      {
        if (PdmaCh2DstBuf[j] != PdmaCh2SrcBuf[j])
        {
          err++;
        }
      }
    }

    /* Verify error                                                                                         */
    while (err != 0);
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
