#ifndef INC_I2C_H_
#define INC_I2C_H_

#include <stdio.h>
#include <stdint.h>
#include "timer4.h"
#include "stm32f1xx.h"
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_mem_addr(char mem_addr);
void i2c_addr(char addr);
void i2c_write_data(int data);
void i2c_read(void);
 extern char temp_value;

#endif /* INC_I2C_H_ */