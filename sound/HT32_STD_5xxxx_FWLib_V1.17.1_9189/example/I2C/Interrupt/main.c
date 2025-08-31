/*********************************************************************************************************//**
 * @file    I2C/Interrupt/main.c
 * @version $Rev:: 5456         $
 * @date    $Date:: 2021-07-06 #$
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

/** @addtogroup I2C_Examples I2C
  * @{
  */

/** @addtogroup I2C_Interrupt
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define I2C_MASTER_ADDRESS     0x0A
#define I2C_SLAVE_ADDRESS      0x60
#define BufferSize             4
#define ClockSpeed             100000

/* Private function prototypes -----------------------------------------------------------------------------*/
void I2CMaster_Configuration(void);
void I2CSlave_Configuration(void);
void I2C_Loopback(void);
ErrStatus CmpBuffer(u8* Buffer1, u8* Buffer2, u32 BufferLength);

/* Private variables ---------------------------------------------------------------------------------------*/
u8 I2C0_Master_Buffer_Tx[BufferSize] = {0x1, 0x2, 0x3, 0x4};
u8 I2C0_Master_Buffer_Rx[BufferSize];
u8 I2C1_Slave_Buffer_Rx[BufferSize];
vu8 I2C0_Master_Tx_Index = 0;
vu8 I2C0_Master_Rx_Index = 0;
vu8 I2C1_Slave_Tx_Index = 0;
vu8 I2C1_Slave_Rx_Index = 0;

vu32 IsMasterRxFinish = FALSE;

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  HT32F_DVB_LEDInit(HT_LED1);
  HT32F_DVB_LEDInit(HT_LED2);

  I2CMaster_Configuration();
  I2CSlave_Configuration();

  /* The I2C master-slave state is checked by interrupt and data is sent from the master to the slave.      */
  I2C_Loopback();

  while (1);
}

/*********************************************************************************************************//**
  * @brief  Configure the I2C.
  * @retval None
  ***********************************************************************************************************/
void I2CMaster_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.I2C0 = 1;
    CKCUClock.Bit.AFIO = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO as I2C function                                                                         */
  AFIO_GPxConfig(I2C_MASTER_SCL_GPIO_ID, I2C_MASTER_SCL_AFIO_PIN, AFIO_FUN_I2C);
  AFIO_GPxConfig(I2C_MASTER_SDA_GPIO_ID, I2C_MASTER_SDA_AFIO_PIN, AFIO_FUN_I2C);

  { /* I2C Master configuration                                                                             */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    I2C_InitTypeDef  I2C_InitStructure;

    I2C_InitStructure.I2C_GeneralCall = DISABLE;
    I2C_InitStructure.I2C_AddressingMode = I2C_ADDRESSING_7BIT;
    I2C_InitStructure.I2C_Acknowledge = DISABLE;
    I2C_InitStructure.I2C_OwnAddress = I2C_MASTER_ADDRESS;
    I2C_InitStructure.I2C_Speed = ClockSpeed;
    I2C_InitStructure.I2C_SpeedOffset = 0;
    I2C_Init(I2C_MASTER_PORT, &I2C_InitStructure);
  }

  /* Enable I2C Matser interrupts                                                                           */
  I2C_IntConfig(I2C_MASTER_PORT, I2C_INT_STA | I2C_INT_ADRS | I2C_INT_RXDNE | I2C_INT_TXDE, ENABLE);
  NVIC_EnableIRQ(I2C0_IRQn);

  I2C_Cmd(I2C_MASTER_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Configure the I2C.
  * @retval None
  ***********************************************************************************************************/
void I2CSlave_Configuration(void)
{
  { /* Enable peripheral clock                                                                              */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.I2C1 = 1;
    CKCUClock.Bit.AFIO = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* Configure AFIO as I2C function                                                                         */
  AFIO_GPxConfig(I2C_SLAVE_SCL_GPIO_ID, I2C_SLAVE_SCL_AFIO_PIN, AFIO_FUN_I2C);
  AFIO_GPxConfig(I2C_SLAVE_SDA_GPIO_ID, I2C_SLAVE_SDA_AFIO_PIN, AFIO_FUN_I2C);

  { /* I2C Slave configuration                                                                              */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    I2C_InitTypeDef  I2C_InitStructure;

    I2C_InitStructure.I2C_GeneralCall = DISABLE;
    I2C_InitStructure.I2C_AddressingMode = I2C_ADDRESSING_7BIT;
    I2C_InitStructure.I2C_Acknowledge = ENABLE;
    I2C_InitStructure.I2C_OwnAddress = I2C_SLAVE_ADDRESS;
    I2C_InitStructure.I2C_Speed = 0;
    I2C_InitStructure.I2C_SpeedOffset = 0;
    I2C_Init(I2C_SLAVE_PORT, &I2C_InitStructure);
  }

  /* Enable I2C Slave interrupts                                                                            */
  I2C_IntConfig(I2C_SLAVE_PORT, I2C_INT_ADRS | I2C_INT_RXDNE | I2C_INT_TXDE | I2C_INT_RXNACK, ENABLE);
  NVIC_EnableIRQ(I2C1_IRQn);

  I2C_Cmd(I2C_SLAVE_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  The I2C master-slave state is checked by interrupt and data is sent from the master to the slave.
  * @retval None
  ***********************************************************************************************************/
void I2C_Loopback(void)
{
  /* Send I2C START & I2C slave address for write                                                           */
  I2C_TargetAddressConfig(I2C_MASTER_PORT, I2C_SLAVE_ADDRESS, I2C_MASTER_WRITE);

  /* Wait until all data transmission is complete                                                           */
  while (!IsMasterRxFinish);

  /* Check on validity of received data on I2C Master & I2C Slave                                           */
  if (CmpBuffer(I2C0_Master_Buffer_Rx, I2C1_Slave_Buffer_Rx, BufferSize) == SUCCESS)
  {
    HT32F_DVB_LEDOn(HT_LED1);
  }
  else
  {
    HT32F_DVB_LEDOn(HT_LED2);
  }
}

/*********************************************************************************************************//**
  * @brief  Compare two buffers.
  * @param  Buffer1, Buffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval SUCCESS or ERROR
  ***********************************************************************************************************/
ErrStatus CmpBuffer(u8* Buffer1, u8* Buffer2, u32 BufferLength)
{
  while (BufferLength--)
  {
    if (*Buffer1 != *Buffer2)
    {
      return ERROR;
    }

    Buffer1++;
    Buffer2++;
  }

  return SUCCESS;
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
