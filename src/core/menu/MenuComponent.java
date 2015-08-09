package core.menu;

public abstract class MenuComponent
{
	// TODO: Vec2D position, size;
	public abstract void tick();
	public abstract void render();

	/* TODO: onEventFunctions
		public void onGainFocus() {}
		public void onLoseFocus() {}
		public void onClick(MousePos?) {}
		public void onMouseEnter(MousePos?) {}
		public void onMouseMove(MousePos?) {}
		public void onMouseExit(MousePos?) {}
		…
	*/
}
