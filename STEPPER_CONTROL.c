#include "TM4C123GH6PM.h" 

void Stepper_Control(int step_no) {
    // Ensure step_no is valid (1 to 4)
    if (step_no < 1 || step_no > 4) return;

    // Clear current outputs (PB0-PB3) without affecting other pins
    GPIOB->DATA &= ~0x0F; // Clear PB0-PB3
    
    // Set outputs based on the step number
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
        default:
					break; 
    }
}
