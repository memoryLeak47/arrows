#include "Account.hpp"

#include <fstream>

#include "Debug.hpp"

Account::Account(const std::string& name, const std::string& pwd) : name(name), password(pwd), rank(0)
{}

Account* Account::get(const std::string& name, const std::string& pwd)
{
	std::vector<Account*> accounts = getAccounts();
	Account* account = getByName(name, accounts);
	accounts.clear();
	if (account == NULL)
	{
		return NULL;
	}
	if (account->getPassword() == pwd)
	{
		return account;
	}
	return NULL;
}

void Account::updateAccount(Account* account) // called when user quits arrows
{
	std::vector<Account*> accounts = getAccounts();
	if (!isNameFree(account->getName(), accounts))
	{
		// delete account with name account->getName()
		for (unsigned int i = 0; i < accounts.size(); i++)
		{
			if (accounts[i]->getName() == account->getName())
			{
				accounts.erase(accounts.begin() + i);
				break;
			}
		}
		accounts.push_back(account);
		writeAccountsToFile(accounts);
		accounts.clear();
	}
	else
	{
		Debug::error("account-name not chosen yet");
	}
}


bool Account::add(const std::string& name, const std::string& pwd)
{
	std::vector<Account*> accounts = getAccounts();
	if (isNameFree(name, accounts))
	{
		Account* account = new Account(name, pwd);
		accounts.push_back(account);
		writeAccountsToFile(accounts);
		accounts.clear();
		return true;
	}
	accounts.clear();
	return false;

}

Account* Account::getByName(const std::string& name, const std::vector<Account*>& accounts)
{
	for (unsigned int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i]->getName() == name)
		{
			return accounts[i];
		}
	}
	return NULL;
}

std::vector<Account*>& Account::getAccounts()
{
	std::vector<Account*> accounts;
	std::ifstream filestream(ACCOUNTS_FILENAME);
/*
	if (!filestream.good())
	{
		Debug::warn((std::string)"Account.getAccounts(): can't open " + ACCOUNTS_FILENAME);
		filestream.close();
		return accounts;
	}
*/

	while (filestream.good())
	{
		std::string readname, readpwd;
		std::getline(filestream, readname);
		std::getline(filestream, readpwd);
		Account* a = new Account(readname, readpwd); // TODO muchos memoryleak
		accounts.push_back(a);
	}

	filestream.close();
	static std::vector<Account*> ref = accounts;
	return ref;
}

void Account::writeAccountsToFile(const std::vector<Account*>& accounts)
{
	std::ofstream filestream(ACCOUNTS_FILENAME);
	if (!filestream.good())
	{
		Debug::warn("Account::writeAccountsToFile(): bad filestream");
		filestream.close();
		return;
	}
	for (unsigned int i = 0; i < accounts.size(); i++)
	{
		filestream << accounts[i]->getName() << std::endl;
		filestream << accounts[i]->getPassword() << std::endl;
/*
		std::string namestring = accounts[i]->getName() + "\n";
		std::string pwdstring = accounts[i]->getPassword() + "\n";
		filestream.write(namestring.c_str(), sizeof(namestring.c_str()));
		filestream.write(pwdstring.c_str(), sizeof(pwdstring.c_str()));
*/
	}
	filestream.close();
}

bool Account::isNameFree(const std::string& name, const std::vector<Account*>& accounts)
{
	return (getByName(name, accounts) == NULL);
}


// public getter
const std::string& Account::getName() { return name; }
const std::string& Account::getPassword() { return password; }
int Account::getRank() { return rank; }
