package menu.components;

import java.awt.Color;

import core.Screen;
import menu.MenuComponent;
import menu.ComponentContainer;
import misc.math.Rect;

public class Button extends MenuComponent
{
	private String caption;
	
	public Button(ComponentContainer parent, Rect rect, String caption)
	{
		super(parent, rect); // setup menu which contains this Button and the rect of the button
		this.caption = caption; // set caption
	}

	@Override public void render() // draws content on getGraphics() -> on image
	{
		// Farbe abfragen, je nachdem, ob enabled oder nicht
		if (isEnabled()) // Falls der Button enabled ist
		{
			Screen.g().setColor(Color.RED); // Farbe auf RED setzen
		}
		else // Falls Button disabled ist
		{
			Screen.g().setColor(Color.GRAY); // Farbe auf GRAY setzen
		}
		Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight()); // "Körper" des Buttons zeichnen
		Screen.g().setColor(Color.BLACK); // Farbe auf schwarz setzen für die Schrift
		Screen.g().drawString(caption, getOffset().getX() + 1, getOffset().getY() + 12); // Caption auf den Button zeichnen
	}
}
