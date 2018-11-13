//lab#4

#include <stdint.h>
#include "headerlab.h"

void initialize_GPIO();
void initialize_TIMER(int load);
void initialize_ADC();
void indication(double temp);
void initialize_PLL(int clk);
void delay();

int main()
{
  initialize_ADC(); // initialize the ADC
  initialize_GPIO(); // initialize the GPIOs
  // we set 4MHz as the default system clock in this lab
  initialize_TIMER(0x3d0900); // initialize the default TIMER
  initialize_PLL(99); // initialize the default PLL
  while(1){}
}

// this function describe the beheavior as any switch is pressed
// sw1 is pressd: system clock is 4MHz and timer load is 4M
// sw2 is pressd: system clock is 80MHz and timer load is 80M
void Handler_PF()
{
  GPIOF_ICR |= 0x11;
  int sw1 = !(GPIOF_DATA & 0x10);
  int sw2 = !(GPIOF_DATA & 0x01);
  int clk;
  int load;
  if(sw1) { //4 80MHz
    clk = 4;
    load = 0x4c4b400;
  } else { //99 4MHz
    clk = 99;
    load = 0x3d0900;
  }
   initialize_TIMER(load);
   initialize_PLL(clk);
}

// pass in integer clk as parameter
// this funciton initialize the phase lock loop
// help to change the frequency of system clock
void initialize_PLL(int clk) {
  RCC = (RCC &~(0x7C << 4)) + (0x54 << 4); // clear XTAL field and configure 16MHz crystal
  RCC2 |= (1U << 31); // RCC2 override the RCC
  RCC2 |= (1 << 11); // set bypass2 while initializing
  RCC2 &= ~(0x7 << 4); // use the main oscillator
  RCC2 |= (0x4 << 28); // use 400MHz PLL
  RCC2 &= ~(0x02 << 12); // activate PLL
  RCC2 = (RCC2 &~(0x1FC << 20)) + (clk << 22); //to reset the system clock frequency
  while(RIS & (4 << 4) == 0){} // wait for PLLRIS bit
  RCC2 &= ~(8 << 8); // clear bypass2 to use PLL
}

// this function describe beheavior when a new conversion is finished
// calculate temperaure in degree Celsius
// determine the LED's color
// clear the interrupt flag
void ADC0_Handler(void)
{
  double temp = 147.5 - ((247.5 * (double)ADC0_FIFO3) / 4096.0);
  indication(temp);
  ADC0_ISC = (1 << 3);
}

// pass in a double temp as parameter
// This function determine LED's color based on temperature it read
void indication(double temp) {
  if(temp >= 0 && temp <= 17) {
    GPIOF_DATA = RED;
  } else if (temp > 17 && temp <= 19) {
    GPIOF_DATA = BLUE;
  } else if (temp > 19 && temp <= 21) {
    GPIOF_DATA = RED + BLUE;
  } else if (temp > 21 && temp <= 23) {
    GPIOF_DATA = GREEN;
  } else if (temp > 23 && temp <= 25) {
    GPIOF_DATA = GREEN + RED;
  } else if (temp > 25 && temp <= 27) {
    GPIOF_DATA = GREEN + BLUE;
  } else if (temp > 27 && temp <= 40) {
    GPIOF_DATA = GREEN + BLUE + RED;
  }
}

// this function initializes the GPIOs
void initialize_GPIO()
{
  // Port F initialization
  RCGCGPIO = 0x20; //enable port F GPIO
  GPIOF_LOCK = 0x4C4F434B; // unlock the specical pin of Port F
  GPIOF_CR = 0xFF; // use the GPIOCR
  GPIOF_PUR = 0x11; // set the pull up resistor
  GPIOF_DIR = 0x0E; // set port pf0 and pf4 as the input, and pf1-3 as the output
  GPIOF_DEN = 0x1F; // enable digital F GPIO
  GPIOF_IM |= (1 << 0) | (1 << 4); // enable interrupt mask for pf0 and pf4
  GPIOF_IBE &= ~0x11; // use single edge sensitive
  GPIOF_IEV = ~0x11; // set the falling edge as the trigger
  GPIOF_IS = ~0x11; // set the pins to be edge sensitive
  NVIC_EN0 |= (1 << 30); // enable interrupt 30 for port F
  GPIOF_DATA = 0x00; // clear all port F
  GPIOF_ICR |= 0x11; // clear the GPIO interrupt
  // Port E initialization
  RCGCGPIO |= 0x10; // enable the prot E GPIO
  GPIOE_AFSEL |= (1 << 3); // tell PE3 is controlled by peripheral
  GPIOE_DEN &= ~(1 << 3); // clear the PE3's digital function
  GPIOE_AMSEL |= (1 << 3); // enable the analog function for PE3
}

// this function initializes the timer
void initialize_TIMER(int load)
{
  RCGCTIMER = 0x01; // enable the timer 0
  GPTMCTL_0 = 0; // deactivate timer
  GPTMCFG_0 = 0x0; // enable the timer 0
  GPTMTAMR |= 0x02; // enable A timer with periodic mode
  GPTMTAMR |= 0x00; // set the direction of the timer to be count down
  GPTMTAILR_0 = load; // set the start value
  GPTMIMR_0 |= (1 << 0); // enable interrupt for timer0A
  NVIC_EN0 |= (1 << 19); // enable interrupt 19 for timer0A
  GPTMICR_0 |= (1 << 0); // clear the timer0A interrupt
  GPTMCTL_0 |= (1 << 5); // enable output TimerA ADC trigger
  GPTMCTL_0 |= (1 << 0); // activate timer
}

// This function initialize the ADC
void initialize_ADC()
{
  RCGCADC |= 0x01; // enable and provide a clock to ADC module in RUN mode
  delay(); // small delay to make sure ADC finish the initialization
  ADC0_ACTSS = ~(1 << 3); // disable the sample sequencer
  ADC0_EMUX |= (0x5 << 12); // use timer for ADC0
  ADC0_SSMUX_3 = 0; // choose AIN0(PE3) as our analog input
  ADC0_SSCTL_3 |= (1 << 1); // set the END bit to avoid unpredictable beheavior
  ADC0_SSCTL_3 |= (1 << 2); // set IE to use interrupt
  ADC0_SSCTL_3 |= (1 << 3); // set TS to use the interenal temperature sensor
  ADC0_IM |= (1 << 3); // set the interrupt mask for the PE3
  NVIC_EN0 |= (1 << 17); // enable the interrupt of sequencer 3
  ADC0_ACTSS = (1 << 3); // enable sample sequencer
}

// this funciton provide a small amount of delay
void delay() {
  int clk = 200000;
  while(clk) {
    clk--;
  }
}
