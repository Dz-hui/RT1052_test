/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:23:11
*@FilePath: \RT1052_test\DEMO\hardware\i2c.c
*@Drscription: 
***********************************************************************/
#include "i2c.h"
#include "pad_config.h"
#include "main.h"

#include "fsl_iomuxc.h"
#include "fsl_lpi2c.h"



/***********************************************************************
*@Drscription: LPI2C_PAD_CONFIG
***********************************************************************/
#define LPI2C_PAD_SETTING     (SRE_0_SLOW_SLEW_RATE|\
                              DSE_6_R0_6|\
                              SPEED_1_MEDIUM_100MHz|\
                              ODE_1_OPEN_DRAIN_ENABLED|\
                              PKE_1_PULL_KEEPER_ENABLED|\
                              PUE_0_KEEPER_SELECTED|\
                              PUS_3_22K_OHM_PULL_UP|\
                              HYS_0_HYSTERESIS_DISABLED)

/***********************************************************************
*@Function: void LPI2C_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 15:16:18
*@Drscription: LPI2C初始化
***********************************************************************/
void LPI2C_GPIO_config(void)
{
    lpi2c_master_config_t lpi2C_masterConfig;
    
    

    CLOCK_SetMux(kCLOCK_Lpi2cMux,LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv,LPI2C_CLOCK_SOURCE_DIV);
	
    LPI2C_MasterGetDefaultConfig(&lpi2C_masterConfig);
	lpi2C_masterConfig.baudRate_Hz=LPI2C_BUADRATE;
    LPI2C_MasterInit(EEPROM_LPI2C_PORT,&lpi2C_masterConfig,LPI2C_CLOCK_FREQ);
    LPI2C_MasterInit(MPU6050_LPI2C_PORT,&lpi2C_masterConfig,LPI2C_CLOCK_FREQ);

}

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 10:08:29
*@Drscription: 
***********************************************************************/
void LPI2C_config(void)
{
    IOMUXC_SetPinConfig(EEPROM_LPI2C_SCL_IOMUXC,LPI2C_PAD_SETTING);
    IOMUXC_SetPinMux(EEPROM_LPI2C_SCL_IOMUXC,1U);

    IOMUXC_SetPinConfig(EEPROM_LPI2C_SDA_IOMUXC,LPI2C_PAD_SETTING);
    IOMUXC_SetPinMux(EEPROM_LPI2C_SDA_IOMUXC,1U);

    IOMUXC_SetPinConfig(MPU6050_LPI2C_SDA_IOMUXC,LPI2C_PAD_SETTING);
    IOMUXC_SetPinMux(MPU6050_LPI2C_SDA_IOMUXC,1U);

    IOMUXC_SetPinConfig(MPU6050_LPI2C_SCL_IOMUXC,LPI2C_PAD_SETTING);
    IOMUXC_SetPinMux(MPU6050_LPI2C_SCL_IOMUXC,1U);
    
    LPI2C_GPIO_config();
    
}

/***********************************************************************
*@Function: void PLI2C_write_data(uint8_t slaveaddr,uint8_t writeaddr,uint8_t* data,uint8_t datasize)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 15:46:04
*@Drscription: PLI2C写数据
***********************************************************************/
uint8_t PLI2C_write_data(LPI2C_Type *base, uint8_t slaveaddr,uint8_t writeaddr,uint8_t data)
{
    lpi2c_master_transfer_t lpi2c_transfer;
	status_t reval = kStatus_Fail;
    
	lpi2c_transfer.direction=kLPI2C_Write;
	lpi2c_transfer.slaveAddress=(slaveaddr>>1);
	lpi2c_transfer.subaddress=writeaddr;
	lpi2c_transfer.subaddressSize=SLAVE_INIT_SIZE;
	lpi2c_transfer.dataSize=0x01;
	lpi2c_transfer.data=&data;
	lpi2c_transfer.flags=kLPI2C_TransferDefaultFlag;

    reval=LPI2C_MasterTransferBlocking(base,&lpi2c_transfer);
    DEBUG_PRINT("\n");
	
    if(reval !=kStatus_Success)
    {
        
        return 1;
    }

    else
    {
		
        return 0;
    }
       
}

/***********************************************************************
*@Function: void LPI2C_write_buff(LPI2C_Type *base,uint8_t slaveaddr,uint8_t writeaddr,uint8_t *buff,uint8_t datasize)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-15 09:04:15
*@Drscription: 
***********************************************************************/
uint8_t LPI2C_write_buff(LPI2C_Type *base,uint8_t slaveaddr,uint8_t writeaddr,uint8_t *buff,uint8_t datasize)
{
    lpi2c_master_transfer_t lpi2c_transfer;
	status_t reval = kStatus_Fail;
	
	lpi2c_transfer.direction=kLPI2C_Write;
	lpi2c_transfer.slaveAddress=(slaveaddr>>1);
	lpi2c_transfer.subaddress=writeaddr;
	lpi2c_transfer.subaddressSize=SLAVE_INIT_SIZE;
	lpi2c_transfer.data=buff;
	lpi2c_transfer.dataSize=datasize;
	lpi2c_transfer.flags=kLPI2C_TransferDefaultFlag;

    reval=LPI2C_MasterTransferBlocking(base,&lpi2c_transfer);
    DEBUG_PRINT("\n");
    if(reval!=kStatus_Success)
    {
        return 1;
    }

    else
    {
        return 0;
    }
    

}

/***********************************************************************
*@Function: void LPI2C_read_data(LPI2C_Type *base,uint8_t slaveaddr,uint8_t readaddr,uint8_t *data,uint8_t datasize)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 16:06:48
*@Drscription: 
***********************************************************************/
void LPI2C_read_data(LPI2C_Type *base, uint8_t slaveaddr,uint8_t readaddr,uint8_t *data)
{
    lpi2c_master_transfer_t lpi2c_transfer;
	status_t reval = kStatus_Fail;

	lpi2c_transfer.direction=kLPI2C_Read;
	lpi2c_transfer.slaveAddress=(slaveaddr>>1);
	lpi2c_transfer.subaddress=readaddr;
	lpi2c_transfer.subaddressSize=SLAVE_INIT_SIZE;
	lpi2c_transfer.dataSize=1;
	lpi2c_transfer.data=data;
	lpi2c_transfer.flags=kLPI2C_TransferDefaultFlag;

    reval=LPI2C_MasterTransferBlocking(base,&lpi2c_transfer);
    
}

/***********************************************************************
*@Function: void LPI2C_read_buff(LPI2C_Type *base,uint8_t slaveaddr,uint8_t readaddr,uint8_t *buff,uint8_t datasize)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 15:32:46
*@Drscription: 
***********************************************************************/
void LPI2C_read_buff(LPI2C_Type *base,uint8_t slaveaddr,uint8_t readaddr,uint8_t *buff,uint8_t datasize)
{
    lpi2c_master_transfer_t lpi2c_transfer;

	lpi2c_transfer.direction=kLPI2C_Read;
	lpi2c_transfer.slaveAddress=(slaveaddr>>1);
	lpi2c_transfer.subaddress=readaddr;
	lpi2c_transfer.subaddressSize=SLAVE_INIT_SIZE;
	lpi2c_transfer.data=buff;
	lpi2c_transfer.dataSize=datasize;
	lpi2c_transfer.flags=kLPI2C_TransferDefaultFlag;
	
    LPI2C_MasterTransferBlocking(base,&lpi2c_transfer);
}
