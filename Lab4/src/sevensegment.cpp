#include <avr/io.h>
#include "sevensegment.h"
#include "timer.h"

void initPortC(){
    //PC0 = A, PC1 = B, PC2 = C, PC3 = D, PC4 = E, PC6 = F, PC7 = G, PC5 = DP
    DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6) | (1 << PORTC7);

}

//Selects specific LED on seven segment
void selectLED(int num){
    //Turns on specific LEDs depending on which number it is turning on
    switch (num){
        case 0: 
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC7));
            break;
        case 1: 
            PORTC |= ((1 << PORTC1) | (1 << PORTC2));
            PORTC &= ~((1 << PORTC0) | (1 << PORTC5) | (1 << PORTC7) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6));
            break;
        case 2: 
            PORTC |= ((1 << PORTC0)| (1 << PORTC1) | (1 << PORTC7) | (1 << PORTC4) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC6) | (1 << PORTC2));
            break;
        case 3: 
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC7) | (1 << PORTC2) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC4) | (1 << PORTC6));
            break;
        case 4: 
            PORTC |= ((1 << PORTC7) | (1 << PORTC6) | (1 << PORTC1) | (1 << PORTC2));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC0));
            break;
        case 5: 
            PORTC |= ((1 << PORTC0) | (1 << PORTC6) | (1 << PORTC7) | (1 << PORTC2) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC1) | (1 << PORTC4));
            break;
        case 6: 
            PORTC |= ((1 << PORTC0) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6) | (1 << PORTC7));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC1));
            break;
        case 7: 
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6) | (1 << PORTC7));
            break;
        case 8: 
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6) | (1 << PORTC7));
            PORTC &= ~((1 << PORTC5));
            break;
        case 9: 
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC6) | (1 << PORTC7));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC4));
            break;
        default:
            PORTC |= ((1 << PORTC0) | (1 << PORTC7) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC4) | (1 << PORTC6));
            break;
    }
}

//Start 10 second timer
void start10(){
    for(int i = 9; i >= -1; i--){
        selectLED(i);
        delayMs(1000);
    } 
}

