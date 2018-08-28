#pragma once

#include "stdafx.hpp"
#include "Globals.hpp"

/// <summary>
/// Game conversions.
/// </summary>
class Convert
{
public:

	template<typename T>
	/// <summary>
	/// Convert from screen to universe coordinates.
	/// </summary>
	static T screenToUniverse(const T& value)
	{
		return value * screenToUniverseRatio;
	}

	template<typename T>
	/// <summary>
	/// Convert from universe to screen coordinates.
	/// </summary>
	static T universeToScreen(const T& value)
	{
		return value * universeToScreenRatio;
	}

private:

	/// <summary>
	/// Size in pixels of one grid piece.
	/// </summary>
	static const int screenToUniverseRatio;

	/// <summary>
	/// Size in grid pieces of one pixel.
	/// </summary>
	static const float universeToScreenRatio;
};