package menu.event.events;

import java.awt.event.KeyEvent;

import menu.event.Event;

public final class KeyPressEvent extends Event
{
	private char key;

	public KeyPressEvent(KeyEvent keyEvent)
	{
		key = keyEvent.getKeyChar();
	}

	public char getKeyChar() { return key; }
}
