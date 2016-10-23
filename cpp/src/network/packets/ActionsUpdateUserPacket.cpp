#include "ActionsUpdateUserPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

ActionsUpdateUserPacket::ActionsUpdateUserPacket(const Actions actions)
	: actions(actions)
{}

ActionsUpdateUserPacket::ActionsUpdateUserPacket(CompressBuffer* buffer)
{
	actions = buffer->cutChar();
}

std::string ActionsUpdateUserPacket::getCompressString() const
{
	std::string s;
	return s + actions;
}

CompressID ActionsUpdateUserPacket::getCompressID() const
{
	return ACTIONS_UPDATE_USER_PACKET_CID;
}

Actions ActionsUpdateUserPacket::getActions() const
{
	return actions;
}
