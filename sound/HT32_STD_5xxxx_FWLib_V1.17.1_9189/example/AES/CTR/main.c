/*********************************************************************************************************//**
 * @file    AES/CTR/main.c
 * @version $Rev:: 427          $
 * @date    $Date:: 2017-07-04 #$
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
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup AES_Examples AES
  * @{
  */

/** @addtogroup CTR
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define KEY_SIZE              (128/8)
#define BUFF_SIZE             (32)

/* Private variables ---------------------------------------------------------------------------------------*/
__ALIGN4 uc8 gu8KeyTable[KEY_SIZE + 1] = "1234567890123456";                // String end \0 is not included
__ALIGN4 uc8 u8OrgData[BUFF_SIZE + 1] = "abcdefghijklmnopqrstuvwxyz012345"; // String end \0 is not included
__ALIGN4 uc8 u8InitVector[128/8 + 1] = "HOLTEKAESTEST123";                  // String end \0 is not included

__ALIGN4 u8 u8PlainText[BUFF_SIZE];
__ALIGN4 u8 u8CipherText[BUFF_SIZE];

__ALIGN4 u8 u8CipherTextExpect[BUFF_SIZE] =
{
  0x41, 0x2f, 0x68, 0xfa, 0x8d, 0xd6, 0xc0, 0xc5,
  0xac, 0xa8, 0x36, 0x23, 0xba, 0x11, 0x3e, 0x1c,
  0x92, 0xe3, 0x2f, 0x56, 0x42, 0x46, 0x23, 0x04,
  0x33, 0x2e, 0x48, 0x03, 0xf1, 0x2a, 0xd3, 0x9f
};

/* Private function prototypes -----------------------------------------------------------------------------*/
void CKCU_Configuration(void);
void AES_Test(void);
void AES_Result(void);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  AES_InitTypeDef AES_InitStruct = { 0 };

  RETARGET_Configuration();               /* Retarget Related configuration                                 */

  CKCU_Configuration();                   /* System Related configuration                                   */

  BFTM_EnaCmd(HT_BFTM0, ENABLE);

  AES_CTR_Init(HT_AES, &AES_InitStruct);  /* AES CTR Init                                                   */

  /* Set key table, AES supports key size of 128, 192 and 256 bits.                                         */
  AES_SetKeyTable(HT_AES, (u32*)gu8KeyTable, KEY_SIZE);
  /* !!! NOTICE !!!
     The 256-bit AES key length may not support on some HT32 models, please check the datasheet for detailed.
  */

  /* Count AES encryption / decryption time from time zero.                                                 */
  BFTM_SetCounter(HT_BFTM0, 0);

  /* AES encryption / decryption test.                                                                      */
  AES_Test();

  /* Display Result                                                                                         */
  AES_Result();

  while (1);                           /* Infinite loop                                                     */
}

/*********************************************************************************************************//**
  * @brief  AES encryption / decryption test.
  * @retval None
  ***********************************************************************************************************/
void AES_Test(void)
{
  /* Encryption                                                                                             */
  if (!AES_CTR_CryptData(HT_AES, (u32*)u8InitVector, BUFF_SIZE, (u32*)u8OrgData, (u32*)u8CipherText))
  {
    /* Input length must be a multiple of 16                                                                */
     printf("ENCRYPT Error\r\n");
  }

  /* Decryption                                                                                             */
  if (!AES_CTR_CryptData(HT_AES, (u32*)u8InitVector, BUFF_SIZE, (u32*)u8CipherText, (u32*)u8PlainText))
  {
    /* Input length must be a multiple of 16                                                                */
    printf("DECRYPT Error\r\n");
  }
}

/*********************************************************************************************************//**
  * @brief  Show AES result.
  * @retval None
  ***********************************************************************************************************/
void AES_Result(void)
{
  int i;
  int isError = 0;
  int TestTime = BFTM_GetCounter(HT_BFTM0)/(SystemCoreClock/1000000);

  printf("index   OrgData   Ciphertext   CipherExpect   Plaintext \r\n");
  printf("--------------------------------------\r\n");
  for (i = 0; i < BUFF_SIZE; i++)
  {
    if (u8CipherText[i] == u8CipherTextExpect[i])
    {
      printf("%03d     |0x%02X     |0x%02X        |0x%02X          |0x%02X\r\n", i + 1, u8OrgData[i], u8CipherText[i], u8CipherTextExpect[i], u8PlainText[i]);
    }
    else
    {
      isError = 1;
      printf("%03d     |0x%02X     |0x%02X        |0x%02X X         |0x%02X\r\n", i + 1, u8OrgData[i], u8CipherText[i], u8CipherTextExpect[i], u8PlainText[i]);
    }
  }
  printf("--------------------------------------\r\n");
  if (isError == 1)
  {
    printf("!!! AES Test ERROR !!!\r\n");
  }
  else
  {
    printf("AES Test Pass\r\n");
  }
  printf("Encryption/Decryption time = %d us\r\n\r\n", TestTime);
}

/*********************************************************************************************************//**
  * @brief  Configure the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.AES        = 1;
  CKCUClock.Bit.BFTM0      = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
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
