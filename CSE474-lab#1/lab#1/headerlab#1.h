#ifndef HEADER_LAB_1
#define HEADER_LAB_1


#define RCGCGPIO        *((int *)0x400FE608)
#define GPIOF_DIR       *((int *)0x40025400)
#define GPIOF_DEN       *((int *)0x4002551C)
#define GPIOF_DATA      *((int *)0x400253FC)

#define GPIOF_LOCK      *((int *)0x40025520)
#define GPIOF_CR        *((int *)0x40025524)
#define GPIOF_PUR       *((int *)0x40025510)



#endif