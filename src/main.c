#include "stdint.h"
#include "flash.h"
#include "spi.h"

int main(void) {
  spi1_init();
  flash_init();
  flash_jedec_id_t id;
  flash_read_jedec_id(&id);
  while(1);
  return 0;
}