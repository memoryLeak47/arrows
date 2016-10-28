#ifndef __ACCOUNT_CLASS__
#define __ACCOUNT_CLASS__

#include <string>
#include <vector>

const std::string ACCOUNTS_FILENAME = ".accounts";

class Account
{
	public:
		Account(const std::string&, const std::string&);
		virtual ~Account() {}
		static void init();
		static void uninit();

		static Account* authenticate(const std::string& name, const std::string& pass);
		static bool isNameFree(const std::string& name);
		static void add(Account*);

		const std::string& getName();
		const std::string& getPassword();
		int getRank();
	private:
		static std::vector<Account*> accounts;
		static void writeAccountsToFile();

		std::string name;
		std::string password;
		int rank;
};

#endif
