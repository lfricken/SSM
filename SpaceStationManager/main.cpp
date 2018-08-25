#include "MemoryDump.hpp"
#include "GraphLib.hpp"


#include <iostream>
using namespace std;


int main()
{
	cout << fnGraphLib();

	_CrtDumpMemoryLeaks();
	return 0;
}

