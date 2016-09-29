#include "Team.hpp"

#include <core/Main.hpp>
#include <misc/Debug.hpp>
#include <misc/Converter.hpp>

std::vector<Team*> Team::teams;

Team::Team(char id, const std::string& name, const std::string& color)
	: id(id), name(name), colorID(Converter::colorStringToInt(color)) // TODO define color id
{}

void Team::init()
{
	if (teams.size() != 0) Debug::warn("Team::init() was already called");
	teams.push_back(new Team(0, "None", "666666"));
	teams.push_back(new Team(1, "Red", "ff0000"));
	teams.push_back(new Team(2, "Blue", "0000ff"));
	teams.push_back(new Team(3, "Green", "00ff00"));
	teams.push_back(new Team(4, "Yellow", "ffff00"));
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

char Team::getID() const
{
	return id;
}

int Team::getColorID() const
{
	return colorID;
}

bool Team::isFriendlyTeam(Team* team) const
{
	return (getID() != 0) && (getID() == team->getID());
}
