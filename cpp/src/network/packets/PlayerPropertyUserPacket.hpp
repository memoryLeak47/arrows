#ifndef __PLAYERPROPERTYUSERPACKET_CLASS__
#define __PLAYERPROPERTYUSERPACKET_CLASS__

#include <vector>

#include "UserPacket.hpp"

class PlayerProperty;

class PlayerPropertyUserPacket : public UserPacket
{
	public:
		virtual ~PlayerPropertyUserPacket() {}
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const = 0;
		virtual void setIDs(const std::string&) = 0;
};

#include "../../player/property/PlayerProperty.hpp"

#endif
