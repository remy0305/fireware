/*********************************************************************************************************//**
 * @file    BM7701_00_1.h_HT32/example_writeAndRead/main.c
 * @version V1.0.1
 * @date    2024-09-23
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

#include "BM7701_00_1.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/

#define TX_POWER     0x0F                   //TX Power
#define XTAL_CLOAD   0x04                   //16MHz Crystal load
#define ADV_MIN      100                    //AdvIntv min=100ms
#define ADV_MAX      100                    //AdvIntv max=100ms
#define CON_MIN      30                     //ConIntv min=30ms
#define CON_MAX      30                     //ConIntv max=30ms
#define CON_LATENCY  00                     //ConIntv latency=00
#define CON_TIMEOUT  300                    //ConIntv timeout=300 
#define BUTTON_CONSISTENCY_DURATION    6
#define BUTTON_REPEAT1_DURATION       (600 / BUTTON_CONSISTENCY_DURATION)
#define BUTTON_REPEAT2_DURATION       (150 / BUTTON_CONSISTENCY_DURATION)
#define INVERT_TIME                   500
bool board_connect = false;
bool board_receive = false;
bool board_conIntv = false;
uint8_t Status;         //BLE status
uint8_t flag=0;
uint8_t count=0;
uint8_t sel = 1;
uint8_t receiveBuf[256] = {0};
uint8_t BDAddress[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66}; //Device address
uint8_t BDName[] = {'B', 'M', 'C', '7', '7', 'M', '0', '0', '1'};//Device name
uint8_t Adata[] = {0x02, 0x01, 0x06}; 					//advertising data
uint8_t Sdata[] = {0x03, 0x02, 0x0f, 0x18};     //scan response data
KEY_MESSAGE Keymessage;
#if defined(USE_BM53A367A_DVB)
/* communication interface----------------------------------------------------------------------------------*/
/* BM53A367A_D13--------------------------------------------------------------------------------------*/
#define   BM7701_00_1_LED_GPIO        STRCAT2(P,            C)
#define   BM7701_00_1_LED_GPIO_ID     STRCAT2(GPIO_P,       C)
#define   BM7701_00_1_LED_AFIO_PIN    STRCAT2(AFIO_PIN_,    11)
#define   BM7701_00_1_LED_GPIO_PORT   STRCAT2(HT_GPIO,      C)
#define   BM7701_00_1_LED_GPIO_PIN    STRCAT2(GPIO_PIN_,    11)
#endif



/*----------------------------------------------------------------------------------------------------------*/
/* USE_HT32F52352_SK                                                                                        */
/*----------------------------------------------------------------------------------------------------------*/
/* ESK32-30501_LED2--------------------------------------------------------------------------------------*/
#if defined(USE_HT32F52352_SK)
#define   BM7701_00_1_LED_GPIO        STRCAT2(P,            C)
#define   BM7701_00_1_LED_GPIO_ID     STRCAT2(GPIO_P,       C)
#define   BM7701_00_1_LED_AFIO_PIN    STRCAT2(AFIO_PIN_,    15)
#define   BM7701_00_1_LED_GPIO_PORT   STRCAT2(HT_GPIO,      C)
#define   BM7701_00_1_LED_GPIO_PIN    STRCAT2(GPIO_PIN_,    15)
#endif
/* Global variables ----------------------------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
void _delay(vu32 count);
void BM7701_00_1_LED_Init(void);
void BM7701_00_1_LED_OUTPUT_HIGH(void);
void BM7701_00_1_LED_OUTPUT_LOW(void);
uint8_t BM7701_00_1_bleProcess(void);
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
	_delay(60);
	RETARGET_Configuration();           //Initialise the serial monitor with a baud rate of 115200
	BM7701_00_1_Init(BM7701_00_1_BAUD_115200);
	BM7701_00_1_reset();
	BM7701_00_1_LED_Init();
	BM7701_00_1_LED_OUTPUT_LOW();
  while (sel != 10)
  {
    switch (sel)
    {
      case 1: if (BM7701_00_1_setAddress(BDAddress) == true) sel++;                        //Set address
        else sel = 0xFF; break;
      case 2: if (BM7701_00_1_setName(sizeof(BDName), BDName) == true) sel++;              //Set Bluetooth Name  (max:31)
        else sel = 0xFF; break;
      case 3: if (BM7701_00_1_setAdvIntv(ADV_MIN / 0.625, ADV_MAX / 0.625, 7) == true) sel++; //Set AdvIntv
        else sel = 0xFF; break;
      case 4: if (BM7701_00_1_setAdvData(BM7701_00_1_APPEND_NAME, sizeof(Adata), Adata) == true) sel++; //Set AdvData
        else sel = 0xFF; break;
      case 5: if (BM7701_00_1_setScanData(sizeof(Sdata), Sdata) == true) sel++;            //Set ScanData
        else sel = 0xFF; break;
      case 6: if (BM7701_00_1_setTXpower(TX_POWER) == true) sel++;                         //Set TX power
        else sel = 0xFF; break;
      case 7: if (BM7701_00_1_setCrystalOffset(XTAL_CLOAD) == true) sel++;                     //Set Xtal Cload
        else sel = 0xFF; break;
      case 8: if (BM7701_00_1_setFeature(BM7701_00_1_FEATURE_DIR,BM7701_00_1_AUTO_SEND_SATUS) == true) sel++;     //Auto Send Satus
        else sel = 0xFF; break;
      case 9: if (BM7701_00_1_setAdvCtrl(BM7701_00_1_ENABLE) == true) sel++;                  //Turn on broadcast
        else sel = 0xFF;
        break;
      case 0xFF: BM7701_00_1_LED_OUTPUT_HIGH();
        break;//Configure fail
		}
		_delay(650);
  }
	while(1)
	{
	Status = BM7701_00_1_bleProcess();                                   //Read BLE status
  if (Status)
  {
    switch (Status)
    {
      case BM7701_00_1_API_CONNECTED:
        if (board_connect == false)
        {
          board_connect = true;
          board_receive = false;
        }
        break;
      case BM7701_00_1_API_DISCONNECTED:
        board_connect = false;
        board_receive = false;
        board_conIntv = false;
        break;
      case BM7701_00_1_DATA_RECEIVED:
        if (board_connect == true)
        {
					BM7701_00_1_LED_OUTPUT_LOW();
          board_receive = true;
        }
        break;
      case BM7701_00_1_API_ERROR:
					BM7701_00_1_LED_OUTPUT_HIGH();
        break;
    }
  }
  if (board_connect == true)
  {
    if (board_conIntv == false)
    {
      BM7701_00_1_wakeUp();
      _delay(30);
      if (BM7701_00_1_setConnIntv1(CON_MIN / 1.25, CON_MAX / 1.25, CON_LATENCY, CON_TIMEOUT) == true) //Set ConIntv
      board_conIntv = true;
    }
    if (board_receive == true)
    {
      board_receive = false;
      if (receiveBuf[3] == 0xB0)
      {
        switch (receiveBuf[4])
        {
          case 0x11:
            count=1;
            printf("KEY1 icon Pushed \r\n");
            break;
          case 0x10:
            count=2; 
            printf("KEY1 icon Released \r\n");
            break;
          case 0x22:
            count=1;
            printf("KEY2 icon Pushed \r\n");
            break;
          case 0x20:
            count=2;
            printf("KEY2 icon Released \r\n");
            break;
          case 0x44:
            count=1;
            printf("KEY3 icon Pushed \r\n");
            break;
          case 0x40:
            count=2; 
            printf("KEY3 icon Released \r\n");
            break;
        }
          if (receiveBuf[4]!=0 && count==2&& flag==0)
          {   
              Keymessage.key = receiveBuf[4]>>4;
              Keymessage.key += receiveBuf[4];
              Keymessage.serial ++;
              Keymessage.checksum = 0xB1 ^ Keymessage.key ^ Keymessage.serial;
              BM7701_00_1_writeData((uint8_t*)&Keymessage,3);
              flag=1;
              receiveBuf[4] = 0;
          }
          if (receiveBuf[4]!=0&&count==2&&flag==1)
          {
              Keymessage.key = receiveBuf[4];
              Keymessage.serial ++;
              Keymessage.checksum = 0xB1 ^ Keymessage.key ^ Keymessage.serial;
              BM7701_00_1_writeData((uint8_t*)&Keymessage,3);   
              flag=0;  
              receiveBuf[4] = 0;         
          }
			}
		}
	}
	}
}
/**********************************************************
 * @brief    Judge the BLE status
 * @param 	 void
 * @retval      API_CONNECTED
                API_DISCONNECTED
                DATA_RECEIVED
                API_ERROR
**********************************************************/
uint8_t BM7701_00_1_bleProcess(void)
{
  uint8_t st = BM7701_00_1_API_ERROR;
  uint8_t lenth = 0;
  BM7701_00_1_readData(receiveBuf, lenth);
  switch (receiveBuf[1])
    {
      case 0x00:
        if (receiveBuf[0] == 0x00)
        {
          if ((receiveBuf[3] & 0x01) == 0x01)
          {
            st = BM7701_00_1_API_CONNECTED;

          }
          else st = BM7701_00_1_API_DISCONNECTED;

        }
        break;
      case 0xF2:
        if ((receiveBuf[0] == 0x00) && (receiveBuf[2] == 0xFF))
        {
          st = BM7701_00_1_DATA_RECEIVED;
        }
        break;
      default: break;
    }
  return st;
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
 * @brief  BM53A367A D13 Init
 * @param  void
 * @retval void
 ************************************************************************************************************/
void BM7701_00_1_LED_Init()
{
	//OUTPUT:D13
	{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.BM7701_00_1_LED_GPIO = 1;
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
	}
	AFIO_GPxConfig(BM7701_00_1_LED_GPIO_ID,BM7701_00_1_LED_AFIO_PIN, AFIO_FUN_GPIO);
	GPIO_DirectionConfig(BM7701_00_1_LED_GPIO_PORT, BM7701_00_1_LED_GPIO_PIN, GPIO_DIR_OUT);
	GPIO_WriteOutBits(BM7701_00_1_LED_GPIO_PORT, BM7701_00_1_LED_GPIO_PIN, SET);
}
/*********************************************************************************************************//**
 * @brief  Raise D13 and light up the LED
 * @param  void
 * @retval void
 ************************************************************************************************************/
void BM7701_00_1_LED_OUTPUT_HIGH(void)
{
		GPIO_WriteOutBits(BM7701_00_1_LED_GPIO_PORT, BM7701_00_1_LED_GPIO_PIN, SET);
}
/*********************************************************************************************************//**
 * @brief  Pull down D13, LED off
 * @param  void
 * @retval void
 ************************************************************************************************************/
void BM7701_00_1_LED_OUTPUT_LOW(void)
{
		GPIO_WriteOutBits(BM7701_00_1_LED_GPIO_PORT, BM7701_00_1_LED_GPIO_PIN, RESET);
}
