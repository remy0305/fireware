/**
 @page ADC_OneShot_SWTrigger_ByTM

 @verbatim
 * @file    ADC/OneShot_SWTrigger_ByTM/readme.txt
 * @version V2.00
 * @date    2021-03-19
 * @brief   Description of Software trigger ADC start of conversion example.
 @endverbatim

@par Example Description:

This example shows how to trigger ADC by software mode according to the Timer's interrupt.

!!! NOTICE !!!
The following ADC pin settings shall be modified according to the MCU part number.
  "GPIO_Px", "AFIO_PIN_n"
  "ADC_CH_n"

void ADC_Configuration(void)
{
  ...
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_0, AFIO_FUN_ADC0);
  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_1, AFIO_FUN_ADC0);
  ...
  ADC_RegularChannelConfig(HT_ADC0, ADC_CH_2, 0);
  ADC_RegularChannelConfig(HT_ADC0, ADC_CH_3, 0);
}

  <PRE>
  ================     =================     =================     =================
  =              =     =               =     =    ADC ISR    =     =     Main()    =
  =    BFTM      = --> =      ADC      = --> =   Save Value  = --> =     print     =
  =              =     = One Shot mode =     =  gADC_Result  =     =   gADC_Result =
  ================     =================     =================     =================
                Software               Cycle End      gADC_CycleEndOfConversion
                Trigger
  </PRE>

ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - One Shot mode, sequence length = 2
  - Set ADST = 36, sampling time = 1.5 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC
  - Set ADC conversion sequence 0 ~ 1 as channel n.
  - Set ADC trigger source as software.

Timer configuration:
  - Timer interrupt   = 1 Second

The "ADC_MainRoutine()" will trigger the ADC start conversion every 2 second (when the "gADC_TimeCount"
down count to 0).

The cycle-end of conversion interrupt is enabled. Each time the ADC cycle conversion is finished (Two
channels are finished), a "cycle-end of conversion" interrupt will be occurred. The ADC interrupt service
routine will store the ADC result into the global variable, "gADC_Result[]".

If the USART/UART is connected to PC, the ADC result will be printed on the terminal.

@par Directory Contents:

- ADC/ADC_OneShot_SWTrigger_ByTM/main.c                     Main program
- ADC/ADC_OneShot_SWTrigger_ByTM/ht32fxxxxx_nn_it.c         Interrupt handlers
- ADC/ADC_OneShot_SWTrigger_ByTM/ht32_board_config.h        Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.
- You need a terminal software such as TeraTerm (https://ttssh2.osdn.jp/).
- Connect a null-modem female/female RS232 cable between the UxART and PC serial port.
  Terminal configuration:
  - Word length = 8 Bits
  - One stop bit
  - No parity
  - BaudRate = 115200 baud
  - Flow control: None

@par Firmware Disclaimer Information

1. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
   proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
   other intellectual property laws.

2. The customer hereby acknowledges and agrees that the program technical documentation, including the
   code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
   other than HOLTEK and the customer.

3. The program technical documentation, including the code, is provided "as is" and for customer reference
   only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
   the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
   the warranties of merchantability, satisfactory quality and fitness for a particular purpose.

 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 */
