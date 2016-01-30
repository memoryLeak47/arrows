package menu.event.events;

import java.awt.event.MouseEvent;

import misc.Debug;
import menu.event.Event;

public final class MouseButtonReleaseEvent extends Event
{
	private int mouseButton;

	public MouseButtonReleaseEvent(MouseEvent event)
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
			Debug.warn("MouseButtonReleaseEvent.<init> bad mouse button(" + event.getButton() + ")", Debug.Tags.EXTENDED_WARNINGS);
		}
	}

	public int getMouseButton() { return mouseButton; }
}
