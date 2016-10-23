#ifndef __ITEMPACKET_CLASS__
#define __ITEMPACKET_CLASS__

class CompressBuffer;
class PlayerProperty;

#include <network/packets/PlayerPropertyPacket.hpp>
#include <string>
#include <vector>
#include <misc/compress/CompressID.hpp>

class ItemPacket : public PlayerPropertyPacket
{
	public:
		ItemPacket(const std::string&);
		ItemPacket(CompressBuffer*);
		ItemPacket();
		bool isValid() const;
		virtual const std::vector<PlayerProperty*> getPlayerProperties() const override;
		virtual void setIDs(const std::string&) override;
		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
	private:
		std::string itemIDs;
};

#endif
