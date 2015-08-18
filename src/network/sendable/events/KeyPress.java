package network.sendable.events;

import network.sendable.Event;
import network.sendable.events.Key;

public final class KeyPress implements Event
{
	Key key;
	int count; // TODO: needed??
}
