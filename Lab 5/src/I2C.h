#ifndef I2C_H
#define I2C_H

void initI2C();
void startI2C_Trans(unsigned char SLA);
void stopI2C_Trans();
void read_from(unsigned char SLA, unsigned char MEMADDRESS);
unsigned char read_data();

#endif
