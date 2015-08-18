package network.sendable.events;

import java.awt.event.KeyEvent;

import network.sendable.Event;
import network.sendable.events.Key;

public final class KeyPress implements Event
{
	Key key;

	public KeyPress(KeyEvent keyEvent)
	{
		key = Key.codeToKey(keyEvent.getKeyCode());
	}
}
