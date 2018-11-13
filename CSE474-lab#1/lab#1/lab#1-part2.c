// Lab#1-part#2

#include <tm4c123gh6pm.h>
#include <stdint.h>

int main {
  SYSCTL_RCGC2_R = 0x20; //enable port F GPIO
  GPIO_PORTF_DIR_R = 0xE; // set port F as the output
  GPIO_PORTF_DEN_R = 0xE; // enable digital F GPIO
  GPIO_PORTF_DATA_R = 0x00; // clear all port F
  
  
  while(1) {
    int * data = 0x400253FC;
    if(*data = 0x10) {
      *data = 0x12;
    } else if(*data = 0x01) {
      *data = 0x09;
    } else {
      *data = 0;
    }
  }
  
}