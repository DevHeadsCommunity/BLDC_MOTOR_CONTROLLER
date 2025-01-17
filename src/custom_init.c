#include "custom_init.h"

float battery, feedBack, dcCurrent;
float shunt = 0.001;
float gain = 76;
float dcCurrentPeak = 0.0;
uint8_t button = 0;
uint8_t timer2_count = 0;
uint16_t value1 = 0;
uint8_t ba3_percentage = 0;
float temperature = 0.00;
long long adc1, adc2, adc3, adc4, adc5, adc6 = 0;
volatile uint16_t timer2_counter = 0;
volatile float feedback = 0.0;
float v_shunt = 0.00;
void custom_Init(void)
{
	RCC->APB2ENR |= 1 << 2; // enable portA clock
	RCC->APB2ENR |= 1 << 3; // enable portB clock
	RCC->APB2ENR |= 1 << 4; // enable portC clock

	GPIOC->CRH &= ~(0x0F << 20); // ON BOARD LED
	GPIOC->CRH |= (0x03 << 20);

	//GPIOB->CRL &= ~(0x0F << 12); // BUZZER
	//GPIOB->CRL |= (0x03 << 12);

	//GPIOB->CRL &= ~(0x0F << 20); // RELAY
	//GPIOB->CRL |= (0x03 << 20);

	//GPIOA->CRL &= ~(0x0F << 28); //  FAN
	//GPIOA->CRL |= (0x03 << 28);

	GPIOB->CRL &= ~(0x0F << 0); // HALL EFFECT SENSOR 1 PB0
	GPIOB->CRL |= (0x04 << 0);

	GPIOB->CRL &= ~(0x0F << 4); // HALL EFFECT SENSOR 2 PB1
	GPIOB->CRL |= (0x04 << 4);

	GPIOB->CRH &= ~(0x0F << 8); // HALL EFFECT SENSOR 3 PB10
	GPIOB->CRH |= (0x04 << 8);

	//GPIOB->CRL &= ~(0x0F << 0); // SG3525 PIN
	//GPIOB->CRL |= (0x03 << 0);

	// AFIO->MAPR |= 2 << 24;
}

uint8_t battery_percentage(float current_voltage, float minimum_voltage,
						   float max_voltage)
{
	return ((current_voltage - minimum_voltage) / (max_voltage - minimum_voltage)) * 100;
}
