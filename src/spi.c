#include "spi.h"
#include "stdint.h"
#include "stm32f103xx.h"

static void spi1_wait_txe(void);
static void spi1_wait_rxne(void);

void spi1_init(void) {
  RCC_APB2ENR |= (1U << 2U);
  RCC_APB2ENR |= (1U << 12U);

  GPIOA_CRL &= ~(0xFU << 20U);
  GPIOA_CRL |= (0x9U << 20U);
  GPIOA_CRL &= ~(0xFU << 24U);
  GPIOA_CRL |= (0x8U << 24U);
  GPIOA_ODR |= (1U << 6U);
  GPIOA_CRL &= ~(0xFU << 28U);
  GPIOA_CRL |= (0x9U << 28U);

  SPI1_CR1 &= ~(1U << 6U);
  SPI1_CR1 &= ~(1U << 0U);
  SPI1_CR1 &= ~(1U << 1U);
  SPI1_CR1 |= (1U << 2U);
  SPI1_CR1 |= (0x2U << 3U);
  SPI1_CR1 |= (1U << 8U);
  SPI1_CR1 |= (1U << 9U);
  SPI1_CR1 |= (1U << 6U);
}

uint8_t spi1_transfer(uint8_t tx) {
  spi1_wait_txe();
  SPI1_DR = tx;
  spi1_wait_rxne(); 
  return SPI1_DR;
}

static void spi1_wait_txe(void) {
  while (!(SPI1_SR & (1U << 1U)));
}

static void spi1_wait_rxne(void) {
  while (!(SPI1_SR & (1U << 0U)));
}