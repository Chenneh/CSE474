#ifndef HEADER_LAB
#define HEADER_LAB

#define OFF             0x00
#define RED             0x02
#define BLUE            0x04
#define GREEN           0x08

#define RCGCGPIO        *((volatile unsigned long *)0x400FE608)
#define GPIOF_DIR       *((volatile unsigned long *)0x40025400)
#define GPIOF_DEN       *((volatile unsigned long *)0x4002551C)
#define GPIOF_DATA      *((volatile unsigned long *)0x400253FC)

#define GPIOF_LOCK      *((volatile unsigned long *)0x40025520)
#define GPIOF_CR        *((volatile unsigned long *)0x40025524)
#define GPIOF_PUR       *((volatile unsigned long *)0x40025510)

#define RCGCTIMER       *((volatile unsigned long *)0x400FE604)
#define GPTMCFG_0       *((volatile unsigned long *)0x40030000)
#define GPTMCTL_0       *((volatile unsigned long *)0x4003000C)
#define GPTMTAMR        *((volatile unsigned long *)0x40030004)
#define GPTMTAILR_0     *((volatile unsigned long *)0x40030028)
#define GPTMRIS_0       *((volatile unsigned long *)0x4003001C)
#define GPTMICR_0       *((volatile unsigned long *)0x40030024)


#endif