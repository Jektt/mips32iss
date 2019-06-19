#ifndef MEMORY_H
#define MEMORY_H

/* ****************************************************************
   MIPS32 Instruction Set Simulator
   Computer Architecture, Semester 1, 2016

   Class for memory

**************************************************************** */

#include <vector>

#include "memory_accessible.h"

using namespace std;

class memory: public memory_accessible {

  struct Block {
	int key;
	uint32_t vBlkAddr;
	uint32_t *rBlkAddr;
	Block(int i_key)
	{
		rBlkAddr = new uint32_t[1024]();
		vBlkAddr = 0x00000000 + (i_key * 4096);
		key = i_key;
	}
	bool operator <(const Block& x) const { 
		return (this->key < x.key); 
	}
  };

 private:
 
  vector<Block> m_list;
  bool m_verbose;
  bool m_cycle_reporting;
  unsigned long int m_address_cycles;		// not used for UG
  unsigned long int m_data_cycles;		// not used for UG
  uint32_t m_vBaseAddr;
  

 public:

  // Constructor
  memory(bool verbose,
	 bool cycle_reporting,
	 unsigned long int address_cycles,
  	 unsigned long int data_cycles);
  	 
  // Read a word of data from an address							
  uint32_t read_word (uint32_t address);

  // Write a word of data to an address, mask contains 1s for bytes to be updated
  void write_word (uint32_t address, uint32_t data, uint32_t mask);

  // Read a block of data of a given size, starting at an address
  // Data size is a power of 2 number of words, and address is block aligned.
  void read_block (uint32_t address, uint32_t data[], unsigned int data_size);

  // Write a block of data of a given size, starting at an address
  // Data size is a power of 2 number of words, and address is block aligned.
  void write_block (uint32_t address, uint32_t data[], unsigned int data_size);

  // Display on cout whether the address is present, and if so, display the data		
  void probe_address (uint32_t address);

  // Report access stats (not for UG?)
  void report_accesses ();

  // Display the word of data at an address							
  void show_address (uint32_t address);

  // Set the word of data at an address								
  void set_address (uint32_t address, uint32_t data);

  // Return the accumulated number of cycles for read accesses
  unsigned long int get_read_cycle_count ();

  // Load a hex image file
  bool load_file(string file_name, uint32_t &start_address);
};

#endif
