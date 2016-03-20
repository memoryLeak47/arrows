#ifndef __SKILLUSERPACKET_CLASS__
#define __SKILLUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class CompressBuffer;

class SkillUserPacket : public PlayerPropertyUserPacket
{
	public:
		SkillUserPacket(const std::string&);
		SkillUserPacket(CompressBuffer*);
		SkillUserPacket();
		bool isValid() const;
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::string&) override;
		virtual std::string toString() const override;
		virtual CID getCID() const override;
	private:
		std::string skillIDs;
};

#include "../../misc/compress/CompressBuffer.hpp"

#endif
