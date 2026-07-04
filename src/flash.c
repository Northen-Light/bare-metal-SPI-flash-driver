#include "spi.h"
#include "flash.h"
#include "stm32f103xx.h"
#include "flash_commands.h"

static void flash_select(void);
static void flash_deselect(void);
static void flash_wait_until_ready(void);
static void flash_send_address(uint32_t address);

void flash_init(void) {
  GPIOA_CRL &= ~(0xFU << 16U);
  GPIOA_CRL |= (0x1U << 16U);
  GPIOA_BSRR |= (1U << 4U);
}

void flash_read_jedec_id(flash_jedec_id_t *id) {
  flash_select();
  spi1_transfer(FLASH_CMD_JEDEC_ID);
  id -> manufacturer = spi1_transfer(FLASH_DUMMY_BYTE);
  id -> memory_type = spi1_transfer(FLASH_DUMMY_BYTE);
  id -> capacity = spi1_transfer(FLASH_DUMMY_BYTE);
  flash_deselect();
}

void flash_read_status_register1(uint8_t *status) {
  flash_select();
  spi1_transfer(FLASH_CMD_READ_STATUS);
  *status = spi1_transfer(FLASH_DUMMY_BYTE);
  flash_deselect();
}

flash_status_t flash_write_enable(void) {
  uint8_t status;

  flash_select();
  spi1_transfer(FLASH_CMD_WRITE_ENABLE);
  flash_deselect();
  flash_read_status_register1(&status);

  if ((status & FLASH_SR1_WEL) != 0U)
    return FLASH_WEL_OK;

  return FLASH_WEL_FAILED;
}

void flash_page_program(uint32_t address, const uint8_t *buffer, uint32_t length) {
  flash_wait_until_ready();

  if (flash_write_enable() != FLASH_WEL_OK)
    return;

  flash_select();
  spi1_transfer(FLASH_CMD_PAGE_PROGRAM);
  flash_send_address(address);
  uint32_t ptr = 0U;

  while (ptr < length)
    spi1_transfer(buffer[ptr++]);

  flash_deselect();
  flash_wait_until_ready();
}

void flash_read(uint32_t address, uint8_t *buffer, uint32_t length) {
  uint32_t ptr = 0U;

  flash_wait_until_ready();
  flash_select();
  spi1_transfer(FLASH_CMD_READ_DATA);
  flash_send_address(address);

  while (ptr < length) 
    buffer[ptr++] = spi1_transfer(FLASH_DUMMY_BYTE);

  flash_deselect();
}

void flash_sector_erase(uint32_t address) {
  flash_wait_until_ready();
  
  if (flash_write_enable() != FLASH_WEL_OK)
    return;

  flash_select();
  spi1_transfer(FLASH_CMD_SECTOR_ERASE); 
  flash_send_address(address);   
  flash_deselect();
  flash_wait_until_ready();
}

static void flash_send_address(uint32_t address) {
  spi1_transfer((address >> 16) & 0xFF);
  spi1_transfer((address >> 8) & 0xFF);
  spi1_transfer(address & 0xFF);
}

static void flash_wait_until_ready(void) {
  uint8_t status;
  do {
    flash_read_status_register1(&status);
  } while ((status & FLASH_SR1_BUSY) != 0U);
}

static void flash_select(void) {
  GPIOA_BSRR |= (1U << (4U + 16U));
}

static void flash_deselect(void) {
  GPIOA_BSRR |= (1U << 4U);
}