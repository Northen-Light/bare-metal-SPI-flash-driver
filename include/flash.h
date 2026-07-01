#ifndef FLASH_H
#define FLASH_H

typedef struct {
  uint8_t manufacturer;
  uint8_t memory_type;
  uint8_t capacity;
} flash_jedec_id_t;

void flash_init(void);
void flash_read_jedec_id(flash_jedec_id_t *id);

#endif