#pragma once

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <Windows.h>
#include <iostream>
#include <sstream>

#ifdef DEBUGGINGLIB_EXPORTS
#define DEBUGGINGLIB_API __declspec(dllexport)
#else
#define DEBUGGINGLIB_API __declspec(dllimport)
#endif

/// <summary>
/// Example exported function.
/// </summary>
void LibDebugOutput(std::string file, int line, std::string message)
{
	std::wostringstream os_;
	if(line != -1)
	{
		os_ << file.c_str() << "(" << line << "): ";
	}
	os_ << message.c_str() << std::endl;
	OutputDebugStringW(os_.str().c_str());
}

#define SIMPLEOUTPUT(message) \
LibDebugOutput("", -1, message)

#define DEBUGOUTPUT(message) \
LibDebugOutput(__FILE__, __LINE__, message)

