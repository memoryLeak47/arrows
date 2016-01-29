#include "Account.h"

#include <fstream>

#include "Debug.h"

Account::Account(const std::string& name, const std::string& pwd) : name(name), password(pwd), rank(0)
{}

Account* Account::get(const std::string& name, const std::string& pwd)
{
	std::vector<Account*> accounts = getAccounts();
	Account* account = getByName(name, accounts);
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
		for (int i = 0; i < accounts.size(); i++)
		{
			if (accounts[i]->getName() == account->getName())
			{
				accounts.erase(accounts.begin() + i);
				break;
			}
		}
		accounts.push_back(account);
		writeAccountsToFile(accounts);
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
		return true;
	}
	return false;

}

Account* Account::getByName(const std::string& name, const std::vector<Account*>& accounts)
{
	for (int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i]->getName() == name)
		{
			return accounts[i];
		}
	}
	return NULL;
}

const std::vector<Account*>& Account::getAccounts()
{
	std::ifstream filestream(ACCOUNTS_FILENAME);
	if (!filestream.good())
	{
		filestream.close();
		const std::vector<Account*>& v = std::vector<Account*>();
		return v;
	}
	filestream.close();

	const std::vector<Account*>& accounts = std::vector<Account*>(); // = (std::vector<Account*>) Serializer::fileToObject(ACCOUNTS_FILENAME);
	return accounts;
}

void Account::writeAccountsToFile(const std::vector<Account*>& accounts)
{
	// Serializer::objectToFile(accounts, new File(accounts_filename));
}

bool Account::isNameFree(const std::string& name, const std::vector<Account*>& accounts)
{
	return (getByName(name, accounts) == NULL);
}

// public getter
const std::string& Account::getName() { return name; }
const std::string& Account::getPassword() { return password; }
int Account::getRank() { return rank; }
