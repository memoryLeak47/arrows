#ifndef __GAMEINTERFACE_CLASS__
#define __GAMEINTERFACE_CLASS__

#include "../menu/NetworkingMenu.hpp"

class GameInterface : public NetworkingMenu
{
	public:
		virtual void tick() override;
};

#endif
