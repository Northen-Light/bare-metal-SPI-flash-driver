#define RCC_APB2ENR       *((volatile uint32_t *) 0x40021018U)

#define SPI1_CR1          *((volatile uint32_t *) 0x40013000U)
#define SPI1_SR           *((volatile uint32_t *) 0x40013008U)
#define SPI1_DR           *((volatile uint8_t *) 0x4001300CU)

#define GPIOA_CRL         *((volatile uint32_t *) 0x40010800U)
#define GPIOA_IDR         *((volatile uint32_t *) 0x40010808U)
#define GPIOA_ODR         *((volatile uint32_t *) 0x4001080CU)
#define GPIOA_BSRR        *((volatile uint32_t *) 0x40010810U)