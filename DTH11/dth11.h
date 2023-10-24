#ifndef  _DTH11_H

#define TIMEOUT ((uint32_t)0xffffffff)
#define DTH11_PORT  GPIOB
#define DTH11_PIN   GPIO_PIN_1

typedef void (*console_buff_log_t)(char * , size_t *);          /*clear & print logs*/
typedef enum{
    DTH11_PIN_DIR_IN,
    DTH11_PIN_DIR_OUT
}DTH11_PIN_DIR;

typedef struct{
	int temp;
	float humditiy;
	console_buff_log_t log_buf;
	console_buff_log_t log_clr;
}DTH11_buf;

#ifdef __cplusplus
extern "C"{

#endif

void dth11_init();
uint8_t dth11_read();

#ifdef __cplusplus
}
#endif
#endif
