package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
import core.menu.menues.LobbyMenu;
import game.item.Item;
import graphics.ImageID;
import graphics.ImageFile;
import misc.math.Rect;

public class ItemIcon extends ChoosableIcon
{
	private Item item;

	public ItemIcon(ComponentContainer parent, Rect rect, Item item)
	{
		super(parent, rect);
		this.item = item;
	}


	// Getter
	@Override public int getChoosePhase() { return LobbyMenu.ITEM_PHASE; }
	public Item getItem() { return item; }
	@Override public ImageID getImageID() 
	{
		if (item == null || item.getIconImageID() == null)
		{
			return ImageFile.VOID_ICON.getImageID(0);
		}
		return item.getIconImageID();
	}
}
