/*
 * common.h
 *
 *  Created on: Oct 24, 2023
 *      Author: vikrant
 */
#ifndef __COMMON__

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "main.h"
/*#include "stm32f7xx_hal_tim.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_gpio.h"*/

/*Initialise the timer*/
extern TIM_HandleTypeDef htim16;

#define TIMER6_PRESCALAR (8 - 1)
#define TIMER6_PEROID  (65535 - 1)


/*Pin Configuration*/
#define DTH11_PORT  GPIOB
#define DTH11_PIN   GPIO_PIN_2

/*WiFi Console Port*/
#define UART_WIFI_CMD            USART2
#define UART_CONSOLE             USART3

/*WiFi Parameters*/
#define WIFI_RST


#define SSID  "Johan"
#define PSK   "123456789"

#define TCP_IP   "10.42.0.1"
#define TCP_PORT  "8080"

#define CHAR_KEY "J2ZEQNXPJKHH6768"



/*Console onto the console windows*/

void tim6_init();
void console_buf_clr(char *console_buf , size_t *console_buf_len);
void console_buf_wr(char *console_buf , size_t *console_buf_len);
extern int _write(int file, char *ptr, int len);




#endif
