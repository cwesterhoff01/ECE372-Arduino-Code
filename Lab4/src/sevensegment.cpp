#include <avr/io.h>
#include "sevensegment.h"

void initPortC(){
    //PC0 = A, PC1 = B, PC2 = C, PC3 = D, PC4 = E, PC6 = F, PC7 = G, PC5 = DP
    DDRC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6) | (1 << PORTC7);

}

void selectLED(int num){
    switch (num){
        case 0: 
            //PORTC = 0b11111100;
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC7));
            break;
        case 1: 
            //PORTC = 0b01100000;
            PORTC |= ((1 << PORTC1) | (1 << PORTC2));
            PORTC &= ~((1 << PORTC0) | (1 << PORTC5) | (1 << PORTC7) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6));
            break;
        case 2: 
            //PORTC = 0b11011010;
            PORTC |= ((1 << PORTC0)| (1 << PORTC1) | (1 << PORTC7) | (1 << PORTC4) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC6) | (1 << PORTC2));
            break;
        case 3: 
            //PORTC = 0b11110010;
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC7) | (1 << PORTC2) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC4) | (1 << PORTC6));
            break;
        case 4: 
            //PORTC = 0b01100110;
            PORTC |= ((1 << PORTC7) | (1 << PORTC6) | (1 << PORTC1) | (1 << PORTC2));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC0));
            break;
        case 5: 
            //PORTC = 0b10110110;
            PORTC |= ((1 << PORTC0) | (1 << PORTC6) | (1 << PORTC7) | (1 << PORTC2) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC1) | (1 << PORTC4));
            break;
        case 6: 
            //PORTC = 0b10111110;
            PORTC |= ((1 << PORTC0) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6) | (1 << PORTC7));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC1));
            break;
        case 7: 
            //PORTC = 0b11100000;
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6) | (1 << PORTC7));
            break;
        case 8: 
            //PORTC = 0b11111110;
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC4) | (1 << PORTC6) | (1 << PORTC7));
            PORTC &= ~((1 << PORTC5));
            break;
        case 9: 
            //PORTC = 0b11110110;
            PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) | (1 << PORTC6) | (1 << PORTC7));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC4));
            break;
        default:
            //PORTC = 0b10010010;
            PORTC |= ((1 << PORTC0) | (1 << PORTC7) | (1 << PORTC3));
            PORTC &= ~((1 << PORTC5) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC4) | (1 << PORTC6));
            break;
    }
}


// void initShift(){
//     //Port 8 is the dataPin (14 on shift register)
//     //Port 9 is the latchPin (12 on shift register)
//     //Port 10 is the clockPin (11 on shift register)

//     DDRH |= (1 << PORT5) | (1 << PORT6); //Port 8 and 9
//     DDRB |= (1 << PORT4); //Port 10
// }


// void display(int num){
//     int numBit = numToBits(num);
    
//     //output enable is 0


//     //Output numBit value to DataPin on shift register

//     //delay 1s

//     //output enable is 1
// }

// int numToBits(int num){
//     switch(num){
//         case 0:
//             return 0b11111100;
//             break;
//         case 1:
//             return 0b01100000;
//             break;
//         case 2:
//             return 0b11011010;
//             break;
//         case 3:
//             return 0b11110010;
//             break;
//         case 4:
//             return 0b01100110;
//             break;
//         case 5:
//             return 0b10110110;
//             break;
//         case 6:
//             return 0b10111110;
//             break;
//         case 7:
//             return 0b11100000;
//             break;
//         case 8:
//             return 0b11111110;
//             break;
//         case 9:
//             return 0b11110110;
//             break;
//         default:
//             return 0b10010010;
//             break;
//     }
// }