/*************************************************************************************************************
 * @file    BME34M101_HT32/example_getMoistureAndTemperature/main.c
 * @version V1.0.1
 * @date    2024-10-10
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
#include "BME34M101.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------------------*/
uint8_t i, id, moisture, temperature;
/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
void _delay(vu32 count);
/***********************************************************************************************************
 * @brief  Main program.
 * @retval None
 ***********************************************************************************************************/
int main(void)
{
  RETARGET_Configuration(); // Initialise the serial monitor with a baud rate of 115200
  BME34M101_Init();         // Module initialization using UART communication.
  _delay(200);
  i = 0;
  id = 1;
  if (BME34M101_isConnected() == true)
  {
    printf("Module connected.\r\n");
  }
  else
  {
    printf("Module not connected.\r\n");
  }
  while (1)
  {
    moisture = BME34M101_getMoisture(id);
    temperature = BME34M101_getTemperature(id);
    printf("Moisture: %d\r\n", moisture); //Unit: %RH
    printf("Temperature: %d\r\n", temperature); // Unit: degrees Celsius
    printf("\r\n");
    _delay(1000);
  }
}

/* Private functions ---------------------------------------------------------------------------------------*/
/***********************************************************************************************************
 * @brief  delay ms.
 * @param  count
 * @retval void
 ************************************************************************************************************/
void _delay(vu32 count)
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}

