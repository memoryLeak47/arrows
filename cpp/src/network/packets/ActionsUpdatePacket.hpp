#ifndef __ACTIONSUPDATEPACKET_CLASS__
#define __ACTIONSUPDATEPACKET_CLASS__

#include <network/Packet.hpp>
#include <controller/Controller.hpp>

class ActionsUpdatePacket : public Packet
{
	public:
		ActionsUpdatePacket(Actions actions);
		ActionsUpdatePacket(CompressBuffer*);
		virtual ~ActionsUpdatePacket() {} // don't delete the LobbyPlayers
		virtual std::string toString() const override;
		virtual CID getCID() const override;
		Actions getActions() const;
	private:
		Actions actions;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
