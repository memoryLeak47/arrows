package core.menu.components;

import core.menu.components.Panel;
import core.menu.components.Button;
import core.menu.Menu;
import misc.math.Rect;

public class LobbyTeamPanel extends Panel
{
	private String teamName;

	public LobbyTeamPanel(Menu menu, Rect rect, String teamName)
	{
		super(menu, rect);
		this.teamName = teamName;
		addComponents();
	}

	private void addComponents()
	{
		addComponent(new Button(getParentMenu(), new Rect(20, 20, 100, 30), teamName));
	}
}
