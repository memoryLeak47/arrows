package network.sendable.events;

import java.awt.event.KeyEvent;

import network.sendable.Event;

public final class KeyPress implements Event
{
	private char key;

	public KeyPress(KeyEvent keyEvent)
	{
		key = keyEvent.getKeyChar();
	}

	public char getKeyChar() { return key; }
}
