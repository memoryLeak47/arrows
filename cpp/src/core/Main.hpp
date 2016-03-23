#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#define MAX_TICK_COUNTER 2000
#define MAX_RENDER_COUNTER 2000

#define FRAME_INTERVAL 40
#define TILESIZE 40
#define DRAG_X 1.9f
#define DRAG_Y 1.02f
#define GRAVITY 0.04f
#define STANDART_JUMPPOWER 0.6f
#define STANDART_ACCELERATION 0.18f

#define deleteAndNULL(x) delete x; x = NULL
#define deleteAndClearVector(x) for (int i = 0; i < x.size(); i++) { delete x[i]; } x.clear();

#include <string>

class MenuList;
class Game;
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
	private:
		static Game* game;
		static MenuList* menuList;
		static NetworkDevice* networkDevice;
		static Account* account;
		static bool running;
		static void run();
		static void tick();
		static void render();
};

#include "../menu/MenuList.hpp"
#include "../game/Game.hpp"
#include "../network/NetworkDevice.hpp"
#include "../misc/Account.hpp"

#endif
