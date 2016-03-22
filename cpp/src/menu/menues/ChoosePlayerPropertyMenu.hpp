#ifndef __CHOOSEPLAYERPROPERTYMENU_CLASS__
#define __CHOOSEPLAYERPROPERTYMENU_CLASS__

#include <vector>

#include "../Menu.hpp"

class LobbyMenu;
class PlayerPropertyUserPacket;
class PlayerProperty;
class PlayerPropertyIcon;
class ChooseIcon;

class ChoosePlayerPropertyMenu : public Menu
{
	public:
		ChoosePlayerPropertyMenu(LobbyMenu*, PlayerPropertyUserPacket*, const std::vector<PlayerProperty*>&);
		virtual ~ChoosePlayerPropertyMenu();
		PlayerPropertyIcon* getFirstVoidSlotIcon() const;
		std::vector<PlayerPropertyIcon*> getSlotIcons() const;
		LobbyMenu* getLobbyMenu() const;
		void okPressed();
		void chooseIconPressed(PlayerProperty*);
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
