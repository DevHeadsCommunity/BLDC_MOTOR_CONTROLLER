#include "timer2.h"

//int timerTick = 0;

void timer2_Init(void) {

	RCC->APB1ENR |= 1 << 0;  // timer clock enable
	TIM2->PSC = 0;
	TIM2->ARR = 3599;  // sets it to work on 20khz
	TIM2->CR1 |= TIM_CR1_URS;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->EGR |= TIM_EGR_UG;
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->CR1 |= 1 << 0;

}