package core.menu.components.icons;

import java.awt.Color;

import core.Screen;
import core.menu.ComponentContainer;
import core.menu.MenuComponent;
import game.graphics.ImageID;
import misc.math.Rect;

public abstract class Icon extends MenuComponent
{
	// private, da Icon an sich nie instanziert wird
	public Icon(ComponentContainer parent, Rect rect)
	{
		super(parent, rect);
	}

	// Diese Funktion wird nicht weiter überschrieben, da alle Icons gleich rendern. Nur das Icon und die Größe ist unterschiedlich
	@Override public final void render()
	{
		if (getParent() != null)
		{
			if (isHovered())
			{
				Screen.g().setColor(Color.GREEN);
			}
			else
			{
				Screen.g().setColor(Color.YELLOW);
			}
		}
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight());
	}

	// Diese Funktion wird von den unterklassen überschieben, um die unterschiedlichen Quellen der Image zu ermöglichen. (Mit den Quellen sind gemeint: SkillInfo, ItemInfo, AvatarInfo)
	protected abstract int getImageID(); // TODO: int -> ImageID
}
