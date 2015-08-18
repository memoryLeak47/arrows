package network.sendable.events;

import java.awt.event.MouseEvent;

import network.sendable.Event;
import network.sendable.events.MouseButton;

public final class MouseButtonRelease implements Event
{
	MouseButton mouseButton;

	public MouseButtonRelease(MouseEvent event)
	{
		if (event.getButton() == event.BUTTON1)
		{
			mouseButton = MouseButton.LEFT;
		}
		else if (event.getButton() == event.BUTTON2)
		{
			mouseButton = MouseButton.MIDDLE;
		}
		else if (event.getButton() == event.BUTTON3)
		{
			mouseButton = MouseButton.RIGHT;
		}
		else
		{
			System.out.println("bad mouse button");
		}
	}

	public MouseButton getMouseButton() { return mouseButton; }
}
