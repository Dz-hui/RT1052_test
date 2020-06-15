/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-10 18:42:11
*@FilePath: \RT1052_test\DEMO\user\main.h
*@Drscription: 
***********************************************************************/
#ifndef _main_h
#define _main_h

#include "fsl_debug_console.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "stdio.h"

#include "led.h"
#include "key.h"
#include "i2c.h"
#include "at24c02.h"
#include "mpu6050.h"
#include "core_delay.h"
#include "usart.h"
#include "board.h"

#define SUCCESS							    1
#define ERROR					    	    0

#define DEBUG_SWITCH                        1
#if DEBUG_SWITCH
#define DEBUG_ERROR(fmt,arg...)             do{printf("<<-ERROR->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)             do{printf("<<-DEBUG->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)                       
#else
#define DEBUG_ERROR(fmt,arg...)
#define DEBUG_PRINT(fmt,arg...)
#endif

#endif
