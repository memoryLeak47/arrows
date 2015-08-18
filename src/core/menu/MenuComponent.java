package core.menu;

import misc.math.Rect;
import misc.math.Position;
import core.menu.Menu;
import network.sendable.events.MouseButton;

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
		return false; // TODO
	}

	protected final boolean isFocused()
	{
		return this == menu.getFocusedComponent();
	}

	public void tick() {}
	public abstract void render();

	// TODO: onEventFunctions
	public void onClick(MouseButton mouseButton) {}
	public void onMouseEnter(Position mousePos) {}
	public void onMouseMove(Position mousePos) {}
	public void onMouseExit(Position mousePos) {}	
}
