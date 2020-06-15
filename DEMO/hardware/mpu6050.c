/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:24:17
*@FilePath: \RT1052_test\DEMO\hardware\mpu6050.c
*@Drscription: 
***********************************************************************/
#include "mpu6050.h"
#include "i2c.h"
#include "core_delay.h"
#include "main.h"

/***********************************************************************
*@Function: void MPU6050_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 19:37:34
*@Drscription: MPU6050≥ı ºªØ
***********************************************************************/
void MPU6050_config(void)
{
    
    CPU_TS_Tmr_Delay_US(600);
    PLI2C_write_data(MPU6050_LPI2C_PORT,MPU6050_ADDR,MPU6050_RA_PWR_MGMT_1,0x00);
    PLI2C_write_data(MPU6050_LPI2C_PORT,MPU6050_ADDR,MPU6050_RA_SMPLRT_DIV,0x07);
    PLI2C_write_data(MPU6050_LPI2C_PORT,MPU6050_ADDR,MPU6050_RA_CONFIG,0x06);
    PLI2C_write_data(MPU6050_LPI2C_PORT,MPU6050_ADDR,MPU6050_RA_ACCEL_CONFIG,0x018);
    PLI2C_write_data(MPU6050_LPI2C_PORT,MPU6050_ADDR,MPU6050_RA_GYRO_CONFIG,0x018);
  
}

/***********************************************************************
*@Function: void MPU6050_read_accel(uint16_t *accel_buff)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 15:46:03
*@Drscription: 
***********************************************************************/
void MPU6050_read_accel(uint16_t *accel_buff)
{
    uint8_t buff[6];
    LPI2C_read_buff(MPU6050_LPI2C_PORT,MPU6050_ADDR,MPU6050_RA_ACCEL_MESUME,buff,6);
    accel_buff[0]=((buff[0]<<8)|buff[1]);
    accel_buff[1]=((buff[2]<<8)|buff[3]);
    accel_buff[2]=((buff[4]<<8)|buff[5]);

}

/***********************************************************************
*@Function: void MPU6050_read_accel(uint16_t *gryo_buff)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 15:58:38
*@Drscription: 
***********************************************************************/
void MPU6050_read_gryo(uint16_t *gryo_buff)
{
    uint8_t buff[6];
    LPI2C_read_buff(MPU6050_LPI2C_PORT,MPU6050_ADDR,MPU6050_RA_GRYO_MESUME,buff,6);
    gryo_buff[0]=((buff[0]<<8)|buff[1]);
    gryo_buff[1]=((buff[2]<<8)|buff[3]);
    gryo_buff[2]=((buff[4]<<8)|buff[5]);
    
}