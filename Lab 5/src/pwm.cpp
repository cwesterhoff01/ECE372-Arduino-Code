#include <avr/io.h>

#include "pwm.h"

void initPWMTimer3()  { //Clockwise (Fast pwm 10-bit)
    //Setting data direction for pin 5
    DDRE |= (1 << DDE3);

    //Setting timer up for fast pwm 10-bit mode
    TCCR3A |= (1 << WGM31) | (1 <<WGM30);
    TCCR3B |= (1 << WGM32);
    TCCR3B &= ~(1 << WGM33);

    //Setting up non inverting mode
    TCCR3A |= (1 << COM3A1);
    TCCR3A &= ~(1 << COM3A0);

    //Setting prescalar to 1
    TCCR3B |= (1 << CS30);
    TCCR3B &= ~((1 << CS31) | (1 << CS32));
    
    //Setting duty cycle
    OCR3A = 0; //0% duty cycle [Temporary Value]

}

void initPWMTimer4(){ //Counter Clockwise (Inverting Fast Pwm 10-bit)
    //setting data direction for pin 6
    DDRH |= (1 << DDH3);
    
    TCCR4A |= (1 << WGM41) | (1 <<WGM40);
    TCCR4B |= (1 << WGM42);
    TCCR4B &= ~(1 << WGM43);

    //Setting up non inverting mode
    TCCR4A |= (1 << COM4A1) | (1 << COM4A0);

    //Setting prescalar to 1
    TCCR4B |= (1 << CS40);
    TCCR4B &= ~((1 << CS41) | (1 << CS42));
    
    //Setting duty cycle
    OCR4A = 1023; //0% duty cycle [Temporary Value]
}

void changeDutyCycle(int digitalValue){
    if(digitalValue < 0b1000000000){
        //clockwise
        OCR3A = 1023 - (2 * digitalValue); //To slow down the clockwise speed, we want to go from 1023 to 0
        OCR4A = 1023; //OCR4A is the counter clockwise. We want it to be "0"
    }
    else if(digitalValue > 0b1000000000){
        //counterclockwise
        OCR3A = 0; 
        OCR4A = 1023 - (2 * (digitalValue - 512)); // Subtract 512 since the digitalValue at this point is 512
    }
    else{
        //Zero
        OCR3A = 0;
        OCR4A = 1023;
    }
    
}
