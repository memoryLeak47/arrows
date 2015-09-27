/*
	Klasse aller Icons die im ChoosePlayerPropertyMenu gelistet werden
*/

package menu.components.icons;

import game.PlayerProperty;
import graphics.ImageID;
import menu.components.Icon;
import menu.ComponentContainer;
import misc.math.Rect;

public final class ChoosePlayerPropertyIcon extends Icon
{
	public static final int WIDTH = 40;
	public static final int HEIGHT = 40;
	private PlayerProperty playerProperty;

	public ChoosePlayerPropertyIcon(ComponentContainer parent, Rect rect, PlayerProperty playerProperty)
	{
		super(parent, rect);
		this.playerProperty = playerProperty;
	}

	public PlayerProperty getPlayerProperty() { return playerProperty; }
	@Override public ImageID getImageID() { return getPlayerProperty().getIconImageID(); }
}
