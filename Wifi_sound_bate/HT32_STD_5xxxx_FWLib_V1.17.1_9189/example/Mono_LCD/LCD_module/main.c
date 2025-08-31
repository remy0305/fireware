/*********************************************************************************************************//**
 * @file    Mono_LCD/LCD_module/main.c
 * @version $Rev:: 4866         $
 * @date    $Date:: 2020-08-05 #$
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
#include "_ht32_project_source.h"
#include "lcd_ESK32_A3A31.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup Mono_LCD_Examples Mono_LCD
  * @{
  */

/** @addtogroup LCD_module
  * @{
  */

/* Global variables ----------------------------------------------------------------------------------------*/
vu32 isUpdateDisplayFinish;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  int x,y; 
  LCD_Init_ESK32_A3A31();
  while(1)
  {
    /* Show a volume picture.                                                                               */
    LCD_show_VoiceConfig(LCD_VOICE_LEVEL_5);

    /* Show a Bluetooth picture.                                                                            */
    LCD_show_BT(LCD_PIXEL_ON);
    LCD_show_BT_UpStream(LCD_PIXEL_ON);
    LCD_show_BT_DownStream(LCD_PIXEL_ON);

    /* Show a Holtek logo picture.                                                                          */
    LCD_show_HoltekLogo(LCD_PIXEL_ON);

    /* Show a RF picture.                                                                                   */
    LCD_show_RF_Level(LCD_RF_LEVEL_3);
    LCD_show_RF_UpStream(LCD_PIXEL_ON);
    LCD_show_RF_DownStream(LCD_PIXEL_ON);

    /* Show a battery picture.                                                                              */
    LCD_show_BAT_Frame(LCD_PIXEL_ON);
    LCD_show_BAT_Level(LCD_BAT_LEVEL_3);

    /* Show the first 7-segment Display                                                                     */
    LCD_show_Group1_number(LCD_DIGIT_0, _7SEG_8);
    LCD_show_Group1_number(LCD_DIGIT_1, _7SEG_8);
    LCD_show_Group1_number(LCD_DIGIT_2, _7SEG_8);
    LCD_show_Group1_number(LCD_DIGIT_3, _7SEG_8);
    LCD_show_Group1_Dot(LCD_DIGIT_0);
    LCD_show_Group1_Unit(LCD_UNIT_AM);

    /* Show the second 7-segment Display                                                                    */
    LCD_show_Group2_number(LCD_DIGIT_NONE, _7SEG_Minus);
    LCD_show_Group2_number(LCD_DIGIT_0, _7SEG_8);
    LCD_show_Group2_number(LCD_DIGIT_1, _7SEG_8);
    LCD_show_Group2_number(LCD_DIGIT_2, _7SEG_8);
    LCD_show_Group2_number(LCD_DIGIT_3, _7SEG_8);
    LCD_show_Group2_number(LCD_DIGIT_4, _7SEG_8);
    LCD_show_Group2_Dot(LCD_DIGIT_0);
    LCD_show_Group2_Unit(LCD_UNIT_mV);

    while(1)
    {
      for(y=0;y<8;y++)
      {
        for(x=0;x<20;x++)
        {
          LCD_show_Matrix(x, y, LCD_PIXEL_ON);
          /* Send upadate display request.                                                                  */
          LCD_SetUpdateDisplayRequest();

          /* Waiting for the update to finish.                                                              */
          isUpdateDisplayFinish = FALSE;
          while(isUpdateDisplayFinish == FALSE){}
        }
      }
      /* Clear Matrix                                                                                       */
      LCD_MatrixClear(0, 0,20,8,LCD_PIXEL_OFF);
    }
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
