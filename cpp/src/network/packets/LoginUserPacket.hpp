#ifndef __LOGINUSERPACKET_CLASS__
#define __LOGINUSERPACKET_CLASS__

#include <string>

#include "UserPacket.hpp"

class CompressBuffer;

class LoginUserPacket : public UserPacket
{
	public:
		LoginUserPacket(const std::string&, int);
		LoginUserPacket(CompressBuffer*);
		std::string getCompressString() const override;
		CID getCID() const override;

		std::string getName() const;
		int getRank() const;
	private:
		std::string name;
		int rank;
};

#include <misc/compress/CompressBuffer.hpp>

#endif
