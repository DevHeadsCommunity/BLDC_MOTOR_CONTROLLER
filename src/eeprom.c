#include "eeprom.h"
#include "i2c.h"
char EEprom_data = 0;
uint8_t eeprom_temp = 0;
uint8_t eeprom_buff[5] = {0};


void eeprom_write(char first_address, char last_address, char eeprom_data)
{
            i2c_start();
			delay_ms(1);
			i2c_addr(EEPROM_WRITE);
			delay_ms(1);
			i2c_mem_addr(first_address);
			delay_ms(1);
            i2c_mem_addr(last_address);
			delay_ms(1);
			i2c_write_data(eeprom_data);
			i2c_stop();
}


 uint8_t eeprom_read(char first_address, char last_address)
{
    i2c_start();
    delay_ms(5);
    i2c_addr(EEPROM_READ);
    delay_ms(5);
    EEprom_data = I2C2->DR;

    i2c_stop();
    return EEprom_data;
}
//void eeprom_write(uint8_t address, uint8_t data) {
//	i2c_start();
//	delay_ms(1);
//	i2c_addr(EEPROM_WRITE);
//	delay_ms(1);
//	i2c_mem_addr(address);
//	delay_ms(1);
//	i2c_write_data(data);
//	i2c_stop();
//}
//
//void eeprom_read(uint8_t lenght) {
//	eeprom_temp = 0;
//	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
//	I2C1->CR2 |= I2C_CR2_DMAEN;
//	I2C1->CR1 |= I2C_CR1_ACK;
//	DMA1_Channel5->CMAR = (uint8_t) eeprom_buff;
//	DMA1_Channel5->CPAR = (uint32_t) &I2C1->DR;
//	DMA1_Channel5->CNDTR = lenght;
//	DMA1_Channel5->CCR |= DMA_CCR_TCIE | DMA_CCR_MINC | DMA_CCR_EN;
//
//
//	i2c_start();
//	delay_ms(5);
//	i2c_addr(EEPROM_READ);
//	delay_ms(5);
//	while ((DMA1->ISR & DMA_ISR_TCIF5) == 0)
//		;
//	i2c_stop();
//
//}