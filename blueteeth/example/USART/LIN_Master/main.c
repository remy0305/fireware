/*********************************************************************************************************//**
 * @file    USART/LIN_Master/main.c
 * @version $Rev:: 9183         $
 * @date    $Date:: 2025-06-23 #$
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
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "lin.h"
#include "ht32_time.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup USART_Examples USART
  * @{
  */

/** @addtogroup LIN_Master
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
#define LIN_TEST_PID_NUM                          (3)
#define LIN_TEST_PID                              0x06, 0x08, 0x0A

/* Private function prototypes -----------------------------------------------------------------------------*/
void UxART_LIN_Configuration(void);

void LIN_TestFun1(u8 uPID);
void LIN_TestFun2(void);
void LIN_TestDumpRx(LIN_RxInfoTypeDef *pRxInfo);
void LIN_TestErrorProcess(u8 uPID, s32 sResult, LIN_RxInfoTypeDef *pRxInfo);

void LIN_UserMainRoutine(void);
void LIN_UserPIDHandler(u8 uPID);

/* Global variables ----------------------------------------------------------------------------------------*/
u8 guRx_Buffer[8 + 1]; // Max 8 bytes data + 1 bytes checksum
u8 guRx_BufferFun1[2 + 1]; // 2 bytes data + 1 bytes checksum

u8 guTestLINData[8 + 1]; // Max 8 bytes data + 1 bytes checksum
u8 guTestLINData2[4 + 1] = {0xA0, 0xA1, 0xA2, 0xA3, 0x00}; // 4 bytes data + 1 bytes checksum

u8 guPIDArray[LIN_TEST_PID_NUM] = {LIN_TEST_PID};

/* Private variables ---------------------------------------------------------------------------------------*/

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
  #if !HTCFG_ONLY_ONE_UART
  RETARGET_Configuration();
  #endif

  Time_Init(); // lin.c required HT32 Time function

  /* !!! NOTICE !!!
     Since the LIN is a single wire bus, for convenience we may connect the Master/Slave UxART Tx and Rx pin
     directly without an external LIN Phy chip for the test purposes. In this case, you MUST turn on the
     Open-Drain in the UxART Tx pin. Otherwise, the Master/Slave Tx pin will be conflicted. Those settings can
     be disabled if external LIN Phy chip is connected.
     The pull-up resistor of Rx pin is turned on. The external pull-up resistor may need if the the baudrate
     speed is high.
  */
  UxART_LIN_Configuration();

  #if 1
  LIN_Init(guRx_Buffer, LIN_UserPIDHandler);
  #else
  LIN_Init(guRx_Buffer, NULL); // Call the User PID Handler by LIN_UserMainRoutine
  #endif

  LIN_TestFun1(0x04);

  while (1)
  {
    LIN_TestFun2();

    #if 0
    LIN_UserMainRoutine();
    #endif
  }
}

/*********************************************************************************************************//**
  * @brief  LIN test function 1.
  * @retval None
  ***********************************************************************************************************/
void LIN_TestFun1(u8 uPID)
{
  s32 sResult;
  LIN_RxInfoTypeDef RxInfo;

  if (LIN_StartFrame(uPID) == ERROR)
  {
    // Do the process when send error
    // ...
    #if 1
      #if !HTCFG_ONLY_ONE_UART
      printf("PID = 0x%02X, Send error\r\n", uPID);
      #endif
    #endif
    LIN_ResetState();
    return;
  }

  // Get status in blocking way
  do
  {
    sResult = LIN_GetStatus(&RxInfo);
  } while (sResult == LIN_PROCESS);

  if (sResult == LIN_FINISH)
  {
    // Process data here if need
    // ...
    #if 1
    LIN_TestDumpRx(&RxInfo);
    #endif
  }
  else
  {
    LIN_TestErrorProcess(uPID, sResult, &RxInfo);
  }
}

/*********************************************************************************************************//**
  * @brief  LIN test function 2.
  * @retval None
  ***********************************************************************************************************/
void LIN_TestFun2(void)
{
  static s32 gsStep = -1;
  static u32 guStartTime = 0;
  static u8 guCurrentPID = 0;

  s32 sResult;
  LIN_RxInfoTypeDef RxInfo;

  if (TIME_TICK2MS(TIME_TICKDIFF(guStartTime, Time_GetTick())) >= 2000)
  {
    // Start send PID every 2000 ms
    guStartTime = Time_GetTick();
    gsStep = 0;
    #if !HTCFG_ONLY_ONE_UART
    printf("\r\n");
    #endif
  }

  if (gsStep >= 0)
  {
    // Get LIN status in non-blocking way
    sResult = LIN_GetStatus(&RxInfo);

    if (sResult == LIN_PROCESS)
    {
      return;
    }

    if (sResult == LIN_NOTUSE)
    {
      guCurrentPID = guPIDArray[gsStep];
      if (LIN_StartFrame(guCurrentPID) == ERROR)
      {
        // Do the process when send error
        // ...
        #if 1
          #if !HTCFG_ONLY_ONE_UART
          printf("PID = 0x%02X, send error\r\n", guCurrentPID);
          #endif
        #endif
        LIN_ResetState();
      }
      gsStep++;
    }
    else
    {
      if (sResult == LIN_FINISH)
      {
        // Process data here if need
        // ...
        #if 1
        LIN_TestDumpRx(&RxInfo);
        #endif
      }
      else
      {
        LIN_TestErrorProcess(guCurrentPID, sResult, &RxInfo);
      }

      if (gsStep >= LIN_TEST_PID_NUM)
      {
        gsStep = -1;
      }
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Dump Rx Data.
  * @param  pRxInfo: Rx information.
  * @retval None
  ***********************************************************************************************************/
void LIN_TestDumpRx(LIN_RxInfoTypeDef *pRxInfo)
{
  #if !HTCFG_ONLY_ONE_UART
  u32 i;
  printf("PID = 0x%02X", LIN_GETID(pRxInfo->uPID));

  if (pRxInfo->uLnegth > 0 && pRxInfo->pBuffer != NULL)
  {
    printf(", Received: ");
    for (i = 0; i < pRxInfo->uLnegth; i++)
    {
      printf("%02X ", pRxInfo->pBuffer[i]);
    }
  }

  printf("\r\n");
  #endif
}

/*********************************************************************************************************//**
  * @brief  Error process.
  * @param  uPID: Protected Identifier.
  * @param  sResult: Result from LIN_GetStatus().
  * @param  pRxInfo: Rx information.
  * @retval None
  ***********************************************************************************************************/
void LIN_TestErrorProcess(u8 uPID, s32 sResult, LIN_RxInfoTypeDef *pRxInfo)
{
  if (sResult < 0)
  {
    #if !HTCFG_ONLY_ONE_UART
    printf("PID = 0x%02X, ", uPID);
    #endif
    LIN_ResetState();
  }

  switch (sResult)
  {
    case LIN_TIMEOUT:
    {
      #if !HTCFG_ONLY_ONE_UART
      printf("timeout no response\r\n");
      #endif
      break;
    }
    case LIN_ERROR:
    {
      #if !HTCFG_ONLY_ONE_UART
      printf("error = 0x%02X\r\n", pRxInfo->uLINState);
      #endif
      break;
    }
    case LIN_CHECKSUMERROR:
    {
      #if !HTCFG_ONLY_ONE_UART
      printf("checksum error, ");
      #endif
      LIN_TestDumpRx(pRxInfo);
      break;
    }
    case LIN_PROCESS:
    case LIN_FINISH:
    default:
    {
      break;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Configure the UxART
  * @retval None
  ***********************************************************************************************************/
void UxART_LIN_Configuration(void)
{
  #if 0 // Use following function to configure the IP clock speed.
  // The UxART IP clock speed must be faster 16x then the baudrate.
  CKCU_SetPeripPrescaler(CKCU_PCLK_UxARTn, CKCU_APBCLKPRE_DIV2);
  #endif

  { /* Enable peripheral clock of AFIO, UxART                                                               */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.AFIO                   = 1;
    CKCUClock.Bit.HTCFG_UART_RX_GPIO_CLK = 1;
    CKCUClock.Bit.HTCFG_UART_IPN         = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }

  /* !!! NOTICE !!!
     Since the LIN is a single wire bus, for convenience we may connect the Master/Slave UxART Tx and Rx pin
     directly without an external LIN Phy chip for the test purposes. In this case, you MUST turn on the
     Open-Drain in the UxART Tx pin. Otherwise, the Master/Slave Tx pin will be conflicted. Those settings can
     be disabled if external LIN Phy chip is connected.
     The pull-up resistor of Rx pin is turned on. The external pull-up resistor may need if the the baudrate
     speed is high.
  */
  #if 1
  { /* Enable peripheral clock of AFIO, UxART                                                               */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.HTCFG_UART_TX_GPIO_CLK = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
  }
  GPIO_OpenDrainConfig(HTCFG_UART_TX_GPIO_PORT, HTCFG_UART_TX_GPIO_PIN, ENABLE);
  #endif

  /* Turn on UxART Rx internal pull-up resistor to prevent unknow state                                     */
  GPIO_PullResistorConfig(HTCFG_UART_RX_GPIO_PORT, HTCFG_UART_RX_GPIO_PIN, GPIO_PR_UP);

  /* Config AFIO mode as UxART function.                                                                    */
  AFIO_GPxConfig(HTCFG_UART_TX_GPIO_ID, HTCFG_UART_TX_AFIO_PIN, AFIO_FUN_USART_UART);
  AFIO_GPxConfig(HTCFG_UART_RX_GPIO_ID, HTCFG_UART_RX_AFIO_PIN, AFIO_FUN_USART_UART);

  {
    /* UxART configured as follow:
          - BaudRate = LIN_BAUDRATE baud in lin.h
          - Word Length = 8 Bits
          - One Stop Bit
          - None parity bit
    */

    /* !!! NOTICE !!!
       Notice that the local variable (structure) did not have an initial value.
       Please confirm that there are no missing members in the parameter settings below in this function.
    */
    USART_InitTypeDef USART_InitStructure = {0};
    USART_InitStructure.USART_BaudRate = LIN_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    #if (LIBCFG_USART_LIN == 1 && LIN_FORCR_UART_MODE == 0)
    USART_InitStructure.USART_Mode = USART_MODE_LIN;
    #else
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
    #endif
    USART_Init(HTCFG_UART_PORT, &USART_InitStructure);
  }

  #if (LIBCFG_USART_LIN == 1 && LIN_FORCR_UART_MODE == 0)
  USART_LIN_LengthSelect(HTCFG_UART_PORT, USART_LINLENGTH_10BIT);
  #endif

  /* Enable UxART interrupt of NVIC                                                                         */
  NVIC_EnableIRQ(HTCFG_UART_IRQn);

  /* Enable UxART Rx interrupt                                                                              */
  #if (LIBCFG_USART_LIN == 1 && LIN_FORCR_UART_MODE == 0)
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_RXDR | USART_INT_LBD, ENABLE);
  #else
  USART_IntConfig(HTCFG_UART_PORT, USART_INT_RXDR, ENABLE);
  #endif

  /* Enable UxART Tx and Rx function                                                                        */
  USART_TxCmd(HTCFG_UART_PORT, ENABLE);
  USART_RxCmd(HTCFG_UART_PORT, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  LIN test main routine.
  * @retval None
  ***********************************************************************************************************/
void LIN_UserMainRoutine(void)
{
  if (LIN_IsPIDReady() == TRUE)
  {
    LIN_UserPIDHandler(LIN_GetPID());
  }
}

/*********************************************************************************************************//**
  * @brief  PID User handler.
  * @param  uPID: Protected Identifier.
  * @retval None
  ***********************************************************************************************************/
void LIN_UserPIDHandler(u8 uPID)
{
  static u8 uDataIndex = 0;
  switch (uPID)
  {
    case 0x04:
    {
      // Receive the response of the PID
      LIN_SetTxRxAttributes(LIN_RX, guRx_Buffer, 2, LIN_CHECKSUM_CLASSIC);
      break;
    }
    case 0x06:
    {
      // Repsonse to the PID and receive the Tx data to buffer for checking
      LIN_SetTxRxAttributes(LIN_TX, guRx_Buffer, 8, LIN_CHECKSUM_ENHANCED);
      guTestLINData[0] = uDataIndex++;
      guTestLINData[1] = 0x01;
      guTestLINData[2] = 0x02;
      guTestLINData[3] = 0x03;
      guTestLINData[4] = 0x04;
      guTestLINData[5] = 0x05;
      guTestLINData[6] = 0x06;
      guTestLINData[7] = 0x07;
      LIN_SendResponse(uPID, guTestLINData, 8, LIN_CHECKSUM_ENHANCED);
      break;
    }
    case 0x08:
    {
      // Receive the response of the PID
      LIN_SetTxRxAttributes(LIN_RX, guRx_BufferFun1, 2, LIN_CHECKSUM_ENHANCED);
      break;
    }
    case 0x0A:
    {
      // Repsonse to the PID and receive the Tx data to buffer for checking
      LIN_SetTxRxAttributes(LIN_TX, guRx_Buffer, 4, LIN_CHECKSUM_ENHANCED);
      #if 0
      guTestLINData2[0] = 0xA0;
      guTestLINData2[1] = 0xA1;
      guTestLINData2[2] = 0xA2;
      guTestLINData2[3] = 0xA3;
      #endif
      LIN_SendResponse(uPID, guTestLINData2, 4, LIN_CHECKSUM_ENHANCED);
      break;
    }
    default:
    {
      break;
    }
  }
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


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
