#ifndef __LOGINUSERPACKET_CLASS__
#define __LOGINUSERPACKET_CLASS__

#include <string>

#include "UserPacket.hpp"

class LoginUserPacket : public UserPacket
{
	private:
		std::string name;
		int rank;
};

#endif
