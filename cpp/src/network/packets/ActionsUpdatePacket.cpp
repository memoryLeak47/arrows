#include "ActionsUpdatePacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

ActionsUpdatePacket::ActionsUpdatePacket(const Actions actions)
	: actions(actions)
{}

ActionsUpdatePacket::ActionsUpdatePacket(CompressBuffer* buffer)
{
	actions = buffer->cutChar();
}

std::string ActionsUpdatePacket::getCompressString() const
{
	std::string s;
	return s + actions;
}

CompressID ActionsUpdatePacket::getCompressID() const
{
	return ACTIONS_UPDATE_PACKET_CID;
}

Actions ActionsUpdatePacket::getActions() const
{
	return actions;
}
