/*
 * Pretty much made to interface with the MAX6675
 */
#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H
#include "gpio_driver.h"
#include "stm32f1xx.h"

uint16_t spi_16bit_recieve(SPI_TypeDef *SPI);

void spi_init(SPI_TypeDef *SPI);

#endif
