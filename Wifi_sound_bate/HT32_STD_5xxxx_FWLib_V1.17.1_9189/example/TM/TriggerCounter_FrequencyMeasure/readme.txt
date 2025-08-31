/**
 @page TM_TriggerCounter_FrequencyMeasure

 @verbatim
 * @file    TM/TriggerCounter_FrequencyMeasure/readme.txt
 * @version V1.01
 * @date    2025-02-13
 * @brief   Description of TM trigger counter for Frequency Measure example.
 @endverbatim

@par Example Description:

This example shows how to use the xxTM peripheral to count the number of pulses on an input pin.
  1. Configure the TMn CH0 as an input capture mode (rising edge)
  2. Set the Slave Trigger Input (STI) source as Filtered Input of CH0 (TI0S0, TRSEL=b0001).
  3. Set the TMn as slave mode, trigger by STI (SMSEL = b111).

  <PRE>
      |<     30 Hz     >|
                |<                      100ms                      >|
                ________          ________          ________          ________
               |        |        |        |        |        |        |        |
   ... ________|        |________|        |________|        |________|        | ...
  cap_count    1                 2                 3                            ...
               ^                                                    v               
         First Rising Edge                                                          
       ->Begin 100ms counter                               100ms counter interrupt  
           "StartValue"                                      "gCAP_Counter"      

   Note: 1.gCAP_Counter = (OverflowCounter * 65536) + (TM_GetCounter(HTCFG_CAP_PORT))
         2.Compensate_Counter = (gCAP_Counter / 10000)
           [Default: turn off, If you want to enable this mechanism, change "#if 0" to "#if 1".]
           -> A simple compensation mechanism has been added to correct test observation errors.
         3.Freq_divd_by_10 = gCAP_Counter + gCompensate_Counter
         4.Input Signal Freq = Freq_divd_by_10 * 10 (Hz)
           e.g. as shown above , 30 Hz Signal in 100ms , get gCAP_Counter = 3 , so Input Signal Freq = 30 Hz
  </PRE>

After the above setting, the counter of TMn will be incremented by one on the rising edge of xxTM CH0.

@par Directory Contents:

- TM/TriggerCounter_FrequencyMeasure/main.c                                  Main program
- TM/TriggerCounter_FrequencyMeasure/ht32f5xxxx_01_it.c                      Interrupt handlers
- TM/TriggerCounter_FrequencyMeasure/ht32_board_config.h                     Board configuration file

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Connect a Input Signal to the xxTM CHn input pin. Refer "ht32_board_config.h" for pin assignment.
- Generate a rising edge on the xxTM CHn input pin to clock the timer.
- When 100ms counter interrupt, the message shall be output, As follows
  "=============================="
  "OverflowCounter   = xxxxx"
  "CAP Timer Counter = xxxxx"
  "Freq_divd_by_10   = xxxxx"
  "Input Signal Freq = xxxxxx Hz"

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
