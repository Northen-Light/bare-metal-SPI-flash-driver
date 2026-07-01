#ifndef SPI_H
#define SPI_H

#include "stdint.h"

void spi1_init(void);
uint8_t spi1_transfer(uint8_t tx);
void spi1_wait_non_busy(void);

#endif 