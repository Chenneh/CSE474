#ifndef HEADER_LAB_1
#define HEADER_LAB_1


#define RCGCGPIO        *((volatile unsigned long *)0x400FE608) // to enable port
#define GPIOF_DIR       *((volatile unsigned long *)0x40025400) // to set input and output on portF
#define GPIOF_DEN       *((volatile unsigned long *)0x4002551C) // to digital enable port F
#define GPIOF_DATA      *((volatile unsigned long *)0x400253FC) // to access data on port F

#define GPIOF_LOCK      *((volatile unsigned long *)0x40025520) // to unlock special pin
#define GPIOF_CR        *((volatile unsigned long *)0x40025524) // need to set up when special pin is unlock
#define GPIOF_PUR       *((volatile unsigned long *)0x40025510) // to pull up resistor for switches



#endif
