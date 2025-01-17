#ifndef __TIMER3_H
#define __TIMER3_H
#include <stdio.h>
#include <stdint.h>
#include "stm32f1xx.h"
extern uint8_t commutation_step;
extern int count;
extern unsigned int count1;
void timer3_Init(void);
void TIM3_IRQHandler(void);



#endif