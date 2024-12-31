#include "TM4C123GH6PM.h"

void GPIO_Init(void);
void Stepper_Control(int step_no);
void Delay(int ms);


int step = 1;

int main() {
    GPIO_Init(); 

    while (1) {
        // Check if Button S1 (Clockwise) is released
        if ((GPIOA->DATA & 0x01) == 0) { // PA0 is low (button pressed)
            while ((GPIOA->DATA & 0x01) == 0); // Eait release
            Delay(20); // debounce delay
            //one step clockwise
            Stepper_Control(step);
            step = (step % 4) + 1; // increment step 
        }

        // Check if Button S2 (Counterclockwise) is released
        if ((GPIOA->DATA & 0x02) == 0) { // PA1 is low (button pressed)
            while ((GPIOA->DATA & 0x02) == 0); // wait for release
            Delay(20); // debounce delay
            // one step counterclockwise
            step = (step == 1) ? 4 : (step - 1); // decrement step 
            Stepper_Control(step);
        }
    }
}


void GPIO_Init(void) {
    // enable clock for Ports A and B
    SYSCTL->RCGCGPIO |= (1 << 0) | (1 << 1);
    while (!(SYSCTL->PRGPIO & ((1 << 0) | (1 << 1)))); // for clock stabilization

    // configure PA0 and PA1 
    GPIOA->DIR &= ~0x03;   
    GPIOA->DEN |= 0x03;    
    GPIOA->PUR |= 0x03;    

    // configure PB0-PB3 
    GPIOB->DIR |= 0x0F;    
    GPIOB->DEN |= 0x0F;    
    GPIOB->DATA &= ~0x0F; 
}

// Motor Control
void Stepper_Control(int step_no) {
    // ensure step_no is valid (1 to 4)
    if (step_no < 1 || step_no > 4) return;

    // clear current outputs (PB0-PB3)
    GPIOB->DATA &= ~0x0F;

    switch (step_no) {
        case 1:
            GPIOB->DATA |= 0x01;
            break;
        case 2:
            GPIOB->DATA |= 0x02; 
            break;
        case 3:
            GPIOB->DATA |= 0x04; 
            break;
        case 4:
            GPIOB->DATA |= 0x08; 
            break;
    }
}

// delay 
void Delay(int ms) {
    int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 3180; j++); // approximate 1 ms delay on 16 MHz clock
    }
}
