#ifndef __SKILLUSERPACKET_CLASS__
#define __SKILLUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class SkillUserPacket : public PlayerPropertyUserPacket
{
	public:
		SkillUserPacket(const std::vector<char>&);
		SkillUserPacket();
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::vector<char>&) override;
		virtual std::string toString() const override;
		virtual CID getCID() const override;
	private:
		std::vector<char> skillIDs;
};

#endif
