#include "MemoryDump.hpp"
#include "GraphLib.hpp"


#include <iostream>
using namespace std;


int main()
{
	cout << fnGraphLib();
	DEBUGOUTPUT("something happened");

	_CrtDumpMemoryLeaks();
	return 0;
}

