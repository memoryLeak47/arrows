#ifndef __LOGINUSERPACKET_CLASS__
#define __LOGINUSERPACKET_CLASS__

#include <string>

#include "UserPacket.h"

class LoginUserPacket : public UserPacket
{
	private:
		std::string name;
		int rank;
};

#endif
