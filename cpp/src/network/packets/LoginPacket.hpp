#ifndef __LOGINPACKET_CLASS__
#define __LOGINPACKET_CLASS__

class CompressBuffer;

#include <network/Packet.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class LoginPacket : public Packet
{
	public:
		LoginPacket(const std::string&, int);
		LoginPacket(CompressBuffer*);
		std::string getCompressString() const override;
		CompressID getCompressID() const override;

		std::string getName() const;
		int getRank() const;
	private:
		std::string name;
		int rank;
};

#endif
