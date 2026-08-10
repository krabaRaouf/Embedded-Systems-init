#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GPIOA_CRL     (*(volatile uint32_t *)0x40010800)
#define GPIOC_CRH     (*(volatile uint32_t *)0x40011004)

// setting GPIO A pin 5 as output
GPIOA_CRL &= ~(0xF << 20);// Clear PA5 configuration bits
GPIOA_CRL |= (0x2 << 20); // Set PA5 as output push-pull, max speed 2 MHz


// setting GPIO C pin 13 as output
GPIOC_CRH &= ~(0xF << 20); // Clear mode bits for pin 13
GPIOC_CRH |= (0x2 << 20); // Set pin 13 as output push-pull, max speed 2 MHz

