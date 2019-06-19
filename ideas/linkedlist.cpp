#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <string>
#include <list>

#include <cstdint>

using namespace std;


struct Block {
	int key;
	uint32_t vBlkAddr;
	uint32_t *rBlkAddr;
	Block(int i_key)
		{
			rBlkAddr = new uint32_t[1024]();
			vBlkAddr = 0x00040000 + (i_key * 4096);
			key = i_key;
		}
	bool operator<(Block const &compBlock)  { return key < compBlock.key; }
};

// function prototypes
void setWord(list<Block> &mem_list, uint32_t addr, uint32_t value);

void setWord(list<Block> &mem_list, uint32_t addr, uint32_t value) {
	mem_list.sort();

	for (list<Block>::iterator list_iter = mem_list.begin(); list_iter != mem_list.end(); list_iter++) 
	{
		Block* temp = &(*list_iter);
		cout << "ORDERED KEYS AFTER SORT: " << temp->key << endl;
		cout << "ORDERED VIRTUAL BASE ADDR AFTER SORT: " << "0x" << setfill('0') << setw(8) << hex << temp->vBlkAddr << dec << endl; 
	}

	uint32_t temp = addr;
	uint32_t baseAddr = 0x00040000;
	int cnt = -1;

	while (temp >= baseAddr)
	{
		temp = temp - 4096;
		cnt++;
	}

	// check to see if the required memory segment has already been initialized
	// search through list for key = cnt
	bool inMemList = false;
	int listPos = 0;
	for (list<Block>::iterator list_iter = mem_list.begin(); list_iter != mem_list.end(); list_iter++)
	{
		Block* temp = &(*list_iter);
		if (temp->key == cnt)
		{
			cout << "Found the block we want in the mem list. So lets write the word" << endl;
			cout << "What is in list_iter when we found it: " << listPos << endl;
			inMemList = true;
			int offset = addr - temp->vBlkAddr;
			offset = offset/4;
			*(temp->rBlkAddr + offset) = value;
			break;
		}
		listPos++;
	}
 
	if (inMemList)
		// then we have already written the word..
		return;
	else 
	{
		// the memory block hasnt been initialized yet. We need to do some work..
		Block temp(cnt);
		mem_list.push_back(temp);
		mem_list.sort();
		// lets try recursively calling this function now
		cout << "Recursively calling the function again" << endl;
		setWord(mem_list, addr, value);
		return;
	}
}
	

int main() 
{
	Block block1(3);
	Block block2(0);
	//Block block3(5);

	list<Block> int_list;
	int_list.push_back(block1);
	int_list.push_back(block2);
	//int_list.push_back(block3);

	for (list<Block>::iterator list_iter = int_list.begin(); list_iter != int_list.end(); list_iter++) 
	{
		Block* temp = &(*list_iter);
		cout << "ORDERED KEYS AFTER SORT: " << temp->key << endl;
		cout << "ORDERED VIRTUAL BASE ADDR AFTER SORT: " << "0x" << setfill('0') << setw(8) << hex << temp->vBlkAddr << dec << endl; 
	}
	
	for(list<Block>::iterator list_iter = int_list.begin(); list_iter != int_list.end(); list_iter++)
	{
	   	Block* temp = &(*list_iter);
		for (int i = 0; i <= 20; i++) {
			cout << "Value @ virtual address: 0x" << setfill('0') << setw(8) << hex << temp->vBlkAddr + 4*i << dec << " is: " << *(temp->rBlkAddr + i) << " | real address is: " << temp->rBlkAddr + i << endl;

		}
	cout << "MOVING TO NEXT BLOCK" << endl;
	}

	setWord(int_list, 0x0004500C, 1337);
	setWord(int_list, 0x00045038, 1337);
	setWord(int_list, 0xFFFFF040, 999);	

	cout << endl << "AFTER THE SETWORD COMMAND!" << endl;
		for(list<Block>::iterator list_iter = int_list.begin(); list_iter != int_list.end(); list_iter++)
	{
	   	Block* temp = &(*list_iter);
		for (int i = 0; i <= 20; i++) {
			cout << "Value @ virtual address: 0x" << setfill('0') << setw(8) << hex << temp->vBlkAddr + 4*i << dec << " is: " << *(temp->rBlkAddr + i) << " | real address is: " << temp->rBlkAddr + i << endl;

		}
	cout << "MOVING TO NEXT BLOCK" << endl;
	}



return 0;
}
