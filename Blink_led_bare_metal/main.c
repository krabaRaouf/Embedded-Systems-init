#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GPIOA_CRL     (*(volatile uint32_t *)0x40010800)
#define GPIOA_ODR    (*(volatile uint32_t *)GPIOA_CRL + 0x0C)
#define GPIOC_CRH     (*(volatile uint32_t *)0x40011004)
#define GPIOC_ODR    (*(volatile uint32_t *)GPIOC_CRH + 0x0C)
#define RCC_APB2ENR   (*(volatile uint32_t *)0x40021018)

// Enable clock for GPIOA and GPIOC
RCC_APB2ENR |= (1 << 2) | (1 << 4); // Enable clock for GPIOA and GPIOC

// setting GPIO A pin 5 as output
GPIOA_CRL &= ~(0xF << 20);// Clear PA5 configuration bits
GPIOA_CRL |= (0x2 << 20); // Set PA5 as output push-pull, max speed 2 MHz


// setting GPIO C pin 13 as output
GPIOC_CRH &= ~(0xF << 20); // Clear mode bits for pin 13
GPIOC_CRH |= (0x2 << 20); // Set pin 13 as output push-pull, max speed 2 MHz

int main(void) {

    //initialize GPIO pins
    GPIOA_ODR &= ~(1 << 5);  // PA5 LOW
    GPIOC_ODR &= ~(1 << 13); // PC13 LOW

    while (1) {
        // Toggle GPIO A pin 5
        GPIOA_CRL ^= (1 << 5); // Toggle PA5
        for (volatile int i = 0; i < 100000; i++); // Delay

        // Toggle GPIO C pin 13
        GPIOC_CRH ^= (1 << 13); // Toggle PC13
        for (volatile int i = 0; i < 100000; i++); // Delay
    }
    return 0;
}