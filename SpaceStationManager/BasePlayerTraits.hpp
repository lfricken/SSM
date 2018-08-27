#pragma once

#include "stdafx.hpp"
#include "Team.hpp"

/// \brief Holds information about each player.
/// 
/// Inherited by Player (local player) and Connection (host has one for each human player).
class BasePlayerTraits
{
public:
	BasePlayerTraits(const String& rName);
	virtual ~BasePlayerTraits();

	///Set our team.
	void setTeam(Team team);
	///Return which team we are on.
	Team getTeam() const;
	
	///Set in game name, seen by other players.
	void setName(const String& rTitle);
	///Get in game name, seen by other players.
	const String& getName() const;

protected:
	///Which controller do we have, 0, 1, 2, ect.(points to a controller in the list)
	int m_controller;

private:
	///In game name.
	String m_name;
	///Which team this player is on.
	Team m_team;
};
