// GraphLib.cpp : Defines the exported functions for the DLL application.
//

#include "GraphLib.hpp"


// This is an example of an exported variable
GRAPHLIB_API int nGraphLib = 0;

/// <summary>
/// Example exported function.
/// </summary>
GRAPHLIB_API int fnGraphLib(void)
{
	return 44;
}

// This is the constructor of a class that has been exported.
// see GraphLib.h for the class definition
CGraphLib::CGraphLib()
{
	return;
}
