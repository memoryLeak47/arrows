#include "RestrictedGameInterface.hpp"

#include <game/GameInterface.hpp>

RestrictedGameInterface::RestrictedGameInterface(GameInterface* gi)
	: gameInterface(gi)
{}

void RestrictedGameInterface::addIdler(Idler* i)
{
	gameInterface->mainFrame.idlers.push_back(i);
}
