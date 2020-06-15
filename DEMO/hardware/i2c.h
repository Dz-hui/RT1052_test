/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:23:01
*@FilePath: \RT1052_test\DEMO\hardware\i2c.h
*@Drscription: 
***********************************************************************/
#ifndef __LPI2C__H
#define __LPI2C__H

#include "fsl_common.h"

#define EEPROM_LPI2C_PORT                   LPI2C1
#define MPU6050_LPI2C_PORT                  LPI2C3


#define EEPROM_LPI2C_SCL_IOMUXC             IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL
#define EEPROM_LPI2C_SDA_IOMUXC             IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA   

#define MPU6050_LPI2C_SDA_IOMUXC            IOMUXC_GPIO_AD_B1_06_LPI2C3_SDA
#define MPU6050_LPI2C_SCL_IOMUXC            IOMUXC_GPIO_AD_B1_07_LPI2C3_SCL



#define LPI2C_CLOCK_SOURCE_SELECT           0U
#define LPI2C_CLOCK_SOURCE_DIV              5U

#define LPI2C_BUADRATE                      400000U
#define LPI2C_CLOCK_FREQ                   10000000

#define SLAVE_INIT_SIZE                     0x01

#define EEPROM_WRITEADDR                    0x02

void LPI2C_config(void);
uint8_t PLI2C_write_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t writeaddr,uint8_t data);
void LPI2C_read_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t readaddr,uint8_t *data);
void LPI2C_read_buff(LPI2C_Type *base,uint8_t slaveaddr,uint8_t readaddr,uint8_t *buff,uint8_t datasize);
uint8_t LPI2C_write_buff(LPI2C_Type *base,uint8_t slaveaddr,uint8_t writeaddr,uint8_t *buff,uint8_t datasize);

#endif /*__LPI2C__H*/

