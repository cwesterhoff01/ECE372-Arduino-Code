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
    TCCR3B |= (1 << CS30) | (1 << CS31);
    TCCR3B &= ~((1 << CS32));
    
    //Setting duty cycle
    OCR3A = 0; //0% duty cycle [Temporary Value]

}

void changeDutyCycle(int noise){
    //noise = noise % 1020;
    OCR3A = noise;
}
