#include "timer.h"
//You many use any timer you wish for the microsecond delay and the millisecond delay


/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
	//select CTC mode
    TCCR1A &= ~(1 << WGM10);
    TCCR1A |= (1 << WGM11);
    TCCR1B &= ~(1 << WGM12);
    TCCR1B &= ~(1 << WGM13);
}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
    // To make 1 microsecond delay
    // we use the formula OCR1A = [Td * fclk]/ PS
    // using a PS = 8, Td = 1us fclk = 16MHz.
    // OCR1A = 2

    //set prescalar
    TCCR1B &= ~((1 << CS12) | (1 << CS10));
    TCCR1B |= (1 << CS11);
    //set OCR1A = 2
    OCR1AH = 0;
    OCR1AL = 2;

    //create delay counter
    unsigned int count = 0;
    //set counter to 0
    TIFR1 |= (1 << OCF1A);
    TCNT1 = 0;

    while(count < delay) {
        if(TIFR1 & (1 << OCF1A)) { //check to see if one microsec has passed
            count++; //increment each time a microsec has passed
            TIFR1 |= (1 << OCF1A); //reset the flag
        }
    }
}

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    //select CTC mode
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
    //set prescalar value
    TCCR0B |= (1 << CS12);
    TCCR0B &= ~((1 << CS11) | (1 << CS10));
    OCR0A = 62;
    
    unsigned int delayNum = 0;

    TCNT0 = 0;
    TIFR0 |= (1 << OCF0A); //set compare flag to start the timer 

    while(delayNum < delay) {
        if(TIFR0 & (1 << OCF0A)) { //check to see if one millsec has passed
            delayNum++; //increment each time a millsec has passed
            TIFR0 |= (1 << OCF0A); //reset the flag
        }
    }
}