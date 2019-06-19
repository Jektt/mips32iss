#ifndef MEMORY_ACCESSIBLE_H
#define MEMORY_ACCESSIBLE_H

/* ****************************************************************
   MIPS32 Instruction Set Simulator
   Computer Architecture, Semester 1, 2016

   Abstract base class for memory and cache

**************************************************************** */

using namespace std;

class memory_accessible {

public:

  // Read a word of data from an address
  virtual uint32_t read_word (uint32_t address) = 0;

  // Write a word of data to an address, mask contains 1s for bytes to be updated
  virtual void write_word (uint32_t address, uint32_t data, uint32_t mask) = 0;

  // Read a block of data of a given size, starting at an address.
  // Data size is a power of 2 number of words, and address is block aligned.
  virtual void read_block (uint32_t address, uint32_t data[], unsigned int data_size) = 0;

  // Write a block of data of a given size, starting at an address
  // Data size is a power of 2 number of words, and address is block aligned.
  virtual void write_block (uint32_t address, uint32_t data[], unsigned int data_size) = 0;

  // Display on cout whether the address is present, and if so, display the data
  virtual void probe_address (uint32_t address) = 0;

  // Report access stats
  virtual void report_accesses () = 0;

};

#endif
