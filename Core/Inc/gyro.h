#include "main.h"

#ifndef _GYRO_H_
#define _GYRO_H_

/*define register constant*/

#define MPU_ADDR_SMPLRT_DIV     0x19
#define MPU_ADDR_CONFIG         0x1A
#define MPU_ADDR_GYRO_CONFIG    0x1B
#define MPU_ADDR_ACCEL_CONFIG   0x1C

#define MPU_ADDR_ACCEL_XOUT_H   0x3B
#define MPU_ADDR_ACCEL_XOUT_L   0x3C
#define MPU_ADDR_ACCEL_YOUT_H   0x3D
#define MPU_ADDR_ACCEL_YOUT_L   0x3E
#define MPU_ADDR_ACCEL_ZOUT_H   0x3F
#define MPU_ADDR_ACCEL_ZOUT_L   0x40

#define MPU_ADDR_TEMP_OUT_H     0x41
#define MPU_ADDR_TEMP_OUT_L     0x42

#define MPU_ADDR_GYRO_XOUT_H    0x43
#define MPU_ADDR_GYRO_XOUT_L    0x44
#define MPU_ADDR_GYRO_YOUT_H    0x45
#define MPU_ADDR_GYRO_YOUT_L    0x46
#define MPU_ADDR_GYRO_ZOUT_H    0x47
#define MPU_ADDR_GYRO_ZOUT_L    0x48

#define MPU_ADDR_PWR_MGMT_1     0x6B
#define MPU_ADDR_WHO_AM_I       0x75

#define WHO_AM_I                0xD0

#define Q30                     1073741824.0f

/*define macro with parameter*/

#define MPU_I2C1_WRITE(REGISTER_ADDR, DATA_BUFFER) HAL_I2C_Mem_Write(&hi2c1, WHO_AM_I, REGISTER_ADDR, 1, DATA_BUFFER, 1, 1000)
#define MPU_I2C1_READ(REGISTER_ADDR, DATA_BUFFER) HAL_I2C_Mem_Read(&hi2c1, WHO_AM_I, REGISTER_ADDR, 1, DATA_BUFFER, 1, 0xff)

void gyroInit(void);
void dmpInit(void);

void gyroGetData(void);
void dmpGetData(void);

void my_sprintfloat(char*, float);

int16_t MPUGetOneTermData(uint8_t, uint8_t);
#endif