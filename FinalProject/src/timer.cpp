// Author: 
// Net ID: 
// Date: 
// Assignment: Lab 3
//----------------------------------------------------------------------//

#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


void initTimer1(){
//Setting timer1 to CTC mode
    TCCR1A &= ~(1 << WGM10);
    TCCR1A &= ~(1 << WGM11);
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
}


void delayUs(unsigned int delay){
    //Setting the prescalar to 1
    TCCR1B &= ~((1 << CS12) | (1 << CS11));
    TCCR1B |= (1 << CS10);

    //Setting the compare flag
    //OCR1A = ((1us * 16Mhz)/ 1) = 16 
    //OCR1A = 16;
    OCR1AL = 0x10;
    OCR1AH = 0;

    //set counter to keep tracck of total delay (each time the counter reaches the flag 1 microsecond has passed)
    unsigned int delayCNT1 = 0;

    //Set the counter to 0
    TIFR1 |= (1 << OCF1A);
    TCNT1 = 0;

    //loop until delay time has been reached
    while(delayCNT1 < delay){
        //When timer reached the flag increment delayCNT
        if(TIFR1 & (1 << OCF1A)){
            //Incrementing delayCNT
            delayCNT1++;
            //set timer to start counting again
            TIFR1 |= (1 << OCF1A);
        }
    }

}



void initTimer0(){
    //Settijng the timer to CTC mode
    TCCR0A &= ~( 1 << WGM00);
    TCCR0A |= ( 1 << WGM01);
    TCCR0B &= ~( 1 << WGM02);
}
/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-2000 milliseconds
*/
void delayMs(unsigned int delay){

    //Setting prescalar to 64
    TCCR0B |= (1 << CS12);
    TCCR0B &= ~( (1 << CS11) | (1 << CS10) );

    //Setting the delay 62 is around 1 ms
    OCR0A = 62;

    //set counter to keep track of the total delay time (each time the timer is high is 1ms)
    unsigned int delayCNT = 0; 
    //Set TCNT0 to zero
    TCNT0 = 0; 
    // set the compare flag to start the timer
    TIFR0 |= (1 << OCF0A); 

    while(delayCNT < delay){
        //increment delayCNT only when timer has reached its compare flag 
        if(TIFR0 & (1 << OCF0A)){
            //Increment delayCNT
            delayCNT++;
            //RESTART the timer
            TIFR0 |= (1 << OCF0A);
        }
    }
}
