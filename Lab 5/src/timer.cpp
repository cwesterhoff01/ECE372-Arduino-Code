#include "timer.h"

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    //Setting timer to use CTC mode
    TCCR0A &= ~(1 << WGM00);
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){
   //Need to calculate the count for 1ms.
    //Need to keep the count under 255. If above 255, it will overflow.
    //OCR0A = (Td * f)/Ps = (1ms * 16MHz)/64 = 250
    TCCR0B |= (1 << CS01) | (1 << CS00); //Sets the prescaler to 64 and also turns on the timer
    TCCR0B &= ~(1 << CS02);
    OCR0A = 250;

    unsigned int delayCnt = 0; //Counts delay

    while (delayCnt < delay){
        //OCF0A is the flag (for CTC) for when TCNT0 = OCR0A. 
        while (!(TIFR0 & (1 << OCF0A))); //Wait while flag is down. "While flag is down do not do anything" 
        //setting timer to 0. Clearing the timer
        TCNT0 = 0; 
        //Set flag down (logic is 1). TIFR0 is register that has OCF0A
        TIFR0 |= (1 << OCF0A); 
        delayCnt++; //increment delayCnt after flag is up
    }
    TCCR0B &= ~((1 << CS01) | (1 << CS00)); //Turns the clock off by setting to no clock source
}