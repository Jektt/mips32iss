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
	     bool verbose) 
{
	m_verbose = verbose;
	m_write_strategy = write_strategy;
	m_associativity = associativity;
	m_size = size;
	m_block_size = block_size;
	m_backing_store = backing_store;
	m_name = name;
	m_number_of_sets = (m_size/m_block_size)/m_associativity;
	m_number_of_entries = m_size/m_block_size;

	m_miss = 0;
	m_accesscount = 0;
	m_non_dirtyreplace = 0;
	m_dirtyreplace = 0;

	// Get index, tag, offset masks
	uint32_t temp;
	offset_length = 0;
	index_length = 0;

	m_offsetmask = m_block_size - 1;

	temp = m_block_size;

	while (((temp % 2) == 0) && (temp > 1))
	{
		temp = temp/2;
		offset_length++;
	}

	temp = m_size/m_block_size;
	if (m_associativity == 1)
	{
		m_indexmask = (temp - 1) << offset_length;
	}
	else if (m_associativity != 1)
	{
		temp = temp/m_associativity;
		m_indexmask = (temp - 1) << offset_length;
	}
	
	while (((temp % 2) == 0) && (temp > 1))
	{
		temp = temp/2;
		index_length++;
	}

	m_tagmask = ~(m_indexmask + m_offsetmask);

	if (verbose) 
	{
		if (m_write_strategy == READ_ONLY) 
			cout << m_name << ": tag_mask = " << setfill('0') << setw(8) << hex << m_tagmask << ", set index mask = " << setfill('0') << setw(8) << m_indexmask << ", offset mask = " << setfill('0') << setw(8) << m_offsetmask << ", read only" << dec << endl;
		else if (m_write_strategy == WRITE_THROUGH)
			cout << m_name << ": tag_mask = " << setfill('0') << setw(8) << hex << m_tagmask << ", set index mask = " << setfill('0') << setw(8) << m_indexmask << ", offset mask = " << setfill('0') << setw(8) << m_offsetmask << ", write through" << dec << endl;
		else if (m_write_strategy == WRITE_BACK)
			cout << m_name << ": tag_mask = " << setfill('0') << setw(8) << hex << m_tagmask << ", set index mask = " << setfill('0') << setw(8) << m_indexmask << ", offset mask = " << setfill('0') << setw(8) << m_offsetmask << ", write back" << dec << endl;
	}

	// Allocate cache memory
	for (unsigned int i=0; i < m_number_of_entries; i++) 
	{
		CacheBlock cachetemp(m_block_size);
		m_cachelist.push_back(cachetemp);
	}

	// LRU queue for each set
	vector<unsigned int> set_rep;
	for (unsigned int i = 0; i < m_associativity; i++) 
	{
		set_rep.push_back(i);
	}
		
	for (unsigned int i = 0; i < m_number_of_sets; i++) 
	{
		m_setsLRU.push_back(set_rep);
	}
}

// Read a word of data from an address
uint32_t cache::read_word (uint32_t address) {

	if (m_verbose) cout << m_name << ": read word address = " << hex << setfill('0') << setw(8) << address << endl;

	uint32_t tag = (m_tagmask & address) >> (offset_length + index_length);
	uint32_t set = (m_indexmask & address) >> offset_length;
	uint32_t offset = m_offsetmask & address;

	bool cachehit = false;
	unsigned int replaceEntry;
	CacheBlock* temp;
	bool setFull = true;
	bool ReplaceSet = false;

	if (m_verbose) cout << m_name << ": lookup address = " << hex << setfill('0') << setw(8) << address << ": tag = " << hex << tag << ", set = " << hex << set << ", offset = " << offset;
	m_accesscount++;

	for (unsigned int i = 0; i < m_associativity; i++)
	{
		temp = &(m_cachelist[(set * m_associativity) + i]);
		if (temp->valid == false || (m_associativity == 1))
		{
			setFull = false;
			if (ReplaceSet == false)
			{
				replaceEntry = i;
				ReplaceSet = true;
			}
		} 
		if ((temp->tag == tag) && (temp->valid == true)) 
		{
			cachehit = true;
			if (m_verbose) cout << ", hit, entry = " << dec << i << endl;

			if (m_associativity != 1) 
			{
				// data is in cache, move entry (i) to start of the queue for this set
				for (auto it = m_setsLRU[set].begin(); it != m_setsLRU[set].end(); it++)
				{
					if (*it == i)
					{
						m_setsLRU[set].erase(it);
						m_setsLRU[set].insert(m_setsLRU[set].begin(), i);
						break;
					}
				}
			}
			return (*(temp->rBlkAddr + offset/4));	
		}
	}

	if (!cachehit)
	{
		m_miss++;
		if (m_verbose) cout << ", miss" << endl;

		if (!setFull  || (m_associativity == 1))
		{
			temp = &(m_cachelist[(set * m_associativity) + replaceEntry]);
		}
		else if (setFull && (m_associativity != 1))
		{
			replaceEntry = m_setsLRU[set].back();
			temp = &(m_cachelist[(set * m_associativity) + replaceEntry]);
		}

		if (!temp->dirty)
		{
			// get block from main memory. then cache 	
			if (m_verbose) cout  << m_name << ": Replacing entry " << dec << replaceEntry << endl;
			m_non_dirtyreplace++;
			uint32_t* mainmem_data = new uint32_t [m_block_size/4];
			m_backing_store->read_block(address - offset, mainmem_data, m_block_size);
			temp->valid = false;
			this->write_block(address - offset, mainmem_data, m_block_size);
		}

		else if (temp->dirty)
		{
			// write cache entry to main memory, read this and put into cache. set dirty to false
			uint32_t dirtyAddr = (temp->tag << (offset_length + index_length)) + (set << offset_length);
			if (m_verbose) cout  << m_name << ": Replacing entry " << dec << replaceEntry << ", dirty address = " << hex << setfill('0') << setw(8) << dirtyAddr << endl;
			m_dirtyreplace++;
			uint32_t* mainmem_data = new uint32_t [m_block_size/4];
			m_backing_store->read_block(address - offset, mainmem_data, m_block_size);
			m_backing_store->write_block(dirtyAddr, temp->rBlkAddr, m_block_size);

			temp->valid = false;	// evict the block so write block function writes to it
			this->write_block(address - offset, mainmem_data, m_block_size);
			temp->dirty = false;
		}	
			
		// update LRU
		if (!setFull)
		{
			for (auto it = m_setsLRU[set].begin(); it != m_setsLRU[set].end(); it++)
			{
				if (*it == replaceEntry)
				{
					m_setsLRU[set].erase(it);
					m_setsLRU[set].insert(m_setsLRU[set].begin(), replaceEntry);
					break;
				}
			}
		}
		
		else if (setFull)
		{
			m_setsLRU[set].erase(m_setsLRU[set].end() - 1);
			m_setsLRU[set].insert(m_setsLRU[set].begin(), replaceEntry);
		}
		return *(temp->rBlkAddr + (offset/4));
	}
	return 0;
}

// Write a word of data to an address, mask contains 1s for bytes to be updated
void cache::write_word (uint32_t address, uint32_t data, uint32_t mask) {

	if (m_verbose) cout << m_name << ": write word address = " << hex << setfill('0') << setw(8) << address << ", data = " << hex << setfill('0') << setw(8) << data << ", mask = " << hex << setfill('0') << setw(8) << mask << endl;

	bool setFull = true;
	unsigned int replaceEntry;
	bool ReplaceSet = false;
	bool cachehit = false;
	CacheBlock* temp;

	uint32_t tag = ((m_tagmask & address) >> (offset_length + index_length));
	uint32_t set = (m_indexmask & address) >> offset_length;
	uint32_t offset = m_offsetmask & address;

	if (m_verbose) cout << m_name << ": lookup address = " << hex << setfill('0') << setw(8) << address << ": tag = " << hex << tag << ", set = " << hex << set << ", offset = " << offset;
	
	// see if we already have that address tagged in our cache. 
	m_accesscount++;
	for (unsigned int i = 0; i < m_associativity; i++)
	{
		temp = &(m_cachelist[(set * m_associativity) + i]);
		if (temp->valid == false || (m_associativity == 1))
		{
			setFull = false;
			if (ReplaceSet == false)
			{
				replaceEntry = i;
				ReplaceSet = true;
			}
		} 
		if ((temp->tag == tag) && (temp->valid == true))
		{
			cachehit = true;
			if (m_verbose) cout << ", hit, entry = " << dec << i << endl;

			if (m_write_strategy == WRITE_THROUGH) 
			{
				*(temp->rBlkAddr + (offset/4)) = data;
				m_backing_store->write_word(address, data, 0xFFFFFFFF);
			}

			if (m_write_strategy == WRITE_BACK)
			{
				if (temp->dirty)
				{
					*(temp->rBlkAddr + (offset/4)) = data;
				}
				else if (!temp->dirty)
				{
					*(temp->rBlkAddr + (offset/4)) = data;
				}
				temp->dirty = true;
			}

			// then also add the entry to front of LRU queue
			if (m_associativity != 1) 
			{
				for (auto it = m_setsLRU[set].begin(); it != m_setsLRU[set].end(); it++)
				{
					if (*it == i)
					{
						//cout << "Moving entry #: " << i << ", in set #: " << set << ", to the front of the queue." << endl;
						m_setsLRU[set].erase(it);
						m_setsLRU[set].insert(m_setsLRU[set].begin(), i);
						break;
					}
				}
			}
			return;
		}
	}

	if (!cachehit)
	{
		m_miss++;
		if (m_verbose) cout << ", miss" << endl;

		if (m_write_strategy == WRITE_THROUGH)
		{
			m_backing_store->write_word(address, data, 0xFFFFFFFF);
			return;
		}
		
		if (!setFull || (m_associativity == 1))
		{
			temp = &(m_cachelist[(set * m_associativity) + replaceEntry]);
		}
		
		else if (setFull && (m_associativity != 1)) 
		{
			temp = &(m_cachelist[(set * m_associativity) + m_setsLRU[set].back()]);
		}

		if (m_write_strategy == WRITE_BACK) 
		{
			if (!temp->dirty)
			{
				// get block from main memory. then cache 	
				if (m_verbose) cout  << m_name << ": Replacing entry " << dec << replaceEntry << endl;
				m_non_dirtyreplace++;
				uint32_t* mainmem_data = new uint32_t [m_block_size/4];
				m_backing_store->read_block(address - offset, mainmem_data, m_block_size);
				temp->valid = false;
				this->write_block(address - offset, mainmem_data, m_block_size);
				*(temp->rBlkAddr + (offset/4)) = data;	// write value to cache
			}

			if (temp->dirty)
			{
				// write cache entry to main memory, read this and put into cache. set dirty to false
				uint32_t dirtyAddr = (temp->tag << (offset_length + index_length)) + (set << offset_length);
				if (m_verbose) cout  << m_name << ": Replacing entry " << dec << replaceEntry << ", dirty address = " << hex << setfill('0') << setw(8) << dirtyAddr << endl;
				m_dirtyreplace++;
				uint32_t* mainmem_data = new uint32_t [m_block_size/4];
				m_backing_store->read_block(address - offset, mainmem_data, m_block_size);
				m_backing_store->write_block(dirtyAddr, temp->rBlkAddr, m_block_size);
				temp->valid = false;	// evict the block so write block function writes to it
				this->write_block(address - offset, mainmem_data, m_block_size);
				*(temp->rBlkAddr + (offset/4)) = data;	// write value to cache
			}
			temp->dirty = true;	

			// update LRU with write back
			if (!setFull)
			{
				for (auto it = m_setsLRU[set].begin(); it != m_setsLRU[set].end(); it++)
				{
					if (*it == replaceEntry)
					{
						m_setsLRU[set].erase(it);
						m_setsLRU[set].insert(m_setsLRU[set].begin(), replaceEntry);
						break;
					}
				}
			}
			
			if (setFull)
			{
				unsigned int entryNum = *(m_setsLRU[set].end() - 1);
				m_setsLRU[set].erase(m_setsLRU[set].end() - 1);
				m_setsLRU[set].insert(m_setsLRU[set].begin(), entryNum);
			}
			return;
		}
	}
}

// Read a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void cache::read_block (uint32_t address, uint32_t data[], unsigned int data_size) {

	uint32_t tag = ((m_tagmask & address) >> (offset_length + index_length));
	uint32_t set = (m_indexmask & address) >> offset_length;

	CacheBlock* temp;

	for (unsigned int i = 0; i < m_associativity; i++) 
	{
		temp = &(m_cachelist[(set * m_associativity) + i]);
		if ((temp->tag == tag) && (temp->valid == true)) 
		{
			// found block we want to cout
			cout << "    ";
			for (unsigned int j=0; j < data_size; j++) 
			{
				if ((j != 0) && (j % 8 == 0)) 
				{
					cout << endl << "    ";
				}
				if (j != (data_size - 1)) 
				{
					cout << hex << setfill('0') << setw(8) << *(temp->rBlkAddr + j) << " ";
				}
				else if (j == (data_size - 1)) 
				{
					cout << hex << setfill('0') << setw(8) << *(temp->rBlkAddr + j) << endl;
				}	
			}
			return;
		}
	}	
}

// Write a block of data of a given size, starting at an address
// Data size is a power of 2 number of words, and address is block aligned.
void cache::write_block (uint32_t address, uint32_t data[], int unsigned data_size) {

	CacheBlock* temp;

	uint32_t tag = ((m_tagmask & address) >> (offset_length + index_length));
	uint32_t set = (m_indexmask & address) >> offset_length;
	//uint32_t offset = m_offsetmask & address;

	for (unsigned int i = 0; i < m_associativity; i++)
	{
		temp = &(m_cachelist[(set * m_associativity) + i]);
		if ((temp->valid == false) || (m_associativity == 1)) 
		{
			for (unsigned int j = 0; j<(data_size/4); j++) 
			{
				*(temp->rBlkAddr + j) = data[j];
			}
			temp->valid = true;
			temp->tag = tag;
			return;
		}
	}
	cout << "oh oh" << endl;
	return;
}

// Display on cout whether the address is present, and if so, display the data
void cache::probe_address (uint32_t address) {

	if (m_verbose) cout << m_name << ": probe address = " << hex << setfill('0') << setw(8) << address << endl;

	uint32_t tag = (m_tagmask & address) >> (offset_length + index_length);
	uint32_t set = (m_indexmask & address) >> offset_length;
	uint32_t offset = m_offsetmask & address;
	bool cachehit = false;

	if (m_verbose) cout << m_name << ": lookup address = " << hex << setfill('0') << setw(8) << address << ": tag = " << hex << tag << ", set = " << hex << set << ", offset = " << offset;

	CacheBlock* temp;

	for (unsigned int i = 0; i < m_associativity; i++) 
	{
		temp = &(m_cachelist[(set * m_associativity) + i]);
		if ((temp->tag == tag) && (temp->valid == true))
		{
			if (m_verbose) cout << ", hit, entry = " << dec << i << endl;
			if (!temp->dirty) cout << m_name << ": hit, set = " << hex << set << ", entry = " << dec << i << ":" << endl;
			if (temp->dirty) cout << m_name << ": hit, set = " << hex << set << ", entry = " << dec << i << ", dirty:" << endl;
			cachehit = true;
			this->read_block(address, 0, m_block_size/4);
			m_backing_store->probe_address(address);
			return;
		}
	}
	if (!cachehit)
	{
		if (m_verbose) cout << ", miss" << endl;
		// go to main memory
		cout << m_name << ": miss, set = " << hex << set << endl;
		m_backing_store->probe_address(address);
		return;
	}
}

// Report access stats
void cache::report_accesses () {

	float missrate = (float)m_miss/(float)m_accesscount;
  	cout << m_name << " access count: " << m_accesscount << endl;
	cout << m_name << " miss rate: " << fixed << setprecision(6) << missrate << endl;
	if (m_write_strategy == WRITE_BACK)
	{
		cout << m_name << " dirty on replacement rate: " << (float)m_dirtyreplace/(float)((m_dirtyreplace + m_non_dirtyreplace)) << endl;
	}
}

