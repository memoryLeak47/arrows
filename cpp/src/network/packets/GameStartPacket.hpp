#ifndef __GAMESTARTPACKET_CLASS__
#define __GAMESTARTPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class GameStartPacket : public Packet
{
	public:
		GameStartPacket(long);
		GameStartPacket(CompressBuffer*);
		virtual ~GameStartPacket() {}

		virtual std::string getCompressString() const override;
		virtual CompressID getCompressID() const override;

		long getUnixBeginTime() const;
	private:
		long unixBeginTime; // milliseconds
};

#endif
