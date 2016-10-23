#ifndef __SKILLUSERPACKET_CLASS__
#define __SKILLUSERPACKET_CLASS__

class CompressBuffer;
class PlayerProperty;

#include "PlayerPropertyUserPacket.hpp"
#include <string>
#include <vector>
#include <misc/compress/CompressID.hpp>

class SkillUserPacket : public PlayerPropertyUserPacket
{
	public:
		SkillUserPacket(const std::string&);
		SkillUserPacket(CompressBuffer*);
		SkillUserPacket();
		bool isValid() const;
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::string&) override;
		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
	private:
		std::string skillIDs;
};

#endif
