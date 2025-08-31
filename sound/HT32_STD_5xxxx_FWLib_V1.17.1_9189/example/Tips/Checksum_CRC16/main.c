/*********************************************************************************************************//**
 * @file    Tips/Checksum_CRC16/main.c
 * @version $Rev:: 7663         $
 * @date    $Date:: 2024-03-25 #$
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

/** @addtogroup Tips_Examples Tips
  * @{
  */

/** @addtogroup Checksum_CRC16
  * @{
  */

/* Private function prototypes -----------------------------------------------------------------------------*/
void Tips_Checksum(void);
void Tips_Checksum_Struct(void);
void Tips_Checksum_HW(void);

/* Private struct prototypes -------------------------------------------------------------------------------*/
typedef struct
{
  u16 uCRCValue; // 0x28
  u16 uKey;      // 0x2A
  u32 uNull[2];  // 0x2C ~ 0x30
  u32 uLength;   // 0x34
} Checksum_TypeDef;


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration();

  Tips_Checksum();
  Tips_Checksum_Struct();
  Tips_Checksum_HW();

  while (1)
  {
  }
}

/*********************************************************************************************************//**
  * @brief  Print CRC Value and AP Length.
  * @retval None
  ***********************************************************************************************************/
void Tips_Checksum(void)
{
  u16 CRC_Value = rw(0x28) & 0x0000FFFF;
  u16 CRC_Key = (rw(0x28) & 0xFFFF0000) >> 16;
  u32 AP_Length = rw(0x34);

  if (CRC_Key == 0x1A0C)
  {
    printf("CRC Value = 0x%04X\r\n", CRC_Value);
    printf("AP Length = %d\r\n\r\n", AP_Length);
  }
  else
  {
    printf("CRC KEY ERROR!\r\n");
  }
}

/*********************************************************************************************************//**
  * @brief  Print CRC Value and AP Length (Struct).
  * @retval None
  ***********************************************************************************************************/
void Tips_Checksum_Struct(void)
{
  Checksum_TypeDef  *ChecksumData = (Checksum_TypeDef *)0x28;

  if (ChecksumData->uKey == 0x1A0C)
  {
    printf("CRC Value = 0x%04X\r\n", ChecksumData->uCRCValue);
    printf("AP Length = %d\r\n\r\n", ChecksumData->uLength);
  }
  else
  {
    printf("CRC KEY ERROR!\r\n");
  }
}

/*********************************************************************************************************//**
  * @brief  Calculate CRC Value.
  * @retval None
  ***********************************************************************************************************/
void Tips_Checksum_HW(void)
{
  #if (LIBCFG_CRC == 1)
  Checksum_TypeDef  *ChecksumData = (Checksum_TypeDef *)0x28;

  if (ChecksumData->uKey == 0x1A0C)
  {
    u32 uPadding = 0xFFFFFFFF;
    u32 uCRCResult;

    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.CRC        = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    uCRCResult = CRC_CCITT(0, (u8 *)0, 40);
    uCRCResult = CRC_CCITT(uCRCResult, (u8 *)&uPadding, 4);
    uCRCResult = CRC_CCITT(uCRCResult, (u8 *)0x0 + 44, 8);
    uCRCResult = CRC_CCITT(uCRCResult, (u8 *)&uPadding, 4);
    uCRCResult = CRC_CCITT(uCRCResult, (u8 *)0x0 + 56, ChecksumData->uLength - 56);

    printf("HW CRC Value = 0x%04X\r\n", uCRCResult);
    printf("Saved CRC Value = 0x%04X\r\n", ChecksumData->uCRCValue);
    printf("AP Length = %d\r\n", ChecksumData->uLength);
    printf("CRC Check ");
    if (ChecksumData->uCRCValue == uCRCResult)
    {
      printf("OK\r\n\r\n");
    }
    else
    {
      printf("FAIL\r\n\r\n");
    }
  }
  else
  {
    printf("CRC KEY ERROR!\r\n");
  }
  #endif
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
