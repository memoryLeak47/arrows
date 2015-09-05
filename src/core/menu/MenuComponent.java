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
	private ComponentContainer parent; // Menu which contains this MenuComponent
	boolean enabled = true;

	public MenuComponent(ComponentContainer parent, Rect rect)
	{
		super(rect); // setup rect per copy-constructor
		this.parent = parent; // set owner menu
	}

	protected final boolean isHovered()
	{
		return this == getParent().getHoveredComponent();
	}

	protected final boolean isFocused()
	{
		return this == getParent().getFocusedComponent();
	}

	public void tick() {} // TODO why this?


	// onEventFunctions: may be overwritten by subclasses
	public void onClick(int mouseButton) {}
	public void onMouseEnter(Position mousePos) {}
	public void onMouseMove(Position mousePos) {}
	public void onMouseExit(Position mousePos) {}	
	public void onKeyPress(char key) {}
	public void onKeyRelease(char key) {}

	public abstract void render();

	// Setter Funktionen
	public void setEnabled(boolean enabled) { this.enabled = enabled; }

	// Getter Funktionen
	public Position getOffset() { return (Position) getParent().getOffset().plus(getPosition()); }

	protected ComponentContainer getParent() { return parent; }
	public Menu getParentMenu()
	{
		if (this instanceof Menu)
		{
			return ((Menu) this);
		}
		else
		{
			return getParent().getParentMenu();
		}
	}
	public boolean isEnabled() { return enabled; }
}
