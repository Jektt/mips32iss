#ifndef CACHE_H
#define CACHE_H

/* ****************************************************************
   MIPS32 Instruction Set Simulator
   Computer Architecture, Semester 1, 2016

   Class for cache

**************************************************************** */

#include <vector>

#include "memory_accessible.h"

using namespace std;

class cache: public memory_accessible {

  struct CacheBlock {
	bool valid;
	bool dirty;
	uint32_t tag;
	unsigned long int block_size;
	uint32_t *rBlkAddr;
	CacheBlock(unsigned long int i_block_size)
	{
		rBlkAddr = new uint32_t[i_block_size/4]();	// each uint32_t object is 4 bytes
		tag = 0;
		valid = false;
		dirty = false;
	}
  };

 public:

  enum write_strategy_t { READ_ONLY, WRITE_THROUGH, WRITE_BACK };

  // Constructor
  cache(string name,
	memory_accessible* backing_store,
	unsigned long int block_size,
	unsigned long int size,
	unsigned long int associativity,
	write_strategy_t write_strategy,
	bool verbose);
  	 
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

  // Report access stats
  void report_accesses ();

 private:

  // TODO: Add private members here
	bool m_verbose;
	write_strategy_t m_write_strategy;
	unsigned long int m_associativity;
	unsigned long int m_size;
	unsigned long int m_block_size;
	memory_accessible* m_backing_store;
	string m_name;

	uint32_t m_tagmask;
	uint32_t m_indexmask;
	uint32_t m_offsetmask;

	vector<CacheBlock> m_cachelist;
	vector<vector<unsigned int>> m_setsLRU;

	unsigned int offset_length;
	unsigned int index_length;

	unsigned int m_accesscount;
	unsigned int m_miss;
	unsigned int m_non_dirtyreplace;
	unsigned int m_dirtyreplace;

	unsigned int m_number_of_sets;
	unsigned int m_number_of_entries;
};

#endif
