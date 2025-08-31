/*********************************************************************************************************//**
 * @file    BMS56M605_HT32/example_readAccelerationAndGyroscopeAndTemperature/main.c
 * @version V1.0.1
 * @date    2024-08-08
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
#include "BMS56M605.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
void _delay(vu32 count);
extern float BMS56M605_temperature;
extern float BMS56M605_accX, BMS56M605_accY, BMS56M605_accZ;
extern float BMS56M605_gyroX, BMS56M605_gyroY, BMS56M605_gyroZ;
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
	RETARGET_Configuration();           //Initialise the serial monitor with a baud rate of 115200
	BMS56M605_Init();                   //Initialise module
	
	while(1)
	{
		BMS56M605_getEvent();
		printf("Temp = ");
		printf("%.2f ",BMS56M605_temperature);
		printf("'/C \r\n");
		
		printf("ax = ");
		printf("%.2f ",BMS56M605_accX);
		printf("ay = ");
		printf("%.2f ",BMS56M605_accY);
		printf("az = ");
		printf("%.2f ",BMS56M605_accZ);
		printf(" g \r\n");
		
		printf("gx = ");
		printf("%.2f ",BMS56M605_gyroX);
		printf("gy = ");
		printf("%.2f ",BMS56M605_gyroY);
		printf("gz = ");
		printf("%.2f ",BMS56M605_gyroZ);
		printf(" '/s \r\n");
		
		_delay(1000);
		
	}
}



/*********************************************************************************************************//**
 * @brief  delay ms.
 * @param  count
 * @retval void
 ************************************************************************************************************/
void _delay(vu32 count)
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}

