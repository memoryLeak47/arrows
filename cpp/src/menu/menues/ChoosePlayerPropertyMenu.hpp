#ifndef __CHOOSEPLAYERPROPERTYMENU_CLASS__
#define __CHOOSEPLAYERPROPERTYMENU_CLASS__

class LobbyMenu;
class PlayerPropertyPacket;
class PlayerProperty;
class PlayerPropertyIcon;

#include <menu/Menu.hpp>
#include <vector>

class ChoosePlayerPropertyMenu : public Menu
{
	public:
		ChoosePlayerPropertyMenu(LobbyMenu*, PlayerPropertyPacket*, const std::vector<PlayerProperty*>&);
		virtual ~ChoosePlayerPropertyMenu();

		void tick() override; // => lobby->tick()

		PlayerPropertyIcon* getFirstVoidSlotIcon() const;
		const std::vector<PlayerPropertyIcon*>& getSlotIcons() const;
		LobbyMenu* getLobbyMenu() const;
		void okPressed();
		void chooseIconPressed(PlayerProperty*);
	private:
		LobbyMenu* lobby;
		PlayerPropertyPacket* slotPacket;
		const std::vector<PlayerProperty*> chooseProperties;
		std::vector<PlayerPropertyIcon*> slotIcons;
};

#endif
