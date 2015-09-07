package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
//import game.avatar.AvatarInfo;
//import game.graphics.ImageID;
import misc.math.Rect;

public class ItemIcon extends Icon
{
	private int itemInfo; // TODO: int itemInfo -> ItemInfo itemInfo

	public ItemIcon(ComponentContainer parent, Rect rect, int itemInfo)
	{
		super(parent, rect);
		this.itemInfo = itemInfo;
	}

	@Override public int getImageID() // TODO: int getImageID() -> ImageID getImageID()
	{
		return itemInfo;
	}
}
