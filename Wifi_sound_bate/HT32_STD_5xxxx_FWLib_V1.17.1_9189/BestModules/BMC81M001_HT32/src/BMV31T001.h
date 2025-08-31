/*********************************************************************************************************//**
 * @file    BMV31T001_HT32/src/BMV31T001.h
 * @version V1.0.1
 * @date    2024-08-01
 * @brief   The header file of the BMV31T001 libray.
 *************************************************************************************************************/
 
#ifndef _BMV31T001_H
#define _BMV31T001_H

#include "ht32.h"

/*************************playback control command***************************************************************************************
 * Play voice                                00H~7FH ——> when the 0xfa command is used,00H:is voice 0； from 0 to 127;
                                                         when the 0xfa cammand is used ,00H:is voice 128;from 128 to 255.
 * Play sentence                             80H~DFH ——> 80H:is sentence 0；from 0 to 95, there are 96 sentences.
 * Volume selection                          E1H~ECH ——> E1H:is the minimum volume（mute）；There are 12 levels of volume adjustment.
 * Pause voice/sentence                      F1H     ——> Pause playing the current voice and sentence.
 * Play after pause                          F2H      ——> Continue playing the paused voice and sentence.
 * Loop playback the current voice/sentence  F4H      ——> Loop playback for the current voice and sentence.
 * Stop playing the current voice/sentence   F8H      ——> Stop playing the current voice and sentence.
**************************************************************************************************************************************/

#define BMV31T001_KEY_MIDDLE 	0X01
#define BMV31T001_KEY_UP 	 	0X02
#define BMV31T001_KEY_DOWN	 	0X04
#define BMV31T001_KEY_LEFT	 	0X08
#define BMV31T001_KEY_RIGHT  	0X10

#define BMV31T001_LED_ON	 	1
#define BMV31T001_LED_OFF    	0

#define BMV31T001_BUSY	 	 	1
#define BMV31T001_NOBUSY     	0

#define BMV31T001_POWER_UP	1	 	 
#define BMV31T001_POWER_DOWN 0

#define BMV31T001_UPDATA_BEGIN  1
#define BMV31T001_NO_KEY		0

#define BMV31T001_VOLUME_MAX     11
#define BMV31T001_VOLUME_MIN	 0


void BMV31T001_Init(void);
//play funtion
void BMV31T001_setVolume(uint8_t volume);
void BMV31T001_playVoice(uint8_t num, uint8_t loop);
void BMV31T001_playSentence(uint8_t num, uint8_t loop);
void BMV31T001_playStop(void);
void BMV31T001_playPause(void);
void BMV31T001_playContinue(void);
void BMV31T001_playRepeat(void);
bool BMV31T001_isPlaying(void);
//key funtion
void BMV31T001_scanKey(void);
bool BMV31T001_isKeyAction(void);
uint8_t BMV31T001_readKeyValue(void);
//Power control
void BMV31T001_setPower(uint8_t status);
//led control
void BMV31T001_setLED(uint8_t status);
//voice source update function
void BMV31T001_initAudioUpdate(unsigned long baudrate);
bool BMV31T001_isUpdateBegin(void);
bool BMV31T001_executeUpdate(void);


#endif
