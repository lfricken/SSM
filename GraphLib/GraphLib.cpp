#include "GraphLib.hpp"

GRAPHLIB_API int fnGraphLib(void)
{
	int* t = new int;
	return 44;
}

// This is the constructor of a class that has been exported.
// see GraphLib.h for the class definition
CGraphLib::CGraphLib()
{
	return;
}
