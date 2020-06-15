/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:22:50
*@FilePath: \RT1052_test\DEMO\hardware\key.c
*@Drscription: 
***********************************************************************/
#include "key.h"
#include "pad_config.h"

#include "fsl_gpio.h"
#include "fsl_iomuxc.h"

/***********************************************************************
*@Drscription: KEY_PAD_CONFIG
***********************************************************************/
#define KEY_PAD_SETTING      (SRE_0_SLOW_SLEW_RATE|\
                              DSE_4_R0_4|\
                              SPEED_1_MEDIUM_100MHz|\
                              ODE_0_OPEN_DRAIN_DISABLED|\
                              PKE_1_PULL_KEEPER_ENABLED|\
                              PUE_1_PULL_SELECTED|\
                              PUS_2_100K_OHM_PULL_UP|\
                              HYS_1_HYSTERESIS_ENABLED)


/***********************************************************************
*@Function: void KEY_config(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 11:09:36
*@Drscription: 按键初始化
***********************************************************************/
void KEY_config(void)
{
    gpio_pin_config_t gpio_config;

    /*
    *输入模式
    *输出电平无效
    *不使能中断
    */
    gpio_config.direction=kGPIO_DigitalInput;
	gpio_config.outputLogic=1;
	gpio_config.interruptMode=kGPIO_NoIntmode;
    GPIO_PinInit(KEY_GPIO_PORT,KEY_GPIO_PIN,&gpio_config);
    GPIO_PinInit(MODE_KEY_GPIO_PORT,MODE_KEY_GPIO_PIN,&gpio_config);

    IOMUXC_SetPinConfig(KEY_IOMUXC,KEY_PAD_SETTING);
    IOMUXC_SetPinMux(KEY_IOMUXC,0U);

    IOMUXC_SetPinConfig(MODE_KEY_IOMUXC,KEY_PAD_SETTING);
    IOMUXC_SetPinMux(MODE_KEY_IOMUXC,0U);
    
}

/***********************************************************************
*@Function: uint8_t KEY_scanf(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 11:28:14
*@Drscription: 按键检测
***********************************************************************/

uint8_t KEY_scanf(void)
{
    static uint8_t flag=1;

    if(KEY_READ()==KEY_ON &&flag)
    {
        flag=0;
        return KEY_ON;
    }
    else if((KEY_READ()==KEY_OFF))
    {
        flag=1;
    }
    return KEY_OFF;

}
