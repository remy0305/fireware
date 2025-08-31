/*********************************************************************************************************//**
 * @file    BMC81M001.h_HT32/example_ONENET/main.c
 * @version V1.0.1
 * @date    2024-09-30
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


#define CLIENTLID "wifi" 
#define USERNAME "cekQZv1EU5"
#define PASSWORD "version=2018-10-31&res=products%2FcekQZv1EU5%2Fdevices%2Fwifi&et=1748654171&method=md5&sign=3Ywcz76x73Hfuhe0%2FrE8hA%3D%3D"
#define MQTT_HOST "mqtts.heclouds.com"             
#define SERVER_PORT 1883
#define ONENET_TOPIC_PROP_POST "$sys/cekQZv1EU5/wifi/thing/property/post"
#define ONENET_TOPIC_PROP_SET "$sys/cekQZv1EU5/wifi/thing/property/set"
#define ONENET_TOPIC_PROP_POST_REPLY "$sys/cekQZv1EU5/wifi/thing/property/post/reply"
#define ONENET_TOPIC_PROP_SET_REPLY "$sys/cekQZv1EU5/wifi/thing/property/set_reply"
#define ONENET_TOPIC_PROP_GET "$sys/cekQZv1EU5/wifi/thing/property/get"
#define ONENET_TOPIC_PROP_GET_REPLY "$sys/cekQZv1EU5/wifi/thing/property/get_reply"   

#define String "Hello" 
char SET_BUF[200];
char readDataBuff[200];
char readTopic[30];
char num[5];
int Data_int=35;
float Temperature=27.50;
int readDataBufflen;
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
	BMC81M001_Init(115200); // Module initialization using UART communication.
  BMC81M001_reset(); 
	BMC81M001_connectToAP(WIFI_SSID,WIFI_PASS);
	printf("ONENET Connection Results:");
	if(BMC81M001_configMqtt(CLIENTLID, USERNAME, PASSWORD, MQTT_HOST, SERVER_PORT) == true) 
	{
    printf("success\r\n");
  } 
	else 
	{
    printf("fail\r\n");
	}
  BMC81M001_setSubscribetopic(ONENET_TOPIC_PROP_SET);
  BMC81M001_setSubscribetopic(ONENET_TOPIC_PROP_GET);
  BMC81M001_setSubscribetopic(ONENET_TOPIC_PROP_GET_REPLY);
  BMC81M001_setSubscribetopic(ONENET_TOPIC_PROP_SET_REPLY);
  BMC81M001_setSubscribetopic(ONENET_TOPIC_PROP_POST_REPLY);
  //Single upload
	BMC81M001_arrayAdd(SET_BUF,"{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"temp\":{\"value\":");
	sprintf(num,"%04.2f ", Temperature);
	BMC81M001_arrayAdd(SET_BUF,num);
	BMC81M001_arrayAdd(SET_BUF,"},\"String\":{\"value\":\"");
	BMC81M001_arrayAdd(SET_BUF,"Hello");
	BMC81M001_arrayAdd(SET_BUF,"\"},\"humi\":{\"value\":");
	sprintf(num,"%2d", Data_int);
	BMC81M001_arrayAdd(SET_BUF,num);
	BMC81M001_arrayAdd(SET_BUF,"}}}\r\n");
	if(BMC81M001_writeByte(SET_BUF,strlen(SET_BUF),ONENET_TOPIC_PROP_POST)==true)
  {
   printf("Send data sucess\r\n");
  }
	else
	{
   printf("Send data fail\r\n");
	}
	while(1)
	{
    BMC81M001_readIotData(readDataBuff,&readDataBufflen,readTopic);
		if(readDataBufflen>0)
    {
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
