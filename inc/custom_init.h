#ifndef INC_CUSTOM_INIT_H_
#define INC_CUSTOM_INIT_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx.h"

#define ONBOARDLEDON GPIOC->ODR |= (1 << 13)
#define ONBOARDLEDOFF GPIOC->ODR &= ~(1 << 13)
#define BUZZERON GPIOB->ODR |= (1 << 3)
#define BUZZEROFF GPIOB->ODR &= ~(1 << 3)
#define MIN_BATTERY_VOLTAGE 22.5
#define MAX_BATTERY_VOLTAGE 26.0
#define H1_PIN (1 << 0)  // Pin 0
#define H2_PIN (1 << 1)  // Pin 1
#define H3_PIN (1 << 10)  // Pin 10

extern volatile float feedback;
extern long long adc1, adc2, adc3, adc4, adc5, adc6;
extern uint8_t battery_percent;
extern volatile uint16_t timer2_counter;
void custom_Init(void);
uint8_t battery_percentage(float current_voltage, float minimum_voltage,
		float max_voltage);
#endif /* INC_CUSTOM_INIT_H_ */