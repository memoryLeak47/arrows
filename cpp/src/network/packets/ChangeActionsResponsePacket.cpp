#include "ChangeActionsResponsePacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

ChangeActionsResponsePacket::ChangeActionsResponsePacket(int frame_arg, char playerID_arg, Actions actions_arg)
	: frame(frame_arg), playerID(playerID_arg), actions(actions_arg)
{}

ChangeActionsResponsePacket::ChangeActionsResponsePacket(CompressBuffer* buffer)
	: frame(buffer->cutInt()), playerID(buffer->cutChar()), actions((Actions) buffer->cutChar())
{}

std::string ChangeActionsResponsePacket::getCompressString() const
{
	return compressInt(frame) + playerID + (char) actions;
}

CompressID ChangeActionsResponsePacket::getCompressID() const
{
	return CHANGE_ACTIONS_RESPONSE_PACKET_CID;
}

int ChangeActionsResponsePacket::getFrame() const { return frame; }
char ChangeActionsResponsePacket::getPlayerID() const { return playerID; }
Actions ChangeActionsResponsePacket::getActions() const { return actions; }
