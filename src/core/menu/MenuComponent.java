package core.menu;

import misc.math.Rect;
import misc.math.Position;
import core.menu.Menu;

public abstract class MenuComponent extends Rect
{
	private Menu menu;

	public MenuComponent(Menu menu, Rect rect)
	{
		super(rect);
		this.menu = menu;
	}

	protected final boolean isHovered()
	{
		return this == menu.getHoveredComponent();
	}

	protected final boolean isFocused()
	{
		return this == menu.getFocusedComponent();
	}

	public void tick() {}
	public abstract void render();

	// TODO: onEventFunctions
	public void onClick(int mouseButton) {}
	public void onMouseEnter(Position mousePos) {}
	public void onMouseMove(Position mousePos) {}
	public void onMouseExit(Position mousePos) {}	
	public void onKeyPress(char key) {}
	public void onKeyRelease(char key) {}
}
