#ifndef __SKILLPACKET_CLASS__
#define __SKILLPACKET_CLASS__

class CompressBuffer;
class PlayerProperty;

#include "PlayerPropertyPacket.hpp"
#include <string>
#include <vector>
#include <misc/compress/CompressID.hpp>

class SkillPacket : public PlayerPropertyPacket
{
	public:
		SkillPacket(const std::string&);
		SkillPacket(CompressBuffer*);
		SkillPacket();
		bool isValid() const;
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::string&) override;
		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
	private:
		std::string skillIDs;
};

#endif
