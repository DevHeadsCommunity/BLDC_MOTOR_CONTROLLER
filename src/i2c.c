#include "i2c.h"
char temp_value=0;
void i2c_init(void) {
	RCC->APB2ENR |= 1 << 3; // enable portb clock
	RCC->APB1ENR |= 1 << 22;  // enable i2c clock
	I2C2->CR2 |= 36;
	I2C2->CCR |= 180;  // setting the value to
	I2C2->TRISE |= 37;
	I2C2->CR1 |= 1 << 10; // enable ack
	// 7 bit addressing mode is enabled by default
	GPIOB->CRH &= ~(0x0F << 8); // SCL LINE SET AS OUTPUT, OPEN DRAIN
	GPIOB->CRH |= (0x0F << 8);

	GPIOB->CRH &= ~(0x0F << 12); // SDA LINE SET AS OUTPUT, OPEN DRAIN
	GPIOB->CRH |= (0x0F << 12);
     delay_ms(10);
	I2C2->CR1 |= (1 << 0); // enable peripherial

}

void i2c_start(void)
{

	I2C2->CR1 |= (1 << 8);

		while(!(I2C2 -> SR1 & I2C_SR1_SB));


}


void i2c_addr(char addr)
{

	I2C2->DR = addr;
	while(!(I2C2->SR1 & I2C_SR1_ADDR));
	temp_value= I2C2->SR2;

}

void i2c_mem_addr(char mem_addr)
{

	I2C2->DR = mem_addr;
	while(!(I2C2->SR1 & I2C_SR1_TXE));


}

void i2c_write_data(int data)
{
	    I2C2->DR = data;
		while(!(I2C2->SR1 & I2C_SR1_TXE));
}


void i2c_stop(void)
{
	I2C2->CR1 |= (1<<9);

}

void i2c_read(void)
{

}