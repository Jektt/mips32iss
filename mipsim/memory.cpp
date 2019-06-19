/* ****************************************************************
   MIPS32 Instruction Set Simulator
   Computer Architecture, Semester 1, 2016

   Class members for memory

**************************************************************** */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>

#include "memory.h"

using namespace std;

// Constructor
memory::memory(bool verbose,
	       bool cycle_reporting,
	       unsigned long int address_cycles,
	       unsigned long int data_cycles) {
  m_verbose = verbose;
  m_cycle_reporting = cycle_reporting;
  m_address_cycles = address_cycles;
  m_data_cycles = data_cycles;
  m_vBaseAddr = 0x00000000;
}

// Read a word of data from an address
uint32_t memory::read_word (uint32_t address) {

	// is the address given word alligned?
	if (address % 4 != 0)
	{
		while (address % 4 != 0) 
		{
			address = address - 1;
		}
	}

	// reference 'key', make sure our blocks of memory are unique for the respective virtual memory addresses and don't overlap
	int ref;
	ref = address/4096;

	for (unsigned int i = 0; i < m_list.size(); i++)
	{
		Block* temp = &(m_list[i]);
		if (temp->key == ref)
		{
			int offset = address - temp->vBlkAddr;		// the offset from the real address of the block to go to
			offset = offset/4;				// Blocks are addressed in 4 byte sequences
			if (m_verbose)
				cout << "Memory read word: address = " << setfill('0') << setw(8) << hex << address << ", data = " << setfill('0') << setw(8) << hex << *(temp->rBlkAddr + offset) << endl;
			return *(temp->rBlkAddr + offset);
		}
	}
	// the memory block hasnt been initialized yet. We need to do that and add it to the m_list
	Block temp(ref);
	m_list.push_back(temp);
	
	return read_word(address);
}

// Write a word of data to an address, mask contains 1s for bytes to be updated (eg 0xFFFFFFFF) (Bytes not updated retain their old value)
void memory::write_word (uint32_t address, uint32_t data, uint32_t mask) 
{
	bool saveVerbose = m_verbose;
	m_verbose = false;
	uint32_t origData = this->read_word(address);
	uint32_t origMask = (~mask) & origData;
	uint32_t dataMask = mask & data;
	uint32_t writeData = dataMask | origMask;
	this->set_address(address, writeData);
	m_verbose = saveVerbose;
	if (m_verbose) cout << "Memory write word: address = " << hex << setfill('0') << setw(8) << address << ", data = " << hex << setfill('0') << setw(8) << data << ", mask = " << hex << setfill('0') << setw(8) << mask << endl;
	return;
}

// Read a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void memory::read_block (uint32_t address, uint32_t data[], unsigned int data_size) {
  // TODO: ...
	unsigned int words = data_size/4;
	if (m_verbose) cout << "Memory read block: address = " << hex << setfill('0') << setw(8) << address << ", " << dec << words << " words" << endl;

	// is the address given word alligned?
	if (address % 4 != 0)
	{
		while (address % 4 != 0) 
		{
			address = address - 1;
		}
	}

	// reference 'key', make sure our blocks of memory are unique for the respective virtual memory addresses and don't overlap
	int ref;
	ref = address/4096;

	for (unsigned int i = 0; i < m_list.size(); i++)
	{
		Block* temp = &(m_list[i]);
		if (temp->key == ref)
		{
			int offset = address - temp->vBlkAddr;		// the offset from the real address of the block to go to
			for (unsigned int j = 0; j < words; j++) 
			{
				data[j] = *(temp->rBlkAddr + (offset/4) + j);
			}
			return;			
		}
	}
	return;
}

// Write a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void memory::write_block (uint32_t address, uint32_t data[], unsigned int data_size) {

	bool saveVerbose = m_verbose;

	if (m_verbose) cout << "Memory write block: address = " << hex << setfill('0') << setw(8) << address << ", " << data_size/4 << " words" << endl;

	m_verbose = false;
	for (unsigned int i = 0; i < (data_size/4); i++)
	{
		this->write_word(address + (4*i), data[i], 0xFFFFFFFF);
	}
	m_verbose = saveVerbose;
}

// Display on cout whether the address is present, and if so, display the data
void memory::probe_address (uint32_t address) {

	// is the address given word alligned?
	if (address % 4 != 0)
	{
		while (address % 4 != 0) 
		{
			address = address - 1;
		}
	}

	// reference 'key', make sure our blocks of memory are unique for the respective virtual memory addresses and don't overlap
	int ref;
	ref = address/4096;

	for (unsigned int i = 0; i < m_list.size(); i++)
	{
		Block* temp = &(m_list[i]);
		if (temp->key == ref)
		{
			int offset = address - temp->vBlkAddr;		// the offset from the real address of the block to go to
			offset = offset/4;				// Blocks are addressed in 4 byte sequences
			cout << "Memory: " << setfill('0') << setw(8) << hex << *(temp->rBlkAddr + offset) << endl;
			return;
		}
	}
	return;
}

// Report access stats
void memory::report_accesses () {
	// Not needed for UG
}

// Display the word of data at an address
void memory::show_address (uint32_t address) {

	bool verboseSave = m_verbose;

	m_verbose = false;
	cout << setfill('0') << setw(8) << hex << this->read_word(address) << endl;
	m_verbose = verboseSave;
}

// Set the word of data at an address
void memory::set_address (uint32_t address, uint32_t data) {

	// is the address given word alligned?
	if (address % 4 != 0)
	{
		while (address % 4 != 0) 
		{
			address = address - 1;
		}
	}

	// Reference key to ensure we dont have overlapping memory blocks
	int ref;
	ref = address/4096;

	// check to see if the required memory segment has already been initialized
	for (unsigned int i = 0; i < m_list.size(); i++)
	{
		Block* temp = &(m_list[i]);
		if (temp->key == ref)
		{
			int offset = address - temp->vBlkAddr;		// the offset from the real address of the block to go to
			offset = offset/4;				// Blocks are addressed in 4 byte sequences
			*(temp->rBlkAddr + offset) = data;
			return;
		}
	}
	// the memory block hasnt been initialized yet. We need to do that and add it to the m_list
	Block temp(ref);
	m_list.push_back(temp);
	set_address(address, data);
	return;
}

// Return the accumulated number of cycles for read accesses
unsigned long int memory::get_read_cycle_count () {
	// Not needed for UG
  	unsigned long int temp = 0;
	return temp;
}

// Load a hex image file
bool memory::load_file(string file_name, uint32_t &start_address) {

  ifstream input_file(file_name);
  string input;
  unsigned long int line_count = 0;
  unsigned long int byte_count = 0;
  char record_start;
  char byte_string[2];
  char halfword_string[4];
  uint32_t record_length;
  uint32_t record_address;
  uint32_t record_type;
  uint32_t record_data;
  uint32_t record_checksum;
  bool end_of_file_record = false;
  uint32_t load_base_address = 0x00000000;
  uint32_t load_address;

  // Going to be loading it a word at a time (Did this before I had done the mask part of write_word)
  uint32_t temp;	
  int cnt = 0;
  uint32_t temp_record_data = 0;

  start_address = 0x00000000;
  if (input_file.is_open()) {
    while (true) {
      line_count++;
      input_file >> record_start;
      if (record_start != ':') {
	cout << "Input line " << dec << line_count << " does not start with colon character" << endl;
	return false;
      }
      input_file.get(byte_string, 3);
      sscanf(byte_string, "%x", &record_length);
      input_file.get(halfword_string, 5);
      sscanf(halfword_string, "%x", &record_address);
      input_file.get(byte_string, 3);
      sscanf(byte_string, "%x", &record_type);
      switch (record_type) {
      case 0x00:  // Data record
	
	for (uint32_t i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	  load_address = (load_base_address | record_address) + i;
	  //   - load_address is the byte address at which to store
	  //   - record_data is the byte of data to store
		if (i!=0) 
		{
			if (load_address != temp + 1) 
			{  
				cout << "FATAL ERROR: Only supporting writing sequential bytes." << endl;
				return false;
			}
		}

		temp = load_address;

		// merge 4 bytes to form a 32 bit int
		if (cnt < 4)
			temp_record_data = temp_record_data | (record_data << ((3-cnt)*8));

		// we have summed 4 bytes of data now
		if (cnt == 3) 
		{
			set_address(load_address-3, temp_record_data);
			cnt = -1;
			temp_record_data = 0;
		}
		cnt++;
		byte_count++;
	}
	break;
      case 0x01:  // End of file
	end_of_file_record = true;
	break;
      case 0x02:  // Extended segment address (ignored)
      case 0x03:  // Start segment address (ignored)
	for (uint32_t i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	}
	break;
      case 0x04:  // Extended linear address (set upper halfword of load base address)
	load_base_address = 0x00000000;
	for (uint32_t i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	  load_base_address = (load_base_address << 8) | (record_data << 16);
	}
	break;
      case 0x05:  // Start linear address (set execution start address)
	start_address = 0x00000000;
	for (uint32_t i = 0; i < record_length; i++) {
	  input_file.get(byte_string, 3);
	  sscanf(byte_string, "%x", &record_data);
	  start_address = (start_address << 8) | record_data;
	}
	break;
      }
      input_file.get(byte_string, 3);
      sscanf(byte_string, "%x", &record_checksum);
      input_file.ignore();
      if (end_of_file_record)
	break;
    }
    input_file.close();
    cout << dec << byte_count << " bytes loaded, start address = "
	 << setw(8) << setfill('0') << hex << start_address << endl;
    return true;
  }
  else {
    cout << "Failed to open file" << endl;
    return false;
  }
}

