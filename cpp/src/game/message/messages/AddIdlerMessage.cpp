#include "AddIdlerMessage.hpp"

AddIdlerMessage::AddIdlerMessage(Idler* i)
	: idler(i)
{}

AddIdlerMessage::~AddIdlerMessage()
{}

Idler* AddIdlerMessage::getIdler() const
{
	return idler;
}

bool AddIdlerMessage::isBroadcast() const
{
	return false;
}
