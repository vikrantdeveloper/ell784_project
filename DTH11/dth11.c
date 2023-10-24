#include "common.h"
#include "dth11.h"

DTH11_buf DTH11_buf_t;
extern TIM_HandleTypeDef htim16;

static void micro_delay(uint32_t delay_cnt)
{
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	while ( __HAL_TIM_GET_COUNTER(&htim16) < delay_cnt);
}

static void set_pin_direction(DTH11_PIN_DIR cnt , GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	switch(cnt)   /*Configure the mode of operation*/
	{
		case DTH11_PIN_DIR_IN:
		{
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		}

		case DTH11_PIN_DIR_OUT:
		{
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		}
	}
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
static uint32_t caltimepulse(GPIO_PinState level, uint32_t maxcount)
{
	uint32_t count = 0;
	while (level == HAL_GPIO_ReadPin(DTH11_PORT, DTH11_PIN))
	{
		micro_delay(1);
		if (count++ >= maxcount + 10)
			return TIMEOUT;
	}
	return count;
}
uint8_t dth11_read()
{
	uint8_t result = 0U;
	uint8_t mask = 0xff;
		for (uint8_t j=0;j<8;j++)
		{
			result <<= 1;
			uint32_t zerocnt = caltimepulse(GPIO_PIN_RESET, 50);
			uint32_t onecnt = caltimepulse(GPIO_PIN_SET, 70);
			if(zerocnt == TIMEOUT || onecnt == TIMEOUT)
			{
				mask = 0U;
			}
			else if(onecnt > zerocnt)
			{
				result |= 1;
			}
		}
		if(!mask)
			HAL_Delay(10);
		return result & mask;
}
void dth11_init()
{
	DTH11_buf_t.log_buf = &console_buf_wr;
	DTH11_buf_t.log_clr = &console_buf_clr;

    set_pin_direction(DTH11_PIN_DIR_OUT , DTH11_PORT, DTH11_PIN); /*configure the input pin as O/P*/
    HAL_GPIO_WritePin(DTH11_PORT, DTH11_PIN, 1);
    HAL_Delay(1500);
    HAL_GPIO_WritePin(DTH11_PORT, DTH11_PIN, 0);   /*Wait for 18 Ms*/ /*Host sends a start signal*/
    HAL_Delay(20000);

    set_pin_direction(DTH11_PIN_DIR_IN , DTH11_PORT, DTH11_PIN); /*configure the input pin as I/P , Host will receive response*/

}
