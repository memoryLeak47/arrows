#ifndef __AVATARUSERPACKET_CLASS__
#define __AVATARUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class AvatarUserPacket : public PlayerPropertyUserPacket
{
	public:
		AvatarUserPacket(char);
		AvatarUserPacket();
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::vector<char>&) override;
		virtual std::string toString() const override;
		virtual CID getCID() const override;
	private:
		char avatarID;

};

#endif
