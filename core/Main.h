#ifndef __MAIN_CLASS__
#define __MAIN_CLASS__

#include "../misc/Account.h"
#include "../network/NetworkDevice.h"
#include "../game/Game.h"
#include "../menu/MenuList.h"

class Main
{
	private:
		Game game;
		MenuList menuList;
		NetworkDevice networkDevice;
		Account account;
	public:
		Main();
		void run();
		
};

#endif
