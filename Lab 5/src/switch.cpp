// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

 void initSwitchPB3(){ //Pin # 50
    // set direction for input. Pin #50
    DDRB &= ~(1 << DDB3);

    // enable the pullup resistor for stable input
    PORTB |= (1 << PORTB3);

    //Enables PCINT 7:0 where PCINT for PB3 is PCINT3. 
    PCICR |= (1 << PCIE0);
    //Enables timer0 interrupt mask register bit PCINT3 for PB3 based on the ATMega2560 schematic
    PCMSK0 |= (1 << PCINT3);
}

