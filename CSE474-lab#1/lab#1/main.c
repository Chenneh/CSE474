//Lab#1
#include <stdint.h>
#include "headerlab#1.h"


//part#1

void delay();

int main()
{
  RCGCGPIO = 0x20; //enable port F GPIO
  GPIOF_DIR = 0x0E; // set port F as the output
  GPIOF_DEN = 0x0E; // enable digital F GPIO
  GPIOF_DATA = 0x00; // clear all port F
  
  // flash the LED in an order of red, blue, and green continuously
  while(1){
      GPIOF_DATA = 0x02; // red on
      delay();
      GPIOF_DATA = 0x00; // red off
      delay();
      GPIOF_DATA = 0x04; // blue on
      delay();
      GPIOF_DATA = 0x00; // blue off
      delay();
      GPIOF_DATA = 0x08; // green on 
      delay();
      GPIOF_DATA = 0x00; // green off
      delay(); 
  }
}

// this function creates a delay to make flahes of LED observable for human
void delay() {
  int clk = 0;
  while(clk < 200000) {
    clk++;
  }
}



//part#2
/*
int main() 
{
  RCGCGPIO = 0x20; //enable port F GPIO
  GPIOF_LOCK = 0x4C4F434B; // unlock the specical pin of Port F
  GPIOF_CR = 0xFF; // use the GPIOCR
  GPIOF_PUR = 0x11; // set the pull up resistor
  GPIOF_DIR = 0x0E; // set port pf0 and pf4 as the input, and pf1-3 as the output
  GPIOF_DEN = 0x1F; // enable digital F GPIO
  GPIOF_DATA = 0; // clear all port F
  
  // read the input and determine which LED to turn on
  while(1) {
    int sw1 = !(GPIOF_DATA & 0x10); // read pin4
    int sw2 = !(GPIOF_DATA & 0x01); // read pin0
    if(sw1) {
      GPIOF_DATA = 0x02;
    } else if(sw2) {
      GPIOF_DATA = 0x08;
    } else {
      GPIOF_DATA = 0;
    }
  }
}
*/