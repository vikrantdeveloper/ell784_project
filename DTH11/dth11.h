#ifndef  _DTH11_H

#define DTH11_PORT  GPIOB
#define DTH11_PIN   GPIO_PIN_1

typedef enum{
    DTH11_PIN_DIR_IN,
    DTH11_PIN_DIR_OUT
}DTH11_PIN_DIR;

void dth11_init();

#endif
