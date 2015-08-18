package network.sendable.events;

import java.awt.event.KeyEvent;

public enum Key
{
	W(), A(), S(), D() /* TODO */;

	public static Key codeToKey(int code)
	{
		if (code == KeyEvent.VK_W)
			return W;
		if (code == KeyEvent.VK_A)
			return A;
		if (code == KeyEvent.VK_S)
			return S;
		if (code == KeyEvent.VK_D)
			return D;
		return null;
	}
}
