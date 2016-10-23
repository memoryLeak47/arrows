#ifndef __LOGINUSERPACKET_CLASS__
#define __LOGINUSERPACKET_CLASS__

class CompressBuffer;

#include <network/packets/UserPacket.hpp>
#include <string>
#include <misc/compress/CompressID.hpp>

class LoginUserPacket : public UserPacket
{
	public:
		LoginUserPacket(const std::string&, int);
		LoginUserPacket(CompressBuffer*);
		std::string getCompressString() const override;
		CompressID getCompressID() const override;

		std::string getName() const;
		int getRank() const;
	private:
		std::string name;
		int rank;
};

#endif
