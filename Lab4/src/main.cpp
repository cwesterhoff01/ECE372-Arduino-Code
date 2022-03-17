#include <Arduino.h>
#include "adc.h"
#include "pwm.h"


int main(){
  initADC();
  initPWMTimer3();
  initPWMTimer4();


  while(1){
    changeDutyCycle(returnVoltage());
  }


return 0;
  
}
