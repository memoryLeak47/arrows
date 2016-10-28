#include "Account.hpp"

#include <fstream>

#include "Global.hpp"

std::vector<Account*> Account::accounts;

Account::Account(const std::string& name, const std::string& pwd)
	: name(name), password(pwd), rank(0)
{}

void Account::init()
{
	std::ifstream filestream(ACCOUNTS_FILENAME);

	while (filestream.good())
	{
		std::string readname, readpwd;
		std::getline(filestream, readname);
		std::getline(filestream, readpwd);
		if (readname != "" && readpwd != "")
		{
			Account* a = new Account(readname, readpwd);
			accounts.push_back(a);
		}
	}

	filestream.close();
}

void Account::uninit()
{
	deleteAndClearVector(accounts);
}

Account* Account::authenticate(const std::string& name, const std::string& pass)
{	
	for (unsigned int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i]->getName() == name)
		{
			if (accounts[i]->getPassword() == pass)
				return accounts[i];
			else
				return nullptr;
		}
	}
	return nullptr;
}

bool Account::isNameFree(const std::string& name)
{
	for (unsigned int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i]->getName() == name)
		{
			return false;
		}
	}
	return true;
}

void Account::add(Account* a)
{
	accounts.push_back(a);
	writeAccountsToFile();
}

void Account::writeAccountsToFile()
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
	}
	filestream.close();
}

// public getter
const std::string& Account::getName() { return name; }
const std::string& Account::getPassword() { return password; }
int Account::getRank() { return rank; }
