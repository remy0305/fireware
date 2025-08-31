/*********************************************************************************************************//**
 * @file    BMC81M001_HT32/src/BMC81M001.c
 * @version V1.0.1
 * @date    2024-10-10
 * @brief   The function of BMC81M001 driver.
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
uint32_t gBMC81M001_SERIAL = BMC81M001_SERIAL;
uint8_t BMC81M001_dataBuff[25];
/* Private variables ---------------------------------------------------------------------------------------*/
uint8_t _BMC81M001_len;     //Length of data reveviced
uint8_t _BMC81M001_state;   
uint8_t _BMC81M001_sum;
uint8_t _BMC81M001_checksum;//Checksum of data reveviced     
uint8_t _BMC81M001_res;
char BMC81M001_Response[RES_MAX_LENGTH];
int resLength = 0;
uint8_t uselessBuff[200];
char OneNetReciveBuff[200];
/* Global functions ----------------------------------------------------------------------------------------*/

/*********************************************************************************************************//**
 * @brief module serial number select.
 * @param serial_number: select serial number.
 * @retval BMC81M001_FAILURE/BMC81M001_SUCCESS
 ************************************************************************************************************/
BMC81M001_selStatus BMC81M001_selSerial(uint32_t serial_number)
{
  if(CHECK_SERIALn(serial_number) == -1)
  {
    return BMC81M001_FAILURE;
  }
  gBMC81M001_SERIAL = serial_number;
  return BMC81M001_SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Module initialization using UART communication.
* @param  BaudRate:Development board communication speed
 * @retval void
 ************************************************************************************************************/
void BMC81M001_Init(uint32_t BaudRate)
{

	USART_InitTypeDef USART_InitStructure = {0};
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
  UARTM_Init(gBMC81M001_SERIAL, &USART_InitStructure, BMC81M001_UART_TXTIMEOUT);
}
/*********************************************************************************************************//**
 * @brief  Connect to AP network.
* @param   ssid:The ID of the AP network
					 pass:Network password
* @retval Communication status
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_connectToAP(char ssid[],char pass[])
{  
  char  cmd[200] = "AT+CWJAP=\"";
  /* <AT+CWMODE=1> command to Set station mode   */
  if( BMC81M001_sendATCommand("AT+CWMODE=1\r\n",3) ==  BMC81M001_SEND_SUCCESS ) ;
  else 
  {
    return false;
  }
  /* <AT+CWJAP="ssid","password"> add to AP  */
	BMC81M001_arrayAdd(cmd,ssid);
  BMC81M001_arrayAdd(cmd,"\",\"");
  BMC81M001_arrayAdd(cmd,pass);
  BMC81M001_arrayAdd(cmd,"\"\r\n");
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS ) 
  {  
    return true;
  }
  else 
  {
    return false;
  } 
}
/*********************************************************************************************************//**
 * @brief Connect to TCP server
* @param  ip:IP address for connecting to TCP server
					port:Connection port
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_connectTCP(char ip[],int port)
{  
  char  cmd[200] = "AT+CIPSTART=\"TCP\",\"";
  char  num[5];
	BMC81M001_arrayAdd(cmd,ip);
	BMC81M001_arrayAdd(cmd,"\",");
	sprintf(num,"%d", port);
	BMC81M001_arrayAdd(cmd,num);
  BMC81M001_arrayAdd(cmd,"\r\n");
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS )
  {
    return true;
  }
  else 
  {
    return false;
  } 
}
/*********************************************************************************************************//**
* @brief Sending data to TCP server
* @param  Dlength:Data length
					Dbuffer:Data to be sent to TCP server
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_writeDataTcp(int Dlength,char Dbuffer[])
{
  char  cmd[200] = "AT+CIPSEND=";
  char  num[2];
	sprintf(num,"%d", Dlength);
	BMC81M001_arrayAdd(cmd,num);
	BMC81M001_arrayAdd(cmd,"\r\n");
  if(BMC81M001_sendATCommand(cmd,4) == BMC81M001_SEND_SUCCESS ) ;
  else 
  {
  return false;
  } 
  _BMC81M001_delay(100);
  if(BMC81M001_sendATCommand(Dbuffer,3) == BMC81M001_SEND_SUCCESS )  
  {  
    return true;
  }
  else 
  {
    return false;
  } 
}
/*********************************************************************************************************//**
 * @brief  Read data issued by TCP server
* @param   readbuff:Data to be read to TCP server
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_readDataTcp(char readbuff[])
{
  int index;  
	char *position;
	int i,length=0;
	BMC81M001_clearResponse(BMC81M001_Response);
	if(UARTM_GetReadBufferLength(gBMC81M001_SERIAL)>0)
	{
		BMC81M001_readBytes((u8*)BMC81M001_Response,200,3);
	}
  if(strstr(BMC81M001_Response, "+IPD") != NULL)
  {
		length=strlen(BMC81M001_Response);
		position = strchr(BMC81M001_Response,':');
		index = position - BMC81M001_Response;
		length=length-index;
		for(i=0;i<length;i++)
		{
			readbuff[i]=BMC81M001_Response[i+index+1];
		}
		return true;
  }
	return false;
}
/*********************************************************************************************************//**
 * @brief  Configure MQTT connection parameters
* @param   clientlid,username,password,mqtt_host,server_port 
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_configMqtt(char clientid[],char username[],char password[],char mqtt_host[],int server_port)
{
/**********************************************************  
Description: Set mqtt user properties
command:     At+mqttusercfg=<linkid>, <scheme>, < "client\u ID" >, <username ">, <password" >, <cert_ Key_ Id>, <ca_ Id>, < "path" >
**********************************************************/
  char  cmd[200]="AT+MQTTUSERCFG=0,1,\"NULL\",\"NULL\",\"NULL\",0,0,\"\"\r\n";
	
  char  cmdCLIENTID[200]="AT+MQTTCLIENTID=0,\"";
  char  cmdUSERNAME[100]="AT+MQTTUSERNAME=0,\"";
  char  cmdPASSWORD[200]="AT+MQTTPASSWORD=0,\"";
	char  num[5];
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS ) ;
  else 
  {
    return false;
  }   
/**********************************************************
Description: Set mqtt client ID
command:     AT+MQTTCLIENTID=<LinkID>,<"client_id">
**********************************************************/
  BMC81M001_arrayAdd(cmdCLIENTID,clientid);
  BMC81M001_arrayAdd(cmdCLIENTID,"\"\r\n");
  if(BMC81M001_sendATCommand(cmdCLIENTID,3) == BMC81M001_SEND_SUCCESS ) ;
  else 
  {
    return false;
  }   
/**********************************************************
Description: Set mqtt username
command:     AT+MQTTUSERNAME=<LinkID>,<"username">
**********************************************************/
  BMC81M001_arrayAdd(cmdUSERNAME,username);
  BMC81M001_arrayAdd(cmdUSERNAME,"\"\r\n");
  if(BMC81M001_sendATCommand(cmdUSERNAME,3) == BMC81M001_SEND_SUCCESS ) ;
  else 
  {
    return false;
  } 
/**********************************************************
Description: Set mqtt userpassword
command:     AT+MQTTPASSWORD=<LinkID>,<"password">
**********************************************************/
  BMC81M001_arrayAdd(cmdPASSWORD,password);
  BMC81M001_arrayAdd(cmdPASSWORD,"\"\r\n");
  if(BMC81M001_sendATCommand(cmdPASSWORD,3) == BMC81M001_SEND_SUCCESS) ;
  else 
  {
    return false;
  } 
/**********************************************************
Description: Connect  MQTT Broker
command:     AT+MQTTCONN=<LinkID>,<"host">,<port>,<reconnect>
**********************************************************/
  memset(cmd,'\0',200);
	strcpy(cmd,"AT+MQTTCONN=0,\"");
	BMC81M001_arrayAdd(cmd,mqtt_host);
  BMC81M001_arrayAdd(cmd,"\",");
	sprintf(num,"%d",server_port);
	BMC81M001_arrayAdd(cmd,num);
  BMC81M001_arrayAdd(cmd,",0\r\n");
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS )
  {  
    return true;
  }
  else 
  {
    return false;
  } 
}
/*********************************************************************************************************//**
 * @brief  Subscribe to publish relevant TOPIC
* @param   publishtopic:Topic of platform release
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_setPublishTopic(char publishtopic[])
{
  char  cmd[200]="AT+MQTTSUB=0,\"";
	BMC81M001_arrayAdd(cmd,publishtopic);
  BMC81M001_arrayAdd(cmd,"\",0\r\n");
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS )
  {  
    return true;
  }
  else 
  {
    return false;
  } 
}
/*********************************************************************************************************//**
 * @brief  Subscription topics on the platform
* @param   subscribetopic:Topic of Subscribe
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_setSubscribetopic(char subscribetopic[])
{
  char  cmd[200]="AT+MQTTSUB=0,\"";
	BMC81M001_arrayAdd(cmd,subscribetopic);
  BMC81M001_arrayAdd(cmd,"\",0\r\n");
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS )
  {  
    return true;
  }  
  else 
  {
    return false;
  } 
}
/*********************************************************************************************************//**
 * @brief  Set custom TOPIC
* @param   topic:custom TOPIC
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_setTopic(char topic[])
{
  char  cmd[200]="AT+MQTTSUB=0,\"";
	BMC81M001_arrayAdd(cmd,topic);
  BMC81M001_arrayAdd(cmd,"\",0\r\n");
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS )
  {  
    return true;
  }  
  else 
  {
    return false;
  } 
}
/*********************************************************************************************************//**
* @brief Send data to Internet platform
* @param  Dbuffer:custom TOPIC
					Dlength:Data length
					topic:Target topic for sending
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_writeByte(char Dbuffer[],int Dlength,char topic[])
{
  char  cmd[200] = "AT+MQTTPUBRAW=0,\"";
	char  num[2];
  BMC81M001_arrayAdd(cmd,topic);
  BMC81M001_arrayAdd(cmd,"\",");
	sprintf(num,"%d", Dlength);
  BMC81M001_arrayAdd(cmd,num);
  BMC81M001_arrayAdd(cmd,",0,0\r\n");
  if(BMC81M001_sendATCommand(cmd,3) == BMC81M001_SEND_SUCCESS )
	{
		BMC81M001_sendATCommand(Dbuffer,3);
	}
  else 
  {
    return false;
  } 	
  return true;
}
/*********************************************************************************************************//**
* @brief  read data to Internet platform
* @param  IotReciveBuff:read data
					*IotReciveBufflen:Data length
					topic:Data source topic
* @retval void
 ************************************************************************************************************/
void BMC81M001_readIotData(char IotReciveBuff[],int *IotReciveBufflen,char IotReciveTopic[])
{
	uint8_t i =0;
	int position=0;	
	int length=0;
	*IotReciveBufflen=0;
  BMC81M001_clearResponse(BMC81M001_Response);
	if(UARTM_GetReadBufferLength(gBMC81M001_SERIAL))
	{
		_BMC81M001_delay(10);
		while(UARTM_GetReadBufferLength(gBMC81M001_SERIAL) != 0)
		{
		 UARTM_ReadByte(gBMC81M001_SERIAL,(u8*)BMC81M001_Response+resLength);
			resLength++;	
			if(resLength==RES_MAX_LENGTH)
			{
				BMC81M001_clearResponse(BMC81M001_Response);
			}
			if(strstr(BMC81M001_Response,"\r\n") != NULL)
			{
				break;
			}
		}
	}
  if(strstr(BMC81M001_Response,"+MQTTSUBRECV") != NULL)
  {
		position = BMC81M001_arrayFind(BMC81M001_Response,'"');
		length=strlen(BMC81M001_Response);
    for(i=0;i<length-position;i++)
		{
      BMC81M001_Response[i]=BMC81M001_Response[i+position+1];;
			OneNetReciveBuff[i]=BMC81M001_Response[i+position];;  
		}	
		position = BMC81M001_arrayFind(BMC81M001_Response,'"');
		length=strlen(BMC81M001_Response);
    for( i=0;i<position;i++)
		{
			IotReciveTopic[i]=BMC81M001_Response[i];
		}
    for( i=0;i<length-position;i++)
		{
			IotReciveBuff[i]=BMC81M001_Response[i+position+2];
		}
		position = BMC81M001_arrayFind(IotReciveBuff,',');
		*IotReciveBufflen=IotReciveBuff[position-1];
		length=strlen(IotReciveBuff);
    for( i=0;i<length-position;i++)
		{
			IotReciveBuff[i]=IotReciveBuff[i+position+1];
		}
	}		
}
/*********************************************************************************************************//**
* @brief  BMC81M001 write Bytes with UART
* @param  wbuf:Data that needs to be written
* @retval void
 ************************************************************************************************************/
void BMC81M001_writeBytes(char wbuf[])
{
		uint8_t len = 0;
		uint8_t i = 0;
		len=strlen(wbuf);
		if(len>128)
		{
			for(i=0;i<len-125;i++)
			{
				OneNetReciveBuff[i]=wbuf[125+i];
			}
			UARTM_Write(gBMC81M001_SERIAL,(u8*)wbuf,125);
			_BMC81M001_delay(2);
			UARTM_Write(gBMC81M001_SERIAL,(u8*)OneNetReciveBuff,len-125);
			BMC81M001_clearResponse(OneNetReciveBuff);
		}
		else
		{		
			UARTM_Write(gBMC81M001_SERIAL,(u8*)wbuf,len);
		}
}
/*********************************************************************************************************//**
* @brief  Reset module
* @param  void
* @retval Communication status  
					@arg true:SEND_Success 
					@arg false:SEND_FAIL 
 ************************************************************************************************************/
bool BMC81M001_reset(void)
{  
  if(BMC81M001_sendATCommand("AT+RST\r\n",3) == BMC81M001_SEND_SUCCESS )
  {
    BMC81M001_clearResponse(BMC81M001_Response);
    _BMC81M001_delay(2000) ;        // Issue soft-reset command
  }
  else 
  {
			return false;
  }
  return true;
}
/*********************************************************************************************************//**
 * @brief  Send AT related instructions
 * @param  @arg StringstrCmd:Instructions that need to be sent to the module
					 @arg reTry:Repeated sending times
 * @retval BMC81M001_SEND_FAIL/BMC81M001_SEND_SUCCESS
 ************************************************************************************************************/

int BMC81M001_sendATCommand(char StringstrCmd[],uint8_t reTry)
{
  char response[]="OK";
	uint8_t time=0;
	uint8_t i=0;
	uint8_t tryTime = 0;
  for(tryTime = 0; tryTime < reTry; tryTime++)
  {  
		time=0;
		BMC81M001_readBytes(uselessBuff,10,1);
		BMC81M001_clearResponse(BMC81M001_Response);
		BMC81M001_writeBytes(StringstrCmd);
  /* check the reply message within the timeout period. If the reply message contains preset characters,  return success  */
    for(i=0;;i++)
    {
			time++;
		  BMC81M001_readBytes((u8*)BMC81M001_Response,100,time);		
      if(strstr(BMC81M001_Response,response) != NULL)
      {	
        return BMC81M001_SEND_SUCCESS;
      }		
      if(time==4)
      {
        break;
      }      
		}
	}
	return BMC81M001_SEND_FAIL;
}
/*********************************************************************************************************//**
* @brief  read data with UART
* @param  rbuf:data
					timeout:Waiting for timeout
					reTry:Repeated sending times
* @retval void
 ************************************************************************************************************/
void BMC81M001_readBytes(uint8_t rbuf[],int timeout, uint8_t reTry)
{
	unsigned char tryTime = 0;
	uint32_t _delayCount = 0;
  char response[]="OK";
  for(tryTime = 0; tryTime < reTry; tryTime++)
{
	for(_delayCount = 0; _delayCount<timeout; _delayCount++)
	{
		while(UARTM_GetReadBufferLength(gBMC81M001_SERIAL) != 0)
		{
		 UARTM_ReadByte(gBMC81M001_SERIAL,rbuf+resLength);
			resLength++;	
			if(resLength==RES_MAX_LENGTH)
			{
				BMC81M001_clearResponse(BMC81M001_Response);
			}
			if(strstr(BMC81M001_Response,response) != NULL)
      {	
				break;
      }	
		}
		_BMC81M001_delay(1);
	}
}
}

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief  clear Buff.
 * @param  void
 * @retval void
 ************************************************************************************************************/
void _BMC81M001_clearBuf(void)
{
	int a = 0;
  for(a = 0; a < 12; a++)
  {
  } 
}

/*********************************************************************************************************//**
 * @brief  delay ms.
 * @param  count
 * @retval void
 ************************************************************************************************************/
void _BMC81M001_delay(vu32 count)
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}


/**********************************************************
 * @brief  clear Response
* @param  Dbuffer:Array that needs to be cleared
 * @retval void      
**********************************************************/
void BMC81M001_clearResponse(char Dbuffer[])
{
  memset(Dbuffer,'\0',RES_MAX_LENGTH);
  resLength = 0;
}
/**********************************************************
 * @brief  add two array
* @param  array1,array2
 * @retval void       
**********************************************************/
void BMC81M001_arrayAdd(char array1[],char array2[])
{
	int length1;
	int length2;
	int i=0;
	length1=strlen(array1);
	length2=strlen(array2);
	for(i=0;i<length2;i++)
	{
	  array1[i+length1]=array2[i];
	}
}
/**********************************************************
 * @brief charbuff add
* @param  Search for characters in array one and return the sequence of the first occurrence
 * @retval position      
**********************************************************/
int BMC81M001_arrayFind(char array1[],char array2)
{
	int length;
	int i=0;
	int position=0;
	length=strlen(array1);
	for(i=0;i<length;i++)
	{
	  if(array1[i]==array2)
		{
			position=i;
			i=length;
		}
	}
	return position;
}
