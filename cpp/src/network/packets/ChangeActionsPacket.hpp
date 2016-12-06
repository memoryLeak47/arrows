#ifndef __CHANGEACTIONSPACKET_CLASS__
#define __CHANGEACTIONSPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <controller/Actions.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class ChangeActionsPacket : public Packet
{
	public:
		ChangeActionsPacket(Actions actions);
		ChangeActionsPacket(CompressBuffer*);
		virtual ~ChangeActionsPacket() {}

		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;
		Actions getActions() const;
	private:
		Actions actions;
};

#endif
