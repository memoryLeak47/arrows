package menu.event.events;

import java.awt.event.MouseEvent;

import misc.math.pixel.PixelPosition;
import menu.event.Event;

public final class MouseMoveEvent extends Event
{
	private final PixelPosition position; // where the mouse moved to

	public MouseMoveEvent(MouseEvent event)
	{
		position = new PixelPosition(event.getX(), event.getY());
	}

	public PixelPosition getMousePosition() { return position; }
}
