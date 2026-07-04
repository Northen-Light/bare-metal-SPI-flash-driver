#include "stdint.h"
#include "flash.h"
#include "spi.h"

int main(void) {
  flash_jedec_id_t id;
  flash_status_t status;
  const uint8_t in_buffer[] = {0x10, 0x20};
  uint8_t out_buffer[10];

  spi1_init();
  flash_init();
  flash_read_jedec_id(&id);
  flash_page_program(0x100000, in_buffer, 2);
  flash_read(0x100000, out_buffer, 2);

  while(1);
  
  return 0;
}