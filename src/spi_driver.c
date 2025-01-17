/*
 * Pretty much made to interface with the MAX6675
 */
#include "spi_driver.h"

uint16_t spi_16bit_recieve(SPI_TypeDef *SPI) {
  // while (!(SPI->SR & SPI_SR_TXE)) {
  //   // Make sure TX is empty
  // }

  SPI->DR = 0xFFFF; // Write 16-bit dummy data to trigger communication

  while (!(SPI->SR & SPI_SR_TXE)) {
    // Wait for TX to empty
  }

  while (!(SPI->SR & SPI_SR_RXNE)) {
    // Wait for RX to fill.
  }

  return SPI->DR; // Return contents of DR
}

void spi_init(SPI_TypeDef *SPI) {
  // Setup RCC SPI peripheral bus and GPIO pins
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  if (SPI == SPI1) {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    gpio_init(GPIOA, 5, OUT50, O_AF_PP); // SPI1_SCK Pin
    gpio_init(GPIOA, 6, IN, I_F);        // SPI1_MISO Pin
  } else if (SPI == SPI2) {
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    gpio_init(GPIOB, 13, OUT50, O_AF_PP); // SPI2_SCK Pin
    gpio_init(GPIOB, 14, IN, I_F);        // SPI2_MISO Pin
  }

  // Set MSTR and SPE bits.
  SPI->CR1 = 0;
  SPI->CR1 |= SPI_CR1_MSTR; // Enable master mode
  // Select the CPOL AND CPHA bits (0 and 0 for MAX6675)
  SPI->CR1 &= ~(SPI_CR1_CPOL);
  SPI->CR1 &= ~(SPI_CR1_CPHA);
  // Select BR[2:0] bits to define the serial clock baud rate
  SPI->CR1 |= SPI_CR1_BR; // 256
  // Set the DFF bit to define 8 or 16 bit data frame format.
  // (16-bit for MAX6675)
  SPI->CR1 |= SPI_CR1_DFF;
  // Configure NNS pin if using hardware SC pin. (I'll use software)
  SPI->CR1 |= SPI_CR1_SSI;
  SPI->CR1 |= SPI_CR1_SSM;
  // Configure LSBFIRST bit to define frame format.
  SPI->CR1 &= ~(SPI_CR1_LSBFIRST);
  // Set recieve only (Output pin will be disabled, and SCK will start.)
  // SPI->CR1 |= SPI_CR1_RXONLY;

  SPI->CR1 |= SPI_CR1_SPE; // Enable SPI peripheral
}
