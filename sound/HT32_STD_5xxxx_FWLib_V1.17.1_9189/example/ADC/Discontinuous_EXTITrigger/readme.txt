/**
@page ADC_Discontinuous_EXTITrigger

 @verbatim
 * @file    ADC/Discontinuous_EXTITrigger/readme.txt
 * @version V2.00
 * @date    2020-02-27
 * @brief   Description of EXTI trigger ADC discontinuous mode example.
 @endverbatim

@par Example Description:

This example shows how to use the ADC discontinuous mode triggered by the EXTI channel.

ADC configuration:
  - ADC clock frequency: CK_ADC = CK_AHB / 64
  - Discontinuous mode, sequence length = 3, subgroup length = 2
  - Set ADST = 0, sampling time = 1.5 + ADST
  - Conversion time = (Sampling time + Latency) / CK_ADC = (1.5 + ADST + 12.5) / CK_ADC
  - Set ADC conversion sequence 0 ~ 3 as channel n.
  - Set EXTI channel n as ADC trigger source.

The subgroup 0 includes:
  - Sequence 0 used to convert Channel n1.
  - Sequence 1 used to convert Channel n2.

The subgroup 1 includes:
  - Sequence 2 used to convert Channel n3.

The cycle-end of conversion and subgroup EOC (end of conversion) interrupts are enabled. The ADC interrupt
service routine will store ADC result into the global variable "gADC_Result[]". The subgroup length is 2, so
that every 2 ADC single EOC trigger a subgroup EOC interrupt. Because sequence length is 3 and subgroup length
is 2, the last subgroup length is 1. When the last subgroup is finished, both cycle-end and subgroup EOC flag
are set. The program can use the cycle-end of conversion to distinguish the last subgroup.

If the UxART is connected to PC, the ADC result will be printed on the terminal as below.

<PRE>
Sequence0:nnnn Sequence1:nnnn
Sequence2:nnnn
</PRE>

@par Directory Contents:

- ADC/Discontinuous_EXTITrigger/main.c                      Main program
- ADC/Discontinuous_EXTITrigger/ht32fxxxxx_nn_it.c          Interrupt handlers
- ADC/Discontinuous_EXTITrigger/ht32_board_config.h         Board configuration file

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
