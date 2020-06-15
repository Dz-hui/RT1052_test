/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:24:29
*@FilePath: \RT1052_test\DEMO\hardware\mpu6050.h
*@Drscription: 
***********************************************************************/
#ifndef __MPU6050__H
#define __MPU6050__H

#include "fsl_common.h"

#define MPU6050_RA_PWR_MGMT_1           0x6B
#define MPU6050_RA_SMPLRT_DIV           0x19
#define MPU6050_RA_CONFIG               0x1A
#define MPU6050_RA_ACCEL_CONFIG         0x1C
#define MPU6050_RA_GYRO_CONFIG          0x1B
#define MPU6050_RA_WHO_AM_I             0x75
#define MPU6050_RA_ACCEL_MESUME         0X3B
#define MPU6050_RA_GRYO_MESUME          0X43



#define MPU6050_ADDR                    0XD0

void MPU6050_config(void);
void MPU6050_read_accel(uint16_t *accel_buff);
void MPU6050_read_gryo(uint16_t *gryo_buff);

#endif /*__MPU6050__H*/

