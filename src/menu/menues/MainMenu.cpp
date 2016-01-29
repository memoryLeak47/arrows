#include "MainMenu.h"

#include "../../core/Main.h"
#include "../components/EditField.h"
#include "../components/Button.h"
#include "../components/QuitButton.h"
#include "../components/Label.h"
#include "CreateServerMenu.h"
#include "JoinServerMenu.h"

MainMenu::MainMenu()
{
	addComponent(new Label(this, PixelRect(400, 10, 200, 40), "Main Menu"));
	addComponent(new EditField(this, PixelRect(200, 200, 100, 100), "text"));

	class CreateServerButton : public Button
	{
		public:
			CreateServerButton(MainMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				Main::getMenuList()->addMenu(new CreateServerMenu());
			}
	};
	addComponent(new CreateServerButton(this, PixelRect(300, 100, 100, 30), "Create Server"));

	class JoinServerButton : public Button
	{
		public:
			JoinServerButton(MainMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				Main::getMenuList()->addMenu(new JoinServerMenu());
			}
		
	};
	addComponent(new JoinServerButton(this, PixelRect(300, 150, 100, 30), "Join Server"));

	class LogoutButton : public Button
	{
		public:
			LogoutButton(MainMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				Main::logout();
				Main::getMenuList()->back();
			}
	};
	addComponent(new LogoutButton(this, PixelRect(140, 500, 100, 30), "Logout"));

	addComponent(new QuitButton(this, PixelVector(20, 500)));
}
