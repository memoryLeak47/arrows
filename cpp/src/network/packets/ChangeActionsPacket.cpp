#include "ChangeActionsPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

ChangeActionsPacket::ChangeActionsPacket(const Actions actions)
	: actions(actions)
{}

ChangeActionsPacket::ChangeActionsPacket(CompressBuffer* buffer)
{
	actions = buffer->cutChar();
}

std::string ChangeActionsPacket::getCompressString() const
{
	std::string s;
	return s + actions;
}

CompressID ChangeActionsPacket::getCompressID() const
{
	return CHANGE_ACTIONS_PACKET_CID;
}

Actions ChangeActionsPacket::getActions() const
{
	return actions;
}
