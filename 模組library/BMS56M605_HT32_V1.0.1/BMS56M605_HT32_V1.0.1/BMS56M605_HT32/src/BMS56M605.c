/*********************************************************************************************************//**
 * @file    BMS56M605_HT32/src/BMS56M605.c
 * @version V1.0.1
 * @date    2024-08-08
 * @brief   The function of BMS56M605 driver.
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "BMS56M605.h"

/* Settings ------------------------------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------------------------------------*/
/* Global variables ----------------------------------------------------------------------------------------*/
uint32_t gBMS56M605_WIRE = BMS56M605_WIRE;
float BMS56M605_temperature;
float BMS56M605_accX, BMS56M605_accY, BMS56M605_accZ;
float BMS56M605_gyroX, BMS56M605_gyroY, BMS56M605_gyroZ;
uint8_t BMS56M605_dataBuff[10];   //Array for storing data
/* Private variables ---------------------------------------------------------------------------------------*/
uint8_t _BMS56M605_intpin;
int _BMS56M605_lsbAcc;
float _BMS56M605_lsbGyro;
uint8_t _BMS56M605_accrange;
uint8_t _BMS56M605_gyrorange;
/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief module wire number select.
 * @param wire_number: select wire number.
 * @retval BMS56M605_SUCCESS/BMS56M605_FAILURE
 ************************************************************************************************************/
BMS56M605_selStatus BMS56M605_selWire(uint32_t wire_number)
{
  if(CHECK_WIREn(wire_number) == -1)
  {
    return BMS56M605_FAILURE;
  }

  gBMS56M605_WIRE = wire_number;
  return BMS56M605_SUCCESS;
}

/*********************************************************************************************************//**
 * @brief  Module initialization using I2C communication.
 * @param  void
 * @retval void
 ************************************************************************************************************/
void BMS56M605_Init(void)
{
	I2CMaster_Init(gBMS56M605_WIRE, BMS56M605_MASTERADDR, BMS56M605_CLKFREQ);
	
	//INPUT:INT Pin
	{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.BMS56M605_INTPIN_GPIO = 1;
  CKCUClock.Bit.AFIO       = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
	}
	AFIO_GPxConfig(BMS56M605_INTPIN_GPIO_ID, BMS56M605_INTPIN_AFIO_PIN, AFIO_FUN_GPIO);
	GPIO_DirectionConfig(BMS56M605_INTPIN_GPIO_PORT, BMS56M605_INTPIN_GPIO_PIN, GPIO_DIR_IN);
	GPIO_PullResistorConfig(BMS56M605_INTPIN_GPIO_PORT, BMS56M605_INTPIN_GPIO_PIN, GPIO_PR_UP);
	GPIO_InputConfig(BMS56M605_INTPIN_GPIO_PORT, BMS56M605_INTPIN_GPIO_PIN, ENABLE);
	
  BMS56M605_enableSleep(false);                                                    //make sure that the device is not in sleep mode
  BMS56M605_setClock(BMS56M605_PLL_X_GYRO);                                        //PLL with X axis gyroscope reference
  BMS56M605_setAccelerometerRange(BMS56M605_ACC_RANGE_2G);                         //the full scale range of the accelerometer:?2g
  BMS56M605_setGyroRange(BMS56M605_GYRO_RANGE_250);                                //the full scale range of the gyroscope:?250 ?s
  BMS56M605_writeRegBit(BMS56M605_REG_INT_PIN_CFG, 6, BMS56M605_PUSH_PULL & 0x01); //the INT pin is configured as push-pull.
  BMS56M605_setInterruptPinPolarity(BMS56M605_ACTIVE_LOW);
}


//read Data
/*********************************************************************************************************//**
 * @brief  read data include temperature/acc and gyro 3 axis data
 * @param  void
 * @retval void
 ************************************************************************************************************/
void BMS56M605_getEvent()
{
    BMS56M605_temperature = BMS56M605_readTemperature();
	  _BMS56M605_delay(10);
    BMS56M605_readAcceleration(&BMS56M605_accX, &BMS56M605_accY, &BMS56M605_accZ);
	  _BMS56M605_delay(10);
    BMS56M605_readGyroscope(&BMS56M605_gyroX, &BMS56M605_gyroY, &BMS56M605_gyroZ);
	  _BMS56M605_delay(10);
}

/*********************************************************************************************************//**
 * @brief  read Temperature
 * @param  void
 * @retval temperature data(unit: 'C)  
 ************************************************************************************************************/
float BMS56M605_readTemperature()
{
      float BMS56M605_tempValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_TEMP_OUT_H,BMS56M605_dataBuff,2);
      BMS56M605_tempValue = (uint16_t)BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      if(BMS56M605_tempValue != 0) BMS56M605_tempValue = BMS56M605_tempValue/340 + 36.53;
      BMS56M605_tempValue /= 10;
      return BMS56M605_tempValue;
}

/*********************************************************************************************************//**
 * @brief  read X-axis Acceleration
 * @param  void
 * @retval data of X-axis Acceleration (unit: g)  
 ************************************************************************************************************/
float BMS56M605_readAccelerationX()
{
      int16_t BMS56M605_x = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_ACCEL_XOUT_H,BMS56M605_dataBuff,2);
      BMS56M605_x = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      return (float)BMS56M605_x/_BMS56M605_lsbAcc;
}

/*********************************************************************************************************//**
 * @brief  read Y-axis Acceleration
 * @param  void
 * @retval data of Y-axis Acceleration (unit: g) 
 ************************************************************************************************************/
float BMS56M605_readAccelerationY()
{
      int16_t BMS56M605_y = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_ACCEL_YOUT_H,BMS56M605_dataBuff,2);
      BMS56M605_y = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      return (float)BMS56M605_y/_BMS56M605_lsbAcc;  
}

/*********************************************************************************************************//**
 * @brief  read Z-axis Acceleration 
 * @param  void
 * @retval data of Z-axis Acceleration (unit: g)
 ************************************************************************************************************/
float BMS56M605_readAccelerationZ()
{
      int16_t BMS56M605_z = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_ACCEL_ZOUT_H,BMS56M605_dataBuff,2);
      BMS56M605_z = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      return (float)BMS56M605_z/_BMS56M605_lsbAcc; 
}

/*********************************************************************************************************//**
 * @brief  read X-axis Gyroscope 
 * @param  void
 * @retval data of X-axis Gyroscope (unit: '/s) 
 ************************************************************************************************************/
float BMS56M605_readGyroscopeX()
{
      int16_t BMS56M605_x = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_GYRO_XOUT_H,BMS56M605_dataBuff,2);
      BMS56M605_x = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      return (float)BMS56M605_x/_BMS56M605_lsbGyro;
}

/*********************************************************************************************************//**
 * @brief  read Y-axis Gyroscope 
 * @param  void
 * @retval data of Y-axis Gyroscope (unit: '/s)    
 ************************************************************************************************************/
float BMS56M605_readGyroscopeY()
{
      int16_t BMS56M605_y = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_GYRO_YOUT_H,BMS56M605_dataBuff,2); 
      BMS56M605_y = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      return (float)BMS56M605_y/_BMS56M605_lsbGyro; 
}
 
/*********************************************************************************************************//**
 * @brief  read Z-axis Gyroscope 
 * @param  void
 * @retval data of Z-axis Gyroscope (unit: '/s)    
 ************************************************************************************************************/
float BMS56M605_readGyroscopeZ()
{
      int16_t BMS56M605_z = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_GYRO_ZOUT_H,BMS56M605_dataBuff,2); 
      BMS56M605_z = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      return (float)BMS56M605_z/_BMS56M605_lsbGyro;  
}


// INT pin
/*********************************************************************************************************//**
 * @brief  set Interrupt Pin Polarity
 * @param  active_level:Optional:
              @arg BMS56M605_ACTIVE_HIGH 
              @arg BMS56M605_ACTIVE_LOW 
 * @retval void
 * @others When this bit is equal to 0, the logic level for the INT pin is active high.
           When this bit is equal to 1, the logic level for the INT pin is active low.
 ************************************************************************************************************/
void BMS56M605_setInterruptPinPolarity(uint8_t active_level)
{
	BMS56M605_writeRegBit(BMS56M605_REG_INT_PIN_CFG, 7, active_level & 0x01); 
}

/*********************************************************************************************************//**
 * @brief  set INT Mode
 * @param  mode:
                @arg BMS56M605_FREE_FALL_MODE            
                @arg BMS56M605_MOTION_MODE               
                @arg BMS56M605_ZERO_MOTION_MODE
              isEnable:
                @arg true:enable
                @arg false:disable
 * @retval void
 ************************************************************************************************************/
void BMS56M605_setINT(uint8_t mode,uint8_t isEnable)
{
     if(isEnable == true)
     {
          BMS56M605_writeRegBit(BMS56M605_REG_INT_ENABLE, mode, BMS56M605_ENABLE);
     }
     if(isEnable == false)
     {
          BMS56M605_writeRegBit(BMS56M605_REG_INT_ENABLE, mode, BMS56M605_DISABLE);
     }
}

/*********************************************************************************************************//**
 * @brief  get INT
 * @param  void
 * @retval INT status 
            @arg 1:INT status is HIGH
            @arg 0:INT status is LOW
 ************************************************************************************************************/
uint8_t BMS56M605_getINT()
{
      return (GPIO_ReadInBit(BMS56M605_INTPIN_GPIO_PORT, BMS56M605_INTPIN_GPIO_PIN));
}


// other
/*********************************************************************************************************//**
 * @brief  writeReg
 * @param  addr :Register to be written
             data:Value to be written  
 * @retval void
 ************************************************************************************************************/
void BMS56M605_writeReg(uint8_t addr, uint8_t data)
{
    uint8_t BMS56M605_sendBuf[2];
		BMS56M605_sendBuf[0] = addr;
		BMS56M605_sendBuf[1] = data;
    BMS56M605_writeBytes(BMS56M605_sendBuf,2);
    _BMS56M605_delay(1);
}

/*********************************************************************************************************//**
 * @brief  read Register data
 * @param  addr :Register to be written 
 * @retval 8-bit data of Register
 * @others  user can use this function to read any register  
             including something are not mentioned.
 ************************************************************************************************************/
uint8_t BMS56M605_readReg(uint8_t addr)
{
	  uint8_t BMS56M605_sendBuf[1];
		BMS56M605_sendBuf[0] = addr;
    BMS56M605_clearBuf();
    BMS56M605_writeBytes(BMS56M605_sendBuf,1);
    _BMS56M605_delay(1);
    BMS56M605_readBytes(BMS56M605_dataBuff,1);
    _BMS56M605_delay(1);
    return BMS56M605_dataBuff[0];
}

/*********************************************************************************************************//**
 * @brief  Read register value continuously
 * @param  addr:Register to be written
             rBuf:Variables for storing Data to be obtained
             rLen:the byte of the data
 * @retval void
 ************************************************************************************************************/
void BMS56M605_readMultipleReg(uint8_t addr, uint8_t rBuf[], uint8_t rLen)
{
	  uint8_t BMS56M605_sendBuf[1];
		BMS56M605_sendBuf[0] = addr;
    BMS56M605_clearBuf();
    BMS56M605_writeBytes(BMS56M605_sendBuf,1);
    _BMS56M605_delay(1);
    BMS56M605_readBytes(rBuf,rLen);
    _BMS56M605_delay(1);
}

/*********************************************************************************************************//**
 * @brief  enable Sleep Mode
 * @param  isEnable =  ture,  enable
             isEnable =  false, disable(default)
             rLen:the byte of the data
 * @retval void
 * @Others When enable, puts the DEVICE into sleep mode.
 ************************************************************************************************************/
void BMS56M605_enableSleep(bool isEnable)
{
  if(isEnable == true)
  {
      BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 6, ENABLE);
  }
  if(isEnable == false)
  {
      BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 6, DISABLE);
  }
}

/*********************************************************************************************************//**
 * @brief  enable Cycle Mode
 * @param  isEnable =  ture,  enable 
             isEnable =  false, disable(default) 
 * @retval void
 * @Others When this bit is set to 1 and SLEEP is disabled, 
          the MPU-60X0 will cycle between sleep mode and waking up 
          to take a single sample of data from active sensors 
          at a rate determined by LP_WAKE_CTRL (register 108).
 ************************************************************************************************************/
void BMS56M605_enableCycle(bool isEnable)
{
   if(isEnable == true)
  {
      BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 5, ENABLE);
  }
  if(isEnable == false)
  {
      BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 5, DISABLE);
  }  
}

/*********************************************************************************************************//**
 * @brief  reset
 * @param  void 
 * @retval void
 * @Others When set to 1, this bit resets all internal registers 
          to their default values.The bit automatically clears 
          to 0 once the reset is done.
 ************************************************************************************************************/
void BMS56M605_reset()
{
	BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 7, 1);
}


// Parameter configuration and reading
/*********************************************************************************************************//**
 * @brief  get Accelerometer Range
 * @param  void 
 * @retval Accelerometer Range data(2 bit)
 ************************************************************************************************************/
uint8_t BMS56M605_getAccelerometerRange()
{
      uint8_t BMS56M605_rangeValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_ACCEL_CONFIG,BMS56M605_dataBuff,1);
      BMS56M605_rangeValue = (BMS56M605_dataBuff[0]>>3)&0x03; //get bit4 and bit3   
      return BMS56M605_rangeValue;
}

/*********************************************************************************************************//**
 * @brief  get Gyroscope Range
 * @param  void 
 * @retval Gyroscope Range data(2 bit) 
 ************************************************************************************************************/
uint8_t BMS56M605_getGyroRange()
{
      uint8_t BMS56M605_rangeValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_GYRO_CONFIG,BMS56M605_dataBuff,1);
      BMS56M605_rangeValue = (BMS56M605_dataBuff[0]>>3)&0x03; //get bit4 and bit3   
      return BMS56M605_rangeValue;
}

/*********************************************************************************************************//**
 * @brief  get Free fall Threshold
 * @param  void 
 * @retval Threshold data(1 byte) ,unit:mg
 * @others when FREE_FALL_Mode is set
 ************************************************************************************************************/
uint8_t BMS56M605_getFreefallThreshold()
{
      uint8_t BMS56M605_thresholdValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_FF_THR,BMS56M605_dataBuff,1); 
      BMS56M605_thresholdValue = BMS56M605_dataBuff[0];
      return BMS56M605_thresholdValue;
}

/*********************************************************************************************************//**
 * @brief  get Motion Threshold
 * @param  void 
 * @retval Threshold data(1 byte)  ,unit:mg   
 * @others when Motion_Mode is set
 ************************************************************************************************************/
uint8_t BMS56M605_getMotionThreshold()
{
      uint8_t BMS56M605_thresholdValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_MOT_THR,BMS56M605_dataBuff,1);   
      BMS56M605_thresholdValue = BMS56M605_dataBuff[0];  
      return BMS56M605_thresholdValue;
}

/*********************************************************************************************************//**
 * @brief  get Free fall Duration
 * @param  void 
 * @retval Duration data(1 byte)   ,unit:ms 
 * @others when FREE_FALL_Mode is set
 ************************************************************************************************************/
uint8_t BMS56M605_getFreefallDuration()
{
      uint8_t BMS56M605_durationValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_FF_DUR,BMS56M605_dataBuff,1); 
      BMS56M605_durationValue = BMS56M605_dataBuff[0]; 
      return BMS56M605_durationValue;
}

/*********************************************************************************************************//**
 * @brief  get Motion Duration
 * @param  void 
 * @retval Duration data(1 byte),unit:ms  
 * @others when Motion_Mode is set
 ************************************************************************************************************/
uint8_t BMS56M605_getMotionDuration()
{
      uint8_t BMS56M605_durationValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_MOT_DUR,BMS56M605_dataBuff,1);
      BMS56M605_durationValue = BMS56M605_dataBuff[0]; 
      return BMS56M605_durationValue;
}

/*********************************************************************************************************//**
 * @brief  get Zero Motion Threshold
 * @param  void 
 * @retval Threshold data(1 byte)   ,unit:mg 
 * @others when Zero_Motion_Mode is set
 ************************************************************************************************************/
uint8_t BMS56M605_getZeroMotionThreshold()
{
      uint8_t BMS56M605_thresholdValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_ZRMOT_THR,BMS56M605_dataBuff,1);
      BMS56M605_thresholdValue = BMS56M605_dataBuff[0]; 
      return BMS56M605_thresholdValue;
}

/*********************************************************************************************************//**
 * @brief  get Zero Motion Duration
 * @param  void 
 * @retval Duration data(1 byte)  ,unit:ms  
 * @others when Zero_Motion_Mode is set
 ************************************************************************************************************/
uint8_t BMS56M605_getZeroMotionDuration()
{
      uint8_t BMS56M605_durationValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_ZRMOT_DUR,BMS56M605_dataBuff,1);
      BMS56M605_durationValue = BMS56M605_dataBuff[0]; 
      return BMS56M605_durationValue;
}

/*********************************************************************************************************//**
 * @brief  get Clock Source
 * @param  void 
 * @retval Clock Source data(3 bit)
 ************************************************************************************************************/
uint8_t BMS56M605_getClock()
{
      uint8_t BMS56M605_clockValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_PWR_MGMT_1,BMS56M605_dataBuff,1);
      BMS56M605_clockValue = BMS56M605_dataBuff[0]&0x07; 
      return BMS56M605_clockValue;
}

/*********************************************************************************************************//**
 * @brief  get Filter Band width
 * @param  bandWidthValue:Variables for storing Filter Band width data
 * @retval Filter Band width data(3 bit)  
 ************************************************************************************************************/
uint8_t BMS56M605_getFilterBandwidth()
{
      uint8_t BMS56M605_bandWidthValue  = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_CONFIG,BMS56M605_dataBuff,1);
      BMS56M605_bandWidthValue = BMS56M605_dataBuff[0]&0x07; 
      return BMS56M605_bandWidthValue;
}

/*********************************************************************************************************//**
 * @brief  get Sample Rate Divisor
 * @param  void
 * @retval Rate divisor data(1 Byte)
 ************************************************************************************************************/
uint8_t BMS56M605_getSampleRateDivisor()
{
      uint8_t BMS56M605_divisorValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_SMPLRT_DIV,BMS56M605_dataBuff,1);
      BMS56M605_divisorValue = BMS56M605_dataBuff[0];
      return BMS56M605_divisorValue;
}

/*********************************************************************************************************//**
 * @brief  get Cycle Rate
 * @param  void
 * @retval Cycle Rate data(2 bit)   
 ************************************************************************************************************/
uint8_t BMS56M605_getCycleRate()
{
      uint8_t BMS56M605_rateValue = 0; 
      BMS56M605_readMultipleReg(BMS56M605_REG_PWR_MGMT_2,BMS56M605_dataBuff,1);
      BMS56M605_rateValue = (BMS56M605_dataBuff[0]>>6)&0x03; 
      return BMS56M605_rateValue;
}


/*********************************************************************************************************//**
 * @brief  set Accelerometer Range
 * @param  range:Optional:
              @arg BMS56M605_ACC_RANGE_2G              
              @arg BMS56M605_ACC_RANGE_4G              
              @arg BMS56M605_ACC_RANGE_8G              
              @arg BMS56M605_ACC_RANGE_16G 
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_setAccelerometerRange(uint8_t range)
{
      _BMS56M605_accrange = range;
            
      switch(_BMS56M605_accrange)
      {
          case BMS56M605_ACC_RANGE_2G: _BMS56M605_lsbAcc = 16384;break;
          case BMS56M605_ACC_RANGE_4G: _BMS56M605_lsbAcc = 8192; break;
          case BMS56M605_ACC_RANGE_8G: _BMS56M605_lsbAcc = 4096; break;
          case BMS56M605_ACC_RANGE_16G:_BMS56M605_lsbAcc = 2048; break;
          default:           _BMS56M605_lsbAcc = 16384;break;
      }
      BMS56M605_writeRegBit(BMS56M605_REG_ACCEL_CONFIG, 3, range & 0x01); 
      BMS56M605_writeRegBit(BMS56M605_REG_ACCEL_CONFIG, 4, range & 0x02); 
}

/*********************************************************************************************************//**
 * @brief  set Gyroscope Range
 * @param  range:Optional:
              @arg BMS56M605_GYRO_RANGE_250            
              @arg BMS56M605_GYRO_RANGE_500            
              @arg BMS56M605_GYRO_RANGE_1000           
              @arg BMS56M605_GYRO_RANGE_2000  
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_setGyroRange(uint8_t range)
{
      _BMS56M605_gyrorange = range;
      switch(_BMS56M605_gyrorange)
      {
          case BMS56M605_GYRO_RANGE_250:  _BMS56M605_lsbGyro = 131 ;break;
          case BMS56M605_GYRO_RANGE_500:  _BMS56M605_lsbGyro = 65.5;break;
          case BMS56M605_GYRO_RANGE_1000: _BMS56M605_lsbGyro = 32.8;break;
          case BMS56M605_GYRO_RANGE_2000: _BMS56M605_lsbGyro = 16.4;break;
          default:              _BMS56M605_lsbGyro = 131 ;break;
      }
      BMS56M605_writeRegBit(BMS56M605_REG_GYRO_CONFIG, 3, range & 0x01); 
      BMS56M605_writeRegBit(BMS56M605_REG_GYRO_CONFIG, 4, range & 0x02); 
}

/*********************************************************************************************************//**
 * @brief  set Free fall Threshold
 * @param  threshold:Variables for storing Threshold data,unit:mg
 * @retval void   
 * @Others when FREE_FALL_Mode is set
	           1 LSB = 1mg
 ************************************************************************************************************/
void BMS56M605_setFreefallThreshold(uint8_t threshold)
{
	BMS56M605_writeReg(BMS56M605_REG_FF_THR, threshold);
}

/*********************************************************************************************************//**
 * @brief  set Free fall Duration
 * @param  duration:Variables for storing Duration data,unit:ms
 * @retval void   
 * @Others when FREE_FALL_Mode is set,unit:ms
 ************************************************************************************************************/
void BMS56M605_setFreefallDuration(uint8_t duration)
{
   BMS56M605_writeReg(BMS56M605_REG_FF_DUR, duration);
}

/*********************************************************************************************************//**
 * @brief  set Motion Threshold
 * @param  threshold:Variables for storing Threshold data ,unit:mg
 * @retval void   
 * @Others when Motion_Mode is set
             1 LSB = 1mg
 ************************************************************************************************************/
void BMS56M605_setMotionThreshold(uint8_t threshold)
{
      BMS56M605_writeReg(BMS56M605_REG_MOT_THR, threshold);
}

/*********************************************************************************************************//**
 * @brief  set Motion Duration
 * @param  duration:Variables for storing Duration data ,unit:ms
 * @retval void   
 * @Others when Motion_Mode is set,unit:ms
 ************************************************************************************************************/
void BMS56M605_setMotionDuration(uint8_t duration)
{
	BMS56M605_writeReg(BMS56M605_REG_MOT_DUR, duration);
}

/*********************************************************************************************************//**
 * @brief  set Zero Motion Threshold
 * @param  threshold:Variables for storing Threshold data,unit:mg
 * @retval void   
 * @Others when Zero_Motion_Mode is set
             1 LSB = 1mg
 ************************************************************************************************************/
void BMS56M605_setZeroMotionThreshold(uint8_t threshold)
{
	BMS56M605_writeReg(BMS56M605_REG_ZRMOT_THR, threshold);
}

/*********************************************************************************************************//**
 * @brief  set Zero Motion Duration
 * @param  duration:Variables for storing Duration data ,unit:ms
 * @retval void   
 * @Others when Zero_Motion_Mode is set,unit:ms
 ************************************************************************************************************/
void BMS56M605_setZeroMotionDuration(uint8_t duration)
{
      BMS56M605_writeReg(BMS56M605_REG_ZRMOT_DUR, duration);
}

/*********************************************************************************************************//**
 * @brief  set Clock Source
 * @param  clock:Optional:
              @arg BMS56M605_INTERAL_8MHZ              
              @arg BMS56M605_PLL_X_GYRO                
              @arg BMS56M605_PLL_Y_GYRO                
              @arg BMS56M605_PLL_Z_GYRO                
              @arg BMS56M605_PLL_EXTERNAL_32_768KHZ    
              @arg BMS56M605_PLL_EXTERNAL_19_2MHZ                
              @arg BMS56M605_STOP_CLOCK 
 * @retval void   
 * @Others It is highly recommended that the device be configured 
          to use one of the gyroscopes (or an external clock source) 
          as the clock reference for improved stability.
 ************************************************************************************************************/
void BMS56M605_setClock(uint8_t clock)
{
      BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 0, clock & 0x01);
      BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 1, clock & 0x02);
      BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_1, 2, clock & 0x04);
}

/*********************************************************************************************************//**
 * @brief  set Filter Band width
 * @param  band:Optional:
              @arg BMS56M605_ACC_260HZ_GYRO_256HZ      
              @arg BMS56M605_ACC_184HZ_GYRO_188HZ      
              @arg BMS56M605_ACC_96HZ_GYRO_98HZ        
              @arg BMS56M605_ACC_44HZ_GYRO_42HZ        
              @arg BMS56M605_ACC_21HZ_GYRO_20HZ        
              @arg BMS56M605_ACC_10HZ_GYRO_10HZ        
              @arg BMS56M605_ACC_5HZ_GYRO_5HZ 
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_setFilterBandwidth(uint8_t band)
{
      BMS56M605_writeRegBit(BMS56M605_REG_CONFIG, 0, band & 0x01);
      BMS56M605_writeRegBit(BMS56M605_REG_CONFIG, 1, band & 0x02);
      BMS56M605_writeRegBit(BMS56M605_REG_CONFIG, 2, band & 0x04);  
}

/*********************************************************************************************************//**
 * @brief  set Sample Rate Divisor
 * @param  divisor: Sample Rate Divisor 
 * @retval void   
 * @Others Sample Rate = Gyroscope Output Rate / (1 + divisor).
          where Gyroscope Output Rate = 8kHz when the DLPF 
          is disabled (DLPF_CFG = 0 or 7), and 1kHz when the 
          DLPF is enabled (see Register 26).
 ************************************************************************************************************/
void BMS56M605_setSampleRateDivisor(uint8_t divisor)
{
     BMS56M605_writeReg(BMS56M605_REG_SMPLRT_DIV, divisor); 
}

/*********************************************************************************************************//**
 * @brief  set Cycle Mode
 * @param  rate:Optional:
              @arg BMS56M605_F_1_25HZ                  
              @arg BMS56M605_F_2_5HZ                   
              @arg BMS56M605_F_5HZ                     
              @arg BMS56M605_F_10HZ
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_setCycleRate(uint8_t rate)
{
     BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_2, 6, rate & 0x01);
     BMS56M605_writeRegBit(BMS56M605_REG_PWR_MGMT_2, 7, rate & 0x02);
}



/* Private functions ---------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief  read Raw Temperature
 * @param  void
 * @retval temperature A/D raw data(2 byte)    
 ************************************************************************************************************/
uint16_t BMS56M605_readRawTemperature()
{
      uint16_t BMS56M605_rawTempValue = 0;
      BMS56M605_readMultipleReg(BMS56M605_REG_TEMP_OUT_H,BMS56M605_dataBuff,2); 
      BMS56M605_rawTempValue = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      return BMS56M605_rawTempValue;
}

/*********************************************************************************************************//**
 * @brief  read Acceleration
 * @param  accX/accY/accZ :Variables for storing Acceleration 3 axis data
 * @Output Acceleration 3 axis data(unit: g) 
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_readAcceleration(float *accX, float *accY, float *accZ)
{
      int16_t BMS56M605_x,BMS56M605_y,BMS56M605_z;
      BMS56M605_readMultipleReg(BMS56M605_REG_ACCEL_XOUT_H,BMS56M605_dataBuff,6); 
      BMS56M605_x = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      *accX = (float)BMS56M605_x/_BMS56M605_lsbAcc;
      BMS56M605_y = BMS56M605_dataBuff[2]*256 + BMS56M605_dataBuff[3];
      *accY = (float)BMS56M605_y/_BMS56M605_lsbAcc;
      BMS56M605_z = BMS56M605_dataBuff[4]*256 + BMS56M605_dataBuff[5];
      *accZ = (float)BMS56M605_z/_BMS56M605_lsbAcc;
}

/*********************************************************************************************************//**
 * @brief  read Gyroscope
 * @param  gyroX/gyroY/gyroZ :Variables for storing Gyroscope 3 axis data
 * @Output Gyroscope 3 axis data(unit: '/s)  
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_readGyroscope(float *gyroX, float *gyroY, float *gyroZ)
{
      int16_t BMS56M605_x,BMS56M605_y,BMS56M605_z;
      BMS56M605_readMultipleReg(BMS56M605_REG_GYRO_XOUT_H,BMS56M605_dataBuff,6);
      BMS56M605_x = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      *gyroX = (float)BMS56M605_x/_BMS56M605_lsbGyro;
      BMS56M605_y = BMS56M605_dataBuff[2]*256 + BMS56M605_dataBuff[3];
      *gyroY = (float)BMS56M605_y/_BMS56M605_lsbGyro;
      BMS56M605_z = BMS56M605_dataBuff[4]*256 + BMS56M605_dataBuff[5];
      *gyroZ = (float)BMS56M605_z/_BMS56M605_lsbGyro;
}

/*********************************************************************************************************//**
 * @brief  read Raw Acceleration
 * @param  rawAccX/rawAccY/rawAccZ :Variables for storing Acceleration 3 axis raw data
 * @Output Acceleration 3 axis raw data(2 byte) 
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_readRawAcceleration(int *rawAccX, int *rawAccY, int *rawAccZ)
{
      BMS56M605_readMultipleReg(BMS56M605_REG_ACCEL_XOUT_H,BMS56M605_dataBuff,6); 
      *rawAccX = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      *rawAccY = BMS56M605_dataBuff[2]*256 + BMS56M605_dataBuff[3];
      *rawAccZ = BMS56M605_dataBuff[4]*256 + BMS56M605_dataBuff[5];
}

/*********************************************************************************************************//**
 * @brief  read Raw Gyroscope
 * @param  rawGyroX/rawGyroY/rawGyroZ :Variables for storing Gyroscope 3 axis raw data
 * @Output Gyroscope 3 axis raw data(2 byte) 
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_readRawGyroscope(int *rawGyroX, int *rawGyroY, int *rawGyroZ)
{
      BMS56M605_readMultipleReg(BMS56M605_REG_GYRO_XOUT_H,BMS56M605_dataBuff,6);
      *rawGyroX = BMS56M605_dataBuff[0]*256 + BMS56M605_dataBuff[1];
      *rawGyroY = BMS56M605_dataBuff[2]*256 + BMS56M605_dataBuff[3];
      *rawGyroZ = BMS56M605_dataBuff[4]*256 + BMS56M605_dataBuff[5];
}

/*********************************************************************************************************//**
 * @brief  clearBuf()
 * @param  void
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_clearBuf()
{
	int BMS56M605_a = 0;
  for(BMS56M605_a = 0; BMS56M605_a < 10; BMS56M605_a++)
  {
    BMS56M605_dataBuff[BMS56M605_a] = 0;
  }
}

/*********************************************************************************************************//**
 * @brief  writeBytes
 * @param  wbuf[]:Variables for storing Data to be sent
             wlen:Length of data sent
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_writeBytes(uint8_t wbuf[], uint8_t wlen)
{
    I2CMaster_Status_Enum I2CResult = I2C_MASTER_GOING;
    I2CMaster_Typedef gI2CMaster = {0x00};

    gI2CMaster.uSlaveAddress = BMS56M605_MASTERADDR;
    gI2CMaster.Tx.puBuffer = (uint8_t *)wbuf;
    gI2CMaster.Tx.uLength = wlen;
    gI2CMaster.uTimeout_us = 30000;
    gI2CMaster.isDynamicOnOff_I2C = FALSE;

    I2CResult = I2C_MASTER_GOING;
    I2CMaster_Write(gBMS56M605_WIRE,&gI2CMaster);
    do {
      I2CResult = I2CMaster_GetStatus(gBMS56M605_WIRE);
    } while (I2CResult == I2C_MASTER_GOING);
}

/*********************************************************************************************************//**
 * @brief  write a bit data
 * @param  bitNum :Number of bits(bit7-bit0)
             bitValue :Value written 
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_writeRegBit(uint8_t addr,uint8_t bitNum, uint8_t bitValue)
{
      uint8_t BMS56M605_data;
      BMS56M605_readMultipleReg(addr,BMS56M605_dataBuff,1);
      BMS56M605_data = BMS56M605_dataBuff[0];
      BMS56M605_data = (bitValue != 0)? (BMS56M605_data|(1<<bitNum)) : (BMS56M605_data & ~(1 << bitNum));
      BMS56M605_writeReg(addr, BMS56M605_data);
}

/*********************************************************************************************************//**
 * @brief  readBytes
 * @param  rbuf[]:Variables for storing Data to be obtained
             rlen:Length of data to be obtained
 * @retval void   
 ************************************************************************************************************/
void BMS56M605_readBytes(uint8_t rbuf[], uint8_t rlen)
{
     I2CMaster_Status_Enum I2CResult = I2C_MASTER_GOING;
     I2CMaster_Typedef I2CMaster = { 0 };

     I2CMaster.uSlaveAddress = BMS56M605_MASTERADDR;
     I2CMaster.Rx.puBuffer = (uint8_t *)rbuf;
     I2CMaster.Rx.uLength = rlen;
     I2CMaster.uTimeout_us = 30000;
     I2CMaster.isDynamicOnOff_I2C = FALSE;

     I2CMaster_Read(gBMS56M605_WIRE, &I2CMaster);
	
     do {
       I2CResult = I2CMaster_GetStatus(gBMS56M605_WIRE);
     } while (I2CResult == I2C_MASTER_GOING);
}

/*********************************************************************************************************//**
 * @brief  delay ms.
 * @param  count
 * @retval void
 ************************************************************************************************************/
void _BMS56M605_delay(vu32 count)
{
  count = SystemCoreClock / 8000 * count;
  while(count--);
}




