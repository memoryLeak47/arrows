package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
import game.avatar.Avatar;
import graphics.ImageID;
import misc.math.Rect;

public class AvatarIcon extends Icon
{
	private Avatar avatar;

	public AvatarIcon(ComponentContainer parent, Rect rect, Avatar avatar)
	{
		super(parent, rect);
		this.avatar = avatar;
	}

	@Override public ImageID getImageID()
	{
		return avatar.getIconImageID();
	}
}
