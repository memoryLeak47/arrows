#include "ActionsUpdatePacket.hpp"

ActionsUpdatePacket::ActionsUpdatePacket(const Actions actions)
	: actions(actions)
{}

ActionsUpdatePacket::ActionsUpdatePacket(CompressBuffer* buffer)
{
	actions = buffer->cutInt();
}

std::string ActionsUpdatePacket::toString() const
{
	std::string s;
	return s + actions;
}

CID ActionsUpdatePacket::getCID() const
{
	return ACTIONS_UPDATE_PACKET_CID;
}

Actions ActionsUpdatePacket::getActions() const
{
	return actions;
}
