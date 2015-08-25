package network.sendable.events;

import java.awt.event.KeyEvent;

import network.sendable.Event;

public final class KeyRelease implements Event
{
	private char key;

	public KeyRelease(KeyEvent keyEvent)
	{
		key = keyEvent.getKeyChar();
	}

	public char getKeyChar() { return key; }
}
