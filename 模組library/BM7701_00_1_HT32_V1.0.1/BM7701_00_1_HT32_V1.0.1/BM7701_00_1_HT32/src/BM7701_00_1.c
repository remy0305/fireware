/*********************************************************************************************************//**
 * @file    BM7701_00_1_HT32/src/BM7701_00_1.c
 * @version V1.0.1
 * @date    2024-09-23
 * @brief   The function of BM7701_00_1 driver.
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
#include "BM7701_00_1.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------------------*/
uint32_t gBM7701_00_1_SERIAL = BM7701_00_1_SERIAL;
uint8_t BM7701_00_1_dataBuff[25];
/* Private variables ---------------------------------------------------------------------------------------*/
uint8_t _BM7701_00_1_len;     //Length of data reveviced
uint8_t _BM7701_00_1_state;   
uint8_t _BM7701_00_1_sum;
uint8_t _BM7701_00_1_checksum;//Checksum of data reveviced     
uint8_t _BM7701_00_1_res;
uint8_t receive_data[256]; 
uint8_t len;
/* Global functions ----------------------------------------------------------------------------------------*/

/*********************************************************************************************************//**
 * @brief module serial number select.
 * @param serial_number: select serial number.
 * @retval BM7701_00_1_FAILURE/BM7701_00_1_SUCCESS
 ************************************************************************************************************/
BM7701_00_1_selStatus BM7701_00_1_selSerial(uint32_t serial_number)
{
  if(CHECK_SERIALn(serial_number) == -1)
  {
    return BM7701_00_1_FAILURE;
  }
  gBM7701_00_1_SERIAL = serial_number;
  return BM7701_00_1_SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Module initialization using UART communication.
 * @param  BaudRate:Communication speed
 * @retval void
 ************************************************************************************************************/
void BM7701_00_1_Init(uint32_t BaudRate)
{

	USART_InitTypeDef USART_InitStructure = {0};
  USART_InitStructure.USART_BaudRate = BaudRate;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_NO;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
  UARTM_Init(gBM7701_00_1_SERIAL, &USART_InitStructure, BM7701_00_1_UART_TXTIMEOUT);
}
/*********************************************************************************************************//**
 * @brief  Turn on broadcast
 * @param  BM7701_00_1_ENABLE:OPEN
           BM7701_00_1_DISABLE:close 
 * @retval true:reply true event
           false:reply false event
 ************************************************************************************************************/
bool BM7701_00_1_setAdvCtrl(bool ctrl)
{
   bool flag = false;
   uint8_t Adven[6]={0x77,0x04,0x00,0x07,0x00,0x00};
	 Adven[5]=ctrl;
   BM7701_00_1_writeBytes(Adven,6);  
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x07 && receive_data[2]==0x00)
      {
        flag = true;
      }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Disconnect
 * @param  void
 * @retval true:reply true event
           false:reply false event
 ************************************************************************************************************/
bool BM7701_00_1_disconnect(void)
{
  bool flag = false;
  uint8_t Disconn[5]={0x77,0x03,0x00,0x02,0x00};
  BM7701_00_1_writeBytes(Disconn,5);
	_BM7701_00_1_delay(150);
  if(BM7701_00_1_readData(receive_data,len)==true)
  {
    if(receive_data[0]==0x00 && receive_data[1]==0x02 && receive_data[2]==0x00)
     {
        flag = true;
     }  
  }
  return flag;
}
/*********************************************************************************************************//**
 * @brief  BC7701 Send Data 
 * @param  length: <128 byte 
           dataBuf:The array to be sent
 * @retval true:reply true event
           false:reply false event
 ************************************************************************************************************/
bool BM7701_00_1_writeData(uint8_t dataBuf[],uint8_t length)
{
	 bool flag = false;
   uint8_t i;
   uint8_t data[255]= {0x77,0x00,0x20,0xF1,0xFF,0xb1};
   for(i=0;i<length;i++)
   {
    data[6+i]=dataBuf[i];
   }
   data[1]=length+4;
   BM7701_00_1_writeBytes(data,length+6);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
    if(receive_data[0]==0x20 && receive_data[1]==0xF1 && receive_data[2]==0xFF)
     {
       flag = true;
     }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  BC7701 raed Data 
 * @param  receiveBuff[]:Received array
					 length:Received array length
 * @retval true:reply true event
           false:reply false event
 ************************************************************************************************************/
bool BM7701_00_1_readData(uint8_t receiveBuff[],uint8_t length)
{
	uint8_t receive[256]={0};
  BM7701_00_1_readBytes(receive,2); 
  length=receive[1];
  if(BM7701_00_1_readBytes(receiveBuff,length)==BM7701_00_1_READ_OK)
	{
		return true;
	}
  return false;
}
/*********************************************************************************************************//**
 * @brief  Set Advertise Interval
 * @param  min: Minimum time parameter for broadcast interval, range: 0x0020~0x4000
					 max: Maximum time parameter for broadcast interval, range: 0x0020~0x4000
					 advMap: Broadcast channel (can simultaneously open multiple channels)
						Bit0=1: Channel37 (2402MHz) switch control
						Bit0=1: Enable
						Bit0=0: Off
						Bit1=1: Channel38 (2426MHz) switch control
						Bit1=1: Enable
						Bit1=0: Closed
						Bit2=1: Channel39 (2480MHz) switch control
						Bit2=1: Enable
						Bit2=0: Closed
 * @retval true:reply true event
           false:reply false event
 ************************************************************************************************************/
bool BM7701_00_1_setAdvIntv(uint16_t min,uint16_t max,uint8_t advMap)
{
	 bool flag = false; 
   uint8_t advintv[10]={0x77,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00};
   advintv[5] = (uint8_t)min;
   advintv[6] = (uint8_t)(min>>8);
   advintv[7] = (uint8_t)max;
   advintv[8] = (uint8_t)(max>>8);
   advintv[9] = advMap;
	 BM7701_00_1_writeBytes(advintv,10); 
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x08 && receive_data[2]==0x00)
      {
        flag = true;
      }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set Advertise Data
 * @param  appendName:
							0x00 (BM7701_00_1_APPENDNAME): Attached data
							0x10 (BM7701_00_1_NOAPPENDNAME): No data attached
					 length: byte length of advdata []
					 AdvData []: Data, the byte length of advData [] needs to be < 32 bytes
					 when appendName=0x00, it contains advData+other attribute information
					 when appendName=0x10, only advData is included      
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setAdvData(uint8_t appendName,uint8_t length,uint8_t AdvData[])
{
	 bool flag = false;
   uint8_t i;
   uint8_t data[128] = {0x77,0x00,0x00,0x09,0x00};
   if(length >31)
	 {
		 length = 31;
	 }
   for(i=0;i<length;i++)
   {
    data[5+i]=AdvData[i];
   }
   data[1]=length+3;
	 data[2]=appendName;
   BM7701_00_1_writeBytes(data,length+5);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
     {
      if(receive_data[0]==0x00 && receive_data[1]==0x09 && receive_data[2]==0x00)
      {
        flag = true;
      }
    }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set Scan Data
 * @param  Length: The byte length of scanData []
					 scanData []: The format is data byte length+data type+data, <32 bytes        
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setScanData(uint8_t length,uint8_t scanData[])
{
	 bool flag = false;
   uint8_t i;
   uint8_t data[128] = {0x77,0x00,0x00,0x0A,0x00};
   if(length >31)length = 31;
   for(i=0;i<length;i++)
   {
    data[5+i]=scanData[i];
   }
   data[1]=length+3;
   BM7701_00_1_writeBytes(data,length+5);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
    if(receive_data[0]==0x00 && receive_data[1]==0x0A && receive_data[2]==0x00)
     {
       flag = true;
     }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set Connected Interval
* @param  Interval: communication interval time parameter, range: 0x0006~0x0c80          
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setConnIntv(uint16_t interval)
{
	 bool flag = false;
   uint8_t connintv[7]={0x77,0x05,0x00,0x03,0x00,0x00,0x00};
   connintv[5]= (uint8_t)interval;
   connintv[6]= (uint8_t)(interval>>8);
   BM7701_00_1_writeBytes(connintv,7);  
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
     if(receive_data[0]==0x00 && receive_data[1]==0x03 && receive_data[2]==0x00)
      {
        flag = true;
      }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set Connected Interval (more detail)
 * @param  MinIntv: Minimum interval time parameter, range: 0x0006~0x0c80
					 MaxIntv: Maximum interval time parameter, range: 0x0006~0x0c80
					 Latency: Time parameter for device delay in sending, range: 0x0000~0x01f3
					 Timeout: Connection timeout parameter, range: 0x0000~0x0c80        
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setConnIntv1(uint16_t minIntv,uint16_t maxIntv,uint16_t latency,uint16_t timeout)
{
	 bool flag = false;
   uint8_t connintv1[13]={0x77,0x0B,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
   connintv1[5] = (uint8_t)minIntv;
   connintv1[6] = (uint8_t)(minIntv>>8);
   connintv1[7] = (uint8_t)maxIntv;
   connintv1[8] = (uint8_t)(maxIntv>>8);
   connintv1[9] = (uint8_t)latency;
   connintv1[10] = (uint8_t)(latency>>8);
   connintv1[11] = (uint8_t)timeout;
   connintv1[12] = (uint8_t)(timeout>>8); 
   BM7701_00_1_writeBytes(connintv1,13);  
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x04 && receive_data[2]==0x00)
      {
        flag = true;
      }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set BLE Name
 * @param  length: number of bytes for Bluetooth name
					 name []: Bluetooth name                 
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setName(uint8_t length,uint8_t name[])
{
	 bool flag = false;
   uint8_t i;
   uint8_t setname[128] = {0x77,0x00,0x00,0x05,0x00};  
   if(length >31)length = 31;
   for(i=0;i<length;i++)
   {
    setname[5+i]=name[i];
   }
   setname[1]=length+3;
   BM7701_00_1_writeBytes(setname,length+5);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x05 && receive_data[2]==0x00)
      {
        flag = true;
      }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set  MAC address
 * @param  Address[]: 6byte address                   
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setAddress(uint8_t address[])
{
	 bool flag = false;
   uint8_t i;
   uint8_t setaddr[128] = {0x77,0x09,0x00,0x06,0x00};
   for(i=0;i<6;i++)
   {
    setaddr[5+i]=address[i];
   }
   BM7701_00_1_writeBytes(setaddr,11);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x06 && receive_data[2]==0x00)
      {
        flag = true;
      }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set Feature
 * @param  CmdFlag: Data Writing Method
					0x00 (BM7701_00_1_FEATURE-DIR): Overwrite the previous value
					0x10 (BM7701_00_1_FEATURE-OR): Write 'OR' to the previous value
					0x20 (BM7701_00_1_FEATURE_SND): Write 'AND' to the previous value
					codeFeature:4byte, Please refer to BLE-API specification 4.14API-Feature for specific details
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setFeature(uint8_t cmdFlag,uint32_t codeFeature)
{
   bool flag = false;
   uint8_t FR[9]={0x77,0x07,0x00,0x10,0x00,0x00,0x00,0x00,0x00};  
	 FR[2] =cmdFlag;
	 FR[5] = (uint8_t)codeFeature;
	 FR[6] = (uint8_t)(codeFeature>>8);
	 FR[7] = (uint8_t)(codeFeature>>16);
	 FR[8] = (uint8_t)(codeFeature>>24);
	 BM7701_00_1_writeBytes(FR,9);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x10 && receive_data[2]==0x00)
      {
       flag = true;
      }
	 }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set module energy-saving mode
 * @param  mode: Energy saving mode
						0x00: Sleep (default)
						0x01: Deep Sleep
						0x15: Shutdown, maintain deep sleep, wake-up will force reset, all settings in RAM Reset to default value             
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setPowerSaving(uint8_t mode)
{
   bool flag = false;
   uint8_t PS[6]={0x77,0x04,0x00,0x25,0x00,0x00};
	 PS[5]=mode;
   BM7701_00_1_writeBytes(PS,6);  
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x25 && receive_data[2]==0x00)
      {
        flag = true;
      }  
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set Whilelist Address
 * @param  Erase: Action to be taken on the whitelist
						  @arg True: Add
							@arg False: delete
				   WhiteListAddr []: Device address to be added to the whitelist (6 bytes)
					 Mask []: Address mask, default value inside the module is 0xFFFFFFFF
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setWhiteList(bool erase,uint8_t whiteListAddr[],uint8_t mask[])
{
	 bool flag = false;
   uint8_t i;
   uint8_t WL[128]={0x77,0x0F,0x00,0x2A,0x00};
   if(erase==ENABLE)
    WL[2]=0x10;
   else
    WL[2]=0x00;
   for(i=0;i<6;i++)
   {
    WL[5+i]=whiteListAddr[i];
   } 
   for(i=0;i<6;i++)
   {
    WL[11+i]=mask[i];
   }
   BM7701_00_1_writeBytes(WL,17);  
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x2A && receive_data[2]==0x00)
      {
        flag = true;
      } 
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set TX power
 * @param  power:Transmission power level, range: 0x00 (min)~0x0F (max)
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setTXpower(uint8_t power)
{
   bool flag = false;
   uint8_t setpower[6]={0x77,0x04,0x00,0x0B,0x00,0x00};
	 setpower[5]=power;
   BM7701_00_1_writeBytes(setpower,6);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x0B && receive_data[2]==0x00)
      {
        flag = true;
      }
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Set Xtal Cload 
 * @param  cload:RF output frequency offset, range 0x00~0x0f 
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_setCrystalOffset(uint8_t cload)
{
   bool flag = false;
   uint8_t setcload[6]={0x77,0x04,0x00,0x0E,0x00,0x00};
	 setcload[5]=cload;
   BM7701_00_1_writeBytes(setcload,6);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[0]==0x00 && receive_data[1]==0x0E && receive_data[2]==0x00)
      {
        flag = true;
      } 
   }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Software reset, restore default values after reset
 * @param  void
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_restoreDefault(void)
{
  bool flag = false; 
  uint8_t swreset[13]= {0x77,0x0B,0x00,0x28,0x00,0x32,0x30,0x32,0x36,0x00,0x03,0x00,0x00};
  BM7701_00_1_writeBytes(swreset,13);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
  {
    if(receive_data[0]==0x00 && receive_data[1]==0x28 && receive_data[2]==0x00)
    {
        flag = true;
    }
  }
  return flag;
}
/*********************************************************************************************************//**
 * @brief  software Reset,save configuration 
 * @param  void
 * @retval      true:reply true event
                false:reply false event      
 ************************************************************************************************************/
bool BM7701_00_1_reset(void)
{
  bool flag = false;
  uint8_t Wdtreset[6]= {0x77,0x04,0x00,0x28,0x00,0x00};
  BM7701_00_1_writeBytes(Wdtreset,6);
	_BM7701_00_1_delay(150);
  if(BM7701_00_1_readData(receive_data,len)==true)
  {    
   if(receive_data[0]==0x00 && receive_data[1]==0x28 &&  receive_data[2]==0x00)
     {
        flag = true;
				_BM7701_00_1_delay(60);
     }
  }
   return flag;
}
/*********************************************************************************************************//**
 * @brief  Dummy wake up from deepsleep/powerdown mode 
 * @param  void
 * @retval void    
 ************************************************************************************************************/
void BM7701_00_1_wakeUp(void)
{
     uint8_t buff[2];
     buff[0]=0x00;
     buff[1]=0x00;
     BM7701_00_1_writeBytes(buff,2);
		 _BM7701_00_1_delay(30);
}
/**********************************************************
 * @brief  	Send Command to BM7701_00_1 with waiting evt
 * @param  type: Type (UUID/Profile/Service/Characteristics/Descriptor)
					 cmd_flag: flag for API command
					 cmd_length: byte length of type+value+cmd_flag
					 value []: Command Data Buffer
 * @retval  true:reply true event
            false:reply false event         
**********************************************************/
bool BM7701_00_1_sendCMD(uint16_t type,uint8_t cmd_flag,uint8_t cmd_length,uint8_t value[])
{
   uint8_t i;
   bool flag = false;
   uint8_t cmd[128]= {0x77,0x00,0x00,0x00,0x00};
   cmd_length=cmd_length+3;
	 cmd[1]=cmd_length;
	 cmd[2]=cmd_flag;
	 cmd[3]=(uint8_t)type;
	 cmd[4]=(uint8_t)(type>>8);
   for(i=0;i<cmd_length;i++)
   {
    cmd[5+i]=value[i];
   }
   BM7701_00_1_writeBytes(cmd,cmd_length+5);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[1]==cmd[3] && receive_data[2]==cmd[4])
     {
       flag = true;
     }
   }    
   return flag;
}

/**********************************************************
 * @brief  Send Command to BM7701_00_1 with no waiting evt
 * @param type: Type (UUID/Profile/Service/Characteristics/Descriptor)
					cmd_flag: flag for API command
					cdm_length: byte length of type+value+cmd_flag
					value []: Command Data Buffer  
 * @retval void     
**********************************************************/
void BM7701_00_1_sendCMD_NoResponse(uint16_t type,uint8_t cmd_flag,uint8_t cmd_length,uint8_t value[])
{
   uint8_t i;
   uint8_t cmd[128]= {0x77,0x00,0x00,0x00,0x00};
   cmd_length=cmd_length+3;
	 cmd[1]=cmd_length;
	 cmd[2]=cmd_flag;
	 cmd[3]=(uint8_t)type;
	 cmd[4]=(uint8_t)(type>>8);
   for(i=0;i<cmd_length;i++)
   {
    cmd[5+i]=value[i];
   }
   BM7701_00_1_writeBytes(cmd,cmd_length+5); 
}
/**********************************************************
 * @brief  Read Command to BM7701_00_1 with waiting evt
 * @param type: Type (UUID/Profile/Service/Characteristics/Descriptor)
					cmd_flag: flag for API command
 * @retval  true:reply true event
            false:reply false event     
**********************************************************/
bool BM7701_00_1_readCMD(uint16_t type,uint8_t cmd_flag)
{
   bool flag = false;
   uint8_t cmd[5]= {0x77,0x03,0x00,0x00,0x00};
	 cmd[2]=cmd_flag;
	 cmd[3]=(uint8_t)type;
	 cmd[4]=(uint8_t)(type>>8);
   BM7701_00_1_writeBytes(cmd,5);
	 _BM7701_00_1_delay(150);
   if(BM7701_00_1_readData(receive_data,len)==true)
   {
      if(receive_data[1]==cmd[3] && receive_data[2]==cmd[4])
      {
        flag = true;
      }
   }
   return flag;
}
/**********************************************************
 * @brief  Read Command to BM7701_00_1 with waiting no evt
 * @param type: Type (UUID/Profile/Service/Characteristics/Descriptor)
					cmd_flag: flag for API command 
 * @retval  true:reply true event
            false:reply false event     
**********************************************************/
void BM7701_00_1_readCMD_NoResponse(uint16_t type,uint8_t cmd_flag)
{
   uint8_t cmd[5]= {0x77,0x03,0x00,0x00,0x00};
	 cmd[2]=cmd_flag;
	 cmd[3]=(uint8_t)type;
	 cmd[4]=(uint8_t)(type>>8);
   BM7701_00_1_writeBytes(cmd,5); 
}
/*********************************************************************************************************//**
 * @brief  write data through UART.
 * @param  wbuf:Variables for storing Data to be sent
 * @param  wlen:Length of data sent
 * @retval void  
 ************************************************************************************************************/
void BM7701_00_1_writeBytes(uint8_t wbuf[], uint8_t wlen)
{
	  UARTM_Write(gBM7701_00_1_SERIAL,wbuf,wlen);
}

/*********************************************************************************************************//**
 * @brief  read data through UART.
 * @param  rbuf:Variables for storing Data to be obtained
					 rlen:Length of data to be obtained
 * @retval BM7701_00_1_READ_OK/BM7701_00_1_READ_ERROR/BM7701_00_1_NO_ACK/BM7701_00_1_TIMEOUT_ERROR 
 ************************************************************************************************************/
uint8_t BM7701_00_1_readBytes(uint8_t rbuf[], uint8_t rlen)
{
	uint8_t _lenCount = 0;
	uint8_t _delayCount = 0;
  uint8_t fReceive;
	for(_lenCount = 0; _lenCount < rlen; _lenCount++)
	{
		_delayCount = 0;
		while(UARTM_GetReadBufferLength(gBM7701_00_1_SERIAL) == 0)
		{
			if(_delayCount >BM7701_00_1_UART_RXTIMEOUT_BYTE)
			{
				return BM7701_00_1_TIMEOUT_ERROR;
			}
			_BM7701_00_1_delay(1);
			_delayCount++;
		}
		UARTM_ReadByte(gBM7701_00_1_SERIAL,rbuf+_lenCount);
	}
  if(rbuf[1]!=0)
         {
            fReceive = BM7701_00_1_READ_OK;
         }
         else 
         {fReceive = BM7701_00_1_READ_ERROR;}    
    return  fReceive;
}

/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief  clear Buff.
 * @param  void
 * @retval void
 ************************************************************************************************************/
void _BM7701_00_1_clearBuf(void)
{
	int a = 0;
  for(a = 0; a < 12; a++)
  {
    BM7701_00_1_dataBuff[a] = 0;
  } 
}

/*********************************************************************************************************//**
 * @brief  delay ms.
 * @param  count
 * @retval void
 ************************************************************************************************************/
void _BM7701_00_1_delay(vu32 count)
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}




