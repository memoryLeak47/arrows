package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
import game.item.Item;
import game.graphics.ImageID;
import misc.math.Rect;

public class ItemIcon extends Icon
{
	private Item item;

	public ItemIcon(ComponentContainer parent, Rect rect, Item item)
	{
		super(parent, rect);
		this.item = item;
	}

	@Override public ImageID getImageID()
	{
		return item.getIconImageID();
	}
}
