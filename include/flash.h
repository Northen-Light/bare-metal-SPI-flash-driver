#ifndef FLASH_H
#define FLASH_H

#define FLASH_SR1_BUSY    (1U << 0)
#define FLASH_SR1_WEL     (1U << 1)

typedef struct {
  uint8_t manufacturer;
  uint8_t memory_type;
  uint8_t capacity;
} flash_jedec_id_t;

typedef enum {
  FLASH_WEL_OK = 0,
  FLASH_WEL_FAILED
} flash_status_t;

void flash_init(void);
void flash_read_jedec_id(flash_jedec_id_t *id);
void flash_read_status_register1(uint8_t *status);
flash_status_t flash_write_enable(void);
void flash_page_program(uint32_t address, const uint8_t *buffer, uint32_t length);
void flash_read(uint32_t address, uint8_t *buffer, uint32_t length);
void flash_sector_erase(uint32_t address);

#endif