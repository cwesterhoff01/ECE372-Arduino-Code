#include "adc.h"
#include <avr/io.h>

void initADC(){

    //Set reference voltage set to AVCC = 5V output
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

    //Set to right justified
    ADMUX &= ~(1 << ADLAR);

    //Set ADC0 as single-ended input with Mux[5:0] = 0b'000000
    ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));
    ADCSRB &= ~(1 << MUX5);

    //Set auto trigger source selection
    //Use free-running mode ADTS[2:0] = 0b'000
    //Starting a new conversion each time the last one is finished. Do not need to retrigger the ADC
    ADCSRB &= ~((1<< ADTS2) | (1 << ADTS1) | (1 << ADTS0));

    //Enable ADC and enable auto-triggering
    ADCSRA |= (1 << ADEN) | (1 << ADATE);

    //Set prescalar to max 128
    //ADC clock frequency is 16MHz with prescaler --> 125KHz
    //Sampling rate is 1/((1/125K Hz) * (13 clock cycles)) = 9615 KHz
    //Takes 13 ADC clock cycles for conversion
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    //Disable ADC0 pin digital input - A0. To prevent bad readings
    DIDR0 |= (1 << ADC0D);

    //Start first ADC conversion. Starts first sample
    ADCSRA |= (1 << ADSC);

}

int returnVoltage(){
    int result = 0;

    //Combines the ADCL and ADCH to an integer result.
    result = ADCL;
    result += ((unsigned int) ADCH)<< 8;

    //Returns result. This will be used for determining the duty cycle
    return result;
}
