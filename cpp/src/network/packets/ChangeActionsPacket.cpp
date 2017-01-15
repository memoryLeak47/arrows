#include "ChangeActionsPacket.hpp"

#include <misc/compress/CompressBuffer.hpp>

ChangeActionsPacket::ChangeActionsPacket(const Actions actions, int frameNumber)
	: actions(actions), frameNumber(frameNumber)
{}

ChangeActionsPacket::ChangeActionsPacket(CompressBuffer* buffer)
{
	actions = buffer->cutChar();
	frameNumber = buffer->cutInt();
}

std::string ChangeActionsPacket::getCompressString() const
{
	std::string s;
	return s + actions + compressInt(frameNumber);
}

CompressID ChangeActionsPacket::getCompressID() const
{
	return CHANGE_ACTIONS_PACKET_CID;
}

Actions ChangeActionsPacket::getActions() const
{
	return actions;
}

int ChangeActionsPacket::getFrameNumber() const
{
	return frameNumber;
}
