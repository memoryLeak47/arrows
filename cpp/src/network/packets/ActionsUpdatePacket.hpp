#ifndef __ACTIONSUPDATEPACKET_CLASS__
#define __ACTIONSUPDATEPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <controller/Actions.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class ActionsUpdatePacket : public Packet
{
	public:
		ActionsUpdatePacket(Actions actions);
		ActionsUpdatePacket(CompressBuffer*);
		virtual ~ActionsUpdatePacket() {}

		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
		Actions getActions() const;
	private:
		Actions actions;
};

#endif
