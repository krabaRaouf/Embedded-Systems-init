# Embedded-Systems-init
A first step into the world of MCUs

1. After more than 10 attempts and over a week of debugging the the Blue Pill finally worked, ALL ALONE, I did nothing. It just worked like that.
2. Now i am blinking a led bare metal:
   First thing, I learned about the peripherals of the mcu, read the block diagram, looked for the address of the registers in the datasheet and how to configure them from the reference manual. 

Day 2 :
In main.c i have written the startup code for the mcu, where i defined the initial entry point of the program and i set up the interrupt vector table.
it contains the reset and the stack functions.
i created a new file called link.ld which organizes the program to the specificality of this mcu, i started by defining 
the begining address of the flash and sram and their legths. 
For the Sectoion part, i specified the vector table to be on top and the rest needs more research.
the Makefile is where the compiler parameters goes on.
I made some mistakes on the syntax (define cannot hold an other defined value), also i made distinguish between CRL/H and ODR (CONFIGURATION VS STATE of the pin).
It was a very fun journey!!!
