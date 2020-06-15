/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-13 10:22:35
*@FilePath: \RT1052_test\DEMO\hardware\key.h
*@Drscription: 
***********************************************************************/
#ifndef __KEY__H
#define __KEY__H

#include "fsl_common.h"

#define KEY_ON                      0
#define KEY_OFF                     1

#define KEY_GPIO_PORT           GPIO5
#define KEY_GPIO_PIN            (0U)
#define KEY_IOMUXC              IOMUXC_SNVS_WAKEUP_GPIO5_IO00

#define MODE_KEY_GPIO_PORT      GPIO1
#define MODE_KEY_GPIO_PIN       (5U)
#define MODE_KEY_IOMUXC         IOMUXC_GPIO_AD_B0_05_GPIO1_IO05

#define KEY_READ()              GPIO_ReadPinInput(KEY_GPIO_PORT,KEY_GPIO_PIN)
#define MODE_KEY_READ()         GPIO_ReadPinInput(MODE_KEY_GPIO_PORT,MODE_KEY_GPIO_PIN)


void KEY_config(void);
uint8_t KEY_scanf(void);



#endif /*__KEY__H*/
