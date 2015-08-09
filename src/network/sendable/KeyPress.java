package network.sendable;

import network.sendable.Event;
import network.sendable.Key;

public final class KeyPress implements Event
{
	Key key;
	int count; // TODO: needed??
}
