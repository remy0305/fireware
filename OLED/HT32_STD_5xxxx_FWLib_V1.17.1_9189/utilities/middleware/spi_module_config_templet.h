/*********************************************************************************************************//**
 * @file    spi_module_config_templet.h
 * @version $Rev:: 1066         $
 * @date    $Date:: 2024-01-22 #$
 * @brief   The header file of SPI config.
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
// <<< Use Configuration Wizard in Context Menu >>>

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __SPI_MODULE_CONFIG_H
#define __SPI_MODULE_CONFIG_H

/* Includes ------------------------------------------------------------------------------------------------*/

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup SPI SPI
  * @{
  */

/** @addtogroup SPI_CONFIG SPI CONFIG
  * @{
  */

/* Settings ------------------------------------------------------------------------------------------------*/
//<q0> Enable Debug mode
// <i> Enable Debug mode which output debug message to retarget.
#define SPICFG_DEBUG_MODE                         (0)   /*  1:Enable debug mode.    0:Disnable debug mode  */

//<o0> Support SPI Channel
//   <1=> 1
//   <2=> 2
//   <3=> 3
//   <4=> 4
// <i> SPI Channel
#define SPICFG_SUPPORT_CH                         (1)   /*  Support channel 1~4                            */

//<o0> MISO Idle Value
//   <0x00=> 0x00
//   <0x01=> 0xFF
#define SPICFG_MISOD_IDLE_VALUE                   (0)   /*  1:Idle value = 0xFF.    0:Idle value = 0x00.   */

//<e> Enable PDMA mode
//<i> Enable PDMA for TX/RX
#define SPICFG_PDMA_MODE                          (0)   /*  1:Enable DMA mode.      0:Disnable DMA mode    */

//<e> Enable CH0 PDMA
//<i> Enable PDMA Channel 0
#define SPICFG_CH0_PDMA_ENABLE                    (0)   /*  1:Enable DMA CH0 .       0:Disable DMA CH0     */
//<o> PDMA Channel 0
//   <0x00=> SPI0
//   <0x01=> SPI1
#define SPICFG_CH0_PDMA                           (0)   /*  1:SPI1.                 0:SPI0                 */
// </e>

//<e> Enable CH1 PDMA
//<i> Enable PDMA Channel 1
#define SPICFG_CH1_PDMA_ENABLE                    (0)   /*  1:Enable DMA CH1 .       0:Disable DMA CH1     */
//<o> PDMA Channel 1
//   <0x00=> SPI0
//   <0x01=> SPI1
#define SPICFG_CH1_PDMA                           (0)   /*  1:SPI1.                 0:SPI0                 */
// </e>

//<e> Enable CH2 PDMA
//<i> Enable PDMA Channel 2
#define SPICFG_CH2_PDMA_ENABLE                    (0)   /*  1:Enable DMA CH2 .       0:Disable DMA CH2     */
//<o> PDMA Channel 2
//   <0x00=> SPI0
//   <0x01=> SPI1
#define SPICFG_CH2_PDMA                           (0)   /*  1:SPI1.                 0:SPI0                 */
// </e>

//<e> Enable CH3 PDMA
//<i> Enable PDMA Channel 3
#define SPICFG_CH3_PDMA_ENABLE                    (0)   /*  1:Enable DMA CH3 .       0:Disable DMA CH3     */

//<o> PDMA Channel 3
//   <0x00=> SPI0
//   <0x01=> SPI1
#define SPICFG_CH3_PDMA                           (0)   /*  1:SPI1.                 0:SPI0                 */
// </e>

#if defined(USE_HT32F52220_30) || defined(USE_HT32F52231_41) || defined(USE_HT32F52331_41)
  #if SPICFG_PDMA_MODE
    #error "PDMA mode does not apply to the chip you selected."
  #endif
#endif
#if SPICFG_PDMA_MODE
  #if !(SPICFG_CH0_PDMA_ENABLE | SPICFG_CH1_PDMA_ENABLE | SPICFG_CH2_PDMA_ENABLE | SPICFG_CH3_PDMA_ENABLE)
    #error "At least one channel is open."
  #endif
#else
  #if (SPICFG_CH0_PDMA_ENABLE | SPICFG_CH1_PDMA_ENABLE | SPICFG_CH2_PDMA_ENABLE | SPICFG_CH3_PDMA_ENABLE)
  #warning "PDMA is not enable."
  #undef SPICFG_CH0_PDMA_ENABLE
  #undef SPICFG_CH1_PDMA_ENABLE
  #undef SPICFG_CH2_PDMA_ENABLE
  #undef SPICFG_CH3_PDMA_ENABLE
  #endif
#endif
// </e>

//<h>SPI Config
//<h>CH0
//<o0> SPI Mode
//   <1=> SPI_MASTER
//   <0=> SPI_SLAVE
//<o1> SPI SEL Polarity
//   <1=> SPI_SELPOLARITY_HIGH
//   <0=> SPI_SELPOLARITY_LOW
//<o2> SPI First Bit
//   <1=> SPI_FIRSTBIT_LSB
//   <0=> SPI_FIRSTBIT_MSB
//<o3> SPI CPOL
//   <1=> SPI_CPOL_HIGH
//   <0=> SPI_CPOL_LOW
//<o4> SPI CPHA
//   <1=> SPI_CPHA_SECOND
//   <0=> SPI_CPHA_FIRST
//<o5> SPI Clock n Hz
// <i> Master mode speed up to fPCLK/2. 
// <i> Slave mode speed up to fPCLK/3.
// <i> lower limit : fPCLK / 131072
// </h>
//<h>CH1
//<o6> SPI Mode
//   <1=> SPI_MASTER
//   <0=> SPI_SLAVE
//<o7> SPI SEL Polarity
//   <1=> SPI_SELPOLARITY_HIGH
//   <0=> SPI_SELPOLARITY_LOW
//<o8> SPI First Bit
//   <1=> SPI_FIRSTBIT_LSB
//   <0=> SPI_FIRSTBIT_MSB
//<o9> SPI CPOL
//   <1=> SPI_CPOL_HIGH
//   <0=> SPI_CPOL_LOW
//<o10> SPI CPHA
//   <1=> SPI_CPHA_SECOND
//   <0=> SPI_CPHA_FIRST
//<o11> SPI Clock n Hz
// <i> Master mode speed up to fPCLK/2. 
// <i> Slave mode speed up to fPCLK/3.
// <i> lower limit : fPCLK / 131072
// </h>
//<h>CH2
//<o12> SPI Mode
//   <1=> SPI_MASTER
//   <0=> SPI_SLAVE
//<o13> SPI SEL Polarity
//   <1=> SPI_SELPOLARITY_HIGH
//   <0=> SPI_SELPOLARITY_LOW
//<o14> SPI First Bit
//   <1=> SPI_FIRSTBIT_LSB
//   <0=> SPI_FIRSTBIT_MSB
//<o15> SPI CPOL
//   <1=> SPI_CPOL_HIGH
//   <0=> SPI_CPOL_LOW
//<o16> SPI CPHA
//   <1=> SPI_CPHA_SECOND
//   <0=> SPI_CPHA_FIRST
//<o17> SPI Clock n Hz
// <i> Master mode speed up to fPCLK/2. 
// <i> Slave mode speed up to fPCLK/3.
// <i> lower limit : fPCLK / 131072
// </h>
//<h>CH3
//<o18> SPI Mode
//   <1=> SPI_MASTER
//   <0=> SPI_SLAVE
//<o19> SPI SEL Polarity
//   <1=> SPI_SELPOLARITY_HIGH
//   <0=> SPI_SELPOLARITY_LOW
//<o20> SPI First Bit
//   <1=> SPI_FIRSTBIT_LSB
//   <0=> SPI_FIRSTBIT_MSB
//<o21> SPI CPOL
//   <1=> SPI_CPOL_HIGH
//   <0=> SPI_CPOL_LOW
//<o22> SPI CPHA
//   <1=> SPI_CPHA_SECOND
//   <0=> SPI_CPHA_FIRST
//<o23> SPI Clock n Hz
// <i> Master mode speed up to fPCLK/2. 
// <i> Slave mode speed up to fPCLK/3.
// <i> lower limit : fPCLK / 131072
// </h>
// </h>
#define SPICFG_CH0_MODE                           (1)   /*  1:SPI_MASTER.           0:SPI_SLAVE             */
#define SPICFG_CH0_SEL_POLARITY                   (0)   /*  1:SPI_SELPOLARITY_HIGH. 0:SPI_SELPOLARITY_LOW   */
#define SPICFG_CH0_FIRST_BIT                      (0)   /*  1:SPI_FIRSTBIT_LSB.     0:SPI_FIRSTBIT_MSB      */
#define SPICFG_CH0_CPOL                           (0)   /*  1:SPI_CPOL_HIGH.        0:SPI_CPOL_LOW          */
#define SPICFG_CH0_CPHA                           (0)   /*  1:SPI_CPHA_SECOND.      0:SPI_CPHA_FIRST        */
#define _SPICFG_CH0_CLOCK_DIV                     (500000)  /* 500K Hz                                      */

#define SPICFG_CH1_MODE                           (1)   /*  1:SPI_MASTER.           0:SPI_SLAVE             */
#define SPICFG_CH1_SEL_POLARITY                   (0)   /*  1:SPI_SELPOLARITY_HIGH. 0:SPI_SELPOLARITY_LOW   */
#define SPICFG_CH1_FIRST_BIT                      (0)   /*  1:SPI_FIRSTBIT_LSB.     0:SPI_FIRSTBIT_MSB      */
#define SPICFG_CH1_CPOL                           (0)   /*  1:SPI_CPOL_HIGH.        0:SPI_CPOL_LOW          */
#define SPICFG_CH1_CPHA                           (0)   /*  1:SPI_CPHA_SECOND.      0:SPI_CPHA_FIRST        */
#define _SPICFG_CH1_CLOCK_DIV                     (500000)   /* 500K Hz                                    */

#define SPICFG_CH2_MODE                           (1)   /*  1:SPI_MASTER.           0:SPI_SLAVE             */
#define SPICFG_CH2_SEL_POLARITY                   (0)   /*  1:SPI_SELPOLARITY_HIGH. 0:SPI_SELPOLARITY_LOW   */
#define SPICFG_CH2_FIRST_BIT                      (0)   /*  1:SPI_FIRSTBIT_LSB.     0:SPI_FIRSTBIT_MSB      */
#define SPICFG_CH2_CPOL                           (0)   /*  1:SPI_CPOL_HIGH.        0:SPI_CPOL_LOW          */
#define SPICFG_CH2_CPHA                           (0)   /*  1:SPI_CPHA_SECOND.      0:SPI_CPHA_FIRST        */
#define _SPICFG_CH2_CLOCK_DIV                     (500000)   /* 500K Hz                                    */

#define SPICFG_CH3_MODE                           (1)   /*  1:SPI_MASTER.           0:SPI_SLAVE             */
#define SPICFG_CH3_SEL_POLARITY                   (0)   /*  1:SPI_SELPOLARITY_HIGH. 0:SPI_SELPOLARITY_LOW   */
#define SPICFG_CH3_FIRST_BIT                      (0)   /*  1:SPI_FIRSTBIT_LSB.     0:SPI_FIRSTBIT_MSB      */
#define SPICFG_CH3_CPOL                           (0)   /*  1:SPI_CPOL_HIGH.        0:SPI_CPOL_LOW          */
#define SPICFG_CH3_CPHA                           (0)   /*  1:SPI_CPHA_SECOND.      0:SPI_CPHA_FIRST        */
#define _SPICFG_CH3_CLOCK_DIV                     (500000)   /* 500K Hz                                    */

/* If MCU is LIBCFG_SPI_CLK_PRE_V01, then the prescaler range is 2 to 65536, otherwise, the prescaler range
   2 to 65536*2. */
   
#if (__CORTEX_M == 4)
#define SPICFG_CH0_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH0_CLOCK_DIV/2)
#define SPICFG_CH1_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH1_CLOCK_DIV/2)
#define SPICFG_CH2_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH2_CLOCK_DIV/2)
#define SPICFG_CH3_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH3_CLOCK_DIV/2)
#else
#define SPICFG_CH0_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH0_CLOCK_DIV)
#define SPICFG_CH1_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH1_CLOCK_DIV)
#define SPICFG_CH2_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH2_CLOCK_DIV)
#define SPICFG_CH3_CLOCK_PRESCALER                (SystemCoreClock/_SPICFG_CH3_CLOCK_DIV)
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

#endif
