// lab#5

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "headerlab.h"

void initialize_GPIO_F_E();
void initialize_TIMER(int load);
void initialize_ADC();
void indication(double temp);
void initialize_PLL(int clk);
void intialize_UART(int ibrd, int fbrd);
void prints(char * string);
void printc(char c);
void delay();

int main()
{

  initialize_GPIO(); // initialize the GPIOs
  initialize_ADC(); // initialize the ADC
  // we set 4MHz as the default system clock in this lab
  initialize_TIMER(0x3d0900); // initialize the default TIMER
  initialize_PLL(99); // initialize the default PLL
  intialize_UART(26, 3); // initialize the default UART
  while(1){}
}

// this function describe the beheavior as any switch is pressed
// sw2 is pressd: system clock is 4MHz and timer load is 4M
// sw1 is pressd: system clock is 80MHz and timer load is 80M
/*void Handler_PF(){
  GPIOF_ICR |= 0x11;
  int sw1 = !(GPIOF_DATA & 0x10);
  int sw2 = !(GPIOF_DATA & 0x01);
  int ibrd;
  int fbrd;
  int clk;
  int load;
  if(sw1) { // 80MHz 4 520 54
    clk = 4;
    load = 0x4c4b400;
    ibrd = 520;
    fbrd = 54;
  } else { // 4MHz 99  26 3
    clk = 99;
    load = 0x3d0900;
    ibrd = 26;
    fbrd = 3;
  }
   initialize_TIMER(load);
   initialize_PLL(clk);
   intialize_UART(ibrd, fbrd);
}*/

// This is the interrupt function for unart0
// Describe the behavior when uart interrupt is triggered
// when "H" on keyboard is pressed: system clock is 80MHz and timer load is 80M
// when other key is pressed: system clock is 4MHz and timer load is 4M
void UART0_Handler() {
  int ibrd;
  int fbrd;
  int clk;
  int load;
  char mode = UART0_DR;
  if(mode == 'h') { // 80MHz 4 520 54
    clk = 4;
    load = 0x4c4b400;
    ibrd = 520;
    fbrd = 54;
  } else { // 4MHz 99  26 3
    clk = 99;
    load = 0x3d0900;
    ibrd = 26;
    fbrd = 3;
  }
   initialize_TIMER(load);
   initialize_PLL(clk);
   intialize_UART(ibrd, fbrd);
   UART0_ICR |= (1 << 4); // clear the flag
}

// this function describe beheavior for each second
// start a new conversion and clear the timer interrupt flag
/*void Timer_Handler_0A(void)
{
  ADC0_PSSI |= (1 << 3);
  GPTMICR_0 |= (1 << 0);
  //GPIOF_DATA ^= GREEN; // test sample frequency
}*/

// this function describe beheavior when a new conversion is finished
// calculate temperaure in degree Celsius
// determine the LED's color
// clear the interrupt flag
void ADC0_Handler(void) {
  ADC0_PSSI |= (1 << 3);
  double temp = 147.5 - ((247.5 * (double)ADC0_FIFO3) / 4096.0);
  indication(temp);
  int t = (int) temp;
  char tem[3];
  sprintf(tem, "%d", t);
  prints(tem);
  ADC0_ISC = (1 << 3);
}

// this function print the string passed in bit by bit to putty
void prints(char * string) {
  while(*string) {
    printc(*string);
    string++;
  }
}

// this funciton print on char into putty's console
void printc(char c) {
  while((UART0_FR & (1 << 5))){}
  UART0_DR = c;
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
  RCGCGPIO |= 0x20; //enable port F GPIO
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
  // Port C
  //RCGCGPIO |= (1 << 2); // enalbe port C
  //GPIOC_AFSEL = (1 << 4) | (1 << 5); // enable alternate function PC4(U1RX) and PC5(U1Tx)
  //GPIOC_DEN = (1 << 4) | (1 << 5); // enable the digital function
  //GPIOC_PCTL = (2 << 16) | (2 << 20); // configure PMC2 to tell we are using UART1
  // Port A
  RCGCGPIO |= (1 << 0); // enalbe port A
  GPIOA_AFSEL = (1 << 1) | (1 << 0); // enable alternate function
  GPIOA_PCTL = (1 << 4) | (1 << 0); // configure PMC1 to tell we are using UART0
  GPIOA_DEN = (1 << 1) | (1 << 0); // enable the digital function
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
  //GPTMIMR_0 |= (1 << 0); // enable interrupt for timer0A
  //NVIC_EN0 |= (1 << 19); // enable interrupt 19 for timer0A
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
  RCC2 = (RCC2 &~(0x1FC << 20)) + (clk << 22);
  while(RIS & (4 << 4) == 0){} // wait for PLLRIS bit
  RCC2 &= ~(8 << 8); // clear bypass2 to use PLL
}

void intialize_UART(int ibrd, int fbrd) {
  RCGCUART |= (1 << 0); // enable uart module
  UART0_CTL &= ~(1 << 0); // disable before configuration
  UART0_IBRD = ibrd; // BRD = 4M / (153600) = 26.0416667
  UART0_FBRD = fbrd; // UARTFBRD = integer(0.0416667 * 64 + 0.5) = 3
  UART0_LCRH = (0x3 << 5); // 8 data bits
  UART0_LCRH &= ~(1 << 3); // 1 stop bit
  UART0_CC = 0x0; // use systme clock
  UART0_IM |= (1 << 4); // set the interrupt mask for UART0 for receiver
  NVIC_EN0 |= (1 << 5); // enable the interrupt for UART0
  UART0_MIS |= (1 << 4); // make uart interrupt triggered by passing the FIFO level set
  UART0_IFLS |= (0x2 << 3); // set uart reciever interrupt FIFO level
  UART0_CTL = (1 << 0) | (1 << 8) | (1 << 9); // enable UART and its reciver and transmitter
}

// this funciton provide a small amount of delay
void delay() {
  int clk = 200000;
  while(clk) {
    clk--;
  }
}
