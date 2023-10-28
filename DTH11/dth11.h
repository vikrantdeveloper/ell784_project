#ifndef  _DTH11_H

#define TIMEOUT ((uint32_t)0xffffffff)


typedef void (*console_buff_log_t)(char * , size_t *);          /*clear & print logs*/
typedef enum{
    DTH11_PIN_DIR_IN,
    DTH11_PIN_DIR_OUT
}DTH11_PIN_DIR;

typedef struct{
	float temp;
	float humditiy;
	console_buff_log_t log_buf;
	console_buff_log_t log_clr;
}DTH11_buf;

extern DTH11_buf DTH11_buf_t;
#ifdef __cplusplus
extern "C"{

#endif

void dth11_init();
uint8_t dth11_check_resp(void);
void dth11_read_temp_hum(void);
void dth11_log(void);

#ifdef __cplusplus
}
#endif
#endif
