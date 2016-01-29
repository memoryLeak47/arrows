#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#define MAX_TICK_COUNTER 2000
#define MAX_RENDER_COUNTER 2000

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

class MenuList;
class Game;
class NetworkDevice;
class Account;

class Main
{
	public:
		static const int FRAME_INTERVAL = 40;
		static const int TILESIZE = 40;

		static const float DRAG_X = 1.9f;
		static const float DRAG_Y = 1.02f;
		static const float GRAVITY = 0.04f;
		static const float STANDART_JUMPPOWER = 0.6f;
		static const float STANDART_ACCELERATION = 0.18f;
	private:
		static Game* game;
		static MenuList* menuList;
		static NetworkDevice* networkDevice;
		static Account* account;
		static bool running;
		static void run();
		static void tick();
		static void render();
	public:
		Main();
		~Main();
		static void setAccount(Account*);
		static void exit();
		static MenuList* getMenuList();
};

#include "../menu/MenuList.h"
#include "../misc/Account.h"
#include "../network/NetworkDevice.h"
#include "../game/Game.h"

#endif
