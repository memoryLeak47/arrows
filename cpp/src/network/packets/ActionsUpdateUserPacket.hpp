#ifndef __ACTIONSUPDATEUSERPACKET_CLASS__
#define __ACTIONSUPDATEUSERPACKET_CLASS__

class CompressBuffer;

#include <network/packets/UserPacket.hpp>
#include <controller/Actions.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class ActionsUpdateUserPacket : public UserPacket
{
	public:
		ActionsUpdateUserPacket(Actions actions);
		ActionsUpdateUserPacket(CompressBuffer*);
		virtual ~ActionsUpdateUserPacket() {}

		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
		Actions getActions() const;
	private:
		Actions actions;
};

#endif
