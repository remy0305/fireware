/*********************************************************************************************************//**
 * @file    i2c_master_config.h
 * @version $Rev:: 816          $
 * @date    $Date:: 2023-04-14 #$
 * @brief   The header file of i2c config.
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
#ifndef __I2C_MASTER_CONFIG_H
#define __I2C_MASTER_CONFIG_H

/* Settings ------------------------------------------------------------------------------------------------*/
//<q0> Enable Debug Mode
// <i> Enable debug mode which output debug message to retarget.
#define I2C_MASTER_DEBUG_MODE               (0)     /* 0:Disnable debug mode, 1:Enable debug mode.          */

//<o0> Support I2C Master Channel
//   <1=> 1
//   <2=> 2
//   <3=> 3
//   <4=> 4
// <i> I2C Master Channel
#define I2C_MASTER_SUPPORT_CH               (1)     /* Support channel 1~4                                  */

//<q0> Enable Master NACK Auto Retry
// <i> Master NACK auto retry by I2CMaster_GetStatus().
#define I2C_MASTER_NACK_AUTO_RETRY          (0)     /* Auto retry when NACK by I2CMaster_GetStatus()        */

//<q0> Enable Clock Generated
// <i> Master generates clock in the initialization phase.
#define I2C_MASTER_INITIAL_BUS              (0)     /* Master generates clock in the initialization phase.  */

//<e0> Enable I2C Hardware Time-out Mode Configuration
// <i> The hardware time-out calculator is:
// <i> F_PCLK = CK_AHB / (2 ^ I2CPCLK)    (I2CPCLK: APB Peripheral Clock Prescaler)
// <i> F_I2CTO = F_PCLK / (2 ^ PSC)
// <i> Time-out = TOUT / F_I2CTO
//    <o1> Counter Prescaler Selection (2 ^ PSC)
//       <0=> /1
//       <1=> /2
//       <2=> /4
//       <3=> /8
//       <4=> /16
//       <5=> /32
//       <6=> /64
//       <7=> /128
//     <i> F_I2CTO = F_PCLK / (2 ^ PSC)
//    <o2> Counter Preload Value (TOUT) <1-0xFFFF:1>
//     <i> Time-out = TOUT / F_I2CTO
//     <i> TOUT range of (1 ~ 0xFFFF).
//</e>
#define I2C_MASTER_HW_TIMEOUT_MODE          (0)     /* 0: DISABLE, 1: ENABLE                                */
#define I2C_MASTER_HW_TIMEOUT_DIV           (2)     /* Timeout Clock = TOUT / (Core Clock / (2 ^ I2C_MASTER_HW_TIMEOUT_DIV))  */
#define I2C_MASTER_HW_TIMEOUT_BASE          (1000)  /* TOUT                                                 */

//<e0> Enable I2C Software Time-out Mode Configuration
// <i> The software time-out configuration is based on Interrupt or Tick mode.
//    <o0> I2C Software Time-out Mode Selection
//       <1=> Interrupt Mode
//       <2=> Tick Mode
//       <i> 1 = Interrupt Mode
//       <i> 2 = Tick Mode
//    <o1> Time-out Timer Base (Hz) <1-0xFFFFFFFF:1>
//       <i> Please follow the external interrupt / tick source parameter.
//       <i> (Tick refer to "ht32fxxxxx_conf.h")
//</e>
#define I2C_MASTER_SW_TIMEOUT_MODE          (1)     /* 1: Interrupt, 2: TimeTick                            */
#define I2C_MASTER_SW_TIMEOUT_BASE          (1000)  /* Time-out Timer Base (Hz)                             */

#endif
