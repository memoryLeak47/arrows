package core.menu.components.icons;

import core.menu.components.icons.Icon;
import core.menu.ComponentContainer;
//import game.avatar.AvatarInfo;
//import game.graphics.ImageID;
import misc.math.Rect;

public class AvatarIcon extends Icon
{
	private int avatarInfo; // TODO: int avatarinfo -> AvatarInfo avatarInfo

	public AvatarIcon(ComponentContainer parent, Rect rect, int avatarInfo)
	{
		super(parent, rect);
		this.avatarInfo = avatarInfo;
	}

	@Override public int getImageID() // TODO: int getImageID() -> ImageID getImageID()
	{
		return avatarInfo;
	}
}
