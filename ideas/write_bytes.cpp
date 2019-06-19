/**

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>

using namespace std;

int main() 
{

uint32_t tmp = 0x11223344;
cout << "Value is: " << hex << tmp << endl;

// we have some mask
uint32_t mask;
cin >> mask;
cout << "Mask is: " << hex << mask << endl;

uint8_t b3 = (uint8_t)(tmp>>24); 
uint8_t b2 = (uint8_t)(tmp>>16); 
uint8_t b1 = (uint8_t)(tmp>>8); 
uint8_t b0 = (uint8_t)(tmp>>0);

cout << "Value of b0 is: " << dec << b0 << endl;
cout << "Value of b1 is: " << dec << b1 << endl;
cout << "Value of b2 is: " << dec << b2 << endl;
cout << "Value of b3 is: " << dec << b3 << endl;


cout << "--------------------" << endl;

uint32_t tmpInt = 11223344;

unsigned char byte0,byte1,byte2,byte3;
byte0 = static_cast<unsigned char>(tmpInt & 0x000000FF); 
byte1 = static_cast<unsigned char>((tmpInt & 0x0000FF00) >> 8); 
byte2 = static_cast<unsigned char>((tmpInt & 0x00FF0000) >> 16); 
byte3 = static_cast<unsigned char>((tmpInt & 0xFF000000) >> 24);

cout << "Value of b0 is: " << hex << byte0 << endl;
cout << "Value of b1 is: " << hex << byte1 << endl;
cout << "Value of b2 is: " << hex << byte2 << endl;
cout << "Value of b3 is: " << hex << byte3 << endl;

**/

#include <iostream>
#include <iomanip>
#include <cstdint>


int main()
{

    
    uint32_t input = 0x392F1234;
    
    uint32_t a = input & 0xFF;
    uint32_t b = (input >> 8) & 0xFF;
    uint32_t c = (input >> 16) & 0xFF;
    uint32_t d = (input >> 24) & 0xFF;
    
    std::cout << std::hex << a  << '\n' << b << '\n' << c << '\n' << d << '\n';
}
