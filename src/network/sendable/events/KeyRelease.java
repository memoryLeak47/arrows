package network.sendable.events;

import java.awt.event.KeyEvent;

import network.sendable.Event;

public final class KeyRelease implements Event
{
	Key key;

	public KeyRelease(KeyEvent keyEvent)
	{
		key = Key.codeToKey(keyEvent.getKeyCode());
	}
}
