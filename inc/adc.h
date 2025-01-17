#ifndef __ADC_H
#define __ADC_H
#include <stdint.h>
#include "stm32f1xx.h"
void adc_Init(void);
extern uint16_t adcValue[4];
extern float  battery;
#endif /* INC_ADC_H_ */