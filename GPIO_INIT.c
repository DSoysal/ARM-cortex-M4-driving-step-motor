#include "TM4C123GH6PM.h" 

void GPIO_Init(void) {
    // enable the clock 
    SYSCTL->RCGCGPIO |= (1 << 0) | (1 << 1);  
    while (!(SYSCTL->PRGPIO & ((1 << 0) | (1 << 1))));  // Wait until ports are ready
    
    // configure Port A pins
    GPIOA->DIR &= ~0x03;  
    GPIOA->DEN |= 0x03;    
    GPIOA->PUR |= 0x03;   
    
    // configure Port B pins 
    GPIOB->DIR |= 0x0F;   
    GPIOB->DEN |= 0x0F;   
    GPIOB->DATA &= ~0x0F; 
}
