package menu;

import java.awt.image.BufferedImage;
import java.awt.Graphics;
import java.awt.Color;
import javax.imageio.ImageIO;

import core.Screen;
import menu.Menu;
import menu.ComponentContainer;
import misc.math.menu.MenuRect;
import misc.math.menu.MenuPosition;

public abstract class MenuComponent extends MenuRect
{
	private boolean enabled = true;
	private ComponentContainer parent; // ComponentContainer wo this enthalten ist

	public MenuComponent(ComponentContainer parent, MenuRect rect)
	{
		super(rect);
		this.parent = parent;
	}

	protected final boolean isHovered()
	{
		if (getParent() != null && getParent().getHoveredComponent() != null)
		{
			return this == getParent().getHoveredComponent();
		}
		return false;
		// return Screen.getCursorMenuPosition().inMenuRect(new MenuRect(getOffset(), getSize()));
	}

	protected final boolean isFocused()
	{
		return this == getParent().getFocusedComponent();
	}

	// tick, bei bedarf überschrieben
	public void tick() {}

	// onEventFunctions: bei bedarf von den MenuComponent-unterklassen überschrieben
	public void onClick(int mouseButton) {}
	public void onMouseEnter(MenuPosition mousePos) {}
	public void onMouseMove(MenuPosition mousePos) {}
	public void onMouseExit(MenuPosition mousePos) {}	
	public void onKeyPress(char key) {}
	public void onKeyRelease(char key) {}

	public abstract void render();

	// Setter Funktionen
	public void setEnabled(boolean enabled) { this.enabled = enabled; }

	// Getter

	// MenuPosition relativ zum Screen
	public MenuPosition getOffset() { return (MenuPosition) getParent().getOffset().plus(getPosition()); }

	// returnt den parent
	protected ComponentContainer getParent() { return parent; }

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

	public boolean isEnabled() { return enabled; }
}
