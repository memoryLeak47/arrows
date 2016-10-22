#ifndef __PLAYERPROPERTYUSERPACKET_CLASS__
#define __PLAYERPROPERTYUSERPACKET_CLASS__

class PlayerProperty;

#include <network/packets/UserPacket.hpp>
#include <vector>
#include <string>

class PlayerPropertyUserPacket : public UserPacket
{
	public:
		virtual ~PlayerPropertyUserPacket() {}
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const = 0;
		virtual void setIDs(const std::string&) = 0;
};

#endif
