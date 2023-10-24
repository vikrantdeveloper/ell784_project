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

/*Console onto the console windows*/


void console_buf_clr(char *console_buf , size_t *console_buf_len);
void console_buf_wr(char *console_buf , size_t *console_buf_len);

/*Initialise the timer*/

#define TIMER16_PRESCALAR (48 - 1)
#define TIMER16_PEROID  (65536 - 1)

extern TIM_HandleTypeDef htim16;

extern int _write(int file, char *ptr, int len);

void MX_TIM16_Init();



#endif
