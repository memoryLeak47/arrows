#include "ActionsUpdateUserPacket.hpp"

ActionsUpdateUserPacket::ActionsUpdateUserPacket(const Actions actions)
	: actions(actions)
{}

ActionsUpdateUserPacket::ActionsUpdateUserPacket(CompressBuffer* buffer)
{
	actions = buffer->cutInt();
}

std::string ActionsUpdateUserPacket::toString() const
{
	std::string s;
	return s + actions;
}

CID ActionsUpdateUserPacket::getCID() const
{
	return ACTIONS_UPDATE_USER_PACKET_CID;
}

Actions ActionsUpdateUserPacket::getActions() const
{
	return actions;
}
