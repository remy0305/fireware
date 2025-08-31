/*********************************************************************************************************//**
 * @file    LEDC/7-SegmentDigitalDisplay/main.c
 * @version $Rev:: 8158         $
 * @date    $Date:: 2024-09-20 #$
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup LEDC_Examples LEDC
  * @{
  */

/** @addtogroup 7-SegmentDigitalDisplay
  * @{
  */

/* Private constants ---------------------------------------------------------------------------------------*/
const u8 NumberChar[] = {
  /* a: Seg4(0x10), b: Seg7(0x80), c: Seg2(0x04), d: Seg5(0x20),
     e: Seg3(0x08), f: Seg0(0x01), g: Seg6(0x40), dp: Seg1(0x02) */
  0xBD, /* '0' = a+b+c+d+e+f      = 0x10 + 0x80 + 0x04 + 0x20 + 0x08 + 0x01               = 0xBD */
  0x84, /* '1' =   b+c+           =        0x80 + 0x04                                    = 0x84 */
  0xF8, /* '2' = a+b  +d+e  +g    = 0x10 + 0x80 +        0x20 + 0x08 +      + 0x40        = 0xF8 */
  0xF4, /* '3' = a+b+c+d    +g    = 0x10 + 0x80 + 0x04 + 0x20 +             + 0x40        = 0xF4 */
  0xC5, /* '4' =   b+c    +f+g    =        0x80 + 0x04               + 0x01 + 0x40        = 0xC5 */
  0x75, /* '5' = a  +c+d  +f+g    = 0x10        + 0x04 + 0x20        + 0x01 + 0x40        = 0x75 */
  0x7D, /* '6' = a  +c+d+e+f+g    = 0x10        + 0x04 + 0x20 + 0x08 + 0x01 + 0x40        = 0x7D */
  0x95, /* '7' = a+b+c    +f      = 0x10 + 0x80 + 0x04               + 0x01               = 0x95 */
  0xFD, /* '8' = a+b+c+d+e+f+g    = 0x10 + 0x80 + 0x04 + 0x20 + 0x08 + 0x01 + 0x40        = 0xFD */
  0xF5, /* '9' = a+b+c+d  +f+g    = 0x10 + 0x80 + 0x04 + 0x20        + 0x01 + 0x40        = 0xF5 */
  0x02  /* '.' =               dp =                                                  0x02 = 0x02 */
};

/* Private function prototypes -----------------------------------------------------------------------------*/
void LEDC_Configuration(void);
void GPIO_Configuration(void);

/* Global variables ----------------------------------------------------------------------------------------*/
extern bool gIsUpdateChar;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  u8 CharIndex = 0;
  u8 CharSize = sizeof(NumberChar);
  GPIO_Configuration();
  LEDC_Configuration();
  while (1)
  {
    if (gIsUpdateChar)
    {
      /* The character has been displayed for 1 second, and the new character will be replaced.             */
      LEDC_SetData(HTCFG_LEDC_COM_D1,  NumberChar[CharIndex++%CharSize]);
      LEDC_SetData(HTCFG_LEDC_COM_D2,  NumberChar[CharIndex++%CharSize]);
      LEDC_SetData(HTCFG_LEDC_COM_D3,  NumberChar[CharIndex++%CharSize]);
      LEDC_SetData(HTCFG_LEDC_COM_D4,  NumberChar[CharIndex++%CharSize]);
      gIsUpdateChar = FALSE;
    }
  }
}
FlagStatus st;
/*********************************************************************************************************//**
  * @brief  Configure the LEDC.
  * @retval None
  ***********************************************************************************************************/
void LEDC_Configuration(void)
{
  LEDC_InitTypeDef LEDC_InitStruct;

  /* Turn on the APB clock of LEDC.                                                                         */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.LEDC       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Frame = fCK_LED / (LEDC_DutyClockNumber * COM Number)                                                  */
  /*       = 1600 / (8 * 4)  =  50Hz                                                                        */
  LEDC_InitStruct.LEDC_ClockSource    = LEDC_SRC_LSI;                    /* LSI = 32Khz                     */
  LEDC_InitStruct.LEDC_ClockPrescaler = HTCFG_LEDC_CLOCK_PRESCAL - 1;    /* fCK_LED = 32Khz / 20 = 1600 Hz  */
  LEDC_InitStruct.LEDC_DutyClockNumber = HTCFG_LEDC_DUTY_CLOCK_NUMBER;   /* Duty CLock Number = 8 Clock     */
  LEDC_InitStruct.LEDC_COMxEN = HTCFG_LEDC_COM1EN | HTCFG_LEDC_COM2EN |\
                                HTCFG_LEDC_COM3EN | HTCFG_LEDC_COM4EN;   /* Enable COMx                     */

  /* Change the brightness, the parameter range is 0~Duty (CLock Number-1.)                                 */
  /* 0: the brightest, 7: the darkest.                                                                      */
  LEDC_InitStruct.LEDC_DeadTime = 0;
  LEDC_Init(&LEDC_InitStruct);                                            /* LEC initialization.            */

  /* Set the LEDC mode to COMMON_CATHODE.                                                                   */
  LEDC_SetPolarityMode(HTCFG_LEDC_COM1POL | HTCFG_LEDC_COM2POL | HTCFG_LEDC_COM3POL | HTCFG_LEDC_COM4POL,
                       LEDC_SEG0POL | LEDC_SEG1POL | LEDC_SEG2POL | LEDC_SEG3POL |\
                       LEDC_SEG4POL | LEDC_SEG5POL | LEDC_SEG6POL | LEDC_SEG7POL,
                       COMMON_CATHODE);

  LEDC_IntConfig(ENABLE);                                                 /* Enable frame interrupt.        */
  NVIC_EnableIRQ(LEDC_IRQn); /* Enable LECD IRQ.                                                            */
  LEDC_Cmd(ENABLE);          /* LEDC Start.                                                                 */
}

/*********************************************************************************************************//**
  * @brief  Configure the GPIO ports.
  * @retval None
  ***********************************************************************************************************/
void GPIO_Configuration(void)
{
  /* Turn on the APB clock of AFIO.                                                                         */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* SEG0~7                                                                                                 */
  AFIO_GPxConfig(HTCFG_LEDC_SEG0_GPIO_ID, HTCFG_LEDC_SEG0_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_SEG1_GPIO_ID, HTCFG_LEDC_SEG1_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_SEG2_GPIO_ID, HTCFG_LEDC_SEG2_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_SEG3_GPIO_ID, HTCFG_LEDC_SEG3_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_SEG4_GPIO_ID, HTCFG_LEDC_SEG4_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_SEG5_GPIO_ID, HTCFG_LEDC_SEG5_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_SEG6_GPIO_ID, HTCFG_LEDC_SEG6_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_SEG7_GPIO_ID, HTCFG_LEDC_SEG7_AFIO_PIN, AFIO_FUN_LEDC);

  /* COM0~4                                                                                                 */
  AFIO_GPxConfig(HTCFG_LEDC_COM0_GPIO_ID, HTCFG_LEDC_COM0_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_COM1_GPIO_ID, HTCFG_LEDC_COM1_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_COM2_GPIO_ID, HTCFG_LEDC_COM2_AFIO_PIN, AFIO_FUN_LEDC);
  AFIO_GPxConfig(HTCFG_LEDC_COM3_GPIO_ID, HTCFG_LEDC_COM3_AFIO_PIN, AFIO_FUN_LEDC);
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
