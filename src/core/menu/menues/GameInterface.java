package core.menu.menues;

import java.net.InetAddress;

import core.Main;
import core.menu.NetworkingMenu;
import network.Packet;

public class GameInterface extends NetworkingMenu
// gives Event to NetworkDevice.onEvent(event)
{
	public GameInterface()
	{
		Main.getNetworkDevice().setMenu(this); // when receiving a packet give it to this.handlePacket(...)
	}

	// TODO much
	@Override public void handlePacket(Packet packet, InetAddress ip) {/*TODO*/}
	@Override public boolean isFullscreen() { return true; }
}
