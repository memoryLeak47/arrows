#include "Team.hpp"

#include <core/Main.hpp>
#include <misc/Global.hpp>

std::vector<Team*> Team::teams;

Team::Team(TeamID id, const std::string& name, const std::string& color)
	: id(id), name(name), color(color)
{}

void Team::init()
{
	if (teams.size() != 0) Debug::warn("Team::init() was already called");
	#define X(teamID, name, color) teams.push_back(new Team(TeamIDs::teamID, name, (#color)));
	#define Y(teamID, name, color) teams.push_back(new Team(TeamIDs::teamID, name, (#color)));
	#include "TeamID.list"
	#undef X
	#undef Y
}

void Team::uninit()
{
	deleteAndClearVector(teams);
}

Team* Team::get(int id)
{
	if (teams.size() == 0) Debug::warn("Team::get(): Teams not yet initialized");
	return teams[id];
}

unsigned int Team::getAmount()
{
	if (teams.size() == 0) Debug::warn("Team::getAmount(): == 0");
	return teams.size();
}

std::string Team::getName() const
{
	return name;
}

TeamID Team::getID() const
{
	return id;
}

const std::string& Team::getColor() const
{
	return color;
}

bool Team::isFriendlyTeam(Team* team) const
{
	return (getID() != 0) && (getID() == team->getID());
}
