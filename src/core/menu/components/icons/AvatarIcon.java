package core.menu.components.icons;

import core.menu.components.icons.ChoosableIcon;
import core.menu.ComponentContainer;
import core.menu.menues.LobbyMenu;
import game.avatar.Avatar;
import game.avatar.avatars.*;
import graphics.ImageID;
import graphics.ImageFile;
import misc.math.Rect;

public class AvatarIcon extends ChoosableIcon
{
	private Avatar avatar;

	public AvatarIcon(ComponentContainer parent, Rect rect, Avatar avatar)
	{
		super(parent, rect);
		this.avatar = avatar;
	}

	// onEvent
	@Override public void onClick(int mouseButton)
	{
		// TODO
	}

	// Getter
	@Override public int getChoosePhase() { return LobbyMenu.AVATAR_PHASE; }
	@Override public ImageID getImageID() 
	{
		if (avatar == null || avatar.getIconImageID() == null)
		{
			return ImageFile.VOID_ICON.getImageID();
		}
		return avatar.getIconImageID(); 
	} // works
	public Avatar getAvatar() { return avatar; }
}
