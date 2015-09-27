package menu.components;

import java.awt.Color;

import core.Screen;
import menu.ComponentContainer;
import menu.MenuComponent;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.Rect;

public abstract class Icon extends MenuComponent
{
	// private, da Icon an sich nie instanziert wird
	public Icon(ComponentContainer parent, Rect rect)
	{
		super(parent, rect);
	}

	// Zeichnet einen Rand und unterkomponenten
	@Override public void render()
	{
		if (getImageID() == null)
		{
			Debug.error("Icon.render tries to render null IconID");
			return;
		}
		if (ImageFile.getImageByImageID(getImageID()) == null)
		{
			Debug.error("Icon.render tries to render null Icon");
			return;
		}
		Screen.g().drawImage(ImageFile.getImageByImageID(getImageID()), getOffset().getX(), getOffset().getY(), getWidth(), getHeight(), null);
	}

	// Diese Funktion wird von den unterklassen überschieben, um die unterschiedlichen Quellen der Image zu ermöglichen. (Mit den Quellen sind gemeint: Skill, Item, Avatar)
	public abstract ImageID getImageID();
}
