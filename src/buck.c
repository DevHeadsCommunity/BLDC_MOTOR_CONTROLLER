#include "buck.h"
uint8_t commutation_step = 1;
void buck_init()
{
	//	RCC->APB1ENR |= 1 << 1;  // timer clock enable
	//	AFIO->MAPR |= (1 << 11);
	//	GPIOB->CRL &= ~(0x0F << 20);
	//	GPIOB->CRL |= (0x0B << 20);
	//	TIM3->PSC = 0; //100KHZ
	//	TIM3->ARR = 3599;
	//	TIM3->CCER |= (1 << 4);
	//	TIM3->CR1 |= (1 << 7);
	//	TIM3->CCMR1 |= (1 << 13);
	//	TIM3->CCMR1 |= (1 << 14); //PWM MODE 1A
	//	TIM3->CCMR1 |= (1 << 11);
	//	//TIM3->CR1 |= TIM_CR1_URS;
	//	//TIM3->DIER |= TIM_DIER_UIE;
	//	TIM3->EGR |= TIM_EGR_UG;
	//	TIM3->CR1 |= (1 << 0);
	//	//NVIC_EnableIRQ(TIM3_IRQn);

	/*RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_TIM1EN;

	// SETTING PA8---> TIMER1 CH1 AS ALTERNATE FUNCTION O/P AND PB13----> TIMER1 CH1N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 0);
	GPIOA->CRH |= (0x0B << 0);

	GPIOB->CRH &= ~(0x0F << 20);
	GPIOB->CRH |= (0x0B << 20);

	// SETTING PA9---> TIMER1 CH2 AS ALTERNATE FUNCTION O/P AND PB14----> TIMER1 CH2N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 4);
	GPIOA->CRH |= (0x0B << 4);

	GPIOB->CRH &= ~(0x0F << 24);
	GPIOB->CRH |= (0x0B << 24);

	// SETTING AUTO RELOAD VALUE AND PRESCALER VALUE
	TIM1->PSC = 0;

	TIM1->ARR = 1799;

	TIM1->CR1 |= (1 << 7);
	TIM1->CR1 |= (1 << 5); // take note of this
	TIM1->CR1 |= 1 << 2;
	// TIM1->CR2 |= (1 << 8) | (1 << 9) |(1 << 10) | (1 << 11);

	// SETTING CHANNEL 1 AND 2 IN COMPLEMENTARY MODE AND SETTING THERE OUTPUT PRELOAD REGISTER
	TIM1->CCMR1 |= (6 << 4) | (6 << 12);
	TIM1->CCMR1 |= (1 << 3) | (1 << 11);

	// ENABLES CHANNEL 1 AND CHANNEL 2 AND THERE COMPLEMENTARY PINS
	TIM1->CCER |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6); //| (1<<5)| (1<<7)| (1<<1)| (1<<3);

	TIM1->BDTR |= (1 << 15) | (1 << 11) | (1 << 10);
	// set deadtime to 1us
	//		TIM1->BDTR |= (0x8 << 8);  // DTG[7:0] = 8
	//		TIM1->BDTR |= (0x4 << 5);  // DTG[10:8] = 4
	//		TIM1->BDTR |= (1 << 4);    // LOCK = 1

	// TIM1->DIER |= TIM_DIER_UIE;
	TIM1->EGR |= TIM_EGR_UG;

	 //NVIC_EnableIRQ(TIM1_CC_IRQn);

	// WORKING ON THE DEAD TIME GENERATOR
	TIM1->BDTR |= (205 << 0); // 5us deadtime

	//NVIC_EnableIRQ(TIM1_UP_IRQn);
*/

	/*RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN
			| RCC_APB2ENR_TIM1EN;
	GPIOA->CRH &= ~(0x0F << 0);
	GPIOA->CRH |= (0x0B << 0);

	GPIOB->CRH &= ~(0x0F << 20);
	GPIOB->CRH |= (0x0B << 20);

	TIM1->PSC = 0;

	TIM1->ARR = 1028;
	TIM1->CR1 |= (1 << 7);
	TIM1->CR1 |= (1 << 5);    // take note of this
	TIM1->CR1 |= 1 << 2;

	TIM1->CCMR1 |= (6 << 4);
	TIM1->CCMR1 |= (1 << 3);

	TIM1->CCER |= (1 << 0) | (1 << 2);
	TIM1->BDTR |= (1 << 15);
	TIM1->BDTR |= (1 << 10);
	TIM1->BDTR |= (1 << 11);
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->BDTR |= (205 << 0);
	TIM1->CR1 |= (1 << 0);*/

	/*RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_TIM1EN;

	// SETTING PA8---> TIMER1 CH1 AS ALTERNATE FUNCTION O/P AND PB13----> TIMER1 CH1N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 0);
	GPIOA->CRH |= (0x0B << 0);

	GPIOB->CRH &= ~(0x0F << 20);
	GPIOB->CRH |= (0x0B << 20);

	// SETTING PA9---> TIMER1 CH2 AS ALTERNATE FUNCTION O/P AND PB14----> TIMER1 CH2N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 4);
	GPIOA->CRH |= (0x0B << 4);

	GPIOB->CRH &= ~(0x0F << 24);
	GPIOB->CRH |= (0x0B << 24);

	// SETTING PA10---> TIMER1 CH3 AS ALTERNATE FUNCTION O/P AND PB15----> TIMER1 CH3N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 8);
	GPIOA->CRH |= (0x0B << 8);

	GPIOB->CRH &= ~(0x0F << 28);
	GPIOB->CRH |= (0x0B << 28);

	// SETTING AUTO RELOAD VALUE AND PRESCALER VALUE
	TIM1->PSC = 0;

	TIM1->ARR = 3599;

	TIM1->CR1 |= (1 << 7);
	TIM1->CR1 |= (1 << 5); // take note of this
	TIM1->CR1 |= 1 << 2;
	// TIM1->CR2 |= (1 << 8) | (1 << 9) |(1 << 10) | (1 << 11);

	// SETTING CHANNEL 1 AND 2 IN COMPLEMENTARY MODE AND SETTING THERE OUTPUT PRELOAD REGISTER
	TIM1->CCMR1 |= (6 << 4) | (6 << 12);
	TIM1->CCMR2 |= (6 << 4);
	TIM1->CCMR1 |= (1 << 3) | (1 << 11);
	TIM1->CCMR2 |= (1 << 3);
	// ENABLES CHANNEL 1 AND CHANNEL 2 AND THERE COMPLEMENTARY PINS
	TIM1->CCER |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6)| (1<<8)| (1<<10);//| (1<<1)| (1<<3);

	TIM1->BDTR |= (1 << 15) | (1 << 11) | (1 << 10);
	// set deadtime to 1us
	//		TIM1->BDTR |= (0x8 << 8);  // DTG[7:0] = 8
	//		TIM1->BDTR |= (0x4 << 5);  // DTG[10:8] = 4
	//		TIM1->BDTR |= (1 << 4);    // LOCK = 1

	// TIM1->DIER |= TIM_DIER_UIE;
	TIM1->EGR |= TIM_EGR_UG;

	// NVIC_EnableIRQ(TIM1_CC_IRQn);

	// WORKING ON THE DEAD TIME GENERATOR
	TIM1->BDTR |= (205 << 0); // 5us deadtime*/
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_TIM1EN;

	// SETTING PA8---> TIMER1 CH1 AS ALTERNATE FUNCTION O/P AND PB13----> TIMER1 CH1N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 0);
	GPIOA->CRH |= (0x0B << 0);

	GPIOB->CRH &= ~(0x0F << 20);
	GPIOB->CRH |= (0x0B << 20);

	// SETTING PA9---> TIMER1 CH2 AS ALTERNATE FUNCTION O/P AND PB14----> TIMER1 CH2N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 4);
	GPIOA->CRH |= (0x0B << 4);

	GPIOB->CRH &= ~(0x0F << 24);
	GPIOB->CRH |= (0x0B << 24);

	// SETTING PA10---> TIMER1 CH3 AS ALTERNATE FUNCTION O/P AND PB15----> TIMER1 CH3N AS ALT FUNCTION O/P
	GPIOA->CRH &= ~(0x0F << 8);
	GPIOA->CRH |= (0x0B << 8);

	GPIOB->CRH &= ~(0x0F << 28);
	GPIOB->CRH |= (0x0B << 28);

	// SETTING AUTO RELOAD VALUE AND PRESCALER VALUE
	TIM1->PSC = 0;

	TIM1->ARR = 3599;

	TIM1->CR1 |= (1 << 7);
	TIM1->CR1 |= (1 << 5); // take note of this
	TIM1->CR1 |= 1 << 2;
	// TIM1->CR2 |= (1 << 8) | (1 << 9) |(1 << 10) | (1 << 11);

	// SETTING CHANNEL 1 AND 2 IN COMPLEMENTARY MODE AND SETTING THERE OUTPUT PRELOAD REGISTER
	TIM1->CCMR1 |= (6 << 4) | (6 << 12);
	TIM1->CCMR2 |= (6 << 4);
	TIM1->CCMR1 |= (1 << 3) | (1 << 11);
	TIM1->CCMR2 |= (1 << 3);
	// ENABLES CHANNEL 1 AND CHANNEL 2 AND THERE COMPLEMENTARY PINS
	TIM1->CCER |= (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6)| (1<<8)| (1<<10);//| (1<<1)| (1<<3);

	TIM1->BDTR |= (1 << 15) | (1 << 11) | (1 << 10);
	// set deadtime to 1us
	//		TIM1->BDTR |= (0x8 << 8);  // DTG[7:0] = 8
	//		TIM1->BDTR |= (0x4 << 5);  // DTG[10:8] = 4
	//		TIM1->BDTR |= (1 << 4);    // LOCK = 1

	// TIM1->DIER |= TIM_DIER_UIE;
	TIM1->EGR |= TIM_EGR_UG;

	// NVIC_EnableIRQ(TIM1_CC_IRQn);

	// WORKING ON THE DEAD TIME GENERATOR
	TIM1->BDTR |= (205 << 0); // 5us deadtime
}
