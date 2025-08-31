/*********************************************************************************************************//**
 * @file    delta_sigma_adc.h
 * @version $Rev:: 5193         $
 * @date    $Date:: 2021-01-25 #$
 * @brief   The header file of delta sigma ADC driver.
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
#ifndef __DELTA_SIGMA_ADC_H
#define __DELTA_SIGMA_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#define HTCFH_I2C_MASTER_CLOCK_SPEED              (100000)
#define HTCFG_I2C_MASTER_ADDRESS                  (0x0A)
#define HFCFG_I2C_SLAVE_ADDRESS                   (0x68)

#define ADC_SKIP_COUNT                            (3) // Skip first n times of sample

#define VCMEN   1       // VCM function - 0: Disable, 1: Enable

#define FADCK   0x28    // Performance optimizing bits - 0x28: fADCK = fMCLK/30, 0x2C: fADCK = fMCLK/12

#define VGS     0       // VREF gain - 0: VREFGN = 1
                        //             1: VREFGN = 1/2
                        //             2: VREFGN = 1/4

#define AGS     0       // ADC gain - 0: ADGN = 1, 1: ADGN = 2 (for Gain = 128 = PGAGNxADGN = 64x2)

#define PGS     5       // PGA gain - 0: PGAGN = 1
                        //            1: PGAGN = 2
                        //            2: PGAGN = 4
                        //            3: PGAGN = 8
                        //            4: PGAGN = 16
                        //            5: PGAGN = 32
                        //            6: PGAGN = 64

#define INIS    0       // Input short - 0: Disable,  1: Enable
#define INX     0       // Input change- 0: Nochange
                        //               1: Short IN2
                        //               2: Short IN1
                        //               3: Exchange

#define DCSET   0       // Differential input signal  - 0 : 0V
                        //                              1 : 0.25 VR
                        //                              2 : 0.5 VR
                        //                              3 : 0.75 VR
                        //                              5 : -0.25 VR
                        //                              6 : -0.5 VR
                        //                              7 : -0.75 VR

#define CHSN    0       //  PGA negative input - 0: AN1
                        //                       1: AN3
                        //                       4: VDACO
                        //                       5: AVSS
                        //                       6: VCM
                        //                       7: VTSN (Temperature sensor negative output)

#define CHSP    0       // PGA positive input - 0: AN0
                        //                      1: AN2
                        //                      4: VDACO
                        //                      6: VCM
                        //                      7: VTSP (Temperature sensor positive output)

#define ADOR    1       // Oversampling rate - 0: OSR = 32768
                        //                     1: OSR = 16384
                        //                     2: OSR = 8192
                        //                     3: OSR = 4096
                        //                     4: OSR = 2048
                        //                     5: OSR = 1024
                        //                     6: OSR = 512
                        //                     7: OSR = 256
                        //                     8: OSR = 128

#define VREFS   1       // Reference voltage pair - 0: Internal VCM & AVSS
                        //                          1: External VREFP & VREFN

#define FLMS    0       // Clock divided ratio - 0: N = 30, 1: N = 12

#define VRBUF   0       // VRN & VRP Reference buffer - 0: Disable
                        //                              1: Enable VRP
                        //                              2: Enable VRN
                        //                              3: Enable VRN & VRP

#define ADCK    0x1F    // Clock source fMCLK  divided ratio - 0x00 ~ 0x1E: fMCLK =fSYS / 2 / (ADCK + 1)
                        //                                             0x1E: fMCLK =fSYS

/* Exported functions --------------------------------------------------------------------------------------*/
void ADC24_Init(void);
void ADC24_Start(void);
void ADC24_Stop(void);
u32 ADC24_ReadData_MainRoutine(s32 *pBuffer);
void ADC24_IRQHandler(void);

void ADC24_WriteRegNonBlock(u32 uAddr, u32 uValue);
void ADC24_WriteReg(u32 uAddr, u32 uValue);

void ADC24_ReadRegNonBlock(u32 uAddr, u8 *pBuffer, u32 uLen);
void ADC24_ReadReg(u32 uAddr, u8 *pBuffer, u32 uLen);

void ADC24_AccessWaiting(void);

#ifdef __cplusplus
}
#endif

#endif
