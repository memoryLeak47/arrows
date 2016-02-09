#ifndef __PLAYERPROPERTYUSERPACKET_CLASS__
#define __PLAYERPROPERTYUSERPACKET_CLASS__

#include <vector>

#include "UserPacket.hpp"

class PlayerProperty;

class PlayerPropertyUserPacket : public UserPacket
{
	public:
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const = 0;
		virtual void setIDs(const std::vector<char>&) = 0;
};

#include "../../player/property/PlayerProperty.hpp"

#endif
