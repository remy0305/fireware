/* Includes ------------------------------------------------------------------------------------------------*/
#include "BMC81M001.h"

#include "BMV31T001.h"
#include "delay.h"
#include "../VoiceBroadcast/voice_cmd_list.h"

#include "ht32.h"               
#include "ht32_board.h"        
#include "ht32_board_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/

/* Global variables ----------------------------------------------------------------------------------------*/

#define WIFI_SSID "A54"
#define WIFI_PASS "remy2271"
#define IP "3.25.95.122"  
#define IP_Port 80
char writeDataBuff[10]="Hello";
char readDataBuff[30]=" ";
vu32 gwTimeDisplay = 0;
u32  TimeReg       = 0;
volatile u32 countdownTime = 0;

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
/* Private variables ---------------------------------------------------------------------------------------*/
/* Global functions ----------------------------------------------------------------------------------------*/
void _delay(vu32 count);
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
	
/*rtc Private function prototypes -----------------------------------------------------------------------------*/
void RTC_Configuration(void);   
u32  Time_Regulate(void);        
void Time_Display(u32 wTimeVar); 
u32  ScanUnsignedDecimal(void); 
char *remove_newlines_char(const char *s);
void rtc();

int main(void)
{
  RETARGET_Configuration();           // UART 115200
  BMC81M001_Init(BMC81M001_baudRate); 
	
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
		
  // =================================
  printf("TCP Connect Result:");
  BMC81M001_connectToAP(WIFI_SSID, WIFI_PASS);
  if (BMC81M001_connectTCP(IP, IP_Port) == true) {
    printf("TCP success\r\n");
  } else {
    printf("TCP fail\r\n");
  }

  BMC81M001_writeDataTcp(5, "12345"); 
  printf("hello");
	  while (1)
  {
    if (BMC81M001_readDataTcp(readDataBuff) == true) {
      printf("Received data: %s\n", readDataBuff);
      char *clean = remove_newlines_char(readDataBuff);
      printf("Cleaned data: %s\n", clean);

      if (strcmp(clean, "fall") == 0) {
        if (BMV31T001_isPlaying()) {
          BMV31T001_playStop();
          _delay(50);                
        }
				BMV31T001_playVoice(voice_table[VOC_1],0);
          
				
        BMC81M001_writeDataTcp(4, "fall");         
      }
      else if (strcmp(clean, "Timing") == 0) {
        BMC81M001_writeDataTcp(6, "Timing");
     
        if (BMV31T001_isPlaying()) {
          BMV31T001_playStop();
          _delay(50);
        }
        rtc();
				BMV31T001_playVoice(voice_table[VOC_1],0);
      }

      free(clean);
    }
  }

}

void rtc()
{
    u32 countdown = Time_Regulate();  

    printf("Countdown start: %u seconds\r\n", (unsigned int)countdown);

    while (countdown > 0)
    {
        Time_Display(countdown); 
        char msg[32];
        sprintf(msg, "Time Left: %u\r\n", (unsigned int)countdown);
        BMC81M001_writeDataTcp(strlen(msg), msg); 

        _delay(1000); 
        countdown--;
    }

    printf("Countdown finished!\r\n");
    BMC81M001_writeDataTcp(strlen("Countdown Finished"), "Countdown Finished");
}


char *remove_newlines_char(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *res = (char *)malloc(len + 1);
    if (!res) return NULL;

    char *d = res;
    for (size_t i = 0; i < len; i++) {
        if (s[i] != '\n' && s[i] != '\r') {
            *d++ = s[i];
        }
    }
    *d = '\0';
    return res;
}

/*********************************************************************************************************//**
 * @brief  delay ms.
 * @param  count
 * @retval void
 ************************************************************************************************************/
void _delay(vu32 count)//wifi
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}

//RTC******************************************
void RTC_Configuration(void)
{
  /* Reset Backup Domain                                                                                    */
  PWRCU_DeInit();

  #if (EXAMPLE_NO_LSE == 0) && (LIBCFG_LSE == 1)
  /* Configure Low Speed External clock (LSE)                                                               */
  RTC_LSESMConfig(RTC_LSESM_FAST);
  RTC_LSECmd(ENABLE);
  while (CKCU_GetClockReadyStatus(CKCU_FLAG_LSERDY) == RESET);

  /* Configure the RTC                                                                                      */
  RTC_ClockSourceConfig(RTC_SRC_LSE);
  #else
  RTC_ClockSourceConfig(RTC_SRC_LSI);
  #endif

  RTC_IntConfig(RTC_INT_CSEC, ENABLE);
  RTC_SetPrescaler(RTC_RPRE_32768);
}


/*********************************************************************************************************//**
  * @brief  Returns the time entered by user, using Hyperterminal.
  * @return Enter time, unit is second within a day.
  ***********************************************************************************************************/
u32 Time_Regulate(void)
{
    u32 Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;

    printf("\r\n==============Time Settings=====================================\r\n");

    BMC81M001_writeDataTcp(strlen("\r\n  Please Set Hours"), "\r\n  Please Set Hours");
    BMC81M001_writeDataTcp(strlen("\r\n"), "\r\n");

    do {
        Tmp_HH = ScanUnsignedDecimal();  
    } while (Tmp_HH > 23);  
    printf(":  %u\r\n", (unsigned int)Tmp_HH);

    BMC81M001_writeDataTcp(strlen("\r\n  Please Set Minutes"), "\r\n  Please Set Minutes");
    BMC81M001_writeDataTcp(strlen("\r\n"), "\r\n");

    do {
        Tmp_MM = ScanUnsignedDecimal();  
    } while (Tmp_MM > 59);
    printf(":  %u\r\n", (unsigned int)Tmp_MM);
		
    BMC81M001_writeDataTcp(strlen("\r\n  Please Set Seconds"), "\r\n  Please Set Seconds");
    BMC81M001_writeDataTcp(strlen("\r\n"), "\r\n");

    do {
        Tmp_SS = ScanUnsignedDecimal();  
    } while (Tmp_SS > 59);
    printf(":  %u\r\n", (unsigned int)Tmp_SS);

    return (Tmp_HH * 3600 + Tmp_MM * 60 + Tmp_SS);  
}



/*********************************************************************************************************//**
  * @brief  Displays the input time.
  * @param  wTimeVar: Displays time.
  * @retval None
  ***********************************************************************************************************/
void Time_Display(u32 wTimeVar)
{
  u32 THH = 0, TMM = 0, TSS = 0;

  wTimeVar %= 86400;

  /* Compute  hours                                                                                         */
  THH = wTimeVar/3600;
  /* Compute minutes                                                                                        */
  TMM = (wTimeVar % 3600)/60;
  /* Compute seconds                                                                                        */
  TSS = (wTimeVar % 3600)% 60;

  printf("Time: %02u:%02u:%02u\r", (unsigned int)THH, (unsigned int)TMM, (unsigned int)TSS);
	
}

/*********************************************************************************************************//**
  * @brief  Scan an unsigned decimal number.
  * @return An unsigned decimal value.
  ***********************************************************************************************************/
u32 ScanUnsignedDecimal(void)
{
    u32 wNbr = 0;
    char *clean = NULL;

    while (1)
    {
        memset(readDataBuff, 0, sizeof(readDataBuff));

        if (BMC81M001_readDataTcp(readDataBuff))
        {
            clean = remove_newlines_char(readDataBuff);
            if (!clean || strlen(clean) == 0 || strspn(clean, "0123456789") != strlen(clean)) {
                printf("Invalid input: %s\n", clean ? clean : "NULL");
                free(clean);
                continue;
            }
            wNbr = atoi(clean);
            free(clean);
            printf("wNbr=%u\n", wNbr);
            break;
        }
    }
    return wNbr;
}


#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif





