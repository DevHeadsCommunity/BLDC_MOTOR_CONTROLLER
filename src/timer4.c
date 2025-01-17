#include "timer4.h"

volatile int timerTick = 0;

void delay_ms(int ms) {

	//timerTick = 0;
	//TIM4->CR1 |= 1 << 0;
	//while (timerTick<(ms*1000));
	//TIM4->CR1 &= ~TIM_CR1_CEN;

    timerTick = 0;
    TIM4->CR1 |= 1 << 0;
    while(timerTick < (ms*1000));
    TIM4->CR1 &= ~TIM_CR1_CEN;

}


void delay_us(int us) {

	timerTick = 0;
	TIM4->CR1 |= 1 << 0;
	while (timerTick<us);

	TIM4->CR1 &= ~TIM_CR1_CEN;


}

void TIM4_IRQHandler(void) {
	timerTick++;
 //GPIOA->ODR |= (1 << 11);
	TIM4->SR &= ~TIM_SR_UIF;
}

void timer4_Init(void)
{
RCC->APB1ENR |= 1 << 2;
        TIM4->PSC =0;
        TIM4->ARR = 72;
        TIM4->CR1 |= TIM_CR1_URS;
        TIM4->DIER |= TIM_DIER_UIE;
        TIM4->EGR |= TIM_EGR_UG;
        NVIC_EnableIRQ(TIM4_IRQn);


}