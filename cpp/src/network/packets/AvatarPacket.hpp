#ifndef __AVATARPACKET_CLASS__
#define __AVATARPACKET_CLASS__

class CompressBuffer;
class PlayerProperty;

#include "PlayerPropertyPacket.hpp"
#include <vector>
#include <string>
#include <misc/compress/CompressID.hpp>

class AvatarPacket : public PlayerPropertyPacket
{
	public:
		AvatarPacket(char);
		AvatarPacket();
		AvatarPacket(CompressBuffer*);
		bool isValid() const;
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::string&) override;
		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
		char getAvatarID() const;
	private:
		char avatarID;

};

#endif
