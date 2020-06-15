/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-14 16:30:10
*@FilePath: \RT1052_test\DEMO\hardware\usart.c
*@Drscription: 
***********************************************************************/
#include "usart.h"
#include "pad_config.h"

#include "fsl_iomuxc.h"
#include "fsl_lpuart.h"
#include "stdio.h"

/***********************************************************************
*@Drscription: UART_PAD_CONFIG
***********************************************************************/
#define UART_PAD_SETTING      (SRE_0_SLOW_SLEW_RATE|\
                              DSE_4_R0_4|\
                              SPEED_1_MEDIUM_100MHz|\
                              ODE_0_OPEN_DRAIN_DISABLED|\
                              PKE_0_PULL_KEEPER_DISABLED|\
                              PUE_0_KEEPER_SELECTED|\
                              PUS_2_100K_OHM_PULL_UP|\
                              HYS_0_HYSTERESIS_DISABLED)

/***********************************************************************
*@Function: 
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 16:32:09
*@Drscription: 
***********************************************************************/
void LPUART_config(void)
{
    lpuart_config_t lpuart_config;
	
    LPUART_GetDefaultConfig(&lpuart_config);
    lpuart_config.enableRx=true;
    lpuart_config.enableTx=true;
    LPUART_Init(USB_UART_PORT,&lpuart_config,USB_UART_CLK_FREQ);
    
    IOMUXC_SetPinConfig(USB_UART_TX_IOMUXC,UART_PAD_SETTING);
    IOMUXC_SetPinMux(USB_UART_TX_IOMUXC,0U);

    IOMUXC_SetPinConfig(USB_UART_RX_IOMUXC,UART_PAD_SETTING);
    IOMUXC_SetPinMux(USB_UART_RX_IOMUXC,0U);

}

/***********************************************************************
*@Function: void LPUART_write_data(uint8_t data)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 16:41:14
*@Drscription: 写入字符
***********************************************************************/
void LPUART_write_data(uint8_t data)
{
    LPUART_WriteByte(USB_UART_PORT,data);
    while(USB_UART_PORT->STAT!=LPUART_STAT_TDRE_MASK);
}

/***********************************************************************
*@Function: void LPUART_write_buff(const uint8_t *str)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 16:47:42
*@Drscription: 写入字符串
***********************************************************************/
void LPUART_write_buff(const uint8_t *str)
{
    LPUART_WriteBlocking(USB_UART_PORT,str,strlen(str));

}

/***********************************************************************
*@Function: printf()
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 16:50:15
*@Drscription: printf重定向
***********************************************************************/
int fputc(int ch, FILE * f)
{
    LPUART_write_data((uint8_t )ch);
    
    return ch;
}

