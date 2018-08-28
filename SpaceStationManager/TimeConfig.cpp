#include "TimeConfig.hpp"



TimeConfig::TimeConfig(float _worldTimeStep)
{
	worldTimeStep = _worldTimeStep;
}
TimeConfig::~TimeConfig()
{

}
float TimeConfig::getWorldTimeStep() const
{
	return worldTimeStep;
}
