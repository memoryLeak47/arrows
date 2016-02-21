#include "Avatar.hpp"

#include "../../../misc/Converter.hpp"
#include "../../../misc/Debug.hpp"
#include "avatars/Archer.hpp"

std::vector<Avatar*> Avatar::avatars;

const int ARCHER_ID = 0; // skills can define class of owner with this id

void Avatar::init()
{
	avatars.push_back(new Archer());
	avatars.back()->setID(ARCHER_ID);
}

void Avatar::uninit()
{
	avatars.clear();
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

void Avatar::setID(char id)
{
	this->id = id;
}

char Avatar::getID() const
{
	return id;
}

int Avatar::getMassStat() const
{
	return 20;
}

float Avatar::getHealthStat() const
{
	return 20;
}
