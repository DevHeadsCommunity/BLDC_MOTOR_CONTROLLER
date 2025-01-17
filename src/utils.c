#include "utils.h"

static volatile uint32_t tickCounter = 0;

// Set clock speed to 72Mhz
void sysclock_init(void) {
  /* Configure the HCLK to run at 72Mhz */
  RCC->CR |= RCC_CR_HSEON; // Enable HSEON bit

  while (!(RCC->CR & RCC_CR_HSERDY)) {
    // Wait for HSERDY bit to flip to 1.
  }

  // Setup Flash Prefetch Buffer and Latency
  FLASH->ACR |= FLASH_ACR_PRFTBE; // Enable Prefetch buffer status

  FLASH->ACR &= ~(FLASH_ACR_LATENCY); // Reset just in case
  FLASH->ACR |= 0x2; // Set Latency to 2 wait states (For 72Mhz)

  // Configure PLL while it is off
  // Reset PLLSRC, PLLXTPRE, and PLLMUL
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);

  RCC->CFGR &= ~(RCC_CFGR_PLLXTPRE); // PLLXTPRE bit to 0
  RCC->CFGR |= RCC_CFGR_PLLSRC;
  RCC->CFGR |= RCC_CFGR_PLLMULL9; // Multiply PLL frequency (8Mhz) by 9 (72Mhz)
  RCC->CFGR &= ~(RCC_CFGR_HPRE);  // Set HPRE to 0
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 Must not exceed 36Mhz
  RCC->CFGR &= ~(RCC_CFGR_PPRE2);   // APB2 Can run at 72Mhz

  RCC->CR |= RCC_CR_PLLON; // Enable PLLON bit
  while (!(RCC->CR & RCC_CR_PLLRDY)) {
    // Wait till PLLRDY bit to flip to 1
  }

  // Use PLL as SysClock Source
  RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) {
    // Wait for SWS bits to change to 2, aka PLL
  }

  SystemCoreClockUpdate();
}

// Use TIM4 as tick source
void tim4_tick_init(void) {
  // Enable TIM4
  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

  // Enable global interrupt for TIM4
  NVIC_SetPriority(TIM4_IRQn, 0x03);
  NVIC_EnableIRQ(TIM4_IRQn);

  // Make sure TIM4 counter is off
  TIM4->CR1 &= ~(TIM_CR1_CEN);

  // Reset the peripheral.
  RCC->APB1RSTR |= (RCC_APB1RSTR_TIM4RST);
  RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM4RST);

  // Set prescaler/autoreload timing registers
  TIM4->PSC = (SystemCoreClock / 1000000) - 1; // 72Mhz / 1Mhz - 1 = 23
  TIM4->ARR = (1000000 / 1000) - 1;            // 1Mhz / 1000 - 1 = ~1ms

  // Send an update event to reset the timer and apply settings.
  TIM4->EGR |= TIM_EGR_UG;

  // Enable the hardware interrupt.
  TIM4->DIER |= TIM_DIER_UIE;

  // Enable the timer.
  TIM4->CR1 |= TIM_CR1_CEN;
}

void systick_init(void) {
  /* Configure SysTick Counter */
  SysTick->CTRL = 0;          // Reset CTRL
  SysTick->LOAD = 0x00FFFFFF; // Set LOAD to Max value
  SysTick->VAL = 0;           // Reset VAL

  SysTick->CTRL =
      5; // Set CLKSOURCE to AHB, Disable TICKINT, and ENABLE Counter
}

void millisDelay(void) {
  // Set the counter limit to a millisecond

  // I set the clock speed to 72Mhz
  SysTick->LOAD = (SystemCoreClock / 1000) - 1;
  // Reset the SysTick value register
  SysTick->VAL = 0;

  while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) {
    // Wait for the counter to wrap back to zero.
  }
}

// void DelayMS(uint32_t t) {
//   for (; t > 0; t--) {
//     millisDelay();
//   }
// }

uint32_t getTickMillis(void) { return tickCounter; }

void DelayMS(uint32_t t) {
  uint32_t currentTick = tickCounter;

  while ((tickCounter - currentTick) < t) {
    // Wait for t number of ticks.
  }
}

/*void TIM4_IRQHandler(void) {
  if (TIM4->SR & TIM_SR_UIF) {
    TIM4->SR &= ~(TIM_SR_UIF);
    // Increment tickCounter
    tickCounter++;
  }
}*/

uint32_t getPCLK1Freq(void) {
  return (SystemCoreClock >>
          APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos]);
}

uint32_t getPCLK2Freq(void) {
  return (SystemCoreClock >>
          APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos]);
}
