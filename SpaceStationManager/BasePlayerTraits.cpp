#include "BasePlayerTraits.hpp"
#include "Message.hpp"
#include "Globals.hpp"
#include "IOManager.hpp"

BasePlayerTraits::BasePlayerTraits(const String& rName)
{
	m_team = Team::One;
	m_name = rName;
}
BasePlayerTraits::~BasePlayerTraits()
{

}
void BasePlayerTraits::setName(const String& rTitle)
{
	m_name = rTitle;
}
const String& BasePlayerTraits::getName() const
{
	return m_name;
}
void BasePlayerTraits::setTeam(Team team)
{
	m_team = team;
}
Team BasePlayerTraits::getTeam() const
{
	return m_team;
}

