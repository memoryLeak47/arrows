package core.menu;

import java.awt.image.BufferedImage;
import java.awt.Graphics;
import java.awt.Color;
import javax.imageio.ImageIO;

import core.Screen;
import core.menu.Menu;
import core.menu.ComponentContainer;
import misc.math.Rect;
import misc.math.Position;

public abstract class MenuComponent extends Rect
{
	private ComponentContainer parent; // ComponentContainer wo this enthalten ist

	public MenuComponent(ComponentContainer parent, Rect rect)
	{
		super(rect);
		this.parent = parent;
	}

	protected final boolean isHovered()
	{
		return this == getParent().getHoveredComponent();
	}

	protected final boolean isFocused()
	{
		return this == getParent().getFocusedComponent();
	}

	// returnt (rekursiv) das menu in dem ich mich im Ent-effekt befinde, gebraucht für TeamPanel-button-event-weitergabe ...
	public Menu getParentMenu()
	{
		if (this instanceof Menu) // falls ich ein menu bin
		{
			return ((Menu) this); // bin ich mein parent-menu
		}
		else // falls nicht
		{
			return getParent().getParentMenu(); // returne das getParentMenu() meines parents -> Rekursion
		}
	}

	public void tick() {} // <TODO>

	// onEventFunctions: bei bedarf von den MenuComponent-unterklassen überschrieben
	public void onClick(int mouseButton) {}
	public void onMouseEnter(Position mousePos) {}
	public void onMouseMove(Position mousePos) {}
	public void onMouseExit(Position mousePos) {}	
	public void onKeyPress(char key) {}
	public void onKeyRelease(char key) {}

	public abstract void render();

	// returnt die Position auf dem fenster, (getPosition() returnt die position relativ zum parent)
	public Position getOffset() { return (Position) getParent().getOffset().plus(getPosition()); }

	// returnt den parent
	protected ComponentContainer getParent() { return parent; }

}
