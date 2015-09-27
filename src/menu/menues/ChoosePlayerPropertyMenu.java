package menu.menues;

import core.Screen;
import menu.Menu;
import menu.components.icons.ChoosePlayerPropertyIcon;
import misc.math.Rect;
import game.PlayerProperty;
import network.lobby.packets.PlayerPropertyUserPacket;

public class ChoosePlayerPropertyMenu extends Menu
{
	private PlayerPropertyUserPacket playerPacket;
	private PlayerProperty[] playerProperties;

	public ChoosePlayerPropertyMenu(PlayerPropertyUserPacket playerPacket, PlayerProperty[] playerProperties)
	{
		super(new Rect(200, 0, Screen.WIDTH-200, Screen.HEIGHT));
		this.playerPacket = playerPacket;
		this.playerProperties = playerProperties;

		for (int i = 0; i < playerProperties.length; i++)
		{
			getComponents().add(new ChoosePlayerPropertyIcon(
					this,
					new Rect(40 + i * (ChoosePlayerPropertyIcon.WIDTH + 5), 40, ChoosePlayerPropertyIcon.WIDTH, ChoosePlayerPropertyIcon.HEIGHT), 
					playerProperties[i]));
		}
	}
}
