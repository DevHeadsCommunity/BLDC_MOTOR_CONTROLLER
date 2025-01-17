#include "timer3.h"
int count=0;
unsigned int count1=0;


void timer3_Init(void)
{


	RCC->APB1ENR |= 1 << 1;  // timer clock enable
		TIM3->PSC = 0;
		TIM3->ARR = 3599;
		TIM3->CR1 |= TIM_CR1_URS;
		TIM3->DIER |= TIM_DIER_UIE;
		TIM3->EGR |= TIM_EGR_UG;
		NVIC_EnableIRQ(TIM3_IRQn);
//lcd_printf("YES");

}