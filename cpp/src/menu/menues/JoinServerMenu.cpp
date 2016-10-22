#include "JoinServerMenu.hpp"

#include <core/Main.hpp>
#include <menu/MenuList.hpp>
#include <menu/components/Label.hpp>
#include <menu/components/Button.hpp>
#include <menu/components/BackButton.hpp>
#include <menu/components/QuitButton.hpp>
#include <menu/components/EditField.hpp>
#include "ClientLobbyMenu.hpp"

JoinServerMenu::JoinServerMenu()
{
	addComponent(new Label(this, PixelRect(400, 10, 200, 40), "Join Server")); // add Label "Join Server"
	addComponent(new BackButton(this, PixelVector(10, 500))); // add Button "back"
	addComponent(ipField = new EditField(this, PixelRect(300, 200, 100, 20), "192.168.178."));

	class JoinServerButton : public Button
	{
		public:
			JoinServerButton(JoinServerMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			virtual void onPress() override
			{
				((JoinServerMenu*) getParent())->joinServer();
			}
	};
	addComponent(new JoinServerButton(this, PixelRect(420, 200, 100, 20), "Join Server"));
}

void JoinServerMenu::joinServer()
{
	Main::getMenuList()->addMenu(new ClientLobbyMenu(ipField->getText()));
}
