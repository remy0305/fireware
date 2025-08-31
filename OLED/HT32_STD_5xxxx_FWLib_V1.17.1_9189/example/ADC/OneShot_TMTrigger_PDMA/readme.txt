/**
 @page ADC_OneShot_TMTrigger_PDMA

 @verbatim
 * @file    ADC/OneShot_TMTrigger_PDMA/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of PDMA move ADC result example.
 @endverbatim

@par Example Description:

This example shows how to use TM trigger the ADC and use PDMA to move ADC result from ADC data register to TM
compare match register, to control the LED output by PWM. The flow is as below:

  <PRE>
  ================     =================     =================     =================     =================
  =              =     =               =     =               =     =               =     =               =
  =      TM      = --> =      ADC      = --> =      PDMA     = --> =       TM      = --> =      LED      =
  =              =     = One Shot mode =     =               =     =     CHnCCR    =     =               =
  ================     =================     =================     =================     =================
     Update Event->MTO                Cycle-End                                   PWM Output
  </PRE>

ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - One Shot mode, sequence length = 1
  - Set ADST = 0, sampling time = 1.5 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC
  - Set ADC conversion sequence 0 as channel n.
  - Set TM MTO as ADC trigger source.
  - Trigger PDMA when cycle-end of conversion.

Timer configuration:
  - Timer clock   = CK_AHB / 100
  - PWM reload    = 4096
  - PWM frequency = CK_AHB / 100 / 4096 (Example: 48 MHz / 100 / 4096 = 117.1 kHz)
  - MTO source is Update Event.
  - TM CHnO is configured as PWM2 output mode.

PDMA configuration:
  - Data width = 32-bit
  - Block length = 1, block count = 1
  - Enable Auto Reload.
  - Source: HT_ADCn->DR[0] (ADC data register for sequence 0)
  - Destination: TM CHnCCR (Timer CHn compare register)

@par Directory Contents:

- ADC/OneShot_TMTrigger_PDMA/main.c                         Main program
- ADC/OneShot_TMTrigger_PDMA/ht32fxxxxx_nn_it.c             Interrupt handlers
- ADC/OneShot_TMTrigger_PDMA/ht32_board_config.h            Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Adjust the potentiometer to change the voltage level of ADC input and observe the LED.

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
