/**
 @page ADC_OneShot_PWMTrigger_Dual_ADC

 @verbatim
 * @file    ADC/OneShot_PWMTrigger_Dual_ADC/readme.txt
 * @version V1.00
 * @date    2020-10-27
 * @brief   Description of Timer PWM trigger Dual ADC start of conversion example.
 @endverbatim

@par Example Description:

This example shows how to trigger Dual ADC by GPTM0 compare match of CH3 (CH3O).

  <PRE>
  ================     =================     =================     =================
  =              =     =               =     =    ADC ISR    =     =     Main()    =
  =    GPTM      = --> =      ADC      = --> =   Save Value  = --> =     print     =
  =              =     = One Shot mode =     =  gADC0_Result  =    =   gADC0_Result =
  =              =     = One Shot mode =     =  gADC1_Result  =    =   gADC1_Result =
  ================     =================     =================     =================
                  CH3O                Cycle End      gADC0_CycleEndOfConversion
                  CH3O                Cycle End      gADC1_CycleEndOfConversion
  </PRE>

Dual ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - Dual Cascade Regular mode on ADC1, delayTime = 0
  - One Shot mode, sequence length = 2
  - Set ADST = 36, sampling time = 1.5 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC
  - Set ADC conversion sequence 0 ~ 1 as channel n.
  - Set GPTM0 CH3O as ADC trigger source.

Timer configuration:
  - Timer clock   = 40 kHz (CK_AHB / (CK_AHB / 40000))
  - PWM reload    = 40000
  - PWM frequency = 40 kHz / 40000 = 1 Hz (Example: 48 MHz / (48 MHz / 40000) / 40000 = 1 Hz)
  - TM CH3O is configured as PWM2 mode, compare match value = 20000 (20000 / 40000 = 50% duty).

The cycle-end of conversion interrupt is enabled. Each time the ADC cycle conversion is finished (Two
channels are finished), a "cycle-end of conversion" interrupt will be occurred. The ADC interrupt service
routine will store the ADC result into the global variable, "gADC0_Result[]" and "gADC1_Result[]".

If the USART/UART is connected to PC, the ADC result will be printed on the terminal. Besides, LED1 ~ LED3
represent to GPTM0 CH3 compare match (trigger), ADC0 cycle-end of conversion, and ADC1 cycle-end of conversion.

@par Directory Contents:

- ADC/OneShot_PWMTrigger_Dual_ADC/main.c                             Main program
- ADC/OneShot_PWMTrigger_Dual_ADC/ht32fxxxxx_nn_it.c                 Interrupt handlers
- ADC/OneShot_PWMTrigger_Dual_ADC/ht32_board_config.h                Board configuration file

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
