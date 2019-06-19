/* ****************************************************************
   MIPS32 Instruction Set Simulator
   Computer Architecture, Semester 1, 2016

   Class members for cache

**************************************************************** */

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "cache.h"

using namespace std;

// Constructors

cache::cache(string name,
	     memory_accessible* backing_store,
	     unsigned long int block_size,
	     unsigned long int size,
	     unsigned long int associativity,
	     write_strategy_t write_strategy,
	     bool verbose) {
  // TODO: ...
}

// Read a word of data from an address
uint32_t cache::read_word (uint32_t address) {
  // TODO: ...
	uint32_t temp = 0;
	return temp;
}

// Write a word of data to an address, mask contains 1s for bytes to be updated
void cache::write_word (uint32_t address, uint32_t data, uint32_t mask) {
  // TODO: ...
}

// Read a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void cache::read_block (uint32_t address, uint32_t data[], unsigned int data_size) {
  // TODO: ...
}

// Write a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void cache::write_block (uint32_t address, uint32_t data[], int unsigned data_size) {
  // TODO: ...
}

// Display on cout whether the address is present, and if so, display the data
void cache::probe_address (uint32_t address) {
  // TODO: ...
}

// Report access stats
void cache::report_accesses () {
  // TODO: ...
}

