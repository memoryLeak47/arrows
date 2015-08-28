package core.menu.components;

import core.menu.components.Panel;
import core.menu.menues.LobbyMenu;
import core.menu.NetworkingMenu;
import core.menu.Menu;
import misc.math.Rect;

public class TeamListPanel extends Panel
{
	public TeamListPanel(Menu menu, Rect rect)
	{
		super(menu, rect);
		
		addComponent(new Button(getParentMenu(), new Rect(100, 50, 200, 50), "Team None") // Button "Team None"
		{
			@Override public void onClick(int mouseButton)
			{
				getParentLobbyMenu().teamPressed(NetworkingMenu.TEAM_NONE);
			}
		}); // Team None Button

		addComponent(new Button(getParentMenu(), new Rect(100, 200, 200, 50), "Team Blue") // Button "Team Blue"
		{
			@Override public void onClick(int mouseButton)
			{
				getParentLobbyMenu().teamPressed(NetworkingMenu.TEAM_BLUE);
			}
		}); // Team Blue Button

		addComponent(new Button(getParentMenu(), new Rect(100, 350, 200, 50), "Team Red") // Button "Team Red"
		{
			@Override public void onClick(int mouseButton)
			{
				getParentLobbyMenu().teamPressed(NetworkingMenu.TEAM_RED);
			}
		}); // Team Red Button

		addComponent(new Button(getParentMenu(), new Rect(100, 500, 200, 50), "Team Green") // Button "Team Green"
		{
			@Override public void onClick(int mouseButton)
			{
				getParentLobbyMenu().teamPressed(NetworkingMenu.TEAM_GREEN);
			}
		}); // Team Green Button
	}

	@Override public void updateImage()
	{
		super.updateImage();
	}

	public LobbyMenu getParentLobbyMenu() { return (LobbyMenu) getParentMenu(); }
}
