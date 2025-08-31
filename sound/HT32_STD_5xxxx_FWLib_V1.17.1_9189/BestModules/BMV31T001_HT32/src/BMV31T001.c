/*********************************************************************************************************//**
 * @file    BBMV31T001_HT32/src/BBMV31T001.c
 * @version V1.0.1
 * @date    2024-08-01
 * @brief    BMV31T001  playback and download
 *************************************************************************************************************/
 
#include "BMV31T001.h"
#include "delay.h"
#include "usb/USB_VCP.h"


#define BMV31T001_CS_PORT  		HT_GPIOC    //SPI CS
#define BMV31T001_CS_PIN  		GPIO_PIN_10
#define BMV31T001_CS_AFPORT  		GPIO_PC
#define BMV31T001_CS_AFPIN  		AFIO_PIN_10

#define BMV31T001_SCK_PORT  		HT_GPIOC  //SPI SCK
#define BMV31T001_SCK_PIN  		GPIO_PIN_11
#define BMV31T001_SCK_AFPORT  		GPIO_PC
#define BMV31T001_SCK_AFPIN  		AFIO_PIN_11
#define BMV31T001_ICPCK_PORT  		HT_GPIOC   //switch mode timing
#define BMV31T001_ICPCK_PIN  		GPIO_PIN_11
#define BMV31T001_ICPCK_AFPORT  		GPIO_PC
#define BMV31T001_ICPCK_AFPIN  		AFIO_PIN_11


#define BMV31T001_MOSI_PORT  		HT_GPIOC   //SPI MOSI
#define BMV31T001_MOSI_AFPORT  		GPIO_PC
#define BMV31T001_MOSI_AFPIN  		AFIO_PIN_8
#define BMV31T001_MOSI_PIN  		GPIO_PIN_8
#define BMV31T001_ICPDA_PORT  		HT_GPIOC  //switch mode timing
#define BMV31T001_ICPDA_AFPORT  		GPIO_PC
#define BMV31T001_ICPDA_AFPIN  		AFIO_PIN_8
#define BMV31T001_ICPDA_PIN  		GPIO_PIN_8



#define BMV31T001_MISO_PORT  		HT_GPIOC   //SPI MISO
#define BMV31T001_MISO_PIN  		GPIO_PIN_9
#define BMV31T001_MISO_AFPORT  		GPIO_PC
#define BMV31T001_MISO_AFPIN  		AFIO_PIN_9
#define BMV31T001_DATA_PORT  		HT_GPIOC        //one wire
#define BMV31T001_DATA_PIN  		GPIO_PIN_9
#define BMV31T001_DATA_AFPORT  		GPIO_PC
#define BMV31T001_DATA_AFPIN  		AFIO_PIN_9


#define BMV31T001_KEY_UP_PORT  	HT_GPIOC
#define BMV31T001_KEY_UP_PIN  	GPIO_PIN_3
#define BMV31T001_KEY_UP_AFPORT  		GPIO_PC
#define BMV31T001_KEY_UP_AFPIN  		AFIO_PIN_3

#define BMV31T001_KEY_LEFT_PORT  	HT_GPIOD
#define BMV31T001_KEY_LEFT_PIN  	GPIO_PIN_4
#define BMV31T001_KEY_LEFT_AFPORT  		GPIO_PD
#define BMV31T001_KEY_LEFT_AFPIN  		AFIO_PIN_4

#define BMV31T001_KEY_DOWN_PORT  	HT_GPIOC
#define BMV31T001_KEY_DOWN_PIN  	GPIO_PIN_2
#define BMV31T001_KEY_DOWN_AFPORT  		GPIO_PC
#define BMV31T001_KEY_DOWN_AFPIN  		AFIO_PIN_2

#define BMV31T001_KEY_RIGHT_PORT  HT_GPIOC
#define BMV31T001_KEY_RIGHT_PIN  	GPIO_PIN_5
#define BMV31T001_KEY_RIGHT_AFPORT  		GPIO_PC
#define BMV31T001_KEY_RIGHT_AFPIN  		AFIO_PIN_5

#define BMV31T001_KEY_MIDDLE_PORT  HT_GPIOC
#define BMV31T001_KEY_MIDDLE_PIN  GPIO_PIN_4
#define BMV31T001_KEY_MIDDLE_AFPORT  		GPIO_PC
#define BMV31T001_KEY_MIDDLE_AFPIN  		AFIO_PIN_4

//#define POWER_PIN	A0
#define BMV31T001_POWER_PORT  HT_GPIOC
#define BMV31T001_POWER_PIN	GPIO_PIN_1
#define BMV31T001_POWER_AFPORT  		GPIO_PC
#define BMV31T001_POWER_AFPIN  		AFIO_PIN_1

#define BMV31T001_LED_PORT		HT_GPIOA
#define BMV31T001_LED_PIN		GPIO_PIN_14
#define BMV31T001_LED_AFPORT  		GPIO_PA
#define BMV31T001_LED_AFPIN  		AFIO_PIN_14



#define BMV31T001_STATUS_PORT	HT_GPIOA
#define BMV31T001_STATUS_PIN	GPIO_PIN_15
#define BMV31T001_STATUS_AFPORT  		GPIO_PA
#define BMV31T001_STATUS_AFPIN  		AFIO_PIN_15


#define  BMV31T001_OUTPUT(NAME) BMV31T001_##NAME##_PORT->DIRCR|=BMV31T001_##NAME##_PIN;BMV31T001_##NAME##_PORT->INER&=~BMV31T001_##NAME##_PIN
#define  BMV31T001_INPUT(NAME) BMV31T001_##NAME##_PORT->DIRCR&=~BMV31T001_##NAME##_PIN;BMV31T001_##NAME##_PORT->INER|=BMV31T001_##NAME##_PIN
#define  BMV31T001_HIGH(NAME) BMV31T001_##NAME##_PORT->SRR=BMV31T001_##NAME##_PIN
#define  BMV31T001_LOW(NAME) BMV31T001_##NAME##_PORT->RR=BMV31T001_##NAME##_PIN
#define  BMV31T001_AFIO(NAME,FUNC)  AFIO_GPxConfig(BMV31T001_##NAME##_AFPORT,BMV31T001_##NAME##_AFPIN,FUNC)
#define  BMV31T001_READ(NAME) ((BMV31T001_##NAME##_PORT->DINR&BMV31T001_##NAME##_PIN)?1:0)
#define  BMV31T001_PUR(NAME) BMV31T001_##NAME##_PORT->PUR|=BMV31T001_##NAME##_PIN;


#define PAUSE_PLAY    	0XF1	//Pause playing the current voice and sentence command
#define CONTINUE_PLAY   0XF2	//Continue playing the paused voice and sentence command
#define LOOP_PLAY    	0XF4	//Loop playback for the current voice and sentence command
#define STOP_PLAY     	0XF8	//Stop playing the current voice and sentence command


#define SPI_FLASH_PAGESIZE 256

#define CE         0x60  // Chip Erase instruction 
#define PP         0x02  // Page Program instruction 
#define READ       0x03  // Read from Memory instruction  
#define WREN       0x06  // Write enable instruction 
#define RDSR       0x05  // Read Status Register instruction 
#define	SFDP	   0x5a	 // Read SFDP.

#define WIP_FLAG   0x01  // Write In Progress (WIP) flag 
#define WEL_FLAG   0x02 // Write Enable Latch

#define DUMMY_BYTE 0xff







static uint8_t _keyValue;
static uint8_t _isKey;
static uint8_t deviceSFDPBuf[4];
static uint8_t rxBuffer[64];
static uint32_t _flashAddr;

static	void writeCmd(uint8_t cmd, uint8_t data);
 
static bool switchSPIMode(void);
static void matchPattern(uint16_t mode);
static void dummyClocks(void);
static uint16_t readData(void);
static uint16_t  ack(void);
static uint16_t readData(void);	
	


static    uint8_t checkCRC8(uint8_t *ptr, uint8_t len); 
static    void recAudioData(void);
static    void SPIFlashWriteEnable(void);
static    void SPIFlashWaitForWriteEnd(void);
static    void SPIFlashChipErase(void);
static    void SPIFlashPageWrite(uint8_t* pBuffer, uint32_t writeAddr, uint16_t numByteToWrite);
static	  void SPIFlashReadSFDP(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);



/*CRC8：x8+x5+x4+1，MSB*/
static const uint8_t crc_table[] =
{
    0x00, 0x31, 0x62, 0x53, 0xc4, 0xf5, 0xa6, 0x97, 0xb9, 0x88, 0xdb, 0xea, 0x7d, 0x4c, 0x1f, 0x2e,
    0x43, 0x72, 0x21, 0x10, 0x87, 0xb6, 0xe5, 0xd4, 0xfa, 0xcb, 0x98, 0xa9, 0x3e, 0x0f, 0x5c, 0x6d,
    0x86, 0xb7, 0xe4, 0xd5, 0x42, 0x73, 0x20, 0x11, 0x3f, 0x0e, 0x5d, 0x6c, 0xfb, 0xca, 0x99, 0xa8,
    0xc5, 0xf4, 0xa7, 0x96, 0x01, 0x30, 0x63, 0x52, 0x7c, 0x4d, 0x1e, 0x2f, 0xb8, 0x89, 0xda, 0xeb,
    0x3d, 0x0c, 0x5f, 0x6e, 0xf9, 0xc8, 0x9b, 0xaa, 0x84, 0xb5, 0xe6, 0xd7, 0x40, 0x71, 0x22, 0x13,
    0x7e, 0x4f, 0x1c, 0x2d, 0xba, 0x8b, 0xd8, 0xe9, 0xc7, 0xf6, 0xa5, 0x94, 0x03, 0x32, 0x61, 0x50,
    0xbb, 0x8a, 0xd9, 0xe8, 0x7f, 0x4e, 0x1d, 0x2c, 0x02, 0x33, 0x60, 0x51, 0xc6, 0xf7, 0xa4, 0x95,
    0xf8, 0xc9, 0x9a, 0xab, 0x3c, 0x0d, 0x5e, 0x6f, 0x41, 0x70, 0x23, 0x12, 0x85, 0xb4, 0xe7, 0xd6,
    0x7a, 0x4b, 0x18, 0x29, 0xbe, 0x8f, 0xdc, 0xed, 0xc3, 0xf2, 0xa1, 0x90, 0x07, 0x36, 0x65, 0x54,
    0x39, 0x08, 0x5b, 0x6a, 0xfd, 0xcc, 0x9f, 0xae, 0x80, 0xb1, 0xe2, 0xd3, 0x44, 0x75, 0x26, 0x17,
    0xfc, 0xcd, 0x9e, 0xaf, 0x38, 0x09, 0x5a, 0x6b, 0x45, 0x74, 0x27, 0x16, 0x81, 0xb0, 0xe3, 0xd2,
    0xbf, 0x8e, 0xdd, 0xec, 0x7b, 0x4a, 0x19, 0x28, 0x06, 0x37, 0x64, 0x55, 0xc2, 0xf3, 0xa0, 0x91,
    0x47, 0x76, 0x25, 0x14, 0x83, 0xb2, 0xe1, 0xd0, 0xfe, 0xcf, 0x9c, 0xad, 0x3a, 0x0b, 0x58, 0x69,
    0x04, 0x35, 0x66, 0x57, 0xc0, 0xf1, 0xa2, 0x93, 0xbd, 0x8c, 0xdf, 0xee, 0x79, 0x48, 0x1b, 0x2a,
    0xc1, 0xf0, 0xa3, 0x92, 0x05, 0x34, 0x67, 0x56, 0x78, 0x49, 0x1a, 0x2b, 0xbc, 0x8d, 0xde, 0xef,
    0x82, 0xb3, 0xe0, 0xd1, 0x46, 0x77, 0x24, 0x15, 0x3b, 0x0a, 0x59, 0x68, 0xff, 0xce, 0x9d, 0xac
};



/************************************************************************* 
 *@brief:    resverd
 *@param:    void            
 *@return:    void     
*************************************************************************/
static void SPI_end(void)
{

}

/************************************************************************* 
 *@brief:   software SPI initial.
 *@param:   void             
 *@return:   void    
*************************************************************************/
static void SPI_begin(void)
{
  BMV31T001_OUTPUT(CS);
  BMV31T001_HIGH(CS);
	
  BMV31T001_OUTPUT(SCK);
  BMV31T001_LOW(SCK);	 //CPOL=LOW
	
  BMV31T001_OUTPUT(MOSI);
  BMV31T001_HIGH(MOSI);

  BMV31T001_INPUT(MISO);
}



/************************************************************************* 
 *@brief:  software SPI read and wirte.
 *@param:   one byte to wirte 
						byte: write data
 *@return:  one byte to read        
*************************************************************************/
static u8 SPI_RW(u8 byte)
{
		uint8_t i;

		u8 Temp=0x00;

		for (i = 0; i < 8; i++)

		{

				BMV31T001_LOW(SCK);

				if (byte&0x80)
				{
						BMV31T001_HIGH(MOSI); //Send 1
						delay_us(1);
				}
				else
				{
						BMV31T001_LOW(MOSI);//Send 0
						delay_us(1);
				}

				byte <<= 1;
				Temp<<=1;
				
				BMV31T001_HIGH(SCK); //read and write on raise clock
				
				if(BMV31T001_READ(MISO)) 
				{
					Temp++;
				}
				delay_us(1);
				BMV31T001_LOW(SCK);
		}
		return Temp; //返回读到miso输入的值

}


/************************************************************************* 
 *@brief:  reset power
 *@param:   void
 *@return:   void    
*************************************************************************/
void BMV31T001_reset(void)
{
		BMV31T001_OUTPUT(POWER);
    BMV31T001_LOW(POWER);
    delay_ms(500);
    BMV31T001_HIGH(POWER);
}

/************************************************************************* 
 *@brief:   BMV31T001 Initial
 *@param:   void
 *@return:   void    
*************************************************************************/
void BMV31T001_Init()
{
	_keyValue = 0;
	_isKey = 0; 
	_flashAddr = 0;
	
	
    BMV31T001_AFIO(POWER,AFIO_FUN_GPIO);
    BMV31T001_AFIO(LED,AFIO_FUN_GPIO);
    BMV31T001_AFIO(DATA,AFIO_FUN_GPIO);
    BMV31T001_AFIO(STATUS,AFIO_FUN_GPIO);
    BMV31T001_AFIO(ICPCK,AFIO_FUN_GPIO);	

	
	
    BMV31T001_reset();
	
    BMV31T001_OUTPUT(POWER);
    BMV31T001_LOW(POWER);//disable
    BMV31T001_OUTPUT(LED);
    BMV31T001_HIGH(LED);//disable

    BMV31T001_OUTPUT(DATA);
    BMV31T001_HIGH(DATA);
	

    BMV31T001_INPUT(ICPCK);

    BMV31T001_INPUT(STATUS);
    //Key port
    BMV31T001_AFIO(KEY_UP,AFIO_FUN_GPIO);
    BMV31T001_INPUT(KEY_UP);
    BMV31T001_PUR(KEY_UP);

    BMV31T001_AFIO(KEY_LEFT,AFIO_FUN_GPIO);
    BMV31T001_INPUT(KEY_LEFT);
    BMV31T001_PUR(KEY_LEFT);

    BMV31T001_AFIO(KEY_DOWN,AFIO_FUN_GPIO);
    BMV31T001_INPUT(KEY_DOWN);
    BMV31T001_PUR(KEY_DOWN);

    BMV31T001_AFIO(KEY_RIGHT,AFIO_FUN_GPIO);
    BMV31T001_INPUT(KEY_RIGHT);
    BMV31T001_PUR(KEY_RIGHT);

    BMV31T001_AFIO(KEY_MIDDLE,AFIO_FUN_GPIO);
    BMV31T001_INPUT(KEY_MIDDLE);
    BMV31T001_PUR(KEY_MIDDLE);

	delay_ms(1000);//There's a delay_ms here to get the BMV31T001 ready
	


}


/************************************************************************* 
 *@brief:   Sends playback control commands
 *@param: 
					cmd：playback control commands
					data : 0x00~0x7f is select the voice 0~127 to play if cmd is 0xfa
                           0x00~0x7f is select the voice 128~255 to play if cmd is 0xfb
 *@return:   void    
*************************************************************************/
static void writeCmd(uint8_t cmd, uint8_t data)
{
	
	uint8_t i, temp;

	delay_ms(5);
	temp = 0x01;
    
    if(0xff != data)//need data
    {
        //start signal
        BMV31T001_LOW(DATA);
        delay_ms(5);

        for (i = 0; i < 8; i ++)
        {
            if (1 == (cmd & temp))
            {
                    // out bit high
                    BMV31T001_HIGH(DATA);
                    delay_us(1200);
                    BMV31T001_LOW(DATA);
                    delay_us(400);
            }
            else
            {
                    BMV31T001_HIGH(DATA);
                    delay_us(400);
                    BMV31T001_LOW(DATA);
                    delay_us(1200);
            }
            cmd >>= 1;
        }

        BMV31T001_HIGH(DATA);
        delay_ms(5);
        BMV31T001_LOW(DATA);
        delay_ms(5);

        for (i = 0; i < 8; i ++)
        {
            if (1 == (data & temp))
            {
                    // out bit high
                    BMV31T001_HIGH(DATA);
                    delay_us(1200);
                    BMV31T001_LOW(DATA);
                    delay_us(400);
            }
            else
            {
                    BMV31T001_HIGH(DATA);
                    delay_us(400);
                    BMV31T001_LOW(DATA);
                    delay_us(1200);
            }
            data >>= 1;
        }
        BMV31T001_HIGH(DATA);
        delay_ms(5);
    }
    else //only send cmd
    {
        BMV31T001_LOW(DATA);
        delay_ms(5);

        for (i = 0; i < 8; i ++)
        {
            if (1 == (cmd & temp))
            {
                    // out bit high
                    BMV31T001_HIGH(DATA);
                    delay_us(1200);
                    BMV31T001_LOW(DATA);
                    delay_us(400);
            }
            else
            {
                    BMV31T001_HIGH(DATA);
                    delay_us(400);
                    BMV31T001_LOW(DATA);
                    delay_us(1200);
            }
            cmd >>= 1;
        }
        BMV31T001_HIGH(DATA);
        delay_ms(5);   
    }

}

/************************************************************************* 
 *@brief:   Set the volume
 *@param: 
					cmd：volume：0~11(0:minimum volume（mute）;11:maximum volume)
 *@return:   void    
*************************************************************************/
void BMV31T001_setVolume(uint8_t volume)
{
	writeCmd(0xe1 + volume,0xff);
}

/************************************************************************* 
 *@brief:  Play voice.
 *@param: 
					num：VOC_01~VOC_256(Enter the number according to the number of the voice 
                    generated by the PC tool.The maximum number is VOC_256. )
                    loop：default 0.(1：Loops the current voice，0：Play it only once) 
 *@return:   void    
*************************************************************************/
void BMV31T001_playVoice(uint8_t num, uint8_t loop)
{

	
	
    if(num < 128)
    {
        writeCmd(0xfa, num);
    }
    else
    {
        writeCmd(0xfb, num % 128);
    }
	
	if(loop)
	{
		writeCmd(0xf4,0xff);
	}

}

/************************************************************************* 
 *@brief:  Play voice.
 *@param: 
				num：SEN_01~SEN_96(Enter the number according to the number of the sentence 
                    generated by the PC tool.The maximum number is SEN_96. )
                    loop：default 0.(1：Loops the current sentence，0：Play it only once)   
 *@return:  void     
*************************************************************************/
void BMV31T001_playSentence(uint8_t num, uint8_t loop)
{
	writeCmd(num,0xff);
	if(loop)
	{
		writeCmd(0xf4,0xff);
	}
}

/************************************************************************* 
 *@brief:  Stop playing the current voice and sentence.
 *@param:  void 
 *@return:  void     
*************************************************************************/
void BMV31T001_playStop(void)
{
	writeCmd(STOP_PLAY,0xff);
}

/************************************************************************* 
 *@brief:  Pause playing the current voice and sentence.
 *@param:  void 
 *@return: void      
*************************************************************************/
void BMV31T001_playPause(void)
{
	writeCmd(PAUSE_PLAY,0xff);
}

/************************************************************************* 
 *@brief:  Continue playing the paused voice and sentence.
 *@param:  void 
 *@return:  void     
*************************************************************************/
void BMV31T001_playContinue(void)
{
	writeCmd(CONTINUE_PLAY,0xff);
}

/************************************************************************* 
 *@brief:  Loop playback the current voice/sentence
 *@param:  void 
 *@return:  void     
*************************************************************************/
void BMV31T001_playRepeat(void)
{
    writeCmd(LOOP_PLAY,0xff);
}

/************************************************************************* 
 *@brief: Get the play status
 *@param: void  
 *@return:     0:Not in the play   1:In the play
*************************************************************************/
bool BMV31T001_isPlaying(void)
{
//	if (0 == digitalRead(STATUS_PIN))
    if (0 == BMV31T001_READ(STATUS))
	{
		return true;
	}
	else
	{
		return false;
	}
}


/************************************************************************* 
 *@brief:  Scanning key
 *@param:  void 
 *@return: void    
*************************************************************************/
void BMV31T001_scanKey(void)
{
    static uint8_t step = 0;
    uint8_t currentKey;
    static uint8_t lastKey = 0;
		uint32_t current_tick;
		static uint32_t last_tick;
	
		current_tick=Get_Sys_ms();
	
    if((current_tick - last_tick) > 10)
    {
        last_tick = current_tick;
			
				currentKey = 0;

        if(BMV31T001_READ(KEY_MIDDLE) == 0)
        {
            currentKey |= 0X01;
        }
        if(BMV31T001_READ(KEY_UP) == 0)
        {
            currentKey |= 0X02;
        }
        if(BMV31T001_READ(KEY_DOWN) == 0)
        {
            currentKey |= 0X04;
        }
        if(BMV31T001_READ(KEY_LEFT) == 0)
        {
            currentKey |= 0X08;
        }
        if(BMV31T001_READ(KEY_RIGHT) == 0)
        {
            currentKey |= 0X10;
        }
        switch(step)
        {
            case 0:
                if(currentKey != lastKey)
                {
                    step = 1;
                }
                return;
            case 1:
                if(currentKey != lastKey)
                {
                    _keyValue = currentKey;
                    _isKey = 1;
                }
                step = 0;
                break;
        }
        lastKey = currentKey;
    }
}

/************************************************************************* 
 *@brief:  Retrun flag true if any keys are pressed
 *@param:  void 
 *@return:  0: No keys were pressed; 1: there are keys that are pressed   
*************************************************************************/
bool BMV31T001_isKeyAction(void)
{
    if(_isKey)
    {
        _isKey = 0;
        return true;     
    }
	else 
    {
        return false;
    }
}

/************************************************************************* 
 *@brief:  read key pressed value
 *@param:  void 
 *@return:  0: pressed; 1: no pressed   
*************************************************************************/
uint8_t BMV31T001_readKeyValue(void)
{
	return _keyValue;
}

/************************************************************************* 
 *@brief:  Set the power up or down of the BMV31T001
 *@param:   status: 0:power down; 1:power up
 *@return:  void
*************************************************************************/
void BMV31T001_setPower(uint8_t status)
{
		delay_ms(1);
    if(status!=0)
		
    BMV31T001_HIGH(POWER);
    else
    BMV31T001_LOW(POWER);
		delay_ms(1);
}

/************************************************************************* 
 *@brief:  Set the onboard LED on or off
 *@param:   status: 0:LED off; 1:LED on
 *@return:  void
*************************************************************************/
void BMV31T001_setLED(uint8_t status)
{
    if(status!=0)
    BMV31T001_LOW(LED);
    else
    BMV31T001_HIGH(LED);	
}
/************************************************************************* 
 *@brief:  Update your audio source with Ardunio
 *@param:     
							boardType: 0: BMduino UNO; 1: Arduino UNO
							baudrate: Updated baud rate
 *@return:  void
*************************************************************************/

void BMV31T001_initAudioUpdate(unsigned long baudrate)
{
    BMV31T001_OUTPUT(DATA);
    BMV31T001_HIGH(DATA);
	USBSerial_begin(baudrate);
}

/************************************************************************* 
 *@brief:   Get the update sound source signal
 *@param:   void
 *@return:   1：execute update; 0：not execute update
*************************************************************************/
bool BMV31T001_isUpdateBegin(void)
{
    if (USBSerial_available())
    {
        return true;
    }
    else
    {
        return false;
    }        
}

/************************************************************************* 
 *@brief:   Update the audio source
 *@param:   void
 *@return:  1:Update completed; 0:Update failed 
*************************************************************************/
bool BMV31T001_executeUpdate(void)
{
    static int8_t dataLength = 0;
    uint32_t delayCount = 0;
    while(1)
    {
        if(USBSerial_available())
        {
            delayCount = 0;
            USBSerial_readBytes(rxBuffer, 3);   
            if ((0xAA == rxBuffer[0]) && (0x23 == rxBuffer[1]))
            {
                dataLength = rxBuffer[2];
                USBSerial_readBytes(rxBuffer + 3, dataLength + 2);                 
                if (rxBuffer[dataLength + 3] == checkCRC8(rxBuffer + 2, dataLength + 1))
                {
                    if (6 == dataLength)
                    {
                        if ((rxBuffer[3] == 'C') && (rxBuffer[4] == 'O') && (rxBuffer[5] == 'M')
                        && (rxBuffer[6] == 'S') && (rxBuffer[7] == 'P') && (rxBuffer[8] == 'I'))
                        {
                                BMV31T001_LOW(POWER);
                                delay_ms(500);
                                BMV31T001_HIGH(POWER);													
                            if (false == switchSPIMode())
                            {
                            
                                USBSerial_write_byte(0xe3);
            
                                BMV31T001_LOW(POWER);
                                delay_ms(500);
                                BMV31T001_HIGH(POWER);         
                                _flashAddr = 0;
           
                                BMV31T001_OUTPUT(DATA);
                                BMV31T001_HIGH(DATA);
                                BMV31T001_INPUT(STATUS);
                                BMV31T001_OUTPUT(ICPDA);
                                BMV31T001_HIGH(ICPDA);
                                BMV31T001_INPUT(ICPCK);

                      
                            }
                            else
                            {
                                USBSerial_write_byte(0x3e);//ACK
                            }
                            
                        }
                        else if ((rxBuffer[3] == 'C') && (rxBuffer[4] == 'O') && (rxBuffer[5] == 'M')
                        && (rxBuffer[6] == 'O') && (rxBuffer[7] == 'R') && (rxBuffer[8] == 'D'))
                        {
                            USBSerial_write_byte(0x3e);//ACK

    
                                BMV31T001_LOW(POWER);
                                delay_ms(500);
                                BMV31T001_HIGH(POWER);   

                            _flashAddr = 0;
                             SPI_end();
                    
                                BMV31T001_OUTPUT(DATA);
                                BMV31T001_HIGH(DATA);                          
                    
                                BMV31T001_INPUT(STATUS);
                                BMV31T001_OUTPUT(ICPDA);
                                BMV31T001_HIGH(ICPDA);
                                BMV31T001_INPUT(ICPCK);                 
                       
                            delay_ms(10);
                            return true;
                        }
                    }
                    else if (5 == dataLength)
                    {
                        if ((rxBuffer[3] == 'C') && (rxBuffer[4] == 'O') && (rxBuffer[5] == 'M')
                        && (rxBuffer[6] == 'C') && (rxBuffer[7] == 'E'))
                        {
                            SPIFlashChipErase();
                            USBSerial_write_byte(0x3e);//ACK
                        }
                    }       
                }
                else
                {
                    USBSerial_write_byte(0xe3);//NACK
                }

            }
            else
            {
                recAudioData();
            }
        }
        delayCount++;

        delay_us(50);
        if(delayCount>=2000)
        {
            return false;//timeout is 50us*2000=100ms,nothing for receive
        }
    }
}

/************************************************************************* 
 *@brief:  Receive audio data update from upper computer into BMV31T001
 *@param:   void
 *@return:  1:Correct reception; 0:Error of reception
*************************************************************************/
static void recAudioData(void)
{
    static int8_t dataLength = 0;
    static uint8_t remainder = 0;
    static uint32_t sumDataCnt = 0;
    if ((0x55 == rxBuffer[0]) && (0x23 == rxBuffer[1]))
    {
        dataLength = rxBuffer[2];
        USBSerial_readBytes(rxBuffer + 3, dataLength + 2);  
        if (rxBuffer[dataLength + 3] == checkCRC8(rxBuffer + 2, dataLength + 1))
        {
            sumDataCnt += dataLength;
            remainder = sumDataCnt % 64;
            if (remainder <= 59)
            {
                SPIFlashPageWrite(rxBuffer + 3, _flashAddr, dataLength - remainder);
                SPIFlashPageWrite(rxBuffer + 3 + dataLength - remainder, _flashAddr + dataLength - remainder, remainder);
                
            }
            else
            {
                SPIFlashPageWrite(rxBuffer + 3, _flashAddr, dataLength);
            }
                
            _flashAddr += dataLength;
            USBSerial_write_byte(0x3e);//ACK
        }
        else
        {
            USBSerial_write_byte(0xe3);//NACK
            return;
        }
    }
}


/************************************************************************* 
 *@brief: Enter update mode
*@param:   mode:enter mode
								0x02：SPI voice update mode
 *@return:   1:Enter mode successfully
                0:Failed to enter mode
*************************************************************************/
static bool  programEntry(uint16_t mode)
{
    static uint8_t retransmissionTimes = 0;
	

		BMV31T001_OUTPUT(POWER);
    BMV31T001_LOW(POWER);
    BMV31T001_OUTPUT(STATUS);
    BMV31T001_LOW(STATUS);
    BMV31T001_OUTPUT(DATA);
    BMV31T001_LOW(DATA);    
    BMV31T001_OUTPUT(CS);
    BMV31T001_LOW(CS);    
    BMV31T001_OUTPUT(ICPCK);
    BMV31T001_LOW(ICPCK); 
    BMV31T001_OUTPUT(ICPDA);
    BMV31T001_LOW(ICPDA);     

    delay_ms(5);

    BMV31T001_INPUT(STATUS);
    delay_ms(1);
    BMV31T001_HIGH(POWER);
    BMV31T001_HIGH(ICPCK);

    delay_ms(2);

    BMV31T001_HIGH(ICPDA);


    do{
        /*READY*/

        BMV31T001_LOW(ICPCK);
        delay_us(160);//tready:150us~

        /*MATCH*/

        BMV31T001_HIGH(ICPCK);

        delay_us(84);
        /*Match Pattern and set mode:0100 1010 1xxx*/
        matchPattern(mode);
        retransmissionTimes++;
        if(5 == retransmissionTimes)
        {
            retransmissionTimes = 0;
            return false;
        }
    }while(mode != ack());
    dummyClocks();
    retransmissionTimes = 0;
    return true;
}

/************************************************************************* 
 *@brief: ack of mode
 *@param:  void 
 *@return:  current mode data
*************************************************************************/
  static uint16_t  ack(void)
{
    /*MSB*/
    static uint8_t i;
    uint16_t ackData = 0;

    BMV31T001_INPUT(ICPDA);

    BMV31T001_LOW(ICPCK);
    for (i = 0; i < 3; i++)
    {

        BMV31T001_HIGH(ICPCK);
				delay_us(1);
        BMV31T001_LOW(ICPCK);
				delay_us(1);
        if (BMV31T001_READ(ICPDA))
        {
             ackData |= (0x04 >> i);
        }
        else
        {
            ackData &= ~(0x04 >> i);
        }
       
        delay_us(1);
				BMV31T001_HIGH(ICPCK);
				delay_us(1);
				
    }
    
 
    BMV31T001_HIGH(ICPCK);
    BMV31T001_OUTPUT(ICPDA);
    return ackData;
}

/************************************************************************* 
 *@brief: Send the dummy Clocks
 *@param:   void
 *@return:  void
*************************************************************************/
static void dummyClocks(void)
{
    static uint16_t i;
    for (i = 0; i < 512; i++)
    {
        BMV31T001_LOW(ICPCK);
        delay_us(2);
        BMV31T001_HIGH(ICPCK);
        delay_us(2);    
    }
}

/************************************************************************* 
 *@brief: Send data bit in high
 *@param:   void
 *@return:  void
*************************************************************************/
static void programDataOut1(void)
{

    BMV31T001_HIGH(ICPDA);
    delay_us(2);
 
    BMV31T001_LOW(ICPCK);
    delay_us(2);//tckl:1~15us

    BMV31T001_HIGH(ICPCK);

}

/************************************************************************* 
 *@brief: Send data bit in low
 *@param:  void 
 *@return:  void
*************************************************************************/
static void programDataOut0(void)
{

    BMV31T001_LOW(ICPDA);
    delay_us(2);

    BMV31T001_LOW(ICPCK);
    delay_us(2);//tckl:1~15us
 
    BMV31T001_HIGH(ICPCK);
}
/************************************************************************* 
 *@brief:  Send address bit in high
 *@param:   void
 *@return:  void
*************************************************************************/
static void programAddrOut1(void)
{



    BMV31T001_HIGH(ICPDA);

    BMV31T001_LOW(ICPCK);
    delay_us(1);//tckl:1~15us
  
    BMV31T001_HIGH(ICPCK);
    delay_us(4);
}

/************************************************************************* 
 *@brief:   Send address bit in low
 *@param:   void
 *@return:  void
*************************************************************************/
static void programAddrOut0(void)
{


        BMV31T001_LOW(ICPDA);
  
    BMV31T001_LOW(ICPCK);
    delay_us(1);//tckl:1~15us

    BMV31T001_HIGH(ICPCK);
    delay_us(4);
}
/************************************************************************* 
 *@brief:   Pattern(mode) matching
 *@param:   mode:0x02 is enter update voice mode success.
 *@return:  void
*************************************************************************/
static void matchPattern(uint16_t mode)
{
    uint16_t i, temp, pattern, mData;
    pattern = 0x4A8;//0100 1010 1000:low 3 bits are mode; high 9 bits are fixed
    mData = (pattern | mode) << 4;
	temp = 0x8000;//MSB

	for (i = 0; i < 12; i++)
	{
		if(mData&temp)
			programDataOut1();
		else
			programDataOut0();
			
		mData <<= 1;
		
	}
   
    BMV31T001_HIGH(ICPDA);
}

/************************************************************************* 
 *@brief:   Send the address
 *@param:   addr:The address to which data is written
 *@return:  void
*************************************************************************/
static void sendAddr(uint16_t addr)
{
	uint16_t i, temp;

    BMV31T001_OUTPUT(ICPDA);
    BMV31T001_HIGH(ICPDA);
    /*LSB*/
	
	temp = 0x0001;//LSB
	
	for (i = 0; i < 12; i++)
	{
		if (addr & temp)
			programAddrOut1();
		else
			programAddrOut0();
			
		addr >>= 1;
		
	}
}

/************************************************************************* 
 *@brief:   Send the data
 *@param:   data:Data sent to the BMV31T001 at a fixed address
 *@return:  void
*************************************************************************/
static void sendData(uint16_t data)
{
    uint16_t i, temp;

    BMV31T001_OUTPUT(ICPDA);
	
	temp = 0x0001;//LSB

	for (i = 0; i < 14; i++)
	{
		if (data & temp)
			programDataOut1();
		else
			programDataOut0();
			
		data >>= 1;		
	}
    delay_us(1);

    BMV31T001_LOW(ICPCK);
    delay_us(1);

    BMV31T001_HIGH(ICPCK);
    delay_us(2000);

    BMV31T001_LOW(ICPCK);
    delay_us(1);

    BMV31T001_HIGH(ICPCK);
    delay_us(5);
}

/************************************************************************* 
 *@brief:   read the data
 *@param:   void
 *@return:  data is readed
*************************************************************************/
static uint16_t readData(void)
{
    /*LSB*/
	uint8_t i;
    uint16_t rxData = 0;

    BMV31T001_INPUT(ICPDA); 
    BMV31T001_LOW(ICPCK);  	
    for (i = 0; i < 14; i++)
    {
    
        BMV31T001_LOW(ICPCK);  
        if (1 == BMV31T001_READ(ICPDA))
        {
            rxData |= (0x01 << i);
        }
        else
        {
            rxData &= ~(0x01 << i);
        }
       
        BMV31T001_HIGH(ICPCK);
        delay_us(2);
    }
    ////15th
    BMV31T001_HIGH(ICPCK);  
    delay_us(2);
   
    BMV31T001_LOW(ICPCK);  
    delay_us(1);
    ////16th
    BMV31T001_HIGH(ICPCK);  
    delay_us(2000);

    BMV31T001_LOW(ICPCK);  
    delay_us(1);

    BMV31T001_HIGH(ICPCK);  
    return rxData;
}

/************************************************************************* 
 *@brief:  Switch SPI Mode
 *@param:   void
 *@return:   true:Switch successfully  false:Fail to switch
*************************************************************************/
static bool switchSPIMode(void)
{
    static uint8_t correctFlag = 0;
    static uint8_t retransmissionTimes = 0;
    if (false == programEntry(0x02))
    {
        return false;
    }
    sendAddr(0x0020);
    sendData(0x0000);
    sendData(0x0000);
    sendData(0x0007);
    sendData(0x0000);    



    //SPI.begin();

    SPI_begin();
    BMV31T001_HIGH(CS);
    delay_ms(10);
    do{     
		SPIFlashReadSFDP(deviceSFDPBuf,0,4);
 
        if ((0x53 == deviceSFDPBuf[0]) && (0x46 == deviceSFDPBuf[1]) 
			&& (0x44 == deviceSFDPBuf[2]) && (0x50 == deviceSFDPBuf[3]))      
        {
            correctFlag = 1;
        }
        retransmissionTimes++;
        if (3 == retransmissionTimes)
        {
            retransmissionTimes = 0;
            return false;
        }
    }while(0 == correctFlag);
	correctFlag = 0;
    retransmissionTimes = 0;
    return true;
}

/************************************************************************* 
 *@brief:  Data check
 *@param: 
						 *ptr:The array to check
						len:Length of data to be check
								
 *@return:  CRC result
*************************************************************************/
static uint8_t checkCRC8(uint8_t *ptr, uint8_t len) 
{
    uint8_t  crc = 0x00;

    while (len--)
    {
        crc = crc_table[crc ^ *ptr++];
    }
    return (crc);
}

/************************************************************************* 
 *@brief:  Enables the write access to the FLASH.
 *@param: 	void					
 *@return: void
*************************************************************************/
static void SPIFlashWriteEnable(void)
{
      /* Select the FLASH: Chip Select low */

     BMV31T001_LOW(CS);
      /* Send instruction */
      SPI_RW(WREN);

      /* Deselect the FLASH: Chip Select high */
  
      BMV31T001_HIGH(CS);
}

/************************************************************************* 
 *@brief: Polls the status of the Write In Progress (WIP) flag in 
                the FLASH's status register and loop until write  opertaion has completed.
 *@param: 						
 *@return: 
*************************************************************************/
static void SPIFlashWaitForWriteEnd(void)
{
    uint8_t FLASH_Status = 0;

    /* Select the FLASH: Chip Select low */

    BMV31T001_LOW(CS);
    /* Send "Read Status Register" instruction */
    SPI_RW(RDSR);
    /* Loop as long as the memory is busy with a write cycle */
    do
    {
    /* Send a dummy byte to generate the clock needed by the FLASH 
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = SPI_RW(DUMMY_BYTE);

    } while((FLASH_Status & WIP_FLAG) == 1); /* Write in progress */
    /* Deselect the FLASH: Chip Select high */
	
    BMV31T001_HIGH(CS);
}

/************************************************************************* 
 *@brief: Erases the entire FLASH.
 *@param: 	void					
 *@return: void
*************************************************************************/
static void SPIFlashChipErase(void)
{
  /* Send write enable instruction */
  SPIFlashWriteEnable();

  /* Bulk Erase */ 
  /* Select the FLASH: Chip Select low */

  BMV31T001_LOW(CS);
  /* Send Chip Erase instruction  */
  SPI_RW(CE);
  /* Deselect the FLASH: Chip Select high */

  BMV31T001_HIGH(CS);
  /* Wait the end of Flash writing */
  SPIFlashWaitForWriteEnd();
}

/************************************************************************* 
 *@brief: Writes more than one byte to the FLASH with a single WRITE cycle(Page WRITE sequence). 
                The number of byte can't exceed the FLASH page size.
 *@param: 		
       pBuffer : pointer to the buffer  containing the data to be written to the FLASH.
       writeAddr : FLASH's internal address to write to.
       numByteToWrite : number of bytes to write to the FLASH, must be equal or less 
                                    than "SPI_FLASH_PAGESIZE" value.
 *@return: void
*************************************************************************/
static void SPIFlashPageWrite(uint8_t* pBuffer, uint32_t writeAddr, uint16_t numByteToWrite)
{
  /* Enable the write access to the FLA
  SH */
  SPIFlashWriteEnable();
  /* Select the FLASH: Chip Select low */

 BMV31T001_LOW(CS);
  /* Send "Write to Memory " instruction */
  SPI_RW(PP);
  /* Send writeAddr high nibble address byte to write to */
  SPI_RW((writeAddr & 0xFF0000) >> 16);
  /* Send writeAddr medium nibble address byte to write to */
  SPI_RW((writeAddr & 0xFF00) >> 8);  
  /* Send writeAddr low nibble address byte to write to */
  SPI_RW(writeAddr & 0xFF);
  
  /* while there is data to be written on the FLASH */
  while(numByteToWrite--) 
  {
    /* Send the current byte */
    SPI_RW(*pBuffer);
    /* Point on the next byte to be written */
    pBuffer++; 
  }
  
  /* Deselect the FLASH: Chip Select high */

BMV31T001_HIGH(CS);
  /* Wait the end of Flash writing */
  SPIFlashWaitForWriteEnd();
}


/************************************************************************* 
 *@brief: Read SFDP.
 *@param: 		
										pBuffer : pointer to the buffer that receives the data read from the FLASH.
                    ReadAddr : FLASH's internal address to read from.
                    NumByteToRead : number of bytes to read from the FLASH.
                                    than "SPI_FLASH_PAGESIZE" value.
 *@return: void
*************************************************************************/
static void SPIFlashReadSFDP(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    /* Select the FLASH: Chip Select low */
	
    BMV31T001_LOW(CS);
    /* Send "Read from Memory " instruction */
    SPI_RW(SFDP);

    /* Send ReadAddr high nibble address byte to read from */
    SPI_RW((ReadAddr & 0xFF0000) >> 16);
    /* Send ReadAddr medium nibble address byte to read from */
    SPI_RW((ReadAddr& 0xFF00) >> 8);
    /* Send ReadAddr low nibble address byte to read from */
    SPI_RW(ReadAddr & 0xFF);
	/* Send 1 byte dummy clock */
	SPI_RW(DUMMY_BYTE);

    //SPI_FIFOReset(SPIx, SPI_FIFO_RX);

    while(NumByteToRead--) /* while there is data to be read */
    {
		/* Read a byte from the FLASH */
		*pBuffer = SPI_RW(DUMMY_BYTE);
		/* Point to the next location where the byte read will be saved */
		pBuffer++;
    }

    /* Deselect the FLASH: Chip Select high */

    BMV31T001_HIGH(CS);
}


