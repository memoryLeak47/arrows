#include "AddIdlerMessage.hpp"

#include <game/message/MessageListener.hpp>

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

void AddIdlerMessage::applyTo(MessageListener* l)
{
	l->applyMessage(*this);
}
