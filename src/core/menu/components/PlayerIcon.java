package core.menu.components;

import java.awt.Color;

import core.Screen;
import core.menu.MenuComponent;
import core.menu.Menu;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class PlayerIcon extends MenuComponent
{
	private LobbyPlayer player; // player to display stats of

	public PlayerIcon(Menu menu, Rect rect, LobbyPlayer player)
	{
		super(menu, rect);
		this.player = player; // set player
		updateImage(); // setup image
	}

	@Override public void updateImage()
	{
		getGraphics().setColor(Color.YELLOW); // set color to yellow
		getGraphics().fillRect(0, 0, getWidth(), getHeight()); // fill rect
	}
}
