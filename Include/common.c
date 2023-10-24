/*
 * common.c
 *
 *  Created on: Oct 24, 2023
 *      Author: vikrant
 */

#include "common.h"


TIM_HandleTypeDef htim16;


void Timer_Error_Handler(void)
{
  __disable_irq();
  while (1)
  {

  }
}

void MX_TIM16_Init(void)
{
  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM1;
  htim16.Init.Prescaler = TIMER16_PRESCALAR;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = TIMER16_PEROID;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
	  Timer_Error_Handler();
  }
  /* USER CODE END TIM16_Init 1 */
}

void console_buf_wr(char *console_buf , size_t *console_buf_len)
{
	size_t len = *console_buf_len;
	console_buf[len] ='\0';
	for(size_t i = 0; i < len; i++)
	  {
		 _write(stdout, &console_buf[i], 1);
	  }
}
void console_buf_clr(char *console_buf , size_t *console_buf_len)
{
	size_t len = *console_buf_len;
	memset(console_buf  , 0 , len);
	*console_buf_len = 0;
}

