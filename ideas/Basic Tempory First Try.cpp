#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <string>

#include <cstdint>

using namespace std;

// lets try storing a word (ignoring big endian format at the moment...)
// want to store 1337 in 0x00040008
// vAddr : virtual address we want to store the word to
// val : word we want to store
// rAddrBase : base address 
// the real base address of the memory 
void storeWord(uint32_t* rBaseAddr, uint32_t vAddr, uint32_t val) {	
	uint32_t tmp = vAddr - 0x00040000;
	cout << "The difference from the requested address to the base is: " << tmp << endl;

	*(rBaseAddr+(tmp/4)) = val;
	return;
}

int main() {

void storeWord(uint32_t*, uint32_t, uint32_t);	// prototype

// Buuut we dont know it to point to that, virtually it points to a different address!
// define some reference addresses perhaps?
uint32_t memoryBase = 0x00040000;

uint32_t *realAddress;
realAddress = new uint32_t[1024]();

for (int i = 0; i <=20; i++) {
	*(realAddress+i) = i*100;
}

for (int i = 0; i <= 20; i++) {
	cout << "Value in index: " << i << " is: " << *(realAddress+i) << " @ real mem loc: " << realAddress+i << " @ virtual mem loc " << hex << "0x" << memoryBase+(4*i) << dec << endl;
}


storeWord(realAddress, 0x00040008, 1337);

cout << endl << endl;

for (int i = 0; i <= 20; i++) {
	cout << "Value in index: " << i << " is: " << *(realAddress+i) << " @ real mem loc: " << realAddress+i << " @ virtual mem loc " << hex << "0x" << memoryBase+(4*i) << dec << endl;
}

return 0;
}

