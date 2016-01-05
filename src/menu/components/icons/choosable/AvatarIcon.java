package menu.components.icons.choosable;

import core.Screen;
import menu.components.icons.ChoosableIcon;
import menu.ComponentContainer;
import menu.menues.LobbyMenu;
import menu.menues.ChoosePlayerPropertyMenu;
import core.Main;
import playerproperty.avatar.Avatar;
import playerproperty.avatar.avatars.*;
import graphics.ImageID;
import graphics.ImageFile;
import misc.math.pixel.PixelRect;
import network.lobby.LobbyPlayer;

public class AvatarIcon extends ChoosableIcon
{
	private LobbyPlayer player;

	public AvatarIcon(ComponentContainer parent, PixelRect rect, LobbyPlayer player)
	{
		super(parent, rect);
		this.player = player;
	}

	// onEvent
	@Override public void onClick(int mouseButton)
	{
		if (isChoosable())
		{
			// added ein neues ChoosePlayerPropertyMenu
			Main.getMenues().add(new ChoosePlayerPropertyMenu(getLobbyMenu(), getLobbyMenu().getLocalPlayer().getAvatarPacket(), Avatar.getAllAvatars()));
		}
	}

	// getter
	@Override public int getChoosePhase() { return LobbyMenu.AVATAR_PHASE; }
	@Override public ImageID getImageID() 
	{
		// Wenn kein Avatar gewählt wurde, oder der Avatar keine imageID hat wird das Void-Icon angezeigt
		if ((player.getAvatarPacket() == null) || (player.getAvatarPacket().getAvatar() == null) || (player.getAvatarPacket().getAvatar().getIconImageID() == null))
		{
			return ImageFile.VOID_ICON.getImageID();
		}
		return player.getAvatarPacket().getAvatar().getIconImageID();
	}
	public Avatar getAvatar() { return player.getAvatarPacket().getAvatar(); }
}
