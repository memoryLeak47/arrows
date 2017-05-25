#include "DestroyMessage.hpp"

DestroyMessage::DestroyMessage(DynamicEntity* e)
	: entity(e)
{}

DestroyMessage::~DestroyMessage()
{}

DynamicEntity* DestroyMessage::getEntity() const
{
	return entity;
}

bool DestroyMessage::isBroadcast() const
{
	return true;
}
