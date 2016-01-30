package menu.event.events;

import java.awt.event.KeyEvent;

import menu.event.Event;

public final class KeyReleaseEvent extends Event
{
	private char key;

	public KeyReleaseEvent(KeyEvent keyEvent)
	{
		key = keyEvent.getKeyChar();
	}

	public char getKeyChar() { return key; }
}
