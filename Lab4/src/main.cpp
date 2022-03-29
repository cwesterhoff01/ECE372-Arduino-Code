#include <Arduino.h>
#include "adc.h"
#include "pwm.h"
#include "timer.h"
#include "switch.h"
#include "sevensegment.h"

typedef enum {
  WAIT_PRESS,
  DEBOUNCE_PRESS,
  WAIT_RELEASE,
  DEBOUNCE_RELEASE
} stateType;

volatile stateType currentState = WAIT_PRESS;

int killMotor = 0;

int main(){
  initADC();
  initSwitchD0();
  initPWMTimer3();
  initPWMTimer4();
  initTimer0();
  initTimer1();
  initPortC();

  sei();
  while(1){
    if(killMotor == 0){
      changeDutyCycle(returnVoltage());
    }
    else{
      //Turn motor off
      changeDutyCycle(512);
      //Countdown
	  start10();
	  killMotor = 0;
      //Once countdown is finish change back killMotor to zero
    }
    switch(currentState){
      case WAIT_PRESS: //Waiting for user to press the switch
      break;
    case DEBOUNCE_PRESS: //Debouncing the signal when user pressed the switch
      delayMs(1);
      currentState = WAIT_RELEASE;
        // showing use of serial print to the serial monitor for debugging only
    // set baud rate for the serial port print function
    Serial.begin(9600);

    // Use Arduino library to print to serial port
    Serial.println ("Hello World I am here");
    Serial.println ("I am still here");
    // flush out buffer so that entire string will print
    Serial.flush();
      break;
    case WAIT_RELEASE: //Waiting for user to release the switch
      break;
    case DEBOUNCE_RELEASE: //Debouncing the signal when user let go of the switch
      delayMs(1);
      currentState = WAIT_PRESS;
      break;
    }
    
  }


return 0;
  
}

//ISR
ISR(INT0_vect){
  if(currentState == WAIT_PRESS){
    currentState = DEBOUNCE_PRESS;
  }
  else if(currentState == WAIT_RELEASE){
    //do stuff
    killMotor = 1;
    currentState = DEBOUNCE_RELEASE;
  }
}
