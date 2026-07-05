#include "stdint.h"
#include "flash.h"
#include "spi.h"

int main(void) {
  flash_jedec_id_t id;
  flash_status_t status;
  uint8_t out_buffer[600U];
  uint8_t in_buffer[600U];

  for (uint16_t i = 0U; i < 600U; i++)
    in_buffer[i] = i % 256U;

  spi1_init();
  flash_init();
  flash_read_jedec_id(&id);
  flash_64KB_block_erase(0x000000U);
  flash_write(0x0000F0U, in_buffer, 600U);
  flash_read(0x0000F0U, out_buffer, 600U);

  while(1);
  
  return 0;
}