#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

class NetworkDevice;
class Account;
class MenuList;

#include <string>

class Main
{
	public:
		Main(); // inits
		virtual ~Main(); // uninits

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

#endif
