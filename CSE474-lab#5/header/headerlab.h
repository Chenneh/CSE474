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

#define RCGCUART        *((volatile unsigned long *)0x400FE618)

#define GPIOC_AFSEL     *((volatile unsigned long *)0x40006420)
#define GPIOC_PCTL      *((volatile unsigned long *)0x4000652C)
#define UART1_CTL       *((volatile unsigned long *)0x4000D030)
#define UART1_IBRD      *((volatile unsigned long *)0x4000D024)
#define UART1_FBRD      *((volatile unsigned long *)0x4000D028)
#define UART1_CC        *((volatile unsigned long *)0x4000DFC8)
#define UART1_LCRH      *((volatile unsigned long *)0x4000D02C)
#define UART1_TIM       *((volatile unsigned long *)0x4000D038)
#define UART1_DR        *((volatile unsigned long *)0x4000D000)
#define UART1_FR        *((volatile unsigned long *)0x4000D018)
#define UART1_ICR       *((volatile unsigned long *)0x4000D044)
#define GPIOC_DEN       *((volatile unsigned long *)0x4000651C)

#define GPIOA_AFSEL     *((volatile unsigned long *)0x40004420)
#define GPIOA_PCTL      *((volatile unsigned long *)0x4000452C)
#define GPIOA_DEN       *((volatile unsigned long *)0x4000451C)
#define UART0_CTL       *((volatile unsigned long *)0x4000C030)
#define UART0_IBRD      *((volatile unsigned long *)0x4000C024)
#define UART0_FBRD      *((volatile unsigned long *)0x4000C028)
#define UART0_CC        *((volatile unsigned long *)0x4000CFC8)
#define UART0_LCRH      *((volatile unsigned long *)0x4000C02C)
#define UART0_IM       *((volatile unsigned long *)0x4000C038)
#define UART0_DR        *((volatile unsigned long *)0x4000C000)
#define UART0_FR        *((volatile unsigned long *)0x4000C018)
#define UART0_ICR       *((volatile unsigned long *)0x4000C044)
#define UART0_MIS       *((volatile unsigned long *)0x4000C040)
#define UART0_IFLS      *((volatile unsigned long *)0x4000C034)



#endif
