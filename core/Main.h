#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#include "Screen.h"
#include "../misc/Account.h"
#include "../network/NetworkDevice.h"
#include "../game/Game.h"
#include "../menu/MenuList.h"
#include "../misc/Debug.h"

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
		Game* game;
		MenuList* menuList;
		NetworkDevice* networkDevice;
		Account* account;
	public:
		Main();
		void run();
		
};

#endif
