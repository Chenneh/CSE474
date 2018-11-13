//Lab#2

#include <stdint.h>
#include "headerlab.h"

void initialize_GPIO();
void initialize_TIMER();
void alter();

int main()
{
  initialize_GPIO(); // initialize the GPIOs properly
  initialize_TIMER(); // initialize the TIMER
  alter(); // change the light every 1 sec
}

// this function makes the LEDs flash
void alter() 
{
  int led = RED;
  while(1){
    if(GPTMRIS_0 & 0x01) {
      GPTMICR_0 = 0x01;
      GPIOF_DATA = led;
      led = led << 1;
      if(led > GREEN) {
        led = RED;
      }
    }
  }
}

/* the draft
int main()
{
  initialize_GPIO(); // initialize the GPIOs properly
  initialize_TIMER(); // initialize the TIMER
  while(1) {
    alter(RED);
    alter(BLUE);
    alter(GREEN);
  }
}

void alter(int led) 
{
  while(1){
    if(GPTMRIS_0 & 0x01) {
      GPTMICR_0 = 0x01;
      GPIOF_DATA = led;
    }
  }
}
*/

// this function initializes the timer
void initialize_TIMER()
{
  RCGCTIMER = 0x01; // enable the timer 0
  GPTMCTL_0 = 0; // deactivate timer
  GPTMCFG_0 = 0x0; // enable the timer 0
  GPTMTAMR = 0x02; // enable A timer with periodic mode
  GPTMTAMR |= 0x00; // set the direction of the timer to be count down
  GPTMTAILR_0 = 0xF42400; // set the start value for the counting down timer to be 16000000
  GPTMCTL_0 = 0x01; // activate timer
}

// this function initializes the GPIOs
void initialize_GPIO() 
{
  RCGCGPIO = 0x20; //enable port F GPIO
  GPIOF_DIR = 0x0E; // set port F as the output
  GPIOF_DEN = 0x0E; // enable digital F GPIO
  GPIOF_DATA = 0x00; // clear all port F
}
