/*************************************************************************************************************
 * @file    BME34M101_HT32/src/BME34M101.c
 * @version V1.0.1
 * @date    2024-10-10
 * @brief   The function of BME34M101 driver.
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
#include "BME34M101.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
#if (CHECK_SERIALn(BME34M101_SERIAL) == -1)
#error "Error: BME34M101_SERIAL doesn't support the current SERIAL number. Check ht32_board_config.h."
#endif
/* Global variables ----------------------------------------------------------------------------------------*/
uint32_t gBME34M101_SERIAL = BME34M101_SERIAL;

/* Private variables ---------------------------------------------------------------------------------------*/
uint8_t _gBME34M101_moduleNumber = 0;

/* Global functions ----------------------------------------------------------------------------------------*/
/************************************************************************************************************
 * @brief module serial part number select.
 * @param serial_number: select serial number.
 * @retval BME34M101_SUCCESS/BME34M101_FAILURE
 ************************************************************************************************************/
BME34M101_selStatus BME34M101_selSerial(uint32_t serial_number)
{
	if (CHECK_SERIALn(serial_number) == -1)
	{
		return BME34M101_FAILURE;
	}
	gBME34M101_SERIAL = serial_number;
	return BME34M101_SUCCESS;
}

/***********************************************************************************************************
 * @brief  Module initialization using I2C communication.
 * @param  void
 * @retval void
 ************************************************************************************************************/
void BME34M101_Init(void)
{
	USART_InitTypeDef USART_InitStructure = {0};
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
	USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
	USART_InitStructure.USART_Parity = USART_PARITY_NO;
	USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
	UARTM_Init(gBME34M101_SERIAL, &USART_InitStructure, BME34M101_UART_TXTIMEOUT);
}
/***********************************************************************************************************
 * @brief  Is the modules ready.
 * @param  void
 * @retval true(1): Connected; flase(0): Disconnect
 ************************************************************************************************************/
bool BME34M101_isConnected(void)
{
	uint8_t i, retval,  sendBuf[3] = {0x00, 0x12, 0x00}; // CMD code: 0x12
	uint8_t recBuf[3] = {0};
	sendBuf[0] = (BME34M101_BROADCAST_ID << 4) + 2;
	for (i = 0; i < 2; i++)
	{
		sendBuf[2] += sendBuf[i];
	}
	BME34M101_writeBytes(sendBuf, 3);
	_BME34M101_delayMs(40); // Response delay time
	retval = BME34M101_readBytes(recBuf, 3);
	if (retval == BME34M101_READ_OK)
	{
		if (recBuf[1] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/***********************************************************************************************************
 * @brief  Get the number of modules.
 * @param  void
 * @retval Number of cascaded modules 
 ************************************************************************************************************/
uint8_t BME34M101_getNumber(void)
{
	uint8_t i, retval, sendBuf[3] = {0x00, 0x11, 0x00}; // CMD code: 0x11
	uint8_t recBuf[4] = {0};
	sendBuf[0] = (BME34M101_BROADCAST_ID << 4) + 2;
	for (i = 0; i < 2; i++)
	{
		sendBuf[2] += sendBuf[i];
	}
	BME34M101_writeBytes(sendBuf, 3);
	_BME34M101_delayMs(40); //Response delay time
	retval = BME34M101_readBytes(recBuf, 4);
	if (retval == BME34M101_READ_OK)
	{
		_gBME34M101_moduleNumber = recBuf[2];
	}
	else
	{
		_gBME34M101_moduleNumber = 0;
	}
	return _gBME34M101_moduleNumber;
}

/***********************************************************************************************************
 * @brief  Get the module soil moisture detection value
 * @param  id: module id
 * @retval soil moisture detection value
 ************************************************************************************************************/
uint8_t BME34M101_getMoisture(uint8_t id)
{
	uint8_t i, retval, sendBuf[3] = {0x00, 0x01, 0x00}; // CMD code: 0x01
	uint8_t recBuf[4] = {0};
	sendBuf[0] = (id << 4) + 2;
	for (i = 0; i < 2; i++)
	{
		sendBuf[2] += sendBuf[i];
	}
	BME34M101_writeBytes(sendBuf, 3);
	_BME34M101_delayMs(40); // Response delay time
	retval = BME34M101_readBytes(recBuf, 4);
	if (retval == BME34M101_READ_OK)
	{
		return recBuf[2];
	}
	else
	{
		return 0;
	}
}

/***********************************************************************************************************
 * @brief  Get the module soil temperature detection value
 * @param  id: module id
 * @retval soil temperature detection value
 ************************************************************************************************************/
uint8_t BME34M101_getTemperature(uint8_t id)
{
	uint8_t i, retval, sendBuf[3] = {0x00, 0x02, 0x00}; // CMD code: 0x01
	uint8_t recBuf[4] = {0};
	sendBuf[0] = (id << 4) + 2;
	for (i = 0; i < 2; i++)
	{
		sendBuf[2] += sendBuf[i];
	}
	BME34M101_writeBytes(sendBuf, 3);
	_BME34M101_delayMs(40); // Response delay time
	retval = BME34M101_readBytes(recBuf, 4);
	if (retval == BME34M101_READ_OK)
	{
		return recBuf[2];
	}
	else
	{
		return 0;
	}
}

/***********************************************************************************************************
 * @brief  Get the module soil moisture detection value
 * @param  moisBuff：The array that stores all soil moisture detection values
 * @retval void
 ************************************************************************************************************/
void BME34M101_getAllMoisture(uint8_t moisBuff[])
{
	uint8_t i, retval, sendBuf[3] = {0x00, 0x01, 0x00}; // CMD code: 0x01
	uint8_t recLen = 0, recBuf[8] = {0};
	sendBuf[0] = (BME34M101_BROADCAST_ID << 4) + 2;
	for (i = 0; i < 2; i++)
	{
		sendBuf[2] += sendBuf[i];
	}
	recLen = _gBME34M101_moduleNumber + 4;
	BME34M101_writeBytes(sendBuf, 3);
	_BME34M101_delayMs(40); // Response delay time
	retval = BME34M101_readBytes(recBuf, recLen);
	if (retval == BME34M101_READ_OK)
	{
		for (i = 0; i <= _gBME34M101_moduleNumber; i++)
		{
			moisBuff[i] = recBuf[i + 2];
		}
	}
	else
	{
		for (i = 0; i <= _gBME34M101_moduleNumber; i++)
		{
			moisBuff[i] = 0;
		}
	}
}

/***********************************************************************************************************
 * @brief  Get the module soil temperature detection values
 * @param  tempBuff: The array that stores all temperature detection values
 * @retval void
 ************************************************************************************************************/
void BME34M101_getAllTemperature(uint8_t tempBuff[])
{
	uint8_t i, retval, sendBuf[3] = {0x00, 0x02, 0x00}; // CMD code: 0x02
	uint8_t recLen = 0, recBuf[8] = {0};
	sendBuf[0] = (BME34M101_BROADCAST_ID << 4) + 2;
	for (i = 0; i < 2; i++)
	{
		sendBuf[2] += sendBuf[i];
	}
	recLen = _gBME34M101_moduleNumber + 4;
	BME34M101_writeBytes(sendBuf, 3);
	_BME34M101_delayMs(40); // Response delay time
	retval = BME34M101_readBytes(recBuf, recLen);
	if (retval == BME34M101_READ_OK)
	{
		for (i = 0; i <= _gBME34M101_moduleNumber; i++)
		{
			tempBuff[i] = recBuf[i + 2];
		}
	}
	else
	{
		for (i = 0; i <= _gBME34M101_moduleNumber; i++)
		{
			tempBuff[i] = 0;
		}
	}
}
/***********************************************************************************************************
 * @brief  write data through UART.
 * @param  wbuf:Variables for storing Data to be sent
					 wlen:Length of data sent
 * @retval void
 ************************************************************************************************************/
void BME34M101_writeBytes(uint8_t wbuf[], uint8_t wlen)
{
	UARTM_Write(gBME34M101_SERIAL, wbuf, wlen);
}

/***********************************************************************************************************
 * @brief  read data through UART.
 * @param  rbuf:Variables for storing Data to be obtained
					 rlen:Length of data to be obtained
 * @retval BME34M101_READ_OK / BME34M101_CHECK_ERROR / BME34M101_TIMEOUT_ERROR
 ************************************************************************************************************/
uint8_t BME34M101_readBytes(uint8_t rbuf[], uint8_t rlen)
{
	uint8_t i = 0, _delayCount = 0;
	uint8_t checkSum = 0, sumTmp = 0;
	for (i = 0; i < rlen; i++)
	{
		_delayCount = 0;
		while (UARTM_GetReadBufferLength(gBME34M101_SERIAL) == 0)
		{
			if (_delayCount > BME34M101_UART_RXTIMEOUT_BYTE)
			{
				return BME34M101_TIMEOUT_ERROR;
			}
			_BME34M101_delayMs(1);
			_delayCount++;
		}
		UARTM_ReadByte(gBME34M101_SERIAL, rbuf + i);
	}
	// Check
	if (rbuf[1] == 0x00)
	{
		checkSum = rbuf[rlen - 1];
		for (i = 0; i < (rlen - 1); i++)
		{
			sumTmp += rbuf[i];
		}
		if (sumTmp == checkSum)
		{
			return BME34M101_READ_OK; // Check sum correct!
		}
		else
		{
			return BME34M101_CHECK_ERROR; // Check sum incorrect
		}
	}
	else
	{
		return BME34M101_CHECK_ERROR;
	}
}

/* Private functions ---------------------------------------------------------------------------------------*/
/***********************************************************************************************************
 * @brief  delay ms.
 * @param  count:unit ms
 * @retval void
 ************************************************************************************************************/
void _BME34M101_delayMs(uint32_t count)
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}
