package core.menu.components;

import java.awt.Color;

import core.menu.MenuComponent;
import network.lobby.LobbyPlayer;
import core.Screen;
import misc.math.Rect;
import core.menu.Menu;

public class PlayerIcon extends MenuComponent
{
	private LobbyPlayer player;

	public PlayerIcon(Menu menu, Rect rect)
	{
		super(menu, rect);
		updateImage();
	}

	public void setPlayer(LobbyPlayer player)
	{
		this.player = player;
	}

	@Override public void updateImage()
	{
		getGraphics().setColor(Color.YELLOW);
		getGraphics().fillRect(0, 0, getWidth(), getHeight());
	}
}
