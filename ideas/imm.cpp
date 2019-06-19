/**

need to be consistent with how I determine the sign and sign extend

  uint32_t processor::sign_extend(uint32_t 16bits)
  {
	    uint32_t mask = 0x00008000;		// 1 in the sign bit position for 16 bit immediate
    	    if (mask & 16bits)
		if (m_verbose)
			cout << "DEBUG: Sign extending wih 1s" << endl;
		value += 0xFFFF0000;
  }  


THis sign extends a 16 bit integer to a 32 bit one

int16_t s = -890;
int32_t i = s;  //this does the job, doesn't it?

**/

// testing bed for unsigned and signed 16 bit and 32 bit integer types

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <string>

using namespace std;

//cout << setfill('0') << setw(8) << hex <<
//cout << setfill('0') << setw(4) << hex <<

int main () {

uint16_t imm;
imm = 0x0abc;

int16_t imm_3 = imm;
cout << "Value of signed 16 bit form is: " << imm_3 << endl;

cout << "Value of immediate as unsigned 16 bit form is: " << setfill('0') << setw(4) << hex << imm << endl;

// want to sign extend it
int32_t imm_2 = imm_3;
cout << "Value of immediate in signed 32 bit form is: " << setfill('0') << setw(8) << hex << imm_2 << endl;

cout << "---------- Adding unsigned its ---------------" << endl;

uint32_t test = 0x0011abc4;
uint16_t test2 = 0x1234;

cout << dec << test << " + " << test2 << " = " << test + test2 << endl;


return 0;
}


















