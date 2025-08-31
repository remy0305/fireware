/*********************************************************************************************************//**
 * @file    BMS56M605_HT32/src/BMS56M605.h
 * @version V1.0.1
 * @date    2024-08-08
 * @brief   The header file of BMS56M605 driver.
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
#ifndef __BMS56M605_H
#define __BMS56M605_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"
#include "i2c_master_config.h"
#include "ht32_board_config.h"
#include "bmduino_check.h"

#include "middleware/i2c_master.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------------------------------------*/
typedef enum {
  BMS56M605_SUCCESS,
  BMS56M605_FAILURE
} BMS56M605_selStatus;
/* Exported constants --------------------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------------------------------------*/
#define BMS56M605_MASTERADDR     0x68
#define BMS56M605_CLKFREQ        100000

#define BMS56M605_ENABLE                    1   
#define BMS56M605_DISABLE                   0

/*set Accelerometer Range*/
#define BMS56M605_ACC_RANGE_2G              0
#define BMS56M605_ACC_RANGE_4G              1
#define BMS56M605_ACC_RANGE_8G              2
#define BMS56M605_ACC_RANGE_16G             3
/*set Gyro Range*/
#define BMS56M605_GYRO_RANGE_250            0
#define BMS56M605_GYRO_RANGE_500            1
#define BMS56M605_GYRO_RANGE_1000           2
#define BMS56M605_GYRO_RANGE_2000           3
/*set Interrupt Pin Polarity*/
#define BMS56M605_ACTIVE_HIGH               0
#define BMS56M605_ACTIVE_LOW                1
/*set Interrupt Pin Open*/
#define BMS56M605_PUSH_PULL                 0
#define BMS56M605_OPEN_DRAIN                1
/*set Clock Source*/
#define BMS56M605_INTERAL_8MHZ              0
#define BMS56M605_PLL_X_GYRO                1
#define BMS56M605_PLL_Y_GYRO                2
#define BMS56M605_PLL_Z_GYRO                3 
#define BMS56M605_PLL_EXTERNAL_32_768KHZ    4
#define BMS56M605_PLL_EXTERNAL_19_2MHZ      5
//#define RESERVED                  6
#define BMS56M605_STOP_CLOCK                7
/*set Filter Bandwidth*/
#define BMS56M605_ACC_260HZ_GYRO_256HZ      0
#define BMS56M605_ACC_184HZ_GYRO_188HZ      1
#define BMS56M605_ACC_96HZ_GYRO_98HZ        2
#define BMS56M605_ACC_44HZ_GYRO_42HZ        3
#define BMS56M605_ACC_21HZ_GYRO_20HZ        4
#define BMS56M605_ACC_10HZ_GYRO_10HZ        5
#define BMS56M605_ACC_5HZ_GYRO_5HZ          6
//#define BMS56M605_RESERVED                  7

/*set Cycle Rate*/
#define BMS56M605_F_1_25HZ                  0
#define BMS56M605_F_2_5HZ                   1
#define BMS56M605_F_5HZ                     2
#define BMS56M605_F_10HZ                    3

/*INT mode*/
#define BMS56M605_FREE_FALL_MODE            7
#define BMS56M605_MOTION_MODE               6
#define BMS56M605_ZERO_MOTION_MODE          5

//BMS56M605 Register
#define BMS56M605_REG_XG_OFFS_TC           0x00 
#define BMS56M605_REG_YG_OFFS_TC           0x01 
#define BMS56M605_REG_ZG_OFFS_TC           0x02
#define BMS56M605_REG_X_FINE_GAIN          0x03
#define BMS56M605_REG_Y_FINE_GAIN          0x04
#define BMS56M605_REG_Z_FINE_GAIN          0x05 
#define BMS56M605_REG_XA_OFFS_H            0x06 
#define BMS56M605_REG_XA_OFFS_L_TC         0x07
#define BMS56M605_REG_YA_OFFS_H            0x08 
#define BMS56M605_REG_YA_OFFS_L_TC         0x09
#define BMS56M605_REG_ZA_OFFS_H            0x0A
#define BMS56M605_REG_ZA_OFFS_L_TC         0x0B
#define BMS56M605_REG_XG_OFFS_USRH         0x13 
#define BMS56M605_REG_XG_OFFS_USRL         0x14
#define BMS56M605_REG_YG_OFFS_USRH         0x15 
#define BMS56M605_REG_YG_OFFS_USRL         0x16
#define BMS56M605_REG_ZG_OFFS_USRH         0x17 
#define BMS56M605_REG_ZG_OFFS_USRL         0x18
#define BMS56M605_REG_SMPLRT_DIV           0x19
#define BMS56M605_REG_CONFIG               0x1A
#define BMS56M605_REG_GYRO_CONFIG          0x1B
#define BMS56M605_REG_ACCEL_CONFIG         0x1C
#define BMS56M605_REG_FF_THR               0x1D
#define BMS56M605_REG_FF_DUR               0x1E
#define BMS56M605_REG_MOT_THR              0x1F
#define BMS56M605_REG_MOT_DUR              0x20
#define BMS56M605_REG_ZRMOT_THR            0x21
#define BMS56M605_REG_ZRMOT_DUR            0x22
#define BMS56M605_REG_FIFO_EN              0x23
#define BMS56M605_REG_I2C_MST_CTRL         0x24
#define BMS56M605_REG_I2C_SLV0_ADDR        0x25
#define BMS56M605_REG_I2C_SLV0_REG         0x26
#define BMS56M605_REG_I2C_SLV0_CTRL        0x27
#define BMS56M605_REG_I2C_SLV1_ADDR        0x28
#define BMS56M605_REG_I2C_SLV1_REG         0x29
#define BMS56M605_REG_I2C_SLV1_CTRL        0x2A
#define BMS56M605_REG_I2C_SLV2_ADDR        0x2B
#define BMS56M605_REG_I2C_SLV2_REG         0x2C
#define BMS56M605_REG_I2C_SLV2_CTRL        0x2D
#define BMS56M605_REG_I2C_SLV3_ADDR        0x2E
#define BMS56M605_REG_I2C_SLV3_REG         0x2F
#define BMS56M605_REG_I2C_SLV3_CTRL        0x30
#define BMS56M605_REG_I2C_SLV4_ADDR        0x31
#define BMS56M605_REG_I2C_SLV4_REG         0x32
#define BMS56M605_REG_I2C_SLV4_DO          0x33
#define BMS56M605_REG_I2C_SLV4_CTRL        0x34
#define BMS56M605_REG_I2C_SLV4_DI          0x35
#define BMS56M605_REG_I2C_MST_STATUS       0x36
#define BMS56M605_REG_INT_PIN_CFG          0x37
#define BMS56M605_REG_INT_ENABLE           0x38
#define BMS56M605_REG_DMP_INT_STATUS       0x39
#define BMS56M605_REG_INT_STATUS           0x3A
#define BMS56M605_REG_ACCEL_XOUT_H         0x3B
#define BMS56M605_REG_ACCEL_XOUT_L         0x3C
#define BMS56M605_REG_ACCEL_YOUT_H         0x3D
#define BMS56M605_REG_ACCEL_YOUT_L         0x3E
#define BMS56M605_REG_ACCEL_ZOUT_H         0x3F
#define BMS56M605_REG_ACCEL_ZOUT_L         0x40
#define BMS56M605_REG_TEMP_OUT_H           0x41
#define BMS56M605_REG_TEMP_OUT_L           0x42
#define BMS56M605_REG_GYRO_XOUT_H          0x43
#define BMS56M605_REG_GYRO_XOUT_L          0x44
#define BMS56M605_REG_GYRO_YOUT_H          0x45
#define BMS56M605_REG_GYRO_YOUT_L          0x46
#define BMS56M605_REG_GYRO_ZOUT_H          0x47
#define BMS56M605_REG_GYRO_ZOUT_L          0x48
#define BMS56M605_REG_EXT_SENS_DATA_00     0x49
#define BMS56M605_REG_EXT_SENS_DATA_01     0x4A
#define BMS56M605_REG_EXT_SENS_DATA_02     0x4B
#define BMS56M605_REG_EXT_SENS_DATA_03     0x4C
#define BMS56M605_REG_EXT_SENS_DATA_04     0x4D
#define BMS56M605_REG_EXT_SENS_DATA_05     0x4E
#define BMS56M605_REG_EXT_SENS_DATA_06     0x4F
#define BMS56M605_REG_EXT_SENS_DATA_07     0x50
#define BMS56M605_REG_EXT_SENS_DATA_08     0x51
#define BMS56M605_REG_EXT_SENS_DATA_09     0x52
#define BMS56M605_REG_EXT_SENS_DATA_10     0x53
#define BMS56M605_REG_EXT_SENS_DATA_11     0x54
#define BMS56M605_REG_EXT_SENS_DATA_12     0x55
#define BMS56M605_REG_EXT_SENS_DATA_13     0x56
#define BMS56M605_REG_EXT_SENS_DATA_14     0x57
#define BMS56M605_REG_EXT_SENS_DATA_15     0x58
#define BMS56M605_REG_EXT_SENS_DATA_16     0x59
#define BMS56M605_REG_EXT_SENS_DATA_17     0x5A
#define BMS56M605_REG_EXT_SENS_DATA_18     0x5B
#define BMS56M605_REG_EXT_SENS_DATA_19     0x5C
#define BMS56M605_REG_EXT_SENS_DATA_20     0x5D
#define BMS56M605_REG_EXT_SENS_DATA_21     0x5E
#define BMS56M605_REG_EXT_SENS_DATA_22     0x5F
#define BMS56M605_REG_EXT_SENS_DATA_23     0x60
#define BMS56M605_REG_MOT_DETECT_STATUS    0x61
#define BMS56M605_REG_I2C_SLV0_DO          0x63
#define BMS56M605_REG_I2C_SLV1_DO          0x64
#define BMS56M605_REG_I2C_SLV2_DO          0x65
#define BMS56M605_REG_I2C_SLV3_DO          0x66
#define BMS56M605_REG_I2C_MST_DELAY_CTRL   0x67
#define BMS56M605_REG_SIGNAL_PATH_RESET    0x68
#define BMS56M605_REG_MOT_DETECT_CTRL      0x69
#define BMS56M605_REG_USER_CTRL            0x6A
#define BMS56M605_REG_PWR_MGMT_1           0x6B
#define BMS56M605_REG_PWR_MGMT_2           0x6C
#define BMS56M605_REG_BANK_SEL             0x6D
#define BMS56M605_REG_MEM_START_ADDR       0x6E
#define BMS56M605_REG_MEM_R_W              0x6F
#define BMS56M605_REG_DMP_CFG_1            0x70
#define BMS56M605_REG_DMP_CFG_2            0x71
#define BMS56M605_REG_FIFO_COUNTH          0x72
#define BMS56M605_REG_FIFO_COUNTL          0x73
#define BMS56M605_REG_FIFO_R_W             0x74
#define BMS56M605_REG_WHO_AM_I             0x75
/* Exported variables --------------------------------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------------------------------------*/
BMS56M605_selStatus BMS56M605_selWire(uint32_t wire_number);
void BMS56M605_Init(void);

/*** Functional function  ***/
//read Data
void BMS56M605_getEvent(void);
float BMS56M605_readTemperature(void);
float BMS56M605_readAccelerationX(void);
float BMS56M605_readAccelerationY(void);
float BMS56M605_readAccelerationZ(void);
float BMS56M605_readGyroscopeX(void);
 float BMS56M605_readGyroscopeY(void);
float BMS56M605_readGyroscopeZ(void);
// INT pin
void BMS56M605_setInterruptPinPolarity(uint8_t active_level);
void BMS56M605_setINT(uint8_t mode,uint8_t isEnable);
uint8_t BMS56M605_getINT(void);
// other
void BMS56M605_writeReg(uint8_t addr, uint8_t data);
uint8_t BMS56M605_readReg(uint8_t addr);
void BMS56M605_readMultipleReg(uint8_t addr, uint8_t rBuf[], uint8_t rLen);
void BMS56M605_enableSleep(bool isEnable);
void BMS56M605_enableCycle(bool isEnable);
void BMS56M605_reset(void);

/*** Parameter configuration and reading  ***/
uint8_t BMS56M605_getAccelerometerRange(void);
uint8_t BMS56M605_getGyroRange(void);
uint8_t BMS56M605_getFreefallThreshold(void);
uint8_t BMS56M605_getFreefallDuration(void);
uint8_t BMS56M605_getMotionThreshold(void);
uint8_t BMS56M605_getMotionDuration(void);
uint8_t BMS56M605_getZeroMotionThreshold(void);
uint8_t BMS56M605_getZeroMotionDuration(void);
uint8_t BMS56M605_getClock(void);
uint8_t BMS56M605_getFilterBandwidth(void);
uint8_t BMS56M605_getSampleRateDivisor(void);
uint8_t BMS56M605_getCycleRate(void);
       
void BMS56M605_setAccelerometerRange(uint8_t range);
void BMS56M605_setGyroRange(uint8_t range);
void BMS56M605_setFreefallThreshold(uint8_t threshold);
void BMS56M605_setFreefallDuration(uint8_t duration);
void BMS56M605_setMotionThreshold(uint8_t threshold);
void BMS56M605_setMotionDuration(uint8_t duration);
void BMS56M605_setZeroMotionThreshold(uint8_t threshold);
void BMS56M605_setZeroMotionDuration(uint8_t duration);
void BMS56M605_setClock(uint8_t clock);
void BMS56M605_setFilterBandwidth(uint8_t band);
void BMS56M605_setSampleRateDivisor(uint8_t divisor);
void BMS56M605_setCycleRate(uint8_t rate);


/*** private  ***/
uint16_t BMS56M605_readRawTemperature(void);
void BMS56M605_readAcceleration(float *accX, float *accY, float *accZ);
void BMS56M605_readGyroscope(float *gyroX, float *gyroY, float *gyroZ);
void BMS56M605_readRawAcceleration(int *rawAccX, int *rawAccY, int *rawAccZ);
void BMS56M605_readRawGyroscope(int *rawGyroX, int *rawGyroY, int *rawGyroZ);
void BMS56M605_clearBuf(void);

void BMS56M605_writeBytes(uint8_t wbuf[], uint8_t wlen);
void BMS56M605_writeRegBit(uint8_t addr,uint8_t bitNum, uint8_t bitValue);
void BMS56M605_readBytes(uint8_t rbuf[], uint8_t rlen);
	 
void _BMS56M605_delay(vu32 count);

#ifdef __cplusplus
}
#endif

#endif

