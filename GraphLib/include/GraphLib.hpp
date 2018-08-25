#pragma once

#include "GraphLib.hpp"
#ifdef GRAPHLIB_EXPORTS
#define GRAPHLIB_API __declspec(dllexport)
#else
#define GRAPHLIB_API __declspec(dllimport)
#endif


class GRAPHLIB_API CGraphLib {
public:
	CGraphLib(void);
};

extern GRAPHLIB_API int nGraphLib;

GRAPHLIB_API int fnGraphLib(void);
