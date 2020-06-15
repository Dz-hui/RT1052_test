/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-14 16:27:50
*@FilePath: \RT1052_test\DEMO\hardware\usart.h
*@Drscription: 
***********************************************************************/
#ifndef __USART__H
#define __USART__H

#include "fsl_common.h"

#define USB_UART_TX_GPIO       GPIO1
#define USB_UART_TX_PIN        (12U)
#define USB_UART_TX_IOMUXC     IOMUXC_GPIO_AD_B0_12_LPUART1_TX

#define USB_UART_RX_GPIO       GPOIO1
#define USB_UART_RX_PIN        (13U)
#define USB_UART_RX_IOMUXC     IOMUXC_GPIO_AD_B0_13_LPUART1_RX

#define USB_UART_PORT          LPUART1
#define USB_UART_CLK_FREQ      BOARD_DebugConsoleSrcFreq()

void LPUART_config(void);
void LPUART_write_data(uint8_t data);
void LPUART_write_buff(const uint8_t *str);

#endif /*__USART__H*/

