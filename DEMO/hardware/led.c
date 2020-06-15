/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:22:28
*@FilePath: \RT1052_test\DEMO\hardware\led.c
*@Drscription: 
***********************************************************************/
#include "led.h"
#include "pad_config.h"

#include "fsl_gpio.h"
#include "fsl_iomuxc.h"


/***********************************************************************
*@Drscription: LED_PAD_CONFIG
***********************************************************************/
#define LED_PAD_SETTING      (SRE_0_SLOW_SLEW_RATE|\
                              DSE_4_R0_4|\
                              SPEED_1_MEDIUM_100MHz|\
                              ODE_0_OPEN_DRAIN_DISABLED|\
                              PKE_0_PULL_KEEPER_DISABLED|\
                              PUE_0_KEEPER_SELECTED|\
                              PUS_2_100K_OHM_PULL_UP|\
                              HYS_0_HYSTERESIS_DISABLED)



/***********************************************************************
*@Function:void LED_config(void) 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-13 10:30:46
*@Drscription: LED初始化
***********************************************************************/
void LED_config(void)
{
    gpio_pin_config_t gpio_config;

    /*
    *输出模式
    *输出电平：高电平
    *不使能中断
    */
   
    gpio_config.direction=kGPIO_DigitalOutput;
	gpio_config.outputLogic=1;
	gpio_config.interruptMode=kGPIO_NoIntmode;

    GPIO_PinInit(LED_GPIO_PORT,LED_GPIO_PIN,&gpio_config);
    IOMUXC_SetPinConfig(LED_IOMUXC,LED_PAD_SETTING);
    IOMUXC_SetPinMux(LED_IOMUXC,0U);

    //LED_OFF();

}

