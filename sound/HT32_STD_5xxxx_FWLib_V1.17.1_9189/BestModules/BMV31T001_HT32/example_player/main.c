/*********************************************************************************************************//**
 * @file    BMV31T001_HT32/example_player/main.c
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
VOC_1};//   ,VOC_2,VOC_3,VOC_4,VOC_5

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


    delay_ms(100);//Delay until the expansion version is powered on
    BMV31T001_setVolume(DEFAULT_VOLUME);//Initialize the default volume
				

  while (1)                           /* Infinite loop                                                      */
{

    //-----------------Play indicator led control------------------------------
    if(BMV31T001_isPlaying() == BMV31T001_BUSY)
    { //Gets the current playback status
        playStatus = BMV31T001_BUSY;
        BMV31T001_setLED(BMV31T001_LED_ON);//LED on
    }
    else
    {
        playStatus = BMV31T001_NOBUSY;
        BMV31T001_setLED(BMV31T001_LED_OFF);//LED off
    }
    //-----------------scan key-----------------------------
    BMV31T001_scanKey();//polling key status

    //-----------------dispose key------------------------------
    if(BMV31T001_isKeyAction() != BMV31T001_NO_KEY)//there is key pressed
    {
        
        keyStatus = BMV31T001_readKeyValue();//Gets the current key level value
				keycode = 0;
        if(lastKeyStatus == 0)
        {
            if((keyStatus & BMV31T001_KEY_MIDDLE) != 0){//middle key pressed;
                keycode = BMV31T001_KEY_MIDDLE;
            }
            else if((keyStatus & BMV31T001_KEY_UP) != 0){//up key pressed;
                keycode = BMV31T001_KEY_UP;
            }
            else if((keyStatus & BMV31T001_KEY_DOWN) != 0){//down key pressed;
                keycode = BMV31T001_KEY_DOWN;
            }
            else if((keyStatus & BMV31T001_KEY_LEFT) != 0){//left key pressed;
                keycode = BMV31T001_KEY_LEFT;
            }
            else {
                keycode = BMV31T001_KEY_RIGHT;//right key pressed;
            }
        }
        lastKeyStatus = keyStatus ;
        switch(keycode)//Judge and dispose key
        {
            case BMV31T001_KEY_MIDDLE://The middle key is pressed
                if(playStatus == BMV31T001_BUSY)//in the play
                {
                    BMV31T001_playStop();//Stop playing if it is currently playing
                }
                else
                {
                    BMV31T001_playVoice(voice_table[playNum],0);//Play the current voice
                }
                keycode = 0;
                break;
            case BMV31T001_KEY_UP://The up key is pressed
                if(volume < BMV31T001_VOLUME_MAX)//If not the loudest
                {
                    volume++;//The volume increase
                    BMV31T001_setVolume(volume);
                }
                keycode = 0;
                break;
            case BMV31T001_KEY_DOWN://The down key is pressed
                if(volume > BMV31T001_VOLUME_MIN)//If not the smallest volume
                {
                    volume--;//The volume reduction
                    BMV31T001_setVolume(volume);
                }    
                keycode = 0;
                break;
            case BMV31T001_KEY_LEFT://The left key is pressed
                if(playNum > 0)
                {
                    playNum--;//last voice
                }
                BMV31T001_playVoice(voice_table[playNum],0); 
                keycode = 0;
                break;
            case BMV31T001_KEY_RIGHT://The right key is pressed
                if(playNum < VOICE_TOTAL_NUMBER - 1)
                {
                    playNum++;//next voice
                }
                BMV31T001_playVoice(voice_table[playNum],0);// play next voice
                keycode = 0;
                break;
            default:
                keycode = 0;
                break;     
        }  
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
