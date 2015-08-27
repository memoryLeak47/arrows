package core.menu.menues;

import java.net.InetAddress;

import core.Main;
import core.menu.NetworkingMenu;
import network.Packet;

public abstract class GameInterface extends NetworkingMenu
// gives Event to NetworkDevice.onEvent(event)
{
	@Override public boolean isFullscreen() { return true; }
}
