/**
How to manually load in instructions

m INST_ADDRESS = 32BIT_INSTRUCTION
PC = INST_ADDRESS
.


So given a 32 bit instruction we have to:

DETERMINE WHAT TYPE OF INSTRUCTION IT IS:
MIPS have 2 types
	R and I (I think)
**/


// need to access the individual bits of the instruction

// try

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <string>

using namespace std;

int main() {

string instMnemonic;

bool m_verbose = true;

uint32_t inst = 0x1234abcd;

uint32_t opMask = 		0xfc000000;
uint32_t rsMask = 		0x03e00000;
uint32_t rtMask = 		0x001f0000;
uint32_t rdMask = 		0x0000f800;
uint32_t shamtMask = 		0x000007c0;
uint32_t functMask = 		0x0000003f;
uint32_t immediateMask = 	0x0000FFFF;
uint32_t addressMask =  	0x03FFFFFF;	

uint32_t opcode = (inst & opMask) >> 26;
uint32_t rs = (inst & rsMask) >> 21;
uint32_t rt = (inst & rtMask) >> 16;
uint32_t rd = (inst & rdMask) >> 11;
uint32_t shamt = (inst & shamtMask >> 6;
uint32_t funct = (inst & functMask);
uint32_t immediate = (inst & immediateMask);
uint32_t address = (inst & addressMask);

// check opcode?
char instType;

if (m_verbose)
{
	cout << "DEBUG: Value in opcode is: " << opcode << endl;
	cout << "DEBUG: Value in opcode in HEX is: " << setfill('0') << setw(8) << hex << opcode << endl;
}

if (opcode == 0x00) {
	if (m_verbose) 
		cout << "DEBUG: R Type Instruction" << endl;
	instType = 'R';
}

else if (opcode == 0x02 || opcode == 0x03)
{
	if (m_verbose)
		cout << "DEBUG: J Type Instruction" << endl;
	instType = 'J';
	if (opcode == 0x02)
		instMnemonic = "j";
	else 
		instMnemonic = "jal"
}

else {
	if (m_verbose)
		cout << "DEBUG: I Type Instruction" << endl;
	instType = 'I';
}

if (instType == 'R')
{
	// we have all the fields already, now we know its R instruction
	// check funct to determine which type
	switch funct 
	{
		case 0x20:
			instMnemonic = "add";
			break;
		case 0x21: 
			instMnemonic = "addu";
			break;
		case 0x24:
			instMnemonic = "and";
			break;
		case 0x09:
			instMnemonic = "jalr";
			break;
		case 0x08:
			instMnemonic = "jr";
			break;
		case 0x27:
			instMnemonic = "nor";
			break;
		case 0x25:
			instMnemonic = "or";
			break;
		case 0x00:
			instMnemonic = "sll";
			break;
		case 0x2a:
			instMnemonic = "slt";
			break;
		case 0x2b:
			instMnemonic = "sltu";
			break;
		case 0x03:
			instMnemonic = "sra";
			break;
		case 0x02:
			instMnemonic = "srl";
			break;
		case 0x22:
			instMnemonic = "sub";
			break;
		case 0x23:
			instMnemonic = "subu";
			break;
		case 0x26:
			instMnemonic = "xor";
			break;
		default:
			cout << "Fatal Error." << endl;
			if (m_verbose)
				cout << "DEBUG: Error determing R instruction mnemonic from funct field." << endl;
			break;
	}
}

	





return 0; 
}

