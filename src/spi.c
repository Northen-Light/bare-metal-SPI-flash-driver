#include "spi.h"
#include "stdint.h"
#include "stm32f103xx.h"

static void spi1_wait_txe(void);
static void spi1_wait_rxne(void);

void spi1_init(void) {
  RCC_APB2ENR |= (1 << 2);
  RCC_APB2ENR |= (1 << 12);

  GPIOA_CRL &= ~(0xF << 20);
  GPIOA_CRL |= (0x9 << 20);
  GPIOA_CRL &= ~(0xF << 24);
  GPIOA_CRL |= (0x8 << 24);
  GPIOA_ODR |= (1 << 6);
  GPIOA_CRL &= ~(0xF << 28);
  GPIOA_CRL |= (0x9 << 28);

  SPI1_CR1 &= ~(1 << 6);
  SPI1_CR1 &= ~(1 << 0);
  SPI1_CR1 &= ~(1 << 1);
  SPI1_CR1 |= (1 << 2);
  SPI1_CR1 |= (0x2 << 3);
  SPI1_CR1 |= (1 << 8);
  SPI1_CR1 |= (1 << 9);
  SPI1_CR1 |= (1 << 6);
}

uint8_t spi1_transfer(uint8_t tx) {
  spi1_wait_txe();
  SPI1_DR = tx;
  spi1_wait_rxne(); 
  return SPI1_DR;
}

void spi1_wait_non_busy(void) {
  while(SPI1_SR & (1 << 7));
}

static void spi1_wait_txe(void) {
  while (!(SPI1_SR & (1 << 1)));
}

static void spi1_wait_rxne(void) {
  while (!(SPI1_SR & (1 << 0)));
}