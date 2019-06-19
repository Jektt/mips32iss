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
  m_vBaseAddr = 0x00040000;
}

// Read a word of data from an address
uint32_t memory::read_word (uint32_t address) {
	
	// is the address given word alligned?
	if (m_verbose)
	{
		if (address % 4 == 0)
			cout << "DEBUG: Address is word aligned." << endl;
		else
		{
			cout << "DEBUG: Address isn't worth aligned. (Not supported)" << endl;
			return 0x00000000;
		}
	}

	m_list.sort();

	if (m_verbose == true)
	{
		for (list<Block>::iterator m_list_i = m_list.begin(); m_list_i != m_list.end(); m_list_i++) 
		{
			Block* temp = &(*m_list_i);
			cout << "DEBUG: Ordered keys after sort: " << temp->key << endl;
			cout << "DEBUG: Ordered virtual base address after sort: " << "0x" << setfill('0') << setw(8) << hex << temp->vBlkAddr << dec << endl; 
		}
	}

	uint32_t temp = address;
	int cnt = -1;			// variable to count how many blocks sizes of memory we are from the base address

	while (temp >= m_vBaseAddr)
	{
		temp = temp - 4096;	// 4096KB is the block size
		cnt++;
	}

	// check to see if the required memory segment has already been initialized
	// search through list for key = cnt
	bool inMemList = false;
	if (m_verbose)
		cout << "DEBUG: Searching initialized memory for a block containing desired address." << endl;

	for (list<Block>::iterator m_list_i = m_list.begin(); m_list_i != m_list.end(); m_list_i++)
	{
		Block* temp = &(*m_list_i);
		if (temp->key == cnt)
		{
			if (m_verbose)
				cout << "DEBUG: Found the memory block, it was already initialized." << endl;
			inMemList = true;
			int offset = address - temp->vBlkAddr;		// the offset from the real address of the block to go to
			offset = offset/4;				// Blocks are addressed in 4 byte sequences
			return *(temp->rBlkAddr + offset);
		}
	}
 
	if (inMemList)
	{
		// then we have already written the word and returned. We can't be here..
		cout << "Error." << endl;
		if (m_verbose)
			cout << "DEBUG: Memory block was already initialized and then found. But we didn't exit the read function." << endl;
		return 0x00000000;
	}

	else 
	{
		// the memory block hasnt been initialized yet. We need to do that and add it to the m_list
		if (m_verbose)
			cout << "DEBUG: Memory not initialized. Initializing an aligned 4096KB block and adding to the memory list." << endl;
		Block temp(cnt);
		m_list.push_back(temp);
		m_list.sort();
		// recursive call on this function since now the memory is there
		if (m_verbose)
			cout << "DEBUG: New memory block added. Recursivly checking the initialized value. (Should be a zero)" << endl;
		return read_word(address);
	}
}

// Write a word of data to an address, mask contains 1s for bytes to be updated (as in, only update the bytes where a 1 is present? mask = 0x1111?
void memory::write_word (uint32_t address, uint32_t data, uint32_t mask) {
  // TODO: ...
}

// Read a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void memory::read_block (uint32_t address, uint32_t data[], unsigned int data_size) {
  // TODO: ...
	// @@@Just use the write word function iteratively over length of data array?
	// Not needed for stage 1.
}

// Write a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void memory::write_block (uint32_t address, uint32_t data[], unsigned int data_size) {
  // TODO: ...
	// Not needed for stage 1.
}

// Display on cout whether the address is present, and if so, display the data
void memory::probe_address (uint32_t address) {

	// is the address given word alligned?
	if (m_verbose)
	{
		if (address % 4 == 0)
			cout << "DEBUG: Address is word aligned." << endl;
		else
		{
			cout << "DEBUG: Address isn't worth aligned. (Not supported)" << endl;
			return;
		}
	}

	m_list.sort();

	uint32_t temp = address;
	int cnt = -1;			// variable to count how many blocks sizes of memory we are from the base address

	while (temp >= m_vBaseAddr)
	{
		temp = temp - 4096;	// 4096KB is the block size
		cnt++;
	}

	// check to see if the required memory segment has already been initialized
	// search through list for key = cnt
	bool inMemList = false;
	if (m_verbose)
		cout << "DEBUG: Searching initialized memory for a block containing desired address." << endl;

	for (list<Block>::iterator m_list_i = m_list.begin(); m_list_i != m_list.end(); m_list_i++)
	{
		Block* temp = &(*m_list_i);
		if (temp->key == cnt)
		{
			if (m_verbose)
				cout << "DEBUG: Found the memory block, it was already initialized." << endl;
			inMemList = true;
			int offset = address - temp->vBlkAddr;		// the offset from the real address of the block to go to
			offset = offset/4;				// Blocks are addressed in 4 byte sequences
			cout << "Address: 0x" << setfill('0') << setw(8) << hex << address << " value is: 0x" << setfill('0') << setw(8) << hex << *(temp->rBlkAddr + offset) << endl;			
			return;
		}
	}
 
	if (inMemList)
	{
		// then we have already printed the word and returned. We can't be here..
		cout << "Error." << endl;
		if (m_verbose)
			cout << "DEBUG: Memory block was already initialized and then found. But we didn't exit the read function." << endl;
		return;
	}

	else 
	{
		// memory address has not been initialized, print message and return
		cout << "Address: 0x" << setfill('0') << setw(8) << hex << address << " is not initialized by simulator" << endl;
		return;
	}


}

// Report access stats
void memory::report_accesses () {
  // TODO: ...
}

// Display the word of data at an address
void memory::show_address (uint32_t address) {
	uint32_t temp = this->read_word(address);
	cout << "0x" << setfill('0') << setw(8) << hex << temp << endl;
}

// Set the word of data at an address
void memory::set_address (uint32_t address, uint32_t data) {

	// is the address given word alligned?
	if (m_verbose)
	{
		if (address % 4 == 0)
			cout << "DEBUG: Address is word aligned." << endl;
		else
		{
			cout << "DEBUG: Address isn't worth aligned. (Not supported)" << endl;
			return;
		}
	}

	m_list.sort();

	if (m_verbose == true)
	{
		for (list<Block>::iterator m_list_i = m_list.begin(); m_list_i != m_list.end(); m_list_i++) 
		{
			Block* temp = &(*m_list_i);
			cout << "DEBUG: Ordered keys after sort: " << temp->key << endl;
			cout << "DEBUG: Ordered virtual base address after sort: " << "0x" << setfill('0') << setw(8) << hex << temp->vBlkAddr << dec << endl; 
		}
	}

	uint32_t temp = address;
	int cnt = -1;			// variable to count how many blocks sizes of memory we are from the base address

	while (temp >= m_vBaseAddr)
	{
		temp = temp - 4096;	// 4096KB is the block size
		cnt++;
	}

	// check to see if the required memory segment has already been initialized
	// search through list for key = cnt
	bool inMemList = false;
	if (m_verbose)
		cout << "DEBUG: Searching initialized memory for a block containing desired address." << endl;

	for (list<Block>::iterator m_list_i = m_list.begin(); m_list_i != m_list.end(); m_list_i++)
	{
		Block* temp = &(*m_list_i);
		if (temp->key == cnt)
		{
			if (m_verbose)
				cout << "DEBUG: Found the memory block, it was already initialized." << endl;
			inMemList = true;
			int offset = address - temp->vBlkAddr;		// the offset from the real address of the block to go to
			offset = offset/4;				// Blocks are addressed in 4 byte sequences
			*(temp->rBlkAddr + offset) = data;
			return;
		}
	}
 
	if (inMemList)
	{
		// then we have already written the word and returned. We can't be here..
		cout << "Error." << endl;
		if (m_verbose)
			cout << "DEBUG: Memory block was already initialized and then found. But we didn't exit the set function." << endl;
		return;
	}

	else 
	{
		// the memory block hasnt been initialized yet. We need to do that and add it to the m_list
		if (m_verbose)
			cout << "DEBUG: Memory not initialized. Initializing an aligned 4096KB block and adding to the memory list." << endl;
		Block temp(cnt);
		m_list.push_back(temp);
		// recursive call on this function since now the memory is there
		if (m_verbose)
			cout << "DEBUG: New memory block added. Doing a recursive call of this function set_address to set the word." << endl;
		set_address(address, data);
		return;
	}

}

// Return the accumulated number of cycles for read accesses
unsigned long int memory::get_read_cycle_count () {
  // TODO: ...
}


// Prints info about the first 20 words in each allocated memory block. Virtual address : Value : Real address
void memory::disp_mem() {
	
	for (list<Block>::iterator m_list_i = m_list.begin(); m_list_i != m_list.end(); m_list_i++)
	{
	   	Block* temp = &(*m_list_i);
		for (int i = 0; i <= 20; i++) {
			cout << "Virtual Word Address: 0x" << setfill('0') << setw(8) << hex << temp->vBlkAddr + 4*i << " | Value Stored: 0x" << setfill('0') << setw(8) << hex << *(temp->rBlkAddr + i) << " | Real Word Address: " << hex << temp->rBlkAddr + i << endl;

		}
	cout << endl << "------------NEXT MEM BLOCK------------" << endl;
	}
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
  // TODO: any other local variables if needed

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
	  // TODO: code to store data byte in memory.
	  //   - load_address is the byte address at which to store
	  //   - record_data is the byte of data to store


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

