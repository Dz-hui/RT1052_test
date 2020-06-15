/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:22:18
*@FilePath: \RT1052_test\DEMO\hardware\led.h
*@Drscription: 
***********************************************************************/
#ifndef __LED__H
#define __LED__H


#include "fsl_common.h"

/*BULE_LED*/
#define LED_GPIO_PORT           GPIO1
#define LED_GPIO_PIN            (10U)
#define LED_IOMUXC              IOMUXC_GPIO_AD_B0_10_GPIO1_IO10

#define LED_ON()                GPIO_PinWrite(LED_GPIO_PORT,LED_GPIO_PIN,0U)
#define LED_OFF()               GPIO_PinWrite(LED_GPIO_PORT,LED_GPIO_PIN,1U)
#define LED_TOGGLE()            GPIO_PortToggle(LED_GPIO_PORT,1<<LED_GPIO_PIN)

void LED_config(void);

#endif /*__LED__H*/

