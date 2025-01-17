#include "gpio_driver.h"
#include "spi_driver.h"
#include "stm32f1xx.h"
#include "utils.h"

float max5575_read_temp(SPI_TypeDef *SPI, GPIO_TypeDef *GPIO, uint8_t CSPin,
                        uint8_t tempFormat) {
  uint16_t data = 0;
  uint8_t TNF = 0;
  float temp = 0;

  // Start communication via CS Pin.
  write_gpio(GPIO, CSPin, LOW); // Start transfer

  data = spi_16bit_recieve(SPI); // Recieve data

  write_gpio(GPIO, CSPin, HIGH); // Stop transfer

  TNF = (data >> 2 & 0x0001); // bit 2 is high if thermocouple input is open.

  temp = (data >> 3); // Bits [14:3] is the temperature in float.

  temp *= 0.25; // Data to Centigrade Conversion.

  if (tempFormat) {
    temp = temp * 9.0 / 5 + 32; // fahrenheit conversion
  }

  DelayMS(250); // Wait for device to reset.

  if (TNF) {
    return TNF;
  } else {
    return temp;
  }
}
