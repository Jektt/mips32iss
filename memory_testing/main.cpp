#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>

#include "memory.h"

using namespace std;

int main () {

	memory some_mem(false, false, 0, 0);

	some_mem.disp_mem();

	some_mem.show_address(0x00045008);
	some_mem.set_address(0x00045008, 999);
	some_mem.show_address(0x00045008);


	return 0;
}
