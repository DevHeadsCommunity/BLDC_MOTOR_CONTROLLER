#include "gpio_driver.h"

void gpio_init(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t direction,
               uint8_t option) {
  volatile uint32_t *CR = &GPIO->CRL;
  uint8_t tPIN = pin;

  if (pin > 7) {
    tPIN -= 8;
    CR = &GPIO->CRH;
  }

  if (GPIO == GPIOA) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable port A
  } else if (GPIO == GPIOB) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable port B
  } else if (GPIO == GPIOC) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable port C
  } else if (GPIO == GPIOD) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN; // Enable port D
  } 

  *CR &= ~(0xF << (tPIN)*4); // Reset the target pin
  // Set up the direction and the option of the PIN
  *CR |= ((direction << (tPIN * 4)) | (option << (tPIN * 4 + 2)));
}

int read_gpio(GPIO_TypeDef *GPIO, uint8_t pin) {
  volatile uint32_t *IDR = &GPIO->IDR;

  // Return the value of the PIN's IDR
  return ((*IDR & (1 << pin)) >> pin);
}

void write_gpio(GPIO_TypeDef *GPIO, uint8_t pin, uint8_t state) {
  volatile uint32_t *ODR = &GPIO->ODR;

  // Set the state of the PIN's ODR
  state ? (*ODR |= (state << pin)) : (*ODR &= ~(1 << pin));
}

void toggle_gpio(GPIO_TypeDef *GPIO, uint8_t pin) {
  if (read_gpio(GPIO, pin)) {
    write_gpio(GPIO, pin, 0);
  } else {
    write_gpio(GPIO, pin, 1);
  }
}
