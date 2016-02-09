#ifndef __CHOOSEPLAYERPROPERTYMENU_CLASS__
#define __CHOOSEPLAYERPROPERTYMENU_CLASS__

#include "../Menu.hpp"

class LobbyMenu;
class PlayerPropertyUserPacket;
class PlayerProperty;
class PlayerPropertyIcon;

class ChoosePlayerPropertyMenu : public Menu
{
	public:
		ChoosePlayerPropertyMenu(LobbyMenu*, PlayerPropertyUserPacket*, const std::vector<PlayerProperty*>&);
	private:
		LobbyMenu* lobby;
		PlayerPropertyUserPacket* slotPacket;
		const std::vector<PlayerProperty*> chooseProperties;
		std::vector<PlayerPropertyIcon*> slotIcons;

};

#include "LobbyMenu.hpp"
#include "../../network/packets/PlayerPropertyUserPacket.hpp"
#include "../../player/property/PlayerProperty.hpp"
#include "../components/PlayerPropertyIcon.hpp"

#endif
