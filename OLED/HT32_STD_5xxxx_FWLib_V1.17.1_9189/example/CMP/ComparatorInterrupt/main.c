/*********************************************************************************************************//**
 * @file    CMP/ComparatorInterrupt/main.c
 * @version $Rev:: 8632         $
 * @date    $Date:: 2025-04-25 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup CMP_Examples CMP
  * @{
  */

/** @addtogroup ComparatorInterrupt
  * @{
  */


/* Private function prototypes -----------------------------------------------------------------------------*/
void CMP_Configuration(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);

  CMP_Configuration();

  /* Enable CMP                                                                                             */
  CMP_UnprotectConfig(HTCFG_CP_PORT);
  CMP_Cmd(HTCFG_CP_PORT, ENABLE);

  /* Infinite loop                                                                                          */
  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Comparator configuration.
  * @retval None
  ***********************************************************************************************************/
void CMP_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.AFIO  = 1;
    CKCUClock.Bit.CMP   = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO mode as CMP function                                                                    */
  AFIO_GPxConfig(HTCFG_CP_GPIO_ID, HTCFG_CP_AFIO_PIN , AFIO_FUN_CMP);

  {
    /*------------------------------------------------------------------------------------------------------*/
    /* Set CMP0 Control Reg:                                                                                */
    /*  1. Setting comparator internal 6-bit/8-bit scaler reference voltage output.                         */
    /*  2. Setting scaler reference voltage source comes from VDDA.                                         */
    /*  3. Enable scaler for comparator voltage reference.                                                  */
    /*  4. Enable scaler output to CN pin.                                                                  */
    /*  5. Setting CVREF = 31 * (VDDA - VSSA) / ((2 ^ n) - 1), n represent the bits of the scaler           */
    /*------------------------------------------------------------------------------------------------------*/

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    CMP_InitTypeDef CMP_IniStruct;

    #if 0
    CMP_StructInit(&CMP_IniStruct);
    #endif
    CMP_IniStruct.CMP_Wakeup            = CMP_WUP_DISABLE;
    CMP_IniStruct.CMP_OutputSelection   = CMP_TRIG_NONE;
    CMP_IniStruct.CMP_ScalerSource      = CMP_SCALER_SRC_VDDA;
    CMP_IniStruct.CMP_ScalerOutputBuf   = CMP_SCALER_OBUF_ENABLE;
    CMP_IniStruct.CMP_ScalerEnable      = CMP_SCALER_ENABLE;
    CMP_IniStruct.CMP_CoutSync          = CMP_ASYNC_OUTPUT;
    CMP_IniStruct.CMP_OutputPol         = CMP_NONINV_OUTPUT;

    #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
    CMP_IniStruct.CMP_InputSelection    = CMP_INPUT_CMPnP;
    #elif defined(USE_HT32F66242) || defined(USE_HT32F66246) || defined(USE_HT32F65233)
    CMP_IniStruct.CMP_InputSelection    = CMP_INPUT_CMP0P;
    #endif

    #if defined(USE_HT32F66242) || defined(USE_HT32F66246) || defined(USE_HT32F65233)
    CMP_IniStruct.CMP_InvInputSelection = CMP_CVREF0_CN_IN;
    #else
    CMP_IniStruct.CMP_InvInputSelection = CMP_SCALER_CN_IN;
    #endif

    CMP_IniStruct.CMP_Hysteresis        = CMP_NO_HYSTERESIS;
    CMP_IniStruct.CMP_Speed             = CMP_LOW_SPEED;
    CMP_UnprotectConfig(HTCFG_CP_PORT);
    CMP_Init(HTCFG_CP_PORT, &CMP_IniStruct);
  }

  /* CVREF = 31 * (VDDA - VSSA) / ((2 ^ n) - 1), n represent the bits of the scaler                         */
  CMP_SetScalerValue(HTCFG_CP_PORT, 31);

  /* Enable CMP rising/falling edge detection.                                                              */
  CMP_EdgeDetectConfig(HTCFG_CP_PORT, CMP_RE_Detect | CMP_FE_Detect, ENABLE);

  /* Enable CMP Interrupt                                                                                   */
  CMP_IntConfig(HTCFG_CP_PORT, CMP_INT_RE | CMP_INT_FE, ENABLE);
  NVIC_EnableIRQ(HTCFG_CMP_IRQn);
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
