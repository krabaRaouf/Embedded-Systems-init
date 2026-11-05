#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GPIOA_CRL     (*(volatile uint32_t *)0x40010800)
#define GPIOA_ODR     (*(volatile uint32_t *)0x4001080C)
#define GPIOC_CRH     (*(volatile uint32_t *)0x40011004)
#define GPIOC_ODR     (*(volatile uint32_t *)0x4001100C)
#define RCC_APB2ENR   (*(volatile uint32_t *)0x40021018)





int main(void) {

    // Enable clock for GPIOA and GPIOC
    RCC_APB2ENR |= (1 << 2) | (1 << 4); // Enable clock for GPIOA and GPIOC

    // setting GPIO A pin 5 as output
    GPIOA_CRL &= ~(0xF << 20);// Clear PA5 configuration bits
    GPIOA_CRL |= (0x2 << 20); // Set PA5 as output push-pull, max speed 2 MHz


// setting GPIO C pin 13 as output
    GPIOC_CRH &= ~(0xF << 20); // Clear mode bits for pin 13
    GPIOC_CRH |= (0x2 << 20); // Set pin 13 as output push-pull, max speed 2 MHz

    //initialize GPIO pins
    GPIOA_ODR &= ~(1 << 5);  // PA5 LOW
    GPIOC_ODR &= ~(1 << 13); // PC13 LOW

    while (1) {
        // Toggle GPIO A pin 5
        GPIOA_ODR ^= (1 << 5); // Toggle PA5
        for (volatile int i = 0; i < 500000; i++); // Delay

        // Toggle GPIO C pin 13
        GPIOC_ODR ^= (1 << 13); // Toggle PC13
        for (volatile int i = 0; i < 500000; i++); // Delay
    }
    return 0;
}


// startup code for STM32F103C8T6
// this is the minimal startup code for the STM32F103C8T6 microcontroller.
// It defines the initial entry point of the program and sets up the interrupt vector table.

// naked, noreturn attribute tells the compiler that this function does not 
// return and should not generate any prologue or epilogue code. 
// from the C standard, the main function is expected to return an int value, but in embedded systems,
// the main function typically runs indefinitely and does not return. 
// The naked attribute is used to indicate that the function does not have a 
// standard prologue or epilogue, and the noreturn attribute indicates that the function 
// will not return to the caller.
int main(void);
__attribute__((noreturn)) void _reset(void) {
    main();
    for(;;)(void) 0; // Infinite loop to prevent returning from reset
}

//stack 
extern void _estack(void); // defined from link.ld

//16 and 91 specific interrupt service routine handlers
__attribute__((section(".vectors"))) void (* const tab [16 + 19])(void) = {
    _estack, _reset 
};