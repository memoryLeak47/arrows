#ifndef __ITEMUSERPACKET_CLASS__
#define __ITEMUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class ItemUserPacket : public PlayerPropertyUserPacket
{
	public:
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::vector<char>&) override;
	private:
		char itemIDs[3];
};

#endif
