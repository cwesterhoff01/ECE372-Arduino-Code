#include "I2C.h"
#include <avr/io.h>

# define wait_for_completion while(!(TWCR & (1 << TWINT)));

void initI2C(){
    PRR0 &= ~(1 << PRTWI); //Wake up I2C module on AT2560 
    TWSR |= (1 << TWPS0); // prescaler = 1
    TWSR &= ~(1 << TWPS1); // prescaler = 1
    //TWBR = ((CPU Clock frequency)/(SCLfrequency) - 16)/(2*(4)^TWPS)
    TWBR = 0xC6; // bit rate generator = 10k (TWBR = 198)
    TWCR = (1 << TWEN); // enable two wire interface
}
void startI2C_Trans(unsigned char SLA){

}
void stopI2C_Trans(){

}
void read_from(unsigned char SLA, unsigned char MEMADDRESS){

}
unsigned char read_data(){

}