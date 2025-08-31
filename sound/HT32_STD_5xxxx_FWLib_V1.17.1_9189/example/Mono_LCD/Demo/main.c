/*********************************************************************************************************//**
 * @file    Mono_LCD/Demo/main.c
 * @version $Rev:: 5250         $
 * @date    $Date:: 2021-02-04 #$
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
#include "ht32_board_config.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup Mono_LCD_Examples Mono_LCD
  * @{
  */

/** @addtogroup Demo
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void LCD_Configuration(void);

/* Private variables ---------------------------------------------------------------------------------------*/
vu32 isUpdateDisplayFinish;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  s32 com;
  LCD_Configuration();                      /* LCD Related configuration                                    */

  /* Write LCD_RAM                                                                                          */
  for(com = 0; com < 16; com++)
  {
    HT_LCD->RAM[com]=0xFFFFFFFF;
  }

  /* Update Display Request                                                                                 */
  LCD_SetUpdateDisplayRequest();

  /* Waiting for finish                                                                                     */
  while(isUpdateDisplayFinish == FALSE){};

  /* Finish and enter the dead loop                                                                         */
  while(1){};
}

/*********************************************************************************************************//**
  * @brief  Configure the LCD.
  * @retval None
  ***********************************************************************************************************/
void LCD_Configuration(void)
{
  /* !!! NOTICE !!!
     Notice that the local variable (structure) did not have an initial value.
     Please confirm that there are no missing members in the parameter settings below in this function.
  */
  LCD_InitTypeDef LCD_InitStructure;

  /* Enable peripheral clocks of AFIO, LCD                                                                 */
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.LCDC          = 1;
  CKCUClock.Bit.LCDR          = 1;
  CKCUClock.Bit.AFIO          = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  /* Config AFIO mode as LCD function                                                                       */
  AFIO_GPxConfig(HTCFG_LCD_COM0_GPIO_ID, HTCFG_LCD_COM0_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM1_GPIO_ID, HTCFG_LCD_COM1_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM2_GPIO_ID, HTCFG_LCD_COM2_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM3_GPIO_ID, HTCFG_LCD_COM3_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM4_GPIO_ID, HTCFG_LCD_COM4_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM5_GPIO_ID, HTCFG_LCD_COM5_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM6_GPIO_ID, HTCFG_LCD_COM6_AFIO_PIN,   AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_COM7_GPIO_ID, HTCFG_LCD_COM7_AFIO_PIN,   AFIO_FUN_LCD);

  AFIO_GPxConfig(HTCFG_LCD_SEG0_GPIO_ID,  HTCFG_LCD_SEG0_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG1_GPIO_ID,  HTCFG_LCD_SEG1_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG2_GPIO_ID,  HTCFG_LCD_SEG2_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG3_GPIO_ID,  HTCFG_LCD_SEG3_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG4_GPIO_ID,  HTCFG_LCD_SEG4_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG5_GPIO_ID,  HTCFG_LCD_SEG5_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG6_GPIO_ID,  HTCFG_LCD_SEG6_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG7_GPIO_ID,  HTCFG_LCD_SEG7_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG8_GPIO_ID,  HTCFG_LCD_SEG8_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG9_GPIO_ID,  HTCFG_LCD_SEG9_AFIO_PIN,  AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG10_GPIO_ID, HTCFG_LCD_SEG10_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG11_GPIO_ID, HTCFG_LCD_SEG11_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG12_GPIO_ID, HTCFG_LCD_SEG12_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG13_GPIO_ID, HTCFG_LCD_SEG13_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG14_GPIO_ID, HTCFG_LCD_SEG14_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG15_GPIO_ID, HTCFG_LCD_SEG15_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG16_GPIO_ID, HTCFG_LCD_SEG16_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG17_GPIO_ID, HTCFG_LCD_SEG17_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG18_GPIO_ID, HTCFG_LCD_SEG18_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG19_GPIO_ID, HTCFG_LCD_SEG19_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG20_GPIO_ID, HTCFG_LCD_SEG20_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG21_GPIO_ID, HTCFG_LCD_SEG21_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG22_GPIO_ID, HTCFG_LCD_SEG22_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG23_GPIO_ID, HTCFG_LCD_SEG23_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG24_GPIO_ID, HTCFG_LCD_SEG24_AFIO_PIN, AFIO_FUN_LCD);
  #if defined(HTCFG_LCD_SEG32_MODE)
  AFIO_GPxConfig(HTCFG_LCD_SEG25_GPIO_ID, HTCFG_LCD_SEG25_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG26_GPIO_ID, HTCFG_LCD_SEG26_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG27_GPIO_ID, HTCFG_LCD_SEG27_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG28_GPIO_ID, HTCFG_LCD_SEG28_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG29_GPIO_ID, HTCFG_LCD_SEG29_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG30_GPIO_ID, HTCFG_LCD_SEG30_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG31_GPIO_ID, HTCFG_LCD_SEG31_AFIO_PIN, AFIO_FUN_LCD);
  AFIO_GPxConfig(HTCFG_LCD_SEG32_GPIO_ID, HTCFG_LCD_SEG32_AFIO_PIN, AFIO_FUN_LCD);
  #endif

  /* !!! NOTICE !!!
     Must wait until the LCDENS = 0 before change the LCD control register.
  */
  while (LCD_GetFlagStatus(LCD_FLAG_ENS) == 1);

  /* LCDCLK config                                                                                          */
  CKCU_LCDClockConfig(CKCU_LCDSRC_LSI);     /* Using internal 32 kHz RC oscillator clock. LCDCLK = 32 kHz.  */

  /* LCD initialization */
  /* Frame rate = LCDCLK / (LCD_Divider_25 * LCD_Prescaler_4) * duty                                        */
  /*            =  32000 / (25 * 4) * 1/8                                                                   */
  /*            =  40 Hz                                                                                    */
  LCD_InitStructure.LCD_Divider = LCD_Divider_25;
  LCD_InitStructure.LCD_Prescaler = LCD_Prescaler_4;
  LCD_InitStructure.LCD_Duty = LCD_Duty_1_8;
  LCD_InitStructure.LCD_Bias = LCD_Bias_1_4;
  LCD_InitStructure.LCD_VoltageSource = LCD_VoltageSource_Internal;
  LCD_InitStructure.LCD_Waveform = LCD_Type_B_Waveform;
  LCD_DriverInit(&LCD_InitStructure);

  /* Enable High Drive Mode                                                                                 */
  LCD_HighDriveConfig(LCD_HighDrive_Static);

  /* Increase LCD drive capability.                                                                         */
  LCD_HalfRLCmd(ENABLE);  /* Enable half of the RL(low value resistor).                                     */

  /* LCD Internal Charge Pump 3.25V                                                                         */
  LCD_ChargePumpConfig(LCD_ChargePump_3V25);

  /* Wait for charge pump ready                                                                             */
  while(LCD_GetFlagStatus(LCD_FLAG_RDY) == RESET);

  /* LCD Interrupt                                                                                          */
  LCD_ClearFlag(LCD_CLR_UDD | LCD_CLR_SOF);
  LCD_IntConfig(LCD_INT_UDD | LCD_INT_SOF, ENABLE);
  NVIC_EnableIRQ(LCD_IRQn);

  /* Enable LCD                                                                                             */
  LCD_Cmd(ENABLE);
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
