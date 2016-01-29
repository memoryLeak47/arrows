#include "CreateServerMenu.h"

#include "../../core/Main.h"
#include "../components/Button.h"
#include "../components/BackButton.h"
#include "../components/Label.h"
#include "ServerLobbyMenu.h"

CreateServerMenu::CreateServerMenu()
{
	addComponent(new Label(this, PixelRect(400, 10, 200, 40), "Create Server")); // add Label "Create Server"

	class CreateServerButton : public Button
	{
		public:
			CreateServerButton(CreateServerMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton) // on click
			{
				Main::getMenuList()->addMenu(new ServerLobbyMenu()); // add new ServerLobbyMenu
			}
	};

	addComponent(new CreateServerButton(this, PixelRect(300, 300, 100, 100), "Create Server")); // add Button "Create Server"
	addComponent(new BackButton(this, PixelVector(10, 500))); // add backbutton
}
