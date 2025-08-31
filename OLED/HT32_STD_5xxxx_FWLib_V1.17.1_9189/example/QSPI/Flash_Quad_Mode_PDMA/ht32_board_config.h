/*********************************************************************************************************//**
 * @file    QSPI/Flash_Quad_Mode_PDMA/ht32_board_config.h
 * @version $Rev:: 8284         $
 * @date    $Date:: 2024-11-22 #$
 * @brief   The header file of board configuration.
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
/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32_BOARD_CONFIG_H
#define __HT32_BOARD_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif


/* Settings ------------------------------------------------------------------------------------------------*/
/* !!! NOTICE !!!
   For the development board which uses "USE_HT32XXXXXX_DVB":
   1. The example requires external components on the expansion board but the development board can not use
      with it directly.
   2. The extra jumper/wired connections may be required to use this example.
   3. Using extra jumper/wired may affect the maximum speed and quality of the signal. For communication interface
      such as SPI/EBI/..., it may be necessary to appropriately reduce the speed by AHB/APB clock prescaler settings.
*/

#ifdef __cplusplus
}
#endif

#endif
