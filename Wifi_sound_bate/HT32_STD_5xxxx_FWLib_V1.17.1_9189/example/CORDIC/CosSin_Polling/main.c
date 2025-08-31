/*********************************************************************************************************//**
 * @file    CORDIC/CosSin_Polling/main.c
 * @version $Rev:: 8712         $
 * @date    $Date:: 2025-05-05 #$
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

/** @addtogroup CORDIC_Examples CORDIC
  * @{
  */

/** @addtogroup CosSin_Polling
  * @{
  */


/* Private types -------------------------------------------------------------------------------------------*/
typedef enum {Fail = 0, Pass = !Fail} TestResult;

/* Private constants ---------------------------------------------------------------------------------------*/
/* Reference values in Q1.31 format                                                                         */
#define ANGLE_CORDIC      (s32)0x10000000       /* pi/8 in CORDIC input angle mapping                   */
#define COS_REF           (s32)0x7641AF3C       /* cos(pi/8) reference value                            */
#define SIN_REF           (s32)0x30FBC54D       /* sin(pi/8) reference value                            */
#define DELTA             (s32)0x00001000       /* Max residual error for cos and sin, with 6 cycle precision:
                                                       2^-19 max residual error, ie 31-19=12 LSB, ie <0x1000*/

/* Private function prototypes -----------------------------------------------------------------------------*/
void CORDIC_Configuration(void);
TestResult Check_Residual_Error(s32 VarA, s32 VarB, s32 MaxError);

/* Global variables ----------------------------------------------------------------------------------------*/
s32 cosOutput = 0;
s32 sinOutput = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  /* Initialize LED1 & LED2 on HT32 board                                                                   */
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);

  CORDIC_Configuration();                /* CORDIC configuration                                            */

  CORDIC_WriteData(ANGLE_CORDIC);

  /* Read Cosine                                                                                            */
  cosOutput = (int32_t)CORDIC_ReadData();

  /* Read Sine                                                                                              */
  sinOutput = (int32_t)CORDIC_ReadData();

  /* Check RRDY, result ready flag. 
     [Reset by hardware when the CORDICRDATA register is read (NRES + 1) times]                             */
  if (CORDIC_GetFlagStatus_RRDY() == SET)
  {
    printf("Result: Unexpected result.\r\n");
    printf("RRDY should reset when the CORDICRDATA register is read (NRES + 1) times.\r\n");
    while(1);
  }

  /* Check residual error on cosine and sine results                                                        */
  if ((Check_Residual_Error(cosOutput, COS_REF, DELTA) == Fail) ||
      (Check_Residual_Error(sinOutput, SIN_REF, DELTA) == Fail))
  {
    HT32F_DVB_LEDOn(HT_LED2);

    printf("Result: Unexpected result.\r\n");
    printf("Check residual error on cosine and sine fail.\r\n");
    while(1);
  }
  else
  {
    HT32F_DVB_LEDOn(HT_LED1);

    printf("Result: Success.\r\n");
    printf("cosOutput = 0x%X, sinOutput = 0x%X\r\n", cosOutput, sinOutput);
  }

  while(1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the CORDIC.
  * @retval None
  ***********************************************************************************************************/
void CORDIC_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.CORDIC = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  { /* CORDIC configuration                                                                                 */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    CORDIC_InitTypeDef CORDIC_InitStructure;
    CORDIC_InitStructure.Function  = CORDIC_FUNCTION_COSINE;   /* COSINE function */
    CORDIC_InitStructure.Precision = CORDIC_PRECISION_6CYCLES; /* max precision for q1.31 cosine */
    CORDIC_InitStructure.Scale     = CORDIC_SCALE_0;           /* no scale */
    CORDIC_InitStructure.NbWrite   = CORDIC_NBWRITE_1;         /* One input data: angle. Second input data (modulus) is 1 after cordic reset */
    CORDIC_InitStructure.NbRead    = CORDIC_NBREAD_2;          /* One output data: sine */
    CORDIC_InitStructure.InSize    = CORDIC_INSIZE_32BITS;     /* q1.31 format for input data */
    CORDIC_InitStructure.OutSize   = CORDIC_OUTSIZE_32BITS;    /* q1.31 format for output data */

    CORDIC_Init(&CORDIC_InitStructure);
  }
}

/*********************************************************************************************************//**
  * @brief  Check delta between two values is below threshold.
  * @param  VarA: First input variable
  * @param  VarB: Second input variable
  * @param  MaxError: Maximum delta allowed between VarA and VarB
  * @retval Pass or Fail
  ***********************************************************************************************************/
TestResult Check_Residual_Error(s32 VarA, s32 VarB, s32 MaxError)
{
  if ((VarA - VarB) >= 0)
  {
    if ((VarA - VarB) > MaxError)
    {
      return Fail;
    }
  }
  else
  {
    if ((VarB - VarA) > MaxError)
    {
      return Fail;
    }
  }

  return Pass;
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
