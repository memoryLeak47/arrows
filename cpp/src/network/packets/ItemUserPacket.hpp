#ifndef __ITEMUSERPACKET_CLASS__
#define __ITEMUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class ItemUserPacket : public PlayerPropertyUserPacket
{
	public:
		ItemUserPacket(const std::vector<char>&);
		ItemUserPacket();
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::vector<char>&) override;
		virtual std::string toString() const override;
		virtual CID getCID() const override;
	private:
		std::vector<char> itemIDs;
};

#endif
