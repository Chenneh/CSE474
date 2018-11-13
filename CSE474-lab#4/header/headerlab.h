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

#define GPTMIMR_0       *((volatile unsigned long *)0x40030018)
#define NVIC_EN0        *((volatile unsigned long *)0xE000E100)
#define GPIOF_IS        *((volatile unsigned long *)0x40025404)
#define GPIOF_IBE       *((volatile unsigned long *)0x40025408)
#define GPIOF_IEV       *((volatile unsigned long *)0x4002540C)
#define GPIOF_IM        *((volatile unsigned long *)0x40025410)
#define GPIOF_ICR       *((volatile unsigned long *)0x4002541C)

#define RCGCADC         *((volatile unsigned long *)0x400FE638)
#define GPIOE_AFSEL     *((volatile unsigned long *)0x40024420)
#define GPIOE_DEN       *((volatile unsigned long *)0x4002451C)
#define GPIOE_AMSEL     *((volatile unsigned long *)0x40024528)
#define ADC0_ACTSS      *((volatile unsigned long *)0x40038000)
#define ADC0_EMUX       *((volatile unsigned long *)0x40038014)
#define ADC0_SSMUX_3    *((volatile unsigned long *)0x400380A0)
#define ADC0_SSCTL_3    *((volatile unsigned long *)0x400380A4)
#define ADC0_IM         *((volatile unsigned long *)0x40038008)
#define ADC0_PSSI       *((volatile unsigned long *)0x40038028)
#define ADC0_ISC        *((volatile unsigned long *)0x4003800C)
#define ADC0_FIFO3      *((volatile unsigned long *)0x400380A8)
#define ADC0_RIS        *((volatile unsigned long *)0x40038004)
#define RCC             *((volatile unsigned long *)0x400FE060)
#define RCC2            *((volatile unsigned long *)0x400FE070)
#define RIS             *((volatile unsigned long *)0x400FE050)

#endif
