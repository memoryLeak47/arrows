#include "Avatar.hpp"

#include "../../../core/Main.hpp"
#include "../../../misc/Converter.hpp"
#include "../../../misc/Debug.hpp"
#include "avatars/Archer.hpp"
#include "avatars/Rogue.hpp"

std::vector<Avatar*> Avatar::avatars;

extern const int ARCHER_AID = 0; // skills can define class of owner with this id
extern const int ROGUE_AID = 0; // skills can define class of owner with this id

void Avatar::init()
{
	avatars.push_back(new Archer());
	avatars.push_back(new Rogue());
}

void Avatar::uninit()
{
	deleteAndClearVector(avatars);
}

Avatar* Avatar::get(int id)
{
	Debug::warnIf(id < 0 || id >= getAmount(), "Avatar::get(): id(" + Converter::intToString(id) + ") out of range");
	return avatars[id];
}

int Avatar::getAmount()
{
	return avatars.size();
}

const std::vector<Avatar*> Avatar::getAllAvatars()
{
	return avatars;
}

int Avatar::getMassStat() const
{
	return 20;
}

float Avatar::getHealthStat() const
{
	return 20;
}
