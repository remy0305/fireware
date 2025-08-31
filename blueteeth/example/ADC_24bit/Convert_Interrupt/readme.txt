/**
 @page ADC_24bit_Convert_Interrupt

 @verbatim
 * @file    ADC_24bit/Convert_Interrupt/readme.txt
 * @version V1.00
 * @date    2021-01-19
 * @brief   Description of delta-sigma ADC example.
 @endverbatim

@par Example Description:

This example shows how to use the delta-sigma ADC to get the ADC value.

The ADC related register is accessed via the I2C (Settings is located in the file, "delta_sigma_adc.h").
  - MCU I2C master to ADC I2C slave.
  - ADC Slave address = 0x68 (HFCFG_I2C_SLAVE_ADDRESS).
  - I2C Speed = 100 kHz (HTCFH_I2C_MASTER_CLOCK_SPEED).

The DRDYB interrupt pin of ADC is connected to the EXTI (low active), it triggers the EXTI interrupt when EOC.
Refer to the "delta_sigma_adc.h" for the settings of the delta-sigma ADC.

@par Directory Contents:

- ADC_24bit/Convert_Interrupt/main.c                        Main program
- ADC_24bit/Convert_Interrupt/ht32fxxxxx_nn_it.c            Interrupt handlers
- ADC_24bit/Convert_Interrupt/ht32_board_config.h           Board configuration file
- ADC_24bit/Convert_Interrupt/delta_sigma_adc.c             Delta sigma ADC driver.
- ADC_24bit/Convert_Interrupt/delta_sigma_adc.h             The header file of delta sigma ADC driver.

@par Hardware and Software Environment:

- This example can be run on the HT32 series development kit.
- Refer "ht32_board_config.h" for pin assignment.

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
