#include "MemoryDump.hpp"


#include <iostream>
using namespace std;


int main()
{
	SIMPLEOUTPUT("\n");
	SIMPLEOUTPUT("Program Started.");

	DEBUGOUTPUT("something happened");

	_CrtDumpMemoryLeaks();

	SIMPLEOUTPUT("Program ended.");
	SIMPLEOUTPUT("\n");
	return 0;
}

