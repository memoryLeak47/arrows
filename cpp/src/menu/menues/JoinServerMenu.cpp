#include "JoinServerMenu.hpp"

#include "../../core/Main.hpp"
#include "../components/Label.hpp"
#include "../components/Button.hpp"
#include "../components/BackButton.hpp"
#include "../components/QuitButton.hpp"
#include "../components/EditField.hpp"
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
			void onClick(int mouseButton)
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
