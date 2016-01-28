#ifndef __ACCOUNT_CLASS__
#define __ACCOUNT_CLASS__

#include <string>

class Account
{
	public:
		static Account* get(const std::string&, const std::string&);
		static bool add(const std::string&, const std::string&);
};

#endif
