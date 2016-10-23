#ifndef __PLAYERPROPERTYPACKET_CLASS__
#define __PLAYERPROPERTYPACKET_CLASS__

class PlayerProperty;

#include <network/Packet.hpp>
#include <vector>
#include <string>

class PlayerPropertyPacket : public Packet
{
	public:
		virtual ~PlayerPropertyPacket() {}
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const = 0;
		virtual void setIDs(const std::string&) = 0;
};

#endif
