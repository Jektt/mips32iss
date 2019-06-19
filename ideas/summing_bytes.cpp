#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {

uint32_t data[4];
data[0] = 0x000000aa;
data[1] = 0x000000bb;
data[2] = 0x000000cc;
data[3] = 0x000000dd;

uint32_t result = 0;

// desired output is: 0xddccbbaa

for (int n = 0; n < 4; n++) {
	cout << "We are going to add: " << setfill('0') << setw(8) << hex << (data[n] * pow(2,n*8)) << endl;
	result = result + data[n]*pow(2,n*8);
}

cout << "Result is: " << setfill('0') << setw(8) << hex << result << endl;

return 0;

} 

