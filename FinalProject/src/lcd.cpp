// Author: 
// Net ID: 
// Date: 
// Assignment: Lab 3
//----------------------------------------------------------------------//
#include "lcd.h"
#include "timer.h"
#include <util/delay.h>

//Initializes all pins related to the LCD to be outputs
void initLCDPins(){
  //Port b4 -enable
  //Port b6 - rs
  DDRB |= (1 << DDB4) | (1 << DDB6);
  //port a0-a3 - data pins
  DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);

}

void fourBitCommandWithDelay(unsigned char data, unsigned int delay){
  //Masking in the data bits
  PORTA = (PORTA & 0xF0) | (data & 0x0F);
  PORTB &= ~(1 << PORTB6); //set RS to low
  PORTB |= (1 << PORTB4); //turn on enable
  delayUs(1); //delay for enable signal
  PORTB &= ~(1 << PORTB4); //turn off enable pin
  delayUs(delay); //delay time for commandd to run

}



void eightBitCommandWithDelay(unsigned char command, unsigned int delay){
  //set data bits to hi
  PORTA = (PORTA & 0xF0) | ((command >> 4) & 0x0F);
  PORTB &= ~(1 << PORTB6); //set RS to low
  PORTB |= (1 << PORTB4); //turn on enable
  delayUs(1);
  PORTB &= ~(1 << PORTB4); //turn off enable
  //set data bits to lo
  PORTA = (PORTA & 0xF0) | (command & 0x0F);
  PORTB |= (1 << PORTB4); //turn on enable
  delayUs(1);
  PORTB &= ~(1 << PORTB4); //turn off enable
  delayUs(delay);
 
}

void writeCharacter(unsigned char character){
  //set top bits with masking
  PORTA = (PORTA & 0xF0) | ((character >> 4) & 0x0F);
  PORTB |= (1 << PORTB6); //set RS to high
  PORTB |= (1 << PORTB4); //turn on enable
  delayUs(1);
  PORTB &= ~(1 << PORTB4); //turn off enable
  //set low bits with masking
  PORTA = (PORTA & 0xF0) | (character & 0x0F);
  PORTB |= (1 << PORTB4); //turn on enable
  delayUs(1);
  PORTB &= ~(1 << PORTB4); //turn off enable
  delayUs(46);
}


void writeString(const char *str){
  //Loops throug string until reached '\0' and prints each charactter on the screen
  while(*str != '\0'){
    writeCharacter(*str);
    str++;
  }
}



//This moves the LCD cursor to a specific place on the screen.
void moveCursor(unsigned char x, unsigned char y){
	eightBitCommandWithDelay(( (0x80) | (x << 6) | y ), 46);
}


/* This is the procedure outline on the LCD datasheet page 4 out of 9.
 * This should be the last function you write as it largely depends on all other
 * functions working.
 */
void initLCDProcedure(){
  // Delay 15 milliseconds
  delayMs(15);
  // Write 0b0011 to DB[7:4] and delay 4100 microseconds
  fourBitCommandWithDelay(0x03, 4100);
  // Write 0b0011 to DB[7:4] and delay 100 microseconds
  fourBitCommandWithDelay(0x03, 100);
  // The data sheet does not make this clear, but at this point you are issuing
  // commands in two sets of four bits. You must delay after each command
  // (which is the second set of four bits) an amount specified on page 3 of
  // the data sheet.
  // write 0b0011 to DB[7:4] and 100us delay
  fourBitCommandWithDelay(0x03, 100);
  // write 0b0010 to DB[7:4] and 100us delay.
  fourBitCommandWithDelay(0x02, 100);
  // Function set in the command table with 53us delay
  eightBitCommandWithDelay(0x28, 53);
  // Display off in the command table with 53us delay
  eightBitCommandWithDelay(0x08, 53);
  // Clear display in the command table. Remember the delay is longer!!!
  eightBitCommandWithDelay(0x01, 3000);
  // Entry Mode Set in the command table.
  eightBitCommandWithDelay(0x06, 53);
  // Display ON/OFF Control in the command table. (Yes, this is not specified),
  // in the data sheet, but you have to do it to get this to work. Yay datasheets!)
  eightBitCommandWithDelay(0x0C, 100);
}



/* Initializes Tri-state for LCD pins and calls initialization procedure.
* This function is made so that it's possible to test initLCDPins separately
* from initLCDProcedure which will likely be necessary.
*/
void initLCD(){
  initLCDPins();
  initLCDProcedure();
}