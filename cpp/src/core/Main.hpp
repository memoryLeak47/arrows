#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#include <string>

class MenuList;
class NetworkDevice;
class Account;

class Main
{
	public:
		Main();
		virtual ~Main();
		static NetworkDevice* getNetworkDevice();
		static void setAccount(Account*);
		static Account* getAccount();
		static void logout();
		static void exit();
		static MenuList* getMenuList();
		static std::string getName();
		static int getRank();
		static bool isRunning();
	private:
		static MenuList* menuList;
		static NetworkDevice* networkDevice;
		static Account* account;
		static bool running;
		static void run();
		static void tick();
		static void render();
};

#include "../menu/MenuList.hpp"
#include "../network/NetworkDevice.hpp"
#include "../misc/Account.hpp"

#endif
