package network.sendable.events;

import java.awt.event.MouseEvent;
import network.sendable.Event;

public final class MouseMove implements Event
{
	private final int x, y; // where the mouse moved to

	public MouseMove(MouseEvent event)
	{
		x = event.getX();
		y = event.getY();
	}
}
