#ifndef __MAX6675_DRIVER_H
#define __MAX6675_DRIVER_H
#include "gpio_driver.h"
#include "spi_driver.h"
#include "stm32f1xx.h"
#include "utils.h"

#define TEMP_F 1
#define TEMP_C 0

float max5575_read_temp(SPI_TypeDef *SPI, GPIO_TypeDef *GPIO, uint8_t CSPin,
                        uint8_t tempFormat);
#endif
