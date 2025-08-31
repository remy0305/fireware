/*********************************************************************************************************//**
 * @file    PID/ChangePara_inSameMode/main.c
 * @version $Rev:: 8231         $
 * @date    $Date:: 2024-10-28 #$
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

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup PID_Examples PID
  * @{
  */

/** @addtogroup ChangePara_inSameMode
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void CKCU_Configuration(void);
void PID_SPD_Para1_Configuration(void);
void PID_SPD_Para2_Configuration(void);
s16 PID_StartFun(s32 ERRn, PID_Mode_Enum PID_Mode);

/* Global variables ----------------------------------------------------------------------------------------*/
s32 gERRn = 0;
s32 gPara1_ERRn_1 = 0, gPara2_ERRn_1 = 0;
s16 gPIDout = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  CKCU_Configuration();

  {
    // Switch to Para1.
    PID_SPD_Para1_Configuration();

    // Get Para1 ERRn Value in PID SPD Mode.
    gERRn = 0x2710;

    // Start PID Compute by PID SPD Mode.
    gPIDout = PID_StartFun(gERRn, PID_SPD_MODE);

    // ERRn_1=0x0, ERRn=0x2710, PIDout=0x766
    printf("Para1, ERRn_1=0x%X, ERRn=0x%X, PIDout=0x%X\r\n", gPara1_ERRn_1, gERRn, gPIDout);
  }

  // Retain the ERRn_1 value of Para1 in PID SPD Mode.
  gPara1_ERRn_1 = PID_GetERRn_1(HT_PID0, PID_SPD_MODE);

  {
    // Switch to Para2.
    PID_SPD_Para2_Configuration();

    // Get Para2 ERRn Value in PID SPD Mode.
    gERRn = 0x2712;

    // Start PID Compute by PID SPD Mode.
    gPIDout = PID_StartFun(gERRn, PID_SPD_MODE);

    // ERRn_1=0x0, ERRn=0x2712, PIDout=0x17F
    printf("Para2, ERRn_1=0x%X, ERRn=0x%X, PIDout=0x%X\r\n", gPara2_ERRn_1, gERRn, gPIDout);
  }

  // Retain the ERRn_1 value of Para2 in PID SPD Mode.
  gPara2_ERRn_1 = PID_GetERRn_1(HT_PID0, PID_SPD_MODE);

  {
    // Switch to Para1.
    PID_SPD_Para1_Configuration();

    // Get Para1 ERRn Value in PID SPD Mode.
    gERRn = 0x2714;

    // Start PID Compute by PID SPD Mode.
    gPIDout = PID_StartFun(gERRn, PID_SPD_MODE);

    // ERRn_1=0x2710, ERRn=0x2714, PIDout=0x172
    printf("Para1, ERRn_1=0x%X, ERRn=0x%X, PIDout=0x%X\r\n", gPara1_ERRn_1, gERRn, gPIDout);
  }

  while(1)
  {
    #if 0 // Demo PID Operation as below.
    if (ControlLoopReach)
    {
      // Set ERRn.
      gERRn = xxxx;
 
      // Start PID Compute by PID XXX Mode.
      gPIDout = PID_StartFun(gERRn, PID_XXX_MODE);

      // Control By PIDOut.
      // ...
    }
    #endif
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.PID0 = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the Para1 for PID SPD Mode.
  * @retval None
  ***********************************************************************************************************/
void PID_SPD_Para1_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  PID_InitTypeDef SPD_InitStructure;

  SPD_InitStructure.ERRn_1 = gPara1_ERRn_1;
  SPD_InitStructure.UIn_1 = 0;
  SPD_InitStructure.KP = 0x0000028F;
  SPD_InitStructure.KI = 555;
  SPD_InitStructure.KD = 5000;
  SPD_InitStructure.UI_MAX = 0x00007FFF;
  SPD_InitStructure.UI_MIN = 0x000F8001;
  SPD_InitStructure.OUT_MAX = 0x7EB7;
  SPD_InitStructure.OUT_MIN = 0x8149;
  PID_Init(HT_PID0, PID_SPD_MODE, &SPD_InitStructure);
}

/*********************************************************************************************************//**
  * @brief  Configure the Para2 for PID SPD Mode.
  * @retval None
  ***********************************************************************************************************/
void PID_SPD_Para2_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  PID_InitTypeDef SPD_InitStructure;

  SPD_InitStructure.ERRn_1 = gPara2_ERRn_1;
  SPD_InitStructure.UIn_1 = 0;
  SPD_InitStructure.KP = 0x000000FF;
  SPD_InitStructure.KI = 1;
  SPD_InitStructure.KD = 1000;
  SPD_InitStructure.UI_MAX = 0x00007FFF;
  SPD_InitStructure.UI_MIN = 0x000F8001;
  SPD_InitStructure.OUT_MAX = 0x7EB7;
  SPD_InitStructure.OUT_MIN = 0x8149;
  PID_Init(HT_PID0, PID_SPD_MODE, &SPD_InitStructure);
}

/*********************************************************************************************************//**
  * @brief  PID start compute function.
  * @param  ERRn: where ERRn is Error Input Value.
  * @param  PID_Mode: where PID_Mode is the selected PID mode.
  * @retval The Value of PID result.
  ***********************************************************************************************************/
s16 PID_StartFun(s32 ERRn, PID_Mode_Enum PID_Mode)
{
  // Set Common Parameter, ERRn.
  PID_SetComPara_ERRn(HT_PID0, ERRn);

  PID_Compute(HT_PID0, PID_Mode);
  while(PID_GetFlagStatus(HT_PID0, PID_FLAG_CMP) == RESET);

  return PID_GetOutResult(HT_PID0);
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
