#include "common.h"
#include "dth11.h"

DTH11_buf DTH11_buf_t;
extern TIM_HandleTypeDef htim16;

static void micro_delay(uint16_t delay_cnt)
{
	__HAL_TIM_SET_COUNTER(&htim16, 0);
	while ( __HAL_TIM_GET_COUNTER(&htim16) < delay_cnt);
}

static void set_pin_dir_OP(GPIO_TypeDef *GPIOx , uint32_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void set_pin_dir_IP(GPIO_TypeDef *GPIOx , uint32_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
static void set_pin_direction(DTH11_PIN_DIR cnt , GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;


	switch(cnt)   /*Configure the mode of operation*/
	{
		case DTH11_PIN_DIR_IN:
		{
			GPIO_InitTypeDef GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = GPIO_Pin;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			break;
		}
		case DTH11_PIN_DIR_OUT:
		{
			GPIO_InitTypeDef GPIO_InitStruct = {0};
			GPIO_InitStruct.Pin = GPIO_Pin;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
			break;
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

uint8_t dth11_check_resp(void)
{
	// Wait 20-40us for DHT to pull the line LOW
	// delay (40);
	if(TIMEOUT == caltimepulse(GPIO_PIN_SET, 40))
		return 0xff;

	// Wait 80us while line has been pulled LOW by DHT
	if(TIMEOUT == caltimepulse(GPIO_PIN_RESET, 80))
		return 0xff;

	// Wait 80us while line has been pulled LOW by DHT
	if(TIMEOUT == caltimepulse(GPIO_PIN_SET, 80))
		return 0xff;

	// Ready to read
	return 1U;
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
void dth11_log(void)
{
	char buf[50];
	sprintf(buf , "temp & hum is %f %f\r\n",  DTH11_buf_t.temp , DTH11_buf_t.humditiy);
	size_t buf_len = strlen(buf) - 1;
	DTH11_buf_t.log_buf(&buf[0] , &buf_len);

}
void dth11_read_temp_hum(void)
{
	 uint8_t Rh_byte1 = dth11_read();
	 uint8_t Rh_byte2 = dth11_read();
	 uint16_t hum = Rh_byte2;
	 hum = hum | (Rh_byte1 << 8);

	 DTH11_buf_t.humditiy = (float)hum / (1 << 8);

	 uint8_t Temp_byte1 = dth11_read();
	 uint8_t Temp_byte2 = dth11_read();
	 uint16_t temp = Temp_byte2;
	 temp = temp | (Temp_byte1 << 8);

	 DTH11_buf_t.temp = (float)temp / (1 << 8);
	 uint8_t P_byte = dth11_read();


}
void dth11_init()
{
	DTH11_buf_t.log_buf = &console_buf_wr;
	DTH11_buf_t.log_clr = &console_buf_clr;

	HAL_GPIO_WritePin (DTH11_PORT, DTH11_PIN, GPIO_PIN_SET);   // pull the pin high
	HAL_Delay(1500);

	set_pin_dir_OP(DTH11_PORT, DTH11_PIN); /*configure the Output pin as O/P*/

    HAL_GPIO_WritePin(DTH11_PORT, DTH11_PIN, GPIO_PIN_RESET);
    micro_delay(18000);
    HAL_GPIO_WritePin(DTH11_PORT, DTH11_PIN, GPIO_PIN_SET);

    set_pin_dir_IP(DTH11_PORT, DTH11_PIN); /*configure the input pin as I/P , Host will receive response*/

}
