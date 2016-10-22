#ifndef __ACTIONSUPDATEUSERPACKET_CLASS__
#define __ACTIONSUPDATEUSERPACKET_CLASS__

#include <network/packets/UserPacket.hpp>
#include <controller/Controller.hpp>

class ActionsUpdateUserPacket : public UserPacket
{
	public:
		ActionsUpdateUserPacket(Actions actions);
		ActionsUpdateUserPacket(CompressBuffer*);
		virtual ~ActionsUpdateUserPacket() {}

		virtual std::string getCompressString() const override;
		virtual CID getCID() const override;
		Actions getActions() const;
	private:
		Actions actions;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
