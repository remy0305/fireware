/*********************************************************************************************************//**
 * @file    BMV31T001_HT32/example_voiceUpdate/main.c
 * @version V1.0.1
 * @date    2024-08-01
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

#include "BMV31T001.h"
#include "delay.h"
#include "../VoiceBroadcast/voice_cmd_list.h" //Contains a library of voice information

/* Global variables ----------------------------------------------------------------------------------------*/
#define VOICE_TOTAL_NUMBER 10//This example tests 10 voices
//Voice_cmd_list. h is used to create a voice list
const uint8_t voice_table[VOICE_TOTAL_NUMBER]={ 
VOC_1,VOC_2,VOC_3,VOC_4,VOC_5};

uint8_t keyStatus; //status of keys
uint8_t lastKeyStatus;//status of last keys
uint8_t playStatus; //current Playing Status
uint8_t playNum; //number of the song being played
#define DEFAULT_VOLUME 6 //default volume
uint8_t volume = DEFAULT_VOLUME; //current volume
uint8_t keycode = 0;//Number of the key that was triggered

 
/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
  
int main(void)
{
	  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
		CKCUClock.Bit.AFIO       = 1;
		CKCUClock.Bit.PA       = 1;	
		CKCUClock.Bit.PB       = 1;	
		CKCUClock.Bit.PC       = 1;	
		CKCUClock.Bit.PD       = 1;	
		CKCUClock.Bit.BFTM0       = 1;			
		CKCU_PeripClockConfig(CKCUClock, ENABLE);
	
		SysTick_Config(SystemCoreClock/1000);//1ms tick
		
    BMV31T001_Init();//Initialize the BMV31T001
    BMV31T001_setPower(BMV31T001_POWER_UP);//Power on the BMV31T001

    //=====================================================================
    //If you want to update the audio source, add the serial port initializer for the audio source update
    BMV31T001_initAudioUpdate(115200);
    //=====================================================================
				

  while (1)                           /* Infinite loop                                                      */
{
    //=========================================================================
    //-----------------update audio source------------------------------
    //If you want to update your audio source, please add this program
    if(BMV31T001_isUpdateBegin() == BMV31T001_UPDATA_BEGIN)
    {//detect update signal
        BMV31T001_executeUpdate();//Execute audio source updates
    }
 
}

}




/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
