package network.packets.events;

import java.awt.event.KeyEvent;

import network.packets.EventPacket;

public final class KeyReleaseEventPacket extends EventPacket
{
	private char key;

	public KeyReleaseEventPacket(KeyEvent keyEvent)
	{
		key = keyEvent.getKeyChar();
	}

	public char getKeyChar() { return key; }
}
