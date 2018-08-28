#pragma once
#include "OOCore.hpp"

class TimeConfig
{
public:
	TimeConfig(float _worldTimeStep);
	~TimeConfig();

	/// <summary>
	/// Instance of this class.
	/// </summary>
	static sp<TimeConfig> Instance;

	/// <summary>
	/// How much time should pass in game per world tick.
	/// </summary>
	float getWorldTimeStep() const;

private:
	float worldTimeStep;
};

