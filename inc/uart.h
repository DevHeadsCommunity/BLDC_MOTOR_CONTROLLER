
#ifndef __UART_H
#define __UART_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f1xx.h"
#include "timer4.h"
void uart_init(void);
void USART1_IRQHandler(void);
void uart_print(char data);
void uart_printn(float x);
void uart_printf(char *str);
extern volatile char temp_uart_data[];
extern uint8_t debug_flag;
extern int data_debug_position;
//extern char value[10];



#endif /* INC_UART_H_ */
