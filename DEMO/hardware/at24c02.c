/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:24:04
*@FilePath: \RT1052_test\DEMO\hardware\at24c02.c
*@Drscription: 
***********************************************************************/
#include "at24c02.h"

/***********************************************************************
*@Function: void AT24C02_write_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t writeaddr,uint8_t* data,uint8_t datasize)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 16:23:39
*@Drscription: EEPROMÐ´º¯Êý
***********************************************************************/
void AT24C02_write_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t writeaddr,uint8_t data)
{
    PLI2C_write_data(base,slaveaddr,writeaddr,data);
}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 16:26:22
*@Drscription: 
***********************************************************************/
void AT24C02_read_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t readaddr,uint8_t *data)
{
    LPI2C_read_data(base,slaveaddr,readaddr,data);
}

