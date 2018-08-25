#pragma once

#include "GraphLibCore.hpp"

#ifdef GRAPHLIB_EXPORTS
#define GRAPHLIB_API __declspec(dllexport)
#else
#define GRAPHLIB_API __declspec(dllimport)
#endif

/// <summary>
/// Example exported class.
/// </summary>
class GRAPHLIB_API CGraphLib {
public:
	CGraphLib(void);
};

/// <summary>
/// Example exported function.
/// </summary>
GRAPHLIB_API int fnGraphLib(void);
