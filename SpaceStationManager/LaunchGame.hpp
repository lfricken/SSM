#pragma once

#include "stdafx.hpp"
#include "Team.hpp"

/// <summary>
/// Sent to all game instances to load the right level.
/// </summary>
struct GameLaunchData
{
	/// <summary>
	/// Name of folder that contains level.
	/// </summary>
	String levelDirectory;
};

