package menu.components.icons.choosable;

import core.Main;
import menu.components.icons.ChoosableIcon;
import menu.ComponentContainer;
import menu.menues.LobbyMenu;
import menu.menues.ChoosePlayerPropertyMenu;
import playerproperty.item.Item;
import graphics.ImageID;
import graphics.ImageFile;
import misc.math.pixel.PixelRect;
import network.lobby.LobbyPlayer;

public class ItemIcon extends ChoosableIcon
{
	private LobbyPlayer player;
	private int number;

	public ItemIcon(ComponentContainer parent, PixelRect rect, LobbyPlayer player, int number)
	{
		super(parent, rect);
		this.player = player;
		this.number = number;
	}

	@Override public void onClick(int mouseButton)
	{
		if (isChoosable())
		{
			Main.getMenues().add(new ChoosePlayerPropertyMenu(getLobbyMenu(), getLobbyMenu().getLocalPlayer().getItemPacket(), Item.getAllItems()));
		}
	}

	// Getter
	@Override public int getChoosePhase() { return LobbyMenu.ITEM_PHASE; }
	public Item getItem() { return player.getItemPacket().getItems()[number]; }
	@Override public ImageID getImageID() 
	{
		if ((player.getItemPacket() == null) || (player.getItemPacket().getItems()[number] == null) || (player.getItemPacket().getItems()[number].getIconImageID() == null))
		{
			return ImageFile.VOID_ICON.getImageID();
		}
		return player.getItemPacket().getItems()[number].getIconImageID();
	}
}
