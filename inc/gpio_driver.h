#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H
#include "stdint.h"
#include "stm32f1xx.h"

// GPIO Directions
#define IN 0
#define OUT10 1
#define OUT2 2
#define OUT50 3

// GPIO Input options
#define I_AN 0
#define I_F 1
#define I_PP 2

// GPIO Output options
#define O_GP_PP 0
#define O_GP_OD 1
#define O_AF_PP 2
#define O_AF_OD 3

// States
#define LOW 0
#define HIGH 1

void gpio_init(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t direction,
               uint8_t option);

int read_gpio(GPIO_TypeDef *GPIO, uint8_t pin);

void write_gpio(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t state);

void toggle_gpio(GPIO_TypeDef *GPIO, uint8_t pin);
#endif
