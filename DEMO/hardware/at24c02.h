/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:23:46
*@FilePath: \RT1052_test\DEMO\hardware\at24c02.h
*@Drscription: 
***********************************************************************/
#ifndef __AT24C02__H
#define __AT24C02__H

#include "fsl_common.h"
#include "i2c.h"

#define EEPROM_WRITE_ADDR           0xA0
#define EEPROM_READ_ADDR            0xA1

void AT24C02_write_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t writeaddr,uint8_t data);
void AT24C02_read_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t readaddr,uint8_t *data);

#endif /*__AT24C02__H*/

