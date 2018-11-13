//Lab#3

#include <stdint.h>
#include "headerlab.h"

void initialize_GPIO();
void initialize_TIMER();

volatile int led = RED;

// this functoin decribes the action when timer interrupt is triggered
void Timer_Handler_0A(void) 
{
  GPTMICR_0 |= (1 << 0);
  if(led & GREEN) {
    led = RED + 0x11;
  } else {
    led = ((led - 0x11)  << 1) + 0x11;
  }
  GPIOF_DATA = led;
}

// this function describle action when GPIO interrupt is triggered.
void Handler_PF(void){
  GPIOF_ICR |= 0x11;
  if(!(GPIOF_DATA & 0x10)) {
    GPIOF_DATA = RED;
    GPTMCTL_0 = 0;
  } else if((!(GPIOF_DATA & 0x01))){
    led = RED;
    GPTMCTL_0 = 1;
  } else {
    GPIOF_DATA = 0;
    GPTMCTL_0 = 0;
  }
}

int main()
{
  initialize_GPIO(); // initialize the GPIOs properly
  initialize_TIMER(); // initialize the TIMER
  while(1){}
}

// this function initializes the GPIOs
void initialize_GPIO() 
{
  RCGCGPIO = 0x20; //enable port F GPIO
  GPIOF_LOCK = 0x4C4F434B; // unlock the specical pin of Port F
  GPIOF_CR = 0xFF; // use the GPIOCR
  GPIOF_PUR = 0x11; // set the pull up resistor
  GPIOF_DIR = 0x0E; // set port pf0 and pf4 as the input, and pf1-3 as the output
  GPIOF_DEN = 0x1F; // enable digital F GPIO
  
  GPIOF_IM |= (1 << 0) | (1 << 4); // enable interrupt mask for pf0 and pf4
  GPIOF_IBE |= (1 << 0) | (1 << 4); // allow both the rising and falling edge to trigger interrupt
  GPIOF_IS = ~0x11; // set the pins to be edge sensitive
  NVIC_EN0 |= (1 << 30); // enable interrupt 30 for port F
  GPIOF_ICR |= 0x11; // clear the GPIO interrupt signal
  
  GPIOF_DATA = 0x00; // clear all port F
}


// this function initializes the timer
void initialize_TIMER()
{
  RCGCTIMER = 0x01; // enable the timer 0
  GPTMCTL_0 = 0; // deactivate timer
  GPTMCFG_0 = 0x0; // enable the timer 0
  GPTMTAMR |= 0x02; // enable A timer with periodic mode
  GPTMTAMR |= 0x00; // set the direction of the timer to be count down
  GPTMTAILR_0 = 0xF42400; // set the start value for the counting down timer to be 16000000
  
  GPTMIMR_0 |= (1 << 0); // set the interrput mask for timer0A
  NVIC_EN0 |= (1 << 19); // enable interrupt 19 for timer0A
  GPTMICR_0 |= (1 << 0); // clear the timer0A interrupt signal
  
  GPTMCTL_0 = (1 << 0); // activate timer
}


