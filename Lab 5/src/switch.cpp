// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

    // Port D7 is Pin 38
  void initSwitchD7(){
      // set direction for input
  DDRD &= ~(1 << DDD7);

    // enable the pullup resistor for stable input
  PORTD |= (1 << PORTD7);
    //enable the switch for interup

//Table 15-1 Any edge of interrupt
  EICRA |= (1 << ISC00);
  EICRA &= ~(1 << ISC01);
  EIMSK |= (1 << INT0);

}
