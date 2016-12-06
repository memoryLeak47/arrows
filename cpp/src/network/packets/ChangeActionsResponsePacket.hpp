#ifndef __CHANGEACTIONSRESPONSEPACKET_CLASS__
#define __CHANGEACTIONSRESPONSEPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <controller/Actions.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class ChangeActionsResponsePacket : public Packet
{
	public:
		ChangeActionsResponsePacket(int frame_arg, char playerID_arg, Actions actions_arg);
		ChangeActionsResponsePacket(CompressBuffer*);
		virtual ~ChangeActionsResponsePacket() {}

		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
		int getFrame() const;
		char getPlayerID() const;
		Actions getActions() const;
	private:
		int frame;
		char playerID;
		Actions actions;
};

#endif
