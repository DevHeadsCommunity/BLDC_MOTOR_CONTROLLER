#ifndef __TIMER4_H
#define __TIMER4_H
#include <stdio.h>
#include <stdint.h>
#include "stm32f1xx.h"

void delay_ms(int ms);
void delay_us(int us);
void TIM4_IRQHandler(void);
void timer4_Init(void);
#endif