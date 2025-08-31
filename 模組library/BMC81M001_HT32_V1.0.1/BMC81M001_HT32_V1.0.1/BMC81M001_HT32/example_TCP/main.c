/*********************************************************************************************************//**
 * @file    BMC81M001.h_HT32/example_TCP/main.c
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

#include "BMC81M001.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/

/* Global variables ----------------------------------------------------------------------------------------*/

#define WIFI_SSID "Hun"
#define WIFI_PASS "kjxxcr520"
#define IP "192.168.58.30"  
#define IP_Port 6000
char writeDataBuff[10]="Hello";
char readDataBuff[30];
/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
void _delay(vu32 count);
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
	RETARGET_Configuration();           //Initialise the serial monitor with a baud rate of 115200
	BMC81M001_Init(BMC81M001_baudRate); // Module initialization using UART communication.
  printf("TCP Connect Result:"); 
	BMC81M001_connectToAP(WIFI_SSID,WIFI_PASS);
  if(BMC81M001_connectTCP(IP,IP_Port)==true)
  {
    printf("TCP success\r\n");
  }  
  else
  {
    printf("TCP fail\r\n");
	}
	BMC81M001_writeDataTcp(5,"HEllo");
	while(1)
	{
    if(BMC81M001_readDataTcp(readDataBuff)==true) 
    {
			printf("%s\r\n",readDataBuff);		
	    BMC81M001_writeDataTcp(8,"received");
    }
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
