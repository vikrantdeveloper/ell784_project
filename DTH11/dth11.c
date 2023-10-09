#include "stm32f722xx.h"
#include "dth11.h"

static void set_pin_direction(DTH11_PIN_DIR cnt , GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	switch(cnt)
	{
		case DTH11_PIN_DIR_IN:
		{

		}

		case DTH11_PIN_DIR_OUT:
		{

		}
		default:
		{

		}
	}
}
void dth11_init()
{
    set_pin_direction(DTH11_PIN_DIR_IN , DTH11_PORT, DTH11_PIN);
}
