/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Bare-metal GPIO toggle example (STM32F103C8T6)
 ******************************************************************************
 */

#include <stdint.h>

/* Peripheral base addresses */
#define RCC_BASE        0x40021000UL
#define GPIOC_BASE      0x40011000UL

/* RCC Registers */
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))

/* GPIOC Registers */
#define GPIOC_CRL       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

/* Simple delay */
void delay(void)
{
    for (volatile uint32_t i = 0; i < 1000000; i++);
}

int main(void)
{
    /*----------------------------------------------------
      1. Enable GPIOC clock
      IOPBEN = Bit 3 of RCC_APB2ENR
    ----------------------------------------------------*/
    RCC_APB2ENR |= (1 << 4);

    /*----------------------------------------------------
      2. Configure PB5 as Output Push-Pull 2 MHz

      Pin5 occupies bits 23:20 in GPIOC_CRL

      MODE5 = 10 (Output 2MHz)
      CNF5  = 00 (General Purpose Push-Pull)

      Final nibble = 0b0010 = 0x2
    ----------------------------------------------------*/

    GPIOC_CRL &= ~(0xF << 20);   // Clear bits 23:20
    GPIOC_CRL |=  (0x2 << 20);   // Set MODE=10 CNF=00

    /*----------------------------------------------------
      3. Toggle PB5 forever
    ----------------------------------------------------*/
    while (1)
    {
        GPIOC_ODR &= ~(1 << 13);   // LED ON (active LOW)
        delay();

        GPIOC_ODR |= (1 << 13);    // LED OFF
        delay();
    }
}