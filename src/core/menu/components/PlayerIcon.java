package core.menu.components;

import java.awt.Color;

import core.Screen;
import core.menu.MenuComponent;
import core.menu.ComponentContainer;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class PlayerIcon extends MenuComponent
{
	private LobbyPlayer player; // player to display stats of

	public PlayerIcon(ComponentContainer parent, Rect rect, LobbyPlayer player)
	{
		super(parent, rect);
		this.player = player; // set player
	}

	@Override public void render()
	{
		Screen.g().setColor(Color.YELLOW); // set color to yellow
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight()); // fill rect
	}
}
