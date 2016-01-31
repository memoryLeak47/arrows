#include "LobbyMenu.h"

#include "../components/Label.h"
#include "../../core/Main.h"

LobbyMenu::LobbyMenu()
{
	phase = TEAM_PHASE;
	
	addComponent(new Label(this, PixelRect(300, 10, 150, 20), "Lobby"));
	addComponent(teamListPanel = new TeamListPanel(this, PixelRect(100, 100, 600, 600)));

	class LockButton : public Button
	{
		public:
			LockButton(LobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				((LobbyMenu*)getParent())->lockPressed();
			}
	};
	addComponent(lockButton = new LockButton(this, PixelRect(SCREEN_SIZE_X - 250, 600, 200, 60), "Lock"));

	addComponent(miniMap = new LobbyMiniMap(this, PixelRect(SCREEN_SIZE_X - 250, 100, 200, 140)));

	class DisconnectButton : public Button
	{
		public:
			DisconnectButton(LobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			void onClick(int mouseButton)
			{
				((LobbyMenu*)getParent())->disconnectPressed();
			}
	};
	addComponent(new DisconnectButton(this, PixelRect(20, 500, 20, 20), "Disconnect"));

}
