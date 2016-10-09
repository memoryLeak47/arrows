#ifndef __AVATARUSERPACKET_CLASS__
#define __AVATARUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class CompressBuffer;

class AvatarUserPacket : public PlayerPropertyUserPacket
{
	public:
		AvatarUserPacket(char);
		AvatarUserPacket();
		AvatarUserPacket(CompressBuffer*);
		bool isValid() const;
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::string&) override;
		virtual std::string getCompressString() const override;
		virtual CID getCID() const override;
		char getAvatarID() const;
	private:
		char avatarID;

};

#include <misc/compress/CompressBuffer.hpp>

#endif
