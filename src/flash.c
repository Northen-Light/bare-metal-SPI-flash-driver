#include "spi.h"
#include "flash.h"
#include "stm32f103xx.h"
#include "flash_commands.h"

static void flash_cs_select(void);
static void flash_cs_deselect(void);

void flash_init(void) {
  GPIOA_CRL &= ~(0xF << 16);
  GPIOA_CRL |= (0x5 << 16);
  GPIOA_BSRR |= (1 << 4);
}

void flash_read_jedec_id(flash_jedec_id_t *id) {
  flash_cs_select();

  spi1_transfer(FLASH_CMD_JEDEC_ID);
  id -> manufacturer = spi1_transfer(FLASH_DUMMY_BYTE);
  id -> memory_type = spi1_transfer(FLASH_DUMMY_BYTE);
  id -> capacity = spi1_transfer(FLASH_DUMMY_BYTE);

  spi1_wait_non_busy();
  flash_cs_deselect();
}

static void flash_cs_select(void) {
  GPIOA_BSRR |= (1 << (4 + 16));
}

static void flash_cs_deselect(void) {
  GPIOA_BSRR |= (1 << 4);
}