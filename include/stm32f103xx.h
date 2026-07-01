#define RCC_APB2ENR       *((volatile unsigned int *) 0x40021018)

#define SPI1_CR1          *((volatile unsigned int *) 0x40013000)
#define SPI1_SR           *((volatile unsigned int *) 0x40013008)
#define SPI1_DR           *((volatile unsigned int *) 0x4001300C)

#define GPIOA_CRL         *((volatile unsigned int *) 0x40010800)
#define GPIOA_IDR         *((volatile unsigned int *) 0x40010808)
#define GPIOA_ODR         *((volatile unsigned int *) 0x4001080C)
#define GPIOA_BSRR        *((volatile unsigned int *) 0x40010810)