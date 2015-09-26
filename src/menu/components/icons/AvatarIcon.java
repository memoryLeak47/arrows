package menu.components.icons;

import core.Screen;
import menu.components.icons.ChoosableIcon;
import menu.menues.ChooseAvatarMenu;
import menu.ComponentContainer;
import menu.menues.LobbyMenu;
import core.Main;
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
		if (isChoosable())
		{
			// added ein neues ChooseAvatarMenu.
			Main.getMenues().add(new ChooseAvatarMenu(new Rect(200, 0, Screen.getScreenSize().getX()-200, Screen.getScreenSize().getY()), Avatar.getAllAvatars()));
		}
	}

	// Getter
	@Override public int getChoosePhase() { return LobbyMenu.AVATAR_PHASE; }
	@Override public ImageID getImageID() 
	{
		// Wenn kein Avatar gewählt wurde, oder der Avatar keine imageID hat wird das Void-Icon angezeigt
		if (avatar == null || avatar.getIconImageID() == null)
		{
			return ImageFile.VOID_ICON.getImageID();
		}
		return avatar.getIconImageID(); 
	}
	public Avatar getAvatar() { return avatar; }
}
