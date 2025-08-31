/*********************************************************************************************************//**
 * @file    delta_sigma_adc.c
 * @version $Rev:: 6412         $
 * @date    $Date:: 2022-11-01 #$
 * @brief   The delta sigma ADC driver.
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
#include "delta_sigma_adc.h"
#include "middleware\i2c_master.h"

/* Private types -------------------------------------------------------------------------------------------*/
typedef union
{
  struct
  {
    unsigned char Res;
    unsigned char Low;
    unsigned char Mid;
    unsigned char High;
  } Byte;
  s32 Data;
} ADC24_Value_TypeDef;

/* Private constants ---------------------------------------------------------------------------------------*/
#define PWRC    0x00
#define PGAC0   0x01
#define PGAC1   0x02
#define PGACS   0x03
#define ADRL    0x04
#define ADRM    0x05
#define ADRH    0x06
#define ADCR0   0x07
#define ADCR1   0x08
#define ADCS    0x09
#define ADCTE   0x0A
#define DAH     0x0B
#define DAL     0x0C
#define DACC    0x0D
#define SIMC0   0x0E
#define SIMTOC  0x10
#define HIRCC   0x11

#define HIRCF           (1 << 1)
#define EOC             (1 << 1)
#define ADCDL           (1 << 2)
#define ADCOFF          (1 << 5)

#define VCMEN_VAL       (VCMEN << 7)
#define FADCK_VAL       (FADCK << 0)
#define VGS_VAL         (VGS   << 5)
#define AGS_VAL         (AGS   << 3)
#define PGS_VAL         (PGS   << 0)

#define INIS_VAL        (INIS  << 6)
#define INX_VAL         (INX   << 4)
#define DCSET_VAL       (DCSET << 1)
#define CHSN_VAL        (CHSN  << 3)
#define CHSP_VAL        (CHSP  << 0)
#define ADOR_VAL        (ADOR  << 1)
#define VREFS_VAL       (VREFS << 0)
#define FLMS_VAL        (FLMS  << 5)
#define VRBUF_VAL       (VRBUF << 3)
#define ADCK_VAL        (ADCK  << 0)

/* Private variables ---------------------------------------------------------------------------------------*/
static u8 ADC24Buffer[2];
static I2CMaster_Typedef I2CMaster = { 0 };

static vu32 gIsDRDYB_IntTrigger = FALSE;
static u32 guSamplingCount = 0;
static ADC24_Value_TypeDef ADCValue;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Init the ADC.
  * @retval None
  ***********************************************************************************************************/
void ADC24_Init(void)
{
  u8 uRegValue = 0;
  I2CMaster_Init(I2C_MASTER_CH0, HTCFG_I2C_MASTER_ADDRESS, HTCFH_I2C_MASTER_CLOCK_SPEED);

  ADC24_WriteReg(HIRCC, 0x01);

  do
  {
    ADC24_ReadReg(HIRCC, &uRegValue, 1);
  } while ((uRegValue & HIRCF) == 0); // Wait HIRC oscillator stable flag

  ADC24_WriteReg(SIMC0,  0x00);
  ADC24_WriteReg(SIMTOC, 0x82);
  ADC24_WriteReg(PWRC,   VCMEN_VAL | FADCK_VAL);
  ADC24_WriteReg(PGAC0,  VGS_VAL | AGS_VAL | PGS_VAL);
  ADC24_WriteReg(PGAC1,  INIS_VAL | INX_VAL | DCSET_VAL);
  ADC24_WriteReg(PGACS,  CHSN_VAL | CHSP_VAL);
  ADC24_WriteReg(ADCR0,  ADOR_VAL | VREFS_VAL);
  ADC24_WriteReg(ADCR1,  FLMS_VAL | VRBUF_VAL);
  ADC24_WriteReg(ADCS,   ADCK_VAL);
  ADC24_WriteReg(ADCTE,  0xE7); // Why??
}

/*********************************************************************************************************//**
  * @brief  Start the ADC conversion.
  * @retval None
  ***********************************************************************************************************/
void ADC24_Start(void)
{
  u8 uRegValue = 0;
  ADC24_ReadReg(ADCR0, &uRegValue, 1);
  ADC24_WriteReg(ADCR0, uRegValue & 0x1F); // ADRST = 0 ADSLP = 0  ADOFF = 0 (ADC power on and enter normal mode)

  ADC24_ReadReg(ADCR0, &uRegValue, 1);
  ADC24_WriteReg(ADCR0, uRegValue | 0x80); // ADRST = 1

  ADC24_ReadReg(ADCR0, &uRegValue, 1);
  ADC24_WriteReg(ADCR0, uRegValue & 0x7F); // ADRST = 0
}

/*********************************************************************************************************//**
  * @brief  Stop the ADC conversion.
  * @retval None
  ***********************************************************************************************************/
void ADC24_Stop(void)
{
  u8 uRegValue = 0;

  ADC24_WriteReg(PWRC, 0x00);
  ADC24_ReadReg(ADCR0, &uRegValue, 1);
  ADC24_WriteReg(ADCR0, uRegValue | ADCOFF);
}

/*********************************************************************************************************//**
  * @brief  Main routine for ADC data read, shall be called regularly.
  * @param  pBuffer: Buffer pointer to save ADC value
  * @retval FALSE (Data not ready) or TRUE (Data ready)
  ***********************************************************************************************************/
u32 ADC24_ReadData_MainRoutine(s32 *pBuffer)
{
  u8 uRegValue = 0;
  u32 uResult = FALSE;

  if (gIsDRDYB_IntTrigger)
  {
    gIsDRDYB_IntTrigger = FALSE;

    ADC24_ReadReg(ADCR1, &uRegValue, 1);
    if (uRegValue & EOC)
    {
      guSamplingCount++;
      if (guSamplingCount > ADC_SKIP_COUNT)
      {
        ADC24_WriteReg(ADCR1, uRegValue | ADCDL);    // ADCDL = 1, lock data for read

        ADC24_ReadReg(ADRL, &ADCValue.Byte.Low, 1);
        ADC24_ReadReg(ADRM, &ADCValue.Byte.Mid, 1);
        ADC24_ReadReg(ADRH, &ADCValue.Byte.High, 1);

        ADC24_WriteReg(ADCR1, uRegValue & (~ADCDL)); // ADCDL = 0, unlock data for ADC convert

        *pBuffer = ADCValue.Data / 256; // Convert to 24-bit signed value
        uResult = TRUE;
      }
      ADC24_WriteReg(ADCR1, uRegValue & (~EOC));
    }
  }

  return uResult;
}

/*********************************************************************************************************//**
  * @brief  Write ADC register (Non-block mode).
  * @param  uAddr: Register address
  * @param  uValue: Register data
  * @retval None
  ***********************************************************************************************************/
void ADC24_WriteRegNonBlock(u32 uAddr, u32 uValue)
{
  ADC24Buffer[0] = uAddr;
  ADC24Buffer[1] = uValue;

  I2CMaster.uSlaveAddress = HFCFG_I2C_SLAVE_ADDRESS;
  I2CMaster.Tx.puBuffer = (u8 *)ADC24Buffer;
  I2CMaster.Tx.uLength = 2;
  I2CMaster.uTimeout_us = 1000000;
  I2CMaster_Write(I2C_MASTER_CH0, &I2CMaster);
}

/*********************************************************************************************************//**
  * @brief  Write ADC register
  * @param  uAddr: Register address
  * @param  uValue: Register data
  * @retval None
  ***********************************************************************************************************/
void ADC24_WriteReg(u32 uAddr, u32 uValue)
{
  ADC24_WriteRegNonBlock(uAddr, uValue);
  ADC24_AccessWaiting();
}

/*********************************************************************************************************//**
  * @brief  Read ADC register (Non-block mode).
  * @param  uAddr: Register address
  * @param  pBuffer: Buffer pointer of register data
  * @param  uLen: Length of read
  * @retval None
  ***********************************************************************************************************/
void ADC24_ReadRegNonBlock(u32 uAddr, u8 *pBuffer, u32 uLen)
{
  ADC24Buffer[0] = uAddr;

  I2CMaster.uSlaveAddress = HFCFG_I2C_SLAVE_ADDRESS;
  I2CMaster.Tx.puBuffer = (u8 *)&ADC24Buffer[0];
  I2CMaster.Tx.uLength = 1;
  I2CMaster.Rx.puBuffer = pBuffer;
  I2CMaster.Rx.uLength = uLen;
  I2CMaster.uTimeout_us = 1000000;

  I2CMaster_WriteRead(I2C_MASTER_CH0, &I2CMaster);
}

/*********************************************************************************************************//**
  * @brief  Read ADC register.
  * @param  uAddr: Register address
  * @param  pBuffer: Buffer pointer of register data
  * @param  uLen: Length of read
  * @retval None
  ***********************************************************************************************************/
void ADC24_ReadReg(u32 uAddr, u8 *pBuffer, u32 uLen)
{
  ADC24_ReadRegNonBlock(uAddr, pBuffer, uLen);
  ADC24_AccessWaiting();
}

/*********************************************************************************************************//**
  * @brief  Wait I2C access finished.
  * @retval None
  ***********************************************************************************************************/
void ADC24_AccessWaiting(void)
{
  I2CMaster_Status_Enum I2CResult = I2C_MASTER_GOING;

  do {
    I2CResult = I2CMaster_GetStatus(I2C_MASTER_CH0);
  } while (I2CResult == I2C_MASTER_GOING);
}

/*********************************************************************************************************//**
  * @brief  Interrupt Handler of ADC.
  * @retval None
  ***********************************************************************************************************/
void ADC24_IRQHandler(void)
{
  gIsDRDYB_IntTrigger = TRUE;
}
