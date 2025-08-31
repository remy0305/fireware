/*********************************************************************************************************//**
 * @file    BMC81M001.h_HT32/example_ThingSpeakPublish/main.c
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

#define CLIENTLID  "ADs1HCwzDyUhNwQWGCIWIwk"
#define USERNAME  "ADs1HCwzDyUhNwQWGCIWIwk"          
#define PASSWORD  "TseHgD3olMNq8knpTz4mPMWT"               
#define MQTT_HOST "mqtt3.thingspeak.com"    

#define SERVER_PORT 1883
#define PUBLISHTOPIC "channels/2181120/publish"    
#define SUBSCRIBERTOPIC1 "channels/2181120/subscribe/fields/field1" 
#define SUBSCRIBERTOPIC2 "channels/2181120/subscribe/fields/field2" 
char readDataBuff[200];
char readtopic[100];
int readDataBufflen;
/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
void _delay(vu32 count);
void clearBuff(char array[]);
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
	RETARGET_Configuration();           //Initialise the serial monitor with a baud rate of 115200
	BMC81M001_Init(BMC81M001_baudRate); // Module initialization using UART communication.
	BMC81M001_reset();
	BMC81M001_connectToAP(WIFI_SSID,WIFI_PASS);
	printf("ThingSpeak Connection Results:");
	if(BMC81M001_configMqtt(CLIENTLID, USERNAME, PASSWORD, MQTT_HOST, SERVER_PORT) == true) 
	{
    printf("success\r\n");
  } 
	else 
	{
    printf("fail\r\n");
	}
  BMC81M001_setPublishTopic(PUBLISHTOPIC);
  BMC81M001_setSubscribetopic(SUBSCRIBERTOPIC1);
  BMC81M001_setSubscribetopic(SUBSCRIBERTOPIC2);
	while(1)
	{
		clearBuff(readDataBuff);
	  clearBuff(readtopic);
    BMC81M001_readIotData(readDataBuff,&readDataBufflen,readtopic);
    if(readDataBufflen>0)
        {
					printf("%s\r\n",readtopic);
					printf("%s\r\n",readDataBuff);
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

/*********************************************************************************************************//**
 * @brief  clear array
* @param  array[]:Array that needs to be cleared
 * @retval void
 ************************************************************************************************************/
void clearBuff(char array[])
{
  memset(array,'\0',strlen(array));
}
