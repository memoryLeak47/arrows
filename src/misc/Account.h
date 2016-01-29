#ifndef __ACCOUNT_CLASS__
#define __ACCOUNT_CLASS__

#define ACCOUNTS_FILENAME ".accounts"

#include <string>
#include <vector>

class Account
{
	public:
		Account(const std::string&, const std::string&);
		static Account* get(const std::string&, const std::string&);
		static void updateAccount(Account*);
		static bool add(const std::string&, const std::string&);

		const std::string& getName();
		const std::string& getPassword();
		int getRank();
	private:
		static Account* getByName(const std::string&, const std::vector<Account*>&);
		static const std::vector<Account*>& getAccounts();
		static void writeAccountsToFile(const std::vector<Account*>&);
		static bool isNameFree(const std::string&, const std::vector<Account*>&);

		std::string name;
		std::string password;
		int rank;
};

#endif
