package network.sendable.events;

import java.awt.event.MouseEvent;

import network.sendable.Event;

public final class MouseButtonPress implements Event
{
	int mouseButton;

	public MouseButtonPress(MouseEvent event)
	{
		if (event.getButton() == event.BUTTON1)
		{
			mouseButton = 1;
		}
		else if (event.getButton() == event.BUTTON2)
		{
			mouseButton = 2;
		}
		else if (event.getButton() == event.BUTTON3)
		{
			mouseButton = 3;
		}
		else
		{
			System.out.println("bad mouse button");
		}
	}

	public int getMouseButton() { return mouseButton; }
}
