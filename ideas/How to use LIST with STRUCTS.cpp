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
};

bool compare(const Block& first, const Block& second)
{
  if (first.key < second.key)
    return true;
  else
    return false;
}

int main() 
{

	Block block1;
	Block block2;
	Block block3;

	block1.key = 30;
	block2.key = 10;
	block3.key = 20;

	list<Block> int_list;
	int_list.push_back(block1);
	int_list.push_back(block2);
	int_list.push_back(block3);
	int_list.sort(compare);

	for(list<Block>::iterator list_iter = int_list.begin(); 
	    list_iter != int_list.end(); list_iter++)
	{
	   	Block temp = *list_iter;
		cout << temp.key << endl;
	}

return 0;
}
