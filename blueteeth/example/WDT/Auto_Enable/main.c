/*********************************************************************************************************//**
 * @file    WDT/Auto_Enable/main.c
 * @version $Rev:: 7609         $
 * @date    $Date:: 2024-02-26 #$
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

/** @addtogroup WDT_Examples WDT
  * @{
  */

/** @addtogroup Auto_Enable
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
ErrStatus AutoWDT_Cmd(ControlStatus autoWdtCmd);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  /* Enable the Auto_WDT                                                                                    */
  if(AutoWDT_Cmd(ENABLE) == ERROR)
  {
    /*If Flash write to OB_WDT is abnormal, enter while loop.                                               */
    while(1);
  }

  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);

  if(RSTCU_GetResetFlagStatus(RSTCU_FLAG_WDTRST) == SET)
  {
    /* WDT generates a reset request and then turns on LED2.                                                */
    HT32F_DVB_LEDOn(HT_LED2);
  }
  else
  {
    /* Other functions generate a reset request and then turns on LED1.                                     */
    HT32F_DVB_LEDOn(HT_LED1);
  }
  RSTCU_ClearAllResetFlag();          /* Clear reset flag                                                   */

  {
    /* Enable WDT APB clock                                                                                 */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.WDT = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  while (1)
  {
    #if 1                   /* Disabling WDT_Restart() can lead to WDT generates a reset and turns on LED2. */
    WDT_Restart();          /* Reload Counter as WDTV Value                                                 */
    #endif
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Auto_WDT by programming FLASH OB page.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus AutoWDT_Cmd(ControlStatus NewState)
{
  FLASH_OptionByte ObStatus;
  FLASH_State flashStatus;
  ErrStatus result = SUCCESS;
  u32 OptionByte_WDT;

  /* Get Option Byte status                                                                                 */
  FLASH_GetOptionByteStatus(&ObStatus);
  if(ObStatus.OptionProtect||ObStatus.MainSecurity)
  {
    /* Security or Option Protection is enabled. Can not modify Option.                                     */
    result = ERROR;
  }

  OptionByte_WDT = rw(HTCFG_OB_WDT_ADDR);

  if(NewState == ENABLE)
  {
    if(OptionByte_WDT != HTCFG_OB_WDT_START_CODE)
    {
      /* Before enable Auto WDT, the erase operation should be performed                                    */
      flashStatus = FLASH_EraseOptionByte();
      /* Enable Auto WDT.                                                                                   */
      flashStatus |= FLASH_ProgramWordData(HTCFG_OB_WDT_ADDR, HTCFG_OB_WDT_START_CODE);
      if(flashStatus == FLASH_COMPLETE)
      {
        /* Successful operation and reset the system                                                        */
        NVIC_SystemReset();
      }
      else
      {
        result = ERROR;          /* Fail operation.                                                         */
      }
    }
  }
  else
  {
    /* Diable Auto WDT.                                                                                     */
    if(OptionByte_WDT == HTCFG_OB_WDT_START_CODE)
    {
      /* Disable Auto WDT by erasing option byte.                                                           */
      flashStatus = FLASH_EraseOptionByte();
      if(flashStatus == FLASH_COMPLETE)
      {
        /* Successful operation and reset the system                                                        */
        NVIC_SystemReset();
      }
      else
      {
        result = ERROR;          /* Fail operation.                                                         */
      }
    }
  }

  return result;
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
