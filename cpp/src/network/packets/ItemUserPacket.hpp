#ifndef __ITEMUSERPACKET_CLASS__
#define __ITEMUSERPACKET_CLASS__

#include "PlayerPropertyUserPacket.hpp"

class CompressBuffer;

class ItemUserPacket : public PlayerPropertyUserPacket
{
	public:
		ItemUserPacket(const std::string&);
		ItemUserPacket(CompressBuffer*);
		ItemUserPacket();
		bool isValid() const;
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::string&) override;
		virtual std::string getCompressString() const override;
		virtual CID getCID() const override;
	private:
		std::string itemIDs;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
