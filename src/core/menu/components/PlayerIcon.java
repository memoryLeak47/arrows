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
	}

	public void setPlayer(LobbyPlayer player)
	{
		this.player = player;
	}

	public void render()
	{
		Screen.g().setColor(Color.YELLOW);
		Screen.g().fillRect(getPosition().getX(), getPosition().getY(), getSize().getX(), getSize().getY());
	}
}
