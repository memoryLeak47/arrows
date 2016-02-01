#ifndef __LOGINUSERPACKET_CLASS__
#define __LOGINUSERPACKET_CLASS__

#include <string>

#include "UserPacket.hpp"

class LoginUserPacket : public UserPacket
{
	public:
		LoginUserPacket(const std::string&, int);
		std::string toString() const override;
		CID getCID() const override;

		std::string getName() const;
		int getRank() const;
	private:
		std::string name;
		int rank;
};

#endif
