#include "ChoosePlayerPropertyMenu.hpp"

#include "../../core/Screen.hpp"
#include "../../core/Main.hpp"
#include "../../misc/Converter.hpp"
#include "../../misc/Debug.hpp"
#include "../components/BackButton.hpp"

class SlotIcon : public PlayerPropertyIcon
{
	public:
		SlotIcon(ChoosePlayerPropertyMenu* c, PlayerProperty* p, const PixelRect& r) : PlayerPropertyIcon(c, r, p) {}
		virtual void onClick(int mouseButton) override
		{
			setPlayerProperty(NULL);
		}
};

class ChooseIcon : public PlayerPropertyIcon
{
	public:
		ChooseIcon(ChoosePlayerPropertyMenu* c, const PixelRect& r, PlayerProperty* p) : PlayerPropertyIcon(c, r, p) {}
		virtual void onClick(int mouseButton) override
		{
			dynamic_cast<ChoosePlayerPropertyMenu*>(getParent())->chooseIconPressed(getPlayerProperty());
		}
};

class OkButton : public Button
{
	public:
		OkButton(ChoosePlayerPropertyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
		virtual void onPress() override
		{
			dynamic_cast<ChoosePlayerPropertyMenu*>(getParent())->okPressed();
		}
	
};

ChoosePlayerPropertyMenu::ChoosePlayerPropertyMenu(LobbyMenu* lobbyMenu, PlayerPropertyUserPacket* packet, const std::vector<PlayerProperty*>& props)
	: chooseProperties(props)
{
	if (lobbyMenu == NULL) Debug::error("ChoosePlayerPropertyMenu::ChoosePlayerPropertyMenu(): lobbyMenu == NULL");
	if (packet == NULL) Debug::error("ChoosePlayerPropertyMenu::ChoosePlayerPropertyMenu(): packet == NULL");

	lobby = lobbyMenu;
	slotPacket = packet; // copy-constructor of packet already used when this constructor is called

	// Slot Icons
	for (unsigned int i = 0; i < slotPacket->getPlayerProperties().size(); i++)
	{
		PlayerPropertyIcon* icon = new SlotIcon(this, slotPacket->getPlayerProperties()[i], PixelRect(60 + i * (PlayerPropertyIcon::getSize().getX() + 15), 40, PlayerPropertyIcon::getSize().getX(), PlayerPropertyIcon::getSize().getY()));
		addComponent(icon);
		slotIcons.push_back(icon);
	}

	// Choose Icons
	for (unsigned int i = 0; i < chooseProperties.size(); i++)
	{
		PlayerPropertyIcon* icon = new ChooseIcon(this, PixelRect(40 + i * (PlayerPropertyIcon::getSize().getX() + 5), 140, PlayerPropertyIcon::getSize().getX(), PlayerPropertyIcon::getSize().getY()), chooseProperties[i]);
		addComponent(icon);
	}

	// Ok Button
	addComponent(new OkButton(this, PixelRect(100, Screen::getSize().getY()-100, 30, 60), "Ok"));

	// Back Button
	addComponent(new BackButton(this, PixelVector(300, Screen::getSize().getY()-100)));
}

ChoosePlayerPropertyMenu::~ChoosePlayerPropertyMenu()
{
	deleteAndNULL(slotPacket);
}

PlayerPropertyIcon* ChoosePlayerPropertyMenu::getFirstVoidSlotIcon() const
{
	for (unsigned int i = 0; i < slotIcons.size(); i++)
	{
		if (slotIcons[i]->getPlayerProperty() == NULL)
		{
			return slotIcons[i];
		}
	}
	Debug::note("ChoosePlayerPropertyMenu.getFirstVoidSlotIcon(): no void SlotIcon");
	return NULL;
}

std::vector<PlayerPropertyIcon*> ChoosePlayerPropertyMenu::getSlotIcons() const
{
	return slotIcons;
}

LobbyMenu* ChoosePlayerPropertyMenu::getLobbyMenu() const
{
	return lobby;
}

void ChoosePlayerPropertyMenu::okPressed()
{
	std::string ids = "";
	for (unsigned int i = 0; i < getSlotIcons().size(); i++)
	{
		if (getSlotIcons()[i]->getPlayerProperty() != NULL)
		{
			ids.push_back(getSlotIcons()[i]->getPlayerProperty()->getID());
		}
		else
		{
			ids.push_back(-1);
		}
		//slotPacket->getPlayerProperty()[i] = slotIcons.get(i).getPlayerProperty();
	}
	slotPacket->setIDs(ids);
	getLobbyMenu()->playerPropertySelected(slotPacket); // weist das LobbyMenu darauf hin, dass die Packets neu versendet werden müssen
	Main::getMenuList()->back();
}

void ChoosePlayerPropertyMenu::chooseIconPressed(PlayerProperty* prop)
{
	if (getFirstVoidSlotIcon() != NULL)
	{
		getFirstVoidSlotIcon()->setPlayerProperty(prop);
	}
}
