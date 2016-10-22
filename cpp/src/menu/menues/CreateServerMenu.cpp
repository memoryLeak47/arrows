#include "CreateServerMenu.hpp"

#include <core/Main.hpp>
#include <menu/MenuList.hpp>
#include <menu/components/Button.hpp>
#include <menu/components/BackButton.hpp>
#include <menu/components/Label.hpp>
#include "ServerLobbyMenu.hpp"

CreateServerMenu::CreateServerMenu()
{
	addComponent(new Label(this, PixelRect(400, 10, 200, 40), "Create Server")); // add Label "Create Server"

	class CreateServerButton : public Button
	{
		public:
			CreateServerButton(CreateServerMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			virtual void onPress() override
			{
				Main::getMenuList()->addMenu(new ServerLobbyMenu()); // add new ServerLobbyMenu
			}
	};

	addComponent(new CreateServerButton(this, PixelRect(300, 300, 100, 100), "Create Server")); // add Button "Create Server"
	addComponent(new BackButton(this, PixelVector(10, 500))); // add backbutton
}
