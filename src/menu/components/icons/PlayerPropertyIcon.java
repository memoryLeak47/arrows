/*
	Klasse aller Icons die im ChoosePlayerPropertyMenu gelistet werden
*/

package menu.components.icons;

import player.property.PlayerProperty;
import graphics.ImageFile;
import graphics.ImageID;
import menu.components.Icon;
import menu.ComponentContainer;
import misc.math.pixel.PixelRect;
import misc.Debug;

public class PlayerPropertyIcon extends Icon
{
	public static final int WIDTH = 40;
	public static final int HEIGHT = 40;
	private PlayerProperty playerProperty;

	public PlayerPropertyIcon(ComponentContainer parent, PixelRect rect, PlayerProperty playerProperty)
	{
		super(parent, rect);
		this.playerProperty = playerProperty;
	}

	// Setter
	public void setPlayerProperty(PlayerProperty playerProperty)
	{
		this.playerProperty = playerProperty;
	}
	// getter
	public PlayerProperty getPlayerProperty() { return playerProperty; }
	@Override public ImageID getImageID()
	{
		// Falls noch kein 
		if (getPlayerProperty() == null)
		{
			Debug.warn("PlayerPropertyIcon.getImageID(): getPlayerProperty() == null -> returning ImageFile.VOID_ICON.getImageID()");
			return ImageFile.VOID_ICON.getImageID();
		}
		return getPlayerProperty().getIconImageID();
	}
}
